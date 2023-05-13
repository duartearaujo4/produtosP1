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
	float preço;
	int id;	
	int categoria;
}caracteristicas;

typedef struct catg {
	INFO node;
	struct catg* next;
	struct elem* prev;
}categoria;

categoria* criar_categoria(INFO new_info){
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
void criarproduto()
{
    // Verificar se o limite máximo de produtos foi atingido
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    int num_produtos = 0;
    char linha[100];
    while (fgets(linha, 100, arquivo) != NULL) {
        num_produtos++;
    }
		 fclose(arquivo);

	 if (num_produtos >= MAX_PRODUTOS) {
        printf("Limite máximo de produtos (%d) atingido.\n", MAX_PRODUTOS);
        return;
    }

	  // Obter informações do usuário
    Caracteristicas novo_produto;
    printf("Digite o nome do produto: ");
    fgets(novo_produto.nome, 30, stdin);
    printf("Digite o SKU do produto: ");
    fgets(novo_produto.sku, 15, stdin);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novo_produto.quantidade);
    printf("Digite o preço do produto: ");
    scanf("%f", &novo_produto.preco);
    printf("Digite o identificador do produto: ");
    scanf("%d", &novo_produto.id);
    printf("Digite a categoria do produto: ");
    scanf("%d", &novo_produto.categoria);
    
    // Abrir o arquivo para escrever
    arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
	// Escrever as informações no arquivo
    fprintf(arquivo, "%s;%s;%d;%.2f;%d;%d\n", novo_produto.nome, novo_produto.sku, novo_produto.quantidade, novo_produto.preco, novo_produto.id, novo_produto.categoria);
    
    // Fechar o arquivo
    fclose(arquivo);
    
    printf("Produto criado com sucesso!\n");
}


void editarproduto()
{
	 // Abrir o arquivo para leitura
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    // Ler as informações do arquivo e armazená-las em uma matriz de structs
    Caracteristicas produtos[MAX_PRODUTOS];
    int num_produtos = 0;
    char linha[100];
    while (fgets(linha, 100, arquivo) != NULL) {
        sscanf(linha, "%[^;];%[^;];%d;%f;%d;%d\n", produtos[num_produtos].nome, produtos[num_produtos].sku, &produtos[num_produtos].quantidade, &produtos[num_produtos].preco, &produtos[num_produtos].id, &produtos[num_produtos].categoria);
        num_produtos++;
    }
     // Fechar o arquivo
    fclose(arquivo);
    
    // Verificar se não há produtos cadastrados
    if (num_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
     // Obter o identificador do produto a ser editado
    int id;
    printf("Digite a identificação do produto a ser editado: ");
    scanf("%d", &id);
    
    // Procurar o produto com o identificador informado e permitir a edição das informações
    int encontrado = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Produto encontrado:\n");
            printf("Nome: %s", produtos[i].nome);
            printf("SKU: %s", produtos[i].sku);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Identificador: %d\n", produtos[i].id);
            printf("Categoria: %d\n", produtos[i].categoria);
            
            printf("Digite as novas informações do produto:\n");
            printf("Nome: ");
            fgets(produtos[i].nome, 30, stdin); // Consumir o caractere de nova linha pendente
            fgets(produtos[i].nome, 30, stdin);
            printf("SKU: ");
            fgets(produtos[i].sku, 15, stdin);
            printf("Quantidade: ");
            scanf("%d", &produtos[i].quantidade);
            printf("Preço: ");
            scanf("%f", &produtos[i].preco);
            printf("Identificador: ");
            scanf("%d", &produtos[i].id);
            printf("Categoria: ");
            scanf("%d", &produtos[i].categoria);
            
            break;
        }
    }
    
    if (!encontrado) {
        printf("Produto com identificador %d não encontrado.\n", id);
        return;
    }
	 // Abrir o arquivo para escrita
    arquivo = fopen("produtos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    // Escrever as informações atualizadas no arquivo
    for (int i = 0; i < num_produtos; i++) {
        fprintf(arquivo, "%s;%s;%d;%.2f;%d;%d\n", produtos[i].nome, produtos[i].sku, produtos[i].quantidade, produtos[i].preco, produtos[i].id, produtos[i].categoria);
    }
    
    // Fechar o arquivo
    fclose(arquivo);
    
    printf("Produto atualizado com sucesso.\n");
}

















