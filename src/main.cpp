#include <Arduino.h>
#include <stdint.h>
#include "Surtidor.h"
#include "Comander.h"

#define USB Serial
#define ESP12 Serial3

void checkIncomingCommand(void);

void setup() {
    USB.begin(115200);
    ESP12.begin(115200);
    motoresInit();
    pinMode(LED_BUILTIN, OUTPUT);
    USB.println("Sistema iniciado");
}

void loop() {
    checkIncomingCommand();
    procesarMotores();
}

void checkIncomingCommand(void){
    static uint8_t incoming[2] = {0,0};
    static uint8_t pos = 0;

    while(ESP12.available()){
        uint8_t incomingByte = ESP12.read();
        USB.print("Recibi el byte: 0x");
        USB.println(incomingByte, HEX);

        // Si pos es menor a 2 el mensaje esta incompleto
        if(pos<2){
            incoming[pos] = incomingByte;
            pos++;
        }

        // Cuando pos sea 2, se completó el mensaje
        if(pos == 2){
            pos = 0;

            if(!isStatus(incoming[0]) || !isData(incoming[1])){
                return;
            }

            uint8_t command = getCommand(incoming[0]);
            uint8_t subcommand = getSubCommand(incoming[0]); 
            uint8_t data = getData(incoming[1]);

            // Proceso el comando
            USB.print("Comando: ");
            USB.print(command, DEC);
            USB.print(" Subcomando: ");
            USB.print(subcommand, DEC);
            USB.print(" Data: ");
            USB.println(data, DEC);

            switch(command){
                case COMMAND_PUMP:{
                        bool err = surtir(subcommand, data);
                        if(err){
                            USB.println("Error al procesar procesar el comando surtir");
                        }
                    }
                    break;
                case COMMAND_LED:{
                        digitalWrite(LED_BUILTIN, data);
                    }
                    break;           
                case COMMAND_STOP_PUMP:{
                        detenerMotor();
                    }
                    break;
                case COMMAND_CALIBRATION:{
                    if(subcommand==0){
                        iniciarCalibracion();
                    }    
                    else{
                        detenerCalibracion();
                    }
                }
                break;
            }
        }
    }
}