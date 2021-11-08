#ifndef _ABPPLUS_H_
#define _ABPPLUS_H_

typedef struct noArvBinaria{
   char letra[5];
   int chave;
   struct noArvBinaria *esq;
   struct noArvBinaria *dir;
} NoArvBinaria;

typedef struct{
   struct noArvBinaria *raiz;
} ABPPlus;

// Funcao que cria uma ABP
ABPPlus* criaABP();

// Funcao que imprime uma ABP de forma indentada
void imprimeABPIndentado(ABPPlus *arv);

// Funcao que insere um elemento na ABP
void insereABP(ABPPlus *arv, int chave, char letra[]);

// Funcao que busca uma informacao na ABP
char* buscaInfoABP(ABPPlus *arv, int chave);

// Funcao que destroi uma ABP
void destroiABP(ABPPlus *arv);

// Inicializa arvore binaria que traduz letras - morse
void inicializaLetrasCod(ABPPlus *arv);

#endif
