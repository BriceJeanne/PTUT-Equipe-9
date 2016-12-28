#include <VirtualWire.h>

/* Broches pour la LED RGB */ 
int redPin = 4;
int greenPin = 3;
int bluePin = 2;

/* Différents messages de commande */
const char* CMD_BUTTON_A = "BPA";
const char* CMD_BUTTON_B = "BPB";
const char* CMD_BUTTON_C = "BPC";
const char* CMD_BUTTON_D = "BPD";

void setup() {
  Serial.begin(9600);
}

void loop() {
	
}
