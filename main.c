#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 9
#define COLUMNAS 13
#define MAX 100
#define REGEX "[0-9]\.[01]?|[0-9]+F Centinela: %"
#define FDT '\0'
#define RECHAZAR 0
#define ACEPTAR 1
#define FIN %

const int AFD[FILAS][COLUMNAS] = {
        /*0*/   {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '|', 'F'},
        /*1*/   { 2,  2,   2,   2,   2,   2,   2,   2,   2,   2,   8,   8,   8 }, // Estado inicial
        /*2*/   { 8,  8,   8,   8,   8,   8,   8,   8,   8,   8,   3,   8,   8 },
        /*3*/   { 4,  4,   2,   2,   2,   2,   2,   2,   2,   2,   2,   5,   2 },
        /*4*/   { 8,  8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   6,   8 },
        /*5*/   { 6,  6,   6,   6,   6,   6,   6,   6,   6,   6,   8,   8,   8 },
        /*6*/   { 6,  6,   6,   6,   6,   6,   6,   6,   6,   6,   8,   8,   7 },
        /*7*/   { 8,  8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8 }, // Estado de aceptación
        /*8*/   { 8,  8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8 }, // Estado de rechazo

};

const int EI = 1;        //Estado inicial
const int EA[2] = { 7 }; //Estados de aceptación

char* obtenerCadena();
void bienvenida();
int reconocer(const char*);
int esEstadoDeAceptacion(int);

int main(){

    bienvenida();
    char* cadena = obtenerCadena();
    int reconoce = reconocer(cadena);
    if(reconoce){
        printf("Acepta");
    } else {
        printf("Rechaza");
    }

    return 0;
}

void bienvenida() {
    printf("-----------------------Bienvenido al AUTÓMATA FINITO DETERMINÍSTICO-----------------------\n");
    printf("El siguiente autómata reconoce el lenguaje: %s\n", REGEX);
    printf("Por favor ingrese un texto para reconocer, su tamaño máximo debe ser: %d\n", MAX);
}

char* obtenerCadena(){
    char* cadena = (char*) malloc((MAX +1) * sizeof(char));
    scanf("%s", cadena);
    return cadena;
}

int reconocer(const char* palabra){
    int i = 0;
    int estadoActual = EI;
    while(palabra[i] != FDT){
        char caracter = palabra[i];
        int j = 0;
        while(AFD[0][j] != caracter){
            if(AFD[0][j] == '\0') return RECHAZAR;
            j++;
        }
        estadoActual = AFD[estadoActual][j];
        i++;
    }

    return esEstadoDeAceptacion(estadoActual);

}

int esEstadoDeAceptacion(int actual) {
    int i = 0;
    while(EA[i] != '\0'){
        if(actual == EA[i]){
            return ACEPTAR;
        }
        i++;
    }
    return RECHAZAR;
}


