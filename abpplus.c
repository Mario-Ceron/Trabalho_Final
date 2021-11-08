#include "abpplus.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Funcao que cria uma ABP
ABPPlus* criaABP(){
   ABPPlus * arv = (ABPPlus*)malloc(sizeof(ABPPlus));
   arv->raiz = NULL;
   return arv;
}

// Funcao auxiliar para imprimir uma ABP
void imprimeNodoABPIndentado(NoArvBinaria *raiz, int *contador){
   int i=0;
   if(raiz != NULL){
      while(i<*contador){
         printf(" ");
         i++;
      }
      (*contador)++;
      printf("%d\n", raiz->chave);
      imprimeNodoABPIndentado(raiz->esq, contador);
      imprimeNodoABPIndentado(raiz->dir, contador);
      (*contador)--;
   }
}

// Funcao que imprime uma ABP
void imprimeABPIndentado(ABPPlus *arv){
   int contador=0;
   printf("-----------------------------------------\n");
   imprimeNodoABPIndentado(arv->raiz, &contador);
   printf("-----------------------------------------\n");
}



// Funcao que auxiliar para inserir um elemento na ABP
NoArvBinaria* insereNodoABP(NoArvBinaria *raiz, int chave, char letra[]){
   if(raiz == NULL){
      raiz = (NoArvBinaria*)malloc(sizeof(NoArvBinaria));
      raiz->chave = chave;

       strcpy(raiz->letra, letra);

      raiz->esq = NULL;
      raiz->dir = NULL;
   }
   else if(chave < raiz->chave)
      raiz->esq = insereNodoABP(raiz->esq, chave, letra);
   else 
      raiz->dir = insereNodoABP(raiz->dir, chave, letra);
   return raiz;
}

// Funcao que insere um elemento na ABP
void insereABP(ABPPlus *arv, int chave, char letra[]){
   arv->raiz = insereNodoABP(arv->raiz, chave, letra);
}



// Funcao auxiliar para buscar uma informacao na ABP
char* buscaInfoNodoABP(NoArvBinaria *raiz, int chave){
   if(raiz==NULL){
      return '\0';}
   else if (raiz->chave > chave)
      return buscaInfoNodoABP(raiz->esq, chave);
   else if (raiz->chave < chave)
      return buscaInfoNodoABP(raiz->dir, chave);
   else
      return raiz->letra;
}

// Funcao que busca uma informacao na ABP
char* buscaInfoABP(ABPPlus *arv, int chave){

  return buscaInfoNodoABP(arv->raiz, chave);


}

// Funcao auxiliar para buscar uma informacao na ABP
char* buscaInfoNodo(NoArvBinaria *raiz, char* chave, int* i){
   if(raiz==NULL){
      return '\0';}
   else if (chave[*i]=='.'){
      (*i)++;
      return buscaInfoNodo(raiz->esq, chave, i);
   }else if (chave[*i]=='-'){
      (*i)++;
      return buscaInfoNodo(raiz->dir, chave, i);
   }else
      return raiz->letra;
}

// Funcao que busca uma informacao na ABP
char* buscaInfo(ABPPlus *arv, char* chave){

   int i=0;
   return buscaInfoNodo(arv->raiz, chave, &i);


}



// Funcao auxiliar para destroir uma ABP
void destroiNodoABP(NoArvBinaria *raiz){
   if(raiz != NULL){
      destroiNodoABP(raiz->esq);
      destroiNodoABP(raiz->dir);
      free(raiz);
   }
}

// Funcao que destroi uma ABP
void destroiABP(ABPPlus *arv){
   destroiNodoABP(arv->raiz);
   free(arv);
}
