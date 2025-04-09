#include <Arduino.h>
#include <HCSR04.h>
#include <liquidcrystal.h>
#include <dht.h>
#include <MFRC522.h>
#include <IRremote.h>


#define ONE 16724175   // Define the key 1
#define TWO 16718055   // Define the key 2
#define THREE 16743045 // Define the key 3
#define FOUR 16716015  // Define the key 4
#define FIVE 16726215  // Define the key 5
#define SIX 16734885   // Define the key 6
#define SEVEN 16728765 // Define the key 7
#define EIGHT 16730805// Define the key 8
#define NINE 16732845 // Define the key 9
#define ZERO 16738455  // Define the key 0

int echo_pin = 2;
int trig_pin = 3;
const int forward = 6;
const int backward = 7;
int time_delay = 1000;
int val = 0;

int headlight1 = 8;
int headlight2 = 9;
int headlight_intensity;

long duration;
int distance;
int auth = 0;

int motor_speed = 0;
int tone_buzzer = 28;

int RECV_PIN = 49;
IRrecv irrecv(RECV_PIN); // pin where you connect the output pin of AX-1838HS
decode_results results;

// object for lcd display
LiquidCrystal lcd(47, 48, 49, 52, 51, 53);

// Temperature sensor
dht DHT;
#define DHT11_PIN 47

//RFID
#define SS_PIN 53
#define RST_PIN 46
MFRC522 mfr(SS_PIN,RST_PIN);  //create MFRC522 instance




void setup()
{
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(headlight1, OUTPUT);
  pinMode(headlight2, OUTPUT);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(tone_buzzer,OUTPUT);
  Serial.begin(9600);

  pinMode(26, OUTPUT);
  analogWrite(26,120);
  lcd.begin(16,2);

  SPI.begin();
  mfr.PCD_Init();
  //Serial.println("Scan your fob");
  irrecv.enableIRIn();
}

void loop() {
  //Security Implementation
  // Look for new cards
  if ( ! mfr.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfr.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfr.uid.size; i++) 
  {
     Serial.print(mfr.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfr.uid.uidByte[i], HEX);
     content.concat(String(mfr.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfr.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "E9 54 AE B0") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    tone(tone_buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(tone_buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
    Serial.println();
    
  }
   else   {
    Serial.println(" Access denied");
  }

  //the circuit
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
  if (distance > 50)
  {
    digitalWrite(forward, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    motor_speed = analogRead(A1);
  }
  else if ((distance < 50) && (distance > 35))
  {
    analogWrite(forward, 190);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    motor_speed = analogRead(A1);
  }
  else if ((distance < 35) && (distance > 15))
  {
    analogWrite(forward, 120);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    motor_speed = analogRead(A1);
  }
  else if (distance < 15)
  {
    digitalWrite(forward, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    motor_speed = 0;
  }

  int chk = DHT.read11(DHT11_PIN);
  int hold = DHT.temperature;
  String temperature = String(hold);

  // water depth
  int depth = analogRead(A0);
  int hold_2 = depth;
  String coolant_level = String(hold_2);

  // motor treatment
  int hold_3 = motor_speed;
  String motor_speed_treated = String(hold_3);

  // LCD config
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Temp: ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.write("Motor Spd: ");
  lcd.print(motor_speed_treated);

  delay(1000);
  lcd.clear();
  lcd.write("Cool Lvl: ");
  lcd.print(coolant_level);

  //LED test IR remote
  if (irrecv.decode(&results))
  {
    //Serial.println(results.value);
    if (results.value == ONE || results.value == 2534850111 || results.value == 3790209247 || results.value == 3736135894)  
    {                               // Check if the key 1 is pressed
      digitalWrite(headlight1, HIGH); // Turn on the headlight 1
      headlight_intensity = 100;
      
    }
    else if (results.value == TWO || results.value == 1033561079 || results.value == 2041940611 || results.value == 1033561079 || results.value == 4294967295)    
    {                                // Check if the key 2 is pressed
      analogWrite(headlight1, 150); // Turn on the headlight 1 (dim)
      headlight_intensity = 50;
      
    }
    else if (results.value == FOUR || results.value == 2351064443 || results.value == 1603439768 || results.value == 1827708134) 
    {                                // Check if the key 3 is pressed
      digitalWrite(headlight1, LOW); // Turn off the headlight 1
      headlight_intensity = 0;
      
    }  
    irrecv.resume(); // Receive the next value    
  }

  delay(1000);
  
  if (distance < 10)
  {
    String str_dist = "00" + String(distance);
    Serial.print(str_dist);
    Serial.print(",");
  }
  else if (distance < 100)
  {
    String str_dist = "00" + String(distance);
    Serial.print(str_dist);
    Serial.print(",");
  }
  else
  {
    Serial.print(distance);
    Serial.print(",");
  }
  
  Serial.print(temperature);
  Serial.print(",");

  if (depth < 10)
  {
    String str_cool_lvl = "00" + String(depth);
    Serial.print(str_cool_lvl);
    Serial.print(",");
  }
  else if (depth < 100)
  {
    String str_cool_lvl = "0" + String(depth);
    Serial.print(str_cool_lvl);
    Serial.print(",");
  }
  else
  {
    Serial.print(depth);
    Serial.print(",");
  }

  if (motor_speed < 10)
  {
    String str_motor_spd = "000" + String(motor_speed);
    Serial.print(str_motor_spd);
    Serial.print(",");
  }
  else if (motor_speed < 100)
  {
    String str_motor_spd = "00" + String(motor_speed);
    Serial.print(str_motor_spd);
    Serial.print(",");
  }
  else
  {
    Serial.print(motor_speed);
    Serial.print(",");
  }

  if (headlight_intensity < 10)
  {
    String str_head = "00" + String(headlight_intensity);
    Serial.print(str_head);
    Serial.print(",");
  }
  else if (headlight_intensity < 100)
  {
    String str_head = "0" + String(headlight_intensity);
    Serial.print(str_head);
    Serial.print(",");
  }
  else
  {
    Serial.print(headlight_intensity);
    Serial.print(",");
  }
  Serial.print("\n");
}

