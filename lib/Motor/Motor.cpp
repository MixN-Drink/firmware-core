#include "Motor.h"

uint8_t motorPin[CANTIDAD_DE_MOTORES] = {MOTOR_0_PIN,MOTOR_1_PIN,MOTOR_2_PIN,MOTOR_3_PIN,255,255,255,255};
uint8_t motorARotar = 0;
uint64_t tiempoFinal = 0;
uint8_t colaMotores[COLA_LONGITUD] = {255, 255, 255, 255, 255, 255, 255};
uint16_t colaDeTiempos[COLA_LONGITUD] = {0, 0, 0, 0, 0, 0, 0};

void motoresInit(void){
    pinMode(MOTOR_0_PIN, OUTPUT);
    pinMode(MOTOR_1_PIN, OUTPUT);
    pinMode(MOTOR_2_PIN, OUTPUT);
    pinMode(MOTOR_3_PIN, OUTPUT);
}
void prepararMotor(uint8_t numeroDeMotor, uint16_t tiempo){
    if(tiempoFinal != 0){
        Serial.println("Ya hay una bomba funcionado. Poniendo en cola...");
        
        // Busca en la cola el primer hueco libre
        for(uint8_t lugar = 0; lugar<COLA_LONGITUD; lugar++){
            if(colaMotores[lugar] == HUECO_LIBRE) {
                colaMotores[lugar] = numeroDeMotor;
                colaDeTiempos[lugar] = tiempo;
                break;
            }
        }
        Serial.print("Cola: ");
        imprimirCola();

        return;
    }
    
    motorARotar = numeroDeMotor;
    tiempoFinal = millis() + (uint32_t)tiempo;

    Serial.print("Procesando motor: ");
    Serial.println(motorARotar);
    digitalWrite(motorPin[motorARotar], 1);
}
void procesarMotores(void){
    if(tiempoFinal==0){
        if(colaMotores[0] != HUECO_LIBRE){
            motorARotar = colaMotores[0];
            tiempoFinal = millis() + colaDeTiempos[0];
            
            sacarPrimerElementoDeLasColas();

            Serial.print("Siguientes: ");
            imprimirCola();

            Serial.print("Procesando motor: ");
            Serial.println(motorARotar);
            digitalWrite(motorPin[motorARotar], 1);            
        }
        return;      
    }
    if(millis() > tiempoFinal){
        detenerMotor();
        return;    
    }    
}
void detenerMotor(void){
    Serial.print("Deteniento motor: ");
    Serial.println(motorARotar);
    digitalWrite(motorPin[motorARotar], 0);
    tiempoFinal = 0;
}

void sacarPrimerElementoDeLasColas(){
    for(uint8_t i = 0; i < COLA_LONGITUD-1 ; i++) {
        colaMotores[i] = colaMotores[i+1];
        colaDeTiempos[i] = colaDeTiempos[i+1];
    }
    colaMotores[COLA_LONGITUD-1] = HUECO_LIBRE;
    colaDeTiempos[COLA_LONGITUD-1] = 0;
}

void imprimirCola(){
    for(uint8_t lugar = 0; lugar<COLA_LONGITUD; lugar++){
        if(colaMotores[lugar] == HUECO_LIBRE) break;

        Serial.print(colaMotores[lugar]);
        Serial.print("(");
        Serial.print(colaDeTiempos[lugar]);
        Serial.print("), ");
    }
    Serial.println();
}