#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfSpiDriver.h>
#include <MirfHardwareSpiDriver.h>

const char payload_length = 32;
byte data[payload_length];
int LedH = 2;
int LedM = 3;
int LedB = 4;

boolean terima() {
  if (!Mirf.isSending() && Mirf.dataReady()) {
    Mirf.getData(data);
    Serial.println((char*)data);
    digitalWrite(LedM, HIGH);
//    delay(500);
//    digitalWrite(LedM, LOW);
//    Serial.println("ok");
    //Serial.write((char*)data);
    return true;
    delay(1000);
    } else {
    //Serial.println((char*)data);
    Serial.println("Tidak Terhubung!!");
    return false;
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//   pinMode(LedH, OUTPUT);
//  pinMode(LedM, OUTPUT);
//  pinMode(LedB, OUTPUT);
//  digitalWrite(LedH, HIGH);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serve");
  Mirf.payload = payload_length;
  Mirf.channel = 123;
  Mirf.config();
}

void loop() {
  boolean statusNrf = terima();
//  delay(1800);
  delay(1700);
  
  //if (!statusNrf) {
    //Serial.println("NRF blm terdeksi");
  //}

}
