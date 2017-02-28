#define MUX0_0      PD_0
#define MUX0_1      PD_1
#define MUX0_2      PD_2
#define MUX0_SHDN   PD_3
#define MUX1_0      PD_7
#define MUX1_1      PD_6
#define MUX1_2      PD_5
#define MUX1_SHDN   PD_4

void setup()
{
  Serial.begin(9600);
  
  // Set pins to outputs
  pinMode(MUX0_0, OUTPUT);
  pinMode(MUX0_1, OUTPUT);
  pinMode(MUX0_2, OUTPUT);
  pinMode(MUX0_SHDN, OUTPUT);
  pinMode(MUX1_0, OUTPUT);
  pinMode(MUX1_1, OUTPUT);
  pinMode(MUX1_2, OUTPUT);
  pinMode(MUX1_SHDN, OUTPUT);
  pinMode(PF_4, OUTPUT);
  
  // Disable active low shutdowns
  digitalWrite(MUX0_SHDN, HIGH);
  digitalWrite(MUX1_SHDN, HIGH);
  
  // Initialize output_0 to camera_0 and output_1 to camera_1
  digitalWrite(MUX0_0, LOW);
  digitalWrite(MUX0_1, LOW);
  digitalWrite(MUX0_2, LOW);
  digitalWrite(MUX1_0, HIGH);
  digitalWrite(MUX1_1, LOW);
  digitalWrite(MUX1_2, LOW);
}

void loop()
{
  //test code to switch between camera_0 and camera_1 on output_0
  if (Serial.available())
  {
    char c = Serial.read();
      if (c == '0')
      {
        digitalWrite(MUX0_0, LOW);
        digitalWrite(PF_4, HIGH);
        Serial.println("Cam 0");
      }
      else if (c == '1')
      {
        digitalWrite(MUX0_0, HIGH);
        digitalWrite(PF_4, LOW);
        Serial.println("Cam 1");
      }
  }
}
