#include <stdio.h>
#include <stdlib.h>
#define MAX 16
#define CANT_ARCHIVOS 10

typedef struct{
    char palabra[MAX];
    float dificultad;
} Palabra;

struct nodo{//DEBO PONERLE NOMBRE AL INICIO
    Palabra dato;
    struct nodo* sig;
};

typedef struct nodo nodo;
typedef nodo* lista;

int crearBinarios(int, lista);
void longitudArchivos(int[], int);
void cargarLista(FILE *, lista *, int*);
void inicializarLista(lista*);
void insertarOrdenadoDescendente(lista*, Palabra);
void imprimirLista(lista);
void liberarLista(lista*);
void imprimirArchivo(FILE *);

int main(){
    FILE *binario;
    binario=fopen("palabrasDificultad.txt", "rb");//archivo ya cargado
    if(binario==NULL){
        printf("Error en el archivo binario\n");
        return 1;
    }

    lista l;
    int diml=0;
    inicializarLista(&l);
    cargarLista(binario, &l, &diml);
    // imprimirLista(l);
    if(crearBinarios(diml, l)==1)
        return 1;

    liberarLista(&l);
    fclose(binario);
    return 0;
}

int crearBinarios(int diml, lista l){
    int cantPalabras[CANT_ARCHIVOS]={0};
    longitudArchivos(cantPalabras, diml);
    FILE * vArchivos[CANT_ARCHIVOS];
    char nombresArchivos[CANT_ARCHIVOS][50]={"bloque1.txt", "bloque2.txt", "bloque3.txt", "bloque4.txt", "bloque5.txt", "bloque6.txt", "bloque7.txt", "bloque8.txt", "bloque9.txt", "bloque10.txt"};

    for(int i=0; i<CANT_ARCHIVOS; i++){
        vArchivos[i]=fopen(nombresArchivos[i], "wb+");
        if(vArchivos[i]==NULL){
            printf("error al abrir archivo %d\n", i+1);
            return 1;
        }
    }

    lista aux=l;
    for(int i=0; i<CANT_ARCHIVOS; i++){//se cuantos archivos tengo
        //  printf("ARCHIVO %d\n", i+1);

        for(int j=0; j<cantPalabras[i]; j++){//se cuantas palabras debo escribir
            fwrite(&aux->dato, sizeof(Palabra), 1, vArchivos[i]);
            // printf("%s\t%f\n", aux->dato.palabra, aux->dato.dificultad);

            aux=aux->sig;
        }

        fseek(vArchivos[i], 0, SEEK_SET);//no olvidar de hacer simepre que escribo
    }

    for(int i=0; i<CANT_ARCHIVOS; i++){
        printf("ARCHIVO %d\n", i+1);
        imprimirArchivo(vArchivos[i]);
    }
    for(int i=0; i<CANT_ARCHIVOS; i++)//no olvidar
        fclose(vArchivos[i]);
    return 0;
}

void longitudArchivos(int cantPalabras[], int diml){
    int largo, resto, i;

    largo=diml / CANT_ARCHIVOS;//sobran entre 0 y 9 palabras
    resto= diml % CANT_ARCHIVOS;

    for(i=0; i<CANT_ARCHIVOS; i++){
        if(resto>0){
            cantPalabras[i]=largo + 1;
            resto--;
        }
        else
            cantPalabras[i]=largo;
    }
}

void cargarLista(FILE *binario, lista *l, int* diml){
    Palabra p;

    while(fread(&p, sizeof(Palabra), 1, binario)!=0){
        insertarOrdenadoDescendente(l, p);
        (*diml)++;
    }
}

//podría haber hecho una busqueda binaria
void insertarOrdenadoDescendente( lista* l, Palabra dato){
    lista nue, ant, act;
    nue=(lista)malloc(sizeof(nodo));//reservo mem
    nue->dato=dato;

    act=(*l);
    ant=(*l);

    while(act!=NULL && act->dato.dificultad > dato.dificultad){
        ant=act;
        act=act->sig;
    }

    nue->sig=act;

    if((*l)==act)
        (*l)=nue;
    else
        ant->sig =nue;

}

void inicializarLista(lista* l){
    (*l)=NULL;
}

void imprimirLista(lista l){
    lista aux=l;
        while(aux!=NULL){
            printf("%s, %f\n",aux->dato.palabra, aux->dato.dificultad);
            aux=aux->sig;
    }

}

void liberarLista(lista* l){
    lista aux;
    while( (*l)){
        aux=(*l);
        (*l)=(*l)->sig;
        free(aux);
    }
}

void imprimirArchivo(FILE *binario){
    Palabra p;
    while (fread(&p, sizeof(Palabra), 1, binario) !=0)
        printf("%s\t%f\n", p.palabra, p.dificultad);

    fseek(binario, 0, SEEK_SET);//no olvidar
}