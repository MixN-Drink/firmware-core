#include "Surtidor.h"

bool calibrando = false;
uint64_t tiempoInicioCalibracion;
uint16_t mililitrosDelVaso = MILILITROS_DEL_VASO_DEFAULT;

bool surtir(uint8_t slot, uint8_t porcentaje){
    if(calibrando)return;
    
    if(porcentaje > 100 || slot > 7){
        return true;
    }

    int mililitrosALlenar = porcentaje * mililitrosDelVaso / 100;

    prepararMotor(slot, mililitrosALlenar * TIEMPO_POR_MILILITRO);
    
    return false;
}
void iniciarCalibracion(){
    if(calibrando)return;
    prepararMotor(SLOT_CALIBRACION, MILILITROS_DE_CALIBRACION * TIEMPO_POR_MILILITRO);
    calibrando = true;
    tiempoInicioCalibracion = millis();
}
void detenerCalibracion(){
    if(!calibrando)return;
    detenerMotor();
    calibrando = false;
    uint64_t tiempoCalibrando = millis() - tiempoInicioCalibracion;
    mililitrosDelVaso = TIEMPO_POR_MILILITRO * tiempoCalibrando;
}