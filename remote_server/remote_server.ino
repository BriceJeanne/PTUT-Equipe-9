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

/* Differents messages de commande */
const char* CMD_BUTTON_A = "BPA";
const char* CMD_BUTTON_B = "BPB";
const char* CMD_BUTTON_C = "BPC";
const char* CMD_BUTTON_D = "BPD";

/* Declaration d'une chaine d'affichage*/
String printString;

/*variable qui stocke la mesure du temps*/
unsigned long temps;

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

  Serial.println("Attente de la session");
  if (digitalRead(PIN_BUTTON_Deb) == LOW) {
    Serial.println("Debut de la session");
    /* Allume la LED en blanc pour prevenir que la session va debuter*/
    setColorWhite();
    delay(5000);

    for (int x = 0; x < nbQuestion; x++) {
      Serial.print("Preparation a la question "); Serial.println(x + 1);
      setColorRed();
      delay(3000);

      Serial.print("Reponse a la question "); Serial.println(x + 1);
      setColorGreen();

      /* Variable tempon declarer pour stocker la dernière valeur de reponse a la question*/
      char* Tempon = "";
      
      //on initialise le temps
      temps = millis();
      
      /*
         on compare l'ancienne valeur du temps et la valeur sauvée
         si la comparaison (l'un moins l'autre) dépasse 5000
         cela signifie que moins 5 secondes se sont écoulées
         et donc la question se déroule toujours
      */
      while ((temps - millis()) > 5000) {
        if (digitalRead(PIN_BUTTON_Fin) == LOW) {
          Serial.println("Fin premature de la session");
          goto bailout;
        }
        
        Serial.println("Reception msg");
        /*on stocke la nouvelle heure*/
        temps = millis(); 
        
        /*
          La variable "taille_message" doit impérativement être remise à
          la taille du buffer avant de pouvoir recevoir un message.
          Le plus simple est d'utiliser une variable locale pour ne pas
          avoir à réassigner la valeur à chaque début de loop().
        */
        byte message[VW_MAX_MESSAGE_LEN];
        byte taille_message = VW_MAX_MESSAGE_LEN;
        /* N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire */

        /* On attend de recevoir un message */
        vw_wait_rx_max(100);

        /* On copie le message */
        if (vw_get_message(message, &taille_message)) {

          if (strcmp((char*) message, CMD_BUTTON_A) == 0) {
            Serial.println("Reception A");
            Tempon = CMD_BUTTON_A;
            Serial.print(Tempon);
            delay(50);

          } else if (strcmp((char*) message, CMD_BUTTON_B) == 0) {
            Serial.println("Reception B");
            Tempon = CMD_BUTTON_B;
            Serial.print(Tempon);
            delay(50);
          }
          else if (strcmp((char*) message, CMD_BUTTON_C) == 0) {
            Serial.println("Reception C");
            Tempon = CMD_BUTTON_C;
            Serial.print(Tempon);
            delay(50);
          }
          else if (strcmp((char*) message, CMD_BUTTON_D) == 0) {
            Serial.println("Reception D");
            Tempon = CMD_BUTTON_D;
            Serial.print(Tempon);
            delay(50);
          }
        }
      }
      
      Serial.println("Traitement msg");
      if (Tempon == CMD_BUTTON_A) {
        cptTA = cptTA + 1;
      }
      else if (Tempon == CMD_BUTTON_B) {
        cptTB = cptTB + 1;
      }
      else if (Tempon == CMD_BUTTON_C) {
        cptTC = cptTC + 1;
      }
      else if (Tempon == CMD_BUTTON_D) {
        cptTD = cptTD + 1;
      }
      else {
        cptTAny = cptTAny + 1;
      }

      Serial.println("On vide le tempon");
      Tempon = "";
      
      Serial.print("Fin de la question "); Serial.println(x + 1);
      setColorYellow();
      delay(3000);
    }
    Serial.println("Fin de la session");
bailout:
    resetColor();
    printPercentage();
  }
}

/* Colore la LED RGB avec les valeurs passee en parametre*/
void setColorRed() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void setColorGreen() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void setColorBlue() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void setColorWhite() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void setColorYellow() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void resetColor() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void resetPercentage(){
  /* Reset des compteurs a la fin d'un affichage*/
  cptTA = 0;    
  cptTB = 0;
  cptTC = 0;
  cptTD = 0;
  cptTAny = 0;
}

/* Petite fonction d'affichage pour plus de propreté dans le code*/
void printPercentage(){
  /* Affichage des pourcentages des reponses*/
  Serial.print("Reponse A : ");   Serial.print(cptTA);   Serial.print(" / ");  Serial.print(nbQuestion);
  Serial.println("");      // affiche un autre retour de chariot
  Serial.print("Reponse B : ");   Serial.print(cptTB);   Serial.print(" / ");  Serial.print(nbQuestion);
  Serial.println("");      // affiche un autre retour de chariot
  Serial.print("Reponse C : ");   Serial.print(cptTC);   Serial.print(" / ");  Serial.print(nbQuestion);
  Serial.println("");      // affiche un autre retour de chariot
  Serial.print("Reponse D : ");   Serial.print(cptTD);   Serial.print(" / ");  Serial.print(nbQuestion);
  Serial.println("");      // affiche un autre retour de chariot
  Serial.print("Aucune reponse  : ");   Serial.print(cptTAny);   Serial.print(" / ");  Serial.print(nbQuestion);
  Serial.println("");      // affiche un autre retour de chariot
  resetPercentage();
}
