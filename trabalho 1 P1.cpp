#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

// Definição das constantes
#define MAX_CARACTERES_NOME 50
#define MAX_CARACTERES_SKU 20
#define MAX_CARACTERES_LINHA 100
#define MAX_CATEGORIAS 20
#define MAX_PRODUTOS 250
#define MAX_CLIENTES 999
#define MAX_NOME 50
#define MAX_SKU 20

#define MAX_NIF 9
#define MAX_TELF 9


// Definição das estruturas
		//struct relativa aos produtos
typedef struct {
    int id;
    char nome[MAX_NOME];
    char sku[MAX_SKU];
    int quantidade;
    double preco;
    int id_categoria;
} Produto;
		//struct relativa às categorias
typedef struct Categoria {
    int categoria_id;
    char nome[50];
    struct Categoria* anterior;
    struct Categoria* proximo;
} Categoria;
typedef struct {
    Categoria* primeira;
    Categoria* ultima;
} ColecaoCategorias;

void inicializarColecao(ColecaoCategorias* colecao) {
    colecao->primeira = NULL;
    colecao->ultima = NULL;
}

// Função para adicionar uma nova categoria à coleção
void adicionarCategoria(ColecaoCategorias* colecao, Categoria novaCategoria) {
    Categoria* novaCategoriaPtr = (Categoria*)malloc(sizeof(Categoria));
    if (novaCategoriaPtr == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);  
    }
    *novaCategoriaPtr = novaCategoria;
    novaCategoriaPtr->anterior = colecao->ultima;
    novaCategoriaPtr->proximo = NULL;

    if (colecao->primeira == NULL) {
        colecao->primeira = novaCategoriaPtr;
    } else {
        colecao->ultima->proximo = novaCategoriaPtr;
    }

    colecao->ultima = novaCategoriaPtr;
}

void liberarColecao(ColecaoCategorias* colecao) {
    Categoria* atual = colecao->primeira;
    while (atual != NULL) {
        Categoria* proxima = atual->proximo;
        free(atual);
        atual = proxima;
    }
    colecao->primeira = NULL;
    colecao->ultima = NULL;
}


		//struct relativa aos clientes
typedef struct{
	char cnome[MAX_NOME];
	char nif[MAX_NIF];
	char telefone[MAX_TELF];
} Cliente;

// Variáveis globais
Categoria categorias[MAX_CATEGORIAS];
Produto produtos[MAX_PRODUTOS];
Cliente clientes[MAX_CLIENTES];
int num_clientes = 0;
int num_categorias = 0;
int num_produtos = 0;

//Funções
void inicializarColecao(ColecaoCategorias* colecao);
void adicionarCategoria(ColecaoCategorias* colecao, Categoria novaCategoria);
void liberarColecao(ColecaoCategorias* colecao);
void criarCategoria(ColecaoCategorias* colecaoCategorias);

void gerirProdutos();
void gerirClientes();
void realizarVendas();
void editarCategoria();
void removerCategoria();
void listarCategorias();
void criarProduto();
void editarProduto();
void removerProduto();
void listarProdutos();
void listarProdutosCategoria();
void gerirProdutosSubmenu();
void gerirCategoriasSubmenu();


// Função para criar uma nova categoria
void criarCategoria(ColecaoCategorias* colecaoCategorias) {
    static int proximoID = 1;  // Declaração da variável proximoID
    Categoria novaCategoria;
    novaCategoria.categoria_id = proximoID++;
    printf("Escreva o nome da categoria: ");
    scanf("%s", novaCategoria.nome);

 
    adicionarCategoria(colecaoCategorias, novaCategoria);

    FILE* arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fprintf(arquivo, "%d %s\n", novaCategoria.categoria_id, novaCategoria.nome);
    fclose(arquivo);

    printf("Categoria criada com sucesso!\n");
}


// Função para editar uma categoria existente
void editarCategoria() {
    if (num_categorias == 0) {
        printf("Erro: nenhuma categoria registada\n");
        return;
    }

    int id_categoria;
    printf("Escreva o ID da categoria a ser editada: ");
    
    // Listar categorias disponíveis
    printf("Categorias disponiveis:\n");
    listarCategorias();

    scanf("%d", &id_categoria);

    // Abrir ficheiro de texto em modo de leitura
    FILE *arquivo;
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }

    int encontrou_categoria = 0;
    int i = 0;

    // Ler cada linha do ficheiro até encontrar a categoria desejada
    while (!feof(arquivo)) {
        char linha[100];
        fgets(linha, 100, arquivo);

        // Extrair os dados da linha
        int categoria_id;
        char nome_categoria[50];
        sscanf(linha, "%d;%[^\n]", &categoria_id, nome_categoria);

        // Verificar se a categoria encontrada é a desejada
        if (categoria_id == id_categoria) {
            printf("Escreva o novo nome da categoria: ");
            scanf("%s", nome_categoria);

            fclose(arquivo);

            // Abrir o ficheiro em modo de escrita e sobrescrever a linha da categoria editada
            arquivo = fopen("produtos.txt", "r+");
            if (arquivo == NULL) {
                printf("Erro ao abrir o ficheiro\n");
                return;
            }

            // Deslocar o ponteiro do arquivo para a posição da linha a ser sobrescrita
            fseek(arquivo, i, SEEK_SET);

            // Sobrescrever a linha com a categoria editada
            fprintf(arquivo, "%d;%s\n", categoria_id, nome_categoria);

            fclose(arquivo);
            printf("Categoria editada com sucesso!\n");

            encontrou_categoria = 1;
            break;
        }

        i = ftell(arquivo); // Obter a posição do ponteiro do ficheiro
    }

    if (!encontrou_categoria) {
        printf("Erro: categoria nao encontrada\n");
        fclose(arquivo);
    }
}

// Função para remover uma categoria existente
void removerCategoria() {
    if (num_categorias == 0) {
        printf("Erro: nenhuma categoria registada\n");
        return;
    }

    int id_categoria;
    printf("Escreva o ID da categoria a ser removida: ");

    // Listar categorias disponíveis para vinculação
    printf("Categorias disponiveis:\n");
    listarCategorias();

    scanf("%d", &id_categoria);

    int i;
    for (i = 0; i < num_categorias; i++) {
        if (categorias[i].categoria_id == id_categoria) {
            // Verifica se há produtos na categoria
            int j;
            for (j = 0; j < num_produtos; j++) {
                if (produtos[j].id == id_categoria) {
                    printf("Erro: ha produtos ligados a essa categoria\n");
                    return;
                }
            }

            // Remove a categoria do array em memória
            num_categorias--;
            for (; i < num_categorias; i++) {
                categorias[i] = categorias[i+1];
            }

            // Remove a categoria do ficheiro de texto
            FILE *arquivo = fopen("produtos.txt", "w");
            if (arquivo == NULL) {
                printf("Erro: nao foi possivel abrir o ficheiro\n");
                return;
            }

            for (i = 0; i < num_categorias; i++) {
                fprintf(arquivo, "%d %s\n", categorias[i].categoria_id, categorias[i].nome);
            }

            fclose(arquivo);

            printf("Categoria removida com sucesso!\n");
            return;
        }
    }

    printf("Erro: categoria nao foi encontrada\n");
}
// Função para listar uma categoria
void listarCategorias() {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: ficheiro nao encontrado\n");
        return;
    }
    
    printf("ID\tNome\n");
    printf("--------------------\n");
    
    Categoria categoria;
    while (fscanf(arquivo, "%d %s", &categoria.categoria_id, categoria.nome) != EOF) {
        printf("%d\t%s\n", categoria.categoria_id, categoria.nome);
    }

    fclose(arquivo);
}


// Função para criar um novo produto
void criarProduto() {
if (num_categorias == 0) {
printf("Erro: nenhuma categoria registada\n");
return;
}
if (num_produtos >= MAX_PRODUTOS) {
printf("Erro: numero maximo de produtos atingido\n");
return;
}
Produto produto;
produto.id = num_produtos + 1;

printf("Escreva o nome do produto: ");
scanf("%s", produto.nome);
fflush(stdin);

printf("Escreva o SKU do produto: ");
scanf("%s", produto.sku);
fflush(stdin);

printf("Escreva a quantidade em stock do produto: ");
scanf("%d", &produto.quantidade);
fflush(stdin);

printf("Escreva o preco do produto: ");
scanf("%lf", &produto.preco);
fflush(stdin);

// Listar categorias disponíveis
printf("Categorias disponiveis:\n");
listarCategorias();

// Vincular o produto a uma categoria existente
int id_categoria;
do {
    printf("Escreva o ID da categoria a qual o produto pertence: ");
    scanf("%d", &id_categoria);

    // Verificar se o ID da categoria existe
    int i;
    for (i = 0; i < num_categorias; i++) {
        if (categorias[i].categoria_id == id_categoria) {
            produto.id_categoria = id_categoria;
            produtos[num_produtos] = produto;
            num_produtos++;

            // Salvar produto no ficheiro
            FILE *f = fopen("produtos.txt", "a");
            if (f == NULL) {
                printf("Erro ao abrir o ficheiro\n");
                return;
            }
            fprintf(f, "%d,%s,%s,%d,%.2f,%d\n", produto.id, produto.nome, produto.sku, produto.quantidade, produto.preco, produto.id_categoria);
            fclose(f);

            printf("Produto criado com sucesso!\n");
            return;
        }
    }

    printf("Erro: categoria nao encontrada\n");

} while (1);
}
// Função para editar um produto existente
void editarProduto() {
    // Verifica se existem produtos
    if (num_produtos == 0) {
        printf("Erro: nenhum produto registado.\n");
        return;
    }

    int id_produto;
    // Listar produtos disponíveis para edição
    printf("Produtos disponiveis:\n");
    listarProdutos();
    printf("Escreva o ID do produto a ser editado: ");
    scanf("%d", &id_produto);

    int i;
    for (i = 0; i < num_produtos; i++) {
        // Verifica se o produto existe na lista de produtos
        if (produtos[i].id == id_produto) {
            printf("Escreva o novo nome do produto: ");
            scanf("%s", produtos[i].nome);
            fflush(stdin);

            printf("Escreva o novo SKU do produto: ");
            scanf("%s", produtos[i].sku);
            fflush(stdin);

            printf("Escreva a nova quantidade do produto: ");
            scanf("%d", &produtos[i].quantidade);
            fflush(stdin);

            printf("Escreva o novo preco do produto: ");
            scanf("%lf", &produtos[i].preco);
            fflush(stdin);

            // Atualiza as informações do produto no ficheiro
            FILE *arquivo = fopen("produtos.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o ficheiro.\n");
                return;
            }
            for (int j = 0; j < num_produtos; j++) {
                fprintf(arquivo, "%d,%s,%s,%d,%.2lf,%d\n", 
                    produtos[j].id, 
                    produtos[j].nome, 
                    produtos[j].sku, 
                    produtos[j].quantidade, 
                    produtos[j].preco, 
                    produtos[j].id_categoria);
            }
            fclose(arquivo);

            printf("Produto editado com sucesso!\n");
            return;
        }
    }

    printf("Erro: produto nao encontrado.\n");
}
// Função para remover um produto existente
void removerProduto() {
    if (num_produtos == 0) {
        printf("Erro: nenhum produto registado.\n");
        return;
    }

    int id_produto;
    printf("Digite o ID do produto a ser removido: ");
    // Listar produtos disponíveis
    printf("Produtos disponiveis:\n");
    listarProdutos();
    scanf("%d", &id_produto);

    FILE *arquivo_produtos = fopen("produtos.txt", "r");
    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    FILE *arquivo_temp = fopen("temp.txt", "w");
    if (arquivo_temp == NULL) {
        printf("Erro ao criar o ficheiro temporario.\n");
        fclose(arquivo_produtos);
        return;
    }

    int i, encontrado = 0;
    char linha[100];
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].id == id_produto) {
            encontrado = 1;
            continue;
        }

        fprintf(arquivo_temp, "%d %s %s %d %.2lf\n", produtos[i].id, produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco);
    }

    if (!encontrado) {
        printf("Erro: produto nao encontrado.\n");
        fclose(arquivo_produtos);
        fclose(arquivo_temp);
        remove("temp.txt");
        return;
    }

    fclose(arquivo_produtos);
    fclose(arquivo_temp);
    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");

    // Atualizar o array de produtos
    arquivo_produtos = fopen("produtos.txt", "r");
    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    num_produtos = 0;
    while (fgets(linha, 100, arquivo_produtos)) {
        sscanf(linha, "%d %s %s %d %lf", &produtos[num_produtos].id, produtos[num_produtos].nome, produtos[num_produtos].sku, &produtos[num_produtos].quantidade, &produtos[num_produtos].preco);
        num_produtos++;
    }

    fclose(arquivo_produtos);

    printf("Produto removido com sucesso!\n");
}

// Função para listar todos os produtos
void listarProdutos() {
    // Abrir o ficheiro de produtos para leitura
    FILE *fp = fopen("produtos.txt", "r");
    if (fp == NULL) {
        printf("Erro: nao foi possivel abrir o ficheiro.\n");
        return;
    }

    // Loop para ler cada linha do ficheiro e exibir a informação do produto
    char linha[MAX_CARACTERES_LINHA];
    while (fgets(linha, MAX_CARACTERES_LINHA, fp) != NULL) {
        // Utilizar a função sscanf para obter as informações do produto da linha
        int id, quantidade;
        double preco;
        char nome[MAX_CARACTERES_NOME], sku[MAX_CARACTERES_SKU];
        sscanf(linha, "%d,%[^,],%[^,],%d,%lf", &id, nome, sku, &quantidade, &preco);
        printf("ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreco: %.2f\n", id, nome, sku, quantidade, preco);
    }
    fclose(fp);
}

// Definição da estrutura produto_temporário
typedef struct {
    int id;
    char nome[MAX_CARACTERES_NOME];
    char sku[MAX_CARACTERES_SKU];
    int quantidade;
    double preco;
    int id_categoria;
} produto_t;

// Função para listar todos os produtos de uma categoria
void listarProdutosCategoria() {
    if (num_categorias == 0) {
        printf("Erro: nenhuma categoria registada.\n");
        return;
    }

    int id_categoria;
    printf("Digite o ID da categoria: ");

    // Listar categorias disponíveis para vinculação
    listarCategorias();

    scanf("%d", &id_categoria);

    // Abrir o ficheiro de produtos em modo de leitura
    FILE *ficheiro_produtos = fopen("produtos.txt", "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (ficheiro_produtos == NULL) {
        printf("Erro: nao foi possivel abrir o ficheiro.\n");
        return;
    }

    // Percorrer o ficheiro de produtos e imprimir os produtos pertencentes à categoria selecionada
    typedef struct {
        int id;
        char nome[MAX_CARACTERES_NOME];
        char sku[MAX_CARACTERES_SKU];
        int quantidade;
        double preco;
        int id_categoria;
    } produto_atual;

    produto_atual prod_atual;
    while (fread(&prod_atual, sizeof(produto_atual), 1, ficheiro_produtos) == 1) {
        if (prod_atual.id_categoria == id_categoria) {
            printf("ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreco: %.2f\n",
                    prod_atual.id, prod_atual.nome, prod_atual.sku,
                    prod_atual.quantidade, prod_atual.preco);
        }
    }

    // Fechar o ficheiro de produtos
    fclose(ficheiro_produtos);
}
void criarcliente()
{
    // Obter informações do cliente
    Cliente novo_cliente;
    printf("Escreva o nome do cliente: ");
    fgets(novo_cliente.cnome, MAX_NOME, stdin);
    printf("Escreva o NIF do cliente: ");
    fgets(novo_cliente.nif, MAX_NIF, stdin);
    printf("Introduza o número de telefone do cliente: ");
    fgets(novo_cliente.telefone, MAX_TELF ,stdin);

    // Abrir o ficheiro para escrever
    FILE* ficheiro = fopen("clientes.txt", "a");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    
    // Escrever as informações no ficheiro
    fprintf(ficheiro, "%s;%s;%s\n", novo_cliente.cnome, novo_cliente.nif, novo_cliente.telefone);
    
    // Fechar o ficheiro
    fclose(ficheiro);
    
    printf("Cliente criado com sucesso!\n");
}
void atualizarCliente() {
    //obter o NIF do cliente a ser atualizado
    char nif[MAX_NIF];
    printf("Digite o NIF do cliente a ser atualizado: ");
    fgets(nif, MAX_NIF, stdin);
    strtok(nif, "\n");

    // abrir o ficheiro original para leitura
    FILE* ficheiro = fopen("clientes.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    // abrir o ficheiro temporário para escrita
    FILE* temp_ficheiro = fopen("temp.txt", "w");
    if (temp_ficheiro == NULL) {
        printf("Erro ao criar ficheiro temporário.\n");
        fclose(ficheiro);
        return;
    }

    // Procurar o cliente com o nif e permitir a atualização dos dados
    int encontrado = 0;
    char linha[MAX_CARACTERES_LINHA];
    while (fgets(linha, MAX_CARACTERES_LINHA, ficheiro)) {
        char *nome = strtok(linha, ";");
        char *nif_atual = strtok(NULL, ";");
        char *telefone = strtok(NULL, "\n");

        if (strcmp(nif_atual, nif) == 0) {
            encontrado = 1;
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", nome);
            printf("NIF: %s\n", nif_atual);
            printf("Telefone: %s\n", telefone);

            printf("Escreva os novos dados do cliente:\n");
            printf("Nome: ");
            fgets(nome, MAX_NOME, stdin);
            strtok(nome, "\n");
            printf("NIF: ");
            fgets(nif_atual, MAX_NIF, stdin);
            strtok(nif_atual, "\n");
            printf("Telefone: ");
            fgets(telefone, MAX_TELF, stdin);
            strtok(telefone, "\n");

            fprintf(temp_ficheiro, "%s;%s;%s\n", nome, nif_atual, telefone);
            printf("Cliente atualizado com sucesso.\n");
        } else {
            fprintf(temp_ficheiro, "%s;%s;%s", nome, nif_atual, telefone);
        }
    }

    fclose(ficheiro);
    fclose(temp_ficheiro);

    // renomear o ficheiro temporário para o nome do ficheiro original
    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (!encontrado) {
        printf("Cliente com nif (%s) não encontrado.\n", nif);
    }
}













void gerirProdutos() {
    int opcao_menu_gerir_produtos;
    do {
        system("cls");
        printf("=== MENU GERIR PRODUTOS ===\n");
        printf("1. Gerir Categorias de Produtos\n");
        printf("2. Gerir Produtos\n");
        printf("3. Listar Produtos por ordem alfabetica do nome\n");
        printf("4. Listar Produtos por ordem descendente de preço\n");
        printf("5. Listar Categoria de Produtos e respetivos produtos\n");
        printf("6. Colocar um Produto sem stock\n");
        printf("7. Gerar um relatório de todo o inventário ordenado por categoria de produto\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_produtos);

        switch (opcao_menu_gerir_produtos) {
            case 1:
                gerirCategoriasSubmenu();
                break;
            case 2:
                gerirProdutosSubmenu();
                break;
            case 3:
                 //ainda em construcao
                break;
            case 4:
                 //ainda em construcao
                break;
            case 5:
                //ainda em construção
                break;
            case 6:
                //ainda em construcao
                break;
            case 7:
                 //ainda em construcao
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    } while (opcao_menu_gerir_produtos != 0);
}
void gerirProdutosSubmenu() {
    int opcao_menu_gerir_produtos;
    do {
        system("cls");
        printf("=== MENU GERIR PRODUTOS ===\n");
        printf("1. Criar Produto\n");
        printf("2. Editar Produto\n");
        printf("3. Remover Produto\n");
        printf("4. Listar Produtos\n");
        printf("5. Listar Produtos por Categoria\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_produtos);

        switch (opcao_menu_gerir_produtos) {
            case 1:
                criarProduto();
                break;
            case 2:
                editarProduto();
                break;
            case 3:
                removerProduto();
                break;
            case 4:
                listarProdutos();
                break;
            case 5:
                listarProdutosCategoria();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    } while (opcao_menu_gerir_produtos != 0);
}

void gerirCategoriasSubmenu() {
     int opcao_menu_gerir_categorias;
    ColecaoCategorias colecaoCategorias;
    inicializarColecao(&colecaoCategorias);
    
    do {
        system("cls");
        printf("=== MENU GERIR CATEGORIAS DE PRODUTOS ===\n");
        printf("1. Criar Categoria\n");
        printf("2. Editar Categoria\n");
        printf("3. Remover Categoria\n");
        printf("4. Listar Categorias\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_categorias);

        switch (opcao_menu_gerir_categorias) {
            case 1:
                criarCategoria(&colecaoCategorias);
                break;
            case 2:
                editarCategoria();
                break;
            case 3:
                removerCategoria();
                break;
            case 4:
                listarCategorias();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    } while (opcao_menu_gerir_categorias != 0);
}

void gerirClientes(){
	printf("Ainda em construção.\n");
}

void realizarVendas() {
    printf("ainda em construcao.\n");
}

void inicializar(){
	// Criar os ficheiros se eles não existirem
	FILE *ficheiro_produtos = fopen("produtos.txt", "a");
    FILE *ficheiro_clientes = fopen("clientes.txt", "a");
    FILE *ficheiro_vendas = fopen("vendas.txt", "a");

    if (ficheiro_produtos == NULL || ficheiro_clientes == NULL || ficheiro_vendas == NULL) {
        printf("Erro: nao foi possivel criar os ficheiros.\n");
        
    }

    fclose(ficheiro_produtos);
    fclose(ficheiro_clientes);
    fclose(ficheiro_vendas);
	setlocale(LC_ALL, "pt_PT.utf8");
}

int main() {
	inicializar();
    int opcao_menu_principal;

    do {
        system("cls");
        printf("=== MENU PRINCIPAL ===\n");
        printf("1. Gerir Produtos\n");
        printf("2. Gerir Clientes\n");
        printf("3. Realizar Vendas\n");
        printf("0. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_principal);

        switch (opcao_menu_principal) {
            case 1:
                gerirProdutos();
                break;
            case 2:
                gerirClientes();
                break;
            case 3:
                realizarVendas();
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao_menu_principal != 0);

    return 0;
}

