  
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3 //Pin D3 para el reset del RC522
#define SS_PIN D8 //Pin D8 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522


char ActualUID[4]; //almacenará el código del Tag leído
char Usuario1[4]= {0xE6, 0x16, 0x0B, 0x4B} ; //código del usuario 1
char Usuario2[4]= {0x12, 0x6A, 0x0D, 0xB0} ; //código del usuario 2
char Usuario3[4]={0x4F, 0x42, 0xED, 0X32};//Codigo de la sube
void setup() 
{
  Serial.begin(9600); //Iniciamos la comunicación serial
  SPI.begin(); //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Lectura del UID");
}

void loop() 
{
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
        else if(compareArray(ActualUID,Usuario3))
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
