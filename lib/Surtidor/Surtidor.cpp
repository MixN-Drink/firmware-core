#include "Surtidor.h"

bool surtir(uint8_t slot, uint8_t porcentaje){
    if(porcentaje > 100 || slot > 8){
        return false;
    }

    int mililitrosALlenar = porcentaje * MILILITROS_DEL_VASO / 100;

    rotarMotor(slot, mililitrosALlenar * PASOS_POR_MILILITRO);

    return true;
}