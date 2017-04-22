#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "RoveEthernet.h"
#include "RoveComm.h"

// Camera Board Rev 1 Pin Definitions
#define MUX0_0      PD_0
#define MUX0_1      PD_1
#define MUX0_2      PD_2
#define MUX0_SHDN   PD_3
#define MUX1_0      PD_7
#define MUX1_1      PD_6
#define MUX1_2      PD_5
#define MUX1_SHDN   PD_4

// RoveComm dataIDs
#define FEED0_OUT 2832
#define FEED1_OUT 2833

void setup()
{
  // Serial.begin(9600);
  
  // Set pins to outputs
  pinMode(MUX0_2, OUTPUT);
  pinMode(MUX0_1, OUTPUT);
  pinMode(MUX0_0, OUTPUT);
  pinMode(MUX0_SHDN, OUTPUT);
  pinMode(MUX1_2, OUTPUT);
  pinMode(MUX1_1, OUTPUT);
  pinMode(MUX1_0, OUTPUT);
  pinMode(MUX1_SHDN, OUTPUT);
  
  // Disable active low shutdowns
  digitalWrite(MUX0_SHDN, HIGH);
  digitalWrite(MUX1_SHDN, HIGH);
  
  // Initialize output_0 to camera_0 and output_1 to camera_1
  digitalWrite(MUX0_2, LOW);
  digitalWrite(MUX0_1, LOW);
  digitalWrite(MUX0_0, LOW);
  digitalWrite(MUX1_2, LOW);
  digitalWrite(MUX1_1, LOW);
  digitalWrite(MUX1_0, HIGH);
  
  // Initialize RoveComm
  roveComm_Begin(192,168,1,140);
}

void loop()
{
  uint16_t dataID = 0;
  size_t size = 0;
  uint8_t data[6];
  roveComm_GetMsg(&dataID, &size, data);
  
  switch(dataID) 
  {
    case FEED0_OUT:
      switchfeed(0, data[0]);
      break;
    case FEED1_OUT:
      switchfeed(1, data[0]);
      break;
  }
}

// Switch the camera that's output on the feed
void switchfeed(uint8_t output, uint8_t camera) 
{
  uint8_t pin2;
  uint8_t pin1;
  uint8_t pin0;
  switch (output)
  {
    case 0:
      pin2 = MUX0_2;
      pin1 = MUX0_1;
      pin0 = MUX0_0;
      break;
    case 1:
      pin2 = MUX1_2;
      pin1 = MUX1_1;
      pin0 = MUX1_0;
      break;
    default:
      return;
  }
  
  switch (camera)
  {
    case 0:
      digitalWrite(pin2, LOW);
      digitalWrite(pin1, LOW);
      digitalWrite(pin0, LOW);
      break;
    case 1:
      digitalWrite(pin2, LOW);
      digitalWrite(pin1, LOW);
      digitalWrite(pin0, HIGH);
      break;
    case 2:
      digitalWrite(pin2, LOW);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin0, LOW);
      break;
    case 3:
      digitalWrite(pin2, LOW);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin0, HIGH);
      break;
    case 4:
      digitalWrite(pin2, HIGH);
      digitalWrite(pin1, LOW);
      digitalWrite(pin0, LOW);
      break;
    case 5:
      digitalWrite(pin2, HIGH);
      digitalWrite(pin1, LOW);
      digitalWrite(pin0, HIGH);
      break;
    case 6:
      digitalWrite(pin2, HIGH);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin0, LOW);
      break;
    case 7:
      digitalWrite(pin2, HIGH);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin0, HIGH);
      break;
    default:
      return;
  }
}
