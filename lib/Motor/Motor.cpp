#include "Motor.h"

uint8_t motorPin[8] = {MOTOR_0_PIN,MOTOR_1_PIN,MOTOR_2_PIN,MOTOR_3_PIN,255,255,255,255};
uint8_t motorARotar = 0;
uint32_t tiempoFinal = 0;

void motoresInit(void){
    pinMode(MOTOR_0_PIN, OUTPUT);
    pinMode(MOTOR_1_PIN, OUTPUT);
    pinMode(MOTOR_2_PIN, OUTPUT);
    pinMode(MOTOR_3_PIN, OUTPUT);
}
void prepararMotor(uint8_t numeroDeMotor, uint32_t tiempo){
    motorARotar = numeroDeMotor;
    tiempoFinal = millis() + tiempo;
    digitalWrite(motorPin[motorARotar], 1);
}
void procesarMotores(void){
    if(tiempoFinal==0){
        return;
    }
    if(millis() > tiempoFinal){
        detenerMotor();
        return;    
    }    
}
void detenerMotor(void){
    digitalWrite(motorPin[motorARotar], 0);
    tiempoFinal = 0;
}


