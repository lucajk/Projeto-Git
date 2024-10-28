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
