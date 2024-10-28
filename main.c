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