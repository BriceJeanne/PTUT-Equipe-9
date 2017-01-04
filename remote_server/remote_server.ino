#include <VirtualWire.h>

/* Déclare les compteurs de réponse*/
int cptA = 0;
int cptB = 0;
int cptC = 0;
int cptD = 0;

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
  
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages
}

void loop() {
	byte message[VW_MAX_MESSAGE_LEN];
  byte taille_message = VW_MAX_MESSAGE_LEN;
  /* N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire */

  /*
  La variable "taille_message" doit impérativement être remise à 
  la taille du buffer avant de pouvoir recevoir un message. 
  Le plus simple est d'utiliser une variable locale pour ne pas
  avoir à réassigner la valeur à chaque début de loop().
  */

  /* On attend de recevoir un message */
  vw_wait_rx();
  
  // On copie le message, qu'il soit corrompu ou non
  if (vw_get_message(message, &taille_message)) {
    
    if (strcmp((char*) message, CMD_BUTTON_A) == 0) {
      setColorCyan();
      Serial.println("TOGGLE LED A");
      cptA = cptA++;
      delay(500);
      ColorReset();
      
    } 
    
    else if (strcmp((char*) message, CMD_BUTTON_B) == 0) {
      setColorMagenta();
      Serial.println("TOGGLE LED B");
      cptB = cptB++;
      delay(500);
      ColorReset();
    }
    
    else if (strcmp((char*) message, CMD_BUTTON_C) == 0) {
      setColorJaune();
      Serial.println("TOGGLE LED C");
      cptC = cptC++;
      delay(500);
      ColorReset();
    }

     else if (strcmp((char*) message, CMD_BUTTON_D) == 0) {
      Serial.println("TOGGLE LED D");
      cptD = cptD++;
      delay(500);
    }
  } 
}

/* Colore la LED RGB avec les valeurs passee en parametre*/
void setColorBleu() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void setColorCyan() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void setColorMagenta() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void setColorJaune() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void ColorReset() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}
