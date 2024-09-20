#ifndef lista_h
#define lista_h
 
#define NOME_LIVRO 150
#define NOME_AUTOR 200
#define NOME_EDITORA 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

     int pos_cabeca;
     int pos_topo; 
     int pos_livre;

} Cabecalho;

typedef struct {

     int codigo;
     char titulo[NOME_LIVRO];
     char autor[NOME_AUTOR];
     char editora[NOME_EDITORA];
     int edicao;
     int ano;
     float preco;
     int estoque;
     int proximo;

}Lista;

//Cria uma lista nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma lista vazia
void cria_lista_vazia(FILE* arq);

//Le o cabecalho do arquivo contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: retorna o ponteiro para o cabecalho lido
Cabecalho* le_cabecalho(FILE * arq);

//Escreve no arquivo o cabecalho contendo as informac~oes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, Cabecalho* cab);

//le um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posicao valida da lista
//Pos-condicao: ponteiro para no lido e retornado
Lista* le_no(FILE* arq, int pos);

//Escreve um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posic~ao valida do arquivo
//Pos-condicao: no escrito no arquivo
void escreve_no(FILE* arq, Lista* x, int pos);

// Escreve um no em uma determinada posicao do arquivo
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//pos deve ser uma posicao valida do arquivo
// Pos-condicao: no escrito no arquivo
void insere(FILE* arq, Lista* x);

// Acao
// Pre-condicao: 
// Pos-condicao:
void imprimir(FILE* arq, int cod);

// Acao
// Pre-condicao: 
// Pos-condicao:
void listar(FILE* arq);

// Acao
// Pre-condicao: 
// Pos-condicao:
void buscaAutor(FILE* arq, char* autor);

// Acao
// Pre-condicao: 
// Pos-condicao:
void buscaTitulo(FILE* arq, char* titulo);

// Acao
// Pre-condicao: 
// Pos-condicao:
void removeLivro(FILE* arq, int codigo);

void calculaTotal(FILE* arq);

void retiraEspaco(char *f);

void converteFloat(char *f);

void funcaoLeitura(FILE* arq, char* nomeArquivo);

void imprimirRegistrosLivres(FILE* arq);

#endif