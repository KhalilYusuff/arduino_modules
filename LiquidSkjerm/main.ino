#include "LiquidSkjerm.h"

LiquidSkjerm minSkjerm(12, 11, 5, 4, 3, 2, 2, 16, "Display 1");

void setup(){
  minSkjerm.begin(); 

}

void loop(){
  minSkjerm.write("Hei Verden!", 0, 0);
}