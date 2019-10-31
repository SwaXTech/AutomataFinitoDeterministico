#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define FILAS 7
#define COLUMNAS 12
#define REGEX "[0-9]\\.[01]?|[0-9]+F Centinela: %"
#define FDT '\0'
#define RECHAZAR 0
#define ACEPTAR 1
#define FIN '%'
#define MAX 1000

// 3.0%1.0%3F%123456F%4.%6456F%1.%9.0%asd%estoNoLoReconoce%1.0

const int AFD[FILAS][COLUMNAS] = {
        /*0*/   {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'F'},
        /*1*/   { 2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  2 ,  6 ,  6 }, // Estado inicial
        /*2*/   { 5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  3 ,  4 },
        /*3*/   { 4 ,  4 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 }, // Estado de aceptación
        /*4*/   { 6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 }, // Estado de aceptación
        /*5*/   { 5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  5 ,  6 ,  4 },
        /*6*/   { 6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 ,  6 }, // Estado de rechazo
};

const int EI = 1;           //Estado inicial
const int EA[3] = { 3, 4 }; //Estados de aceptación

char* obtenerCadena();
void bienvenida();
int reconocer(const char*);
int esEstadoDeAceptacion(int);
char* parteDeUnaCadena(const char*, int, int);

int main(){
    //Seteo de idioma al español. Permite impresión de caracteres con tilde.
    setlocale(LC_ALL, "spanish");

    bienvenida();
    short int continuar = 0;

   do{
       printf("Por favor ingrese una cadena para reconocer: ");
       char *cadena = obtenerCadena();
       int i = 0;
       int j = 1;
       int ultimoCentinela = 0;
       while (cadena[i] != FDT) {
           if (cadena[i] == FIN) {
               char *palabra = parteDeUnaCadena(cadena, ultimoCentinela, i - 1);
               int reconoce = reconocer(palabra);
               if (reconoce) printf("%d- %s\n", j++, palabra);
               ultimoCentinela = i + 1;
           }
           i++;
       }
       char *palabra = parteDeUnaCadena(cadena, ultimoCentinela, i - 1);
       int reconoce = reconocer(palabra);
       if (reconoce) printf("%d- %s\n", j++, palabra);
       printf("Desea ingresar otra cadena? (Y/N): ");
       char* respuesta = obtenerCadena();
       continuar = strcasecmp(respuesta, "y")? 0 : 1;

   }while(continuar);

    return 0;
}


void bienvenida() {
    printf("-----------------------Bienvenido al AUTÓMATA FINITO DETERMINÍSTICO-----------------------\n");
    printf("El siguiente autómata reconoce el lenguaje: %s\n", REGEX);
    printf("Por favor, el texto a reconocer no debe superar los %d caracteres\n", MAX);
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
            if(AFD[0][j] == FDT) return RECHAZAR;
            j++;
        }
        estadoActual = AFD[estadoActual][j];
        i++;
    }

    return esEstadoDeAceptacion(estadoActual);

}

int esEstadoDeAceptacion(int actual) {
    int i = 0;
    while(EA[i] != FDT){
        if(actual == EA[i]){
            return ACEPTAR;
        }
        i++;
    }
    return RECHAZAR;
}

char* parteDeUnaCadena(const char* cadena, int inicio, int fin){
    int i = inicio;
    int j = 0;
    char* nuevaCadena = (char*) malloc((fin - inicio + 1)* sizeof(char));

    while(i <= fin){
        nuevaCadena[j] = cadena[i];
        i++;
        j++;
    }
    nuevaCadena[j] = FDT;
    return nuevaCadena;
}



