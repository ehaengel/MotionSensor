#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>

Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);  // Use I2C, ID #1000

#define LSM9DS0_XM_CS 10
#define LSM9DS0_GYRO_CS 9
#define LSM9DS0_SCLK 13
#define LSM9DS0_MISO 12
#define LSM9DS0_MOSI 11

int baud_mode = 0;
int data_mode = 0;

void configureSensor(void)
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);

  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

void setup(void) 
{
  pinMode(2, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  pinMode(13, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, HIGH);

  delay(1000);

  if(digitalRead(4) == LOW)
  {
    baud_mode = 0;
    Serial.begin(9600);
    Serial.println("9600");
  }

  else if(digitalRead(5) == LOW)
  {
    baud_mode = 1;
    Serial.begin(115200);
    Serial.println("115200");
  }

  else
  {
    while(1)
    {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
  }

  if(digitalRead(10) == LOW)
  {
    data_mode = 0;
    Serial.println("text mode");
  }

  else if(digitalRead(11) == LOW)
  {
    Serial.println("binary mode");
    data_mode = 1;
  }

  else
  {
    while(1)
    {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
  }

  Serial.println("Checking LSM");
  if(!lsm.begin())
  {
    Serial.println("Ooops, no LSM9DS0 detected ... Check your wiring or I2C ADDR!");
    while(1)
    {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
  }

  Serial.println("Configuring sensor");
  configureSensor();

  Serial.println("Start program");
  Serial.println(baud_mode);
  Serial.println(data_mode);
}

void loop(void) 
{
  sensors_event_t accel, mag, gyro, temp;

  lsm.getEvent(&accel, &mag, &gyro, &temp); 

  if(data_mode == 0)
  {
    Serial.print(millis(), 8); 
    Serial.print(" ");
    Serial.print(accel.acceleration.x, 8); 
    Serial.print(" ");
    Serial.print(accel.acceleration.y, 8); 
    Serial.print(" ");
    Serial.print(accel.acceleration.z, 8); 
    Serial.print(" ");
    Serial.print(mag.magnetic.x, 8); 
    Serial.print(" ");
    Serial.print(mag.magnetic.y, 8); 
    Serial.print(" ");
    Serial.print(mag.magnetic.z, 8); 
    Serial.print(" ");
    Serial.print(gyro.gyro.x, 8); 
    Serial.print(" ");
    Serial.print(gyro.gyro.y, 8); 
    Serial.print(" ");
    Serial.print(gyro.gyro.z, 8); 
    Serial.print(" ");
    Serial.print(temp.temperature, 8); 
    Serial.print("\n");
  }

  else
  {
    float sensor_output[10];
    sensor_output[0] = accel.acceleration.x;
    sensor_output[1] = accel.acceleration.y;
    sensor_output[2] = accel.acceleration.z;
    sensor_output[3] = mag.magnetic.x;
    sensor_output[4] = mag.magnetic.y;
    sensor_output[5] = mag.magnetic.z;
    sensor_output[6] = gyro.gyro.x;
    sensor_output[7] = gyro.gyro.y;
    sensor_output[8] = gyro.gyro.z;
    sensor_output[9] = temp.temperature;

    unsigned long cur_time = millis();

    Serial.write("start");
    Serial.write((const uint8_t*) &cur_time, sizeof(unsigned long));
    Serial.write((const uint8_t*) sensor_output, sizeof(float)*10);
  }
}

