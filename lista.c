#include "lista.h"
#include <ctype.h>

//Cria uma lista nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma lista vazia
void cria_lista_vazia(FILE* arq){

    Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));
    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escreve_cabecalho(arq,cab);
    free(cab);

}

//Le o cabecalho do arquivo contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: retorna o ponteiro para o cabecalho lido
Cabecalho* le_cabecalho(FILE * arq){

    Cabecalho * cab = (Cabecalho*) malloc(sizeof(Cabecalho));
    fseek(arq,0,SEEK_SET); // posiciona no incio do arquivo
    fread(cab,sizeof(Cabecalho),1,arq);
    return cab;

}

//Escreve no arquivo o cabecalho contendo as informac~oes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: cabecalho escrito no arquivo
 
void escreve_cabecalho(FILE* arq, Cabecalho* cab){

    fseek(arq,0,SEEK_SET); //posiciona no incio do arquivo
    fwrite(cab,sizeof(Cabecalho),1,arq);

}

//le um no em uma determinada posic~ao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posicao valida da lista
//Pos-condicao: ponteiro para no lido e retornado

Lista* le_no(FILE* arq, int pos){

    Lista* x = (Lista*) malloc(sizeof(Lista));

    fseek(arq,sizeof(Cabecalho)+ pos*sizeof(Lista), SEEK_SET);
    fread(x,sizeof(Lista),1,arq);


    return x;


}

//Escreve um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posic~ao valida do arquivo
//Pos-condicao: no escrito no arquivo

void escreve_no(FILE* arq, Lista* x, int pos){

    fseek(arq,sizeof(Cabecalho)+ pos*sizeof(Lista),SEEK_SET);
    fwrite(x,sizeof(Lista),1,arq);

}

// Escreve um no em uma determinada posicao do arquivo
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//pos deve ser uma posicao valida do arquivo
// Pos-condicao: no escrito no arquivo

void insere(FILE* arq, Lista* x){

    Cabecalho* cab = le_cabecalho(arq);

    x= (Lista*) malloc (sizeof(Lista));

    printf("Codigo: ");
    scanf("%d", &x->codigo);
    getchar();

    printf("Titulo: ");
    scanf("%[^\n]%*c", x->titulo);
    

    printf("Autor: ");
    scanf("%[^\n]%*c", x->autor);


    printf("Editora: ");
    scanf("%[^\n]%*c", x->editora);
    

    printf("Ano: ");
    scanf("%d", &x->ano);

    printf("Edicao: ");
    scanf("%d", &x->edicao);


    printf("Preco: ");
    scanf("%f", &x->preco);
    

    printf("Estoque: ");
    scanf("%d", &x->estoque);

    x->proximo = cab->pos_cabeca;


    if(cab->pos_livre == -1){

        escreve_no(arq,x,cab->pos_topo);
        cab->pos_cabeca = cab->pos_topo;
        cab->pos_topo++;

    }else{ 

        Lista* aux = le_no(arq,cab->pos_livre);

        escreve_no(arq,x,cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->proximo;
        free(aux);

    }

    escreve_cabecalho(arq,cab); 

    free(cab);

}


void imprimir(FILE* arq, int cod){

    Cabecalho* cab = le_cabecalho(arq);
    int pos_aux = cab->pos_cabeca;
    Lista* aux = NULL;
    int encontrado = 0;

    while (pos_aux != -1 && ((aux = le_no(arq, pos_aux)) != NULL)){

        if (cod == aux->codigo) {
            printf("Titulo : %s\n",   aux->titulo );
            printf("Autor  : %s\n",   aux->autor  );
            printf("Editora: %s\n",   aux->editora);
            printf("Edicao : %d\n",   aux->edicao );
            printf("Ano    : %d\n",   aux->ano    );
            printf("Preco  : %.2f\n", aux->preco  );
            printf("Estoque: %d\n",   aux->estoque);

            encontrado++;
            break;

        }

        pos_aux = aux->proximo;
        free(aux);
        aux = NULL;

    }

    if (!encontrado)

        printf ("\nLivro com codigo digitado nao encontrado!\n");

        free(aux);
        free(cab);

    }



void listar(FILE* arq){

    Cabecalho* cab = le_cabecalho(arq);
    int pos_aux = cab->pos_cabeca;
    Lista* aux = NULL;

    while (pos_aux != -1 && ((aux = le_no(arq, pos_aux)) != NULL)){

        printf("Codigo : %d\n", aux->codigo );
        printf("Titulo : %s\n", aux->titulo );
        printf("Autor  : %s\n", aux->autor  );
        printf("Estoque: %d\n", aux->estoque);
        printf("\n");

        pos_aux = aux->proximo;
        free(aux);
        aux = NULL;
    }

    free(aux);
    free(cab);
}


void buscaAutor(FILE* arq, char* autor){

    Cabecalho* cab = le_cabecalho(arq);
    int pos_aux = cab->pos_cabeca;
    Lista* aux = NULL;
    int encontrado = 0;

    while (pos_aux != -1 && ((aux = le_no(arq, pos_aux)) != NULL)){

        if (strcmp(aux->autor, autor) == 0){

            encontrado++;
            printf("Titulo : %s\n",   aux->titulo );

        }

        pos_aux = aux->proximo;
        free(aux);
        aux = NULL;

    }

    if (!encontrado){

        printf ("\nLivro com autor digitado nao encontrado!\n");

    }

    free(aux);
    free(cab);

}


// Acao
// Pre-condicao: 
// Pos-condicao:

int vazia(Lista* l){

    if(l==NULL){

        return 1;

    }

    return 0;

}

void buscaTitulo(FILE* arq, char* titulo){

    Cabecalho* cab = le_cabecalho(arq);
    int pos_aux = cab->pos_cabeca;
    Lista* aux = NULL;
    int encontrado = 0;

    while(pos_aux != -1 && ((aux = le_no(arq, pos_aux)) != NULL)){

        if (strcmp(aux->titulo, titulo) == 0){

            printf("Codigo : %d\n",   aux->codigo );
            printf("Autor  : %s\n",   aux->autor  );
            printf("Editora: %s\n",   aux->editora);
            printf("Edicao : %d\n",   aux->edicao );
            printf("Ano    : %d\n",   aux->ano    );
            printf("Preco  : %.2f\n", aux->preco  );
            printf("Estoque: %d\n",   aux->estoque);
            printf("\n");

            encontrado++;
        
        }

        pos_aux = aux->proximo;
        free(aux);
        aux = NULL;

    }

    if (!encontrado){

        printf ("\nLivro com titulo digitado nao encontrado!\n");
    }

    free(aux);
    free(cab);

}

void removeLivro(FILE* arq, int codigo){

    Cabecalho* cab = le_cabecalho(arq);
    int pos_aux = cab->pos_cabeca;
    int pos_ant = cab->pos_cabeca;
    Lista* aux = NULL;

    while(pos_aux != -1 && ((aux = le_no(arq,pos_aux))!= NULL) && aux->codigo != codigo){

        pos_ant = pos_aux;
        pos_aux = aux->proximo;

        free(aux);
        aux = NULL;

    }

    if(pos_aux != -1){ 
       
        if(pos_ant == pos_aux){ 

            cab->pos_cabeca = aux->proximo;

        }else { 

            Lista* ant = le_no(arq,pos_ant);

            ant->proximo = aux->proximo;
            escreve_no(arq,ant,pos_ant);
            free(ant);

        }

        aux->proximo = cab->pos_livre; 
        cab->pos_livre = pos_aux;
        escreve_no(arq,aux,pos_aux);
        escreve_cabecalho(arq,cab);
        free(aux);

    }

    free(cab);

}
void calculaTotal(FILE* arq){

    int i=0;

    Cabecalho* cab = le_cabecalho(arq);
    int pos_aux = cab->pos_cabeca;
    Lista* aux = NULL;

    while(pos_aux != -1 && ((aux = le_no(arq, pos_aux)) != NULL)){

        pos_aux = aux->proximo;
        free(aux);
        aux = NULL;

        i++;

    }


    printf("numero de livros cadastrados: %d \n", i);

}   


void insereArquivo(FILE* arq, Lista* x){

    Cabecalho* cab = le_cabecalho(arq);

    x->proximo = cab->pos_cabeca;


    if(cab->pos_livre == -1) { // nao ha nos livres, ent~ao usar o topo

        cab->pos_cabeca = cab->pos_topo;
        escreve_no(arq,x,cab->pos_topo);
        cab->pos_topo++;

    }else{ // usar no da lista de livres

        Lista* aux = le_no(arq,cab->pos_livre);

        escreve_no(arq,x,cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->proximo;
        free(aux);

    }

    escreve_cabecalho(arq,cab); 

    free(cab);

}

void retiraEspaco(char *f){

   int inicio = 0; 
    int fim = strlen(f) - 1;

 
    while (isspace(f[inicio])) {
        inicio++;
    }


    while (fim >= inicio && isspace(f[fim])) {
        fim--;
    }

   
    int i, j;
    for (i = inicio, j = 0; i <= fim; i++, j++) {
        f[j] = f[i];
    }

    f[j] = '\0';

}

void converteFloat(char *f){

    while(*f !='\0'){

        if(*f == ','){

            *f='.';

            return;

        }

        f++;
    }

}


void funcaoLeitura(FILE* arq, char* nomeArquivo){

    char codigo[200];
    char edicao[200];
    char ano[200];
    char preco[200];
    char estoque[200];

    FILE* arqTxt = fopen(nomeArquivo, "r");

    Lista* aux= (Lista*) malloc (sizeof(Lista));

    if (arq==NULL){

        printf("nao foi possivel abrir o arquivo");

        return;

    }


    while(fscanf(arqTxt, "%[^;]%*c %[^;]%*c %[^;]%*c %[^;]%*c %[^;]%*c %[^;]%*c %[^;]%*c %[^\n]%*c", codigo, aux->titulo, aux->autor, aux->editora, edicao, ano,
    preco, estoque) != EOF){

        retiraEspaco(codigo);
        retiraEspaco(ano);
        retiraEspaco(edicao);
        retiraEspaco(aux->titulo);
        retiraEspaco(aux->editora);
        retiraEspaco(aux->autor);
        retiraEspaco(preco);
        retiraEspaco(estoque);

        converteFloat(preco);
        aux->preco= atof(preco);
        aux->codigo= atoi(codigo);
        aux->edicao= atoi(edicao);
        aux->ano= atoi(ano);
        aux->estoque= atoi(estoque);

        insereArquivo(arq,aux);

    }

    fclose(arqTxt);

}

void imprimirRegistrosLivres(FILE* arq){

    Cabecalho* cab = le_cabecalho(arq);

    int pos_livre = cab->pos_livre;

    printf("Posicoes de registros livres:\n");

    while(pos_livre != -1){

        printf("%d ", pos_livre);

        Lista* aux = le_no(arq, pos_livre);

        pos_livre = aux->proximo;

        free(aux);
    }

    printf("\n");
 
    free(cab);

}
