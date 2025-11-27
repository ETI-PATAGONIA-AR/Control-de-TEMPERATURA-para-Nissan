#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>               // PROGMEM

#define SCREEN_WIDTH 128                // ancho display OLED 
#define SCREEN_HEIGHT 64                // alto display OLED 
#define REC_LENGTH 200                  // 

// Declaramos la coneccion I2C de un display OLED SSD1306 (SDA, SCL pines)
#define OLED_RESET     -1      // Reset pin # 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ADC_VREF_mV 5000.0
#define ADC_RESOLUTION 1024.0
#define PIN_LM35 A1
#define MOTOR 3 // pin 3 salida PWM a motor
String tempString;
const int POT = A0;
const int Modo = 13;
const int Vel4 = 12;
const int Vel3 = 11;
const int Vel2 = 10;
const int Vel1 = 9;
int posicionSELECTORA=0;
int LecturaANALOGICA=0;
int VerPWM=0;
int SalidaPWM = 0;


void setup()
{
    pinMode(MOTOR, OUTPUT);
  pinMode(Vel1, INPUT);  
  pinMode(Vel2, INPUT);  
  pinMode(Vel3, INPUT);  
  pinMode(Vel4, INPUT); 
  pinMode(Modo, INPUT); 
  Serial.begin(9600);

   //     Serial.begin(115200);        // RAM
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { // Address I2C 0x3C for 128x64
    //       Serial.println(F("SSD1306 failed"));
    for (;;);                               // 
  }

  tempString.reserve(10);
  //startScreen(); 
}

void loop()
{
 while (digitalRead(Modo) == LOW) 
      {
       Serial.println("modo SELECTORA MANUAL"); 
       CtrlSELECTORA();
       }
 while (digitalRead(Modo) == HIGH) 
       {
        Serial.println("modo POTENCIOMETRO");
        CtrlPOTENCIOMETRO();
       }  
}


/////////////////////////////////////////MODO MANUAL/////////////////////////////////////////
void CtrlPOTENCIOMETRO()
{
  
  LecturaANALOGICA = analogRead(POT);
  SalidaPWM = map(LecturaANALOGICA, 0, 1023, 0, 255);
  VerPWM= map(LecturaANALOGICA, 0, 1023, 0, 100);
  
  analogWrite(MOTOR, SalidaPWM);
  Serial.println(SalidaPWM);
    delay(2);
int adcVal = analogRead(PIN_LM35);
  float milliVolt=adcVal*(ADC_VREF_mV/ADC_RESOLUTION);
  float tempC= milliVolt/10;
  display.clearDisplay();
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 4);         //(10, 25);
  display.println(F("TEMPERATURA"));   // 
  display.drawFastHLine(3, 2, 120, WHITE);
  display.drawFastHLine(3, 12, 120, WHITE);
  display.drawFastHLine(3, 62, 120, WHITE);
  display.drawFastVLine(3, 3, 60, WHITE);
  display.drawFastVLine(123, 3, 60, WHITE);
  display.setTextSize(2);            // 2
  display.setCursor(15, 20);         //
  display.println(tempC,2);
  display.setCursor(75, 20);         //
  display.println(F("C"));
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 45);         //
  display.println(F("Velocidad:")); 
  display.setCursor(65, 45);         //
  display.println(VerPWM); 
   display.display();                 // 
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);            // 
  }


/////////////////////////////////////////MODO FIJO/////////////////////////////////////////
void CtrlSELECTORA()
{
 if (digitalRead(Vel1)==HIGH & digitalRead(Vel2)==HIGH & digitalRead(Vel3)==HIGH & digitalRead(Vel4)==HIGH)
{
   analogWrite(MOTOR, 0);
   //MOTOR=LOW;
   Serial.println("pwm 0"); 
   delay(2);
 int adcVal = analogRead(PIN_LM35);
  float milliVolt=adcVal*(ADC_VREF_mV/ADC_RESOLUTION);
  float tempC= milliVolt/10;
  display.clearDisplay();
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 4);         //(10, 25);
  display.println(F("TEMPERATURA"));   // 
  display.drawFastHLine(3, 2, 120, WHITE);
  display.drawFastHLine(3, 12, 120, WHITE);
  display.drawFastHLine(3, 62, 120, WHITE);
  display.drawFastVLine(3, 3, 60, WHITE);
  display.drawFastVLine(123, 3, 60, WHITE);
  display.setTextSize(2);            // 2
  display.setCursor(15, 20);         //
  display.println(tempC,2);
  display.setCursor(75, 20);         //
  display.println(F("C"));
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 46);         //
  display.println(F("Velocidad 0")); 
   display.display();                 // 
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);            // 
}
  
 posicionSELECTORA = digitalRead(Vel1);
  if (posicionSELECTORA == LOW) 
  {
    analogWrite(MOTOR, 80);
   Serial.println("pwm 80");
   delay(2);
int adcVal = analogRead(PIN_LM35);
  float milliVolt=adcVal*(ADC_VREF_mV/ADC_RESOLUTION);
  float tempC= milliVolt/10;
  display.clearDisplay();
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 4);         //(10, 25);
  display.println(F("TEMPERATURA"));   // 
  display.drawFastHLine(3, 2, 120, WHITE);
  display.drawFastHLine(3, 12, 120, WHITE);
  display.drawFastHLine(3, 62, 120, WHITE);
  display.drawFastVLine(3, 3, 60, WHITE);
  display.drawFastVLine(123, 3, 60, WHITE);
  display.setTextSize(2);            // 2
  display.setCursor(15, 20);         //
  display.println(tempC,2);
  display.setCursor(75, 20);         //
  display.println(F("C"));
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 46);         //
  display.println(F("Velocidad 1")); 
   display.display();                 // 
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);            // 
  } 
  posicionSELECTORA = digitalRead(Vel2);
  
  if (posicionSELECTORA == LOW) 
  {
   analogWrite(MOTOR, 128);
   Serial.println("pwm 128");
   delay(2);
 int adcVal = analogRead(PIN_LM35);
  float milliVolt=adcVal*(ADC_VREF_mV/ADC_RESOLUTION);
  float tempC= milliVolt/10;
  display.clearDisplay();
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 4);         //(10, 25);
  display.println(F("TEMPERATURA"));   // 
  display.drawFastHLine(3, 2, 120, WHITE);
  display.drawFastHLine(3, 12, 120, WHITE);
  display.drawFastHLine(3, 62, 120, WHITE);
  display.drawFastVLine(3, 3, 60, WHITE);
  display.drawFastVLine(123, 3, 60, WHITE);
  display.setTextSize(2);            // 2
  display.setCursor(15, 20);         //
  display.println(tempC,2);
  display.setCursor(75, 20);         //
  display.println(F("C"));
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 46);         //
  display.println(F("Velocidad 2")); 
   display.display();                 // 
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);            // 
  }  
   posicionSELECTORA = digitalRead(Vel3);
   
  if (posicionSELECTORA == LOW) 
  {
    analogWrite(MOTOR, 190);
   Serial.println("pwm 190");
   delay(2);
  int adcVal = analogRead(PIN_LM35);
  float milliVolt=adcVal*(ADC_VREF_mV/ADC_RESOLUTION);
  float tempC= milliVolt/10;
  display.clearDisplay();
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 4);         //(10, 25);
  display.println(F("TEMPERATURA"));   // 
  display.drawFastHLine(3, 2, 120, WHITE);
  display.drawFastHLine(3, 12, 120, WHITE);
  display.drawFastHLine(3, 62, 120, WHITE);
  display.drawFastVLine(3, 3, 60, WHITE);
  display.drawFastVLine(123, 3, 60, WHITE);
  display.setTextSize(2);            // 2
  display.setCursor(15, 20);         //
  display.println(tempC,2);
  display.setCursor(75, 20);         //
  display.println(F("C"));
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 46);         //
  display.println(F("Velocidad 3")); 
   display.display();                 // 
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);            // 
 
  } 
   posicionSELECTORA = digitalRead(Vel4);
   
  if (posicionSELECTORA == LOW) 
  {
  analogWrite(MOTOR, 255);
  Serial.println("pwm 255"); 
  delay(2);
  int adcVal = analogRead(PIN_LM35);
  float milliVolt=adcVal*(ADC_VREF_mV/ADC_RESOLUTION);
  float tempC= milliVolt/10;
  display.clearDisplay();
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 4);         //(10, 25);
  display.println(F("TEMPERATURA"));   // 
  display.drawFastHLine(3, 2, 120, WHITE);
  display.drawFastHLine(3, 12, 120, WHITE);
  display.drawFastHLine(3, 62, 120, WHITE);
  display.drawFastVLine(3, 3, 60, WHITE);
  display.drawFastVLine(123, 3, 60, WHITE);
  display.setTextSize(2);            // 2
  display.setCursor(15, 20);         //
  display.println(tempC,2);
  display.setCursor(75, 20);         //
  display.println(F("C"));
  display.setTextSize(1);            // 2
  display.setTextColor(WHITE);       //
  display.setCursor(5, 46);         //
  display.println(F("Velocidad 4")); 
   display.display();                 // 
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);            //  
   } 
}
////////////////////////////////////////////////////////////////////////////////////////
