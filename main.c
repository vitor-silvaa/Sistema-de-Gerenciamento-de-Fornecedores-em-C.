#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

struct fornecedor {
  char nome[MAX_SIZE];
  char representante[MAX_SIZE];
  char numero[MAX_SIZE];
  char cnpj[MAX_SIZE];
};

// Função para verificar se a string possui apenas dígitos
int is_all_digits(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isdigit(str[i])) {
      return 0;
    }
  }
  return 1;
}

// Função para validar o CNPJ (implementação simplificada)
int is_valid_cnpj(const char *cnpj) {
  // Verifica se o CNPJ possui 14 caracteres
  if (strlen(cnpj) != 14) {
    return 0;
  }

  // Verifica se todos os caracteres são dígitos
  for (int i = 0; cnpj[i] != '\0'; i++) {
    if (!isdigit(cnpj[i])) {
      return 0;
    }
  }

  // TODO: Implementar a validação completa do CNPJ

  return 1;
}
void adicionarFornecedor(FILE *arquivo) {
struct fornecedor novoFornecedor;

printf("Digite o nome do fornecedor: ");
scanf("%s", novoFornecedor.nome);
printf("Digite o nome do representante: ");
scanf("%s", novoFornecedor.representante);

// Validação do número de telefone
while (1) {
  printf("Digite o número do representante: ");
  scanf("%s", novoFornecedor.numero);

  // Verifica se a string possui apenas dígitos
  if (!is_all_digits(novoFornecedor.numero)) {
    printf("Erro: O número de telefone deve conter apenas dígitos.\n");
    continue;
  }

  // Verifica o tamanho da string
  int len = strlen(novoFornecedor.numero);
  if (len < 11) {
    printf("Erro: O número de telefone deve ter no mínimo 11 dígitos.\n");
    continue;
  }

  break;
}

// Validação do CNPJ
while (1) {
  printf("Digite o CNPJ do fornecedor: ");
  scanf("%s", novoFornecedor.cnpj);

  // Verifica se o CNPJ é válido
  if (!is_valid_cnpj(novoFornecedor.cnpj)) {
    printf("Erro: O CNPJ informado é inválido.\n");
    continue;
  }

  break;
}

  fprintf(arquivo, "%s %s %s %s\n", novoFornecedor.nome,
          novoFornecedor.representante, novoFornecedor.numero,
          novoFornecedor.cnpj);

  printf("\nFornecedor adicionado com sucesso!\n");
}

void exibirFornecedores(FILE *arquivo) {
  struct fornecedor fornecedor;
  rewind(arquivo);
  printf("\n** Lista de fornecedores **\n");
  while (fscanf(arquivo, "%s %s %s %s", fornecedor.nome,
                fornecedor.representante, fornecedor.numero,
                fornecedor.cnpj) != EOF) {
    printf("\nNome: %s\nRepresentante: %s\nNúmero: %s\nCNPJ: %s\n\n//////\n",
           fornecedor.nome, fornecedor.representante, fornecedor.numero,
           fornecedor.cnpj);
  }
}

void editarFornecedor(FILE *arquivo) {
  char nomeEditar[MAX_SIZE];
  struct fornecedor fornecedor;
  FILE *tempArquivo;
  tempArquivo = fopen("temp.txt", "w");

  printf("Digite o nome do fornecedor que deseja editar: ");
  scanf("%s", nomeEditar);

  rewind(arquivo);
  while (fscanf(arquivo, "%s %s %s %s", fornecedor.nome,
                fornecedor.representante, fornecedor.numero,
                fornecedor.cnpj) != EOF) {
    if (strcmp(fornecedor.nome, nomeEditar) == 0) {
      printf("\nDigite os novos dados:\n");
      printf("Nome: ");
      scanf("%s", fornecedor.nome);
      printf("Representante: ");
      scanf("%s", fornecedor.representante);
      printf("Número: ");
      scanf("%s", fornecedor.numero);
      printf("CNPJ: ");
      scanf("%s", fornecedor.cnpj);
      printf("\nFornecedor editado com sucesso!\n");
    }
    fprintf(tempArquivo, "%s %s %s %s\n", fornecedor.nome,
            fornecedor.representante, fornecedor.numero, fornecedor.cnpj);
  }

  fclose(arquivo);
  fclose(tempArquivo);
  remove("fornecedores.txt");
  rename("temp.txt", "fornecedores.txt");
}

void excluirFornecedor(FILE *arquivo)  {
  char nomeExcluir[MAX_SIZE];
  struct fornecedor fornecedor;
  FILE *tempArquivo;
 tempArquivo = fopen("temp.txt", "w");

  printf("Digite o nome do fornecedor que deseja excluir: ");
  scanf("%s", nomeExcluir);

  rewind(arquivo);
  int encontrado = 0;

while (fscanf(arquivo, "%s %s %s %s", fornecedor.nome, fornecedor.representante, fornecedor.numero, fornecedor.cnpj) != EOF) {   
    if (strcmp(fornecedor.nome, nomeExcluir) == 0){
      printf( "\nFornecedor excluído com sucesso!\n");
      encontrado=1;
    } else{
      fprintf(tempArquivo, "%s %s %s %s\n", fornecedor.nome,fornecedor.representante, fornecedor.numero, fornecedor.cnpj);
    }
}
fclose(arquivo);
fclose(tempArquivo);

if (!encontrado){
  printf("\nFornecedor não encontrado.\n");
  remove("temp.txt");
  return;
}
remove("fornecedores.txt");
rename("temp.txt", "fornecedores.txt");
}

void pesquisarFornecedor(FILE *arquivo){
  char nomePesquisar[MAX_SIZE];
  struct fornecedor fornecedor;

  printf ("digite o nome do fornecedor que deseja pesquisar: ");
  scanf("%s", nomePesquisar);
  rewind(arquivo);
  int encontrado = 0;
  while (fscanf(arquivo, "%s %s %s %s", fornecedor.nome, fornecedor.representante,fornecedor.numero,fornecedor.cnpj) != EOF){
    if (strcmp(fornecedor.nome, nomePesquisar) == 0){
     printf( "\nFornecedor encontrado:\n");
     printf("Nome: %s\nRepresentante: %s\nNúmero: %s\nCNPJ: %s\n\n", fornecedor.nome,fornecedor.representante,fornecedor.numero,fornecedor.cnpj);
      encontrado = 1;
      break;
    }
  }
  if (!encontrado){
    printf("\nFornecedor não encontrado.\n");
  }
}
void aguardarEnter() {
  printf("Pressione Enter para continuar...");
  while (getchar() != '\n'); 
}
int main() {
  FILE *arquivo;
  arquivo = fopen("fornecedores.txt", "a+");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n");
    return 1;
  }
  int opcao;
  do {
    printf("\nMenu:\n");
    printf("1. Adicionar fornecedor\n");
    printf("2. Exibir fornecedores\n");
    printf("3. Editar fornecedor\n");
    printf("4. Excluir fornecedor\n");
    printf("5. Pesquisar fornecedor\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      adicionarFornecedor(arquivo);
      aguardarEnter();
      
      break;
    case 2:
      exibirFornecedores(arquivo);
      aguardarEnter();
      break;
    case 3:
      editarFornecedor(arquivo);
      arquivo = fopen("fornecedores.txt", "r+");
      if (arquivo == NULL) {
        printf("Erro ao abrir arquivo após edição.\n");
        return 1;
      }
       aguardarEnter();
      break;
      case 4:
      excluirFornecedor(arquivo);
      arquivo = fopen("fornecedores.txt", "r+");
      if (arquivo == NULL){
        printf("Erro ao abrir arquivo após exclusão.\n");
        return 1;
      }
         aguardarEnter();
      break;  
      case 5:
      pesquisarFornecedor(arquivo);
         aguardarEnter();
      break;
    case 6:
      printf("Encerrando programa.\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 6);

  fclose(arquivo);
  return 0;    
}

