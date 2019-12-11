#include "sistem.h"
#include "arduino.h"
#include "cnu1.h"



extern bool flag;
bool estado = 0;
extern String str; //var global definida en el .ino
extern String str2; //var global definida en el .ino

void initPorts(void)
{
  Serial.begin(9600);
}

//*******************************************************
//Configura Timer2
//******************************************************
void initTimer2(void)
{
  SREG = 0b01111111;       //Desabilitar interrupciones
  TIMSK2 = 0b00000001;     //Habilita la interrupcion por desbordamiento
  TCCR2B = 0b00000011;     //Configura preescala para que FT2 sea de 250KHz
  SREG = 0b10000000;       //Habilitar interrupciones //Desabilitar interrupciones
  TCNT2 = 5;               //255-5 =250 (el valor que queremos)
}

bool captureData(char car)
{
  char datoRet = 0;
  switch (car)
  {
    case '>':
      {
        str = "";
        str2 = "";
        break;
      }
    case '<':
      {
        datoRet = 1;
        break;
      }
    default:
      {
        str = str + car;
        str2 = str2 + car;
      }
  }
  return datoRet;
}



void parseMsg()
{
  String tipoCmd = str.substring(1, 3); //captura del car 1 al car 3 (2 caracter) ej: recibe; SP1234 y se queda con P1
  String Valor;


  if (tipoCmd == "U1")//User1
  {
    cnu1();
  }
 
}
