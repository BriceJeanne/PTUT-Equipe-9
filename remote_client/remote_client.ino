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

  /* Met les broches des LEDs en sortie*/
  pinMode(redPin, OUTPUT); //Patte 4 reliee a la cathode de la LED rouge
  pinMode(greenPin, OUTPUT); //Patte 3 reliee a la cathode de la LED vert
  pinMode(bluePin, OUTPUT); //Patte 2 reliee a la cathode de la LED bleu 
  
  /* Eteint la LED par defaut*/
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  
  /* Met les broches des boutons en entrees avec pull-up */
  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  pinMode(PIN_BUTTON_C, INPUT_PULLUP);
  pinMode(PIN_BUTTON_D, INPUT_PULLUP);

  // Initialisation de la bibliotheque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si necessaire
  vw_setup(2000);
}

void loop() {
  byte message[VW_MAX_MESSAGE_LEN];
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire

  /* Envoi la commande adequate */
  if (digitalRead(PIN_BUTTON_A) == LOW) {
    vw_send((byte*) CMD_BUTTON_A, strlen(CMD_BUTTON_A) + 1); // On envoie le message
    vw_wait_tx(); // On attend la fin de l'envoi

    delay(50); // Attend que le bouton soit relache
    while (digitalRead(PIN_BUTTON_A) == LOW);
    delay(50);
  }

  else if (digitalRead(PIN_BUTTON_B) == LOW) {
    vw_send((byte*) CMD_BUTTON_B, strlen(CMD_BUTTON_B) + 1); // On envoie le message
    vw_wait_tx(); // On attend la fin de l'envoi

    delay(50); // Attend que le bouton soit relÃ¢chÃ©
    while (digitalRead(PIN_BUTTON_B) == LOW);
    delay(50);
  }
}
