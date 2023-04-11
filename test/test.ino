#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

const byte ULTRASON_TRIGGER_PIN = 7; // Broche TRIGGER
const byte ULTRASON_ECHO_PIN = 8; //broche echo de reception

/* Constantes pour le timeout */
const unsigned long ULTRASON_MEASURE_TIMEOUT = 25000UL;

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;


const int broche_LED_1 = 1; const int broche_LED_2 = 2;
const int broche_LED_3 = 3; const int broche_LED_4 = 4;
const int broche_LED_5 = 5; const int broche_LED_6 = 6;
const int broches[6] = {broche_LED_1,broche_LED_2,broche_LED_3,
                        broche_LED_4,broche_LED_5,broche_LED_6};
const int nombre_diode=sizeof(broches); //indice 0 compris


int speed=250;


void setup() {
          // put your setup code here, to run once:
          mySoftwareSerial.begin(9600);
          Serial.begin(115200);
          
          Serial.println();
          Serial.println(F("DFRobot DFPlayer Mini Demo"));
          Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
        
          if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
            Serial.println(F("Unable to begin:"));
            Serial.println(F("1.Please recheck the connection!"));
            Serial.println(F("2.Please insert the SD card!"));
            while(true);
          }
          Serial.println(F("DFPlayer Mini online."));
          myDFPlayer.volume(30);  //Set volume value. From 0 to 30
 
          for (int i = 0 ; i < 6 ; i ++){
            pinMode(broches[i],OUTPUT);
            digitalWrite(broches[i], HIGH);
            randomSeed(analogRead(A0));
          }

          pinMode(ULTRASON_TRIGGER_PIN, OUTPUT);
          digitalWrite(ULTRASON_TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
          pinMode(ULTRASON_ECHO_PIN, INPUT);

}

void loop() {
  //Serial.println(mesureUltrason());
  if(mesureUltrason()<
  200){
    radar_motif_8(speed);
    myDFPlayer.play(2);
    
    
    delay (2000);
  }
 else{
    radar_motif_1(speed);
 }
  
}

//_________________________________________________________________________________________

void radar_motif_1(int speed)
{
  for (int i = 0 ; i < 6 ; i++){
    digitalWrite(broches[i], HIGH);
    delay(speed);
  }
  for (int i = 0 ; i < 6 ; i++){
    digitalWrite(broches[i], LOW);
    delay(speed);
  }
}

void radar_motif_2()
{
  int aleatoire = random(0,6);
  digitalWrite(broches[aleatoire], HIGH);
  int aleatoire_delay = random(100,501);
  delay(aleatoire_delay);
  digitalWrite(broches[aleatoire], LOW);
}

void radar_motif_3(int speed)
{
  for (int i = 0 ; i < 6 ; i++){
    digitalWrite(broches[i], HIGH);
    delay(speed);
    digitalWrite(broches[i], LOW);
    delay(speed);
  }
    for (int i = 6 ; i >= 0 ; i--){
    digitalWrite(broches[i], HIGH);
    delay(speed);
    digitalWrite(broches[i], LOW);
    delay(speed);
  }
}

void radar_motif_4(int speed){

  for (int i=0; i<nombre_diode;i++){ //on allume une a une les leds
    digitalWrite(broches[i], HIGH);
    delay(speed);
  }
  for (int i=0; i<nombre_diode;i++){ //on allume une a une les leds
    digitalWrite(broches[i], LOW);
    delay(speed);
  }
}

void radar_motif_5(int speed){ 
  
  for (int x=0; x<2; x++){ //nbre de clignotements
    
    for (int i=0; i<nombre_diode;i++){ //
    
      if (x%2)
      digitalWrite(broches[i], LOW);  //allume 1 fois sur 2
      
      else
      digitalWrite(broches[i], HIGH);
    }
  
  delay(speed);   //délai du clignotement
  }
    
}

void radar_motif_6(int speed){
  
  for (int x;x<2;x++){ //nombre de clignotage
    
    for (int i=0; i<nombre_diode;i++){

          if (i%2 & x%2)
          digitalWrite(broches[i], HIGH);

          else if (i%2 )
          digitalWrite(broches[i], LOW);
        
          else if (x%2)
          digitalWrite(broches[i], LOW);
        
          else
          digitalWrite(broches[i],HIGH);
     }
    
  delay(speed);
  }
  
}

void radar_motif_7(int speed) {
  for (int i = 0; i < 12; i++)
  {
    digitalWrite(broches[i%6], HIGH);
    digitalWrite(broches[(i+1)%6], HIGH);
    delay(speed);
    digitalWrite(broches[i%6], LOW);
    digitalWrite(broches[(i+1)%6], LOW);
  }
  for (int i = 0; i < 6; i++)
  {
    pinMode(broches[i], OUTPUT);
    digitalWrite(broches[i], LOW);
  }
}

void radar_motif_8(int speed) {
  for (int j = 0; j < 5; j++)
  {
    for (int i = 0; i < 6; i++)
    {
      digitalWrite(broches[i], HIGH);
    }
    delay(75);
    for (int i = 0; i < 6; i++)
    {
      digitalWrite(broches[i], LOW);
    }
    delay(speed);
  }
}

void radar_motif_9(int speed) {
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i <3; i++)
    {
      digitalWrite(broches[i], HIGH);
      digitalWrite(broches[5-i], HIGH);
      delay(speed/3);
      digitalWrite(broches[i], LOW);
      digitalWrite(broches[5-i], LOW);
    }
    for (int i = 2; i > -1; i--)
    {
      digitalWrite(broches[i], HIGH);
      digitalWrite(broches[5-i], HIGH);
      delay(speed/3);
      digitalWrite(broches[i], LOW);
      digitalWrite(broches[5-i], LOW);
    }
    delay(speed);
  }
}
float mesureUltrason(){
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(ULTRASON_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASON_TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ULTRASON_ECHO_PIN, HIGH, ULTRASON_MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  return distance_mm;
}
