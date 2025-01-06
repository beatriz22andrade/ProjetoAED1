typedef struct Pessoa { //Nó da fila
    char nome[50];
    int pedido;
    char telefone[15];
    long int cpf;
    struct Pessoa *proximo;
}Pessoa;

typedef struct{ // Fila
    Pessoa *inicio;
    Pessoa *final;
}Fila;

typedef struct Produto{ //Nó da lista
    char nome[50];
    int id_produto;
    int quantidade;
    float valor;
    struct Produto *proximo;
}Produto;

typedef struct Estoque{ //Lista
    Produto *final;
    Produto *inicio;
}Estoque;

typedef struct ETAPA{
    char nome[50];
    struct ETAPA* prox;
}ETAPA;

typedef struct PROCEDIMENTO{
    char nome[100];
    ETAPA* etapas; //ponteiro pra etapas
    struct PROCEDIMENTO* prox;
}PROCEDIMENTO;

typedef struct{
    PROCEDIMENTO* prim; //tem que ser ponteiro pra que possa ser 0
    PROCEDIMENTO* ult;
}FILA;

void inicia_fila(FILA* f );

void LimpaBuffer();

void InicializaFila(Fila *fila);

int VerificaFilaVazia(Fila *fila);

void MostraMenuCadastro();

void mostrarMenuConsultaProdutos();

void mostraMenuConsultaProcedimentos();

void CadastroCliente(Fila *FilaProduto, Fila *FilaProcedimento, char nome[], char telefone[], long int cpf, int pedido);

void ConsultarFila(Fila *FilaProduto, Fila *FilaProcedimento);

void InicializaLista(Estoque *estoque);

int VerificaListaVazia(Estoque *estoque);

void CadastroEstoque(Estoque *estoque, char nome[], int id, int quantidade, float valor);

void ConsultarLista(Estoque *estoque);

void RemoveProduto(Estoque *estoque, int id);

void checarInserido(Fila *FilaProduto, Fila *FilaProcedimento, long int cpf, int pedido);

int checaID(Estoque *estoque, int id);

void normalizeString(char* str);

char* checaNome(Estoque* estoque, char nome[]);

void MenuProdutosDisponiveis(Estoque *estoque, int opcao);

void AtenderClienteFilaProduto(Fila *FilaProduto, Estoque *estoque);

void DiminuirQuantidade(Estoque *estoque, int ID, int quantidade_desejada);

int ChecaIdValido(Estoque *estoque, int ID);

void RetiraClienteFila(Fila *Fila);

void carregarCliente(const char *arqClientes, Fila *filaProdutos, Fila *filaProcedimentos);

void carregarProdutos(const char *arqEstoque, Estoque *estoque);

void salvarClientes(const char *arqClientes, Fila* filaProdutos, Fila *filaProcedimentos);

void salvarEstoque(const char *arqEstoque, Estoque *estoque);

void liberaFila(Fila *fila);

void liberaEstoque(Estoque *estoque);

PROCEDIMENTO* criar_procedimento(char* nome);

void adicionar_procedimento(FILA* f, char* nome);

void adicionar_etapa(PROCEDIMENTO* procedimento, char* nome_etapa);

void remover_etapa(PROCEDIMENTO* procedimento, char* nome_etapa);

void mostrar_procedimentos(FILA* f);

void excluir_procedimento(FILA* f, char* nome_procedimento);

void salvar_dados(FILA* f, const char* nome_arquivo);

void carregar_dados(FILA* f, const char* nome_arquivo);

void AtenderClienteFilaProcedimento(Fila *filaProcedimentos, FILA *procedimentos);