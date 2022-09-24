#include "Motor.h"

uint8_t motorPin[8] = {MOTOR_0_PIN_STEP,0,0,0,0,0,0,0};
uint8_t motorARotar = 0;
uint32_t pasosRestantes = 0;

void motoresInit(void){
    pinMode(MOTOR_0_PIN_STEP, OUTPUT);
    pinMode(MOTOR_0_PIN_DIR, OUTPUT);
    pinMode(MOTOR_0_PIN_ENABLE, OUTPUT);
    digitalWrite(MOTOR_0_PIN_ENABLE, 0);
}

void prepararMotor(uint8_t numeroDeMotor, uint32_t pasos){
    motorARotar = numeroDeMotor;
    pasosRestantes = pasos;
}

void procesarMotores(void){
    if(pasosRestantes == 0){
        return;
    }
    
    Serial.print("Motor: ");
    Serial.print(motorARotar);
    Serial.print(" Pasos restantes: ");
    Serial.println(pasosRestantes);

    rotarMotor();
}

void rotarMotor() {
    uint64_t time = millis();

    while(pasosRestantes>0 && millis() - time < MOTOR_LOOP_TIME) {
        digitalWrite(motorPin[motorARotar], 1);
        digitalWrite(motorPin[motorARotar], 0);

        delay(DELAY_ENTRE_PASOS);
        pasosRestantes--;
    }
}