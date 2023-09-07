# Documentación de codigo
---
**Metodo principal:**

    int main() {
       while (true) {
           cout << "Para dar enter oprimir *" << endl;
           menu();
           cout << endl << "===============================" << endl << endl;
       }
    }

Da estilo para la consola entre el llamado del metodo menu.

---
**Metodo del menu:**

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

* Muestra las opciones que tiene el programa.
* Se debe ingresar un valor entre 1 y 3.
* Se llama la función respectiva.

## Lectura del teclado
**Inicializacion de objetos con los que se leera el teclado matricial:**

    DigitalIn filas[] = {D2, D3, D4, D5};
    DigitalOut columnas[] = {D6, D7, D8};

Se usa un objeto de tipo entrada para las filas y para las columnas se usa un objeto de salida.

---
**Se declara la matriz teclado:**

    string teclado[][3] = {
       {"1", "2", "3"},
       {"4", "5", "6"},
       {"7", "8", "9"},
       {"*", "0", "#"}
    };

* Contiene los mismos valores que el teclado matricial
* Hacerlo en forma de matriz facilita el proceso de lectura del teclado
    
---
**Función para leer el teclado matricial:**

    string tecladoMatricial() {
       ThisThread::sleep_for(BLINKING_RATE);
   
       for (int i=0; i<3; i++) {
           columnas[i] = 0;
   
           for (int j=0; j<4; j++) {
               if (filas[j]==0) {
                   columnas[i] = 1;
                   return teclado[j][i];
               }
           }
   
           columnas[i] = 1;
       }
   
       return "";
    }

* Como se debe usar inputs para las filas y outputs para las columnas, se hace un for por cada columna asignando un valor de 0 para por asi decirlo "cerrar el circuito", luego se recorren las filas y en el caso de que la fila tambien tenga el valor de 0, se puede determinar cual es la posición del teclado que se esta presionando.
* Es necesario devolver la columna con el valor 1, ya que de lo contrario siempre se tomaria el valor de la primer columna.
* Contiene un tiempo de espera entre presionar las teclas de 300ms.

---
**Función complementaria para leer el teclado:**

    string escribir() {
       string tecla = "";
       string input = "";
   
       while (tecla!="*") {
           tecla = tecladoMatricial();
   
           if (tecla!="") {
               input += tecla;
               cout << input << endl;
           }
       }
   
       return input;
    }

* Se usa '*' como un aceptar (enter)
* El metodo va creando una cadena que se va llenando cada que se apreta una tecla, se verifica que no sea vacia y que no se halla dado enter, en el ultimo caso se devuelve el valor ingresado
* Tambien muestra en pantalla lo que se va escribiendo

## Opciones
### Opción 1
**Función de raices de un polinomio de grado 2 (Fórmula cuadrática):**

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

* Se le pide al usuario los coeficientes del polinomio (grado 2).
* se procede a calcular la raiz segun la formula del estudiante.
* En la primer asignación de R2 se halla el determinante del polinomio (R2 = CB*CB - 4*CA*CC).
* se usa la misma variable (R2) primero para el determinante y luego para la raiz para ahorrar memoria.
* Si es negativo significa que no tiene raices reales.
* En caso de ser positivo, se muestran las raices del polinomio.

### Opción 2
**Metodo de calificación:**

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

Se asigna una letra segun la calificación ingresada.
Se generan las restricciones de más restrictivo a menos restrictivo para reducir el
numero de restricciones que se deben hacer

### Opción 3
    void Leds() {
       cout << "Introduzca un codigo hexadecimal: " << endl;
   
       string color = escribir();
   
       colorLed(color);
    }

Le pide al usuario un valor hexadecimal y le envia dicho valor a la funcion colorLed().

---
**Metodo para cambiar el color del led:**

    void colorLed(string hexValue) {
       // Inicializando leds
       PwmOut ledR(LED1);
       PwmOut ledG(LED2);
       PwmOut ledB(LED3);
   
       // Determinar periodo de los leds
       ledR.period(0.01);
       ledG.period(0.01);
       ledB.period(0.01);
   
       // Calcular valor de color
       unsigned int colorValue = stoi(hexValue, nullptr, 16);
       unsigned char red, green, blue;
       red = (1-(float)((colorValue >> 16) & 0xFF) / 255.0f);
       green = (1-(float)((colorValue >> 8) & 0xFF) / 255.0f);
       blue = (1-(float)(colorValue & 0xFF) / 255.0f);
   
       // Asignar valor de color a los leds
       ledR = red;
       ledG = green;
       ledB = blue;
    }

* Recibe el color hexadecimal al cual cambiar el led.
* Crea los leds R-G-B por separado para luego asignarles el valor correspondiente.
