#include "config.h"

struct Button {
  char* color;
  int hex;
};

AdafruitIO_Feed *color = io.feed("Status");


/*char *buttons[] = {
  "up"           ,"down"       ,"off"       ,"on"    ,
  "red"          ,"green"      ,"blue"      ,"white" ,
  "red orange"   ,"light green","light blue","flash" ,
  "orange"       ,"cyan"       ,"purple"    ,"strobe",
  "yellow orange","teal"       ,"violet"    ,"fade"  ,
  "yellow"       ,"turquoise"  ,"magenta"   ,"smooth"
  };
*/
Button buttons[24] = {
  {"up",0x0},{"down",0x1},{"off",0x2},{"on",0x3},
  {"red",0x4},{"green",0x5},{"blue",0x6},{"white",0x7},
  {"red orange",0x8},{"light green",0x9},{"light blue",0xA},{"flash",0xB},
  {"orange",0xC},{"cyan",0xD},{"purple",0xE},{"strobe",0xF},
  {"yellow orange",0x10},{"teal",0x11},{"violet",0x12},{"fade",0x13},
  {"yellow",0x14},{"turquoise",0x15},{"magenta",0x16},{"smooth",0x17}
};
void setup() {
  Serial.begin(115200);

  
  

  while (! Serial);

  io.connect();
  color->onMessage(handleMessage);
  while(io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  color->get();
}

void loop() {
  io.run();
}

void handleMessage(AdafruitIO_Data *data) {

  for (int i = 0; i < 24; i++) { 

    //Serial.println(buttons[i]);
    //Serial.println(data->value());
    char button[100];
    strcpy(button, buttons[i].color);
    char value[100];
    strcpy(value,data->value());
    //Serial.println(valuee);
    //Serial.println(buton);
    if (strcmp(button, value) == 0) {
      Serial.print("\nMATCH: ");
      Serial.println(buttons[i].color);
      Serial.print(i, HEX);
    }
  }
}
