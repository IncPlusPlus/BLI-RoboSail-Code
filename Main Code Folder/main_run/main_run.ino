/* BoatCodeStarterWindOnly rev 4/8/2016
© 2014-2016 RoboSail
Find detailed description in Decription tab
*/

#include <Servo.h>
#include "RoboSail.h"
boolean verbose = true;  //true calls function for values to be printed to monitor
boolean Auto = true;

//Fill in min/max parameters for the RC Receiver and WindSensor in RoboSail.h tab

void setup() {
  Serial.begin(115200);
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
    sailPosition = abs(windAngle) / 2; // round it eventually if not whole number 
    rudderPosition = ((windAngle - desBoatAngle) / 180) * 50;
    
    if (rudderPulseWidth < 1005)
    {
      desBoatAngle = desBoatAngle - 45;
          if (desBoatAngle < -180)
          {
            desBoatAngle = 135;
          }
    delay(500);
    }
    if (rudderPulseWidth > 1965)
    {
      desBoatAngle = desBoatAngle + 45;
          if (desBoatAngle > 180)
          {
            desBoatAngle = -135;
          }
    delay(500);
    }
    Serial.print("Desired boat angle is: ");
    Serial.println(desBoatAngle);
    //if the rudder is out of range it will round
    if (rudderPosition > 50)
      {
        rudderPosition = 50;
      }
     if (rudderPosition < -50)
      {
        rudderPosition = -50;
       }
   
      driveSailServo(sailPosition);
      driveRudderServo(rudderPosition);
  
      if (verbose) {printToMonitor();}
}
  

  
//the boat will sail 45 degrees to the wind
// if ((windAngle < 45) && (windAngle >= -45)
// {
//     //rudderPosition = 45;
//     sailPosition = 0;
// }
// else if ((windAngle < -45) && (windAngle > -90))
// {
//   //rudderPosition = -50;
//   sailPosition = 13;
// }
// else if ((windAngle < -90) && (windAngle >= -135))
// {
//   //rudderPosition =  ;
//   sailPosition = 43;
// }
// else if ((windAngle < -135) || (windAngle >= 135))
// {
//   //rudderPosition = -;
//   sailPosition = 90;
// }
// else if ((windAngle <= 135 ) && (windAngle > 90))
// {
//   //rudderPosition = ;
//   sailPosition = 43;
// }
// else 
// {
//   //rudderPosition = ;
//   sailPosition = 13;
// }


/********************* send commands to motors *************************/
  driveSailServo(sailPosition);
  driveRudderServo(rudderPosition);
  
  if (verbose) {printToMonitor();}
  
} //end of loop()


