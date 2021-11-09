#ifndef _ABP_H_
#define _ABP_H_

typedef struct noArvBinaria{
   char letra;
   struct noArvBinaria *esq;
   struct noArvBinaria *dir;
} NoArvBinaria;

typedef struct{
   struct noArvBinaria *raiz;
} ABP;

// Funcao que cria uma ABP
ABP* criaABP();

// Funcao que imprime uma ABP de forma indentada
void imprimeABPIndentado(ABP *arv);

// Funcao que insere um elemento na ABP
void insereABP(ABP *arv, char letra, char codigo[], char binario[]);

// Funcao que busca uma informacao na ABP
char buscaInfoABP(ABP *arv, char codigo[], char binario[]);

// Funcao que destroi uma ABP
void destroiABP(ABP *arv);

// Inicializa arvore binaria que traduz letras - morse
void inicializaCodLetras(ABP *arv);

#endif
