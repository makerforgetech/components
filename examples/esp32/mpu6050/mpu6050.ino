/* Basic demo for accelerometer readings from Adafruit MPU6050 
 * (example sketch 'Adafruit MPU6050 -> basic_readings', modified)
 * 
 * Guide: https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
 * Pinout:
 * VCC: 3.3V
 * GND: GND
 * SCL: GPIO22
 * SDA: GPIO21
 * 
 * Required Libraries (Tools -> Manage Libraries):
 * - Adafruit MPU6050 (by Adafruit)
 * - Adafruit Unified Sensor (by Adafruit
 * - Adafruit BusIO (by Adafruit) 
 * 
 * Deploy sketch then open serial plotter (Tools -> Serial Plotter) to see the readings
 */
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");

  delay(10);
}
