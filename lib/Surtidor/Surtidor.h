#include <stdint.h>
#include "Motor.h"

#define TIEMPO_POR_MILILITRO            30
#define MILILITROS_DEL_VASO_DEFAULT     200
#define TIEMPO_MAX_DE_CALIBRACION       60000
#define SLOT_CALIBRACION                0

bool surtir(uint8_t slot, uint8_t porcentaje);
void iniciarCalibracion();
void detenerCalibracion();