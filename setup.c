#include "avl.h"
#include "abp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void preencheArvoreSetup(AVL *letrasCod, ABP *codLetras, char* espaco, char binario[]){

   FILE *setup;

   setup = fopen("setup.txt", "r");

   // Conta o número de linhas.

   int linhas=0;
   char aux1;

   if(setup==NULL){
      printf("Arquivo Setup nao localizado.");
   }else while((aux1=fgetc(setup))!=EOF){
      if(aux1=='\n')
         linhas++;
   }
   rewind(setup); // Volta vetor para começo do arquivo;
   linhas=linhas-3;
   // Cria vetor de acordo com número de linhas

   char *letra = (char*)malloc(linhas * sizeof(char));

   char **codigo = (char**)malloc(linhas * sizeof(char*));
   for (int i = 0; i < linhas; i++)
      codigo[i] = (char*)malloc(10* sizeof(char));

   char aux[20];

   if(setup!=NULL){
      fscanf(setup,"Simbolos binarios: %c e %c", &binario[0], &binario[1]);
      fscanf(setup," ",&aux);
      fscanf(setup,"Espaco = %c", espaco);
      fscanf(setup," ",&aux);

      for(int i=0; i<linhas;i++){
         fgets(aux, 20 , setup);
         letra[i]=aux[0];
         strncpy(codigo[i], aux + 4, strlen(aux) - 2);
         codigo[i][strlen(codigo[i])-1]='\0';//remove newline no final do string
      }
   }

   // Insere dados nas árvores criadas na Main

   for(int i=0; i<linhas; i++){

      insereABP(codLetras, letra[i], codigo[i], binario);
      insereAVL(letrasCod, letra[i], codigo[i]);

   }


   //Libera espaço alocado dinamicamente
   free(letra);

   for (int i = 0; i < (linhas-4); i++)
      free(codigo[i]);
   free(codigo);

   fclose(setup);
}


