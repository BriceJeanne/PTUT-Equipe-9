#include <VirtualWire.h>

/* Broches pour la LED RGB */
const int redPin = 4;
const int greenPin = 3;
const int bluePin = 2;

/* Broches pour les boutons */
const byte PIN_BUTTON_A = 5;
const byte PIN_BUTTON_B = 6;
const byte PIN_BUTTON_C = 7;
const byte PIN_BUTTON_D = 8;

/* DiffÃ©rents messages de commande */
const char* CMD_BUTTON_A = "BPA";
const char* CMD_BUTTON_B = "BPB";
const char* CMD_BUTTON_C = "BPC";
const char* CMD_BUTTON_D = "BPD";

void setup() {
  Serial.begin(9600);
}

void loop() {
}
