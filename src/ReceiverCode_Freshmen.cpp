#include <Servo.h>
#include <RF24.h>

Servo turn;
Servo ESC;

RF24 radio(9, 10);
const byte address[6] = "00001";

struct package {
  int y = 0;
  int x = 0;
};

typedef struct package Package;
Package data;

void setup() {
  ESC.attach(8, 1000, 2000);
  turn.attach(7, 1000, 2000);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    data.x -= 0;

    Serial.print(data.x);
    Serial.print(" | ");
    Serial.println(data.y);

    turn.write(data.x);
    ESC.write(data.y);
  }
}
