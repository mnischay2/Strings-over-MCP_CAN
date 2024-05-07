#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg; 
MCP2515 mcp2515(10);                 // SPI CS Pin 10
 
void numbers_to_hex_and_ascii(int x[], int array_length, String hex_array[], String ascii_array[]) {
  for (int i = 0; i < array_length; i++) {
    // Convert number to hexadecimal string
    hex_array[i] = String(x[i], HEX);

    // Convert hexadecimal string to ASCII character
    int decimal_value = strtol(hex_array[i].c_str(), NULL, 16);
    ascii_array[i] = char(decimal_value);
  }
}

void setup(){
  pinMode(6,1);
  Serial.begin(115200);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();     
                    //Begins SPI communication

  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
  Serial.println("------- CAN Read ----------");
 
 }
 
 
void loop()
{ 
  //char hex_a[8][8];
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK){
    if(canMsg.can_id==0x0F6){
      int x[canMsg.can_dlc];
      for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
       x[i]=canMsg.data[i];

       Serial.print(x[i]); // Print the character
       Serial.print(" ");
      
	   }
//    Serial.println();     
  int array_length = sizeof(x) / sizeof(x[0]);
  String hex_array[array_length];
  String ascii_array[array_length];
  numbers_to_hex_and_ascii(x, array_length, hex_array, ascii_array);
  Serial.println();
  
  Serial.print("ASCII array: ");
  for (int i = 0; i < array_length; i++) {
    Serial.print(ascii_array[i]);
  }
  Serial.println();

}
}}