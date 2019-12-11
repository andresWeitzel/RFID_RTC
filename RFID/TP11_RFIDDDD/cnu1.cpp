//--Config new user(cnu)--
#include "sistem.h"
#include "arduino.h"
#include "cnu1.h"

//--Importamos las variables del .ino-- 
extern String str;
extern int b1u1;//Bloque 1 del usuario1
extern int b2u1;//Bloque 2 del usuario1
extern int b3u1;//Bloque 3 del usuario1
extern int b4u1;//Bloque 4 del usuario1

//extern char ActualUID[4];

extern char ActualUID[4]{ b1u1, b2u1, b3u1, b4u1};


void cnu1()
{
  String accion = str.substring(0, 1); //se queda con  Q o S
  if (accion == "Q")
  {
    ru1();
  }

  if (accion == "S")
  {
    su1();
  }

}


void ru1()
{

  Serial.println(ActualUID);
  /*char str2[30];
  sprintf(str2, ">RU1%02d%02d%02d%02<",b1u1,b2u1,b3u1,b4u1);
  Serial.println(str2);
*/
}

void su1()
{
  //Primer byte del id. //Su1xx000000 captura el valor del u1.
  b1u1 = str.substring(3, 5).toInt();
  //Segundo byte del id. //Su100xx0000 captura el valor del u1.
  b2u1 = str.substring(5, 7).toInt();
  //Tercer byte del id. //Su10000xx0000 captura el valor del u1.
  b3u1 = str.substring(7, 9).toInt();
  //Cuarto byte del id. //Su1000000xx captura el valor del u1.
  b4u1 = str.substring(9, 11).toInt();



}
/*//Funcion para nuevo usuario 1
void nu1(){
  char user1[4]{ "0x"+b1u1, "0x"+b2u1, "0x"+b3u1, "0x"+b4u1};
}*/
