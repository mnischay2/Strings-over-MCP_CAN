#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg1;

MCP2515 mcp2515(10);
 
void setup(){
  canMsg1.can_id  = 0x0F6;           //CAN id as 0x036
  canMsg1.can_dlc = 5;               //CAN data length as 8
  
  while (!Serial);
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  Serial.println("Example: Write to CAN");

 
  char x[] = "delhi"; // Example character, replace with your own variable
  char hex_string[8]; // Array to store hexadecimal string (including prefix)
  int i=0;
  Serial.println(x); // Print the hexadecimal string
  Serial.println("encoding"); // Print the hexadecimal string
  delay(1000);
  for (i=0;i<strlen(x);i++){
    canMsg1.data[i] = x[i]; // Store each character as is
    Serial.print("0x");
    Serial.print(x[i], HEX); // Print the hexadecimal representation of each character
    Serial.print(" ");
   }
  
  
//    canMsg1.data[0] = 0x0CB;  
 mcp2515.sendMessage(&canMsg1);     //Sends the CAN message
  } 
 
void loop(){
 }