# Calibración

Proceso de calibración la [librería MQ135](https://github.com/GeorgK/MQ135)

Dejamos funcionando entre 12 y 24 horas el sensor MQ135 lo  con el siguiente código:

      #include "MQ135.h"

      void setup (){
        Serial.begin (9600);
      }

      void loop() {
        MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
        float rzero = gasSensor.getRZero();
        Serial.println (rzero);
        delay(1000);
      }


  Nos irá enviando por el puerto serie los valores de calibración de RZero.

  Luego sustituiremos el valor del RZero en mq135.h

      /// Calibration resistance at atmospheric CO2 level
      #define RZERO 76.63


[Dataset for 24 hours](https://docs.google.com/spreadsheets/d/1MD-_lNkqOwHFsI5Y2xTGExGSEopUglo4_CpP7liHbYc/edit?usp=sharing)

  ([Fuente](https://circuitdigest.com/microcontroller-projects/iot-air-pollution-monitoring-using-arduino))
