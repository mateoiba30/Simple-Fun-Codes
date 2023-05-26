#include <stdio.h>
#include <stdlib.h>
#define MAX 16
#define ABC 26
#define CANT_MAX 14
#define CANT_MIN 4

typedef struct{
    char palabra[MAX];
    float dificultad;
} Palabra;

void cargarBinario(FILE*, FILE*);
int analizarPalabra(char[], float *, int*);
void imprimirArchivo(FILE *);

int main(){
    FILE *texto, *binario;
    binario=fopen("palabrasDificultad.txt", "wb+");
    if(binario==NULL){
        printf("Error en el archivo binario\n");
        return 1;
    }
    texto=fopen("palabras.txt", "r");
    if(texto==NULL){
        printf("Error en el archivo txt\n");
        return 1;
    }
    // char aux='ñ';
    // printf("%d", aux);

    // int problema=0;
    // printf("dificultad de mateo: %f", obtenerDificultad("mateo", &problema));
    // if(problema==1)
    //     printf("tiene enie");
    cargarBinario(binario, texto);
    imprimirArchivo(binario);

    fclose(binario);
    fclose(texto);
    return 0;
}

void cargarBinario(FILE*binario, FILE*texto){
    Palabra p;
    int cantLetras;

    while(fscanf(texto, "%s", p.palabra)!=EOF){//scanf no incluye el \n pero corta en espacios (no es un problema en las palabras)
        if(analizarPalabra(p.palabra, &p.dificultad, &cantLetras)==0 && cantLetras<= CANT_MAX && cantLetras >= CANT_MIN){
            // printf("%s\t%f\n", p.palabra, p.dificultad);
            fwrite(&p, sizeof(Palabra), 1, binario);
        }
    }
    fseek(binario, 0, SEEK_SET);
}

int analizarPalabra(char palabra[], float * dificultad, int *cantLetras){
    float frecuencias[ABC]={12.53, 1.42, 4.68, 5.86, 13.68, 0.69, 1.01, 0.7, 6.25, 0.44, 0.01, 4.97, 3.15, 
                            6.71, 8.68, 2.51, 0.88, 6.87, 7.98, 4.63, 3.93, 0.9, 0.02, 0.22, 0.9, 0.52};
    char cAct, aux='a', aux2=aux-'A';
    int i=0;
    (*dificultad)=0;

    cAct=palabra[i];
    while(cAct!='\0'){
        if(cAct>='A' && cAct <= 'Z')
            cAct=cAct+aux2;
        // printf("%d ", cAct);
        if(cAct==-61)// reconoce error ante ñ o Ñ
            return 1;
        (*dificultad)+=(frecuencias[cAct-aux]*frecuencias[cAct-aux]);//la dificultad es la sumatoria de frecuenfias al cuadrado de cada letra

        i++;
        cAct=palabra[i];
    }
    (*cantLetras)=i;

    return 0;
}

void imprimirArchivo(FILE *binario){
    Palabra p;
    while (fread(&p, sizeof(Palabra), 1, binario) !=0)
        printf("%s\t%f\n", p.palabra, p.dificultad);

    fseek(binario, 0, SEEK_SET);//no olvidar
}