#ifndef _AVL_H_
#define _AVL_H_

typedef struct noArvAVL{
   int chave;
   char codigo[10];
   int alt;
   struct noArvAVL *esq;
   struct noArvAVL *dir;
} NoArvAVL;

typedef struct{
   struct noArvAVL *raiz;
} AVL;


// Funcao que cria uma AVL
AVL* criaAVL();

// Funcao que imprime uma AVL
void imprimeAVL(AVL *arv);

// Funcao que insere um elemento na AVL
void insereAVL(AVL *arv, int chave, char codigo[]);

// Funcao que busca uma informacao na AVL
char* buscaInfoAVL(AVL *arv, int chave);

// Funcao que destroi uma AVL
void destroiAVL(AVL *arv);

// Inicializa arvore binaria que traduz letras - morse
void inicializaLetrasCod(AVL *arv);

#endif
