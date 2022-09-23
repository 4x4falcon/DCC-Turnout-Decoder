//Functions.h

void BasicAccDecoderPacket_Handler(int address, boolean activate, byte data) 
{ 
  Serial.print("    ");
  Serial.print(address);
  Serial.print(" - ");
  Serial.print(data);
  Serial.print(" - ");
  Serial.println(activate);

// Process the address of the turnout:

  if (address == DECODER_ADDRESS_1) {          // If the address in the packet == the address of decoder #1, then process

      Serial.print(data);
      Serial.print(" - ");
      Serial.println("On");

      Wire.beginTransmission(0x20);
      Wire.write(0x12);       // GPIOA
      Wire.write(1 << data);   // port A
      Wire.endTransmission();

      delay(TURNOUT_DELAY);          // delay for solenoid to switch
      Serial.print(data);
      Serial.print(" - ");
      Serial.println("Off");

      Wire.beginTransmission(0x20);
      Wire.write(0x12);        // GPIOA
      Wire.write(0x00);        // port A
      Wire.endTransmission();

  }  // if DECODDER_ADDRESS_1


  if (address == DECODER_ADDRESS_2) {       // If the address in the packet == the address of decoder #2, then process.

      Serial.print(data);
      Serial.print(" - ");
      Serial.println("On");

      Wire.beginTransmission(0x20);
      Wire.write(0x13);       // GPIOA
      Wire.write(1 << data);   // port B
      Wire.endTransmission();

      delay(TURNOUT_DELAY);          // delay for solenoid to switch
      Serial.print(data);
      Serial.print(" - ");
      Serial.println("Off");

      Wire.beginTransmission(0x20);
      Wire.write(0x13);        // GPIOA
      Wire.write(0x00);        // port A
      Wire.endTransmission();

  }  // if DECODER_ADDRESS_2
}

// end of handler




// do serial received commands

#include "StringSplitter.h"

void doSerialCommand(String readString)
 {
    byte p = 0;

    readString.trim();

    Serial.println(readString);  //so you can see the captured string

    if (readString == "<?>")
     {
      Serial.println(F("Help Text"));
      Serial.println(F("Close a turnout: <C address subaddress>\n"
                       "Throw a turnout: <T address subaddress>\n"
                       "Change decoder address: <W 1 address>\n"
                       "Show current CVs: <>"));
     }
    else
     {
      if (readString.startsWith("<>"))
       {
        Serial.println(F("CVs are:"));
        Serial.print(F("CV1 = "));
        Serial.println(EEPROM.readByte(eepromDecoderCV1Address));
        Serial.print(F("CV7 = "));
        Serial.println(EEPROM.readByte(eepromDecoderCV7Address));
        Serial.print(F("CV8 = "));
        Serial.println(EEPROM.readByte(eepromDecoderCV8Address));
       }
      else
       {
        if (readString.startsWith("<"))
         {
           int pos = 0;
           // this is where commands are completed

           // command to close turnout <C address subaddress>

          if (readString.startsWith("<C"))
           {
            StringSplitter *splitter = new StringSplitter(readString, ' ', 3);  // new StringSplitter(string_to_split, delimiter, limit)
            int itemCount = splitter->getItemCount();
//            Serial.println("Item count: " + String(itemCount));

            if ( itemCount == 3)
             {
              int addr = splitter->getItemAtIndex(1).toInt();
              int subaddress = splitter->getItemAtIndex(2).toInt();

              if ((subaddress < 0) || (subaddress > 3))
               {
                Serial.println(F("Invalid subaddress: must be 0 - 3"));
               }
              else
               {
                Serial.println("Close");
                Serial.print("Address = ");
                Serial.println(addr);
                Serial.print("Subaddress = ");
                Serial.println(subaddress * 2);
                BasicAccDecoderPacket_Handler(addr, true, subaddress * 2 );
               }

             }
            else
             {
              Serial.println(F("Invalid command: should be <C address subaddress>"));
             }
           }


           // command to throw turnout <T address subaddress>

          if (readString.startsWith("<T"))
           {
            StringSplitter *splitter = new StringSplitter(readString, ' ', 3);  // new StringSplitter(string_to_split, delimiter, limit)
            int itemCount = splitter->getItemCount();
//            Serial.println("Item count: " + String(itemCount));

            if ( itemCount == 3)
             {
              int addr = splitter->getItemAtIndex(1).toInt();
              int subaddress = splitter->getItemAtIndex(2).toInt();

              if ((subaddress < 0) || (subaddress > 3))
               {
                Serial.println(F("Invalid subaddress: must be 0 - 3"));
               }
              else
               {
                Serial.println("Throw");
                Serial.print("Address = ");
                Serial.println(addr);
                Serial.print("Subaddress = ");
                Serial.println((subaddress * 2) + 1);
                BasicAccDecoderPacket_Handler(addr, true, (subaddress * 2) + 1 );
               }

             }
            else
             {
              Serial.println(F("Invalid command: should be <T address subaddress>"));
             }
           }

          if (readString.startsWith("<W"))
           {
            StringSplitter *splitter = new StringSplitter(readString, ' ', 3);  // new StringSplitter(string_to_split, delimiter, limit)
            int itemCount = splitter->getItemCount();
//            Serial.println("Item count: " + String(itemCount));

            if ( itemCount == 3)
             {
              byte addr = splitter->getItemAtIndex(1).toInt();
              byte value = splitter->getItemAtIndex(2).toInt();

              if (addr == 1)
               {
                cvStruct.cv1 = value;
                DECODER_ADDRESS_1 = cvStruct.cv1;
                DECODER_ADDRESS_2 = DECODER_ADDRESS_1 + 1;

                EEPROM.writeByte(eepromDecoderCV1Address, cvStruct.cv1);
               }
              else
               {
                Serial.println(F("Invalid cv number: should be <W 1 addr>"));
               }
             }
            else
             {
              Serial.println(F("Invalid command: should be <T address subaddress>"));
             }
           }
         }
        else
         {
          Serial.println(F("ERROR: Unknown command"));
         }
       }
     }
 }

#ifdef FIRSTRUN
void firstRun() {
  EEPROM.writeByte(eepromDecoderCV1Address, cvStruct.cv1);
  EEPROM.writeByte(eepromDecoderCV7Address, cvStruct.cv7);
  EEPROM.writeByte(eepromDecoderCV8Address, cvStruct.cv8);
}
#endif
