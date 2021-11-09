#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Prototipos
int alturaNodoAVL(NoArvAVL *raiz);
int fatorBalanceamentoNodoAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoEsquerdaAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoDireitaAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoDireitaEsquerdaAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoEsquerdaDireitaAVL(NoArvAVL *raiz);

// Funcao que cria uma AVL
AVL* criaAVL(){
   AVL * arv = (AVL*)malloc(sizeof(AVL));
   arv->raiz = NULL;
   return arv;
}

// Funcao auxiliar para imprimir uma AVL
void imprimeNodoAVL(NoArvAVL *raiz){
   if(raiz != NULL){
      imprimeNodoAVL(raiz->esq);
      printf("%d ", raiz->chave);
      imprimeNodoAVL(raiz->dir);
   }   
}

// Funcao que imprime uma AVL
void imprimeAVL(AVL *arv){
   printf("-----------------------------------------\n");
   imprimeNodoAVL(arv->raiz);
   printf("-----------------------------------------\n");
}

// Funcao que retorna a altura de um nodo
int alturaNodoAVL(NoArvAVL *raiz){
   if(raiz->esq != NULL && raiz->dir != NULL){
      if(raiz->esq->alt < raiz->dir->alt)
         return raiz->dir->alt + 1;
      else
         return raiz->esq->alt + 1;
   }
   else if(raiz->esq != NULL)
      return raiz->esq->alt + 1;
   else if(raiz->dir != NULL)
      return raiz->dir->alt + 1;
   else
      return 1;
}

// Funcao que retorna o fator de balanceamento de um nodo
int fatorBalanceamentoNodoAVL(NoArvAVL *raiz){
   if(raiz == NULL)
      return 0;
   if(raiz->esq != NULL && raiz->dir != NULL)
      return raiz->esq->alt - raiz->dir->alt;
   else if(raiz->esq != NULL)
      return raiz->esq->alt;
   else if(raiz->dir != NULL)
      return -raiz->dir->alt;
}

// Funcao que insere um elemento na AVL
NoArvAVL* insereNodoAVL(NoArvAVL *raiz, int chave, char codigo[]){
   if(raiz == NULL){
      raiz = (NoArvAVL*)malloc(sizeof(NoArvAVL));
      raiz->chave = chave;
      strcpy(raiz->codigo, codigo);
      raiz->alt = 1;
      raiz->esq = NULL;
      raiz->dir = NULL;
      return raiz;
   }
   else if(chave < raiz->chave)
      raiz->esq = insereNodoAVL(raiz->esq, chave, codigo);
   else if(chave > raiz->chave)
      raiz->dir = insereNodoAVL(raiz->dir, chave, codigo);
   
   raiz->alt = alturaNodoAVL(raiz);
   int FB = fatorBalanceamentoNodoAVL(raiz);
   int FBEsq = fatorBalanceamentoNodoAVL(raiz->esq);
   int FBDir = fatorBalanceamentoNodoAVL(raiz->dir);
      
   if (FB == 2 && FBEsq == 1){
      raiz = rotacaoDireitaAVL(raiz);
   }

   else if (FB == -2 && FBDir == -1){
      raiz = rotacaoEsquerdaAVL(raiz);
   }

   else if (FB == -2 && FBDir == 1){
      raiz = rotacaoDireitaEsquerdaAVL(raiz);
   }
   
   else if (FB == 2 && FBEsq == -1){
      raiz = rotacaoEsquerdaDireitaAVL(raiz);
   }   
   
   return raiz;
}

// Funcao que insere um elemento na AVL
void insereAVL(AVL *arv, int chave, char codigo[]){
   arv->raiz = insereNodoAVL(arv->raiz, chave, codigo);
}


// Funcao auxiliar para buscar uma informacao na AVL
char* buscaInfoNodoAVL(NoArvAVL *raiz, int chave){
   if (raiz == NULL){
      char *infoAux = '\0';
      return infoAux;
   }else if (raiz->chave > chave)
      return buscaInfoNodoAVL(raiz->esq, chave);
   else if (raiz->chave < chave)
      return buscaInfoNodoAVL(raiz->dir, chave);
   else
      return raiz->codigo;
}

// Funcao que busca uma informacao na AVL
char* buscaInfoAVL(AVL *arv, int chave){
   return buscaInfoNodoAVL(arv->raiz, chave);
}

// Funcao auxiliar para destroir uma AVL
void destroiNodoAVL(NoArvAVL *raiz){
   if(raiz != NULL){
      destroiNodoAVL(raiz->esq);
      destroiNodoAVL(raiz->dir);
      free(raiz);
   }
}

// Funcao que destroi uma AVL
void destroiAVL(AVL *arv){
   destroiNodoAVL(arv->raiz);
   free(arv);
}

// Rotacoes
// Rotacao simples a esquerda
NoArvAVL * rotacaoEsquerdaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;
   
   tmp1 = raiz;
   tmp2 = tmp1->dir;
   
   tmp1->dir = tmp2->esq;
   tmp2->esq = tmp1;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);
   
   return tmp2;
}

// Rotacao simples a direita 
NoArvAVL * rotacaoDireitaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;
   
   tmp1 = raiz;
   tmp2 = tmp1->esq;
   
   tmp1->esq = tmp2->dir;
   tmp2->dir = tmp1;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);
   
   return tmp2;
}

// Rotacao esquerda-direita
NoArvAVL * rotacaoEsquerdaDireitaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;
   NoArvAVL *tmp3;
   
   tmp1 = raiz;
   tmp2 = tmp1->esq;
   tmp3 = tmp1->esq->dir;
   
   tmp1->esq = tmp3->dir;
   tmp2->dir = tmp3->esq;
   tmp3->dir = tmp1;
   tmp3->esq = tmp2;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);
   tmp3->alt = alturaNodoAVL(tmp3);
   
   return tmp3;
}

// Rotacao direita-esquerda
NoArvAVL * rotacaoDireitaEsquerdaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;
   NoArvAVL *tmp3;
   
   tmp1 = raiz;
   tmp2 = tmp1->dir;
   tmp3 = tmp1->dir->esq;
   
   tmp1->dir = tmp3->esq;
   tmp2->esq = tmp3->dir;
   tmp3->esq = tmp1;
   tmp3->dir = tmp2;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);
   tmp3->alt = alturaNodoAVL(tmp3);
   
   return tmp3;
}
