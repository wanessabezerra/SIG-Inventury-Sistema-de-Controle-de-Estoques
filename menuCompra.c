#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int validacaoEhNumero(char);
int validacaoEhLetra(char);
int validacaoPalavra(char[]);
int validacaoEhLetra1(char);
int validacaoPalavra1(char[]);
int validacaoCod(char *);
int validacaoCod2(char *);

typedef struct compra Compra;

struct compra {
  char cod[6];
  char cod2[5];
  char nome[15];
  char marca[15];
  char status;
  int qntd;
  
};

int menuCompra(void);
void cadastraCompra(void);
void buscaCompra(void);
void editaCompra(void);
void excluiCompra(void);
void listaCompra(void);
void exibeCompra(Compra*);
void gravaCompra(Compra*);
void dataEhora(Compra*);


int main(void) {
  int opcao;
  opcao = menuCompra();
  while (opcao != 0) {
    switch (opcao) {
      case 1 :  cadastraCompra();
                break;
      case 2 :  buscaCompra();
                break;
      case 3 :  editaCompra();
                break;
      case 4 :  excluiCompra();
                break;
      case 5 :  listaCompra();
                break;
    }
    opcao = menuCompra();
  }
  printf("\nFim do programa!\n\n");
  return 0;
}

int menuCompra(void) {
  int op;
  printf("\n\n");
  printf("= = = = = = = = = = = = = = = = = = = \n");
  printf("= = = =  Compras de Produto  = = = = \n");
  printf("= = = = = = = = = = = = = = = = = = = \n");
  printf("1 - Cadastrar Compras\n");
  printf("2 - Pesquisar Compras\n");
  printf("3 - Atualizar Compras\n");
  printf("4 - Deletar Compras\n");
  printf("5 - Listar todos as Compras\n");
  printf("0 - Retornar\n");
  printf("Escolha sua opção: ");
  scanf("%d", &op);
  system("cls || clear");
  return op;
}


void cadastraCompra(void) {
  Compra* compra;
  printf("\n\n");
  printf(" = = = = = = = = = = = = = = = = =\n");
  printf(" =  Cadastrar Compra de Produtos =\n");
  printf(" = = = = = = = = = = = = = = = = =\n");
  compra = (Compra*) malloc(sizeof(Compra));
  printf("\nInforme o código da empresa: ");
  scanf("%4s", compra->cod2);
  while((validacaoCod2(compra->cod2)!=1)) {
    printf("inválido");
    printf("\nInforme o código da empresa: ");
    scanf("%4s", compra->cod2);
  }
  printf("Informe o código do produto: ");
  scanf("%5s", compra->cod);
  while((validacaoCod(compra->cod)!=1)) {
    printf("inválido");
    printf("\nInforme o código do produto: ");
    scanf("%5s", compra->cod);
  }
  printf("Informe o nome do produto: ");
  scanf(" %14[^\n]", compra->nome);
  while((validacaoPalavra(compra->nome)!= 1)) {
    printf("inválido");
    printf("\nInforme o nome do produto: ");
    scanf(" %14[^\n]", compra->nome);
  }
  printf("Informe a marca do produto: ");
  scanf(" %14[^\n]", compra->marca);
  while((validacaoPalavra1(compra->marca)!= 1)) {
    printf("inválido");
    printf("\nInforme a marca do produto: ");
    scanf(" %14[^\n]", compra->marca);
  }
  printf("Informe a quantidade do produto: ");
  scanf("%d", &compra->qntd);
  while((validacaoEhNumero(compra->qntd)!=1)) {
    printf("inválido");
    printf("\nInforme a quantidade do produto: ");
    scanf("%d", &compra->qntd);
  }
  (dataEhora(compra));
  getchar();
  compra->status = '1';
  printf("###############################\n");
  exibeCompra(compra);
  printf("###############################\n");
  gravaCompra(compra);
}


void buscaCompra(void) {
  FILE* fp;
  Compra* compra;
  int achou;
  char procurado[15];
  fp = fopen("compra.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("= = = = = = = = = = = = \n");
  printf("= =  Buscar Compras = = \n");
  printf("= = = = = = = = = = = = \n");
  printf("Informe o codigo do produto a ser buscado: ");
  scanf(" %14[^\n]", procurado);
  compra = (Compra*) malloc(sizeof(Compra));
  achou = 0;
  while((!achou) && (fread(compra, sizeof(Compra), 1, fp))) {
   if ((strcmp(compra->cod, procurado) == 0) && (compra->status == '1')) {
     achou = 1;
   }
  }
  fclose(fp);
  if (achou) {
    exibeCompra(compra);
  } else {
    printf("O produto %s não foi encontrado...\n", procurado);
  }
  free(compra);
}

void editaCompra(void) {
  FILE* fp;
  Compra* compra;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("compra.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("= = = = = = = = = = = \n");
  printf("= = Editar compras = = \n");
  printf("= = = = = = = = = = = \n");
  printf("Informe o código do produto a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  compra = (Compra*) malloc(sizeof(Compra));
  achou = 0;
  while((!achou) && (fread(compra, sizeof(Compra), 1, fp))) {
   if ((strcmp(compra->cod, procurado) == 0) && (compra->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibeCompra(compra);
    getchar();
    printf("Deseja realmente editar este produto (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("\nInforme o código do produto: ");
      scanf("%5s", compra->cod);
      while((validacaoCod(compra->cod)!=1)) {
        printf("inválido");
        printf("\nInforme o código do produto: ");
        scanf("%5s", compra->cod);
      }
      printf("Informe o nome do produto: ");
      scanf(" %14[^\n]", compra->nome);
      while((validacaoPalavra(compra->nome)!= 1)) {
        printf("inválido");
        printf("\nInforme o nome do produto: ");
        scanf(" %14[^\n]", compra->nome);
      }
      printf("Informe a marca do produto: ");
      scanf(" %14[^\n]", compra->marca);
      while((validacaoPalavra1(compra->marca)!= 1)) {
        printf("inválido");
        printf("\nInforme a marca do produto: ");
        scanf(" %14[^\n]", compra->marca);
      }
      printf("Informe a quantidade disponivel do produto: ");
      scanf("%d", &compra->qntd);
      while((validacaoEhNumero(compra->qntd)!=1)) {
        printf("inválido");
        printf("\nInforme a quantidade do produto: ");
        scanf("%d", &compra->qntd);
      }
      getchar();
      compra->status = '1';
      fseek(fp, (-1)*sizeof(Compra), SEEK_CUR);
      fwrite(compra, sizeof(Compra), 1, fp);
      printf("\nProduto editado com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
  } else {
    printf("O produto %s não foi encontrado...\n", procurado);
  }
  free(compra);
  fclose(fp);
}


void excluiCompra(void) {
  FILE* fp;
  Compra* compra;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("compra.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("= = = = = = = =  = = = \n");
  printf("= = Apagar Compra = = \n");
  printf("= = = = = = = = =  = = \n");
  printf("Informe o código do produto a ser apagado: ");
  scanf(" %14[^\n]", procurado);
  compra = (Compra*) malloc(sizeof(Compra));
  achou = 0;
  while((!achou) && (fread(compra, sizeof(Compra), 1, fp))) {
   if ((strcmp(compra->cod, procurado) == 0) && (compra->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibeCompra(compra);
    getchar();
    printf("Deseja realmente apagar este produto (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      compra->status = '0';
      fseek(fp, -1*sizeof(Compra), SEEK_CUR);
      fwrite(compra, sizeof(Compra), 1, fp);
      printf("\nProduto excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O produto %s não foi encontrado...\n", procurado);
  }
  fclose(fp);
  free(compra);
}


void listaCompra(void) {
  FILE* fp;
  Compra* compra;
  fp = fopen("compra.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("= = = = = = = = = = = \n");
  printf("= = Exibe Compras = = \n");
  printf("= = = = = = = = = = = \n");
  compra = (Compra*) malloc(sizeof(Compra));
  while(fread(compra, sizeof(Compra), 1, fp)) {
    if (compra->status == '1') {
      exibeCompra(compra);
    }
  }
  fclose(fp);
  free(compra);
}


void gravaCompra(Compra* compra) {
  FILE* fp;
  fp = fopen("compra.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(compra, sizeof(Compra), 1, fp);
  fclose(fp);
}


void exibeCompra(Compra* compra) {
  printf("Código da Empresa: %s\n", compra->cod2);
  printf("Código do produto: %s\n", compra->cod);
  printf("Nome: %s\n", compra->nome);
  printf("Marca: %s\n", compra->marca);
  printf("Quantidade: %d\n", compra->qntd);
  (dataEhora(compra));
  printf("\n");
}

void dataEhora(Compra* compra) {
  FILE* fp;
  fp = fopen("compra.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  struct tm *data_hora_atual;     
  
  time_t segundos;  
  time(&segundos);     
  data_hora_atual = localtime(&segundos);
  
  printf("\nHora de entrada: %d:",data_hora_atual->tm_hour-3);printf("%d:",data_hora_atual->tm_min);
  printf("%d\n",data_hora_atual->tm_sec);
  printf("\nData de entrada: %d/", data_hora_atual->tm_mday);
  printf("%d/",data_hora_atual->tm_mon+1);
  printf("%d\n\n",data_hora_atual->tm_year+1900);
  fclose(fp);
}

int validacaoEhNumero(char c) {
  if (c>='0'&& c<='9') {
    return 0;
  }
  else {
    return 1;
  }
}

int validacaoPalavra(char s[]) {
  int tam;
  tam = strlen(s) - 1;
  for (int i = 0; i < tam; i++) {
    if (!validacaoEhLetra(s[i])) {
      return 0;
    }
  }
  return 1;
}

int validacaoEhLetra(char c) {
  if (c>='A' && c<='Z') {
    return 1;
  }
  else if (c>='a' && c<='z') {
    return 1;
  }
  else {
    return 0;
  }
}

int validacaoPalavra1(char s[]) {
  int tam;
  tam = strlen(s);
  for (int i = 0; i < tam; i++) {
    if (!validacaoEhLetra(s[i])) {
      return 0;
    }
  }
  return 1;
}

int validacaoEhLetra1(char c) {
  if (c>='A' && c<='Z') {
    return 1;
  }
  else if (c>='a' && c<='z') {
    return 1;
  }
  else {
    return 0;
  }
}

int validacaoCod2(char *codi){
    if(strlen(codi) != 4)
        return 0;
    else if((strcmp(codi,"0000") == 0) || (strcmp(codi,"1111") == 0) || (strcmp(codi,"2222") == 0) ||
            (strcmp(codi,"3333") == 0) || (strcmp(codi,"4444") == 0) || (strcmp(codi,"5555") == 0) ||
            (strcmp(codi,"6666") == 0) || (strcmp(codi,"7777") == 0) || (strcmp(codi,"8888") == 0) ||
            (strcmp(codi,"9999") == 0))
        return 0;
    else {
      return 1;
    }
}

int validacaoCod(char *codi){
    if(strlen(codi) != 5)
        return 0;
    else if((strcmp(codi,"0000") == 0) || (strcmp(codi,"1111") == 0) || (strcmp(codi,"2222") == 0) ||
            (strcmp(codi,"3333") == 0) || (strcmp(codi,"4444") == 0) || (strcmp(codi,"5555") == 0) ||
            (strcmp(codi,"6666") == 0) || (strcmp(codi,"7777") == 0) || (strcmp(codi,"8888") == 0) ||
            (strcmp(codi,"9999") == 0))
        return 0;
    else {
      return 1;
    }
}
