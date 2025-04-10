#include <RF24.h>
#include <Wire.h>
#include <MPU6050.h>

RF24 radio(9, 10);
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

const byte address[6] = "00001";

struct package {
  int y = 0;
  int x = 0;
};

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  mpu.initialize();
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  data.x = ax;
  data.y = ay;

  data.x = map(data.x, -17000, 17000, 0, 180);
  data.y = map(data.y, -17000, 17000, -180, 180);

  radio.write(&data, sizeof(data));

  Serial.print(data.x);
  Serial.print(" | ");
  Serial.println(data.y);

  delay(15);
}
