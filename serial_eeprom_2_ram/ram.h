#define SData 2
#define SClock 3
#define SLatch 4
#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define WRITE_EN 5

void ram_setup(void){
  pinMode(SData, OUTPUT);
  pinMode(SClock, OUTPUT);
  pinMode(SLatch, OUTPUT);
}

void set_address(unsigned int address) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, address);
}

void write_to_ram(unsigned int address, byte data) {
  
  shiftOut(SData, SClock, LSBFIRST, data);
  digitalWrite(SLatch, LOW);
  digitalWrite(SLatch, HIGH);
  digitalWrite(SLatch, LOW);
  shiftOut(SData, SClock, LSBFIRST, address);
  digitalWrite(SLatch, LOW);
  digitalWrite(SLatch, HIGH);
  digitalWrite(SLatch, LOW);
  shiftOut(SData, SClock, LSBFIRST, (address >> 8));
  digitalWrite(SLatch, LOW);
  digitalWrite(SLatch, HIGH);
  digitalWrite(SLatch, LOW);

  if (DEBUG == 1){
  Serial.println("In Function: write_to_ram()");
  Serial.print(address,BIN);
  Serial.println(data, BIN);
  }

  digitalWrite(WRITE_EN, LOW);
  delayMicroseconds(1);
  digitalWrite(WRITE_EN, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
  delay(10);

  if (DEBUG == 1){
    Serial.println("End Function");
  }
}

// Cannot read from RAM to Arduino
//byte read_ram(int address) {
//  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
//    pinMode(pin, INPUT);
//  }
//  set_address(address);
//
//  byte data = 0;
//  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
//    data = (data << 1) + digitalRead(pin);
//  }
//  return data;
//}
//
//void printContents() {
//  for (int base = 0; base <= 255; base += 16) {
//    byte data[16];
//    for (int offset = 0; offset <= 15; offset += 1) {
//      data[offset] = read_ram(base + offset);
//    }
//
//    char buf[80];
//    sprintf(buf, "%03x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
//            base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
//            data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
//
//    Serial.println(buf);
//  }
//}
