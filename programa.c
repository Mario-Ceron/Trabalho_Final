/*
Programa: Trabalho Final
Objetivos: Programa para traduzir letras para Morse (e vice-versa)
Autor:
Data:07/11/2021
*/

// Inclusao de bibliotecas
#include "abp_modif.h"
#include "avl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Limpa tela
#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif


#define MAXCARACT 5000

// Imprime menu principal
int menuPrincipal(char* nomeCodigo);

// Busca informações iniciais no arquivo __Setup. Com retorno "multiplo"
int informacoesIniciaisSetup(char* nomeCodigo, char* espaco, char* binario, char* minuscula, int* linhas);

// Preenche árvores com Setup
void preencheArvoresSetup(AVL *letrasCod, ABP *codLetras, int linhas, char* binario);

// Traduz Letras->Cod
void traduzLetrasCod(AVL *letrasCod, char* texto, char espaco, char minuscula);

// Traduz Cod->Letras
void traduzCodLetras(ABP *codLetras, char* texto, char espaco, char* binario);

// Traduz Letras->Cod a partir de um arquivo
void traduzLetrasCodArquivo(AVL *letrasCod, char espaco, char minuscula);

// Traduz Cod->Letras a partir de um arquivo
void traduzCodLetrasArquivo(ABP *codLetras, char espaco, char* binario);

// Tranforma letras minusculas em maiusculas
char* minuscMaiusc(char* texto);

int main(){

   //Declaração de variáveis
   int loop=-1;//Mantem loop do While.
   int caso=0;

   char binario[2];     // Armazena simbolos utilizados para o codigo
   char espaco;         // Armazena simbolo utilizado para o caractere espaço
   char nomeCodigo[50];
   char minuscula;      // Armazena se precisamos transformar letras minusculas em maiusculas
   int linhas;          // Quantidade de linha no arquivo setup

   // Declara e cria arvores binarias
   ABP *codLetras;
   AVL *letrasCod;

   codLetras = criaABP();
   letrasCod = criaAVL();


   // Caso arquivo __Setup nao exista, o programa é encerrado
   if(informacoesIniciaisSetup(nomeCodigo, &espaco, binario, &minuscula, &linhas)==0)
      return 0;

   preencheArvoresSetup(letrasCod, codLetras, linhas, binario);

   while(loop != 0){

      caso = menuPrincipal(nomeCodigo);

      switch(caso){

         case 1:{
            CLEAR_SCREEN;
            printf("Verifique se as alteracoes desejadas foram salvas no arquivo __Setup.txt.\n\n");

            int caso1=0;

            while(caso1!=2){
               printf("\n1. Prosseguir.\n");
               printf("2. Retornar ao menu.\n\n->");
               scanf("%d", &caso1);

               if(caso1==1){
                  // Destroi arvores existentes
                  destroiABP(codLetras);
                  destroiAVL(letrasCod);

                  // // Cria novas arvores
                  codLetras = criaABP();
                  letrasCod = criaAVL();

                  // // Insere novas informacoes
                  if(informacoesIniciaisSetup(nomeCodigo, &espaco, binario, &minuscula, &linhas)==0)
                     return 0;

                  preencheArvoresSetup(letrasCod, codLetras, linhas, binario);
                  printf("\nSetup atualizado!\n")
               }
            }
         break;}

         case 2:{
            CLEAR_SCREEN;
            printf("----------------Letras -> Codigo----------------\n\nPressione enter para retornar ao menu principal.");
            char texto1[MAXCARACT]="";

            while(texto1[0]!='\n'){
               printf("\n\nINPUT :");
               fgets(texto1, MAXCARACT, stdin);
               traduzLetrasCod(letrasCod, texto1, espaco, minuscula);
            }
         break;}

         case 3:{
            CLEAR_SCREEN;
            printf("----------------Codigo -> Letras----------------\n\nPressione enter para retornar ao menu principal.");
            char texto1[MAXCARACT];
            char aux='\0';

            while(aux!='\n'){
               printf("\n\nINPUT :");
               fgets(texto1, MAXCARACT, stdin);
               aux=texto1[0];
               traduzCodLetras(codLetras, texto1, espaco, binario);
            }
         break;}

         case 4:{

            CLEAR_SCREEN;
            printf("-----------Letras -> Codigo (arquivo)-----------\n\n");
            printf("Verifique se as informacoes desejadas foram inseridas (e salvas) no arquivo _Entrada.\n");

            int caso1=0;

            while(caso1!=2){
               printf("\n1. Prosseguir.\n");
               printf("2. Retornar ao menu.\n\n->");
               scanf("%d", &caso1);

               if(caso1==1){
                  traduzLetrasCodArquivo(letrasCod, espaco, minuscula);
                  printf("\nTraducao disponivel no arquivo _Saida.txt\n");
               }
            }
         break;}

         case 5:{

            CLEAR_SCREEN;
            printf("-----------Codigo -> Letras (arquivo)-----------\n\n");
            printf("Verifique se as informacoes desejadas foram inseridas (e salvas) no arquivo _Entrada.\n");

            int caso1=0;

            while(caso1!=2){
               printf("\n1. Prosseguir.\n");
               printf("2. Retornar ao menu.\n\n->");
               scanf("%d", &caso1);

               if(caso1==1){
                  traduzCodLetrasArquivo(codLetras, espaco, binario);
                  printf("\nTraducao disponivel no arquivo _Saida.txt\n");
               }
            }
         break;}

         case 6:{
            printf("          PROGRAMA ENCERRADO \n");
            loop=0;//Encera loop do comando while.

            // Destroi arvores
            destroiABP(codLetras);
            destroiAVL(letrasCod);

         break;}

         case 111:{ // DEBUG

         imprimeAVLIndentado(letrasCod);
         imprimeABPIndentado(codLetras);

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
   CLEAR_SCREEN;
   printf("\n\n          MENU PRINCIPAL \n\n");
   printf("%s\n", nomeCodigo);
   printf("Limite caracteres no Terminal: %d\n\n", MAXCARACT);
   printf("1. Setup. \n");
   printf("2. Letras->Cod. \n");
   printf("3. Cod->Letras. \n");
   printf("4. Letras->Cod (arquivo). \n");
   printf("5. Cod->Letras (arquivo). \n\n");
   printf("6. Sair. \n");
   printf("Acessar:");

   scanf("%d", &sel);getchar();
   return sel;
}

// Busca informações iniciais no arquivo __Setup
int informacoesIniciaisSetup(char* nomeCodigo, char* espaco, char* binario, char* minuscula, int* linhas){
   FILE *setup;

   setup = fopen("__setup.txt", "r");

   // Caso arquivo não exista, retorna 0 e para execução da função
   if(setup==NULL){
      printf("ERRO: Arquivo __Setup nao localizado.\n\n");
      return 0;
   }

   // Conta o número de linhas no arquivo
   char aux1;
   (*linhas)=0;
   while((aux1=fgetc(setup))!=EOF){
      if(aux1=='\n')
         (*linhas)++;
   }
   rewind(setup);    // Volta ponteiro para o começo do arquivo


   // Armazena informações iniciais
   char aux[51];

   fgets(nomeCodigo, 50, setup); //Armazena linha do arquivo
   fseek(setup, 2, SEEK_CUR);    // Avança ponteiro duas posições

   fgets(aux, 50, setup);
   binario[0]=aux[19];
   binario[1]=aux[23];
   fseek(setup, 2, SEEK_CUR);

   fgets(aux, 50, setup);
   *espaco = aux[9];
   fseek(setup, 2, SEEK_CUR);

   fgets(aux, 50, setup);
   *minuscula=aux[29];


   // Fecha arquivo aberto
   fclose(setup);

   return 1;
}

// Preenche árvores com Setup
void preencheArvoresSetup(AVL *letrasCod, ABP *codLetras, int linhas, char* binario){
   FILE *setup;

   setup = fopen("__setup.txt", "r");

   linhas=linhas-9; //Desconta linhas que não sao tradução

   char aux[50];
   char codigo[10];
   // Avança ponteiro até primeira linha de tradução
   for(int i=0; i<9; i++)
      fgets(aux, 50, setup);

   // Preenche arvores
   for(int i=0; i<linhas;i++){
      fgets(aux, 20 , setup);
      strncpy(codigo, aux + 4, strlen(aux) - 3);
      codigo[strlen(codigo)-1]='\0';//remove newline no final do string


      insereABP(codLetras, aux[0], codigo, binario);
      insereAVL(letrasCod, aux[0], codigo);
   }

   // Fecha arquivo aberto
   fclose(setup);
}

void traduzLetrasCod(AVL *letrasCod, char* texto, char espaco, char minuscula){

   printf("OUTPUT: ");

   int i=0;

   if(minuscula=='S')
      texto = minuscMaiusc(texto);

   while(texto[i]!='\n'){

      if(texto[i]==' ')
         printf("%c ", espaco);
      else
         printf("%s ",buscaInfoAVL(letrasCod, texto[i]));
      i++;
   }
}

void traduzCodLetras(ABP *codLetras, char* texto, char espaco, char* binario){

   texto[strlen(texto)-1]='\0';

   printf("OUTPUT: ", texto);

   char *palavra = strtok(texto, " ");

   while( palavra != NULL ) {

      if(palavra[0]==espaco)
         printf(" ");
      else
         printf("%c",buscaInfoABP(codLetras, palavra, binario));

      palavra = strtok(NULL, " ");
   }
}

// Traduz Letras->Cod a partir de um arquivo
void traduzLetrasCodArquivo(AVL *letrasCod, char espaco, char minuscula){

   char buffer[256];
   FILE *entrada, *saida;

   entrada = fopen("_Entrada.txt", "r");
   saida = fopen("_Saida.txt", "w");

   if (entrada == NULL || saida == NULL){
      printf("ERRO: Arquivo nao localizado.\n");
   }else{
      while(fgets(buffer, 256, entrada) != NULL){

         // Tranforma letras minusculas em maiusculas
         if(minuscula=='S')
            strcpy(buffer, minuscMaiusc(buffer));

         int i=0;

         while(buffer[i]!='\0'){

            if(buffer[i]==' ')
               fprintf(saida, "%c ", espaco);
            else if(buffer[i]=='\n')
               fprintf(saida, "\n");
            else
               fprintf(saida, "%s ", buscaInfoAVL(letrasCod, buffer[i]));

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
               fseek(entrada, -strlen(aux)-1, SEEK_CUR);//(**)
            }else{
               if(aux[0]==espaco)
                  fprintf(saida, " ");
               else if(aux[0]=='\n')
                  fprintf(saida, "\n");
               else{
                  if(aux[strlen(aux)-1]=='\n'){// Preserva quebra de linha
                     aux[strlen(aux)-1]='\0';
                     fprintf(saida, "%c", buscaInfoABP(codLetras, aux, binario));
                     fprintf(saida,"\n");
                  }else
                     fprintf(saida, "%c", buscaInfoABP(codLetras, aux, binario));

               }
            }
         }
      }
   }
   fclose(entrada);
   fclose(saida);

   /*(**) Eventualmente, dado o tamanho do buffer, poderia acontecer de uma letra ser cortada pela metade.
   Por exemplo, a frase ".... . .-.. .-.. ---" com um buffer com 14 caracteres, seria dividida em
   ".... . .-.. .-" e ".. ---" separando um "L" em duas letras, "A" e "I".
   Para evitar o problema, quando isso acontece, voltamos o ponteiro até o inicio da letra cortada */
}

// Tranforma letras minusculas em maiusculas
char* minuscMaiusc(char* texto){
   for(int j=0;j<strlen(texto);j++){
      if(texto[j]>=97 && texto[j]<=122)
         texto[j]=texto[j]-32;
   }
   return texto;
}