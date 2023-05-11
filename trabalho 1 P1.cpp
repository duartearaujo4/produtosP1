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
void adicionarproduto
	if (contadorprodutos > MAX_PRODUTOS ) {
		printf("A loja nao tem capacidade para mais produtos!");
	}

void removerproduto
    if (contadorprodutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    }


Produto novoproduto;
printf("Digite o nome do novo produto:");
scanf("%s, novoproduto.nome");
printf("Digite o SKU do novo produto:");
scanf("%s, novoproduto.sku");
printf("Digite a quantidade(stock) do novo produto:");
scanf("%d, novoproduto.quantidade");
printf("Digite o preço do novo produto:");
scanf("&f, novoproduto.preço");
printf("Selecione a categoria do novo produto:");
printf("Novo produto adicionado!");
















