/*
Programa: Trabalho Final
Objetivos: Programa para traduzir letras para Morse (e vice-versa)
Autor:
Data:07/11/2021
*/

// Inclusao de bibliotecas
#include "abp.h"
#include "avl.h"
#include <stdio.h>
#include <string.h>


#define TAM 5000


//imprime menu principal
int menuPrincipal();

// Preenche árvores com Setup
void preencheArvoreSetup(AVL *letrasCod, ABP *codLetras, char* espaco, char binario[]);

int main(){

   //Declaração de variáveis
   int loop=-1;//Mantem loop do comando while até que loop = 0.
   int caso=0;

   ABP *codLetras;
   AVL *letrasCod;

   codLetras = criaABP(); // Cria as arvores
   letrasCod = criaAVL();

   char binario[2];
   char espaco;

   preencheArvoreSetup(letrasCod, codLetras, &espaco, binario);

   while(loop != 0){

      caso = menuPrincipal();

      switch(caso){

         case 1:{

            char texto[TAM];

            fgets(texto, TAM, stdin);

            printf("\n\nINPUT: %sOUTPUT: ", texto);

            int i=0;

            for(int j=0;j<strlen(texto);j++){
               if(texto[j]>=97 && texto[j]<=122)
                  texto[j]=texto[j]-32;
            }

            while(texto[i]!='\n'){

               if(texto[i]==' ')
                  printf("%c ", espaco);
               else if(buscaInfoAVL(letrasCod, texto[i])!='\0')
                  printf("%s ",buscaInfoAVL(letrasCod, texto[i]));
               else
                  printf(" ");
               i++;
            }

         break;}

         case 2:{

            char texto[TAM];

            fgets(texto, TAM, stdin);

            texto[strlen(texto)-1]='\0';

            printf("\n\nINPUT: %s\nOUTPUT: ", texto);

            int i=0;
            int j=0;

            char *palavra = strtok(texto, " ");

            while( palavra != NULL ) {

               if(palavra[0]==espaco)
                  printf(" ");
               else if(buscaInfoABP(codLetras, palavra, binario)!='\0' && buscaInfoABP(codLetras, palavra, binario)!=' ')
                  printf("%c",buscaInfoABP(codLetras, palavra, binario));

               palavra = strtok(NULL, " ");
            }

         break;}

         case 3:{

            char buffer[256];
            FILE *entrada, *saida;

            entrada = fopen("_Entrada.txt", "r");
            saida = fopen("_Saida.txt", "w");

            if (entrada == NULL || saida == NULL){
               printf("ERRO: Arquivo nao localizado.\n");
            }else{
               while(fgets(buffer, 256, entrada) != NULL){
                  int i=0;
                  for(int j=0;j<strlen(buffer);j++){
                    if(buffer[j]>=97 && buffer[j]<=122)
                        buffer[j]=buffer[j]-32;
                  }
                  while(buffer[i]!='\0'){

                     if(buffer[i]==' ')
                        fprintf(saida, "%c ", espaco);
                     else if(buffer[i]=='\n')
                        fprintf(saida, "\n");
                     else if(buscaInfoAVL(letrasCod, buffer[i])!='\0')
                       fprintf(saida, "%s ", buscaInfoAVL(letrasCod, buffer[i]));
                     else
                        fprintf(saida, " ");
                     i++;
                  }
               }
            }

            fclose(entrada);
            fclose(saida);
         break;}

         case 4:{

            char buffer[100];
            FILE *entrada, *saida;

            entrada = fopen("_Entrada.txt", "r");
            saida = fopen("_Saida.txt", "w");

            if (entrada == NULL || saida == NULL){
               printf("ERRO: Arquivo nao localizado.\n");
            }else{
               while(fgets(buffer, 100, entrada) != NULL){

                  int tam = strlen(buffer);

                  printf("%s\n", buffer);

                  char *palavra = strtok(buffer, " ");

                  while( palavra != NULL ){

                     char* aux= palavra;

                     palavra = strtok(NULL, " ");

                     if(palavra==NULL && tam==99){
                        printf("->%s\n ", aux);
                        fseek(entrada, -strlen(aux)-1, SEEK_CUR);
                     }else{
                        if(aux[0]==espaco)
                           fprintf(saida, " ");
                        else if(buscaInfoABP(codLetras, aux, binario)!='\0' && buscaInfoABP(codLetras, aux, binario)!=' '){
                           fprintf(saida, "%c", buscaInfoABP(codLetras, aux, binario));
                        }
                     }
                  }
               }
            }
            fclose(entrada);
            fclose(saida);
         break;}

         case 5:{


         break;}

         case 6:{
            printf("          PROGRAMA ENCERRADO \n");
            loop=0;//Encera loop do comando while.
            destroiABP(codLetras);
            destroiAVL(letrasCod);

         break;}

         default:
            printf("\nSelecione um menu valido!\n");
      }
   }
   return 0;
}

//imprime menu principal
int menuPrincipal(){
   int sel;
   printf("\n\n          MENU PRINCIPAL \n\n");
   printf("1. Letras->Cod. \n");
   printf("2. Cod->Letras. \n");
   printf("3. Imprime arvore indentado (teste). \n");
   printf("4. VOID. \n");
   printf("5. VOID. \n\n");
   printf("6. Sair. \n");
   printf("Acessar:");

   scanf("%d", &sel);getchar();
   return sel;
}
