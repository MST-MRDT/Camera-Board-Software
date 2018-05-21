/*
 * Camera Board Software
 * Rev 1, 2018
 * Used with Camera Board Hardware Rev 1
 * Andrew Van Horn
 * 
 * Controls 4-camera MUX
 */

#include "RoveWare.h"

////////////////////
//   Board Pins   //
////////////////////
/////////////////////////////////////////////////
//X7 Pins
const int MUX1_PIN = PK_4;
const int MUX2_PIN = PK_5;
const int OE_PIN   = PG_1;
//X9 Pins
//const int MUX1_PIN = PF_2;
//const int MUX2_PIN = PF_3;
//const int OE_PIN   = PF_1;
/*The MUX folows the following truth table (MUX2, MUX1):
 * (0,0): Camera 1
 * (0,1): Camera 2
 * (0,1): Camera 3
 * (0,1): Camera 4
 */

////////////////////
// RoveComm Setup //
////////////////////
RoveCommEthernetUdp RoveComm;

//Data ID definition///////////////////////////////////////////////////////////////////////////////////////////////////////////
const uint16_t CAMERA_MUX_CHANNEL = CAMERA_MUX_CHANNEL_1;  //Use this data ID for Camera Board 1 if you have two Camera Boards
//const uint16_t CAMERA_MUX_CHANNEL = CAMERA_MUX_CHANNEL_2;  //Use this data ID for Camera Board 2 if you have two Camera Boards

//Data Value Definition////////////////////////////////////////////////
const uint8_t MUX_CAMERA_1 = 1;
const uint8_t MUX_CAMERA_2 = 2;
const uint8_t MUX_CAMERA_3 = 3;
const uint8_t MUX_CAMERA_4 = 4;

//Read Variables/////////
uint16_t data_id;
size_t command_data_size;
uint8_t data_value[2];

void setup() {
  RoveComm.begin(ROVE_FIRST_OCTET, ROVE_SECOND_OCTET, ROVE_THIRD_OCTET, CAMERABOARD_FOURTH_OCTET);
  delay(10);
  
  pinMode(MUX1_PIN, OUTPUT);
  pinMode(MUX2_PIN, OUTPUT);
  pinMode(OE_PIN,   OUTPUT);

  digitalWrite(MUX1_PIN, LOW);
  digitalWrite(MUX2_PIN, LOW);
  digitalWrite(OE_PIN,   HIGH);
  delay(10);

}

void loop() {
  delay(100);
  RoveComm.read(&data_id, &command_data_size, data_value);

  if(data_id = CAMERA_MUX_CHANNEL)
  {
    switch(data_value[0]
    {
      case(MUX_CAMERA_1):
        digitalWrite(MUX1_PIN, LOW);
        digitalWrite(MUX2_PIN, LOW);
        break;
      case(MUX_CAMERA_2):
        digitalWrite(MUX1_PIN, HIGH);
        digitalWrite(MUX2_PIN, LOW);
        break;
      case(MUX_CAMERA_3):
        digitalWrite(MUX1_PIN, LOW);
        digitalWrite(MUX2_PIN, HIGH);
        break;
      case(MUX_CAMERA_4):
        digitalWrite(MUX1_PIN, HIGH);
        digitalWrite(MUX2_PIN, HIGH);
        break;
    }
  }
}
