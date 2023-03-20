#include <M5Stack.h>
#define DEVICE_ADDR 0X5E

namespace LTLabs::Encoder {
  struct Props {
    int min = 0;
    int max = 100;
    int step = 1;
    int value = 0;
    void (*onPress)(int);
  };

  class Encoder {
    private:
      Props props;


    public:
      int readValue;
      int curValue;
      int direction;
      int increment;

      Encoder(Props config) {
        props = config;
      }

      int start() {
        int dir;
        Wire.requestFrom(DEVICE_ADDR, 3);

        if(Wire.available()) {
          readValue = Wire.read();
          curValue = Wire.read();
        }

        if (curValue == 0) {
          if (props.onPress) {
            props.onPress(props.value);
          }
          // props.value = 0;
        }

        if (readValue > 0){
          dir = readValue > 127 ? (props.step * -1) : props.step;
          props.value = props.value + dir;
          if (props.value > props.max) {
            props.value = props.max;
          }
          if (props.value < props.min) {
            props.value = props.min;
          }
        }
        return props.value;
      }

      int getValue() {
        return props.value;
      }
      
      Props getProps() {
        return props;
      }

  };
}

/*
   void GetValue(void) {
   int temp_encoder_increment;

   Wire.requestFrom(Faces_Encoder_I2C_ADDR, 3);
   if (Wire.available()) {
   temp_encoder_increment = Wire.read();
   cur_button             = Wire.read();
   }
   if (temp_encoder_increment > 127) {  // anti-clockwise
   direction         = 1;
   encoder_increment = 256 - temp_encoder_increment;
   } else {
   direction         = 0;
   encoder_increment = temp_encoder_increment;
   }
   }

*/
