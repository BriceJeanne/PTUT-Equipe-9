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

/* Declaration d'une chaine d'affichage*/
String printString;

void setup() {
  Serial.begin(9600);
  
  /* Met les broches des LEDs en sortie*/
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
    
  /* Eteint la LED par defaut*/
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  
  /* Met les broches des boutons en entrees avec pull-up */
  pinMode(PIN_BUTTON_Deb, INPUT_PULLUP);
  pinMode(PIN_BUTTON_Fin, INPUT_PULLUP);
}

void loop() {
	
}
