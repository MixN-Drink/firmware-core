#include <stdint.h>
#include <Arduino.h>

#define DELAY_ENTRE_PASOS 2
#define MOTOR_LOOP_TIME 100

#define MOTOR_0_PIN_STEP 54
#define MOTOR_0_PIN_DIR 55
#define MOTOR_0_PIN_ENABLE 38

void motoresInit(void);
void prepararMotor(uint8_t numeroDeMotor, uint32_t pasos);
void procesarMotores(void);
void rotarMotor();
