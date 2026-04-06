#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>


#define PIN_EINK_CS   10
#define PIN_EINK_DC   9
#define PIN_EINK_RST  8
#define PIN_EINK_BUSY 7

#define PIN_EINK_MOSI 11
#define PIN_EINK_CLK  12

#define PIN_I2C_SDA 5
#define PIN_I2C_SCL 6

#define PIN_ENC_CLK 3
#define PIN_ENC_DT  4
#define PIN_ENC_SW  2



Adafruit_BME280 bme;

int lastCLK = HIGH;



void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("InkDesk is alive!!!!");

  
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  
  SPI.begin(PIN_EINK_CLK, -1, PIN_EINK_MOSI);

  
  pinMode(PIN_ENC_CLK, INPUT_PULLUP);
  pinMode(PIN_ENC_DT, INPUT_PULLUP);
  pinMode(PIN_ENC_SW, INPUT_PULLUP);

  
  if (!bme.begin(0x76))
  {
    Serial.println("BME280 NOT FOUND");
  }
  else
  {
    Serial.println("BME280 OK:3");
  }

  Serial.println("Setup complete yay");
}



void loop()
{
  
  static unsigned long timer = 0;

  if (millis() - timer > 3000)
  {
    timer = millis();

    float temp = bme.readTemperature();
    float humidity = bme.readHumidity();

    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  
  int currentCLK = digitalRead(PIN_ENC_CLK);

  if (currentCLK != lastCLK && currentCLK == LOW)
  {
    if (digitalRead(PIN_ENC_DT) != currentCLK)
    {
      Serial.println("Encoder: RIGHT");
    }
    else
    {
      Serial.println("Encoder: LEFT");
    }
  }

  lastCLK = currentCLK;

  
  if (digitalRead(PIN_ENC_SW) == LOW)
  {
    Serial.println("Encoder  pressed");
    delay(300);
  }
}
