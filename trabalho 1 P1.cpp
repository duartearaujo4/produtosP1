#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 250

typedef struct  Produtos {
	char nome [30];
	char sku [15];
	int quantidade;
	float preço;
	int id;
	int categoria;
};

typedef struct Categoria {
	char nome [30];
	int id;
};

typedef struct Clientes {
	char nome [30];
	int NIF [9];
	char telefone [9];
};




printf("Digite o nome do novo produto:");
scanf("%s");
printf("Digite o SKU do novo produto:");
scanf("%s");
printf("Digite a quantidade(stock) do novo produto:");
scanf("%d");
printf("Digite o preço do novo produto:");
scanf("&f");
printf("Selecione a categoria do novo produto:");
scanf
printf("Novo produto adicionado!");

