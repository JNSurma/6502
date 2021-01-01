#define DEBUG 0
#define OFFSET 0x8000
#define BUFFSIZE 32
#include "eeprom.h"
#include "ram.h"

void setup() {
    Wire.begin(); // initialise the connection
    Serial.begin(115200);
    unsigned int addr=0; //first address
    byte b = 0;
    byte buff[BUFFSIZE] = {0};
    ram_setup();

Serial.println("Reading EEPROM.");
unsigned long StartTimeEEPROM = millis();
//Read EEPROM to RAM
    while (addr < 0x8000){
      i2c_eeprom_read_buffer(0X50, addr, buff, BUFFSIZE );
      for (int i=0; i<BUFFSIZE; i++){

        if (DEBUG == 1){
          if ((int)buff[i]<0x10) {Serial.print("0");} //add leading zero
          if ((int)addr<0x10) {Serial.print("000");} //add leading zeros
          else if ((int)addr<0x100) {Serial.print("00");} //add leading zeros
          else if ((int)addr<0x1000) {Serial.print("0");} //add leading zero
          Serial.print(addr, HEX);
          Serial.print(":  ");
          Serial.print((byte)buff[i], HEX); //print content to serial port
          Serial.println(" ");
        }
        
        write_to_ram(addr, (byte)buff[i]);
        if (DEBUG == 1){serial_getch();}
        addr++; //increase address
      }
    Serial.println(" ");
    }
unsigned long EndTimeEEPROM = millis();
unsigned long ElapsedTimeEEPROM = EndTimeEEPROM - StartTimeEEPROM;
Serial.print(ElapsedTimeEEPROM / 1000);
Serial.println ("Seconds.");
    
Serial.println("Done.");
}

void loop() {

}


void serial_getch(){
  char c;
  while(Serial.available() == 0){}
  if (Serial.available() > 0) {
    // read the incoming byte:
    c = Serial.read();
  }
}
