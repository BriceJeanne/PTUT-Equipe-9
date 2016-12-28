#include <VirtualWire.h>

/* Declare les compteurs total de reponse*/
int cptTA = 0;
int cptTB = 0;
int cptTC = 0;
int cptTD = 0;
int cptTAny = 0;

/* Declare le nombre de question dans la session*/
int nbQuestion = 4;

/* Broches pour la LED RGB */ 
int redPin = 4;
int greenPin = 3;
int bluePin = 2;

/* Broches pour les boutons */
const byte PIN_BUTTON_Deb = 5;
const byte PIN_BUTTON_Fin = 6;

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
