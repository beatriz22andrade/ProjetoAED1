#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SPA.h"

int main(void){


    char nome[50], telefone[12], nome_produto[50];
    int pedido, id, quantidade, opcao;
    float valor;
    long int cpf;
    int opcao_produtos;
    int opcao_procedimentos;
    char nome_procedimento[50];
    char nome_etapa[50];
    const char* nome_arquivo = "dados.txt";

    FILA fila;
    
    Fila *FilaProduto = (Fila *)malloc(sizeof(Fila));
    Fila *FilaProcedimento = (Fila *)malloc(sizeof(Fila)); 

    inicia_fila(&fila);
    InicializaFila(FilaProduto);
    InicializaFila(FilaProcedimento);
    VerificaFilaVazia(FilaProduto);
    VerificaFilaVazia(FilaProcedimento);

    Estoque *EstoqueSPA = (Estoque *)malloc(sizeof(Estoque));

    InicializaLista(EstoqueSPA);
    VerificaListaVazia(EstoqueSPA);

    carregar_dados(&fila, nome_arquivo);
    carregarCliente("arqClientes.txt", FilaProduto, FilaProcedimento);
    carregarProdutos("arqEstoque.txt", EstoqueSPA);

    int Escolha;

    do{
        MostraMenuCadastro();
        scanf("%d", &Escolha);
        LimpaBuffer();

        switch (Escolha){
            case 1:

                do{

                    printf("Insira o nome do cliente:\n");
                    scanf(" %[^\n]s", &nome);
                    LimpaBuffer();
                
                    printf("Insira o telefone do cliente: \n");
                    scanf(" %[^\n]s", &telefone);
                    LimpaBuffer();
                
                    printf("Insira seu cpf: \n");
                    scanf("%ld", &cpf);
                    LimpaBuffer();
                
                    printf("Insira qual o pedido do cliente: \n");
                    printf("1. Produto\n");
                    printf("2. Procedimento\n");
                    scanf("%d", &pedido);
                    LimpaBuffer();
                
                    CadastroCliente(FilaProduto, FilaProcedimento, nome, telefone, cpf, pedido);

                    printf("Deseja cadastrar outro cliente?:\n");
                    printf("1. Sim\n");
                    printf("2. Não\n");
                    scanf("%d", &opcao);
                }while(opcao==1);

                break;
            case 2:

                ConsultarFila(FilaProduto, FilaProcedimento);

                break;
            case 3:

                do{

                    mostrarMenuConsultaProdutos();
                    scanf("%d", &opcao_produtos);
                    
                    switch (opcao_produtos){
                    case 1:
                        
                        printf("Insira o nome do produto:\n");
                        scanf(" %[^\n]s", &nome_produto);
                        LimpaBuffer();
                        char *novoNome = checaNome(EstoqueSPA, nome_produto);
                        strcpy(nome_produto, novoNome);
                        
                        printf("Insira o ID do produto:\n");
                        scanf("%d", &id);
                        LimpaBuffer();
                        id = checaID(EstoqueSPA, id);
                        
                        printf("Insira a quantidade do produto: \n");
                        scanf("%d", &quantidade);
                        LimpaBuffer();
                        
                        printf("Insira o valor do produto: \n");
                        scanf("%f", &valor);
                        LimpaBuffer();
                        
                        CadastroEstoque(EstoqueSPA, nome_produto, id, quantidade, valor);
                        printf("Produto inserido com sucesso.\n");

                        break;

                    case 2:
                        
                        ConsultarLista(EstoqueSPA);
                        
                        break;

                    case 3:

                        printf("Digite o id do produto para remove-lo: \n");
                        scanf("%d", &id);
                        RemoveProduto(EstoqueSPA, id);

                        break;

                    case 0:

                        opcao_produtos = 0;

                        break;

                    default:

                        printf("Opção inválida.\n");

                        break;
                    }
                    
                }while(opcao_produtos != 0);
                break;
                
            case 4:
                do{
                    mostraMenuConsultaProcedimentos();
                    scanf("%d", &opcao_procedimentos);
                    getchar();

                    if(opcao_procedimentos == 1){
                        printf("Digite o nome do procedimento: ");
                        fgets(nome_procedimento, sizeof(nome_procedimento), stdin);
                        nome_procedimento[strcspn(nome_procedimento, "\n")] = '\0'; //tira o '\n'

                        adicionar_procedimento(&fila, nome_procedimento);
                        printf("Procedimento adicionado a fila.\n");
                        
                    } else if(opcao_procedimentos == 2){
                        mostrar_procedimentos(&fila);

                    } else if(opcao_procedimentos == 3){
                        printf("Digite o nome do procedimento pra adicionar a etapa: ");
                        fgets(nome_procedimento, sizeof(nome_procedimento), stdin);
                        nome_procedimento[strcspn(nome_procedimento, "\n")] = '\0';

                        //procura o procedimento pra adicionar a etapa
                        PROCEDIMENTO* atual = fila.prim;
                        while(atual != NULL){
                            if(strcmp(atual->nome, nome_procedimento) == 0){
                                break;
                            }
                            atual = atual->prox;
                        }

                        if(atual == NULL){
                            printf("Procedimento nao encontrado.\n");
                        } else{
                            printf("Digite o nome da etapa: ");
                            fgets(nome_etapa, sizeof(nome_etapa), stdin);
                            nome_etapa[strcspn(nome_etapa, "\n")] = '\0';

                            adicionar_etapa(atual, nome_etapa);
                            printf("Etapa adicionada ao procedimento.\n");
                        }

                    } else if(opcao_procedimentos == 4){
                        printf("Digite o nome do procedimento a ser excluido: ");
                        fgets(nome_procedimento, sizeof(nome_procedimento), stdin);
                        nome_procedimento[strcspn(nome_procedimento, "\n")] = '\0';

                        excluir_procedimento(&fila, nome_procedimento);
                    }else if(opcao_procedimentos == 5){
                        printf("Digite o nome do procedimento: ");
                        fgets(nome_procedimento, sizeof(nome_procedimento), stdin);
                        nome_procedimento[strcspn(nome_procedimento, "\n")] = '\0';

                        PROCEDIMENTO* atual = fila.prim;
                        while(atual != NULL && strcmp(atual->nome, nome_procedimento) != 0){
                            atual = atual->prox;
                        }

                        if(atual == NULL){
                            printf("Procedimento nao encontrado.\n");
                        } else{
                            printf("Digite o nome da etapa a ser removida: ");
                            fgets(nome_etapa, sizeof(nome_etapa), stdin);
                            nome_etapa[strcspn(nome_etapa, "\n")] = '\0';

                            remover_etapa(atual, nome_etapa);
                        }
                    }else if(opcao_procedimentos == 6){
                        salvar_dados(&fila, nome_arquivo);
                    }
                } while(opcao_procedimentos != 0);
                break;
            case 5:

                AtenderClienteFilaProduto(FilaProduto, EstoqueSPA);

                break;
            case 6:
                AtenderClienteFilaProcedimento(FilaProcedimento, &fila);
                break;

            case 0:

                Escolha = 0;
                break;
                
            default:
                printf("Opção inválida.\n");
                break;
        }
    }while(Escolha != 0);

    salvarClientes("arqClientes.txt", FilaProduto, FilaProcedimento);
    salvarEstoque("arqEstoque.txt", EstoqueSPA);
    salvar_dados(&fila, nome_arquivo);

    liberaFila(FilaProcedimento);
    liberaFila(FilaProduto);
    liberaEstoque(EstoqueSPA);

    return 0;
}