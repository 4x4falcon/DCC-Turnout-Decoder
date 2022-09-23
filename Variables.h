// CV structure

struct CV {
  byte cv1;     // primary address
  byte cv7;     // version number
  byte cv8;     // manufacture id = diy = 13
};

CV cvStruct = { 3, 1, 13 };

// EEPROM storage address for primary address, version number and manufacturer

volatile int eepromDecoderCV1Address;               // decoder primary address
volatile int eepromDecoderCV7Address;               // version number
volatile int eepromDecoderCV8Address;               // manufacturer number = diy = 13

byte DECODER_ADDRESS_1 = 0;
byte DECODER_ADDRESS_2 = 0;
