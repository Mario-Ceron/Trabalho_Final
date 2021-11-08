/*
Programa: Trabalho Final
Objetivos: Programa para traduzir letras para Morse (e vice-versa)
Autor:
Data:07/11/2021
*/

// Inclusao de bibliotecas
#include <stdio.h>
#include <string.h>
#include "abpplus.h"

#define TAM 16


//imprime menu principal
int menuPrincipal();

int main(){

   //Declaração de variáveis
   int loop=-1;//Mantem loop do comando while até que loop = 0.
   int caso=0;

   ABPPlus *codLetras;
   ABPPlus *letrasCod;

   codLetras = criaABP(); // Cria as arvores
   letrasCod = criaABP();

   // inicializaCodLetras(codLetras); // Preenche arvores com as informações necessárias.
   inicializaLetrasCod(letrasCod);


   while(loop != 0){

      caso = menuPrincipal();

      switch(caso){

         case 1:{

            char texto[TAM];

            scanf("%s", texto);

            for(int i=0;i<strlen(texto);i++){
               if(buscaInfoABP(letrasCod, texto[i])!='\0')
                  printf(" %s",buscaInfoABP(letrasCod, texto[i]));
            }

         break;}

         case 2:{

         break;}

         case 3:{

            imprimeABPIndentado(letrasCod);

         break;}

         case 4:{

         // if(buscaInfoABP(letrasCod, 'A')!='\0')
         //    printf(" %s",buscaInfoABP(letrasCod, 'A'));

         break;}

         case 5:{


         break;}

         case 6:{
            printf("          PROGRAMA ENCERRADO \n");
            loop=0;//Encera loop do comando while.
            destroiABP(codLetras);
            destroiABP(letrasCod);

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
   printf("1. Traducao. \n");
   printf("2. VOID. \n");
   printf("3. Imprime arvore indentado. \n");
   printf("4. Busca. \n");
   printf("5. VOID. \n\n");
   printf("6. Sair. \n");
   printf("Acessar:");

   scanf("%d", &sel);getchar();
   return sel;
}
