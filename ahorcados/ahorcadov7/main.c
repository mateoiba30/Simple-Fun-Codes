#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
  #include<windows.h>
#endif
int verificar_palabra(char palabra[], int longitud){
    int fin=0, i=0;
    while( (i<longitud)&&(fin==0) ){
        if((letra_en_abecedario(palabra[i])) == 0)//si la letra no esta en el abecedario
            fin=1;
        i++;
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

    limpiar_pantalla();
    printf(" GANASTE !!!! \n \n");
    printf("    |  |  \n \n");
    printf("  \\      / \n");
    printf("   ------  \n");
}
int letra_repetida(char letra, char letras_dichas[], int diml_dichas){
    int fin=0, i=0;

    while( (i<=diml_dichas)&&(fin==0) ){
        if(letras_dichas[i]==letra){
            fin=1;
        }
        i++;
    }
    return fin;
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
    printf("------------------        (sin acentos, mayusculas ni la letra ''enie'') \n");

}
void actualizacion_de_pantalla(char guiones[], int longitud, int vidas, char letras_equivocadas[], int diml_equivocadas){

    limpiar_pantalla();
    titulo();
    printf("\n");
    imprimir_letras_equivocadas(letras_equivocadas, diml_equivocadas);
    printf("\n");
    imprimir_guiones(guiones,longitud);
    printf("\n \n");
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

int letra_en_abecedario(char letra[]){//como a veces le mando la posicion de un vector de caracteeres, tuve que hacer de cuenta que letra es nu vector
    char abedecario[26]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int i=0, fin=0;

    while( (fin==0)&&(i<25) ){
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
    char palabra[256], letra, guiones[256], letras_equivocadas[26], letras_dichas[26];
    int volver=1,longitud, letras_acertadas=0, vidas=6, aux, diml_equivocadas=-1, fin=0, diml_dichas=-1;//diml_equivocadas=-1 no significa ninguna posicion, es para decir que está vacío

    titulo();

    while(volver==1){
        printf("Ingrese una palabra para jugar \n");
        scanf("%s", &palabra);
        longitud=strlen(palabra);
        volver=verificar_palabra(palabra, longitud);//vale 1 si esta mal, y cero si esta bien
        if(volver==1)
            printf("Hay caracteres invalidos en la palabra \nal lado del titulo estan las condiciones \n");
    }

    inicializar_guiones(guiones,longitud);
    actualizacion_de_pantalla(guiones, longitud, vidas,letras_equivocadas, diml_equivocadas);
    getchar();

    while( (vidas>0)&&(letras_acertadas<longitud) ){
        fin=0;

        while(fin==0){
            printf("Ingrese una letra: ");
            scanf("%c", &letra);//la palabra la lee bien

            if(letra_en_abecedario(letra)==0){//si NO es una letra
                actualizacion_de_pantalla(guiones, longitud, vidas,letras_equivocadas, diml_equivocadas);
                printf("eso no es una letra bobo \n");
                getchar();
            }
            else{
                if(letra_repetida(letra,letras_dichas,diml_dichas)==1){
                    actualizacion_de_pantalla(guiones, longitud, vidas,letras_equivocadas, diml_equivocadas);
                    printf("letra ya dicha, prueve con otra \n");
                    getchar();
                }
                else{
                    diml_dichas++;
                    letras_dichas[diml_dichas]=letra;
                    fin=1;
                }
            }
        }

        aux=letras_acertadas;
        letras_acertadas=buscar_letra(palabra,longitud,letra,guiones, letras_acertadas);

        if(aux==letras_acertadas){
            vidas--;
            diml_equivocadas++;
            letras_equivocadas[diml_equivocadas]=letra;
            actualizacion_de_pantalla(guiones, longitud, vidas, letras_equivocadas, diml_equivocadas);
            printf("letra erronea \n");
            getchar();

        }
        else{
            actualizacion_de_pantalla(guiones, longitud, vidas, letras_equivocadas, diml_equivocadas);
            printf("muy bien! \n");
            getchar();
        }
    }

    if(vidas==0)
        perdiste(palabra);
    else
        ganaste();

    return 0;
}
