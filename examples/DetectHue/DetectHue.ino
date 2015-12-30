#include <math.h>

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
  double rgb[3] = {
    colorSensor.getRed(),
    colorSensor.getGreen(),
    colorSensor.getBlue()
  };

  // adjust white balance
  //
  // hard coded white balance
  //    red: 1.0
  //    green: 1.3
  //    blue; 1.1
  rgb[1] = rgb[1] / 1.3;
  rgb[2] = rgb[2] / 1.1;

  if (rgb[0] >= 1 || rgb[1] >= 1 || rgb[2] >= 1) {
    // detect brightest color
    int detectIndex = 0;
    for (int i = 1; i < 3; i++) {
      if (rgb[i] > rgb[detectIndex]) {
        detectIndex = i;
      }
    }

    // up brightest color value to 4095 (max value) and calculate ratio
    double ratio = S9706_RGB_MAX / rgb[detectIndex];
    rgb[detectIndex] = S9706_RGB_MAX;

    // multiply the other color value by the ratio.
    for (int i = 0; i < 3; i++) {
      if (i != detectIndex) {
        rgb[i] = rgb[i] * ratio;
      }
    }
  }

  // calculate hue
  double denominator = (rgb[0] * 2 - rgb[1] - rgb[2]);
  double hue = -1;
  if (denominator != 0.0) {
    hue = (sqrt(3) * (rgb[1] - rgb[2])) / denominator;
    hue = fmod((hue + 360.0), 360.0);
  }

  // print line "hue,red,geen,blue"
  Serial.print(hue);
  Serial.print(",");
  Serial.print(rgb[0]);
  Serial.print(",");
  Serial.print(rgb[1]);
  Serial.print(",");
  Serial.print(rgb[2]);
  Serial.println("");

  delay(500);
}

