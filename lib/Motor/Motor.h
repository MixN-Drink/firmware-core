#include <stdint.h>
#include <Arduino.h>

#define MOTOR_0_PIN 8
#define MOTOR_1_PIN 9
#define MOTOR_2_PIN 10
#define MOTOR_3_PIN 11

#define CANTIDAD_DE_MOTORES 8
#define HUECO_LIBRE 255
#define COLA_LONGITUD CANTIDAD_DE_MOTORES-1

void motoresInit(void);
void prepararMotor(uint8_t numeroDeMotor, uint16_t tiempo);
void procesarMotores(void);
void detenerMotor(void);
void sacarPrimerElementoDeLasColas();
void imprimirCola();