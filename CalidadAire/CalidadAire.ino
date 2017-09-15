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



/* ==== Includes - Librerias==== */

// Pantalla lcd
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Sensor Temperatura-Humedad
#include <SimpleDHT.h>

/* ====  END Includes ==== */

/* ==== Defines - Constantes ==== */
/* ==== END Defines ==== */

/* ==== Variables Globales ==== */

// Pantalla lcd
LiquidCrystal_I2C lcd(0x27,16,2);  // Displany 16x2

// Sensor Temperatura-Humedad
SimpleDHT11 dht11;

/* ==== END Global Variables ==== */


/* ==== Funciones a usar - Prototipos ==== */

/* ==== END Prototipos ==== */

/* ==== Setup - Configuracion ==== */
void setup() {
  // Configuraion Pantalla
  
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  lcd.setCursor(1,0);
  lcd.print("Medida calidad de Aire");
  lcd.setCursor(2,1);
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

  Serial.print("Temp: ");
  lcd.setCursor(0,0);
  lcd.print("T:");
  
  
  Serial.print((int)temperatura); 
  lcd.print((int)temperatura); 
  
  Serial.print(" *C, ");
  lcd.print(" *C, "); 

  Serial.print("Hum: ");
  lcd.setCursor(8,0);
  lcd.print("Hum: "); 
  
  
  Serial.print((int)humedad); 
  lcd.print((int)humedad); 
  Serial.println(" %");
  lcd.print(" %");
  
  delay(1000);  // Esperamos 1 segundo

}
/* ==== End Loop ==== */

/* ==== Funciones ==== */

/* ==== END Functions ==== */
