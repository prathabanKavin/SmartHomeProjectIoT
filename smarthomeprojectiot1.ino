#include <IRremote.h>

int pin8 = 8;
int MQ2sensor = A0;
int sensorValue = 0;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  pinMode(pin8, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  sensorValue = analogRead(MQ2sensor);
 // Serial.println(sensorValue, DEC);
  if (sensorValue > 750) {
    Serial.print("SENSOR VALUE: ");
    Serial.print(sensorValue, DEC);
    Serial.println(" | SMOKE DETECTED");
    digitalWrite(pin8, HIGH);
    if (irrecv.decode(&results)){
  		Serial.println(results.value, HEX);
    	irrecv.resume();
      if(results.value == 0xFD30CF){
        digitalWrite(pin8, LOW);
        delay(10000);
      } else if(results.value == 0xFD08F7){
        digitalWrite(pin8, HIGH);
      }
  	}
  }
  else {
    digitalWrite(pin8, LOW);
	Serial.print("SENSOR VALUE: ");
    Serial.println(sensorValue, DEC);

  }
delay(1500);
}