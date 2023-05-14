#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 250

typedef struct  produtos {
	char nome [30];
	char sku [15];
	int quantidade;
	float preco;
	int id;	
	int categoria;
}caracteristicas;

typedef struct catg {
	INFO node;
	struct catg* next;
	struct elem* prev;
}categoria;

typedef struct clientes{
    char nome[50];
    int nif[9];
    char telefone[9];
} dados;

/*categoria* criar_categoria(INFO new_info){
	categoria* nova = (categoria*) calloc(1, sizeof(categoria));
	nova ->node = new_info;
	nova ->next =NULL;
	nova ->prev =NULL;
	return novo;
}
categoria* inserir_categoria_inicio(categoria* lista, INFO new_info){
	categoria* nova = criar_categoria(new_info);
	if(lista!= NULL){
		lista->prev = nova;
	}
	nova->next = lista;
	nova->prev = NULL;
	return nova;
}
*/
void criarproduto()
{
    // Verificar se o limite máximo de produtos foi atingido
    FILE *ficheiro = fopen("produtos.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    
    int num_produtos = 0;
    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        num_produtos++;
    }
		 fclose(ficheiro);

	 if (num_produtos >= MAX_PRODUTOS) {
        printf("Limite máximo de produtos (%d) atingido.\n", MAX_PRODUTOS);
        return;
    }

	  // Obter informações do utilizador
    Caracteristicas novo_produto;
    printf("Escreva o nome do produto: ");
    fgets(novo_produto.nome, 30, stdin);
    printf("Escreva o SKU do produto: ");
    fgets(novo_produto.sku, 15, stdin);
    printf("Escreva a quantidade do produto: ");
    scanf("%d", &novo_produto.quantidade);
    printf("Escreva o preço do produto: ");
    scanf("%f", &novo_produto.preco);
    printf("Escreva o id do produto: ");
    scanf("%d", &novo_produto.id);
    printf("Escreva a categoria do produto: ");
    scanf("%d", &novo_produto.categoria);
    
    // Abrir o ficheiro para escrever
    ficheiro = fopen("produtos.txt", "a");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
	// Escrever as informações no ficheiro
    fprintf(ficheiro, "%s;%s;%d;%.2f;%d;%d\n", novo_produto.nome, novo_produto.sku, novo_produto.quantidade, novo_produto.preco, novo_produto.id, novo_produto.categoria);
    
    // Fechar o ficheiro
    fclose(ficheiro);
    
    printf("Produto criado com sucesso!\n");
}


void editarproduto()
{
	 // Abrir o ficheiro para leitura
    FILE *ficheiro = fopen("produtos.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    // Ler as informações do ficheiro e armazená-las numa matriz de structs
    Caracteristicas produtos[MAX_PRODUTOS];
    int num_produtos = 0;
    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        sscanf(linha, "%[^;];%[^;];%d;%f;%d;%d\n", produtos[num_produtos].nome, produtos[num_produtos].sku, &produtos[num_produtos].quantidade, &produtos[num_produtos].preco, &produtos[num_produtos].id, &produtos[num_produtos].categoria);
        num_produtos++;
    }
     // Fechar o ficheiro
    fclose(ficheiro);
    
    // Verificar se não há produtos 
    if (num_produtos == 0) {
        printf("Nenhum produto registado.\n");
        return;
    }
     // Obter o id do produto a ser editado
    int id;
    printf("Digite o id do produto a ser editado: ");
    scanf("%d", &id);
    
    // Procurar o produto com o id e permitir a edição das informações
    int encontrado = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Produto encontrado:\n");
            printf("Nome: %s", produtos[i].nome);
            printf("SKU: %s", produtos[i].sku);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Id: %d\n", produtos[i].id);
            printf("Categoria: %d\n", produtos[i].categoria);
            
            printf("Escreva as novas informações do produto:\n");
            printf("Nome: ");
            fgets(produtos[i].nome, 30, stdin); // Consumir o caractere de nova linha pendente
            fgets(produtos[i].nome, 30, stdin);
            printf("SKU: ");
            fgets(produtos[i].sku, 15, stdin);
            printf("Quantidade: ");
            scanf("%d", &produtos[i].quantidade);
            printf("Preço: ");
            scanf("%f", &produtos[i].preco);
            printf("Id: ");
            scanf("%d", &produtos[i].id);
            printf("Categoria: ");
            scanf("%d", &produtos[i].categoria);
            
            break;
        }
    }
    
    if (!encontrado) {
        printf("Produto com id (%d) não encontrado.\n", id);
        return;
    }
	 // Abrir o ficheiro para escrita
    ficheiro = fopen("produtos.txt", "w");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    
    // Escrever as informações atualizadas no ficheiro
    for (int i = 0; i < num_produtos; i++) {
        fprintf(ficheiro, "%s;%s;%d;%.2f;%d;%d\n", produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco, produtos[i].id, produtos[i].categoria);
    }
    
    // Fechar o ficheiro
    fclose(ficheiro);
    
    printf("Produto atualizado com sucesso.\n");
}
void removerproduto()
{
    // Abrir o ficheiro para leitura
    FILE *ficheiro = fopen("produtos.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    // Ler as informações do ficheiro e armazená-las numa matriz de structs
    caracteristicas produtos[MAX_PRODUTOS];
    int num_produtos = 0;
    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        sscanf(linha, "%[^;];%[^;];%d;%f;%d;%d\n", produtos[num_produtos].nome, produtos[num_produtos].sku, &produtos[num_produtos].quantidade, &produtos[num_produtos].preco, &produtos[num_produtos].id, &produtos[num_produtos].categoria);
        num_produtos++;
    }
    // Fechar o ficheiro
    fclose(ficheiro);
    
    // Verificar se não há produtos 
    if (num_produtos == 0) {
        printf("Nenhum produto registado.\n");
        return;
    }
    
    // Obter o id do produto a ser removido
    int id;
    printf("Digite o id do produto a ser removido: ");
    scanf("%d", &id);
    
    // Procurar o produto com o id e, se encontrado, mover todos os produtos depois dele para uma posição anterior na matriz
    int encontrado = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Produto encontrado:\n");
            printf("Nome: %s", produtos[i].nome);
            printf("SKU: %s", produtos[i].sku);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Id: %d\n", produtos[i].id);
            printf("Categoria: %d\n", produtos[i].categoria);
            
            // Mover todos os produtos depois do produto encontrado para uma posição anterior na matriz
            for (int j = i; j < num_produtos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
			  // Atualizar o número de produtos na matriz
			num_produtos--;
			break;
		}
	}
	// Se o produto não foi encontrado, informar o usuário
	if (!encontrado) {
   	 printf("Produto não encontrado.\n");
   	 return;
	}

	// Abrir o ficheiro para escrita
	ficheiro = fopen("produtos.txt", "w");
	if (ficheiro == NULL) {
	    printf("Erro ao abrir o ficheiro.\n");
 	   return;
	}

	// Escrever a matriz atualizada no ficheiro
	for (int i = 0; i < num_produtos; i++) {
	    fprintf(ficheiro, "%s;%s;%d;%.2f;%d;%d\n", produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco, produtos[i].id, produtos[i].categoria);
	}

	// Fechar o ficheiro
	fclose(ficheiro);

	printf("Produto removido com sucesso.\n");
}
void listarprodutos() {
    // Abrir o ficheiro para leitura
    FILE *ficheiro = fopen("produtos.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    // Ler as informações do ficheiro e armazená-las numa matriz de structs
    caracteristicas produtos[MAX_PRODUTOS];
    int num_produtos = 0;
    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        sscanf(linha, "%[^;];%[^;];%d;%f;%d;%d\n", produtos[num_produtos].nome, produtos[num_produtos].sku, &produtos[num_produtos].quantidade, &produtos[num_produtos].preco, &produtos[num_produtos].id, &produtos[num_produtos].categoria);
        num_produtos++;
    }

    // Fechar o ficheiro
    fclose(ficheiro);

    // Verificar se não há produtos
    if (num_produtos == 0) {
        printf("Nenhum produto registado.\n");
        return;
    }

    // Imprimir a tabela com as informações dos produtos
    printf("Produtos cadastrados:\n");
    printf("+----+-----------------------------------+-------------------+----------+--------------+------------+\n");
    printf("| ID |             Nome do Produto         |        SKU        | Quantidade |    Preço     | Categoria  |\n");
    printf("+----+-----------------------------------+-------------------+----------+--------------+------------+\n");
    for (int i = 0; i < num_produtos; i++) {
        printf("|%4d|%35s|%19s|%10d|%14.2f|%12d|\n", produtos[i].id, produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco, produtos[i].categoria);
    }
    printf("+----+-----------------------------------+-------------------+----------+--------------+------------+\n");
}






void criarcliente()
{
	//Obter informaçoes do cliente
Dados novo_cliente;	
printf("Escreva o nome do cliente: ");
fgets(novo_cliente.nome, 50, stdin);
printf("Escreva o NIF do cliente: ");
fgets(novo_cliente.nif, 9, stdin);	
printf("Introduza o numero de telefone do cliente: ");
fgets(novo_cliente.telefone,9 ,stdin);

	// Abrir o ficheiro para escrever
    ficheiro = fopen("clientes.txt", "a");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
	// Escrever as informações no ficheiro
    fprintf(ficheiro, "%s;%s;%d;%.2f;%d;%d\n", novo_cliente.nome, novo_cliente.nif, novo_cliente.telefone);
    
    // Fechar o ficheiro
    fclose(ficheiro);
    
    printf("cliente criado com sucesso!\n");
}
	
void atualizarcliente()
{
	//obter o NIF do cliente a ser atualizado
	int nif;
	printf("Digite o NIF do cliente a ser atualizado: ");
	scanf("%d", &nif);
	
	// Procurar o cliente com o nif e permitir a atualizaçao dos dados
	 int encontrado = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].nif == nif) {
            encontrado = 1;
            printf("Cliente encontrado:\n");
            printf("Nome: %s", clientes[i].nome);
            printf("NIF: %s", clientes[i].nif);
            printf("Telefone: %d\n", clientes[i].telefone);
            
            
            printf("Escreva os novos dados do cliente:\n");
            printf("Nome: ");
            fgets(clientes[i].nome, 50, stdin); 
        	printf("NIF: ");
            fgets(clientes[i].nif, 9, stdin);
            printf("Telefone: ");
            scanf("%d", &clientes[i].telefone);
            break;
	
	
		}		
	}
	
	 if (!encontrado) {
        printf("Cliente com nif (%s) não encontrado.\n", nif);
        return;
