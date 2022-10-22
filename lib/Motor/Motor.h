#include <stdint.h>
#include <Arduino.h>

#define MOTOR_0_PIN 8
#define MOTOR_1_PIN 9
#define MOTOR_2_PIN 10
#define MOTOR_3_PIN 11

void motoresInit(void);
void prepararMotor(uint8_t numeroDeMotor, uint32_t tiempo);
void procesarMotores(void);
void detenerMotor(void);