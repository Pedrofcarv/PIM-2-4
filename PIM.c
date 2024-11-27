#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nome[30];
    char tipo[20];
    char fornecedor[50];
    char tipovend [3];
    float valor;
    int codigo;
	int quant; 
	
} Merc;

// Função para mostrar produtos
int mostrarprod() {
    FILE *arq;
    char Linha[100];

    arq = fopen("Estoque.csv", "r");  // Abre o arquivo para leitura
    if (arq == NULL) {  
        printf("Problemas para ler o arquivo\n");
        return 1;  
    }

    // Cabeçalho da tabela
    printf("\n%-24s %-24s %-20s %-10s %-15s %-20s %-12s\n", "Nome do Produto", "Tipo do Produto", "Fornecedor", "Código", "Quantidade", "Tipo de venda", "Valor");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(Linha, sizeof(Linha), arq) != NULL) {  
        char nome[30], tipo[20], fornecedor[50], tipovend[3];
        int codigo, quant;
        float valor;

        // Usar sscanf para extrair os dados da linha
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%d,%[^,],%f", nome, tipo, fornecedor, &codigo, &quant, tipovend, &valor);
        
        // Imprimir os dados em formato de tabela
        printf("   %-27s %-20s %-20s %-13d %-17d %-12s %-10f\n", nome, tipo, fornecedor, codigo, quant, tipovend, valor);
    }
    printf("\n");
    printf("\n _______________________________________");
    printf("\n|\t  1 - Editar produto\t\t|\n");
    printf("\n|\t  2 - Remover produto\t\t|\n");
     printf("\n|\t  3 - Adicionar Quantidade\t|\n");
    printf("\n|\t  0 - Inicio\t\t\t|\n");
    printf(" _______________________________________\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\t  Selecione uma opcao: \t\t|");
    printf("\n|_______________________________________|\n\n");
    
    printf("\n\n\n");
    return 0;
}


int geracod() {
    FILE *arq; 
    char linha[100];
    
    // Vai armazenar o último código, que também é o maior, e gerar um novo com base nisso.
    int ultimocod = 0;
    arq = fopen("Estoque.csv", "r");
    
    // Verificação se o arquivo existe
    if (arq == NULL) {
        return 1;
    }
    
    while (fgets(linha, sizeof(linha), arq) != NULL) {
        int codigo;
        sscanf(linha, "%*[^,],%*[^,],%*[^,],%d", &codigo);
        
        if (codigo > ultimocod) {
            ultimocod = codigo;  // Atualiza o maior código encontrado
        }
    }
    
    fclose(arq);
    
    return ultimocod + 1;  // Retorna o próximo código
}




void Telaest() {
    printf(" _______________________________________");
    printf("\n|\t\tESTOQUE\t\t\t|\n");
    printf("|_______________________________________|");
    printf("\n _______________________________________");
    printf("\n|\t  1 - Cadastrar Produtos\t|\n");
    printf("\n|\t  2 - Consultar Cadastros\t|\n");
    printf(" _______________________________________\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\t  Selecione uma opcao: \t\t|");
    printf("\n|_______________________________________|\n\n");
   
}

// Função para mostrar o menu principal
void Telainicial() {
    printf(" _______________________________________");
    printf("\n|\t\tHORTIFRUTI\t\t|\n");
    printf("|_______________________________________|");
    printf("\n _______________________________________");
    printf("\n|\t  1 - Estoque\t\t\t|\n");
    printf("\n|\t  2 - Caixa\t\t\t|\n");
    printf(" _______________________________________\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\t  Selecione uma opcao: \t\t|");
    printf("\n|_______________________________________|\n\n");
}

// Funçãoo para cadastrar um produto
int Cadprod() {
    FILE *arq;
    Merc produto;
    int i = 0, opcad, optipo, opvend;
    
    // Exibir cabeçalho
    printf("\n==========================================\n");
    printf("|           CADASTRO DE PRODUTOS         |\n");
    printf("==========================================\n");
    
	do{
    // Abrir o arquivo uma vez fora do loop
    arq = fopen("Estoque.csv", "a");
    if (arq == NULL) {  
        printf("Problemas na abertura do arquivo\n");
        return 1;  
    }
    
    
        // Exibir cabeçalho para cada produto
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
        printf(" 5 - Orgânico\n");
        printf(" 6 - Outro\n");
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
		strcpy(produto.tipo,"Orgânico");
		}
		else if (optipo == 6){
		strcpy(produto.tipo,"Outro");
		}
	
        setbuf(stdin, NULL);     
        produto.tipo[strcspn(produto.tipo, "\n")] = '\0';

        // Ler o fornecedor do produto
        printf(" Fornecedor do produto: ");
        setbuf(stdin, NULL);     
        fgets(produto.fornecedor, sizeof(produto.fornecedor), stdin);
        produto.fornecedor[strcspn(produto.fornecedor, "\n")] = '\0';

        // Ler o código do produto com validação
        produto.codigo = geracod();
        printf(" Código gerado automaticamente: %d\n", produto.codigo);
        
        //declarando a quantidade 
        printf(" Quantiadade: ");
        setbuf(stdin, NULL);     
         while (scanf("%d", &produto.quant) != 1) {
            printf("Quantidade inválida: ");
            setbuf(stdin, NULL);
        }
        
        //a forma de venda do produto(UNIDADE/KG)
        printf(" A venda sera por: \n");
        printf(" 1 - UNIDADE\n");
        printf(" 2 - KG\n");
        scanf("%d", &opvend);
         if (opvend == 1){
		strcpy(produto.tipovend,"UN"); 
		}
		else if (opvend == 2){
		strcpy(produto.tipovend,"KG");
		}
		
		//valor do produto
		 printf(" Valor: ");
        setbuf(stdin, NULL);     
        while (scanf("%f", &produto.valor) <= 0) {
            printf("Valor Invalido: ");
            setbuf(stdin, NULL);
        }
        
        
        
        

        // Armazenar os detalhes do produto no arquivo
        fprintf(arq, "%s,%s,%s,%d,%d,%s,%.2f\n", produto.nome, produto.tipo, produto.fornecedor, produto.codigo, produto.quant, produto.tipovend, produto.valor); 

        // Confirmação de cadastro
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
		printf("Digite uma opção válida\n");
		
		}while(opcad != 0 && opcad != 1);
		
		 fclose(arq);
	
        i++;
    } while(opcad != 0);

    // Fechar o arquivo após todos os produtos serem cadastrados
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
            	
                Telaest();
                int opest;
                scanf("%d", &opest);
                system("cls");
                
                switch(opest){
                	case 1:
                		Cadprod();
                		break;
                		
                	case 2:
                		 mostrarprod();
                		 	int oprod;
                		scanf("%d", &oprod);
                		break;
                		
				}
            /*default:
                printf("Opcao invalida! Tente novamente.\n");
                break;*/
        }
    } while (op != 0);

    return 0;
}
