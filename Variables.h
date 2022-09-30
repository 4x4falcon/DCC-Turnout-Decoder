// CV structure

struct CV {
  byte cv1;     // primary address
  byte cv7;     // version number
  byte cv8;     // manufacture id = diy = 13
  byte cv29;    // different settings
  byte cv47;    // pulse length in micro seconds recomended 100uS if set to 255 ignored
};

CV cvStruct = { 3, 1, 13, 0, 100 };

// EEPROM storage address for primary address, version number and manufacturer

volatile int eepromDecoderCV1Address;               // decoder primary address
volatile int eepromDecoderCV7Address;               // version number
volatile int eepromDecoderCV8Address;               // manufacturer number = diy = 13
volatile int eepromDecoderCV29Address;              // 
volatile int eepromDecoderCV47Address;              // pulse length

byte DECODER_ADDRESS_1 = 0;
byte DECODER_ADDRESS_2 = 0;

//#define TURNOUT_DELAY 100   // should be less than 100uS for solenoids, longer for leds when testing.
byte TURNOUT_DELAY = 100;
