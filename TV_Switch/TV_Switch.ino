#include <tiny_IRremote.h>

IRrecv irrecv(PB0);
decode_results results;

int relay = PB1;
bool on = 0;

void setup() {
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
 
  irrecv.enableIRIn();
}

void loop() {
  int sensorValue = analogRead(PB2);
  float voltage = sensorValue * (5.0 / 1023.0);
 

  //irrecv.decode(&results);
  if (irrecv.decode(&results)) {
   
    if (((results.value == 0xF4BA2988)||(results.value == 0xE0E040BF)) && (on == 0)) {
      digitalWrite(relay, HIGH);
      delay(1000);
      on = 1;

      irrecv.resume();

    }
    irrecv.resume();

  }



  if ((voltage < 2) && (on == 1)) {
    on = 0;
    digitalWrite(relay, LOW);
  }

}
