/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <string>

// Blinking rate in milliseconds
#define BLINKING_RATE     300ms

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

string tecladoMatricial() {
    for (int i=0; i<3; i++) {
        columnas[i] = 0;

        for (int j=0; j<4; j++) {
            if (filas[j]==0) {
                while (filas[j]==0);
                columnas[i] = 1;
                return teclado[j][i];
            }
        }

        columnas[i] = 1;
    }

    return "";
}

string escribir() {
    string tecla = "";
    string input = "";

    while (tecla!="*") {
        tecla = tecladoMatricial();

        if (tecla!="") {
            if (tecla=="#") {
                if (input.size()!=0) input.pop_back();
                cout << endl << input;
            } else {
                input += tecla;
                cout << tecla;
            }
            cout.flush();
        }
    }
    
    cout << endl;

    return input;
}

void raices() {
    float CA,CB,CC;

    cout << "Dada la forma del polinomio AX^2 + BX + C" << endl;
    cout << "Introduzca el coeficiente A" << endl;
    CA = stoi(escribir());
    cout << "Introduzca el coeficiente B" << endl;
    CB = stoi(escribir());
    cout << "Introduzca el coeficiente C" << endl;
    CC = stoi(escribir());

    float R1, R2;
    R2 = CB*CB - 4*CA*CC;

    if (R2 < 0){
        cout << "El polinomio no tiene raices reales" << endl;
    } else {
        R1 = (-1*CB + sqrt(R2))/(2*CA);
        R2 = (-1*CB - sqrt(R2))/(2*CA);
        cout << "Raiz 1 = " << R1 << endl;
        cout << "Raiz 2 = " << R2 << endl;
    }
}

void calificacion() {
    cout << "Introduzca una nota del 0 al 10: " << endl;
    int nota = stoi(escribir());

    if (nota <= 3) {
        cout << "La nota es A" << endl;
    } else if (nota <= 4) {
        cout << "La nota es B" << endl;
    } else if (nota <= 5) {
        cout << "La nota es C" << endl;
    } else if (nota <= 7) {
        cout << "La nota es D" << endl;
    } else if (nota < 9) {
        cout << "La nota es E" << endl;
    } else if (nota <= 10) {
        cout << "La nota es F" << endl;
    } else {
        cout << "La nota no es válida" << endl;
    }
}

void Leds() {
    // Inicializando leds
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);

    // Determinar periodo de los leds
    ledR.period(0.01);
    ledG.period(0.01);
    ledB.period(0.01);
    
    // Obtener los colores
    cout << "Introduzca la intensidad del rojo (R): " << endl;
    float red = stoi(escribir());

    while (red>255) {
        cout << "Introduzca una intensidad dentro del rango (0-255): " << endl;
        red = stoi(escribir());
    }

    cout << "Introduzca la intensidad del verde (G): " << endl;
    float green = stoi(escribir());

    while (green>255) {
        cout << "Introduzca una intensidad dentro del rango (0-255): " << endl;
        green = stoi(escribir());
    }

    cout << "Introduzca la intensidad del azul (B): " << endl;
    float blue = stoi(escribir());

    while (blue>255) {
        cout << "Introduzca una intensidad dentro del rango (0-255): " << endl;
        blue = stoi(escribir());
    }

    // Calcular valor de color
    float scaledRed = red / 255;
    float scaledGreen = green / 255;
    float scaledBlue = blue / 255;

    // Asignar valor de color a los leds
    ledR = 1 - scaledRed;
    ledG = 1 - scaledGreen;
    ledB = 1 - scaledBlue;
}

void menu() {
    int opcion;
    cout << "Escoja una opcion para continuar:" << endl;
    cout << "1) Calculadora de raices del polinomio" << endl;
    cout << "2) Obtener nota con puntuacion" << endl;
    cout << "3) Encender LED con valor RGB" << endl;
    opcion = stoi(escribir());

    while (opcion < 1 || opcion >3){
        cout << "Ingrese una opcion valida" << endl;
        opcion = stoi(escribir());
    }

    if (opcion == 1){
        raices();
    } else if (opcion == 2){
        calificacion();
    } else if(opcion == 3){
        Leds();
    }
}

int main() {
    while (true) {
        cout << "-----------------------" << endl;
        cout << "Para dar enter oprimir *" << endl;
        cout << "Para eliminar oprimir #" << endl;
        cout << "-----------------------" << endl;
        menu();
        cout << endl << "===============================" << endl << endl;
    }
}
