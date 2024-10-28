#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define NOTA_MINIMA 0.0
#define NOTA_MAXIMA 10.0
#define MEDIA_APROVACAO 7.0
#define FALTAS_MAXIMAS 20
#define ARQUIVO "alunos.txt"
#define ARQUIVO_BINARIO "alunos.bin"

typedef struct {
  char nome[50];
  int matricula;
  float notas[3];
  float media;
  int faltas;
} Aluno;

// Funções do sistema
void adicionarAluno(Aluno *alunos, int *quantidade);
void editarAluno(Aluno *alunos, int quantidade);
void removerAluno(Aluno *alunos, int *quantidade);
void calcularMedia(Aluno *aluno);
void listarAlunos(Aluno *alunos, int quantidade);
void buscarAluno(Aluno *alunos, int quantidade, int matricula);
void listarAprovadosReprovados(Aluno *alunos, int quantidade);
void salvarDados(Aluno *alunos, int quantidade);
void salvarDadosBinario(Aluno *alunos, int quantidade);
void carregarDados(Aluno *alunos, int *quantidade);
void carregarDadosBinario(Aluno *alunos, int *quantidade);
int buscarIndiceAluno(Aluno *alunos, int quantidade, int matricula);
int validarNota(float nota);
int validarNotaInput(char *input);

int main() {
  Aluno alunos[MAX_ALUNOS];
  int quantidade = 0;
  int opcao, matricula;

  carregarDados(alunos, &quantidade);

  do {
    printf("\nSistema de Gerenciamento de Alunos\n");
    printf("1. Adicionar Aluno\n");
    printf("2. Editar Aluno\n");
    printf("3. Remover Aluno\n");
    printf("4. Listar Alunos\n");
    printf("5. Buscar Aluno\n");
    printf("6. Relatório de Aprovados/Reprovados\n");
    printf("7. Salvar e Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      adicionarAluno(alunos, &quantidade);
      break;
    case 2:
      editarAluno(alunos, quantidade);
      break;
    case 3:
      removerAluno(alunos, &quantidade);
      break;
    case 4:
      listarAlunos(alunos, quantidade);
      break;
    case 5:
      printf("Digite a matrícula do aluno: ");
      if (scanf("%d", &matricula) != 1) {
        printf("A matrícula deve conter apenas números.\n");
        while (getchar() != '\n')
          ;
        break;
      }
      buscarAluno(alunos, quantidade, matricula);
      break;
    case 6:
      listarAprovadosReprovados(alunos, quantidade);
      break;
    case 7:
      salvarDados(alunos, quantidade);
      salvarDadosBinario(alunos, quantidade);
      printf("Dados salvos em texto e binário. Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (opcao != 7);

  return 0;
}

void adicionarAluno(Aluno *alunos, int *quantidade) {
    if (*quantidade >= MAX_ALUNOS) {
        printf("Limite de alunos atingido!\n");
        return;
    }

    Aluno novoAluno;
    char notaStr[10];
    char matriculaStr[10]; // Nova variável para armazenar a matrícula como string

    // Alteração: leitura da matrícula como string
    do {
        printf("Matrícula do aluno: ");
        scanf("%s", matriculaStr);

        if (validarMatricula(matriculaStr)) {
            novoAluno.matricula = atoi(matriculaStr); // Converte a string para inteiro
            if (buscarIndiceAluno(alunos, *quantidade, novoAluno.matricula) != -1) {
                printf("Matrícula já existente! Aluno não foi adicionado.\n");
                return;
            }
            break; // Matrícula válida e única, saímos do loop
        } else {
            printf("Matrícula inválida! Deve conter apenas números.\n");
        }
    } while (1);

    printf("Nome do aluno: ");
    scanf(" %[^\n]", novoAluno.nome);

    for (int i = 0; i < 3; i++) {
        int notaValida = 0;
        do {
            printf("Nota %d: ", i + 1);
            scanf("%s", notaStr);

            if (validarNotaInput(notaStr)) {
                novoAluno.notas[i] = atof(notaStr);
                if (validarNota(novoAluno.notas[i])) {
                    notaValida = 1;
                } else {
                    printf("Nota inválida! Digite uma nota entre %.1f e %.1f.\n",
                           NOTA_MINIMA, NOTA_MAXIMA);
                }
            } else {
                printf("A nota deve conter apenas números. Tente novamente.\n");
            }
        } while (!notaValida);
    }

    printf("Quantidade de faltas: ");
    scanf("%d", &novoAluno.faltas);

    calcularMedia(&novoAluno);
    alunos[*quantidade] = novoAluno;
    (*quantidade)++;
    printf("Aluno adicionado com sucesso!\n");
}

int validarMatricula(char *input) {
  for (int i = 0; input[i] != '\0'; i++) {
      if (!isdigit(input[i])) {
          return 0; // Se não for um dígito, retorna 0 (falso)
      }
  }
  return 1; // Se todos os caracteres forem dígitos, retorna 1 (verdadeiro)
}
// Função para editar um aluno
void editarAluno(Aluno *alunos, int quantidade) {
  int matricula, indice;

  printf("Digite a matrícula do aluno para editar: ");
  char matriculaStr[10];
  scanf("%s", matriculaStr);

  if (!validarMatricula(matriculaStr)) {
      printf("A matrícula deve conter apenas números.\n");
      return;
  }

  matricula = atoi(matriculaStr); // Converte a string para inteiro

  indice = buscarIndiceAluno(alunos, quantidade, matricula);
  if (indice == -1) {
      printf("Aluno não encontrado.\n");
      return;
  }

  Aluno *aluno = &alunos[indice];
  printf("Editando aluno: %s\n", aluno->nome);

  printf("Novo nome do aluno: ");
  scanf(" %[^\n]", aluno->nome);

  for (int i = 0; i < 3; i++) {
      char notaStr[10];
      int notaValida = 0;
      do {
          printf("Nova Nota %d: ", i + 1);
          scanf("%s", notaStr);

          if (validarNotaInput(notaStr)) {
              aluno->notas[i] = atof(notaStr);
              if (validarNota(aluno->notas[i])) {
                  notaValida = 1;
              } else {
                  printf("Nota inválida! Digite uma nota entre %.1f e %.1f.\n",
                         NOTA_MINIMA, NOTA_MAXIMA);
              }
          } else {
              printf("A nota deve conter apenas números. Tente novamente.\n");
          }
      } while (!notaValida);
  }

  printf("Nova quantidade de faltas: ");
  scanf("%d", &aluno->faltas);

  calcularMedia(aluno);
  printf("Aluno editado com sucesso!\n");
}

// Função para remover um aluno

void removerAluno(Aluno *alunos, int *quantidade) {
  int matricula, indice;

  printf("Digite a matrícula do aluno para remover: ");
  if (scanf("%d", &matricula) != 1) {
    printf("A matrícula deve conter apenas números.\n");
    while (getchar() != '\n')
      ;
    return;
  }

  indice = buscarIndiceAluno(alunos, *quantidade, matricula);
  if (indice == -1) {
    printf("Aluno não encontrado.\n");
    return;
  }

  for (int i = indice; i < *quantidade - 1; i++) {
    alunos[i] = alunos[i + 1];
  }

  (*quantidade)--;
  printf("Aluno removido com sucesso!\n");
}

// Função para calcular a média do aluno
void calcularMedia(Aluno *aluno) {
  float soma = 0;
  for (int i = 0; i < 3; i++) {
    soma += aluno->notas[i];
  }
  aluno->media = soma / 3;
}



// Função para listar todos os alunoss
void listarAlunos(Aluno *alunos, int quantidade) {
  if (quantidade == 0) {
    printf("Nenhum aluno cadastrado.\n");
    return;
  }

  for (int i = 0; i < quantidade; i++) {
    printf("Aluno: %s\n", alunos[i].nome);
    printf("Matrícula: %d\n", alunos[i].matricula);
    printf("Notas: %.2f, %.2f, %.2f\n", alunos[i].notas[0], alunos[i].notas[1],
           alunos[i].notas[2]);
    printf("Média: %.2f\n", alunos[i].media);
    printf("Faltas: %d\n\n", alunos[i].faltas);
  }
}

// Função para buscar um aluno pela matrícula
void buscarAluno(Aluno *alunos, int quantidade, int matricula) {
  int indice = buscarIndiceAluno(alunos, quantidade, matricula);
  if (indice == -1) {
    printf("Aluno não encontrado.\n");
    return;
  }

  Aluno *aluno = &alunos[indice];
  printf("Aluno encontrado:\n");
  printf("Nome: %s\n", aluno->nome);
  printf("Matrícula: %d\n", aluno->matricula);
  printf("Notas: %.2f, %.2f, %.2f\n", aluno->notas[0], aluno->notas[1],
         aluno->notas[2]);
  printf("Média: %.2f\n", aluno->media);
  printf("Faltas: %d\n", aluno->faltas);
}


// Função para listar alunos aprovados e reprovados
void listarAprovadosReprovados(Aluno *alunos, int quantidade) {
  printf("\nAlunos Aprovados:\n");
  for (int i = 0; i < quantidade; i++) {
    if (alunos[i].media >= MEDIA_APROVACAO &&
        alunos[i].faltas <= FALTAS_MAXIMAS) {
      printf("Nome: %s, Matrícula: %d\n", alunos[i].nome, alunos[i].matricula);
    }
  }

  printf("\nAlunos Reprovados:\n");
  for (int i = 0; i < quantidade; i++) {
    if (alunos[i].media < MEDIA_APROVACAO ||
        alunos[i].faltas > FALTAS_MAXIMAS) {
      printf("Nome: %s, Matrícula: %d\n", alunos[i].nome, alunos[i].matricula);
    }
  }
}

// Função para salvar dados dos alunos em arquivo de texto organizado
void salvarDados(Aluno *alunos, int quantidade) {
  FILE *arquivo = fopen(ARQUIVO, "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para salvar os dados.\n");
    return;
  }

  for (int i = 0; i < quantidade; i++) {
    fprintf(arquivo, "Nome: %s\n", alunos[i].nome);
    fprintf(arquivo, "Matrícula: %d\n", alunos[i].matricula);
    fprintf(arquivo, "Notas: %.2f, %.2f, %.2f\n", alunos[i].notas[0],
            alunos[i].notas[1], alunos[i].notas[2]);
    fprintf(arquivo, "Média: %.2f\n", alunos[i].media);
    fprintf(arquivo, "Faltas: %d\n", alunos[i].faltas);
    fprintf(arquivo, "-------------------------\n");
  }

  fclose(arquivo);
  printf("Dados salvos no arquivo texto com sucesso.\n");
}


// Função para carregar dados dos alunos do arquivo de texto
void carregarDados(Aluno *alunos, int *quantidade) {
  FILE *arquivo = fopen(ARQUIVO, "r");
  if (arquivo == NULL) {
    printf("Nenhum arquivo de dados encontrado. Criando novo arquivo...\n");
    return;
  }

  *quantidade = 0;
  while (fscanf(arquivo,
                " Nome: %[^\n]\n Matrícula: %d\n Notas: %f, %f, %f\n Média: "
                "%f\n Faltas: %d\n -------------------------\n",
                alunos[*quantidade].nome, &alunos[*quantidade].matricula,
                &alunos[*quantidade].notas[0], &alunos[*quantidade].notas[1],
                &alunos[*quantidade].notas[2], &alunos[*quantidade].media,
                &alunos[*quantidade].faltas) == 7) {
    (*quantidade)++;
  }

  fclose(arquivo);
  printf("Dados carregados do arquivo texto com sucesso!\n");
}

// Função para salvar dados dos alunos em arquivo binário
void salvarDadosBinario(Aluno *alunos, int quantidade) {
  FILE *arquivo = fopen(ARQUIVO_BINARIO, "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para salvar os dados em binário.\n");
    return;
  }

  // Salva a quantidade de alunos primeiro
  if (fwrite(&quantidade, sizeof(int), 1, arquivo) != 1) {
    printf("Erro ao salvar a quantidade de alunos no arquivo binário.\n");
    fclose(arquivo);
    return;
  }

  // Salva todos os alunos
  if (fwrite(alunos, sizeof(Aluno), quantidade, arquivo) != quantidade) {
    printf("Erro ao salvar os dados dos alunos no arquivo binário.\n");
    fclose(arquivo);
    return;
  }

  fclose(arquivo);
  printf("Dados salvos no arquivo binário com sucesso.\n");
}

// Função para carregar dados dos alunos de arquivo binário
void carregarDadosBinario(Aluno *alunos, int *quantidade) {
  FILE *arquivo = fopen(ARQUIVO_BINARIO, "rb");
  if (arquivo == NULL) {
    printf("Nenhum arquivo binário encontrado. Criando novo...\n");
    *quantidade = 0;
    return;
  }

  // Lê a quantidade de alunos primeiro
  if (fread(quantidade, sizeof(int), 1, arquivo) != 1) {
    printf("Erro ao ler a quantidade de alunos do arquivo binário.\n");
    fclose(arquivo);
    return;
  }

  // Lê os dados dos alunos
  if (fread(alunos, sizeof(Aluno), *quantidade, arquivo) != *quantidade) {
    printf("Erro ao ler os dados dos alunos do arquivo binário.\n");
    fclose(arquivo);
    *quantidade = 0; // Define quantidade como zero em caso de falha
    return;
  }

  fclose(arquivo);
  printf("Dados carregados do arquivo binário com sucesso.\n");
}

// Função para buscar o índice do aluno no array pela matrícula
int buscarIndiceAluno(Aluno *alunos, int quantidade, int matricula) {
  for (int i = 0; i < quantidade; i++) {
    if (alunos[i].matricula == matricula) {
      return i;
    }
  }
  return -1;
}

// Função para validar se uma nota está dentro do intervalo permitido
int validarNota(float nota) {
  return (nota >= NOTA_MINIMA && nota <= NOTA_MAXIMA);
}

// Função para verificar se a entrada de nota é um número válido
int validarNotaInput(char *input) {
  for (int i = 0; input[i] != '\0'; i++) {
    if (!isdigit(input[i]) && input[i] != '.') {
      return 0;
    }
  }
  return 1;
}
