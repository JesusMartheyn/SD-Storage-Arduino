////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
/*

Para conectar el Modulo de Tarjeta SD debe Conectar:

 Pin "GND" a Tierra
 Pin "+5" a  5 Voltios 
 Pin "CS" al pin 4 del Arduino
 Pin "MOSI" al pin 11 del Arduino
 Pin "SCK" al pin 13 del Arduino
 Pin "MISO" al pin 12 del Arduino

Para conectar el Sensor de corriente SY-712 se debe conectar:

A0 para el sensor de corriente de la Bateria
A1 para el sensor de corriente del panel solar

Para conectar el Reloj de tiempo real se debe conectar:

Pin "DS" al pin 2 del Arduino
Pin "SCL" al pin A5
Pin "SDA" al pin A4
Pin "VCC" a 5 Voltios
Pin "GND" a Tierra

Códido elabroado por Jesus Martheyn y David Muñoz, en representación del Grupo de Investigación GISNET

*/
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////// 
//LIBRERIAS TARJETA SD ////
#include <SPI.h>
#include <SD.h>

//LIBRERIAS TIEMPO REAL ////
#include <Wire.h> 
#include "RTClib.h"
RTC_DS1307 RTC;

File Archivo;
float corriente_Bateria=0;
float corriente_Panel=0;
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////// 
void setup()
{ 
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  Serial.begin(9600);
  
  Serial.println("Comenzando la comunicación con la tarjeta SD");
  
  pinMode(10, OUTPUT);
 
  if (!SD.begin(4))
  {
      Serial.println("Se ha producido un fallo al iniciar la comunicación");
      return;
  }
      Serial.println("Se ha iniciado la comunicación correctamente");     
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop()
{
  DateTime now = RTC.now();
  
  corriente_Bateria=(((1.9/27.0)* analogRead(A0)) - 35.88);
  corriente_Panel=(((1.9/27.0)* analogRead(A1)) - 35.88);
  
   Serial.print(now.year(), DEC);
   Serial.print("/");
   Serial.print(now.month(), DEC);
   Serial.print("/");
   Serial.print(now.day(), DEC);
   Serial.print("  ");
   Serial.print(now.hour(), DEC); // Horas
   Serial.print(":");
   Serial.print(now.minute(), DEC); // Minutos
   Serial.print(":");
   Serial.print(now.second(), DEC); // Segundos
   Serial.print("  Corriente_Bateria: ");
   Serial.print(corriente_Bateria);
   Serial.print("  Corriente_Panel: ");
   Serial.println(corriente_Panel);

    if(now.hour()>=5 && now.hour() <=19)
      {  
        if(now.second() == 59)
        {
          Archivo = SD.open("datos.txt", FILE_WRITE);
          corriente_Bateria=(((1.9/27.0)* analogRead(A0)) - 35.88);
          corriente_Panel=(((1.9/27.0)* analogRead(A1)) - 35.88);
    
          Archivo.print(now.year(), DEC);
          Archivo.print("/");
          Archivo.print(now.month(), DEC);
          Archivo.print("/");
          Archivo.print(now.day(), DEC);
          Archivo.print("\t");
          Archivo.print(now.hour(), DEC); // Horas
          Archivo.print(":");
          Archivo.print(now.minute(), DEC); // Minutos
          Archivo.print(":");
          Archivo.print(now.second(), DEC); // Segundos
          Archivo.print("\t");
          Archivo.print("  Corriente_Bateria: ");
          Archivo.print(corriente_Bateria);
          Archivo.print("\t");
          Archivo.print("  Corriente_Panel: ");
          Archivo.println(corriente_Panel);
          Archivo.close();
        }
    }  
     delay(1000);
}


