#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SPA.h"

void LimpaBuffer(){
    scanf("%*[^\n]");
    scanf("%*c");
}

void InicializaFila(Fila *fila){
    fila->inicio = NULL;
    fila->final = NULL;
}

int VerificaFilaVazia(Fila *fila){
    if(fila->inicio == NULL){
        return 1;
    }else{
        return 0;
    }
}

void MostraMenuCadastro(){
    printf("\n");
    printf("==========================================\n");
    printf("           ** MENU PRINCIPAL **           \n");
    printf("==========================================\n");
    printf("| 1. Cadastrar cliente                   |\n"); //feito
    printf("| 2. Consultar clientes na fila          |\n"); //feito
    printf("| 3. Consultar estoque                   |\n");
    printf("| 4. Consultar procedimentos             |\n"); //feito
    printf("| 5. Atender cliente (fila produtos)     |\n");
    printf("| 6. Atender cliente (fila procedimentos)|\n");
    printf("| 0. Sair                                |\n");
    printf("==========================================\n");
    printf("Digite sua escolha: ");
        
}

void mostraMenuConsultaProcedimentos(){
    printf("\n");
    printf("==========================================\n");
    printf("         ** MENU PROCEDIMENTOS **         \n");
    printf("==========================================\n");
    printf("| 1. Cadastrar procedimento              |\n"); //feito
    printf("| 2. Mostrar procedimentos e suas etapas |\n"); //feito
    printf("| 3. Adicionar etapa                     |\n");
    printf("| 4. Excluir um procedimento             |\n"); //feito
    printf("| 5. Remover uma etapa.                  |\n");
    printf("| 6. Salvar dados.                       |\n");
    printf("| 0. Sair.                               |\n");
    printf("==========================================\n");
    printf("Digite sua escolha: ");

}

void mostrarMenuConsultaProdutos(){
    printf("\n");
    printf("==========================================\n");
    printf("            ** MENU ESTOQUE **            \n");
    printf("==========================================\n");
    printf("| 1. Cadastrar produto                   |\n"); //feito
    printf("| 2. Consultar estoque                   |\n"); //feito
    printf("| 3. Remover produtos do estoque         |\n");
    printf("| 0. Sair                                |\n"); //feito
    printf("==========================================\n");
    printf("Digite sua escolha: ");
}

void CadastroCliente(Fila *FilaProduto, Fila *FilaProcedimento, char nome[], char telefone[], long int cpf, int pedido){
    Pessoa *cliente = (Pessoa *)malloc(sizeof(Pessoa)); //aloca novo cliente
    strcpy(cliente->nome, nome);
    strcpy(cliente->telefone, telefone);
    cliente->cpf = cpf;
    cliente->pedido = pedido;
    cliente->proximo = NULL;

    if(pedido == 1){
        if(VerificaFilaVazia(FilaProduto) == 1){ //caso fila vazia, coloca o cliente como o primeiro
            FilaProduto->inicio = cliente;
            FilaProduto->final = cliente;
            printf("Cliente adicionado na fila de Produto com sucesso.\n");
        }else{
            FilaProduto->final->proximo = cliente; //caso não esteja vazia, coloca no fim da fila
            FilaProduto->final = cliente;
            printf("Cliente adicionado na fila de Produto com sucesso.\n");
        }
    }else if(pedido == 2){
        if(VerificaFilaVazia(FilaProcedimento) == 1){
            FilaProcedimento->inicio = cliente;
            FilaProcedimento->final = cliente;
            printf("Cliente adicionado na fila de Procedimento com sucesso.\n");
        }else{
            FilaProcedimento->final->proximo = cliente;
            FilaProcedimento->final = cliente;
            printf("Cliente adicionado na fila de Procedimento com sucesso.\n");
        }
    }
}

void ConsultarFila(Fila *FilaProduto, Fila *FilaProcedimento){
    int pedido;
    printf("Qual fila você deseja consultar?\n");
    printf("1. Produto\n");
    printf("2. Procedimento\n");
    scanf("%d", &pedido);
    LimpaBuffer();

    if(pedido == 1){
        if(FilaProduto->inicio == NULL){
            printf("A fila de produtos está vazia.");
        }else{
            Pessoa *aux = FilaProduto->inicio;
            printf("--------- LISTA DE CLIENTES NA FILA DE PRODUTO ---------\n");
            printf("--------------------------------------------------------\n");
            printf("| %-30s | %-15s |\n", "NOME", "TELEFONE");
            printf("--------------------------------------------------------\n");
            while(aux != NULL){
                printf("| %-30s | %-15s |\n", aux->nome, aux->telefone);
                aux = aux->proximo;
            }
            printf("--------------------------------------------------------\n");
        }
    }else{
        if(FilaProcedimento->inicio == NULL){
            printf("A fila de procedimentos está vazia.");
        }else{
            Pessoa *aux = FilaProcedimento->inicio;

            printf("--------- LISTA DE CLIENTES NA FILA DE PROCEDIMENTO ---------\n");
            printf("-------------------------------------------------------------\n");
            printf("| %-30s | %-15s |\n", "NOME", "TELEFONE");
            printf("-------------------------------------------------------------\n");
            while(aux != NULL){
                printf("| %-30s | %-15s |\n", aux->nome, aux->telefone);
                aux = aux->proximo;
            }
            printf("-------------------------------------------------------------\n");
        }
    }
}

void InicializaLista(Estoque *estoque){
    estoque->inicio = NULL;
    estoque->final = NULL;
}

int VerificaListaVazia(Estoque *estoque){
    if(estoque->inicio == NULL){
        return 1;
    }else{
        return 0;
    }
}

void CadastroEstoque(Estoque *estoque, char nome[], int id, int quantidade, float valor){
    Produto *NovoProduto = (Produto *)malloc(sizeof(Produto));
    strcpy(NovoProduto->nome, nome);
    NovoProduto->id_produto = id;
    NovoProduto->quantidade = quantidade;
    NovoProduto->valor = valor;
    NovoProduto->proximo = NULL;

    if(estoque->inicio == NULL){
        estoque->inicio = NovoProduto;
        estoque->final = NovoProduto;
    }else{
        estoque->final->proximo = NovoProduto;
        estoque->final = NovoProduto;
    }
}

void ConsultarLista(Estoque *estoque){
    if(estoque->inicio == NULL){
        printf("Não há nenhum produto no estoque.\n");
    }else{
        Produto *aux = estoque->inicio;
        
        printf("Lista de produtos no estoque:\n");
        printf("---------------------------------------------------\n");
        printf("| Nome          | ID       | Valor     | Quantidade |\n");
        printf("---------------------------------------------------\n");
        
        while(aux != NULL){
            printf("| %-12s | %-8d | %-9.2f | %-10d |\n", aux->nome, aux->id_produto, aux->valor, aux->quantidade);
            aux = aux->proximo;
        }
        printf("---------------------------------------------------\n");
    }
}

void RemoveProduto(Estoque *estoque, int id){
    if (estoque->inicio == NULL) {
        printf("O estoque está vazio.\n");
        return;
    }

    Produto *atual = estoque->inicio;
    Produto *anterior = NULL;

    // Remove do início
    if (atual->id_produto == id) {
        estoque->inicio = atual->proximo;
        if (estoque->inicio == NULL) { // Caso era o único elemento
            estoque->final = NULL;
        }
        free(atual);
        printf("Produto com ID %d removido.\n", id);
        return;
    }

    // Percorrer a lista para encontrar o produto
    while (atual != NULL && atual->id_produto != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o produto não foi encontrado
    if (atual == NULL) {
        printf("Produto com ID %d não encontrado.\n", id);
        return;
    }

    if (atual->proximo != NULL) {
        anterior->proximo = atual->proximo;
    } else {
        anterior->proximo = NULL;
        estoque->final = anterior;
    }

    free(atual);
    printf("Produto com ID %d removido.\n", id);
}

void checarInserido(Fila *FilaProduto, Fila *FilaProcedimento, long int cpf, int pedido){

    if(pedido == 1){
        Pessoa *aux = FilaProduto->final;
        if(aux->cpf == cpf){
            printf("Cliente cadastrado com sucesso!\n");
            return; 
        }else{
            printf("Falha no cadastro do cliente.\n");
            return; 
        }
    }else if(pedido == 2){
        Pessoa *aux = FilaProcedimento->final;
        if(aux->cpf == cpf){
            printf("Cliente cadastrado com sucesso!\n");
            return; 
        }else{
            printf("Falha no cadastro do cliente.\n");
            return; 
        }
    }

    return;
}

int checaID(Estoque *estoque, int id){
    int cont;

        if(estoque->inicio != NULL){ //Caso não seja o primeiro item da lista.
            do{
                cont = 0;   //Condição de parada sempre inicializa em 0.
                    
                Produto *aux = estoque->inicio; //Primeiro item do estoque.
                while(aux != NULL){ //Enquanto não chega no último.
                    if(aux->id_produto == id){ //Se o produto atual tiver o mesmo id de algum produto existente
                        cont = 1;   //Atualiza o condição de parada (O loop vai rodar de novo)
                        printf("O ID cadastrado já existe, insira outro por favor.\n");
        
                        scanf("%d", &id);   //Pega o novo ID.
                        LimpaBuffer();

                        break; //Se achou um produto com o mesmo ID, sai do loop interior e vai para o do-while.
                    }
                    aux = aux->proximo; //Vai para o próximo produto da lista
                }
                
            }while(cont != 0);
        }

    return id;
}

void normalizeString(char* str) {
    char* src = str; // Ponteiro para a origem
    char* dst = str; // Ponteiro para o destino
    int capitalize = 1; // Indica se a próxima letra deve ser maiúscula

    // Remove espaços do início
    while (isspace((unsigned char)*src)) {
        src++;
    }

    // Copia o conteúdo sem os espaços iniciais e ajusta a capitalização
    while (*src) {
        if (isspace((unsigned char)*src)) {
            *dst++ = *src++; // Copia espaços
            capitalize = 1; // Próximo caractere pode ser início de palavra
        } else if (capitalize && isalpha((unsigned char)*src)) {
            *dst++ = toupper((unsigned char)*src++); // Primeira letra maiúscula
            capitalize = 0; // Não capitalizar mais até o próximo espaço
        } else {
            *dst++ = tolower((unsigned char)*src++); // Restante da palavra em minúsculo
        }
    }

    *dst = '\0'; // Finaliza a string

    // Remove espaços do final
    dst--;
    while (dst >= str && isspace((unsigned char)*dst)) {
        dst--;
    }

    // Finaliza a string no último caractere não-espacial
    *(dst + 1) = '\0';
}

char* checaNome(Estoque* estoque, char nome[]) {
    int cont;
    static char str[50];
    strcpy(str, nome);

    // Normaliza a string de entrada
    normalizeString(str);

    if (estoque->inicio != NULL) { // Caso não seja o primeiro item da lista
        do {
            cont = 0; // Condição de parada inicializa em 0
                
            Produto* aux = estoque->inicio; // Primeiro item do estoque
            while (aux != NULL) { // Enquanto não chega ao último
                
                char auxNome[50];
                strcpy(auxNome, aux->nome); // Faz uma cópia do nome no estoque
                normalizeString(auxNome);  // Normaliza o nome no estoque

                if (strcmp(auxNome, str) == 0) { // Compara nomes normalizados
                    cont = 1; // Atualiza a condição de parada
                    printf("Esse produto já existe.\n");
                    printf("Insira um produto diferente:\n");

                    scanf(" %[^\n]s", str); // Pega o novo nome
                    LimpaBuffer();
                    normalizeString(str); // Normaliza o novo nome

                    break; // Sai do loop interior
                }
                aux = aux->proximo; // Vai para o próximo produto
            }
                
        } while (cont != 0);
    }

    return str;
}

void MenuProdutosDisponiveis(Estoque *estoque, int opcao){
    if(estoque->inicio == NULL){
            printf("Não há produtos disponíveis.\n");
    }else{
        if(opcao == 1){
            Produto *aux = estoque->inicio;
            printf("Lista de produtos disponíveis:\n");
            printf("-------------------------------------------\n");
            printf("| ID          | Produto       | Valor     |\n");
            printf("-------------------------------------------\n");
            
            while(aux != NULL){
                printf("| %-8d | %-12s | %-9.2f |\n", aux->id_produto, aux->nome, aux->valor);
                aux = aux->proximo;
            }
                printf("-------------------------------------------\n");
        }else{
            return;
        }
    }
}

void AtenderClienteFilaProduto(Fila *FilaProduto, Estoque *estoque){

    int escolha_cliente, quantidade_desejada, opcao = 1, aux2;
    int nota_fiscal_id[50], nota_fiscal_qtd[50], cont = 0;
    Pessoa *cliente = FilaProduto->inicio;

    if(FilaProduto->inicio == NULL){
        printf("A fila está vazia, não há ninguém para o atendimento.\n");
    }else{

        MenuProdutosDisponiveis(estoque, opcao);

        printf("Você está atendendo o cliente %s - %d. \n", cliente->nome, cliente->cpf);

        do{
            printf("Digite o ID do produto que deseja comprar: \n");
            do{
                scanf("%d", &escolha_cliente);
            }while(!ChecaIdValido(estoque, escolha_cliente));
            
            nota_fiscal_id[cont] = escolha_cliente;

            printf("Quantas unidades do produto você deseja?:\n");
            scanf("%d", &quantidade_desejada);
            DiminuirQuantidade(estoque, escolha_cliente, quantidade_desejada);

            nota_fiscal_qtd[cont] = quantidade_desejada;
            cont++;
            
            printf("Você deseja fazer outra compra?\n");
            printf("1. Sim\n");
            printf("2. Não\n");
            scanf("%d", &opcao);

            if(estoque->inicio == NULL){
                printf("Não há produtos disponíveis.\n");
            }else{
                MenuProdutosDisponiveis(estoque, opcao);
            }

        }while(opcao != 2);

        Pessoa *aux = FilaProduto->inicio;
        Produto *aux2 = estoque->inicio;
        float preco_individual, preco_total = 0;

        printf("-------------------Nota fiscal-------------------\n");
        printf("Cliente: %s\n", aux->nome);
        for(int i = 0; i<cont; i++){
            Produto *aux2 = estoque->inicio;
            while(aux2 != NULL){
                if(aux2->id_produto == nota_fiscal_id[i]){
                    preco_individual = (float)nota_fiscal_qtd[i] * aux2->valor;
                    printf("%d %s - %.2f\n", nota_fiscal_qtd[i], aux2->nome, preco_individual);

                    preco_total += preco_individual;
                }
                aux2 = aux2->proximo;
            }
        }
        printf("%.2f\n", preco_total);
        printf("-----------------------------------------------\n");

        RetiraClienteFila(FilaProduto);
    }

    int opcao2;
    
    printf("Deseja continuar atendendo a fila de Produto?\n");
    printf("1. Sim\n");
    printf("2. Não\n");
    scanf("%d", &opcao2);
    
    if(opcao2 == 1){
        
        AtenderClienteFilaProduto(FilaProduto, estoque);
    }else if(opcao2 == 2){
        return;
    }else{
        printf("Opção inválida\n");
    }

}

void DiminuirQuantidade(Estoque *estoque, int ID, int quantidade_desejada){
    Produto *aux = estoque->inicio;
    while(aux != NULL){
        if(aux->id_produto == ID){
            if(quantidade_desejada > aux->quantidade){
                printf("Quantidade de produtos disponíveis insuficiente.\n");
                return; // Encerra a função sem realizar alterações
            }else{
                aux->quantidade -= quantidade_desejada;
                printf("Compra realizada com sucesso. Quantidade restante do produto %s: %d.\n", aux->nome, aux->quantidade);
                if(aux->quantidade == 0){
                    printf("Produto %d - %s esgotado. Reponha no estoque.\n", aux->id_produto, aux->nome);
                    RemoveProduto(estoque, ID);
                }
                return;
            }
        }
        aux = aux->proximo;
    }
    printf("Produto não encontrado no estoque.\n"); // Caso o ID não exista
}

int ChecaIdValido(Estoque *estoque, int ID){
    Produto *aux = estoque->inicio;
    
    while(aux != NULL){
        if(aux->id_produto == ID){
            return 1;
        }
        aux = aux->proximo;
    }
    printf("ID inválido, insira um válido.\n");
    return 0;
}

void RetiraClienteFila(Fila *Fila){
    if(Fila->inicio == NULL){
        printf("A fila está vazia.\n");
    }else{
        Pessoa *clinte = Fila->inicio;
        Fila->inicio = Fila->inicio->proximo;

        if(Fila->inicio == NULL){
            Fila->final = NULL;
        }

        free(clinte);
    }
}

void carregarCliente(const char *arqClientes, Fila *filaProdutos, Fila *filaProcedimentos){
    FILE *arquivo = fopen(arqClientes, "r");

    if(!arquivo){
        perror("Erro ao abrir arquivo de clientes.\n");
        return;
    }

    char linha[100];
    char nome[50], telefone[15];
    int pedido;
    long int cpf;

    while(fgets(linha, sizeof(linha), arquivo)){
        if(sscanf(linha, "%49[^;];%d;%14[^;];%ld", nome, &pedido, telefone, &cpf) == 4){
            CadastroCliente(filaProdutos, filaProcedimentos, nome, telefone, cpf, pedido);
        }
    }

    fclose(arquivo);
}

void carregarProdutos(const char *arqEstoque, Estoque *estoque){
    FILE *arquivo = fopen(arqEstoque, "r");

    if(!arquivo){
        perror("Erro ao abrir arquivo de estoque.\n");
        return;
    }

    char linha[100];
    char nome[50];
    int id_produto, quantidade;
    float valor;

    while(fgets(linha, sizeof(linha), arquivo)){
        if(sscanf(linha, "%49[^;];%d;%d;%f", nome, &id_produto, &quantidade, &valor) == 4){
            CadastroEstoque(estoque, nome, id_produto, quantidade, valor);
        }
    }

    fclose(arquivo);
}

void salvarClientes(const char *arqClientes, Fila *filaProdutos, Fila *filaProcedimentos){
    FILE *arquivo = fopen(arqClientes, "w");

    if(!arquivo){
        perror("Erro ao abrir arquivo de clientes para escrita.\n");
        return;
    }

    Pessoa *cliente = filaProdutos->inicio;
    while(cliente != NULL){
        fprintf(arquivo, "%s;%d;%s;%ld\n", cliente->nome, cliente->pedido, cliente->telefone, cliente->cpf);
        cliente = cliente->proximo;
    }

    fclose(arquivo);
}

void salvarEstoque(const char *arqEstoque, Estoque *estoque){
    FILE *arquivo = fopen(arqEstoque, "w");
    
    if(!arquivo){
        perror("Erro ao abrir arquivo de clientes para escrita.\n");
        return;
    }

    Produto *produto = estoque->inicio;
    while(produto != NULL){
        fprintf(arquivo, "%s;%d;%d;%f\n", produto->nome, produto->id_produto, produto->quantidade, produto->valor);
        produto = produto->proximo;
    }

    fclose(arquivo); 
}

void liberaFila(Fila *fila){
    Pessoa *cliente = fila->inicio;

    while(fila != NULL){
        Pessoa *aux = cliente;
        cliente = cliente->proximo;
        free(aux);
    }
    free(fila);
}

void liberaEstoque(Estoque *estoque){
    Produto *produto = estoque->inicio;

    while(estoque != NULL){
        Produto *aux = produto;
        produto = produto->proximo;
        free(aux);
    }
    free(estoque);
}

void inicia_fila(FILA* f ){
    f->prim = 0;
    f->ult = 0;
}

PROCEDIMENTO* criar_procedimento(char* nome){
    PROCEDIMENTO* novo_procedimento = (PROCEDIMENTO*)malloc(sizeof(PROCEDIMENTO));//pra alocar dinamicamente uma estrutura do tipo procedimento
    if(novo_procedimento == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strncpy(novo_procedimento->nome, nome, sizeof(novo_procedimento->nome));//é pra tirar o /0
    novo_procedimento->nome[sizeof(novo_procedimento->nome) - 1] = '\0'; // Garantir o terminador nulo
    novo_procedimento->etapas = NULL;
    novo_procedimento->prox = NULL;
    return novo_procedimento;

}

void adicionar_procedimento(FILA* f, char* nome){
    PROCEDIMENTO* novo_procedimento = criar_procedimento(nome); //não entendi muito essa parte aqui
    if(f->prim == NULL){
        f->prim = novo_procedimento;
        f->ult = novo_procedimento;
    }else{
        f->ult->prox = novo_procedimento;
        f->ult = novo_procedimento;
    }
}

void adicionar_etapa(PROCEDIMENTO* procedimento, char* nome_etapa){
    ETAPA* nova_etapa = (ETAPA*)malloc(sizeof(ETAPA));//aloca dinamicamente uma estrutura etapa
    if(nova_etapa == NULL){
        printf("Erro ao alocar memoria para a etapa.\n");
        exit(1);
    }
    strncpy(nova_etapa->nome, nome_etapa, sizeof(nova_etapa->nome));
    nova_etapa->nome[sizeof(nova_etapa->nome) - 1] = '\0';
    nova_etapa->prox = NULL;

    if(procedimento->etapas == NULL){ //se nao tiver outras etapas essa vai ser a primeira
        procedimento->etapas = nova_etapa;
    } else{//adiciona elas no fim das etapas
        ETAPA* atual = procedimento->etapas;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = nova_etapa;
    }
}

void remover_etapa(PROCEDIMENTO* procedimento, char* nome_etapa){
    if(procedimento->etapas == NULL){
        printf("Nao existe etapas para remover neste procedimento.\n");
        return;
    }

    ETAPA* atual = procedimento->etapas;
    ETAPA* anterior = NULL;

    //procura a etapa
    while(atual != NULL && strcmp(atual->nome, nome_etapa) != 0){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Etapa '%s' nao encontrada.\n", nome_etapa);
        return;
    }

    //vai excluir a etapa encontrada
    if(anterior == NULL){
        //a etapa que vai ser excluida é a primeira da lista
        procedimento->etapas = atual->prox;
    } else{
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Etapa '%s' removida com sucesso.\n", nome_etapa);
}


void mostrar_procedimentos(FILA* f){
    if(f->prim == NULL){//confere se tem procedimento
        printf("A fila esta vazia.\n");
        return;
    }
    PROCEDIMENTO* atual = f->prim;
    while(atual != NULL){//mostra todos os procedimentos
        printf("\nProcedimento: %s\n", atual->nome);
        if(atual->etapas == NULL){//confere se o procedimento tem etapas
            printf("  Nenhuma etapa cadastrada.\n");
        }else{
            ETAPA* etapa_atual = atual->etapas;
            printf("  Etapas:\n");
            while(etapa_atual != NULL){//mostra todas as etapas
                printf("  - %s\n", etapa_atual->nome);
                etapa_atual = etapa_atual->prox;
            }
        }
        atual = atual->prox;
    }
}

void excluir_procedimento(FILA* f, char* nome_procedimento){
    if(f->prim == NULL){
        printf("A fila esta vazia. Nenhum procedimento para excluir.\n");
        return;
    }

    PROCEDIMENTO* atual = f->prim;
    PROCEDIMENTO* anterior = NULL;

    //vai procurar o procedimento
    while(atual != NULL && strcmp(atual->nome, nome_procedimento) != 0){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Procedimento '%s' nao encontrado.\n", nome_procedimento);
        return;
    }

    if(anterior == NULL){
        f->prim = atual->prox;
    } else{
        anterior->prox = atual->prox;
    }

    if (atual == f->ult) {//vai atualizar o ponteiro ult se o procedimento for o ultimo
        f->ult = anterior;
    }

    ETAPA* etapa_atual = atual->etapas;
    while(etapa_atual != NULL){
        ETAPA* etapa_remover = etapa_atual;
        etapa_atual = etapa_atual->prox;
        free(etapa_remover);
    }

    free(atual);
    printf("Procedimento '%s' excluido com sucesso.\n", nome_procedimento);
}

void salvar_dados(FILA* f, const char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para salvar os dados.\n");
        return;
    }

    PROCEDIMENTO* atual = f->prim;
    while(atual != NULL){
        fprintf(arquivo, "P;%s\n", atual->nome);
        ETAPA* etapa_atual = atual->etapas;
        while(etapa_atual != NULL){
            fprintf(arquivo, "E;%s\n", etapa_atual->nome);
            etapa_atual = etapa_atual->prox;
        }
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso no arquivo '%s'.\n", nome_arquivo);
}

void carregar_dados(FILA* f, const char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Nenhum arquivo de dados encontrado. Começando com uma lista vazia.\n");
        return;
    }

    char linha[150];
    PROCEDIMENTO* procedimento_atual = NULL;

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        linha[strcspn(linha, "\n")] = '\0';

        if(linha[0] == 'P' && linha[1] == ';'){
            char* nome_procedimento = linha + 2;
            adicionar_procedimento(f, nome_procedimento); //coloca um procedimento à fila
            procedimento_atual = f->ult; //atualiza o ponteiro para o último procedimento
        } else if(linha[0] == 'E' && linha[1] == ';'){
            if(procedimento_atual != NULL){
                char* nome_etapa = linha + 2;
                adicionar_etapa(procedimento_atual, nome_etapa); //coloca a etapa ao procedimento atual
            } else{
                printf("Erro: etapa encontrada sem um procedimento associado.\n");
            }
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso do arquivo '%s'.\n", nome_arquivo);
}

void AtenderClienteFilaProcedimento(Fila *filaProcedimentos, FILA *procedimentos){

    Pessoa *cliente = filaProcedimentos->inicio; //Pega o primeiro cliente da fila
    char pedido[50];
    char nome_etapa[50];
    int opcao;
    int opcao2;
    PROCEDIMENTO *aux = procedimentos->prim;
    PROCEDIMENTO* atual = procedimentos->prim;

    if(filaProcedimentos->inicio == NULL){ //Checa se ta vazia
        printf("A fila está vazia, não há ninguém para o atendimento.\n");
    }else{
        
        mostrar_procedimentos(procedimentos);
        
        printf("Você está atendendo o cliente %s - %d. \n", cliente->nome, cliente->cpf);

        do{

            printf("Insira o procedimento desejado.\n");
            scanf("%[^\n]", pedido);
            LimpaBuffer();

            while(aux != NULL){
                if(!strcmp(aux->nome, pedido)){
                    printf("Procedimento: %s.\n", aux->nome);

                    if(aux->etapas == NULL){
                        printf("Nenhuma etapa cadastrada.\n");
                    }else{
                        ETAPA *etapaAtual = aux->etapas;
                        printf("Etapas: \n");
                        while(etapaAtual){
                            printf("   - %s\n", etapaAtual->nome);
                            etapaAtual = etapaAtual->prox;
                        }
                    }
                }
                aux = aux->prox;
            }

            do{

                printf("Deseja remover ou adicionar alguma etapa?\n");
                printf("1. Remover.\n");
                printf("2. Adicionar.\n");
                printf("3. Não.\n");
                scanf("%d", &opcao);
                LimpaBuffer();

                switch (opcao){
                
                case 1:

                    atual = procedimentos->prim;
                    while(atual != NULL && strcmp(atual->nome, pedido) != 0){
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
                    break;
                
                case 2:

                    //procura o procedimento pra adicionar a etapa
                    atual = procedimentos->prim;
                    while(atual != NULL){
                        if(strcmp(atual->nome, pedido) == 0){
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

                    break;
                
                case 3:

                    opcao = 3;

                    break;
                
                default:
                    printf("Opção inválida.\n");
                    break;
                }

            }while(opcao != 3);

            printf("Deseja escolher mais um procedimento?\n");

            printf("1. Sim.\n");
            printf("2. Não.\n");           
            scanf("%d", &opcao2);
        
        
        }while(opcao2 != 2);

        RetiraClienteFila(filaProcedimentos);
    }
}