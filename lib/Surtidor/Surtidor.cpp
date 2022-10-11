#include "Surtidor.h"

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