/*
 * Eeprom.h
 */

void getEepromAddresses()
 {

  eepromDecoderCV1Address = EEPROM.getAddress(sizeof(cvStruct.cv1));               // decoder primary address
  eepromDecoderCV7Address = EEPROM.getAddress(sizeof(cvStruct.cv7));               // version number
  eepromDecoderCV8Address = EEPROM.getAddress(sizeof(cvStruct.cv8));               // manufacturer number = diy = 13
  eepromDecoderCV29Address = EEPROM.getAddress(sizeof(cvStruct.cv29));               // 
  eepromDecoderCV47Address = EEPROM.getAddress(sizeof(cvStruct.cv47));               // 

 }

/*
 * read values stored in eeprom and calculate values based on these
 */

void getEepromValues ()
 {
  // title and version from eeprom
  cvStruct.cv1 = EEPROM.readByte(eepromDecoderCV1Address);
  cvStruct.cv7 = EEPROM.readByte(eepromDecoderCV7Address);
  cvStruct.cv8 = EEPROM.readByte(eepromDecoderCV8Address);
  cvStruct.cv29 = EEPROM.readByte(eepromDecoderCV29Address);
  cvStruct.cv47 = EEPROM.readByte(eepromDecoderCV47Address);
 }
