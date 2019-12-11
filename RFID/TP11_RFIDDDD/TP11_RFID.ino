
#include <SPI.h>
#include <MFRC522.h>
#include "sistem.h"
#include "cnu1.h"

//>SU1Y6760K6<
//>QU1<

//--Pines para el RFID--
#define RST_PIN 9 //Pin 9 para el reset del RC522
#define SS_PIN 10 //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

//--Variables para el lector del RFID--
char ActualUID[4]; //almacenará el código del Tag leído
char Usuario1[4]= {0xE6, 0x16, 0x0B, 0x4B} ; //código del usuario 1
char Usuario2[4]= {0x12, 0x6A, 0x0D, 0xB0} ; //código del usuario 2


//--Vector interrupcion Timer2--
void initTimer2(void);  //Inicializamos el constructor
int cont = 0;           //Contador del vector interrupcion
bool flag = 0;          //Bandera para el vector interrupcion
int led=13;             //Declaramos el pin del led

//--Variables para el input del  mensaje--
int msgNuevo = 0;
String str = "";
String str2 = "";

//--Variables para separar por bloques el hash-- 
int b1u1;//Bloque 1 del usuario1
int b2u1;//Bloque 2 del usuario1
int b3u1;//Bloque 3 del usuario1
int b4u1;//Bloque 4 del usuario1



void setup() 
{
  initPorts(); //Iniciamos la comunicación serial
  initTimer2();//Iniciamos la comun. del vector interrupcion
  pinMode(led,OUTPUT);//Inicializamos el led testigo
  SPI.begin(); //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Lectura del UID");
  
}

void loop() {
  //Vector Interrupcion Timer2
  if(flag){
    flag=0;  
  }

  if (Serial.available())   // detecta si se escribe en la consola
  {
    char carRec = Serial.read();
    msgNuevo = captureData(carRec);
  }

  if (msgNuevo)  // detecta si hay mensaje nuevo valido
  {
    msgNuevo = 0;
    parseMsg();
  }
  
  
  
  // Revisamos si hay nuevas tarjetas presentes
  if ( mfrc522.PICC_IsNewCardPresent())
  {
    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial())
    {
      // Enviamos serialemente su UID
      Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        ActualUID[i]=mfrc522.uid.uidByte[i];        
      }
      Serial.println();
      
      //comparamos los UID para determinar si es uno de nuestros usuarios
      if(compareArray(ActualUID,Usuario1))
        Serial.println("Acceso concedido...");
      else if(compareArray(ActualUID,Usuario2))
        Serial.println("Acceso concedido...");
      else
        Serial.println("Acceso denegado...");
      // Terminamos la lectura de la tarjeta tarjeta actual
      mfrc522.PICC_HaltA();
    }
  }
}

//funcion que compara los arrays
boolean compareArray(char array1[],char array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
//*********************************************************
//Vector interrupcion Timer2
//********************************************************

ISR(TIMER2_OVF_vect)
{
  TCNT2 = 5;
  cont++;
  if (cont == TOSC)
  {
    cont = 0;
    flag = 1;
    
  }
}
