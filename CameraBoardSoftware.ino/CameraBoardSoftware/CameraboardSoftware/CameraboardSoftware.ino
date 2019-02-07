/*
   Camera Board Software
   Rev 1, 2018
   Used with Camera Board Hardware Rev 1
   Brian Dahlman
   Controls 4-camera MUX
*/

#include "RoveComm.h"

////////////////////
//   Board Pins   //
////////////////////
/////////////////////////////////////////////////
//X7 Pins
const int MUX_A0                 = PF_1;
const int MUX_A1                 = PF_2;
const int MUXA_SHDN              = PP_2;

const int MUX_B0                 = PF_3;
const int MUX_B1                 = PG_0;
const int MUXB_SHDN              = PL_3; 
/*The MUX folows the following truth table (MUX_A0, MUX_A1):
   (0,0): Camera 1
   (0,1): Camera 2
   (0,1): Camera 3
   (0,1): Camera 4
*/

////////////////////
// RoveComm Setup //
////////////////////
RoveCommEthernetUdp RoveComm;

//Data ID definition///////////////////////////////////////////////////////////////////////////////////////////////////////////
//const uint16_t CAMERA_MUX_CHANNEL = CAMERA_MUX_CHANNEL_1;  //Use this data ID for Camera Board 1 if you have two Camera Boards
//const uint16_t CAMERA_MUX_CHANNEL = CAMERA_MUX_CHANNEL_2;  //Use this data ID for Camera Board 2 if you have two Camera Boards

///////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
//  RoveComm.begin(CAMERABOARD_FOURTH_OCTET);
  delay(10);
  Serial.begin(9600);
  pinMode(MUX_A0,           OUTPUT);
  pinMode(MUX_A1,           OUTPUT);
  pinMode(MUX_B0,           OUTPUT);
  pinMode(MUX_B1,           OUTPUT);
  pinMode(MUXA_SHDN,        OUTPUT);
  pinMode(MUXB_SHDN,        OUTPUT);
 // pinMode(OUTPUT_ENABLE1_OE_PIN, OUTPUT);

  digitalWrite(MUX_A0,           LOW);
  digitalWrite(MUX_A1,           LOW);
  digitalWrite(MUX_A0,           LOW);
  digitalWrite(MUX_A1,           LOW);
  digitalWrite(MUXA_SHDN,        HIGH); //Active low
  digitalWrite(MUXB_SHDN,        HIGH);
 // digitalWrite(OUTPUT_ENABLE1_OE_PIN, HIGH);
 
  delay(10);
}

//////////////////////////////////////////////////////////
void loop() {
//////Read Variables/////////
  delay(100);
  rovecomm_packet packet;
  packet = RoveComm.read();
  if(packet.data_id!=0)
  {
    Serial.println(packet.data_id);
    Serial.println(packet.data_count);
    for(int i = 0; i<packet.data_count; i++)
    {
      Serial.print(packet.data[i]);
    }
    switch(packet.data[0])
    {
      case 0:
      {
        digitalWrite(MUX_A0, LOW);
        digitalWrite(MUX_A1, LOW);
        Serial.println("MUX Camera 1");
        break;
      }
      case 1:
      {
        digitalWrite(MUX_A0, HIGH);
        digitalWrite(MUX_A1, LOW);
        Serial.println("MUX Camera 2");
        break;
      }
      case 2:
      {
        digitalWrite(MUX_A0, LOW);
        digitalWrite(MUX_A1, HIGH);
        Serial.println("MUX Camera 3");
        break;
      }
      case 3:
      {
        digitalWrite(MUX_A0, HIGH);
        digitalWrite(MUX_A1, HIGH);
        Serial.println("MUX Camera 4"); 
        break;
      }
      default:
        break;
    }
  }
}



/*
//////////////////////OLD CODE///////////////////////////
  delay(100);
  RoveComm.read(&data_id, &command_data_size, &data_value);

  Serial.print("ID: ");
  Serial.println(data_id);
  Serial.print("Value: ");
  Serial.println(data_value);

  if (data_id == RC_CAMERABOARD_CAMMUX_DATAID)
  {
    switch (data_value)
    {
      case (MUX_CAMERA_1):
        digitalWrite(MUX_A0, LOW);
        digitalWrite(MUX_A1, LOW);
        Serial.println("MUX Camera 1");
        break;
      case (MUX_CAMERA_2):
        digitalWrite(MUX_A0, HIGH);
        digitalWrite(MUX_A1, LOW);
        Serial.println("MUX Camera 2");
        break;
      case (MUX_CAMERA_3):
        digitalWrite(MUX_A0, LOW);
        digitalWrite(MUX_A1, HIGH);
        Serial.println("MUX Camera 3");
        break;
      case (MUX_CAMERA_4):
        digitalWrite(MUX_A0, HIGH);
        digitalWrite(MUX_A1, HIGH);
        Serial.println("MUX Camera 4");
        break;
      default:
        break;
    }
  }
*/
