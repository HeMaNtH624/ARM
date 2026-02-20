#include "arduino_secrets.h"
#include "thingProperties.h"

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here  
}


/*
  Since Fan is READ_WRITE variable, onFanChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFanChange()  {
  // Add your code here to act upon Fan change
  if(fan)
  {
    Serial.write('A');
  }
  else
  {
    Serial.write('a');
  }
}

/*
  Since Light is READ_WRITE variable, onLightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightChange()  {
  // Add your code here to act upon Light change
  if(light)
  {
    Serial.write('B');
  }
  else
  {
    Serial.write('b');
  }
}

/*
  Since Buzzer is READ_WRITE variable, onBuzzerChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBuzzerChange()  {
  // Add your code here to act upon Buzzer change
  if(buzzer)
  {
    Serial.write('C');
  }
  else
  {
    Serial.write('c');
  }
}

/*
  Since Conveyor is READ_WRITE variable, onConveyorChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onConveyorChange()  {
  // Add your code here to act upon Conveyor change
  if(conveyor)
  {
    Serial.write('D');
  }
  else
  {
    Serial.write('d');
  }
}