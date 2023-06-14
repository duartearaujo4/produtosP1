		#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <locale.h>
	#include <math.h>
	#include <time.h>
	
	// Definição das constantes
	#define MAX_CARACTERES_NOME 50
	#define MAX_CARACTERES_SKU 20
	#define MAX_CARACTERES_LINHA 100
	#define MAX_PRODUTOS 250
	#define MAX_NOME 50
	#define MAX_SKU 20
	#define MAX_NIF 10
	#define MAX_TELF 10

	
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
	    char categoria_nome[50];
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
	
	
			// Struct relativa aos clientes
	typedef struct Cliente {
 	   int cliente_id;
 	   char nome_cliente[MAX_NOME];
 	   char nif[MAX_NIF];
 	   char contato[MAX_TELF];
  	  struct Cliente* anterior;
  	  struct Cliente* proximo;
	} Cliente;
		typedef struct {
  	  Cliente* primeiro;
  	  Cliente* ultimo;
	} ColecaoClientes;

		// Inicializar a coleção de clientes
	void inicializarColecaoClientes(ColecaoClientes* colecao) {
  	 	colecao->primeiro = NULL;
    	colecao->ultimo = NULL;
	}
	
	// Adicionar um novo cliente à coleção
void adicionarCliente(ColecaoClientes* colecao, Cliente novoCliente) {
    Cliente* novoClientePtr = (Cliente*)malloc(sizeof(Cliente));
    if (novoClientePtr == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);  
    }
    *novoClientePtr = novoCliente;
    novoClientePtr->anterior = colecao->ultimo;
    novoClientePtr->proximo = NULL;

    if (colecao->primeiro == NULL) {
        colecao->primeiro = novoClientePtr;
    } else {
        colecao->ultimo->proximo = novoClientePtr;
    }

    colecao->ultimo = novoClientePtr;
}

// Liberar a coleção de clientes
void liberarColecaoClientes(ColecaoClientes* colecao) {
    Cliente* atual = colecao->primeiro;
    while (atual != NULL) {
        Cliente* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    colecao->primeiro = NULL;
    colecao->ultimo = NULL;
}

typedef struct Venda{
    int venda_id;
    int cliente_id;  // Referência para o cliente
    int produto_id;  // Referência para o produto
    int quantidade;  // Quantidade de produtos na venda
    double desconto;  // Desconto aplicado na venda
    double total;  // Valor total da venda (produto.preco * quantidade - desconto)
    char data[11];  // Data da venda no formato AAAA-MM-DD
    char hora[6];  // Hora da venda no formato HH:MM
    struct Venda* anterior;
    struct Venda* proximo;
} Venda;

typedef struct {
    Venda* primeira;
    Venda* ultima;
} ColecaoVendas;

// Inicializar a coleção de vendas
void inicializarColecaoVendas(ColecaoVendas* colecao) {
    colecao->primeira = NULL;
    colecao->ultima = NULL;
}

// Adicionar uma nova venda à coleção
void adicionarVenda(ColecaoVendas* colecao, Venda novaVenda) {
    Venda* novaVendaPtr = (Venda*)malloc(sizeof(Venda));
    if (novaVendaPtr == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);  
    }
    *novaVendaPtr = novaVenda;
    novaVendaPtr->anterior = colecao->ultima;
    novaVendaPtr->proximo = NULL;

    if (colecao->primeira == NULL) {
        colecao->primeira = novaVendaPtr;
    } else {
        colecao->ultima->proximo = novaVendaPtr;
    }

    colecao->ultima = novaVendaPtr;
}

// Liberar a coleção de vendas
void liberarColecaoVendas(ColecaoVendas* colecao) {
    Venda* atual = colecao->primeira;
    while (atual != NULL) {
        Venda* proxima = atual->proximo;
        free(atual);
        atual = proxima;
    }
    colecao->primeira = NULL;
    colecao->ultima = NULL;
}


		
	
	// Variáveis globais
	Produto produtos[MAX_PRODUTOS];
	int num_categorias = 0;
	int num_produtos = 0;
	
	//Funções
	void listarVendasPorHora(ColecaoVendas* colecaoVendas);

	void copiarColecaoClientes(ColecaoClientes* original, ColecaoClientes* copia);
	void inicializarColecao(ColecaoCategorias* colecao);
	void adicionarCategoria(ColecaoCategorias* colecao, Categoria novaCategoria);
	void liberarColecao(ColecaoCategorias* colecao);
	void criarCategoria(ColecaoCategorias* colecaoCategorias);
	void gerirClientesSubmenu(ColecaoClientes* colecaoClientes, ColecaoVendas* colecaoVendas);
	void gerirProdutos();
	void gerirClientes();
	void realizarVenda(ColecaoVendas* colecaoVendas, ColecaoCategorias* colecaoCategorias, ColecaoClientes* colecaoClientes,
				   Produto produtos[], int numProdutos);
	void editarCategoria(ColecaoCategorias* colecaoCategorias);
	void removerCategoria(ColecaoCategorias* colecaoCategorias);
	void listarCategorias();
	void criarProduto(ColecaoCategorias* colecaoCategorias);
	void editarProduto();
	void removerProduto();
	void listarProdutos();
	void listarProdutosCategoria();
	void gerirProdutosSubmenu();
	void gerirCategoriasSubmenu();
	void listarClientes(ColecaoClientes* colecaoClientes);
	int checkVendasCliente(ColecaoVendas* colecaoVendas,int cliente_id);
	void listarProdutosMaisVendidosHoje(ColecaoVendas* colecaoVendas);
	void listarVendasPorData(ColecaoVendas* colecaoVendas);
	void listarVendasPorDataEspecifica(ColecaoVendas* colecaoVendas, const char* data);
void listarProdutosMaisRentaveis(ColecaoVendas* colecaoVendas, Produto produtos[], int num_produtos, int periodo);
	//Esta função server para dar refresh às categorias
	void carregarCategorias(ColecaoCategorias* colecaoCategorias) {
    // Abrir o arquivo em modo de leitura
    FILE *arquivo = fopen("categorias.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: ficheiro nao encontrado\n");
        return;
    }

    // Limpar a coleção atual de categorias
    colecaoCategorias->primeira = NULL;
    colecaoCategorias->ultima = NULL;

    // Ler todas as categorias do ficheiro
    Categoria categoria;
    while (fscanf(arquivo, "%d %s", &categoria.categoria_id, categoria.categoria_nome) != EOF) {
        // Adicionar cada categoria à coleção de categorias
        adicionarCategoria(colecaoCategorias, categoria);
    }

    fclose(arquivo);
	}
	
	//Função para dar refresh aos produtos
	int carregarProdutos(Produto produtos[]) {
    FILE* arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: ficheiro nao encontrado\n");
        return 0;
    }

    int num_produtos = 0;

    while (fscanf(arquivo, "%d,%[^,],%[^,],%d,%lf,%d\n", 
              &produtos[num_produtos].id, 
              produtos[num_produtos].nome, 
              produtos[num_produtos].sku, 
              &produtos[num_produtos].quantidade, 
              &produtos[num_produtos].preco, 
              &produtos[num_produtos].id_categoria) == 6) {
        num_produtos++;
    }

    fclose(arquivo);
    return num_produtos;
}



	// Esta função serve para dar refresh aos clientes
void carregarClientes(ColecaoClientes* colecaoClientes) {
    // Abrir o arquivo em modo de leitura
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: ficheiro nao encontrado\n");
        return;
    }

    // Limpar a coleção atual de clientes
    colecaoClientes->primeiro = NULL;
    colecaoClientes->ultimo = NULL;

    // Ler todos os clientes do ficheiro
    Cliente cliente;
    while (fscanf(arquivo, "%d %s %s %s", &cliente.cliente_id, cliente.nome_cliente, cliente.nif, cliente.contato) != EOF) {
        // Adicionar cada cliente à coleção de clientes
        adicionarCliente(colecaoClientes, cliente);
    }

    fclose(arquivo);
}
	// Esta função serve para dar refresh às vendas
void carregarVendas(ColecaoVendas* colecaoVendas) {
    FILE *arquivo = fopen("vendas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: ficheiro nao encontrado\n");
        return;
    }

    liberarColecaoVendas(colecaoVendas);
    inicializarColecaoVendas(colecaoVendas);

    Venda venda;
    char buffer[MAX_CARACTERES_LINHA];  // buffer para leitura de linhas

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {  // ler uma linha do arquivo
        if (sscanf(buffer, "ID da Venda: %d", &venda.venda_id) == 1) {
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "ID do Cliente: %d", &venda.cliente_id);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "ID do Produto: %d", &venda.produto_id);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Quantidade: %d", &venda.quantidade);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Desconto: %lf", &venda.desconto);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Total: %lf", &venda.total);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Data: %s", venda.data);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Hora: %s", venda.hora);
            fgets(buffer, sizeof(buffer), arquivo);  // pular linha "===================="
            
            adicionarVenda(colecaoVendas, venda);
        }
    }

    fclose(arquivo);
}
	//função que vê se um cliente tem alguma venda
	int checkVendasCliente(ColecaoVendas* colecaoVendas,int cliente_id) {
    // Verificamos se a lista de vendas está vazia
    if (colecaoVendas->primeira == NULL) {
        printf("Nenhuma venda foi realizada ainda.\n");
        return 0; // Retorna 0 para indicar que não há vendas
    }

    // Percorremos a lista de vendas
    Venda* atual = colecaoVendas->primeira;
    while (atual != NULL) {
        // Se a venda atual foi feita para o cliente de id cliente_id
        if (atual->cliente_id == cliente_id) {
            printf("O cliente de ID %d tem vendas associadas.\n", cliente_id);
            return 1; // Retorna 1 para indicar que encontrou uma venda para o cliente
        }
        atual = atual->proximo;
    }

    // Se percorreu toda a lista e não encontrou nenhuma venda para o cliente
    printf("O cliente de ID %d não tem vendas associadas.\n", cliente_id);
    return 0; // Retorna 0 para indicar que não encontrou nenhuma venda para o cliente
}

	
	// Função para criar uma nova categoria----------
	void criarCategoria(ColecaoCategorias* colecaoCategorias) {
	    static int proximoID = 1;  // Declaração da variável proximoID
	    Categoria novaCategoria;
	    novaCategoria.categoria_id = proximoID++;
	    printf("Escreva o nome da categoria: ");
	    scanf("%s", novaCategoria.categoria_nome);
	
	 
	    adicionarCategoria(colecaoCategorias, novaCategoria);
	
	    FILE* arquivo = fopen("categorias.txt", "a");
	    if (arquivo == NULL) {
	        printf("Erro ao abrir o arquivo\n");
	        return;
	    }
	
	    fprintf(arquivo, "%d %s\n", novaCategoria.categoria_id, novaCategoria.categoria_nome);
	    fclose(arquivo);
	
	    printf("Categoria criada com sucesso!\n");
	}
	
	
// Função para editar uma categoria existente----------
void editarCategoria(ColecaoCategorias* colecaoCategorias) {
    if (colecaoCategorias->primeira == NULL) {
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
    FILE* arquivo;
    arquivo = fopen("categorias.txt.txt", "r");

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
        char* nome_categoria = malloc(sizeof(char) * 50);
        sscanf(linha, "%d %[^\n]", &categoria_id, nome_categoria);

        // Verificar se a categoria encontrada é a desejada
        if (categoria_id == id_categoria) {
            printf("Escreva o novo nome da categoria: ");
            scanf("%s", nome_categoria);

            // Fechar o arquivo para aplicar as alterações
            fclose(arquivo);

            // Reabrir o arquivo em modo de escrita e sobrescrever a linha da categoria editada
            arquivo = fopen("categorias.txt", "r+");
            if (arquivo == NULL) {
                printf("Erro ao abrir o ficheiro\n");
                return;
            }

            // Deslocar o ponteiro do arquivo para a posição da linha a ser sobrescrita
            fseek(arquivo, i, SEEK_SET);

            // Sobrescrever a linha com a categoria editada
            fprintf(arquivo, "%d %s\n", categoria_id, nome_categoria);

            fclose(arquivo);
            printf("Categoria editada com sucesso!\n");

            encontrou_categoria = 1;
            break;
        }

        i = ftell(arquivo); // Obter a posição do ponteiro do ficheiro
        free(nome_categoria);
    }

    if (!encontrou_categoria) {
        printf("Erro: categoria nao encontrada\n");
        fclose(arquivo);
    } else {
        // Após a edição, a listagem é feita novamente
        listarCategorias();
    }
}


	//Função para remover uma categoria----------
	void removerCategoria(ColecaoCategorias* colecaoCategorias) {
	    if (colecaoCategorias->primeira == NULL) {
	        printf("Erro: nenhuma categoria registada\n");
	        return;
	    }
	
	    int id_categoria;
	    printf("Escreva o ID da categoria a ser removida: ");
	
	    // Listar categorias disponiveis para vinculacao
	    printf("Categorias disponiveis:\n");
	    listarCategorias();
	
	    scanf("%d", &id_categoria);
	
	    Categoria* atual = colecaoCategorias->primeira;
	    while (atual != NULL) {
	        if (atual->categoria_id == id_categoria) {
	            // Verifica se ha produtos na categoria
	            int j;
	            for (j = 0; j < num_produtos; j++) {
	                if (produtos[j].id_categoria == id_categoria) {
	                    printf("Erro: ha produtos ligados a essa categoria\n");
	                    return;
	                }
	            }
	
	            Categoria* proximo = atual->proximo;

			// Remove a categoria da colecao
			if (atual == colecaoCategorias->primeira) {
 						   colecaoCategorias->primeira = proximo;
			} else {
 			   atual->anterior->proximo = proximo;
			}

			if (atual == colecaoCategorias->ultima) {
  			  colecaoCategorias->ultima = atual->anterior;
			} else {
  			  proximo->anterior = atual->anterior;
			}

			// Remove a categoria do ficheiro de texto
			FILE *arquivo = fopen("categorias.txt", "w");
			if (arquivo == NULL) {
  			  printf("Erro: nao foi possivel abrir o ficheiro\n");
  			  return;
				}

			Categoria* categoriaAtual = colecaoCategorias->primeira;
				while (categoriaAtual != NULL) {
  			  fprintf(arquivo, "%d %s\n", categoriaAtual->categoria_id, categoriaAtual->categoria_nome);
  			  categoriaAtual = categoriaAtual->proximo;
			}

			fclose(arquivo);

			printf("Categoria removida com sucesso!\n");
			return;
	
	        }
	
	        atual = atual->proximo;
	    }
	
	    printf("Erro: categoria nao foi encontrada\n");
	}
	
// Função para listar as categorias----------
void listarCategorias(ColecaoCategorias* colecaoCategorias) {
    if (colecaoCategorias->primeira == NULL) {
        printf("Nenhuma categoria foi encontrada.\n");
        return;
    }

    printf("ID\tNome\n");
    printf("--------------------\n");

    // Declaração da variável atual fora do loop
    Categoria* atual;
    
    // Percorrendo a lista ligada e imprimindo cada categoria
    for (atual = colecaoCategorias->primeira; atual != NULL; atual = atual->proximo) {
        printf("%d\t%s\n", atual->categoria_id, atual->categoria_nome);
    }
}


	
	// Função para criar um novo produto----------
	void criarProduto(ColecaoCategorias* colecaoCategorias) {
	    if (colecaoCategorias->primeira == NULL) {
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
	
		// Listar categorias disponiveis para vinculacao
	    printf("Categorias disponiveis:\n");
	    listarCategorias(colecaoCategorias);
	
	    // Vincular o produto a uma categoria existente
	    int id_categoria;
	    do {
	        printf("Escreva o ID da categoria a qual o produto pertence: ");
	        scanf("%d", &id_categoria);
	
	        // Verificar se o ID da categoria existe
	        Categoria* atual = colecaoCategorias->primeira;
	        while (atual != NULL) {
	            if (atual->categoria_id == id_categoria) {
	                produto.id_categoria = id_categoria;
	                produtos[num_produtos] = produto;
	                num_produtos++;
	
	                // Salvar produto no ficheiro
	                FILE* f = fopen("produtos.txt", "a");
	                if (f == NULL) {
	                    printf("Erro ao abrir o ficheiro\n");
	                    return;
	                }
	                fprintf(f, "%d,%s,%s,%d,%.2f,%d\n", produto.id, produto.nome, produto.sku, produto.quantidade, produto.preco, produto.id_categoria);
	                fclose(f);
	
	                printf("Produto criado com sucesso!\n");
	                return;
	            }
	            atual = atual->proximo;
	        }
	
	        printf("Erro: categoria nao encontrada\n");
	
	    } while (1);
	}

// Função para editar um produto existente----------
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
            int j;
            for (j = 0; j < num_produtos; j++) {
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
// Função para remover um produto existente----------
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

// Função para listar todos os produtos----------
void listarProdutos() {
    FILE *fp = fopen("produtos.txt", "r");
    if (fp == NULL) {
        printf("Erro: nao foi possivel abrir o ficheiro.\n");
        return;
    }

    char linha[MAX_CARACTERES_LINHA];
    while (fgets(linha, MAX_CARACTERES_LINHA, fp) != NULL) {
        int id, quantidade;
        double preco;
        char nome[MAX_CARACTERES_NOME], sku[MAX_CARACTERES_SKU];

        // Apenas se ambos nome e sku forem lidos corretamente a linha será considerada como produto
        if (sscanf(linha, "%d,%[^,],%[^,],%d,%lf", &id, nome, sku, &quantidade, &preco) == 5) {
            printf("ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreco: %.2f\n", id, nome, sku, quantidade, preco);
        }
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
void listarProdutosCategoria(ColecaoCategorias* colecaoCategorias) {
    if (num_categorias == 0) {
        printf("Erro: nenhuma categoria registada.\n");
        return;
    }

    int id_categoria;
    printf("Digite o ID da categoria: ");

    // Listar categorias disponíveis para vinculação
    listarCategorias(colecaoCategorias);

    scanf("%d", &id_categoria);

    // Abrir o ficheiro de produtos em modo de leitura
    FILE* arquivo_produtos = fopen("produtos.txt", "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (arquivo_produtos == NULL) {
        printf("Erro: nao foi possivel abrir o ficheiro.\n");
        return;
    }

    // Percorrer o ficheiro de produtos e imprimir os produtos pertencentes à categoria selecionada
    int id, id_categoria_lido, quantidade;
    double preco;
    char nome[MAX_CARACTERES_NOME], sku[MAX_CARACTERES_SKU];

    printf("=== PRODUTOS DA CATEGORIA ===\n");
    while (fscanf(arquivo_produtos, "%d,%[^,],%[^,],%d,%lf,%d\n", &id, nome, sku, &quantidade, &preco, &id_categoria_lido) == 6) {
        if (id_categoria_lido == id_categoria) {
            printf("ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreco: %.2f\tID Categoria: %d\n",
                   id, nome, sku, quantidade, preco, id_categoria_lido);
        }
    }

    // Fechar o ficheiro de produtos
    fclose(arquivo_produtos);
}



	// Função para listar produtos por ordem alfabética do nome----------
	int compararNomes(const void* a, const void* b) {
   	 Produto* produtoA = (Produto*)a;
 	   Produto* produtoB = (Produto*)b;
  	  return strcmp(produtoA->nome, produtoB->nome);
	}

	// Função para listar os produtos por ordem alfabética do nome
	void listarProdutosPorNome() {
 	   if (num_produtos == 0) {
  	      printf("Erro: nenhum produto registado.\n");
  	      return;
  	  }

  	  // Ordenar os produtos por nome
 		  qsort(produtos, num_produtos, sizeof(Produto), compararNomes);

  		  printf("=== LISTA DE PRODUTOS POR ORDEM ALFABÉTICA DO NOME ===\n");
  		  int i;
   		 for (i= 0; i < num_produtos; i++) {
  		      printf("ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreço: %.2f\tID Categoria: %d\n",
  	          produtos[i].id, produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco, produtos[i].id_categoria);
  	  }
	}


	// Função de comparação para ordenação descendente dos preços dos produtos----------
	int compararPrecosDesc(const void* a, const void* b) {
  	  Produto* produtoA = (Produto*)a;
  	  Produto* produtoB = (Produto*)b;
 	   if (produtoA->preco < produtoB->preco)
 	       return 1;
	    else if (produtoA->preco > produtoB->preco)
 	       return -1;
	    else
  	      return 0;
	}

	// Função para listar os produtos por ordem descendente de preço
	void listarProdutosPorPrecoDesc() {
 	   if (num_produtos == 0) {
 	       printf("Erro: nenhum produto registado.\n");
 	       return;
	    }

 	   // Ordenar os produtos por preço descendente
 	   qsort(produtos, num_produtos, sizeof(Produto), compararPrecosDesc);
	
	    printf("=== LISTA DE PRODUTOS POR ORDEM DESCENDENTE DE PREÇO ===\n");
	    int i;
 	   for (i = 0; i < num_produtos; i++) {
  	      printf("ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreço: %.2f\tID Categoria: %d\n",
  	             produtos[i].id, produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco, produtos[i].id_categoria);
  	  }
	}

// Função para colocar um produto sem stock----------
void colocarProdutoSemStock() {
    if (num_produtos == 0) {
        printf("Erro: nenhum produto registado.\n");
        return;
    }

    int id_produto;
    printf("Digite o ID do produto a ser colocado sem stock: ");
    // Listar produtos disponíveis
    listarProdutos();
    scanf("%d", &id_produto);

    int i;
    for (i = 0; i < num_produtos; i++) {
        // Verificar se o produto existe na lista de produtos
        if (produtos[i].id == id_produto) {
            produtos[i].quantidade = 0;

            // Atualizar as informações do produto no ficheiro
            FILE* arquivo = fopen("produtos.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o ficheiro.\n");
                return;
            }
            int j;
            for (j = 0; j < num_produtos; j++) {
                fprintf(arquivo, "%d,%s,%s,%d,%.2f,%d\n",
                        produtos[j].id, produtos[j].nome, produtos[j].sku,
                        produtos[j].quantidade, produtos[j].preco, produtos[j].id_categoria);
            }
            fclose(arquivo);

            printf("Produto colocado sem stock com sucesso!\n");
            return;
        }
    }

    printf("Erro: produto nao encontrado.\n");
}


// Função para gerar um relatório de todo o inventário ordenado por categoria de produto----------
void gerarRelatorioInventario(ColecaoCategorias* colecaoCategorias) {
    FILE* arquivo_relatorio = fopen("relatorio_inventario.txt", "w");
    if (arquivo_relatorio == NULL) {
        printf("Erro ao criar o ficheiro do relatório.\n");
        return;
    }

    // Percorrer todas as categorias
    Categoria* categoria_atual = colecaoCategorias->primeira;
    while (categoria_atual != NULL) {
        fprintf(arquivo_relatorio, "Categoria: %s\n", categoria_atual->categoria_nome);

        // Percorrer todos os produtos da categoria atual
        int i;
        for (i = 0; i < num_produtos; i++) {
            if (produtos[i].id_categoria == categoria_atual->categoria_id) {
                fprintf(arquivo_relatorio, "ID: %d\tNome: %s\tSKU: %s\tQuantidade: %d\tPreço: %.2f\n",
                        produtos[i].id, produtos[i].nome, produtos[i].sku,
                        produtos[i].quantidade, produtos[i].preco);
            }
        }

        fprintf(arquivo_relatorio, "\n");

        categoria_atual = categoria_atual->proximo;
    }

    fclose(arquivo_relatorio);

    printf("Relatório de inventario gerado com sucesso.\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


// Função para criar um novo cliente----------
void criarCliente(ColecaoClientes* colecaoClientes) {
    static int proximoID = 1;  // Declaração da variável proximoID
    Cliente novoCliente;
    novoCliente.cliente_id = proximoID++;
    printf("Escreva o nome do cliente: ");
    scanf("%s", novoCliente.nome_cliente); // Ler o nome do cliente. Isso não lê espaços.
    getchar(); // Consumir o '\n' deixado por scanf.
    printf("Nome do cliente lido: %s\n", novoCliente.nome_cliente); // Debug line
    printf("Escreva o NIF do cliente: ");
    fgets(novoCliente.nif, sizeof(novoCliente.nif), stdin);
    limparBuffer();
    novoCliente.nif[strcspn(novoCliente.nif, "\n")] = 0; // remove newline added by fgets
    printf("Escreva o contato do cliente: ");
    fgets(novoCliente.contato, sizeof(novoCliente.contato), stdin);
    limparBuffer();
    novoCliente.contato[strcspn(novoCliente.contato, "\n")] = 0; // remove newline added by fgets

    adicionarCliente(colecaoClientes, novoCliente);

    FILE* arquivo = fopen("clientes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fprintf(arquivo, "%d %s %s %s\n", novoCliente.cliente_id, novoCliente.nome_cliente, novoCliente.nif, novoCliente.contato);
    fclose(arquivo);

    printf("Cliente criado com sucesso!\n");
}


	//Função para editar os dados de um cliente----------
	void editarCliente(ColecaoClientes* colecaoClientes) {
    if (colecaoClientes->primeiro == NULL) {
        printf("Erro: nenhum cliente registado\n");
        return;
    }

    int id_cliente;
    printf("Escreva o ID do cliente a ser editado: ");

    // Listar clientes disponíveis
    printf("Clientes disponiveis:\n");
    listarClientes(colecaoClientes);

    scanf("%d", &id_cliente);

    // Abrir ficheiro de texto em modo de leitura
    FILE* arquivo;
    arquivo = fopen("clientes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }

    int encontrou_cliente = 0;
    int i = 0;

    // Ler cada linha do ficheiro até encontrar o cliente desejado
    while (!feof(arquivo)) {
        char linha[100];
        fgets(linha, 100, arquivo);

        // Extrair os dados da linha
        int cliente_id;
        char* nome_cliente = malloc(sizeof(char) * 50);
        sscanf(linha, "%d %[^\n]", &cliente_id, nome_cliente);

        // Verificar se o cliente encontrado é o desejado
        if (cliente_id == id_cliente) {
            printf("Escreva o novo nome do cliente: ");
            scanf("%s", nome_cliente);

            // Fechar o arquivo para aplicar as alterações
            fclose(arquivo);

            // Reabrir o arquivo em modo de escrita e sobrescrever a linha do cliente editado
            arquivo = fopen("clientes.txt", "r+");
            if (arquivo == NULL) {
                printf("Erro ao abrir o ficheiro\n");
                return;
            }

            // Deslocar o ponteiro do arquivo para a posição da linha a ser sobrescrita
            fseek(arquivo, i, SEEK_SET);

            // Sobrescrever a linha com o cliente editado
            fprintf(arquivo, "%d %s\n", cliente_id, nome_cliente);

            fclose(arquivo);
            printf("Cliente editado com sucesso!\n");

            encontrou_cliente = 1;
            break;
        }

        i = ftell(arquivo); // Obter a posição do ponteiro do ficheiro
        free(nome_cliente);
    }

    if (!encontrou_cliente) {
        printf("Erro: cliente nao encontrado\n");
        fclose(arquivo);
    } else {
        // Após a edição, a listagem é feita novamente
        listarClientes(colecaoClientes);
    }
}

		//Função que remove um cliente----------
void removerCliente(ColecaoClientes* colecaoClientes, ColecaoVendas* colecaoVendas) {
    if (colecaoClientes->primeiro == NULL) {
        printf("Erro: nenhum cliente registado\n");
        return;
    }

    int id_cliente;
    printf("Escreva o ID do cliente a ser removido: ");

    // Listar clientes disponiveis
    printf("Clientes disponiveis:\n");
    listarClientes(colecaoClientes);

    scanf("%d", &id_cliente);

    Cliente* atual = colecaoClientes->primeiro;
    while (atual != NULL) {
        if (atual->cliente_id == id_cliente) {
            // Verifica se há vendas para o cliente
            // ** Aqui você precisa de implementar uma função checkVendasCliente(id_cliente) **
            if (checkVendasCliente(colecaoVendas, id_cliente)) {
      		  printf("Erro: ha vendas ligadas a este cliente\n");
      		  return;
  			}

            Cliente* proximo = atual->proximo;

            // Remove o cliente da colecao
            if (atual == colecaoClientes->primeiro) {
                colecaoClientes->primeiro = proximo;
            } else {
                atual->anterior->proximo = proximo;
            }

            if (atual == colecaoClientes->ultimo) {
                colecaoClientes->ultimo = atual->anterior;
            } else {
                proximo->anterior = atual->anterior;
            }

            // Remove o cliente do ficheiro de texto
            FILE *arquivo = fopen("clientes.txt", "w");
            if (arquivo == NULL) {
                printf("Erro: não foi possivel abrir o ficheiro\n");
                return;
            }

            Cliente* clienteAtual = colecaoClientes->primeiro;
            while (clienteAtual != NULL) {
                fprintf(arquivo, "%d %s %s %s\n", clienteAtual->cliente_id, clienteAtual->nome_cliente, clienteAtual->nif, clienteAtual->contato);
                clienteAtual = clienteAtual->proximo;
            }

            fclose(arquivo);

            printf("Cliente removido com sucesso!\n");
            return;

        }

        atual = atual->proximo;
    }

    printf("Erro: cliente nao foi encontrado\n");
}

void copiarColecaoClientes(ColecaoClientes* original, ColecaoClientes* copia) {
    // Inicializar a coleção de cópia
    inicializarColecaoClientes(copia);

    // Iterar sobre a coleção original e adicionar cada cliente à coleção de cópia
    Cliente* atual = original->primeiro;
    while (atual != NULL) {
        // Cria um novo cliente com as mesmas informações do cliente atual
        Cliente novoCliente;
        novoCliente.cliente_id = atual->cliente_id;
        strcpy(novoCliente.nome_cliente, atual->nome_cliente);
        strcpy(novoCliente.nif, atual->nif);
        strcpy(novoCliente.contato, atual->contato);

        // Adiciona o novo cliente à coleção de cópia
        adicionarCliente(copia, novoCliente);

        // Passar para o próximo cliente na coleção original
        atual = atual->proximo;
    }
}


	//Função que lista os clientes por ordem alfabética do nome----------
void listarClientesPorNome(ColecaoClientes* colecaoClientes) {
    if(colecaoClientes->primeiro == NULL) {
        printf("Erro: Nenhum cliente registado\n");
        return;
    }
    
    // Cria uma cópia da colecao de clientes para ordenar sem modificar a original
    ColecaoClientes copiaColecao;
    copiarColecaoClientes(colecaoClientes, &copiaColecao);
    
    Cliente* clienteAtual;
    Cliente* proximoCliente;
    for(clienteAtual = copiaColecao.primeiro; clienteAtual != NULL; clienteAtual = clienteAtual->proximo) {
        for(proximoCliente = clienteAtual->proximo; proximoCliente != NULL; proximoCliente = proximoCliente->proximo) {
            // Se o nome do clienteAtual for maior do que o do proximoCliente, troca-os
            if(strcmp(clienteAtual->nome_cliente, proximoCliente->nome_cliente) > 0) {
                Cliente temp = *clienteAtual;
                *clienteAtual = *proximoCliente;
                *proximoCliente = temp;
            }
        }
    }
    
    // Agora a cópia da colecao de clientes está ordenada alfabeticamente pelo nome do cliente
    // Então podemos imprimir os clientes
    for(clienteAtual = copiaColecao.primeiro; clienteAtual != NULL; clienteAtual = clienteAtual->proximo) {
        printf("%s\n", clienteAtual->nome_cliente);
    }
    
    // Libera a memória alocada para a cópia da coleção de clientes
    liberarColecaoClientes(&copiaColecao);
}


//Função que apresenta os dados de um cliente pelo seu NIF ----------
void apresentarInfoClientePorNIF(ColecaoClientes* colecaoClientes) {
    if(colecaoClientes->primeiro == NULL) {
        printf("Erro: Nenhum cliente registado\n");
        return;
    }

    char nif[MAX_NIF + 1];
    printf("Digite o NIF do cliente: ");
    scanf("%s", nif);

    Cliente* clienteAtual;
    for(clienteAtual = colecaoClientes->primeiro; clienteAtual != NULL; clienteAtual = clienteAtual->proximo) {
        printf("Comparando '%s' com '%s'\n", clienteAtual->nif, nif);  // Imprime os NIFs que estão sendo comparados
        if(strcmp(clienteAtual->nif, nif) == 0) {
            // Encontrou o cliente com o NIF fornecido, então imprime as informações
            printf("Nome: %s\n", clienteAtual->nome_cliente);
            printf("NIF: %s\n", clienteAtual->nif);
            // Adicione aqui qualquer outra informação que você queira imprimir

            return;
        }
    }

    printf("Erro: Nenhum cliente com o NIF fornecido foi encontrado\n");
}


//Função para listar os clientes----------

void listarClientes(ColecaoClientes* colecaoClientes) {
    if (colecaoClientes->primeiro == NULL) {
        printf("Nenhum cliente registado.\n");
        return;
    }

    Cliente* atual = colecaoClientes->primeiro;
    printf("Lista de clientes:\n");

    // Iterar sobre a lista de clientes e imprimir as informações de cada um
    while (atual != NULL) {
        printf("ID: %d\n", atual->cliente_id);
        printf("Nome: %s\n", atual->nome_cliente);
        printf("NIF: %s\n", atual->nif);
        printf("Contato: %s\n", atual->contato);
        printf("-------------------\n");
        atual = atual->proximo;
    }
}

//função que aninomiza os dados de um cliente
void anonimizarDadosCliente(ColecaoClientes* colecaoClientes) {
    if(colecaoClientes->primeiro == NULL) {
        printf("Erro: Nenhum cliente registado\n");
        return;
    }

    int id_cliente;
    printf("Digite o ID do cliente a ser anonimizado: ");
    scanf("%d", &id_cliente);

    Cliente* clienteAtual;
    for(clienteAtual = colecaoClientes->primeiro; clienteAtual != NULL; clienteAtual = clienteAtual->proximo) {
        if(clienteAtual->cliente_id == id_cliente) {
            // Encontrou o cliente com o ID fornecido, então substitui os dados por valores genéricos
            strcpy(clienteAtual->nome_cliente, "Anonimo");
            strcpy(clienteAtual->nif, "000000000");  // Assumindo que NIF tem 9 dígitos
            strcpy(clienteAtual->contato, "000000000");  // Assumindo que o contato tem 9 dígitos

            printf("Dados do cliente com ID %d foram anonimizados.\n", id_cliente);

            // Reabra o arquivo em modo de gravação para atualizar os dados anonimizados
            FILE* arquivo = fopen("clientes.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo\n");
                return;
            }

            // Percorra a lista de clientes e reescreva todos os dados no arquivo
            Cliente* clienteAtualParaEscrever;
            for(clienteAtualParaEscrever = colecaoClientes->primeiro; clienteAtualParaEscrever != NULL; clienteAtualParaEscrever = clienteAtualParaEscrever->proximo) {
                fprintf(arquivo, "%d %s %s %s\n", clienteAtualParaEscrever->cliente_id, clienteAtualParaEscrever->nome_cliente, clienteAtualParaEscrever->nif, clienteAtualParaEscrever->contato);
            }

            fclose(arquivo);

            return;
        }
    }

    printf("Erro: Nenhum cliente com o ID fornecido foi encontrado\n");
}



	//Função para realizar uma venda----------
int venda_id_counter = 0;	
void realizarVenda(ColecaoVendas* colecaoVendas, ColecaoCategorias* colecaoCategorias, ColecaoClientes* colecaoClientes,
				   Produto produtos[], int num_produtos) {
    Venda novaVenda;
    // Listar produtos disponíveis para edição
    printf("Produtos disponiveis:\n");
    listarProdutos();	
    printf("Numero de produtos: %d\n", num_produtos);

    // Solicite ao usuário o ID do produto
    printf("Digite o ID do produto: ");
    scanf("%d", &novaVenda.produto_id);
    

    // Verifique se o produto existe
    Produto* produto = NULL;
    int i = 0;
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].id == novaVenda.produto_id) {
            produto = &produtos[i];
            break;
        }
    }

    if (produto == NULL) {
        printf("Erro: Produto nao encontrado.\n");
        return;
    }

    // Solicite ao usuário o ID do cliente
    printf("Digite o ID do cliente: ");
    scanf("%d", &novaVenda.cliente_id);

    // Verifique se o cliente existe
    Cliente* clienteAtual = colecaoClientes->primeiro;
    while (clienteAtual != NULL && clienteAtual->cliente_id != novaVenda.cliente_id) {
        clienteAtual = clienteAtual->proximo;
    }

    if (clienteAtual == NULL) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    // Solicite ao usuário a quantidade do produto
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novaVenda.quantidade);

    // Verifique se a quantidade é válida
    if (novaVenda.quantidade > produto->quantidade) {
        printf("Erro: Quantidade insuficiente em stock.\n");
        return;
    }

    // Atualize a quantidade de stock do produto
    produto->quantidade -= novaVenda.quantidade;
    // Abrir o arquivo "produtos.txt" em modo de escrita
	FILE* arquivoProdutos = fopen("produtos.txt", "w");
	if (arquivoProdutos == NULL) {
    printf("Erro ao abrir o arquivo produtos.txt\n");
    return;
	}

	// Escrever os dados atualizados dos produtos no arquivo
	for (i = 0; i < num_produtos; i++) {
    fprintf(arquivoProdutos, "%d,%s,%s,%d,%.2f,%d\n",
            produtos[i].id, produtos[i].nome, produtos[i].sku,
            produtos[i].quantidade, produtos[i].preco, produtos[i].id_categoria);
	}

	// Fechar o ficheiro
	fclose(arquivoProdutos);

    // Pergunte ao utilizador sobre o desconto
    printf("Digite o desconto aplicado: ");
    scanf("%lf", &novaVenda.desconto);

    // Calcular total
    novaVenda.total = produto->preco * novaVenda.quantidade - novaVenda.desconto;

    // Preencha a data e a hora da venda
    time_t agora = time(NULL);
    struct tm* tempoAgora = localtime(&agora);
    strftime(novaVenda.data, sizeof(novaVenda.data), "%Y-%m-%d", tempoAgora);
    strftime(novaVenda.hora, sizeof(novaVenda.hora), "%H:%M", tempoAgora);

    // Adicionar a nova venda à coleção
    adicionarVenda(colecaoVendas, novaVenda);

    // Abrir o ficheiro "vendas.txt" em modo de escrita
    FILE* ficheiro = fopen("vendas.txt", "a");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro vendas.txt\n");
        return;
    }
	 // Gerar um ID único para a venda
    novaVenda.venda_id = ++venda_id_counter;
	 // Adicionar a nova venda à coleção
    adicionarVenda(colecaoVendas, novaVenda);
	
    // Escrever os dados da venda no ficheiro
    fprintf(ficheiro, "ID da Venda: %d\n", novaVenda.venda_id);
    fprintf(ficheiro, "ID do Cliente: %d\n", novaVenda.cliente_id);
    fprintf(ficheiro, "ID do Produto: %d\n", novaVenda.produto_id);
    fprintf(ficheiro, "Quantidade: %d\n", novaVenda.quantidade);
    fprintf(ficheiro, "Desconto: %.2f\n", novaVenda.desconto);
    fprintf(ficheiro, "Total: %.2f\n", novaVenda.total);
    fprintf(ficheiro, "Data: %s\n", novaVenda.data);
    fprintf(ficheiro, "Hora: %s\n", novaVenda.hora);
    fprintf(ficheiro, "====================\n");

    // Fechar o ficheiro
    fclose(ficheiro);

    printf("Venda registada com sucesso.\n");
}





void listarVendasPorHora(ColecaoVendas* colecaoVendas) {
    // Verificar se há vendas na coleção
    if (colecaoVendas->primeira == NULL) {
        printf("Nenhuma venda registada.\n");
        return;
    }

    // Contar o número de vendas
    int numVendas = 0;
    Venda* vendaAtual = colecaoVendas->primeira;
    while (vendaAtual != NULL) {
        numVendas++;
        vendaAtual = vendaAtual->proximo;
    }

    // Alocar memória para o array temporário de vendas
    Venda** vendasArray = (Venda**)malloc(numVendas * sizeof(Venda*));
    if (vendasArray == NULL) {
        printf("Erro: falha na alocaçao de memoria.\n");
        return;
    }

    // Copiar as vendas para o array temporário
    int i = 0;
    vendaAtual = colecaoVendas->primeira;
    while (vendaAtual != NULL) {
        vendasArray[i] = vendaAtual;
        i++;
        vendaAtual = vendaAtual->proximo;
    }

    // Ordenar as vendas em ordem ascendente da hora
    int k;
    int j;
    for (k = 0; k < numVendas - 1; k++) {
        for (j = 0; j < numVendas - k - 1; j++) {
            if (strcmp(vendasArray[j]->hora, vendasArray[j + 1]->hora) > 0) {
                Venda* temp = vendasArray[j];
                vendasArray[j] = vendasArray[j + 1];
                vendasArray[j + 1] = temp;
            }
        }
    }

    // Mostrar as vendas em ordem ascendente da hora
    printf("=== LISTAGEM DE VENDAS POR HORA ===\n");
    int a;
    for (a = 0; a < numVendas; a++) {
        Venda* venda = vendasArray[a];
        printf("ID da Venda: %d\n", venda->venda_id);
        printf("ID do Cliente: %d\n", venda->cliente_id);
        printf("ID do Produto: %d\n", venda->produto_id);
        printf("Quantidade: %d\n", venda->quantidade);
        printf("Desconto: %.2f\n", venda->desconto);
        printf("Total: %.2f\n", venda->total);
        printf("Data: %s\n", venda->data);
        printf("Hora: %s\n", venda->hora);
        printf("====================\n");
    }

    // Liberar a memória alocada para o array de vendas
    free(vendasArray);
}

//Função para listar os produtos mais vendidos hoje
void listarProdutosMaisVendidosHoje(ColecaoVendas* colecaoVendas) {
    // Obter a data de hoje
    time_t agora = time(NULL);
    struct tm* tempoAgora = localtime(&agora);
    char dataHoje[11];
    strftime(dataHoje, sizeof(dataHoje), "%Y-%m-%d", tempoAgora);

    // Criar um array para armazenar a quantidade vendida de cada produto
    // O índice do array corresponde ao ID do produto e o valor armazenado é a quantidade vendida
    int* quantidadeVendida = (int*)malloc(num_produtos * sizeof(int));
    if (quantidadeVendida == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        return;
    }
    memset(quantidadeVendida, 0, num_produtos * sizeof(int));

    // Percorrer as vendas e atualizar o array com as quantidades vendidas de cada produto hoje
    Venda* vendaAtual = colecaoVendas->primeira;
    while (vendaAtual != NULL) {
        if (strcmp(vendaAtual->data, dataHoje) == 0) {
            quantidadeVendida[vendaAtual->produto_id - 1] += vendaAtual->quantidade;
        }
        vendaAtual = vendaAtual->proximo;
    }

    // Verificar se há produtos vendidos hoje
    int numProdutosVendidos = 0;
    int i;
    for (i = 0; i < num_produtos; i++) {
        if (quantidadeVendida[i] > 0) {
            numProdutosVendidos++;
        }
    }
    if (numProdutosVendidos == 0) {
        printf("Nenhum produto vendido hoje.\n");
        free(quantidadeVendida);
        return;
    }

    // Mostrar os produtos mais vendidos hoje em ordem decrescente da quantidade vendida
    printf("=== PRODUTOS MAIS VENDIDOS HOJE ===\n");
    while (numProdutosVendidos > 0) {
        int maxQuantidade = -1;
        int maxIndex = -1;
        int o;
        for (o = 0; o < num_produtos; o++) {
            if (quantidadeVendida[i] > maxQuantidade) {
                maxQuantidade = quantidadeVendida[o];
                maxIndex = o;
            }
        }

        if (maxIndex >= 0) {
            printf("ID do Produto: %d\n", maxIndex + 1);
            printf("Quantidade Vendida: %d\n", maxQuantidade);
            printf("====================\n");

            quantidadeVendida[maxIndex] = -1;
            numProdutosVendidos--;
        }
    }

    // Liberar a memória alocada
    free(quantidadeVendida);
}
		//Função que  mostra as vendas por data específica
void listarVendasPorDataEspecifica(ColecaoVendas* colecaoVendas, const char* data) {
    // Percorrer as vendas e listar as vendas da data específica
    Venda* vendaAtual = colecaoVendas->primeira;
    int encontrouVendas = 0;
    while (vendaAtual != NULL) {
        if (strcmp(vendaAtual->data, data) == 0) {
            // Mostrar os detalhes da venda
            printf("ID da Venda: %d\n", vendaAtual->venda_id);
            printf("ID do Cliente: %d\n", vendaAtual->cliente_id);
            printf("ID do Produto: %d\n", vendaAtual->produto_id);
            printf("Quantidade: %d\n", vendaAtual->quantidade);
            printf("Desconto: %.2f\n", vendaAtual->desconto);
            printf("Total: %.2f\n", vendaAtual->total);
            printf("Data: %s\n", vendaAtual->data);
            printf("Hora: %s\n", vendaAtual->hora);
            printf("====================\n");

            encontrouVendas = 1;
        }
        vendaAtual = vendaAtual->proximo;
    }

    // Verificar se foram encontradas vendas na data específica
    if (!encontrouVendas) {
        printf("Nenhuma venda encontrada na data especificada.\n");
    }
}
		//Função que  lista as vendas por data de dia ou mês
void listarVendasPorData(ColecaoVendas* colecaoVendas) {
    // Função para verificar se a data inserida é válida
    int verificarDataValida(const char* data) {
    int dia, mes, ano;
    if (sscanf(data, "%d-%d-%d", &ano, &mes, &dia) != 3) {
        return 0;  // Data inválida
    }

    // Verificar se os valores são válidos para dia, mês e ano
    if (ano < 1900 || ano > 9999 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0;  // Data inválida
    }

    return 1;  // Data válida
}

    
    // Obter a data de hoje
    time_t agora = time(NULL);
    struct tm* tempoAgora = localtime(&agora);
    char dataHoje[11];
    strftime(dataHoje, sizeof(dataHoje), "%Y-%m-%d", tempoAgora);

    // Perguntar ao utilizador se deseja listar as vendas de hoje ou inserir uma data específica
    int opcao;
    printf("Deseja listar as vendas de hoje ou de uma data específica?\n");
    printf("1. Hoje\n");
    printf("2. Data especifica\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);

    if (opcao == 2) {
        // Solicitar ao utilizador uma data específica
        char data[11];
        printf("Digite a data (no formato YYYY-MM-DD): ");
        scanf("%s", data);

        // Verificar se a data inserida é válida
        int dataValida = verificarDataValida(data);
        if (!dataValida) {
            printf("Data inválida.\n");
            return;
        }

        // Chamar a função para listar as vendas na data específica
        listarVendasPorDataEspecifica(colecaoVendas, data);
    } else {
        // Chamar a função para listar as vendas de hoje
        listarVendasPorDataEspecifica(colecaoVendas, dataHoje);
    }
}

char *strptime(const char *s, const char *format, struct tm *tm) {
    int year, month, day;
    sscanf(s, "%d-%d-%d", &year, &month, &day);
    tm->tm_year = year - 1900;  // Anos desde 1900
    tm->tm_mon = month - 1;     // Meses desde janeiro [0-11]
    tm->tm_mday = day;          // Dia do mês [1-31]
    return NULL;  // Retorna NULL em caso de falha
}

		//Função que  apresenta os produtos mais rentaveis
void listarProdutosMaisRentaveis(ColecaoVendas* colecaoVendas, Produto produtos[], int num_produtos, int periodo) {
    double receitas[MAX_PRODUTOS] = {0};
    Venda* vendaAtual = colecaoVendas->primeira;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Calcular a receita total para cada produto
    while (vendaAtual != NULL) {
        struct tm tm_venda;
        strptime(vendaAtual->data, "%Y-%m-%d", &tm_venda);
        
        // Checar se a venda aconteceu hoje ou neste mês
        if ((periodo == 1 && tm.tm_year == tm_venda.tm_year && tm.tm_yday == tm_venda.tm_yday) ||
            (periodo == 2 && tm.tm_year == tm_venda.tm_year && tm.tm_mon == tm_venda.tm_mon)) {
            // Procurar o produto da venda
            int i;
            for (i = 0; i < num_produtos; i++) {
                if (produtos[i].id == vendaAtual->produto_id) {
                    // Adicionar o total da venda à receita do produto
                    receitas[i] += vendaAtual->total;
                    break;
                }
            }
        }
        vendaAtual = vendaAtual->proximo;
    }

    // Imprimir os produtos e suas respectivas receitas
    printf("Produtos mais rentaveis:\n");
    int i;
    for (i = 0; i < num_produtos; i++) {
        if (receitas[i] > 0) {
            printf("Produto: %s, Receita: %.2lf\n", produtos[i].nome, receitas[i]);
        }
    }
}
		//Função que  apresenta as vendas por tipo de produto
void vendasPorTipoProduto(ColecaoVendas* colecaoVendas, Produto produtos[], int num_produtos, int id_produto, int periodo) {
    int vendas = 0;
    Venda* vendaAtual = colecaoVendas->primeira;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Calcular o total de vendas para o produto escolhido
    while (vendaAtual != NULL) {
        struct tm tm_venda;
        strptime(vendaAtual->data, "%Y-%m-%d", &tm_venda);
        
        // Verificar se a venda é do produto escolhido e se aconteceu hoje ou neste mês
        if (vendaAtual->produto_id == id_produto &&
           ((periodo == 1 && tm.tm_year == tm_venda.tm_year && tm.tm_yday == tm_venda.tm_yday) ||
           (periodo == 2 && tm.tm_year == tm_venda.tm_year && tm.tm_mon == tm_venda.tm_mon))) {
            vendas += vendaAtual->quantidade;
        }
        vendaAtual = vendaAtual->proximo;
    }

    // Imprimir o total de vendas do produto
    int i;
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].id == id_produto) {
            printf("Total de vendas do produto %s: %d\n", produtos[i].nome, vendas);
            break;
        }
    }
}
	//Função que gera o relatório de contas do mês, ou do dia
	void gerarRelatorioContas(ColecaoVendas* colecaoVendas, Produto produtos[], int num_produtos, int periodo) {
    Venda* vendaAtual = colecaoVendas->primeira;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *file;

    // Nome do arquivo baseado no período
    if (periodo == 1) {
        file = fopen("relatorio_contas_dia.txt", "w");
    } else if (periodo == 2) {
        file = fopen("relatorio_contas_mes.txt", "w");
    } else {
        printf("Periodo invalido.");
        return;
    }

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    // Percorrer todas as vendas e gravar as que correspondem ao período escolhido no arquivo
    while (vendaAtual != NULL) {
        struct tm tm_venda;
        strptime(vendaAtual->data, "%Y-%m-%d", &tm_venda);
        
        // Verificar se a venda aconteceu hoje ou neste mês
        if ((periodo == 1 && tm.tm_year == tm_venda.tm_year && tm.tm_yday == tm_venda.tm_yday) ||
            (periodo == 2 && tm.tm_year == tm_venda.tm_year && tm.tm_mon == tm_venda.tm_mon)) {
            // Procurar o produto da venda
            int i;
            for (i = 0; i < num_produtos; i++) {
                if (produtos[i].id == vendaAtual->produto_id) {
                    // Gravar os detalhes da venda no arquivo
                    fprintf(file, "Produto: %s, Quantidade: %d, Total: %.2lf\n", produtos[i].nome, vendaAtual->quantidade, vendaAtual->total);
                    break;
                }
            }
        }
        vendaAtual = vendaAtual->proximo;
    }

    fclose(file);
}
		//Função que gera um relatório para produtos com stock baixo
void gerarRelatorioBaixoStock(Produto produtos[], int num_produtos, ColecaoVendas* colecaoVendas) {
    FILE* f = fopen("relatorio_baixo_stock.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo relatorio_baixo_stock.txt para escrita\n");
        return;
    }

    fprintf(f, "=== Relatorio de Produtos com Baixo Stock ===\n");

    time_t t = time(NULL);
    struct tm* tm_atual = localtime(&t);
	int i;
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].quantidade < 5) {
            // Contabilizar as vendas do ultimo mes para este produto
            int vendas_no_ultimo_mes = 0;
            Venda* vendaAtual = colecaoVendas->primeira;
            while (vendaAtual != NULL) {
                struct tm tm_venda;
                strptime(vendaAtual->data, "%Y-%m-%d", &tm_venda);

                // Verificar se a venda é deste produto e do ultimo mes
                if (vendaAtual->produto_id == produtos[i].id && 
                    tm_atual->tm_year == tm_venda.tm_year && 
                    tm_atual->tm_mon == tm_venda.tm_mon) {
                    vendas_no_ultimo_mes += vendaAtual->quantidade;
                }

                vendaAtual = vendaAtual->proximo;
            }

            fprintf(f, "ID: %d Nome: %s SKU: %s Quantidade: %d Vendas no ultimo mes: %d\n", 
                produtos[i].id, produtos[i].nome, produtos[i].sku, produtos[i].quantidade, vendas_no_ultimo_mes);
        }
    }

    fclose(f);
}


void gerirProdutos() {
    int opcao_menu_gerir_produtos;
    ColecaoCategorias colecaoCategorias;
    inicializarColecao(&colecaoCategorias);
    carregarCategorias(&colecaoCategorias);
    num_produtos = carregarProdutos(produtos);


    do {
        system("cls");
        printf("=== MENU GERIR PRODUTOS ===\n");
        printf("1. Gerir Categorias de Produtos\n");
        printf("2. Gerir Produtos\n");
        printf("3. Listar Produtos por ordem alfabetica do nome\n");
        printf("4. Listar Produtos por ordem descendente de preço\n");
        printf("5. Listar Categoria de Produtos e respetivos produtos\n");
        printf("6. Colocar um Produto sem stock\n");
        printf("7. Gerar um relatorio de todo o inventario ordenado por categoria de produto\n");
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
                 listarProdutosPorNome();
                break;
            case 4:
                 listarProdutosPorPrecoDesc();
                break;
            case 5:
                 listarProdutosCategoria(&colecaoCategorias);
                break;
            case 6:
                 colocarProdutoSemStock();
                break;
            case 7:
                 gerarRelatorioInventario(&colecaoCategorias);
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
    ColecaoCategorias colecaoCategorias;
    inicializarColecao(&colecaoCategorias);
    carregarCategorias(&colecaoCategorias);
    num_produtos = carregarProdutos(produtos);

    do {
        system("cls");
        printf("=== MENU GERIR PRODUTOS ===\n");
        printf("1. Criar Produto\n");
        printf("2. Editar Produto\n");
        printf("3. Remover Produto\n");
        printf("4. Listar Produtos\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_produtos);

        switch (opcao_menu_gerir_produtos) {
            case 1:
   				criarProduto(&colecaoCategorias);
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
    carregarCategorias(&colecaoCategorias);

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
                editarCategoria(&colecaoCategorias);
                break;
           case 3:
                removerCategoria(&colecaoCategorias); 
                break; 
            case 4:
                listarCategorias(&colecaoCategorias);
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

void gerirClientes() {
    int opcao_menu_gerir_clientes;
    ColecaoClientes colecaoClientes;
    inicializarColecaoClientes(&colecaoClientes);
    carregarClientes(&colecaoClientes);
    ColecaoVendas colecaoVendas;
	inicializarColecaoVendas(&colecaoVendas);
	carregarVendas(&colecaoVendas);

    do {
        system("cls");
        printf("=== MENU GERIR CLIENTES ===\n");
        printf("1. Gerir Clientes\n");
        printf("2. Listar Clientes por ordem alfabetica do nome\n");
        printf("3. Apresentar informacoes do cliente pelo NIF\n");
        printf("4. Anonimizar dados do cliente (RGPD)\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_clientes);

        switch (opcao_menu_gerir_clientes) {
            case 1:
                gerirClientesSubmenu(&colecaoClientes, &colecaoVendas);
                break;
            case 2:
                listarClientesPorNome(&colecaoClientes);  
                break;
            case 3:
                apresentarInfoClientePorNIF(&colecaoClientes);  
                break;
            case 4:
                anonimizarDadosCliente(&colecaoClientes);  
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    } while (opcao_menu_gerir_clientes != 0);
}


void gerirClientesSubmenu(ColecaoClientes* colecaoClientes, ColecaoVendas* colecaoVendas) {
    int opcao_menu_gerir_clientes;
      carregarClientes(colecaoClientes);
    do {
        system("cls");
        printf("=== SUBMENU GERIR CLIENTES ===\n");
        printf("1. Criar Cliente\n");
        printf("2. Editar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("4. Listar Clientes\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_clientes);

        switch (opcao_menu_gerir_clientes) {
            case 1:
   				criarCliente(colecaoClientes);
   		        break;
            case 2:
                editarCliente(colecaoClientes);
                break;
            case 3:
                removerCliente(colecaoClientes,colecaoVendas);
                break;
            case 4:
                listarClientes(colecaoClientes);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    } while (opcao_menu_gerir_clientes != 0);
}



void gerirVendas() {
    int opcao_menu_gerir_vendas;
    ColecaoVendas colecaoVendas;
    ColecaoCategorias colecaoCategorias;
    ColecaoClientes colecaoClientes;

    inicializarColecaoVendas(&colecaoVendas);
    inicializarColecao(&colecaoCategorias);
    inicializarColecaoClientes(&colecaoClientes);

    carregarVendas(&colecaoVendas);
    carregarCategorias(&colecaoCategorias);
    carregarClientes(&colecaoClientes);
    
    num_produtos = carregarProdutos(produtos);
	int periodo;
	 int numProdutos;
    do {
        system("cls");
        printf("=== MENU GERIR VENDAS ===\n");
        printf("1. Realizar venda\n");
        printf("2. Listar todas as vendas de hoje\n");
        printf("3. Listar produtos mais vendidos hoje\n");
        printf("4. Listar todas as vendas de hoje por categoria de produto\n");
        printf("5. Produtos que geraram mais receita hoje\n");
        printf("6. Vendas por tipo de produto hoje\n");
        printf("7. Gerar relatorio de contas do dia\n");
        printf("8. Gerar relatorio de produtos com baixo stock\n");
        printf("0. Voltar\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao_menu_gerir_vendas);
        switch (opcao_menu_gerir_vendas) {
            case 1:
                realizarVenda(&colecaoVendas, &colecaoCategorias, &colecaoClientes, produtos, num_produtos); 
                break;
            case 2:
                listarVendasPorHora(&colecaoVendas); 
                break;
            case 3:
               	 listarProdutosMaisVendidosHoje(&colecaoVendas);
                break;
            case 4:
                listarVendasPorData(&colecaoVendas);
                break;
            case 5:
  				printf("Digite 1 para produtos mais rentaveis hoje, 2 para este mes: ");
  				scanf("%d", &periodo);
  				listarProdutosMaisRentaveis(&colecaoVendas, produtos, num_produtos, periodo);
                break;
            case 6:
                  // Listar produtos disponíveis
  				  printf("Produtos disponiveis:\n");
  				  listarProdutos();
 				  int id_produto;
 			      printf("Digite o ID do produto que deseja verificar: ");
  				  scanf("%d", &id_produto);
  				  printf("Digite 1 para vendas de hoje, 2 para este mes: ");
  				  scanf("%d", &periodo);
  					  
  				  vendasPorTipoProduto(&colecaoVendas, produtos, num_produtos, id_produto, periodo);
                break;
            case 7:
                printf("Digite 1 para gerar relatorio do dia, 2 para gerar relatorio do mes: ");
				scanf("%d", &periodo);
				gerarRelatorioContas(&colecaoVendas, produtos, num_produtos, periodo);
                break;
            case 8:
                gerarRelatorioBaixoStock(produtos, num_produtos, &colecaoVendas);	 
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    } while (opcao_menu_gerir_vendas != 0);
}
	

void inicializar(){
	// Criar os ficheiros se eles não existirem
	FILE *ficheiro_produtos = fopen("produtos.txt", "a");
    FILE *ficheiro_clientes = fopen("clientes.txt", "a");
    FILE *ficheiro_vendas = fopen("vendas.txt", "a");
    FILE *ficheiro_categorias = fopen("categorias.txt", "a");

    if (ficheiro_produtos == NULL || ficheiro_clientes == NULL || ficheiro_vendas == NULL || ficheiro_categorias == NULL) {
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
                gerirVendas();
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


