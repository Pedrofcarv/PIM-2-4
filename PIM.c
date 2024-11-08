#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nome[30];
    char tipo[20];
    char fornecedor[50];
    int codigo;
	int quant; 
} Merc;

// Fun��o para mostrar produtos
int mostrarprod() {
    FILE *arq;
    char Linha[100];

    arq = fopen("Estoque.csv", "r");  // Abre o arquivo para leitura
    if (arq == NULL) {  
        printf("Problemas para ler o arquivo\n");
        return 1;  
    }

    // Cabe�alho da tabela
    printf("\n%-30s %-20s %-20s %-10s %-10s\n", "Nome do Produto", "Tipo do Produto", "Fornecedor", "C�digo", "Quantidade");
    printf("----------------------------------------------------------------------------------------------------\n");

    while (fgets(Linha, sizeof(Linha), arq) != NULL) {  
        char nome[30], tipo[20], fornecedor[50];
        int codigo, quant;

        // Usar sscanf para extrair os dados da linha
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%d", nome, tipo, fornecedor, &codigo, &quant);
        
        // Imprimir os dados em formato de tabela
        printf("%-30s %-20s %-20s %-10d %-10d\n", nome, tipo, fornecedor, codigo, quant);
    }
    
    printf("\n\n\n");
    return 0;
}

// Fun��o para mostrar o menu principal
void Telainicial() {
    printf(" _______________________________________");
    printf("\n|\t\tHORTIFRUTI\t\t|\n");
    printf("|_______________________________________|");
    printf("\n _______________________________________");
    printf("\n|\t  1 - Cadastrar Produtos\t|\n");
    printf("\n|\t  2 - Consultar Cadastros\t|\n");
    printf("\n|\t  3 - Estoque\t\t\t|\n");
    printf("\n|\t  4 - Caixa\t\t\t|\n");
    printf(" _______________________________________\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\t  Selecione uma opcao: \t\t|");
    printf("\n|_______________________________________|\n\n");
}

// Fun��o para cadastrar um produto
int Cadprod() {
    FILE *arq;
    Merc produto;
    int i = 0, opcad, optipo;
    
    // Exibir cabe�alho
    printf("\n==========================================\n");
    printf("|           CADASTRO DE PRODUTOS         |\n");
    printf("==========================================\n");

    // Abrir o arquivo uma vez fora do loop
    arq = fopen("Estoque.csv", "a");
    if (arq == NULL) {  
        printf("Problemas na abertura do arquivo\n");
        return 1;  
    }
    
    do {
        // Exibir cabe�alho para cada produto
        printf("\n=========================================\n");
        printf("|        CADASTRO DO PRODUTO %d          |\n", i + 1);
        printf("=========================================\n");

        // Ler o nome do produto
        printf(" Nome do produto: ");
        setbuf(stdin, NULL);     
        fgets(produto.nome, sizeof(produto.nome), stdin);
        produto.nome[strcspn(produto.nome, "\n")] = '\0'; // Remover nova linha

        // Ler o tipo do produto
        printf(" Qual o tipo do produto: \n");
        printf(" 1 - Fruta\n");
        printf(" 2 - Verdura\n");
        printf(" 3 - Legume\n");
        printf(" 4 - Tempero\n");
        printf(" 5 -  Org�nicos\n");
        scanf("%d", &optipo);
        
        if (optipo == 1){
		strcpy(produto.tipo,"Fruta"); 
		}
		else if (optipo == 2){
		strcpy(produto.tipo,"Verdura");
		}
		else if (optipo == 3){
		strcpy(produto.tipo,"Legume"); 
		}
		else if (optipo == 4){
		strcpy(produto.tipo,"Tempero");
		}
		else if (optipo == 5){
		strcpy(produto.tipo,"Org�nico");
		}
	
        setbuf(stdin, NULL);     
        produto.tipo[strcspn(produto.tipo, "\n")] = '\0';

        // Ler o fornecedor do produto
        printf(" Fornecedor do produto: ");
        setbuf(stdin, NULL);     
        fgets(produto.fornecedor, sizeof(produto.fornecedor), stdin);
        produto.fornecedor[strcspn(produto.fornecedor, "\n")] = '\0';

        // Ler o c�digo do produto com valida��o
        printf(" C�digo do produto (apenas n�meros): ");
        while (scanf("%d", &produto.codigo) != 1) {
            printf("C�digo inv�lido! Insira apenas n�meros: ");
            setbuf(stdin, NULL);
        }
        
        //declarando a quantidade 
        printf(" Quantiadade: ");
        setbuf(stdin, NULL);     
         while (scanf("%d", &produto.quant) != 1) {
            printf("Quantidade inv�lida: ");
            setbuf(stdin, NULL);
        }
        
        

        // Armazenar os detalhes do produto no arquivo
        fprintf(arq, "%s,%s,%s,%d,%d\n", produto.nome, produto.tipo, produto.fornecedor, produto.codigo, produto.quant); 

        // Confirma��o de cadastro
        printf("===========================================\n");
        printf("|   Produto %d cadastrado com sucesso!     |\n", i + 1);
        printf("===========================================\n\n");
        
        printf("Deseja finalizar ou continuar?\n");
        do{
        printf("0 - Sair\n");
        printf("1 - Continuar\n");
	    scanf("%d", &opcad); 
        setbuf(stdin, NULL);
        system("cls");
        if(opcad != 0 && opcad != 1)
		printf("Digite uma op��o v�lida\n");
		
		}while(opcad != 0 && opcad != 1);
		
	
        i++;
    } while(opcad != 0);

    // Fechar o arquivo ap�s todos os produtos serem cadastrados
    fclose(arq);
    printf("\n=============================================\n");
    printf("|  Cadastro finalizado para %d produto(s)!   |\n", i);
    printf("=============================================\n\n");
	printf(" Voltando ao menu inicial");
    sleep(3);
    system("cls");
    
    
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    int op;

    do {
        Telainicial();
        scanf("%d", &op);
        system("cls");

        switch (op) {
            case 0:
                printf("\nExecucao Finalizada!!!\n");
                break;
            case 1:
                Cadprod();
                break;
            case 2:
                mostrarprod();
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (op != 0);

    return 0;
}

