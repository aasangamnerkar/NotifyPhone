SYSTEM_THREAD(ENABLED);
#include <blynk.h>
#include "oled-wing-adafruit.h"

OledWingAdafruit display;

// variables
uint16_t reading;
double voltage;
double temperature;

void setup() {
  pinMode(A4, INPUT);
  

  // init display values
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println();
  display.display();
  Blynk.begin("cnjXDn_t7vcs3I-PR-jbSobGd__j2qM9", IPAddress(167, 172, 234, 162), 9090);
  Blynk.run();
}

void loop() {
  display.loop();
  //read sensor and convert values to voltage + temperature
  reading = analogRead(A4);
  voltage = (reading * 3.3) / 4095.0;
  temperature = (voltage - 0.5) * 100;
  String output = "";

  // set up display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
    
  //set up output string with celsius and fahrenheit
  output += "Celsius: ";
  output += (String) temperature;
  output += "\n";
  output += "Fahrenheit: ";
  output += (String) ((temperature*9/5)+32);

  //print to display
  display.println(output);
  display.display();


  // notify app button A pressed
  if (display.pressedA())
  {
    Blynk.notify(output);
  }
}