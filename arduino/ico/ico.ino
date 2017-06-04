#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined(ARDUINO_ARCH_SAMD)
  #include <SoftwareSerial.h>
#endif
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_BNO055 bno;

uint16_t currtouched = 0;
int timeSinceSend = 0;
char touchMap[12] = {'e', 'a', 'f', 'd', 'b', 'c', 'i', 'h', 'j', 'g', 'l', 'k'}; //mapping order of inputs to labels on object.


void setup(void)
{
  while (!Serial);
  delay(500);
  Serial.begin(115200);
  
  Serial.println("MPR121 Begin");
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 broken.");
    while (1);
  }
  Serial.println("MPR121 End");
    
  Serial.println("BNO-055 Begin");
  Adafruit_BNO055 bno = Adafruit_BNO055(55);
  delay(1000);
  if(!bno.begin()) {
    Serial.println("BNO-055 broken.");
    while(1);
  }
  bno.setExtCrystalUse(true);  
  Serial.println("BNO-055 End");

  Serial.print(F("Initialising the BLE module: "));
  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Bluefruit not found."));
  }
  Serial.println( F("OK!") );
  if ( FACTORYRESET_ENABLE ) {
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  ble.echo(false);

  //Serial.println("Requesting Bluefruit info:");
  //ble.info();

  Serial.println(F("Setting device name to 'ico': "));
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=ico" )) ) {
    error(F("Could not set device name."));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) ) {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  } else {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Could not reset."));
  } 
}

void loop(void) {
  String touch = "";
  
  /*
  //IMU
  imu::Quaternion quat = bno.getQuat();
  
  Serial.print("qW: "); Serial.print(quat.w(), 4);
  Serial.print(" qX: "); Serial.print(quat.y(), 4);
  Serial.print(" qY: "); Serial.print(quat.x(), 4);
  Serial.print(" qZ: "); Serial.print(quat.z(), 4);
  Serial.println("");

  // Send abbreviated integer data out over BLE UART888888888883  
  ble.print("AT+BleKeyboard=[");
  ble.print(quat.w(), 4);
  ble.print(",");
  ble.print(quat.y(), 4);
  ble.print(",");
  ble.print(quat.x(), 4);
  ble.print(",");
  ble.print(quat.z(), 4);
  ble.println("] ");
  
  if( ble.waitForOK() ) {
    Serial.println( F("OK!") );
  }else {
    Serial.println( F("FAILED!") );
  }
  Serial.println("Quaternion Sent");
  */

  //Touch
  touch = "";
  currtouched = cap.touched();
  for (int i=0; i<12; i++) {
    if (currtouched & _BV(i)) {
      char temp = touchMap[i];//i+'a';
      touch += temp;
      Serial.print(i);
      Serial.print(" ");
      Serial.println(temp);
    }
  }
  touch+='o';  
  if(touch != ""){
    Serial.println(touch);
    ble.print("AT+BleKeyboard=");
    ble.println(touch);
    
    if( ble.waitForOK() ) {
      Serial.println( F("OK!") );
    }else {
      Serial.println( F("FAILED!") );
    }
  }
}

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

