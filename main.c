#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//criacao de todas funcoes
int gerar_id();
struct produto criar_produto();
void salvar_produto(struct produto p, int id);
void Trans_Maius(char *str);
void Listar();
void List_S();
void Lista_Comp();
void Pausa_Seguir();
void Lista_Filtro();
void Update(int id);
void Delete_Prod(int id);

//estrutura do produto
struct produto {
	char Marca[15];
	char Tipo[10];
	char Modelo[20];
	char Sexo;
	char Cor[10];
	int Tamanho;
	int Ano;
};

//principal
int main()
{
	int sair = 0;
	do {
		int opcao = 0;
		int op = 0;
		printf("\033[1;34mBEM VINDO A CALSARAH\033[0m\n");
		printf("\033[35mby owners: Jonathan Matthias & Andrea Doriah\033[0m");
		printf("\n\n\n\n");
		do {
			printf("1- Criar produto\n2- Listar produtos\n3- Atualizar produtos\n4- Deletar produto\n99- Sair\n");
			printf("sua opcao: ");
			scanf("%d", &opcao);
			printf("\n\n");
		} while(opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 &&  opcao != 99);

		switch(opcao) {
		case 1:
			do {
				int id = gerar_id();

				struct produto novo = criar_produto();

				if(novo.Marca[0] == '\0') {
					break; //cancelado
				}

				salvar_produto(novo, id);

				printf("criar novo produto? (1)nao (2)sim: ");
				scanf("%d", &op);
				system("clear");
			} while(op == 2);
			break;

		case 2:
			op = 0;
			Listar();
			break;

		case 3:
			//atualizar arquivo
			int up = 0;
			List_S();
			printf("informe o ID: ");
			scanf("%d", &up);
			Update(up);
			
			break;
		
		case 4:
		    //excluir o produto
		    int ex = 0;
		    List_S();
		    printf("informe o ID: ");
			scanf("%d", &ex);
			Delete_Prod(ex);
			
			break;

		case 99:
			printf("tchau ate mais");
			sair = 1;
			break;
		default:
			printf("opcao invalida");
			system("sleep 1");
			system("clear");
		}
	} while(sair != 1);

	return 0;
}

//gerar o numero
int gerar_id() {
	int id = 1;
	FILE *idCheck = fopen("id.txt", "r");
	if (idCheck == NULL) {
		FILE *initID = fopen("id.txt", "w");
		if (initID != NULL) {
			fprintf(initID, "%d", id); // ComeC'a do 1
			fclose(initID);
		}
		else {
			printf("Erro ao criar arquivo de ID.\n");
			return EXIT_FAILURE;
		}
	} else {
		fscanf(idCheck, "%d", &id);
		fclose(idCheck); // JC! existe, sC3 fecha
	}
	return id;
}

//transformar para maiusculo
void Trans_Maius(char *str) {
	for(int i = 0; str[i] != '\0'; i++) {
		if(str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
}


//geracao do produto
struct produto criar_produto() {
	int op = 0;
	struct produto prod1;

	while (1) {
		system("clear");
		printf("certo iremos criar seu produto\n");
		printf("marca: ");
		scanf("%14s", prod1.Marca);
		printf("tipo: ");
		scanf("%9s", prod1.Tipo);
		printf("modelo: ");
		scanf("%19s", prod1.Modelo);
		do {
			printf("sexo (M ou F): ");
			scanf(" %c", &prod1.Sexo);
			if(prod1.Sexo == 'm' || prod1.Sexo == 'f') {
				prod1.Sexo -= 32;
			}
		} while (prod1.Sexo != 'M' && prod1.Sexo != 'm' && prod1.Sexo != 'f' && prod1.Sexo != 'F');
		printf("cor: ");
		scanf("%9s", prod1.Cor);
		do {
			printf("tamanho: ");
			scanf("%2d", &prod1.Tamanho);
		} while (prod1.Tamanho < 10);
		do {
			printf("ano: ");
			scanf("%4d", &prod1.Ano);
		} while (prod1.Ano < 1500 || prod1.Ano > 2050);

		printf("\nConfirme os dados:\n");
		printf("%s %s %s %c %s %d %d\n", prod1.Marca, prod1.Tipo, prod1.Modelo, prod1.Sexo, prod1.Cor, prod1.Tamanho, prod1.Ano);
		printf("1- salvar\n2- tentar novamente\n3- cancelar\n");
		scanf("%d", &op);

		if (op == 1) {
			Trans_Maius(prod1.Marca);
			Trans_Maius(prod1.Tipo);
			Trans_Maius(prod1.Modelo);
			Trans_Maius(prod1.Cor);
			return prod1;
		}
		else if (op == 3) {
			struct produto vazio = {"", "", "", '\0', "", 0, 0};
			op = 0;
			return vazio;
		}
		// se digitar 2 repete o loop
	}
}

//salvamento do produto
void salvar_produto(struct produto prod1, int id) {
	FILE *f=fopen("sapatos.txt", "a");
	if(f == NULL) {
		printf("arquivo nao pode ser aberto.");
		system("sleep 1");
		system("clear");
		return;
	}

	fprintf(f, "%2d %15s %10s %20s %1c %10s %3d %4d\n", id, prod1.Marca, prod1.Tipo, prod1.Modelo, prod1.Sexo, prod1.Cor, prod1.Tamanho, prod1.Ano);
	fflush(f);
	fclose(f);


	FILE *i2 = fopen("id.txt", "w");
	if (i2 != NULL) {
		fprintf(i2, "%d", id + 1);
		fclose(i2);
	}
	system("clear");
	printf("\033[32mProduto salvo com sucesso!\033[0m\n");
	system("sleep 2");
	system("clear");
}

void Pausa_Seguir() {
	printf("Aperte ENTER para continuar...");
	getchar();
	getchar();
	system("clear");
}

void Lista_Comp() {
	FILE *f=fopen("id.txt", "r");
	char c;
	if (f == NULL) {
		printf("arquivo de id nao encontrado\n");
		printf("\033[33mFATAL_ERROR\033[0m\n");
	}
	else {
		while((c = fgetc(f)) != EOF) {
			printf("%c",c);
		}
		printf(" total de itens\n");
		fclose(f);
	}

	FILE *t = fopen("sapatos.txt", "r");
	char x;
	if (t == NULL) {
		printf("arquivo de produtos nao encontrado\n");
		printf("\033[33mFATAL_ERROR\033[0m\n\n\n");
	}
	else {
		system("clear");
		printf("ID|    MARCA      |   TIPO   |        MODELO      |S|   COR    |TAM| ANO |\n\n");
		while((x = fgetc(t)) != EOF) {
			printf("%c",x);
		}
		printf("\n\n");
		Pausa_Seguir();
		fclose(t);
	}
}

void List_S() {
	FILE *f=fopen("id.txt", "r");
	char c;
	if (f == NULL) {
		printf("arquivo de id nao encontrado\n");
		printf("\033[33mFATAL_ERROR\033[0m\n");
	}
	else {
		while((c = fgetc(f)) != EOF) {
			printf("%c",c);
		}
		printf(" total de itens\n");
		fclose(f);
	}

	FILE *t = fopen("sapatos.txt", "r");
	char x;
	if (t == NULL) {
		printf("arquivo de produtos nao encontrado\n");
		printf("\033[33mFATAL_ERROR\033[0m\n\n\n");
	}
	else {
		system("clear");
		printf("ID|    MARCA      |   TIPO   |        MODELO      |S|   COR    |TAM| ANO |\n\n");
		while((x = fgetc(t)) != EOF) {
			printf("%c",x);
		}
		printf("\n\n");
		fclose(t);
	}
}

void Lista_Filtro(const char* filtro, int tipo) {
	FILE *f = fopen("sapatos.txt", "r");
	if (f == NULL) {
		printf("erro ao abrir o arquivo\n");
		return;
	}

	struct produto p;
	int id;
	printf("ID    |    MARCA      |   TIPO  |        MODELO      |S|   COR    |TAM| ANO |\n\n");
	while (fscanf(f, "%d %s %s %s %c %s %d %d", &id, p.Marca, p.Tipo, p.Modelo, &p.Sexo, p.Cor, &p.Tamanho, &p.Ano) == 8) {
		switch(tipo) {
		case 1:
			if(strcmp(p.Marca, filtro) == 0) {
				printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
				break;
			}
		case 2:
			if(strcmp(p.Tipo, filtro) == 0) {
				printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
				break;
			}
		case 3:
			if(strcmp(p.Modelo, filtro) == 0) {
				printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
				break;
			}
		case 4:
			if(strcmp(p.Cor, filtro) == 0) {
				printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
				break;
			}
		case 5:
		    if(p.Tamanho == filtro){
		        printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
				break;
		    }
		case 6:
		    if(p.Ano == filtro){
		        printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
				break;
		    }
		case 7:
		    break;
		default:
		    printf("opcao invalida");
		    break;
		}
	}
	fclose(f);
}

void Listar() {
	int op = 0;
	system("clear");
	printf("1- listar todos os sapatos\n2- listar especifico\n");
	scanf("%d", &op);
	switch(op) {
	case 1:
		//fazer listagem completa
		Lista_Comp();
		break;
	case 2:
		//opcoes para listagem (cor, sexo, marca, tipo, tamanho, ano, modelo)
		do {
			char busca[20];
			int tipo;
			do {
				printf("filtrar por: 1-Marca 2-Tipo 3-Modelo 4-Cor 5-Tamanho 6-Ano 7-Sexo(erro)\nEscolha: ");
				scanf("%d", &tipo);
			} while(tipo < 1 || tipo > 7);
			system("clear");
			printf("Buscar: ");
			scanf("%19s", busca);
			Trans_Maius(busca);
			Lista_Filtro(busca, tipo);
			Pausa_Seguir();
			break;
		default:
			printf("opcao invalida");
			system("sleep 2");
			system("clear");
			break;
		} while(op != 1 && op != 2);
	}
}

void Update(int id){
    FILE *f = fopen("sapatos.txt", "r");
    if (f == NULL){
        printf("arquivo nao encontrado");
        return;
    }
    
    struct produto p;
    int upd;
    int idn;
    
    FILE *x = fopen("temp.txt", "w");
    
    while(fscanf (f, "%d %s %s %s %c %s %d %d",  &upd, p.Marca, p.Tipo, p.Modelo, &p.Sexo, p.Cor, &p.Tamanho, &p.Ano) == 8){
        
        if(upd == id){
            int conf = 0;
            printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
            printf("confirmar: 1-sim 2-nao\n");
            scanf("%d", &conf);
            while (getchar() != '\n');
            if(conf == 1){
                struct produto novo = criar_produto();
                fprintf(x, "%2d %15s %10s %20s %c %10s %2d %4d\n", id, novo.Marca, novo.Tipo, novo.Modelo, novo.Sexo, novo.Cor, novo.Tamanho, novo.Ano);
            }
            else if(conf == 2){
                printf("cancelando...");
                system("clear");
                continue;
            }
            else{
                printf("invalido");
                continue;
            }
        }
        else{
            fprintf(x, "%2d %15s %10s %20s %c %10s %2d %4d\n",  upd, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
        }
    }
    fclose(x);
    fclose(f);
    remove("sapatos.txt");
    rename("temp.txt", "sapatos.txt");
    system("clear");
    printf("ATUALIZADO COM EXITO\n");
    system("sleep 1");
    system("clear");
}

void Delete_Prod(int id){
    FILE *f = fopen("sapatos.txt", "r");
    if (f == NULL){
        printf("arquivo nao encontrado");
        return;
    }
    
    struct produto p;
    int upd;
    int idn = 1;
    
    FILE *x = fopen("temp.txt", "w");
    
    while(fscanf (f, "%d %s %s %s %c %s %d %d", &upd, p.Marca, p.Tipo, p.Modelo, &p.Sexo, p.Cor, &p.Tamanho, &p.Ano) == 8){
        
        if(upd == id){
            int conf = 0;
            printf("ID %2d %15s %10s %20s %1c %10s %3d %4d\n", id, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
            printf("confirmar: 1-sim 2-nao\n");
            scanf("%d", &conf);
            if(conf == 1){
                continue;
            }
            else if(conf == 2){
                printf("cancelando...");
                system("clear");
                break;
            }
            else{
                printf("invalido");
                break;
            }
        }
        else{
            fprintf(x, "%2d %15s %10s %20s %c %10s %2d %4d\n", idn, p.Marca, p.Tipo, p.Modelo, p.Sexo, p.Cor, p.Tamanho, p.Ano);
            idn++;
        }
    }
    fclose(x);
    fclose(f);
    remove("sapatos.txt");
    rename("temp.txt", "sapatos.txt");
    system("clear");
    printf("EXCLUIDO COM EXITO\n");
    system("sleep 1");
    system("clear");
    FILE *t = fopen("sapatos.txt", "r");
    if (t == NULL) {
        printf("Erro ao abrir sapatos.txt\n");
        return;
    }
    
    int linhas = 0;
    char linha[200];
    while(fgets(linha, sizeof(linha), t) != NULL){
        linhas++;
    }
    fclose(t);
    
    FILE *id_novo = fopen("id.txt", "w");
    if (id_novo == NULL){
         printf("Erro ao abrir id.txt\n");
        return;
    }
    fprintf(id_novo, "%d", linhas + 1);
    fclose(id_novo);
}









