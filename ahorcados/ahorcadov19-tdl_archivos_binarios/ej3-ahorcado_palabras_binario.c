#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#ifdef _WIN32
  #include<windows.h>
#endif

#define MAX 16
#define LETRAS 26
//si bien hay funciones que funcionan sin las libreias, es porque C la encuentra a la fuerza, lo mejor es ponerlas
#define CANT_ARCHIVOS 10

typedef struct{
    char palabra[MAX];
    float dificultad;
} Palabra;

//declaramos las funciones que vamos a usar
//esto es una buena practica para convertir datos del tipo erroneo en el necesitado y por otros temas
int palabra_random(int, char[]);
int verificar_palabra(char[], char[], int);
void perdiste(char[]);
void ganaste(void);
void imprimir_letras_equivocadas(char[], int);
void titulo(void);
void actualizacion_de_pantalla(char[], int, int, char[], int);
void imprimir_muneco(int);
int buscar_letra(char[], int, char, char[], int);
void imprimir_guiones(char[], int);
void inicializar_guiones(char[], int);
void limpiar_pantalla(void);
int generar_palabra(char[], char[], int*);
void adivinar_palabra(char[], char[], int *, int, char[26], int, char[]);
void fin_del_juego(char[], int);
int char_en_vector(char[], char, int);

int main()
//resumimos el main tanto como podamos
//modularizamos los mendsajes de salida ya que son muchos y repetitivos
{
    char abecedario[26]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char palabra[256], guiones[256], letras_equivocadas[26];//asignamos direccion f�sica a los vectores
    int estado, longitud, vidas=6, diml_equivocadas=-1;//diml_equivocadas=-1 no significa ninguna posicion, es para decir que est� vac�o

    titulo();
    estado=generar_palabra(abecedario, palabra, &longitud);
    if(estado==0){//vemos la palabra y su longitud, la cual mandamos la direccion de longitud para omodificarla con punteros
        inicializar_guiones(guiones,longitud);//creamos una cadena de guiones de igual tama�o que la palabra
        actualizacion_de_pantalla(guiones, longitud, vidas,letras_equivocadas, diml_equivocadas);
        getchar(); //son demasiado importantes los getchar() para poder leer la letra ingresada y no el enter
        adivinar_palabra(abecedario, palabra, &vidas, longitud, letras_equivocadas, diml_equivocadas, guiones);//solo modifico las vidas mientras trato de jugar
        fin_del_juego(palabra, vidas);//mensaje de fin
    }
    else{
        if(estado==1)
            printf("saliste del juego\n");
        else
            printf("problema al generar palabra random\n");

    }

    return 0;//el main devuleve cero por defecto para verificar que la ejecucion sea correcta
}

int palabra_random(int dificultad, char palabra[]){
    int posArchivo, nroPalabra, cantPalabras=0;
    FILE * vArchivos[CANT_ARCHIVOS];
    char nombresArchivos[CANT_ARCHIVOS][50]={"bloque1.txt", "bloque2.txt", "bloque3.txt", "bloque4.txt", "bloque5.txt", "bloque6.txt", "bloque7.txt", "bloque8.txt", "bloque9.txt", "bloque10.txt"};
    Palabra p;
    
    for(int i=0; i<CANT_ARCHIVOS; i++){
        vArchivos[i]=fopen(nombresArchivos[i], "rb");//si uso wb+ me reescribe el archivo
        if(vArchivos[i]==NULL){
            printf("error al abrir archivo %d\n", i+1);
            return 1;
        }
    }

    posArchivo=dificultad-1; //el archivo 10 está en la pos 9

    while(fread(&p, sizeof(Palabra), 1, vArchivos[posArchivo])!=0)//veo cant de palabras
        cantPalabras++;
    fseek(vArchivos[posArchivo], 0, SEEK_SET);
    printf("cant palabras: %d\n", cantPalabras);

    nroPalabra=rand()%cantPalabras+1;//elijo a una random

    for(int i=0; i<nroPalabra; i++)//la busco
        fread(&p, sizeof(Palabra), 1, vArchivos[posArchivo]);
    fseek(vArchivos[posArchivo], 0, SEEK_SET);

    strcpy(palabra, p.palabra);//la copio

    for(int i=0; i<CANT_ARCHIVOS; i++)//cierro archivo
        fclose(vArchivos[i]);

    return 0;
}
int verificar_palabra(char abecedario[], char palabra[], int longitud){
    int fin=0, i=0;
    while( (i<longitud)&&(fin==0) ){//recorro caracter por caracter
        if(char_en_vector(abecedario, palabra[i], LETRAS) == 0)//si la letra no esta en el abecedario, si fin es cero, la letra no est� en el abecedario
            fin=1;
        i++;//no olvidar de incrementar fuera del if, al final del while
    }
    return fin;
}
void perdiste(char palabra[]){

    limpiar_pantalla();
    printf(" PERDISTE \n la palabra era: %s \n \n", palabra);
    printf("    |  |  \n");
    printf("         \n");
    printf("   ------  \n");
    printf(" /        \\  \n");

    imprimir_muneco(0);
}
void ganaste(){

    printf("\n");
    printf(" GANASTE !!!! \n \n");
    printf("    |  |  \n \n");
    printf("  \\      / \n");
    printf("   ------  \n");

}
void imprimir_letras_equivocadas(char letras_equivocadas[], int diml_equivocadas){
    int i;
    printf("letras equivocadas: ");
    for(i=0; i<=diml_equivocadas; i++)
        printf(" %c ", letras_equivocadas[i]);
}
void titulo(){

    printf("------------------ \n");
    printf("|    AHORCADO    | \n");
    printf("------------------ \n");

}
void actualizacion_de_pantalla(char guiones[], int longitud, int vidas, char letras_equivocadas[], int diml_equivocadas){
    //para actualizar la pantalla borro todo y lo vuelvo a escribir en el mismo orden con los nuevos datos pasados
    //lo malo es que uso una librer�a compatible solo con windows
    limpiar_pantalla();
    titulo();
    printf("\n");
    imprimir_letras_equivocadas(letras_equivocadas, diml_equivocadas);
    printf("\n\n");
    imprimir_guiones(guiones,longitud);
    printf("\n \n");
    imprimir_muneco(vidas);
    printf("\n \n");
}
void imprimir_muneco(int vidas){

    switch(vidas){
        case 0:
            printf("  ------- \n");
            printf("  O     | \n");
            printf(" /|\\    | \n");
            printf("  |    _|_ \n");
            printf(" / \\  |   | \n");
            printf("----------- \n");
            break;
        case 1:
            printf("  ------- \n");
            printf("  O     | \n");
            printf(" /|\\    | \n");
            printf("  |    _|_ \n");
            printf(" /    |   | \n");
            printf("----------- \n");
            break;
        case 2:
            printf("  ------- \n");
            printf("  O     | \n");
            printf(" /|\\    | \n");
            printf("  |    _|_ \n");
            printf("      |   | \n");
            printf("----------- \n");
            break;
        case 3:
            printf("  ------- \n");
            printf("  O     | \n");
            printf(" /|     | \n");
            printf("  |    _|_ \n");
            printf("      |   | \n");
            printf("----------- \n");
            break;
        case 4:
            printf("  ------- \n");
            printf("  O     | \n");
            printf("  |     | \n");
            printf("  |    _|_ \n");
            printf("      |   | \n");
            printf("----------- \n");
            break;
        case 5:
            printf("  ------- \n");
            printf("  O     | \n");
            printf("        | \n");
            printf("       _|_ \n");
            printf("      |   | \n");
            printf("----------- \n");
            break;
        default:
            printf("  ------- \n");
            printf("        | \n");
            printf("        | \n");
            printf("       _|_ \n");
            printf("      |   | \n");
            printf("----------- \n");
            break;
    }
}
int buscar_letra(char palabra[],int longitud, char letra, char guiones[], int letras_acertadas){
    int i;
    for(i=0; i<longitud; i++){//i va desde cero hasta la longitud-1
        if(palabra[i]==letra){
            letras_acertadas++;//cuenta cuantas veces se encuentra la letra en la palabra
            guiones[i]=letra;//y modifica ese gui�n con la letra para mostrarlo en pantalla
        }
    }
    return letras_acertadas;
}
void imprimir_guiones(char guiones[], int longitud){
    int i;
    for(i=0; i<longitud; i++)  //  printf("%s", guiones); no me sirve porque quiero que los imprima separados
        printf("%c ", guiones[i]);
}
void inicializar_guiones(char guiones[], int longitud){
    int i;
    for(i=0; i<longitud; i++)//cargo los valors iniciales del vector
        guiones[i]='_';
}
void limpiar_pantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
int generar_palabra(char abecedario[], char palabra[], int *longitud){//solo modifico la longitud
    int dificultad, terminar=0, volver=1;
    char cant_jugadores;

    while(terminar==0){
        printf("%c", cant_jugadores);
        printf("Ingrese la cantidad de jugadores (x para salir): ");
        scanf("%c", &cant_jugadores);

        if(cant_jugadores=='1'){
            printf("ingrese dificultad entre 1 y 10 (10 para capos): \n");
            scanf("%d", &dificultad);

            if(palabra_random(dificultad, palabra)==1)//recibe un puntero a una palabra
                return 2;
            *longitud=strlen(palabra);//no olvidar de poner el * para operar con el valor y no la direccion
            terminar=1;
        }
        else{
            if(cant_jugadores>'0' && cant_jugadores!='x'){
                while(volver==1){
                    printf("\n \nIngrese una palabra para jugar \n");
                    scanf("%s", palabra);
                    *longitud=strlen(palabra);
                    volver=verificar_palabra(abecedario, palabra, *longitud);//vale 1 si esta mal, y cero si esta bien

                    if(volver==1)
                        printf("Hay caracteres invalidos en la palabra \(sin acentos, ni mayusculas ni la letra ''enie'')  \n");
                }
            terminar=1;
            }
            else{
                if(cant_jugadores=='x')
                    terminar=2;
                else
                    printf("No te hagas el canchero \n");
            }
        }
    }
    if (terminar==2)
        return 1;
    else
        return 0;
}
void adivinar_palabra(char abecedario[], char palabra[], int *vidas, int longitud, char letras_equivocadas[26], int diml_equivocadas, char guiones[]){
    //solo modifica las vidas
    char letra,letras_dichas[26];
    int aux, letras_acertadas=0, fin=0,diml_dichas=-1;//inicio las dimensiones l�gicas en -1 poara representar ninguna posicion

    while( (*vidas>0)&&(letras_acertadas<longitud) ){
        fin=0;

        while(fin==0){
            printf("Ingrese una letra: ");
            scanf("%c", &letra);//la palabra la lee bien

            if(char_en_vector(abecedario, letra, LETRAS)==0){//si NO es una letra
                actualizacion_de_pantalla(guiones, longitud, *vidas,letras_equivocadas, diml_equivocadas);
                printf("eso no es una letra bobo \n");
                getchar();
            }
            else{
                if(char_en_vector(letras_dichas, letra, diml_dichas)==1){
                    actualizacion_de_pantalla(guiones, longitud, *vidas,letras_equivocadas, diml_equivocadas);
                    printf("letra ya dicha, pruebe con otra \n");
                    getchar();
                }
                else{
                    diml_dichas++;
                    letras_dichas[diml_dichas]=letra;//en la siguiente posicion guardo la letra
                    fin=1;
                }
            }
        }

        aux=letras_acertadas;
        letras_acertadas=buscar_letra(palabra,longitud,letra,guiones, letras_acertadas);

        if(aux==letras_acertadas){
            *vidas=*vidas-1;
            diml_equivocadas++;
            letras_equivocadas[diml_equivocadas]=letra;
            actualizacion_de_pantalla(guiones, longitud, *vidas, letras_equivocadas, diml_equivocadas);
            printf("letra erronea \n");
            getchar();

        }
        else{
            actualizacion_de_pantalla(guiones, longitud, *vidas, letras_equivocadas, diml_equivocadas);
            printf("muy bien! \n");
            getchar();
        }
    }
}
void fin_del_juego(char palabra[], int vidas){
    if(vidas<1)
        perdiste(palabra);
    else
        ganaste();
}
int char_en_vector(char vector[], char letra, int diml){
    int i=0, fin=0;

    while((i<=diml)&&(fin==0)){//la diml ya representa la pos del vector, debe llegar a podeer igualarla
        if(vector[i]==letra)
            fin=1;
        i++;
    }
    return fin;
}
