#include <ServoTimer2.h>
ServoTimer2 servo2;  //stop 9

void arret(bool condition){
  servo2.attach(9);
  delay(100);
   if(condition == true){
    Serial.println("déblocage");
    servo2.write(0);
   }
   if(condition == false){
    Serial.println("blocage");
    servo2.write(180);
   }
   servo2.detach();
}

void setup() {
  Serial.begin(9600); 
  servo2.attach(9);
}

void loop() {
  arret(true);
  delay(500);
  arret(false);
  delay(500);

}
