#include "Surtidor.h"

bool calibrando = false;
uint32_t tiempoInicioCalibracion;
uint16_t mililitrosDelVaso = MILILITROS_DEL_VASO_DEFAULT;

bool surtir(uint8_t slot, uint8_t porcentaje){
    if(calibrando) return true;
    
    if(porcentaje > 100 || slot > 7){
        return true;
    }

    uint16_t mililitrosALlenar = (uint32_t)porcentaje * (uint32_t)mililitrosDelVaso / 100;

    prepararMotor(slot, mililitrosALlenar * TIEMPO_POR_MILILITRO);
    
    return false;
}
void iniciarCalibracion(){
    if(calibrando)return;
    prepararMotor(SLOT_CALIBRACION, TIEMPO_MAX_DE_CALIBRACION);
    tiempoInicioCalibracion = millis();
    calibrando = true;
}
void detenerCalibracion(){
    if(!calibrando)return;
    uint32_t tiempoCalibrando = millis() - tiempoInicioCalibracion;
    detenerMotor();
    calibrando = false;
    mililitrosDelVaso = tiempoCalibrando / TIEMPO_POR_MILILITRO;
}