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

  /* Lecture d'une question en entrée et affichage par la suite */
  while (Serial.available()) {
    delay(3); /* Attends 3ms que les données arrivent */
    /* Récupère les données caractère par caractère */
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if(readString.length() > 0) {
     Serial.println(readString); /* Affiche ce qui a été récupéré */
     if(readString == "Affichage" || readString == "affichage"){
        printpercentage();
     }
     readString = "";
  }

  /* On attend de recevoir un message */
  vw_wait_rx();
  
  // On copie le message, qu'il soit corrompu ou non
  if (vw_get_message(message, &taille_message)) {
    
    if (strcmp((char*) message, CMD_BUTTON_A) == 0) {
      setColorRouge();
      Serial.println("TOGGLE LED A");
      cptA = cptA++;
      delay(500);
      ColorReset();
      
    } 
    
    else if (strcmp((char*) message, CMD_BUTTON_B) == 0) {
      setColorVert();
      Serial.println("TOGGLE LED B");
      cptB = cptB++;
      delay(500);
      ColorReset();
    }
    
    else if (strcmp((char*) message, CMD_BUTTON_C) == 0) {
      setColorBleu();
      Serial.println("TOGGLE LED C");
      cptC = cptC++;
      delay(500);
      ColorReset();
    }

     else if (strcmp((char*) message, CMD_BUTTON_D) == 0) {
      setColorBlanc();
      Serial.println("TOGGLE LED D");
      cptD = cptD++;
      delay(500);
      ColorReset();
    }
  } 
}

/* Colore la LED RGB avec les valeurs passee en parametre*/
void setColorRouge() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void setColorVert() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void setColorBleu() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void setColorBlanc() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void ColorReset() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

/* Petite fonction d'affichage pour plus de propreté dans le code*/
void printpercentage()
{
  /* Affichage des pourcentages des reponses*/
  printString = " / ";
  Serial.print(cptA);   Serial.print(printString);  Serial.print((cptA + cptB + cptC + cptD));
  Serial.println("");      // affiche un autre retour de chariot  
  Serial.print(cptB);   Serial.print(printString);  Serial.print((cptA + cptB + cptC + cptD));
  Serial.println("");      // affiche un autre retour de chariot
  Serial.print(cptC);   Serial.print(printString);  Serial.print((cptA + cptB + cptC + cptD));
  Serial.println("");      // affiche un autre retour de chariot
  Serial.print(cptD);   Serial.print(printString);  Serial.print((cptA + cptB + cptC + cptD));
  Serial.println("");      // affiche un autre retour de chariot
}
