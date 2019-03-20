#include <ServoTimer2.h>
ServoTimer2 servo1;

 int triage(int y){
  Serial.println("on commece le triage");
  if(y==0){
    return false;
  }
else{
  servo1.attach(12);
  switch(y){
    case 1:
    servo1.write(1200);
    break;
    case 2:
    servo1.write(1400);
    break;
    case 3:
    servo1.write(1600);
    break;
    case 4:
    servo1.write(1800);
    break;
    case 5:
    servo1.write(1900);
    break;
    
  }
  delay(100);
  servo1.detach();
  return true;
}
Serial.print("le triage est fini");
}
void setup() {
  Serial.begin(9600); 
  servo1.attach(12);
}
void loop() {
  triage(1900);

}
