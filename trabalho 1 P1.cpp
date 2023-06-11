	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <locale.h>
	#include <math.h>
	
	// Definição das constantes
	#define MAX_CARACTERES_NOME 50
	#define MAX_CARACTERES_SKU 20
	#define MAX_CARACTERES_LINHA 100
	#define MAX_PRODUTOS 250
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

		
	
	// Variáveis globais
	Produto produtos[MAX_PRODUTOS];
	int num_categorias = 0;
	int num_produtos = 0;
	
	//Funções
	void inicializarColecao(ColecaoCategorias* colecao);
	void adicionarCategoria(ColecaoCategorias* colecao, Categoria novaCategoria);
	void liberarColecao(ColecaoCategorias* colecao);
	void criarCategoria(ColecaoCategorias* colecaoCategorias);
	void gerirClientesSubmenu(ColecaoClientes* colecaoClientes);
	void gerirProdutos();
	void gerirClientes();
	void realizarVendas();
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
	
	//Esta função server para dar refresh às categorias
	void carregarCategorias(ColecaoCategorias* colecaoCategorias) {
    // Abrir o arquivo em modo de leitura
    FILE *arquivo = fopen("produtos.txt", "r");
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
	
	//Esta função server para dar refresh aos produtos
	void carregarProdutos(Produto produtos[], int* num_produtos) {
    FILE* arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: ficheiro nao encontrado\n");
        return;
    }

    *num_produtos = 0;

    while (fscanf(arquivo, "%d,%[^,],%[^,],%d,%lf\n", &produtos[*num_produtos].id, produtos[*num_produtos].nome, produtos[*num_produtos].sku, &produtos[*num_produtos].quantidade, &produtos[*num_produtos].preco) == 5) {
        (*num_produtos)++;
    }

    fclose(arquivo);
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
	
	// Função para criar uma nova categoria----------
	void criarCategoria(ColecaoCategorias* colecaoCategorias) {
	    static int proximoID = 1;  // Declaração da variável proximoID
	    Categoria novaCategoria;
	    novaCategoria.categoria_id = proximoID++;
	    printf("Escreva o nome da categoria: ");
	    scanf("%s", novaCategoria.categoria_nome);
	
	 
	    adicionarCategoria(colecaoCategorias, novaCategoria);
	
	    FILE* arquivo = fopen("produtos.txt", "a");
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
        char* nome_categoria = malloc(sizeof(char) * 50);
        sscanf(linha, "%d %[^\n]", &categoria_id, nome_categoria);

        // Verificar se a categoria encontrada é a desejada
        if (categoria_id == id_categoria) {
            printf("Escreva o novo nome da categoria: ");
            scanf("%s", nome_categoria);

            // Fechar o arquivo para aplicar as alterações
            fclose(arquivo);

            // Reabrir o arquivo em modo de escrita e sobrescrever a linha da categoria editada
            arquivo = fopen("produtos.txt", "r+");
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
			FILE *arquivo = fopen("produtos.txt", "w");
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
        printf("Erro ao criar o arquivo de relatório.\n");
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

    printf("Relatório de inventário gerado com sucesso.\n");
}




















// Função para criar um novo cliente----------
void criarCliente(ColecaoClientes* colecaoClientes) {
    static int proximoID = 1;  // Declaração da variável proximoID
    Cliente novoCliente;
    novoCliente.cliente_id = proximoID++;
    printf("Escreva o nome do cliente: ");
    scanf("%s", novoCliente.nome_cliente);
    printf("Escreva o NIF do cliente: ");
    scanf("%s", novoCliente.nif);
    printf("Escreva o contato do cliente: ");
    scanf("%s", novoCliente.contato);

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
void removerCliente(ColecaoClientes* colecaoClientes) {
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
            if (checkVendasCliente(id_cliente)) {
                printf("Erro: há vendas ligadas a este cliente\n");
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
                printf("Erro: não foi possível abrir o ficheiro\n");
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
	void apresentarInformacoesPorNIF(ColecaoClientes* colecaoClientes) {
    if(colecaoClientes->primeiro == NULL) {
        printf("Erro: Nenhum cliente registado\n");
        return;
    }

    char nif[10]; // substitua 10 pelo tamanho correto do NIF
    printf("Digite o NIF do cliente: ");
    scanf("%s", nif);

    Cliente* clienteAtual;
    for(clienteAtual = colecaoClientes->primeiro; clienteAtual != NULL; clienteAtual = clienteAtual->proximo) {
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


void gerirProdutos() {
    int opcao_menu_gerir_produtos;
    ColecaoCategorias colecaoCategorias;
    inicializarColecao(&colecaoCategorias);
    carregarCategorias(&colecaoCategorias);
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
                gerirClientesSubmenu(&colecaoClientes);  // Para criar, atualizar e remover clientes
                break;
            case 2:
                listarClientesPorNome(&colecaoClientes);  // Para listar os clientes em ordem alfabética
                break;
            case 3:
                apresentarInfoClientePorNIF(&colecaoClientes);  // Para apresentar informações do cliente dado o NIF
                break;
            case 4:
                anonimizarDadosCliente(&colecaoClientes);  // Para anonimizar os dados do cliente
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

void gerirClientesSubmenu(ColecaoClientes* colecaoClientes) {
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
                removerCliente(colecaoClientes);
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


