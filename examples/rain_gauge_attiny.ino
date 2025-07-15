#define __AVR_ATtiny84__

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#if defined(__AVR_ATtiny841__)
#define F_CPU 16000000                          // clock speed: 16MHz (external crystal)
#include "WireS.h"                              // I2C library for ATtiny841 (and other modern ATtinys)
#else
#define F_CPU 20000000                          // clock speed: 20MHz (external crystal)
#include "TinyWireS.h"                          // I2C library for ATtiny84A (and other older ATtinys)
#endif

const byte I2C_ADDR = 100;           // Meshtastic default
#define CLEANUP_FLOAT_TIPS 0.28f // mm per tip (DFRobot default)
const byte NUM_BYTES = 4;

volatile uint32_t tipCounter = 0;
// uint32_t tips;
volatile byte data[NUM_BYTES] = {0, 0, 0, 0};

static inline void initInterrupt(void)
{
	GIMSK |= (1 << PCIE);   // pin change interrupt enable
	PCMSK |= (1 << PCINT1); // pin change interrupt enabled for PCINT4
	sei();                  // enable interrupts
}

void setup() {
  TinyWireS.begin(I2C_ADDR);
  TinyWireS.onRequest(onI2CRequest);

  pinMode(PB1, INPUT_PULLUP);    
  initInterrupt();
}

ISR(PCINT0_vect){
  if (digitalRead(PB1) == LOW) {
    tipCounter++;
  }
}

void loop() {
  // noInterrupts();         // Begin atomic section
  // tips = tipCounter;      // 4-byte read
  // interrupts(); 
  // float rainfall = tips * CLEANUP_FLOAT_TIPS;
  // memcpy(data, &rainfall, sizeof(rainfall));
}

void onI2CRequest() {

  float rainfall = tipCounter * CLEANUP_FLOAT_TIPS;
  memcpy(data, &rainfall, sizeof(rainfall));

  for (byte i = 0; i < NUM_BYTES; i++) {
    TinyWireS.write(data[i]);
  }
  tipCounter = 0;
}

// void onI2CRequest() {
//   // noInterrupts();
//   for (byte i = 0; i < NUM_BYTES; i++) {
//     TinyWireS.write(data[i]);
//   }
//   tipCounter = 0;
//   // interrupts();

// }
