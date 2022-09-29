/*
 * Eeprom.h
 */

/*
 * get eeprom addresses
 */

void getEepromAddresses()
 {

  eepromDecoderCV1Address = EEPROM.getAddress(sizeof(cvStruct.cv1));               // decoder primary address
  eepromDecoderCV7Address = EEPROM.getAddress(sizeof(cvStruct.cv7));               // version number
  eepromDecoderCV8Address = EEPROM.getAddress(sizeof(cvStruct.cv8));               // manufacturer number = diy = 13

 }

/*
 * read values stored in eeprom
 */

void getEepromValues ()
 {
  // title and version from eeprom
  cvStruct.cv1 = EEPROM.readByte(eepromDecoderCV1Address);
  cvStruct.cv7 = EEPROM.readByte(eepromDecoderCV7Address);
  cvStruct.cv8 = EEPROM.readByte(eepromDecoderCV8Address);
 }
