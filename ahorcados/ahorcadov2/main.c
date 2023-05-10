#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
  #include<windows.h>
#endif
int letra_en_abecedario(char letra){
    char abedecario[27]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int i=0, fin=0;

    while( (fin==0)&&(i<26) ){
        if(abedecario[i]==letra)
            fin=1;
        i++;
    }

    return fin;
}
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
//hacer muñequito
//mostrar letras equivocadas
//avisar si repito letras
//chequear si anda al ñ
    char palabra[256], letra, guiones[256], letras_equivocadas[27];
    int longitud, letras_acertadas=0, vidas=6, aux, diml_equivocadas, fin=0;

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
        fin=0;

        while(fin==0){
            printf("Ingrese una letra: ");
            scanf("%c", &letra);//la palabra la lee bien
            if(letra_en_abecedario(letra)==0){//si NO es una letra
                printf("eso no es una letra bobo \n");
                getchar();
            }
            else
                fin=1;
            printf("%d \n", letra_en_abecedario(letra));
        }

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
