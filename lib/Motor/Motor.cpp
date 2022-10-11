#include "Motor.h"

uint8_t motorPin[8] = {MOTOR_0_PIN,0,0,0,0,0,0,0};
uint8_t motorARotar = 0;
uint32_t tiempoFinal = 0;

void motoresInit(void){
    pinMode(MOTOR_0_PIN, OUTPUT);
}

void prepararMotor(uint8_t numeroDeMotor, uint32_t tiempo){
    motorARotar = numeroDeMotor;
    tiempoFinal = millis() + tiempo;
    digitalWrite(motorPin[motorARotar], 1);
    Serial.print("inicio: ");
    Serial.println(millis());
}

void procesarMotores(void){
    if(tiempoFinal==0){
        return;
    }
    if(millis()> tiempoFinal){
        digitalWrite(motorPin[motorARotar], 0);
        tiempoFinal = 0;
        Serial.print("final: ");
        Serial.print(millis());
        Serial.print("(");
        Serial.print(millis() - tiempoFinal);
        Serial.print(")");
        return;    
    }
    
}


