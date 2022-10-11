#include "Surtidor.h"

bool calibrando = false;
uint64_t tiempoInicioCalibracion;

bool surtir(uint8_t slot, uint8_t porcentaje){
    if(porcentaje > 100 || slot > 7){
        return true;
    }

    int mililitrosALlenar = porcentaje * MILILITROS_DEL_VASO / 100;

    Serial.print("Encolando motor ");
    Serial.print(slot);
    Serial.print("para surtir ");
    Serial.print(mililitrosALlenar);
    Serial.println("ml");

    prepararMotor(slot, mililitrosALlenar * TIEMPO_POR_MILILITRO);
    
    return false;
}


void iniciarCalibracion(){
    if(calibrando)return;
    prepararMotor(SLOT_CALIBRACION, MILILITROS_DE_CALIBRACION * TIEMPO_POR_MILILITRO);
    calibrando = true;
    tiempoInicioCalibracion = millis();
}