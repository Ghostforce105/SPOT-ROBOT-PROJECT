#include <WiFi.h>
//#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <stdint.h>
#include <DHT.h>

#define BLYNK_TEMPLATE_ID "YOUR ID"
#define BLYNK_TEMPLATE_NAME "ELECTRONICS PROJECT"
#define BLYNK_AUTH_TOKEN "YOUR TOKEN"

char ssid[] = "########";
char pass[] = "########";

#define MQD0 33
#define MQA0 34
#define SDA 21
#define SCL 22
#define TRIG 25
#define ECHO 32
#define SDA_DHT 19
#define DHT_THRESHOLD 40

#define MPU_ADDR 0x68
#define DHTTYPE DHT11
DHT dht(SDA_DHT, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, ESP32!");

  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Smoke sensor
  pinMode(MQD0, INPUT);

  // Start I2C
  Wire.begin(SDA, SCL);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // Ultrasonic bursts
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // HUMIDITY
  dht.begin();
}

void loop() {
  // GAS SENSOR READING
  int gasDigital = digitalRead(MQD0);
  int gasAnalog = analogRead(MQA0);
  Serial.print("Gas D0: ");
  Serial.print(gasDigital);
  Serial.print(" | Gas A0: ");
  Serial.println(gasAnalog);
  // Blynk.virtualWrite(V1, gasAnalog);

  // MPU6050 SENSOR READING
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Starting register for Accel X
  Wire.endTransmission(false); // Restart condition

  Wire.requestFrom(MPU_ADDR, 14);
  uint16_t rawData[7]; // ax, ay, az, temp, gx, gy, gz

  for (int i = 0; i < 7; i++) {
    uint8_t high = Wire.read();
    uint8_t low = Wire.read();
    rawData[i] = (high << 8) | low;
  }

  // Print values
  Serial.print("Accel X: "); Serial.print(rawData[0]);
  Serial.print(" | Accel Y: "); Serial.print(rawData[1]);
  Serial.print(" | Accel Z: "); Serial.print(rawData[2]);
  /*
  Blynk.virtualWrite(V7, (rawData[0]/16384.0)*9.81);
  Blynk.virtualWrite(V8, (rawData[1]/16284.0)*9.81);
  Blynk.virtualWrite(V9, (rawData[2]/16284.0)*9.81);
  */

  Serial.print(" | Temp: ");
  float temperature = rawData[3] / 340.0 + 36.53; // Convert to Celsius
  Serial.print(temperature);
  //Blynk.virtualWrite(V1, temperature);

  Serial.print(" | Gyro X: "); Serial.print(rawData[4]);
  Serial.print(" | Gyro Y: "); Serial.print(rawData[5]);
  Serial.print(" | Gyro Z: "); Serial.print(rawData[6]);
  //Blynk.virtualWrite(V4, rawData[4]/131.0);
  //Blynk.virtualWrite(V5, rawData[5]/131.0);
  //Blynk.virtualWrite(V6, rawData[6]/131.0);

  // Ultrasonic SENSOR READING
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); // Short LOW pulse before triggering
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  float distance = duration * 0.0343 / 2;
  Serial.print("DISTANCE: ");
  Serial.print(distance);
  Serial.println(" cm");
  //Blynk.virtualWrite(V3, distance);

  // HUMIDITY SENSOR READING
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
  }
  //Blynk.virtualWrite(V0, HUMIDITY);

  delay(1000);
}
//-------------------------------------------------------------
