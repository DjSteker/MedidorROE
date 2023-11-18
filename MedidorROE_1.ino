
#include "TramasMicros2.h"

int aFwd, aRef;
float vSWR;


int PIN_ReleS1;
int PIN_Led = 13;
int Cuenta;

void setup(){
   Serial.begin(9600);
 pinMode(PIN_Led, OUTPUT); 
   delay(3000);
}



TramaTiempo blink_LecturaSensores = TramaTiempo(4000123, LecturaSensores);

TramaTiempo blink_LedRoe1 = TramaTiempo(500123, Led);
TramaTiempo blink_LedError = TramaTiempo(20123, LedError);

void LecturaSensores() {

  Cuenta = 0;
 
  
   aFwd = analogRead(A0);
   aRef = analogRead(A1);



   vSWR = (aFwd+aRef)/(aFwd-aRef);

   Serial.print("FWD: ");
   Serial.print(aFwd);
   Serial.print(" | REF: ");
   Serial.print(aRef);  
   Serial.print(" | SWR: ");
   Serial.println(vSWR);
   blink_LedRoe1.reset();
   if (aRef >= 1023 || aFwd >= 1023)
   {  

      blink_LedError.enable();
      Serial.print("Error: ");
      blink_LedRoe1.disable();
   }
   else
   {

     blink_LedRoe1.enable();
      Serial.print("Roe1: ");
      blink_LedError.disable();
    }
}



void Led() {
bool valor = digitalRead(PIN_Led);
 if ((bool)digitalRead(PIN_Led))
    {
      digitalWrite(PIN_Led, LOW);//digitalWrite(PinLedS1, LOW);
      
        blink_LedRoe1.setInterval(60000) ;
        Cuenta+=1;
          if (vSWR < 1 ) {
            blink_LedRoe1.setInterval(70000) ;
            blink_LedRoe1.disable();
          } 


    
    }
    else {
      digitalWrite(PIN_Led, HIGH);

        if (vSWR >= (Cuenta/2) ) {
          blink_LedRoe1.setInterval(70000) ;
        } 
        else {
          blink_LedRoe1.disable();
        }
     

      
    }

  
 
}



void LedError() {

 if ((bool)digitalRead(PIN_Led))
    {
      digitalWrite(PIN_Led, LOW);
     

    
    }
    else {
      digitalWrite(PIN_Led, HIGH);

    }

  
 
}


void loop(){
 
  blink_LecturaSensores.check();
  blink_LedRoe1.check();
  blink_LedError.check();
  delay(1);
}
