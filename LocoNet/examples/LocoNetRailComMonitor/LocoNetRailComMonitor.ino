#include <LocoNet.h>

// LocoNet RailCom Monitor
// Demonstrates the use of the:
//
// OPC_MULTI_SENSE call-back from a Uhlenbrock 68500 MARCo-Empfänger

lnMsg        *LnPacket;

void setup() {
  // First initialize the LocoNet interface
  LocoNet.init();

  // Configure the serial port for 57600 baud
  Serial.begin(57600);
  Serial.println("LocoNet Monitor");
}

void loop() {  
  // Check for any received LocoNet packets
  LnPacket = LocoNet.receive() ;
  if( LnPacket ) {
      // First print out the packet in HEX
    Serial.print("RX: ");
    uint8_t msgLen = getLnMsgSize(LnPacket); 
    for (uint8_t x = 0; x < msgLen; x++)
    {
      uint8_t val = LnPacket->data[x];
        // Print a leading 0 if less than 16 to make 2 HEX digits
      if(val < 16)
        Serial.print('0');
        
      Serial.print(val, HEX);
      Serial.print(' ');
    }
    
      // If this packet was not a Switch or Sensor Message then print a new line 
    if(!LocoNet.processSwitchSensorMessage(LnPacket)) {
      Serial.println();
    }
  }
}

  // This call-back function is called from LocoNet.processSwitchSensorMessage
  // for OPC_MULTI_SENSE 0xD0
void notifyMultiSense( uint16_t Address, uint8_t Type, uint8_t Zone ) {
  Serial.print("Railcom Address: ");
  Serial.print(Address, DEC);
  Serial.print(':');
  Serial.print(Type ? "present" : "absent");
  Serial.print(" in zone ");
  Serial.println(Zone);
}
