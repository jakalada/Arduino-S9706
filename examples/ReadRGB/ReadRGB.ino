#include <S9706.h>

const int dataPin = 10; // No.1 Dout connected to digital pin 10
const int rangePin = 4; // No.4 Range connected to digital pin 4
const int clockPin = 5; // No.5 CK connected to digital pin 5
const int gatePin = 6;  // No.6 Gate connected to digital pin 6

S9706 colorSensor(dataPin, rangePin, clockPin, gatePin);

void setup() {
  Serial.begin(9600);
  colorSensor.begin();
}

void loop() {
  // update RGB
  // 
  // S9706::update(mode, durationMs, durationUs = 0)
  //    mode:         specify S9706_MODE_HIGH or S9706_MODE_LOW
  //    durationMs:   specify sensor integration process time (milliseconds)
  //    durationUs:   specify sensor integration process time (microseconds) or not
  colorSensor.update(S9706_MODE_HIGH, 100);

  // get updated RGB (value min: 0, max: 4095)
  int red = colorSensor.getRed();
  int green = colorSensor.getGreen();
  int blue = colorSensor.getBlue();

  // print line "red,geen,blue"
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.println("");

  delay(500);
}

