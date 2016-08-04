/* BoatCodeStarterWindOnly rev 4/8/2016
© 2014-2016 RoboSail
Find detailed description in Decription tab
*/

#include <Servo.h>  
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include "RoboSail.h"
boolean verbose = true;  //true calls function for values to be printed to monitor

//Fill in min/max parameters for the RC Receiver and WindSensor in RoboSail.h tab

void setup() {
  Serial.begin(115200);
  accel.begin();
  Serial.println("\nRoboSail BoatCode - The Blobfish");  //write program name here
  // Set RC receiver and WindSensor on digital input pins
  declarePins();
}

void loop() {
//*********** Read in data from the RC receiver and sensors *********
readReceiverSensors();

// You now have values from the RC Receiver and Sensors in these variable: 
// rudderPosition, sailPosition, and windAngle
// Calculate new values for rudderPosition and sailPosition in degrees 
// and set those variables to the new values.
// If you do not set the values, it will use the values from the RC Receiver
// For example, to make the rudder follow the wind angle you would have:
// rudderPosition = windAngle;
//**************** your code here ******************



while (sailPulseWidth >= 2030)
{
    readReceiverSensors();
    sailPosition = abs(windAngle) / 2;  //set the sail in relation to the wind, round it eventually if not whole number
    
    rudderPosition = (((windAngle - newdesBoatAngle) / 90) * 50) * -1; //set the rudder position based on the desired angle relative to the wind

    if (abs(windAngle - newdesBoatAngle) > 180)
    {
      rudderPosition = rudderPosition * -1;
    }

    
  
    if (rudderPulseWidth < 1050)  //if rudderPulseWidth is less than 1005, which is a swipe all the way left, subtract 45 degrees to the Boat angle in relation to the wind angle and wait 1/2 second
    {
      newdesBoatAngle = newdesBoatAngle - 45;
          if (newdesBoatAngle < -180) //in case the newdesBoatAngle goes less than -180, swing around to positive 135
          {
            newdesBoatAngle = 135;
          }
          if (newdesBoatAngle == 0) //in case the newdesBoatAngle goes to zero, go to -45
          {
            newdesBoatAngle = -45;
          }
      while (rudderPulseWidth < 1400)  {readReceiverSensors();}
    }

    if (rudderPulseWidth > 1800) //if rudderPulseWidth is greater than 1965, which is a swipe all the way right, add 45 degrees to the Boat angle in relation to the wind angle and wait 1/2 second
    {
      newdesBoatAngle = newdesBoatAngle + 45;
          if (newdesBoatAngle > 180)  //in the case that the newdesBoatAngle goes greater than 180, swing around to negative 135
          {
            newdesBoatAngle = -135;
          }
          if (newdesBoatAngle == 0) //in case the newdesBoatAngle goes to zero, go to 45
          {
            newdesBoatAngle = 45;
          }
      while (rudderPulseWidth > 1550)  {readReceiverSensors();}
    }
    Serial.print("------------------------------------------------------------------------------------------------------------------------------------------------------------------Desired boat angle is: ");
    Serial.println(newdesBoatAngle);
    //if the rudder is out of range it will round to 50 or -50 respectively 
    if (rudderPosition > 50)
      {
        rudderPosition = 50;
      }
     if (rudderPosition < -50)
      {
        rudderPosition = -50;
       }

  if (abs(newdesBoatAngle) < abs(desBoatAngle)) //if the new desired boat angle is less than the old desired boat angle, the sail will be let out
  {
    sailPosition = 90;
  }
  if (windAngle == newdesBoatAngle) //when the newdesBoatAngle is reached, the older boat angle will be overwritten for later comparisons
  {
    desBoatAngle = newdesBoatAngle;
  }
  
  if (abs(roll) > maxRoll)  //If the roll value (which could be + or -) is greater than max allowed roll...
  {
    sailPosition = sailPosition + (abs(roll) * compensationFactor);  //adjust the sail accordingly
    if (sailPosition > 90)  //catch if the sail is greater than what it should be
    {
      sailPosition = 90;
      Serial.println("Sail position is out of range, defaulting to 90.");
    }
  }
  
      driveSailServo(sailPosition);
      driveRudderServo(rudderPosition);
  
      if (verbose) {printToMonitor();}
}


  




/********************* send commands to motors *************************/
  driveSailServo(sailPosition);
  driveRudderServo(rudderPosition);
  
  if (verbose) {printToMonitor();}
  
} //end of loop()


