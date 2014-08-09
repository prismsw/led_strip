#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

/**
 * Defines all pins that are used
 */

/**
 * The RGB pins for the LEDs respectively
 */
#define R_PIN 2
#define G_PIN 3
#define B_PIN 5

/**
 * The pin on which the heartbeat will be shown
 */
#define HEART_PIN 13

/**
 * The pin from which to read the IR signals
 */
#define IR_PIN A0

/**
 * The pin from which to read the knock signals
 */
#define KNOCK_PIN A15

/**
 * Ultrasonic sensor 1
 */
#define US1_TRIGGER_PIN A9
#define US1_ECHO_PIN A8

#endif
