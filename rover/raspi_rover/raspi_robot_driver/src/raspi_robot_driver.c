/*
Useful information for the GPIO functions was found here:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
The LED PWM controller information was inspired by:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html
https://github.com/espressif/esp-idf/blob/master/examples/peripherals/ledc/main/ledc_example_main.c
*/

#include "raspi_robot_driver.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "raspi_robot_adc.h"
#include "raspi_robot_leds.h"
#include "raspi_robot_motors.h"
#include "raspi_robot_sonar.h"
#include "raspi_robot_switches.h"

// GPIO pins available according to ESP datasheet.
// input: 0-19, 21-23, 25-27, 32-39
// output: 0-19, 21-23, 25-27, 32-33
// Only ADC1 can be used with Wi-FI enabled, pins 32-39.
//
// Available on board:
// On board: 2, 4, 5,12,13,14,15,18,19,21,22,23,25,26,27,32,33,34,35
// Used:     L    Se Ml Ml Ml    Se El Er L  L  Mr Mr Mr So So    B
//
// GPIO pins used.
// LEDS: 2,22,23 Note: 2 is for the on board blue LED.
// SWITCHES: 18,19
// MOTORS: 12,13,14,25,26,27
// SONAR:
// ENCODERS: 19, 21
// SERVOS: 4,5
// BATTERY: 15

// Switch GPIOs - NOT used but set ot valid values.
#define GPIO_SWITCH_SW1 38
#define GPIO_SWITCH_SW2 39
// Sonar GPIOs
#define GPIO_SONAR_OUT 32
#define GPIO_SONAR_IN 33
// Servo GPIOs
#define SERVO_X 5
#define SERVO_Y 18
// Encoder GPIOs
#define ENCODER_LEFT 19
#define ENCODER_RIGHT 21
// Battery voltage pin
#define BATTERY_VOLTAGE_PIN 35
#define BATTERY_VOLTAGE_RANGE_MV 11000

void raspi_robot_init(void) {
  adc_init(BATTERY_VOLTAGE_PIN, BATTERY_VOLTAGE_RANGE_MV);
  leds_init();
  switches_init(GPIO_SWITCH_SW1);
  switches_init(GPIO_SWITCH_SW2);
  motors_init();
  sonar_init(GPIO_SONAR_OUT, GPIO_SONAR_IN);
}

void raspi_robot_term(void) { sonar_term(); }

void raspi_robot_tick(void) {
  adc_tick();
  leds_tick();
  motors_tick();
  sonar_tick();
}

void raspi_robot_get_status(status_t *status) {
  // Switches.
  status->switch1 = switches_get(GPIO_SWITCH_SW1);
  status->switch2 = switches_get(GPIO_SWITCH_SW2);
  // Sonar.
  status->sonar_mm = sonar_get();
}

void raspi_robot_set_led(const raspi_robot_led_t led_value,
                         const raspi_robot_led_flash_t flash_rate) {
  leds_set(led_value, flash_rate);
}

void raspi_robot_motors_drive(int8_t speed_left, int8_t speed_right,
                              uint16_t ticks) {
  motors_drive(speed_left, speed_right, ticks);
}

uint32_t raspi_robot_get_battery_voltage() {
  return adc_battery_voltage();
}

int16_t raspi_robot_get_hall_effect() {
  // Just return the result.
  return adc_hall_effect_sensor();
}