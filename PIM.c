#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//struct para definir o produto 
typedef struct {
    char nome[30];
    char tipo[20];
    char fornecedor[50];
    char tipovend [3];
    float valor;
    int codigo;
	float quant; 
	
} Merc;

//struct para armazenar os dados da transação
typedef struct {
    char item[30];
    int quantidade;
    float valor_unitario;
    float valor_total;
    char data[20];  // Ex: "27/11/2024 14:35"
} Transacao;

//função para pegar data e hora 
void DataHora(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

// Função para mostrar produtos
int mostrarprod() {
    FILE *arq;
    char Linha[200];

    arq = fopen("Estoque.csv", "r");  // Abre o arquivo para leitura
    if (arq == NULL) {  
        printf("Problemas para ler o arquivo\n");
        return 1;  
    }

    // Cabeçalho da tabela
    printf("\n%-24s %-24s %-20s %-12s %-15s %-20s %-12s\n", "Nome do Produto", "Tipo do Produto", "Fornecedor", "Código", "Quantidade", "Tipo de venda", "Valor");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(Linha, sizeof(Linha), arq) != NULL) {  
        char nome[30], tipo[20], fornecedor[50], tipovend[3];
        int codigo;
        float valor, quant;

        // Usar sscanf para extrair os dados da linha
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%f,%[^,],%f", nome, tipo, fornecedor, &codigo, &quant, tipovend, &valor);
        
        // Imprimir os dados em formato de tabela
        printf("   %-27s %-20s %-20s %-13d %-17.2f %-15s %-10.2f\n", nome, tipo, fornecedor, codigo, quant, tipovend, valor);
    }
    printf("\n");
    printf("\n _______________________________________");
    printf("\n|\t  [1] - Editar produto\t\t|\n");
    printf("\n|\t  [2] - Remover produto\t\t|\n");
     printf("\n|\t  [3] - Adicionar Quantidade\t|\n");
    printf("\n|\t  [0] - Inicio\t\t\t|\n");
    printf(" _______________________________________\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\t  Selecione uma opcao: \t\t|");
    printf("\n|_______________________________________|\n\n");
    
    printf("\n\n");
    return 0;
}

//função para editar o produto 
void editprod() {
    FILE *arq;
    char Linha[200];
    Merc produtos[200]; // Array para armazenar produtos
    int count = 0, encontrado = 0, codigo;
    printf("\n==========================================\n");
    printf("|           EDIÇÃO DE PRODUTOS         |\n");
    printf("==========================================\n");
    

    // Abrir o arquivo para leitura
    arq = fopen("Estoque.csv", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Carregar todos os produtos em memória
    while (fgets(Linha, sizeof(Linha), arq) != NULL) {
        Merc produto;
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%f,%[^,],%f",
               produto.nome, produto.tipo, produto.fornecedor,
               &produto.codigo, &produto.quant, produto.tipovend,
               &produto.valor);
        produtos[count++] = produto;
    }
    fclose(arq);

    // Solicitar o código do produto
    printf("Digite o código do produto que deseja editar: ");
    scanf("%d", &codigo);
    system("cls");

    // Procurar o produto pelo código
    for (int i = 0; i < count; i++) {
        if (produtos[i].codigo == codigo) {
            encontrado = 1;

            printf("Produto encontrado: %s\n", produtos[i].nome);

            // Editar nome
            printf("Digite o novo nome do produto (ou pressione Enter para manter): ");
            setbuf(stdin, NULL);
            char novo_nome[30];
            fgets(novo_nome, sizeof(novo_nome), stdin);
            if (novo_nome[0] != '\n') {
                    novo_nome[strcspn(novo_nome, "\n")] = '\0';
                    strcpy(produtos[i].nome, novo_nome);
                }


                // Editar tipo
                printf("Selecione o novo tipo do produto (ou 0 para manter):\n");
                printf(" [1] - Fruta\n [2] - Verdura\n [3] - Legume\n [4] - Tempero\n [5] - Orgânico\n [6] - Outro\n");
                int novo_tipo;
                    do{

                        scanf("%d", &novo_tipo);
                        setbuf(stdin, NULL);

                        if (novo_tipo >= 0 && novo_tipo <= 6) {
                            switch (novo_tipo) {
                                case 0: strcpy(produtos[i].tipo, produtos[i].tipo); 
                                break;

                                case 1: strcpy(produtos[i].tipo, "Fruta"); 
                                break;

                                case 2: strcpy(produtos[i].tipo, "Verdura"); 
                                break;

                                case 3: strcpy(produtos[i].tipo, "Legume");
                                break;

                                case 4: strcpy(produtos[i].tipo, "Tempero"); 
                                break;

                                case 5: strcpy(produtos[i].tipo, "Orgânico"); 
                                break;

                                case 6: strcpy(produtos[i].tipo, "Outro"); 
                                break;
                            }
                        }
                        else {
                            printf("Digite uma opção válida!\n");
                        }
                    }while(novo_tipo < 0 || novo_tipo > 6);

                // Editar fornecedor
                printf("Digite o novo fornecedor (ou pressione Enter para manter): ");
                char novo_fornecedor[50];
                fgets(novo_fornecedor, sizeof(novo_fornecedor), stdin);
                if (novo_fornecedor[0] != '\n') {
                    novo_fornecedor[strcspn(novo_fornecedor, "\n")] = '\0';
                    strcpy(produtos[i].fornecedor, novo_fornecedor);
                }


                // Editar valor
                printf("Digite o novo valor (ou 0 para manter): ");
                float novo_valor;
                scanf("%f", &novo_valor);
                if (novo_valor != 0) {
                    produtos[i].valor = novo_valor;
                }

                // Editar tipo de venda
                printf("Selecione o novo tipo de venda (ou 0 para manter):\n");
                printf("[1] - UN\n[2] - KG\n");
                int novo_tipovend;
                
                do{
                    scanf("%d", &novo_tipovend);
                    setbuf(stdin, NULL);
                    if(novo_tipovend == 0){
                        produtos[i].tipovend == produtos[i].tipovend;
                    }

                    else if (novo_tipovend >= 1 && novo_tipovend <= 2) {
                        switch (novo_tipovend) {
                            case 1: strcpy(produtos[i].tipovend, "UN"); 
                            break;

                            case 2: strcpy(produtos[i].tipovend, "KG"); 
                            break;
                        }
                    }
                    else{
                        printf("Digite uma opção válida!\n");
                    }
                }while(novo_tipovend < 0 || novo_tipovend > 2);

                // Editar quantidade
                printf("[0] - Manter Quantiade \n[1] - Alterar Quantidade \n");
                int decisao; // para mudar ou não a quantidade
                float nova_quant;
                int result;
                 result = strcmp(produtos[i].tipovend, "UN");
                setbuf(stdin, NULL);
                scanf("%d", &decisao);
                if (decisao == 0) {
                    produtos[i].quant = produtos[i].quant;
                }
                
                else if((novo_tipovend == 1 || result == 0) && decisao == 1){
                    
                    printf(" Quantiadade (não atribua números com casas decimais!!!): ");
                    do{   
                        setbuf(stdin, NULL);
                        scanf("%f", &nova_quant);

                        produtos[i].quant = nova_quant;

                        if(produtos[i].quant <= 0){
                            printf("Quantidade inválida: ");
                        }
                    }while(produtos[i].quant <= 0);
                }

                else if((novo_tipovend == 2 || result != 0) && decisao == 1){
                    
                    printf(" Quantidade em KG ");
                    do{   
                        setbuf(stdin, NULL);
                        scanf("%f", &nova_quant);

                        produtos[i].quant = nova_quant;

                        if(produtos[i].quant <= 0){
                            printf("Quantidade inválida: ");
                        }
                    }while(produtos[i].quant <= 0);
                }


            printf("Produto atualizado com sucesso!\n");
            break;
        }



    }

    if (!encontrado) {
        printf("Produto com código %d não encontrado.\n", codigo);
        return;
    }

    // Abrir o arquivo para reescrita e salvar os produtos atualizados
    arq = fopen("Estoque.csv", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(arq, "%s,%s,%s,%d,%f,%s,%.2f\n",
                produtos[i].nome, produtos[i].tipo, produtos[i].fornecedor,
                produtos[i].codigo, produtos[i].quant, produtos[i].tipovend,
                produtos[i].valor);
    }
    fclose(arq);
}


//função para remover produto 
void removerprod() {
    FILE *arq;
    char Linha[200];
    Merc produtos[200]; // Array para armazenar produtos
    int count = 0, encontrado = 0, codigo;

    printf("\n==========================================\n");
    printf("|           EXCLUSÃO DE PRODUTOS         |\n");
    printf("==========================================\n");

    // Abrir o arquivo para leitura
    arq = fopen("Estoque.csv", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Carregar todos os produtos em memória
    while (fgets(Linha, sizeof(Linha), arq) != NULL) {
        Merc produto;
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%f,%[^,],%f",
               produto.nome, produto.tipo, produto.fornecedor,
               &produto.codigo, &produto.quant, produto.tipovend,
               &produto.valor);
        produtos[count++] = produto;
    }
    fclose(arq);

    // Solicitar o código do produto
    printf("Digite o código do produto que deseja excluir: ");
    scanf("%d", &codigo);
    system("cls");

    // Procurar o produto pelo código
    for (int i = 0; i < count; i++) {
        if (produtos[i].codigo == codigo) {
            encontrado = 1;

            printf("Produto encontrado: %s\n", produtos[i].nome);

            int opexc;
            printf("\nDeseja realmente excluir o produto?\n 1 - Sim\n 2 - Não\n");

            do {
                scanf("%d", &opexc);

                if (opexc == 1) {
                    // Excluir o produto movendo os itens subsequentes
                    for (int j = i; j < count - 1; j++) {
                        produtos[j] = produtos[j + 1];
                    }
                    count--; // Reduz o número de produtos
                    printf("Produto excluído com sucesso!\n");
                    break;

                } else if (opexc == 2) {
                    printf("Exclusão cancelada!\n");
                    sleep(2); 
                    return;   
                } else {
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opexc != 1 && opexc != 2);

            break; 
        }
    }

    if (!encontrado) {
        printf("Produto com código %d não encontrado.\n", codigo);
        return;
    }

    // Abrir o arquivo para reescrita e salvar os produtos atualizados
    arq = fopen("Estoque.csv", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(arq, "%s,%s,%s,%d,%f,%s,%.2f\n",
                produtos[i].nome, produtos[i].tipo, produtos[i].fornecedor,
                produtos[i].codigo, produtos[i].quant, produtos[i].tipovend,
                produtos[i].valor);
    }
    fclose(arq);
}


//função para adicionar quantidades
void addquant(){

    FILE *arq;
    char Linha[200];
    Merc produtos[200]; // Array para armazenar produtos
    int count = 0, encontrado = 0, codigo;
    float quantidade;

    printf("\n==========================================\n");
    printf("|           ADICIONAR QUANTIDADES        |\n");
    printf("==========================================\n");

    // Abrir o arquivo para leitura
    arq = fopen("Estoque.csv", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Carregar todos os produtos em memória
    while (fgets(Linha, sizeof(Linha), arq) != NULL) {
        Merc produto;
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%f,%[^,],%f",
               produto.nome, produto.tipo, produto.fornecedor,
               &produto.codigo, &produto.quant, produto.tipovend,
               &produto.valor);
        produtos[count++] = produto;
    }
    fclose(arq);

    // Solicitar o código do produto
    printf("Digite o código do produto que deseja adicionar quantidades: ");
    scanf("%d", &codigo);
    system("cls");

    // Procurar o produto pelo código
    for (int i = 0; i < count; i++) {
        if (produtos[i].codigo == codigo) {
            encontrado = 1;

            //solicitando as quantidades
            printf("Produto encontrado: %s \t Quantidade Atual: %f\n", produtos[i].nome, produtos[i].quant);
            printf("Digite a quantidade que deseja adicionar: ");
            scanf("%f", &quantidade);
            if (quantidade > 0) {
                produtos[i].quant += quantidade;
                printf("Quantidade atualizada com sucesso! Nova quantidade: %f\n", produtos[i].quant);
            } else {
                printf("Quantidade inválida. Operação cancelada.\n");
                return;
            }
            break; // Produto encontrado e atualizado
        
        }
   }

        if (!encontrado) {
            printf("Produto com código %d não encontrado.\n", codigo);
            return;
        }

    // Abrir o arquivo para reescrita e salvar os produtos atualizados
    arq = fopen("Estoque.csv", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(arq, "%s,%s,%s,%d,%f,%s,%.2f\n",
                produtos[i].nome, produtos[i].tipo, produtos[i].fornecedor,
                produtos[i].codigo, produtos[i].quant, produtos[i].tipovend,
                produtos[i].valor);
    }
    fclose(arq);


}

//função para gerar o código do produto.
int geracod() {
    FILE *arq; 
    char linha[200];
    
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

            // Atualiza o maior código encontrado
            ultimocod = codigo;  
        }
    }
    
    fclose(arq);
    
    // Retorna o próximo código
    return ultimocod + 1;  
}




//função para imprimir a tela do estoque.
void Telaest() {
    printf(" _______________________________________");
    printf("\n|\t\tESTOQUE\t\t\t|\n");
    printf("|_______________________________________|");
    printf("\n _______________________________________");
    printf("\n|\t  [1] - Cadastrar Produtos\t|\n");
    printf("\n|\t  [2] - Consultar Cadastros\t|\n");
     printf("\n|\t  [0] - Menu Principal  \t|\n");
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
    printf("\n|\t      [1] - Estoque\t\t|\n");
    printf("\n|\t      [2] - Caixa\t\t|\n");
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
        do{
            setbuf(stdin, NULL);     
            fgets(produto.nome, sizeof(produto.nome), stdin);
            
            if (produto.nome[0] == '\n'){
                printf("É necessário um nome para o produto: ");
            }
        } while(produto.nome[0] == '\n') ;

        produto.nome[strcspn(produto.nome, "\n")] = '\0'; // Remover nova linha

        // Ler o tipo do produto
        printf("Selecione o novo tipo do produto (ou 0 para manter):\n");
             printf(" [1] - Fruta\n [2] - Verdura\n [3] - Legume\n [4] - Tempero\n [5] - Orgânico\n [6] - Outro\n");
                do{
                    scanf("%d", &optipo);
                    setbuf(stdin, NULL);

                    if (optipo>= 1 && optipo <= 6) {
                        switch (optipo) {
    
                            case 1: strcpy(produto.tipo, "Fruta"); 
                            break;

                            case 2: strcpy(produto.tipo, "Verdura"); 
                            break;

                            case 3: strcpy(produto.tipo, "Legume");
                            break;

                            case 4: strcpy(produto.tipo, "Tempero"); 
                            break;

                            case 5: strcpy(produto.tipo, "Orgânico"); 
                            break;

                            case 6: strcpy(produto.tipo, "Outro"); 
                            break;
                        }
                    }
                    else {
                        printf("Digite uma opção válida!\n");
                    }
                }while(optipo < 1 || optipo > 6);

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

        //a forma de venda do produto(UNIDADE/KG)
        printf(" A venda sera por: \n");
        printf(" [1] - UNIDADE\n");
        printf(" [2] - KG\n");
        do{
            scanf("%d", &opvend);
            if (opvend == 1){
            strcpy(produto.tipovend,"UN"); 
            }
            else if (opvend == 2){
            strcpy(produto.tipovend,"KG");
            }
            else {
                printf("opção inválida!");
            }
        }while(opvend != 1 && opvend != 2);
        
        //declarando a quantidade 
        if(opvend == 1){
            printf(" Quantiadade (não atribua números com casas decimais!!!): ");
            do{   
                setbuf(stdin, NULL);
                scanf("%f", &produto.quant);

                if(produto.quant <= 0){
                    printf("Quantidade inválida: ");
                }
            }while(produto.quant <= 0);
        }

        else if(opvend == 2){
            printf(" Quantidade em KG: ");
            do{   
                setbuf(stdin, NULL);
                scanf("%f", &produto.quant);
                if(produto.quant <= 0){
                    printf("Quantidade inválida: ");
                }
            }while(produto.quant <= 0);

        }
		
		//valor do produto
		 printf(" Valor: "); 
            do{   
                setbuf(stdin, NULL);
                scanf("%f", &produto.valor);
                if(produto.valor <= 0){
                    printf("Valor inválido: ");
                }
            }while(produto.valor <= 0);   
        
        

        // Armazenar os detalhes do produto no arquivo
        fprintf(arq, "%s,%s,%s,%d,%.2f,%s,%.2f\n", produto.nome, produto.tipo, produto.fornecedor, produto.codigo, produto.quant, produto.tipovend, produto.valor); 

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


//tela do caixa 
void telacaixa(){

    printf(" _______________________________________");
    printf("\n|\t\t CAIXA\t\t\t|\n");
    printf("|_______________________________________|");
    printf("\n _______________________________________");
    printf("\n|\t [1] - Realizar Venda\t\t|\n");
    printf("\n|\t [2] - Fluxo de Caixa\t\t|\n");
    printf(" _______________________________________\n");
    printf("|\t\t\t\t\t|\n");
    printf("|\t  Selecione uma opcao: \t\t|");
    printf("\n|_______________________________________|\n\n");
    printf("\n\n");
}

//função para realizar venda
void venda() {
   FILE *arq, *fluxo;
    char Linha[200];
    Merc produtos[200]; // Array para armazenar produtos
    int count = 0, encontrado = 0, codigo, frete;
    float quantidade, total = 0.0;

    printf("\n==========================================\n");
    printf("|                 CARRINHO                  |\n");
    printf("==========================================\n");

    // Abrir o arquivo de estoque para leitura
    arq = fopen("Estoque.csv", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    // Carregar todos os produtos em memória
    while (fgets(Linha, sizeof(Linha), arq) != NULL) {
        Merc produto;
        sscanf(Linha, "%[^,],%[^,],%[^,],%d,%f,%[^,],%f",
               produto.nome, produto.tipo, produto.fornecedor,
               &produto.codigo, &produto.quant, produto.tipovend,
               &produto.valor);
        produtos[count++] = produto;
    }
    fclose(arq);

    // Abrir o arquivo de fluxo diário para escrita (adicionando ao final)
    fluxo = fopen("FluxoDiario.csv", "a");
    if (fluxo == NULL) {
        printf("Erro ao abrir o arquivo de fluxo diário!\n");
        return;
    }

    // Obter a data e hora atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fluxo, "Data: %02d/%02d/%04d Hora: %02d:%02d:%02d\n",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);

    while (1) {
        printf("\nProdutos disponíveis:\n");
        printf("Código\t\tNome\tUnidade\t\tQuantidade\tPreço\n");
        for (int i = 0; i < count; i++) {
            printf("%d\t\t%s\t  %s\t\t  %.2f\t\tR$ %.2f\n", 
                   produtos[i].codigo, produtos[i].nome, produtos[i].tipovend,
                   produtos[i].quant, produtos[i].valor);
        }

        // Solicitar o código do produto
        printf("\nDigite o código do produto para vender (ou 0 para finalizar): ");
        scanf("%d", &codigo);

        // Encerrar o caixa
        if (codigo == 0) {
            printf("Opções de venda\n[1] - Presencial\n[2] - Online\n");
            do{
                scanf("%d", &frete);
                if(frete == 1) {

                    total = total;
                
                }

                else if (frete == 2){

                    total += 11.90;

                }

                else{

                    printf("Opcão de venda inválida");
                }
            }while(frete != 1 && frete != 2);

            printf("\nVenda finalizada. Total da compra: R$ %.2f\n", total);
            fprintf(fluxo, "Total da compra: R$ %.2f\n\n", total);
            break;
        }

        // Procurar o produto pelo código
        encontrado = 0;
        for (int i = 0; i < count; i++) {
            if (produtos[i].codigo == codigo) {
                encontrado = 1;

                // Exibir informações do produto
                printf("Produto selecionado: %s\n", produtos[i].nome);

                // Verificar se é vendido por unidade ou peso
                int result = strcmp(produtos[i].tipovend, "UN");

                 if((result = 0)){
                    printf("Quantidade disponível: %.2f\n", produtos[i].quant);
                }

                else if (!result){
                    printf("Quantidade disponível em KG: %.2f\n", produtos[i].quant);
                }

                printf("Digite a quantidade que deseja vender: ");
                scanf("%f", &quantidade);

                // Verificar se há estoque suficiente
                if (quantidade > 0 && quantidade <= produtos[i].quant) {
                    produtos[i].quant -= quantidade; // Atualizar o estoque
                    float subtotal = quantidade * produtos[i].valor;
                    total += subtotal; // Atualizar o total da venda
                    printf("Venda realizada! Subtotal: R$ %.2f\n", subtotal);

                    // Registrar a venda no arquivo de fluxo diário
                    fprintf(fluxo, "Produto: %s, Quantidade: %.2f, Subtotal: R$ %.2f\n",
                            produtos[i].nome, quantidade, subtotal);
                } else {
                    printf("Quantidade inválida ou insuficiente em estoque.\n");
                }
                break;
            }
        }

        if (!encontrado) {
            printf("Produto com código %d não encontrado.\n", codigo);
        }
    }

    fclose(fluxo);

    // Abrir o arquivo para reescrita e salvar os produtos atualizados
    arq = fopen("Estoque.csv", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de estoque para salvar!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(arq, "%s,%s,%s,%d,%.2f,%s,%.2f\n",
                produtos[i].nome, produtos[i].tipo, produtos[i].fornecedor,
                produtos[i].codigo, produtos[i].quant, produtos[i].tipovend,
                produtos[i].valor);
    }
    fclose(arq);

    printf("\nEstoque atualizado com sucesso!\n");
}

void fluxocaixa(Transacao *transacao){

        FILE *arq = fopen("FluxoCaixa.csv", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de fluxo de caixa!\n");
        return;
    }

    fprintf(arq, "%s,%d,%.2f,%.2f,%s\n",
            transacao->item, transacao->quantidade,
            transacao->valor_unitario, transacao->valor_total,
            transacao->data);

    fclose(arq);

}

void lerfluxo(){

FILE *fluxo;
    char linha[200];

    printf("\n==========================================\n");
    printf("|\t     FLUXO DE VENDAS\t\t |\n");
    printf("==========================================\n");

    // Abrir o arquivo de fluxo diário
    fluxo = fopen("FluxoDiario.csv", "r");
    if (fluxo == NULL) {
        printf("Erro ao abrir o arquivo de fluxo diário!\n");
        return;
    }

    // Ler e exibir cada linha do arquivo
    while (fgets(linha, sizeof(linha), fluxo) != NULL) {
        printf("%s", linha);
    }

    fclose(fluxo); // Fechar o arquivo após a leitura
    printf("\n==========================================\n");
    printf("\t  Fim do fluxo diário.\n");;

}


int main() {
	setlocale(LC_ALL, "Portuguese_Brazil");
    int op;
    do {
        Telainicial();
        scanf("%d", &op);
        system("cls");

        //switch principal
        switch (op) {
            case 0:
                printf("\nExecução Finalizada!!!\n");
                break;

            //estoque
            case 1:
                Telaest();
                int opest;
                scanf("%d", &opest);
                system("cls");
                
                //switch do estoque
                switch(opest){

                    case 0:
                    break;;

                	case 1:
                		Cadprod();
                	break;
                		
                	case 2:
                		mostrarprod();
                		int oprod;
                		scanf("%d", &oprod);

                        //switch de manipulação de produtos
                        switch (oprod){

                            case 0:
                                system("cls");
                            break;;

                            case 1:
                                editprod();
                            break;
                                
                            case 2:
                                removerprod();
                            break;

                            case 3:
                                addquant();
                            break;

                            default:
                                printf("Opcao invalida! Tente novamente.\n");
                            break;;
                        }   
                		
				}
                break; // para voltar ao menu principal

                
            //caixa
            case 2:
                telacaixa();
                int opcaixa;
                scanf("%d", &opcaixa);

                switch(opcaixa){

                    case 1:
                        venda();
                    break;

                    case 2:
                        lerfluxo();   
                    break;


                    








                }



            break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    } while (op != 0);

    return 0;
}