#include "abp_modif.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Funcao que cria uma ABP
ABP* criaABP(){
   ABP * arv = (ABP*)malloc(sizeof(ABP));
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
      printf("%c\n", raiz->letra);
      imprimeNodoABPIndentado(raiz->esq, contador);
      imprimeNodoABPIndentado(raiz->dir, contador);
      (*contador)--;
   }
}

// Funcao que imprime uma ABP
void imprimeABPIndentado(ABP *arv){
   int contador=0;
   printf("-----------------------------------------\n");
   imprimeNodoABPIndentado(arv->raiz, &contador);
   printf("-----------------------------------------\n");
}




// Funcao que auxiliar para inserir um elemento na ABP
NoArvBinaria* insereNodoABP(NoArvBinaria *raiz, char codigo[], int *contador, char binario[]){
   if(raiz == NULL){
      raiz = (NoArvBinaria*)malloc(sizeof(NoArvBinaria));
      raiz->letra = '*';
      raiz->esq = NULL;
      raiz->dir = NULL;
   }

   if(codigo[*contador]==binario[0]){
      (*contador)++;
      raiz->esq = insereNodoABP(raiz->esq, codigo, contador, binario);
   }
   else if(codigo[*contador]==binario[1]){
      (*contador)++;
      raiz->dir = insereNodoABP(raiz->dir, codigo, contador, binario);
   }

   return raiz;
}


// Funcao que insere um elemento na ABP
void insereABP(ABP *arv, char letra, char codigo[], char binario[]){

   int i=0;
   int contador=0;
   int tam=strlen(codigo);

   arv->raiz = insereNodoABP(arv->raiz, codigo, &contador, binario);

   NoArvBinaria *tmp=arv->raiz;

   while(tmp!=NULL && i<tam){
      if(codigo[i]==binario[1]){
         tmp=tmp->dir;
         i++;
      }
      else if(codigo[i]==binario[0]){
         tmp=tmp->esq;
         i++;
      }
   }
   tmp->letra=letra;
}


// Funcao que busca uma informacao na ABP
char buscaInfoABP(ABP *arv, char codigo[], char binario[]){

   int i=0;
   int tam=strlen(codigo);

   NoArvBinaria *tmp=arv->raiz;

   while(tmp!=NULL && i<tam){
      if(codigo[i]==binario[1]){
         tmp=tmp->dir;
         i++;
      }
      else if(codigo[i]==binario[0]){
         tmp=tmp->esq;
         i++;
      }else if(codigo[i]!=binario[0] && codigo[i]!=binario[1])
         return '*';
   }

   if(tmp!=NULL)
      return tmp->letra;

   return '*';

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
void destroiABP(ABP *arv){
   destroiNodoABP(arv->raiz);
   free(arv);
}
