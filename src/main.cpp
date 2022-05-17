#include <Arduino.h>
#define SOIL_PIN A0 
#define SOIL_POWER 7
#define PUMP_PIN 3

// ##############
// ## Script listens to serial port and writes contents into a file
// ##############
// ## requires pySerial to be installed 
// import serial  # sudo pip install pyserial should work

// serial_port = '/dev/ttyACM0';
// baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
// write_to_file_path = "output.txt";

// output_file = open(write_to_file_path, "w+");
// ser = serial.Serial(serial_port, baud_rate)
// while True:
//     line = ser.readline();
//     line = line.decode("utf-8") #ser.readline returns a binary, convert to string
//     print(line);
//     output_file.write(line);

// Max is about 900
const int MOISTURE_THRESHOLD = 400;
float sensor_value = 0; 
int read_wait = 1000; // 1 second reading intervals

float readSoil() {
  float temp = 0;
  digitalWrite(SOIL_POWER, HIGH);
  delay(10);
  for(int i = 0; i < 100; i++) { 
    temp = temp + analogRead(SOIL_PIN); 
    delay(1); 
  } 
  temp = temp/100.0;
  digitalWrite(SOIL_POWER, LOW);
  return temp;
}

void pumpWater() {
  Serial.println("Water!");
  digitalWrite(PUMP_PIN, HIGH);
  delay(3000);
  digitalWrite(PUMP_PIN, LOW);
}

void setup() { 
  Serial.begin(9600); 
  pinMode(SOIL_POWER, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(SOIL_PIN, INPUT);

  digitalWrite(SOIL_POWER, LOW);
}
void loop() { 
  // Check threshold and trigger relay
  sensor_value = readSoil();
  Serial.println(sensor_value);

  if(sensor_value < MOISTURE_THRESHOLD) {
    pumpWater();
  }
  delay(read_wait); 
}