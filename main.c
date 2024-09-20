#include "lista.h"


int main(){

    Lista* livro = NULL;
    Lista* livros = NULL;
    Cabecalho* cadastro = NULL;
    FILE* arquivo;
    int opcao, cod;
    char nome[NOME_AUTOR];

    while(opcao!='9'){
        printf("\n\n");
        printf(" _______________________________________\n");
        printf("|                                       |\n");
        printf("| SISTEMA LIVRARIA                      |\n");
        printf("|                                       |\n");
        printf("| [0] - Cadastrar                       |\n");
        printf("| [1] - Remover                         |\n");
        printf("| [2] - Imprimir Dados                  |\n");
        printf("| [3] - Listar Todos                    |\n");
        printf("| [4] - Busca por Autor                 |\n");
        printf("| [5] - Busca por Titulo                |\n");
        printf("| [6] - Calcular Total                  |\n");
        printf("| [7] - Carregar Arquivo                |\n");
        printf("| [8] - Imprimir Registros Livres       |\n");
        printf("| [9] - Encerrar                        |\n");
        printf("|_______________________________________|\n\n");

        printf("INFORME: ");
        scanf("%d", &opcao);

        printf("\n");

        arquivo = fopen("arquivo.bin", "r+b"); 

        if (arquivo == NULL){

            arquivo= fopen("arquivo.bin", "w+b");
            cria_lista_vazia(arquivo);

        }

        switch(opcao){

            case 0:
                
                escreve_cabecalho(arquivo, cadastro);
                insere(arquivo, livros);
                break;

            case 1:

                printf("Codigo Livro: ");
                scanf("%d", &cod);
                removeLivro(arquivo,cod);
                break;

            case 2:

                printf("Codigo Livro: ");
                scanf("%d", &cod);
                imprimir(arquivo, cod);
                break;

            case 3:

                listar(arquivo);
                break;


            case 4:
                printf("Autor: ");
                scanf("%s", nome);
                printf("\n");
                buscaAutor(arquivo, nome);
                break;

            case 5:

                printf("Titulo: ");
                scanf("%s", nome);
                printf("\n");
                buscaTitulo(arquivo, nome);

                break;

            case 6:

                calculaTotal(arquivo);
                
                break;

            case 7:
            
                funcaoLeitura(arquivo, "arquivo.txt"); 

                break;
                
            case 8:
                
                imprimirRegistrosLivres(arquivo);

                break;

            case 9: 

                fclose(arquivo);

                return 0;

        }

    fclose(arquivo);

    }

    return 0;
    
}