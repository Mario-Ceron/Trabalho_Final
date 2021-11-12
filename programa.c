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


#define MAXCARACT 5000


//imprime menu principal
int menuPrincipal(char* nomeCodigo);

// Preenche árvores com Setup
void preencheArvoreSetup(AVL *letrasCod, ABP *codLetras, char* espaco, char* binario, char* nomeCodigo);

// Traduz Letras->Cod
void traduzLetrasCod(AVL *letrasCod, char* texto, char espaco);

// Traduz Cod->Letras
void traduzCodLetras(ABP *codLetras, char* texto, char espaco, char* binario);

// Traduz Letras->Cod a partir de um arquivo
void traduzLetrasCodArquivo(AVL *letrasCod, char espaco);

// Traduz Cod->Letras a partir de um arquivo
void traduzCodLetrasArquivo(ABP *codLetras, char espaco, char* binario);

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
   char nomeCodigo[50];

   preencheArvoreSetup(letrasCod, codLetras, &espaco, binario, nomeCodigo);

   while(loop != 0){

      caso = menuPrincipal(nomeCodigo);

      switch(caso){

         case 1:{
            char texto[MAXCARACT];

            fgets(texto, MAXCARACT, stdin);

            traduzLetrasCod(letrasCod, texto, espaco);
         break;}

         case 2:{
            char texto[MAXCARACT];

            fgets(texto, MAXCARACT, stdin);

            traduzCodLetras(codLetras, texto, espaco, binario);
         break;}

         case 3:{

            traduzLetrasCodArquivo(letrasCod, espaco);

         break;}

         case 4:{

            traduzCodLetrasArquivo(codLetras, espaco, binario);

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
int menuPrincipal(char* nomeCodigo){
   int sel;
   printf("\n\n          MENU PRINCIPAL \n\n");
   printf("%s\n", nomeCodigo);
   printf("Limite caracteres no Terminal: %d\n\n", MAXCARACT);
   printf("1. Letras->Cod. \n");
   printf("2. Cod->Letras. \n");
   printf("3. Letras->Cod (arquivo). \n");
   printf("4. Cod->Letras (arquivo). \n");
   printf("5. Salvar historico terminal. \n\n");
   printf("6. Sair. \n");
   printf("Acessar:");

   scanf("%d", &sel);getchar();
   return sel;
}


void traduzLetrasCod(AVL *letrasCod, char* texto, char espaco){

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
}

void traduzCodLetras(ABP *codLetras, char* texto, char espaco, char* binario){

   texto[strlen(texto)-1]='\0';

   printf("\n\nINPUT: %s\nOUTPUT: ", texto);

   char *palavra = strtok(texto, " ");

   while( palavra != NULL ) {

      if(palavra[0]==espaco)
         printf(" ");
      else if(buscaInfoABP(codLetras, palavra, binario)!='\0' && buscaInfoABP(codLetras, palavra, binario)!=' ')
         printf("%c",buscaInfoABP(codLetras, palavra, binario));

      palavra = strtok(NULL, " ");
   }
}

// Traduz Letras->Cod a partir de um arquivo
void traduzLetrasCodArquivo(AVL *letrasCod, char espaco){

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

}

// Traduz Cod->Letras a partir de um arquivo
void traduzCodLetrasArquivo(ABP *codLetras, char espaco, char* binario){
   char buffer[256];
   FILE *entrada, *saida;

   entrada = fopen("_Entrada.txt", "r");
   saida = fopen("_Saida.txt", "w");

   if (entrada == NULL || saida == NULL){
      printf("ERRO: Arquivo nao localizado.\n");
   }else{
      while(fgets(buffer, 256, entrada) != NULL){

         int tam = strlen(buffer);

         char *palavra = strtok(buffer, " ");

         while( palavra != NULL ){

            char* aux= palavra;

            palavra = strtok(NULL, " ");

            if(palavra==NULL && tam==255){
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
}