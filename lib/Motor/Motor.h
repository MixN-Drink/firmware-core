#include <stdint.h>
#include <Arduino.h>

#define MOTOR_0_PIN 4

void motoresInit(void);
void prepararMotor(uint8_t numeroDeMotor, uint32_t tiempo);
void procesarMotores(void);
void detenerMotor(void);