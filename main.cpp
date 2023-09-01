/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <string>

// Blinking rate in milliseconds
#define BLINKING_RATE     200ms

// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);

// Objeto pa leer la matriz numerica
DigitalIn filas[] = {D2, D3, D4, D5};
DigitalOut columnas[] = {D6, D7, D8};

using namespace std;

string teclado[][3] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"},
    {"*", "0", "#"}
};

bool bandera = true;

string escribir() {
    for (int i=0; i<3; i++) {
        columnas[i] = 0;

        for (int j=0; j<4; j++) {
            if (bandera && filas[j]==0) {
                columnas[i] = 1;
                bandera = false;
                return teclado[j][i];
            }
        }

        columnas[i] = 1;
    }

    bandera = true;

    return "";
}

int main()
{
    string tecla = "";
    while (true) {
        tecla = escribir();
        if (tecla!="") cout << tecla << endl;
    }
}
