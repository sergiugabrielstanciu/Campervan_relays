#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <RFM69.h>
#include <RFM69_ATC.h>
#include <RFM69_OTA.h>
#include <Adafruit_SleepyDog.h>
#include <avr/power.h>
#include <OneWire.h>

#ifdef F_CPU 
  #undef F_CPU 
  #define F_CPU = 8E6
#endif

#define LED_PIN        PC1 
#define LED_NUMBERS    1 
#define DELAYVAL       500 
#define RFM_SS         PE1
#define RFM_IRQ        PC4
#define RFM_DIO1       PC2
#define RFM_DIO2       PC3
#define BTN_SW_EN_0    PD2
#define BTN_SW_EN_1    PD1
#define BTN_SW_EN_2    PD0
#define BTN_SW_EN_3    PD5
#define BTN_SW_EN_4    PD6
#define BTN_SW_EN_5    PD7
#define BTN_SW_EN_6    PB1
#define BTN_SW_EN_7    PB2
#define DALLAS_PIN     PB0
#define VBAT_SENSE     A4
#define BUZZER         PD3
#define SEL0           PE0
#define SEL1           PD4
#define TEST_BUTT      PE2

#define NODEID       789
#define NETWORKID    100
#define GATEWAYID    1   //as a rule of thumb the gateway ID should always be 1
#define FREQUENCY    RF69_433MHZ
#define ENCRYPTKEY   "sampleEncryptKey" //exactly the same 16 characters/bytes on all nodes!
#define ENABLE_ATC   //comment out this line to disable AUTO TRANSMISSION CONTROL
#define ATC_RSSI     -90

#ifdef ENABLE_ATC
  RFM69_ATC radio(RFM_SS, RFM_IRQ, false, &SPI);
#else
  RFM69 radio(RFM_SS, RFM_IRQ, false, &SPI);
#endif

Adafruit_NeoPixel ws_led(LED_NUMBERS, LED_PIN, NEO_GRB + NEO_KHZ800);
OneWire           ds_sensor(DALLAS_PIN);

int radio_init()
{
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
    
  #ifdef ENABLE_ATC
    radio.enableAutoPower(ATC_RSSI);
  #endif
  return true;
}


void setup() 
{
  ws_led.begin();
  radio_init();
  pinMode(SEL0, INPUT_PULLUP);
  pinMode(SEL1, INPUT_PULLUP);
  tone(BUZZER, 1000, 100);
}

void loop() 
{

}