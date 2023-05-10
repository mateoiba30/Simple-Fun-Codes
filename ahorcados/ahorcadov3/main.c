#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
  #include<windows.h>
#endif

void actualizacion_de_pantalla(char guiones[], int longitud, int vidas){
    limpiar_pantalla();
    imprimir_guiones(guiones,longitud);
    printf("\n");
    imprimir_muneco(vidas);
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
    //ver cuales getchar sacar
//hacer muñequito
//mostrar letras equivocadas
//avisar si repito letras
//chequear si anda al ñ
//muestre la palabra si perdiste
    char palabra[256], letra, guiones[256], letras_equivocadas[27];
    int longitud, letras_acertadas=0, vidas=6, aux, diml_equivocadas, fin=0;

    printf("Ingrese una palabra para jugar \n");
    scanf("%s", &palabra);
    longitud=strlen(palabra);
    inicializar_guiones(guiones,longitud);
    actualizacion_de_pantalla(guiones, longitud, vidas);
    getchar();
//hasta acá anda

    while( (vidas>0)&&(letras_acertadas<longitud) ){
        fin=0;

        while(fin==0){
            printf("Ingrese una letra: ");
            scanf("%c", &letra);//la palabra la lee bien

            if(letra_en_abecedario(letra)==0){//si NO es una letra
                actualizacion_de_pantalla(guiones, longitud, vidas);
                printf("eso no es una letra bobo \n");
                getchar();
            }
            else
                fin=1;
        }

        aux=letras_acertadas;
        letras_acertadas=buscar_letra(palabra,longitud,letra,guiones, letras_acertadas);

        if(aux==letras_acertadas){
            vidas--;
            actualizacion_de_pantalla(guiones, longitud, vidas);
            printf("letra erronea \n");
            getchar();
        }
        else{
            actualizacion_de_pantalla(guiones, longitud, vidas);
            printf("muy bien! \n");
            getchar();
        }
    }
    return 0;
}
