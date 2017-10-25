/*
  Estacion de medida de calidad del aire

  Conexiones

  Sensor CO2                    -   A0
  Sensor temperatura y humedad  -    7
  Pantalla LCD                  - SDA y SCL


  by JAVacasM
*/

#define PIN_SENSOR_TEMP_HUM 7
#define PIN_SENSOR_CO2      A0
#define PIN_SENSOR_CO2_2      A1
#define PIN_SENSOR_CO2_3      A2


/* ==== Includes - Librerias==== */

// Pantalla lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Sensor Temperatura-Humedad
#include <SimpleDHT.h>

// Sensor de CO2
#include "MQ135.h"

/* ====  END Includes ==== */

/* ==== Defines - Constantes ==== */
#define PLOT
/* ==== END Defines ==== */

/* ==== Variables Globales ==== */

// Pantalla lcd
LiquidCrystal_I2C lcd(0x27, 16, 2); // Displany 16x2

// Sensor Temperatura-Humedad
SimpleDHT11 dht11;

// Sensor CO2
MQ135 gasSensor = MQ135(PIN_SENSOR_CO2);
MQ135 gasSensor2 = MQ135(PIN_SENSOR_CO2_2);
MQ135 gasSensor3 = MQ135(PIN_SENSOR_CO2_3);

int iMedidas=0;

double result;
double rzero;

/* ==== END Global Variables ==== */


/* ==== Funciones a usar - Prototipos ==== */

/* ==== END Prototipos ==== */

/* ==== Setup - Configuracion ==== */
void setup() {
  // Configuraion Pantalla

  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Medida calidad de Aire");
  lcd.setCursor(2, 1);
  lcd.print("con Arduino!");

  delay(1000);


  Serial.begin(9600);
}
/* ==== END Setup ==== */

/* ==== Loop - Codigo que se repite==== */
void loop() {

  // Lectura de temperatura-humedad
  byte temperatura = 0;
  byte humedad = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(PIN_SENSOR_TEMP_HUM, &temperatura, &humedad, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Error leyendo temperatura, err=");
    Serial.println(err);
    delay(1000);
    return;
  }
  
#ifndef PLOT
  Serial.print("Temp: ");
#endif  
  lcd.setCursor(0, 0);
  lcd.print("T:");


  Serial.print(1.0*temperatura);
  lcd.print((int)temperatura);

#ifndef PLOT
  Serial.print("C");
#endif   
  Serial.print(", ");
  lcd.print("C ");

#ifndef PLOT
  Serial.print("Hum:");
#endif   
  lcd.print("Hum:");


  Serial.print(1.0*humedad);
  lcd.print((int)humedad);
#ifndef PLOT  
  Serial.print(" %");
#endif   
  lcd.print(" %  ");

  

// Medida de CO2

 if (iMedidas==0) {
   rzero = gasSensor.getRZero(); 
 }
 if (iMedidas>0) {  
   result = gasSensor.getRZero();
   rzero = (rzero + result)/2;
  }
iMedidas++;
float ppm = gasSensor.getPPM();
#ifndef PLOT
Serial.print(" PPM:");
#endif 
#ifdef PLOT
Serial.print(", ");
#endif 

Serial.print(ppm);
Serial.print(", ");
ppm = gasSensor2.getPPM();
Serial.print(ppm);
Serial.print(", ");
ppm = gasSensor3.getPPM();

Serial.println(ppm);


lcd.setCursor(0,1);
lcd.print("CO2:");
lcd.print(ppm);
lcd.print(" (");
float ppmCorregida=gasSensor.getCorrectedPPM(temperatura,humedad);
lcd.print(ppmCorregida);
lcd.print(") ");

delay(200);  // Esperamos 1 segundo
}
/* ==== End Loop ==== */

/* ==== Funciones ==== */

/* ==== END Functions ==== */
