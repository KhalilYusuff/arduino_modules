#include "LiquidSkjerm.h"

LiquidSkjerm minSkjerm(12, 11, 5, 4, 3, 2, 2, 16, "Display 1");

void setup(){
  minSkjerm.begin(); 
  minSkjerm.write("Hei", 0, 0);

}

void loop(){

  minSkjerm.write(millis() / 1000, 0, 1);

}