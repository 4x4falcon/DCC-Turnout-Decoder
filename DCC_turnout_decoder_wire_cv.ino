//DCC_turnout_decoder

// uncomment this for first run to initialize eeprom
//#define FIRSTRUN

//include the wire library
#include <Wire.h>

//inlcude the EEPROM library
#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "Variables.h"

#include "Eeprom.h"

//include CV's
#include "CV_list.h"


// Interrupt for DCC library
#define DCC_INTERRUPT 0

#define TURNOUT_DELAY 100   // should be less than 100uS for solenoids, longer for leds when testing.

//include the DCC_Decoder library
#include <DCC_Decoder.h>

//include my functions
#include "Functions.h"


// buffer to hold serial commands
String readString;




void setup() {

  getEepromAddresses();

#ifdef FIRSTRUN
  firstRun();
#endif
  
  getEepromValues();



  DECODER_ADDRESS_1 = cvStruct.cv1;
  DECODER_ADDRESS_2 = DECODER_ADDRESS_1 + 1;

  Serial.begin(115200); // Debug via terminal window at 9600 or 115200 
  Serial.print("Start decoders ");
  Serial.print(DECODER_ADDRESS_1);
  Serial.print(" and ");
  Serial.println(DECODER_ADDRESS_2);

  // Initialize the decoder:

  DCC.SetBasicAccessoryDecoderPacketHandler(BasicAccDecoderPacket_Handler, true); 
//  DCC.SetupDecoder(0x00, 0x00, DCC_INTERRUPT);
  DCC.SetupDecoder(cvStruct.cv8, cvStruct.cv7, DCC_INTERRUPT);

  Wire.begin();

  Wire.beginTransmission(0x20);
  byte error = Wire.endTransmission();

  if (error)
   {
    Serial.println("No MCP23017");
    while(1)
    {
    }
   }

    // set I/O pins to outputs
  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x20);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();





  // Set the turnouts straight
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x00);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x02);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x04);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_1, true, 0x06);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_2, true, 0x00);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_2, true, 0x02);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_2, true, 0x04);
  BasicAccDecoderPacket_Handler(DECODER_ADDRESS_2, true, 0x06);



}

void loop()
{
  DCC.loop();                     // process the dcc messages

    // see if there are serial commands

  while (Serial.available()) {
    char c = Serial.read();     //gets one byte from serial buffer
    readString += c;            //makes the string readString
    delay(2);                   //slow looping to allow buffer to fill with next character
  }

  // act on serial commands

  if (readString.length() >0) {
    doSerialCommand(readString);
    readString="";              //empty for next input
  } 

}
