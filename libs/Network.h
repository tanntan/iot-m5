#include <WiFi.h>

namespace LTLabs::Network {

  struct AccessPoint {
    IPAddress ip;
    IPAddress localIP;
    const char* ssid;
    bool isSuccess;
  };

  class Network {
    public:

      struct WifiStatus {
        IPAddress ip;
        int status;
      };

      static AccessPoint initAP(const char* ssid) {
        AccessPoint ap;
        bool success =  WiFi.softAP(ssid);
        IPAddress ip = WiFi.softAPIP();
        ap.ip = ip;
        ap.isSuccess = success;
        ap.ssid = ssid;
        ap.localIP = WiFi.localIP();
        return ap;
      }

      static bool disconnectAP(bool restoreSettings = false) {
        return WiFi.softAPdisconnect(restoreSettings);
      }

      /**
       * Connect to an access point, known access point
       * with password and returns the connection status
       * WL_CONNECTED when successfully connection,
       * otherwise returns WL_IDLE_STATUS
       */
      int connectTo(const char* ssid, const char* pass = "") {
        WiFi.begin(ssid, pass);
        int status = WiFi.status();
        return status;
      }

      WifiStatus getWifiStatus() {
        int status = WiFi.status();
        IPAddress ip = WiFi.localIP();
        WifiStatus wifiStatus;
        wifiStatus.ip = ip;
        wifiStatus.status = status;
        return wifiStatus;
      }

      static bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
      }
  };
}
