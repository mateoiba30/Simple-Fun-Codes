#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
  #include<windows.h>
#endif
int buscar_letra(char palabra[],int longitud, char letra, char guiones[], int letras_acertadas){
    int i;
    for(i=0; i<longitud; i++){
        if(palabra[i]==letra){
            letras_acertadas++;
            guiones[i]=letra;
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
    for(i=0; i<longitud; i++)
        guiones[i]='_';
}
void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
int main()
{
    char palabra[256], letra, guiones[256];
    int longitud, letras_acertadas=0, vidas=6, aux;

    printf("Ingrese una palabra para jugar \n");
    scanf("%s", &palabra);
    longitud=strlen(palabra);

    limpiar_pantalla();

    inicializar_guiones(guiones,longitud);
    imprimir_guiones(guiones,longitud);
    printf("\n");
    getchar();
//hasta acá anda

    while( (vidas>0)&&(letras_acertadas<longitud) ){
        printf("Ingrese una letra: ");
        scanf("%c", &letra);//la palabra la lee bien

        aux=letras_acertadas;
        letras_acertadas=buscar_letra(palabra,longitud,letra,guiones, letras_acertadas);
        if(aux==letras_acertadas){
            vidas--;
            printf("letra erronea \n");
            getchar();
        }
        else{
            limpiar_pantalla();
            imprimir_guiones(guiones,longitud);
            printf("\n");
            getchar();
        }
    }
    return 0;
}
