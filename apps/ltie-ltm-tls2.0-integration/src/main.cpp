

/*
Author: Tann tan
Email: tan.t@ltlabs.co
*/
#include "../../libs/version.h"
#include "ltlabs/ltlabs.h"
#include <M5Tough.h>
#include "ltlabs/secret.h"
#include <WiFi.h>
#include "ui/ui.h"
#include <SocketIoClient.h>
#include <WiFiManager.h>
#include <qrcode.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <time.h>
#include <LittleFS.h>
#include <esp32fota.h>

bool isGetState = false;
bool isSuccess = false;

int buffer = 0;
int dailyOutputCount;
int len_mc = 0;

unsigned long timeOut = 2000;
unsigned long currentTimeOut;
unsigned long currentRetrive;
unsigned long current;

static BaseType_t app_cpu = 1;
static BaseType_t pro_cpu = 0;

const char *title[] = {"Device Name", "Line ID/Area ID", "Device Mac", "IP", "SN", "Company"}; // dummy data
const char *test[] = {}; 

const char *app[5];

TaskHandle_t guiTask;
TaskHandle_t socketTaskhandler;
/////////////////////////// GUI
lv_obj_t * msgBox;
lv_obj_t * errMsgBox;
lv_obj_t * errLabel;
/// @brief /////////
// socket io client
SocketIoClient socketioclient;
WiFiManager wm;

LTLABS ltlabs;
LTLABS::GlobalConfig global;
LTLABS::ltmconfig ltm;
LTLABS::LTIE ltie;

bool isReported = false;

esp32FOTA esp32fota("esp32-fota-http", VERSION, false, true);
const char* manifest_url = "https://esp32binfile.s3.ap-southeast-1.amazonaws.com/firmware.json";
bool getUpdate = false;

JsonArray ltmjson;
void readConfigure()
{
    File file = LittleFS.open( "/config.json", "r");
    if(!file){
        Serial.print("No file Is found");
        return;
    };

    String payload = file.readString();
    StaticJsonDocument<1500> doc;
    DeserializationError err = deserializeJson(doc, payload);
    if(err)
    {
        Serial.print("Read config fails!!");
        return;
    }
    JsonObject conf = doc["config"];
    global={conf["timeZone"], conf["deviceName"].as<const char*>(), conf["lineID"].as<const char*>(), conf["lineSetupId"].as<int>(), conf["x-factory-id"].as<int>(), conf["factoryId"]};

    JsonArray myapp = conf["app"];
    JsonObject ltm = conf["ltm"];
    JsonArray machines = ltm["machines"];

    buffer = myapp.size();
    for(int i=0;i<myapp.size();i++)
    {
        app[i] = myapp[i].as<const char*>();
    }
    len_mc= machines.size();
    if(len_mc > 1)
    {
        for(int i = 0; i<len_mc;i++)
        {
            int sta = machines[i]["station"];
            machineList(machines[i]["machinesSubType"], machines[i]["machineCode"], std::to_string(sta).c_str());
        }
    }
    if(len_mc >! 1 && len_mc != 0)
    {
        int sta = machines[0]["station"];
        lv_label_set_text(ui_lineIdText1, std::to_string(sta).c_str());
        lv_label_set_text(ui_lineIdText2, machines[0]["machineCode"]);
    }
    file.close();
}
void ui_event_redbtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);  
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_LONG_PRESSED) {
        if(len_mc > 1) lv_scr_load(ui_listOfMachine);
        if(len_mc == 1)
        {
            lv_scr_load(ui_confirmScreen);
        }
    }
}
void qr_code()
{
    uint32_t qr = ESP.getEfuseMac();

    String hostString = String(WIFI_getChipId(),HEX);
    hostString.toUpperCase();

    // char hostString[16] = {0};
    // sprintf(hostString, "%06X", ESP.getChipId()); 

    String qrtxt = "WIFI:T:WPA;S:M5Tough_AP;P:1234512345;;";
    msgBox = lv_msgbox_create(lv_scr_act(), "WiFi-Connect", "", NULL, true);
    lv_obj_move_background(msgBox);

    lv_obj_t *wifiqr = lv_qrcode_create(msgBox, 150, lv_color_hex(0x173f5f),lv_color_hex(0xeeeeee));
    lv_qrcode_update(wifiqr, qrtxt.c_str(), strlen(qrtxt.c_str()));
    lv_obj_center(wifiqr);
}

// GUI Update
void ui_event_yesConfigmBtn(lv_event_t * e)
{
    const char *lineID;
    const char *station;
    const char *MC;

    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
       lineID = lv_label_get_text(ui_lineIdText);
       station = lv_label_get_text(ui_lineIdText1);
       MC = lv_label_get_text(ui_lineIdText2); 
       char output[255];
       StaticJsonDocument<512> s;
       s["remarks"] = "From M5Stack report";
       s["station"] = station;
       s["machineCode"] = MC;
       s["factoryCode"] = global.companyId;
       // response back
       s["extra_event"] = "response";
       s["roomId"] = global.lineID;
       s["app"] = "LTM";
       s["event"] = "post";
       serializeJson(s, output);
        socketioclient.emit("ltieRefresh", output);
       lv_scr_load(ui_home);
    }
}

void get_data_api()
{
    char output[255];
    StaticJsonDocument<256> s;
    s["extra_event"] = "LTM";
    s["roomId"] = global.lineID;
    s["app"] = "LTM";
    s["event"] = "get";
    s["factoryId"] = global.companyId;
    serializeJson(s, output);
    socketioclient.emit("ltieRefresh", output);
}
void greenButtonEvent(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        
    }
}

void updateGUI(void *params)
{
    vTaskDelay(500/portTICK_PERIOD_MS);
    String hostString = String(WIFI_getChipId(),HEX);
    hostString.toUpperCase();

    ltlabs.ui();
    qr_code();
    IPAddress ipadd = WiFi.localIP();
    String ipStr = ipadd.toString();
    String mac = WiFi.macAddress();
    lv_label_set_text(ui_lineIdText,global.lineID);
    lv_obj_add_event_cb(ui_redbtn, ui_event_redbtn, LV_EVENT_ALL, NULL);
    ui_list("Device Name:", global.deviceName);
    ui_list("Line ID/Area ID", global.lineID);
    ui_list("Serial Number:", hostString.c_str());
    ui_list("IP:", ipStr.c_str());
    ui_list("Mac address:", mac.c_str());
    ui_list("Company:", std::to_string(global.xfactoryId).c_str());
    ui_list("Firmware Version:", VERSION);

    lv_obj_add_event_cb(ui_yesConfigmBtn, ui_event_yesConfigmBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_greenBtn, greenButtonEvent, LV_EVENT_ALL, NULL);
    lv_label_set_text(ui_brandLabel, global.lineID);

    errMsgBox  = lv_msgbox_create(lv_scr_act(), "Message!!", "", NULL, true);
    lv_obj_set_size(errMsgBox, lv_pct(0), lv_pct(0));
    lv_obj_move_foreground(errMsgBox);

    errLabel = lv_label_create(errMsgBox);
    lv_label_set_text(errLabel, "error message!! ");
    if(WiFi.status() != WL_CONNECTED)
    {
        lv_obj_del(msgBox);
    }
    while (1)
    {   
        ltlabs.currentMillis = millis();
        ltlabs.hardwareButtonEvent();
        if(ltlabs.btnRedStateLongPress)
        {
            if(len_mc > 1) lv_scr_load(ui_listOfMachine);
            if(len_mc == 1)
            {
                lv_scr_load(ui_confirmScreen);
            }
        }

        ltie.count = ltlabs.count;
        lv_label_set_text(countLabel, std::to_string(ltlabs.count).c_str());
        lv_label_set_text(ui_totalOutput, std::to_string(ltie.subTotal).c_str());
        lv_label_set_text(ui_valueDayOut, std::to_string(dailyOutputCount).c_str());
        lv_label_set_text(ui_valueDayOut1, std::to_string(ltie.targetOpt).c_str());
        lv_label_set_text(ui_quantity, std::to_string(ltie.quantity).c_str());
        lv_obj_set_style_img_recolor_opa(ui_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_timer_handler();
        lv_bar_set_value(ui_Bar2, ltlabs.interval, LV_ANIM_ON);
        
        vTaskDelay(5/portTICK_PERIOD_MS);
    }  
}

void eventConfig(const char *payload, size_t length)
{
    LittleFS.remove("/config.json");

    File file = LittleFS.open("/config.json", FILE_WRITE);
    if(!file) Serial.print("File not found!!");

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if(error)
    {
        Serial.print("error while derserialize");
        return;
    }

    JsonObject conf = doc["config"];
    char output[255];
    StaticJsonDocument<1024> ser;
    serializeJson(conf, output);

    if (serializeJson(doc, file) == 0) {
        Serial.println(F("Failed to write to file"));
        file.print(output);
        
        ESP.restart();
    }
    // Close the file
    file.close();
    vTaskDelay(3000/ portTICK_PERIOD_MS);
    ESP.restart();
}

String socketEmit(const char *extra_event, const char *app, const char *event)
{
        char output[200];
        StaticJsonDocument<192> serial1;

        serial1["name"] = global.deviceName;
        serial1["roomId"] = global.lineID;
        serial1["lineSetupId"] = global.lineSetupID;
        serial1["app"] = app;
        serial1["factoryId"] = global.xfactoryId;
        serial1["extra_event"] = extra_event;
        serial1["event"] = event;
        serializeJson(serial1, output);
        return output;
}
void ltie_event(const char *payload, size_t length)
{
    DynamicJsonDocument doc(1024);
    DeserializationError err = deserializeJson(doc, payload);
    if(err)
    {
        Serial.print("Error on Deserialize");
        Serial.print(err.f_str());
        doc.clear();
        return;
    }
    ltie.totalOutput = doc["totalOutput"];
    ltie.quantity = doc["quantity"];
    ltie.dailyOpt = doc["dailyTotal"];
    ltie.targetOpt = doc["dailyTarget"];

    if(dailyOutputCount < ltie.dailyOpt || ltie.subTotal < ltie.totalOutput)
    {
        dailyOutputCount = ltie.dailyOpt;
        ltie.subTotal = ltie.totalOutput;
    }
    
    doc.clear();
    isGetState = true;
    
}
void post_data_to_api(int numberOfCount, const char *event, const char *appName)
{
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }

    char date[50];
    char time[25];
    strftime(date, sizeof(date), "%Y-%m-%d", &timeinfo);
    strftime(time, sizeof(time), "%H:%M:%S", &timeinfo);
    char output_ltie[200];
    StaticJsonDocument<192> doc;
    doc["lineSetupId"] = global.lineSetupID;
    doc["tranDt"] = date; 
    doc["tranTime"] = time;
    doc["outputQty"] = numberOfCount;
    doc["factoryId"] = global.xfactoryId;
    doc["extra_event"] = "response";
    doc["roomId"] = global.lineID;
    doc["app"] = appName;
    doc["event"] = event;
    serializeJson(doc, output_ltie);

    socketioclient.emit("ltieRefresh", output_ltie);

    dailyOutputCount = ltie.dailyOpt + ltlabs.count;
    ltie.subTotal = ltie.totalOutput + ltlabs.count;
    ltlabs.count = 0;
    doc.clear();
}
void eventConnect(const char *payload, size_t length)
{
    String hostString = String(WIFI_getChipId(),HEX);
    hostString.toUpperCase();
    
    readConfigure();
    char output[255];
    StaticJsonDocument<512> serialized;
    Serial.print(strlen(global.deviceName));
    if(strlen(global.deviceName) < 1)
    {
        lv_label_set_text(ui_brandLabel, hostString.c_str());
        serialized["name"] = hostString;
        serialized["roomId"] = hostString;
        serialized["app"] = "NEW";
        serializeJson(serialized, output);
        socketioclient.emit("roomJoin", output); 
    }
    else{
        for(int i=0; i<buffer;i++)
        {
            serialized["name"] = global.deviceName;
            serialized["roomId"] = global.lineID;
            serialized["app"] = app[i];
            serializeJson(serialized, output);
            socketioclient.emit("roomJoin", output); 
        }
    }
    
}
void updateData() {
    vTaskDelay(1000/portTICK_PERIOD_MS);
   
    socketioclient.emit("ltieRefresh", socketEmit("ltie_get", "LTIE", "ltie_get").c_str());
    vTaskDelay(1000/portTICK_PERIOD_MS);
    get_data_api();
}
void socketio(void *parameter)
{

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    socketioclient.on("connect", eventConnect);
    socketioclient.on("configure", eventConfig);
    // get ltm report when trigger 
    socketioclient.on("LTM", ([](const char *payload, size_t length){
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }
        isReported = doc["data"]; // true
    }));
    socketioclient.on("cardStatus",([](const char *payload, size_t length){
            Serial.print(payload); // do blink light or button 
    }));

    socketioclient.on("response", ([](const char *payload, size_t length) {
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }
        bool resError = doc["err"]["error"]; // true
        const char * err_message = doc["err"]["message"];

        vTaskDelay(1000/portTICK_PERIOD_MS);
        if(resError)
        {
            lv_obj_move_background(errMsgBox);
            lv_obj_set_size(errMsgBox, lv_pct(100), lv_pct(100));
            lv_label_set_text(errLabel, err_message);
            vTaskDelay(2000/portTICK_PERIOD_MS);
            lv_obj_move_foreground(errMsgBox);
            lv_obj_set_size(errMsgBox, lv_pct(0), lv_pct(0));
            ltie.subTotal = ltie.totalOutput;
            dailyOutputCount = ltie.dailyOpt;
        }
        
    }));

    socketioclient.on("ltie_get",ltie_event);
    socketioclient.on("update", ([](const char *payload, size_t length){
        getUpdate = true;
    }));
    socketioclient.beginSSL(socketURL, 443);
    socketioclient.setAuthorization(token);

    while (1)
    {
        socketioclient.loop();
        unsigned long startTime = millis();
        if(ltlabs.count != 0)
        {
            ltlabs.interval--;
            if(ltlabs.interval == 0 && isGetState)
            {
                ltlabs.LtieOutputCounter();
                post_data_to_api(ltlabs.count, "ltie_post", "LTIE");
                isGetState = false;
                ltlabs.interval = 10;
            }
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }

        if (startTime - currentRetrive >= 5000) {
            if(buffer != 0)
            {
                updateData();
            } 
            currentRetrive = startTime;
        }

        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void wifiBegin(void *parameter)
{
    bool wificonnect;
    wificonnect = wm.autoConnect("M5Tough_AP");
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(250/portTICK_PERIOD_MS);
        unsigned long startTime = millis();
        if(startTime - currentTimeOut >= timeOut)
        {
            Serial.print("Connection Failure!!");
            currentTimeOut = startTime;
            return;
        }
    }
    
    esp32fota.setManifestURL( manifest_url );
    esp32fota.printConfig();

    configTime(offset_sec, daylightOffset_sec, ntpServer);

    while (1)
    {
        vTaskDelay(5);
    }
    
}
void Output(void *parameter)
{
    while (1)
    {
        if(isReported)
        {
            digitalWrite(led_btn_1, HIGH);
            lv_obj_set_style_bg_color(ui_indicator, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            vTaskDelay(500/portTICK_PERIOD_MS);
            digitalWrite(led_btn_1, LOW);
            lv_obj_set_style_bg_color(ui_indicator, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            vTaskDelay(500/portTICK_PERIOD_MS);
        }
        vTaskDelay(10);
    }
    
}
void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    M5.begin();
    ltlabs.ui();
    
    if (!LittleFS.begin())
    {
        Serial.print("Mount unsuccess");
        vTaskDelay(250);
        return;
    }
    readConfigure();

    pinMode(led_btn_1, OUTPUT);
    pinMode(led_btn_2, OUTPUT);
    pinMode(BTN_RED, INPUT_PULLUP);
    pinMode(BTN_G, INPUT_PULLUP);

    vTaskDelay(1000/portTICK_PERIOD_MS);
    xTaskCreatePinnedToCore( &updateGUI, "updateGUI", 4096*3, NULL, 1, &guiTask, tskNO_AFFINITY );
    xTaskCreatePinnedToCore( &wifiBegin, "wifiTask", 4096*1, NULL, 2, NULL, tskNO_AFFINITY );
    xTaskCreatePinnedToCore( &socketio, "SocketIO", 4096*3 , NULL, 3, &socketTaskhandler, tskNO_AFFINITY );
    xTaskCreatePinnedToCore( &Output, "ledOuput", 2048, NULL, 4, NULL, tskNO_AFFINITY);
}
void loop()
{
    if(getUpdate)
    {
        if(socketTaskhandler != NULL)
        {
            vTaskDelete(socketTaskhandler);
        }
        bool updatedNeeded = esp32fota.execHTTPcheck();
        if (updatedNeeded)
        {
            esp32fota.execOTA();
            ESP.restart();
        } 
        ESP.restart();
    }
    
}
