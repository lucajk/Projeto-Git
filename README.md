# Sistema de Gerenciamento de Alunos

Este projeto é um sistema simples de gerenciamento de alunos, permitindo a adição, edição, remoção e consulta de informações de alunos, como notas, matrícula e faltas. O sistema também gera relatórios de alunos aprovados e reprovados e salva os dados em arquivos de texto e binário.

## Funcionalidades

- **Adicionar Aluno**: Permite a adição de um novo aluno com nome, matrícula, notas e faltas.
- **Editar Aluno**: Permite a edição das informações de um aluno existente.
- **Remover Aluno**: Remove um aluno da lista.
- **Listar Alunos**: Exibe todos os alunos cadastrados com suas informações.
- **Buscar Aluno**: Procura um aluno específico pela matrícula.
- **Relatório de Aprovados/Reprovados**: Gera uma lista de alunos aprovados e reprovados com base nas notas e faltas.
- **Salvar e Carregar Dados**: Salva os dados em arquivos de texto e binário para persistência.

## Estrutura do Código

O código é escrito em C e utiliza uma estrutura `Aluno` para armazenar as informações de cada aluno. As funções principais incluem:

- `adicionarAluno()`: Adiciona um novo aluno ao sistema.
- `editarAluno()`: Edita as informações de um aluno existente.
- `removerAluno()`: Remove um aluno da lista.
- `listarAlunos()`: Lista todos os alunos.
- `buscarAluno()`: Busca um aluno pelo número de matrícula.
- `listarAprovadosReprovados()`: Exibe alunos que foram aprovados ou reprovados.
- `salvarDados()`: Salva os dados dos alunos em um arquivo de texto.
- `carregarDados()`: Carrega dados de um arquivo de texto.
- `salvarDadosBinario()`: Salva os dados dos alunos em um arquivo binário.
- `carregarDadosBinario()`: Carrega dados de um arquivo binário.
- `validarNota()`: Valida se a nota está dentro do intervalo permitido.

## Como Usar

1. Clone o repositório:
   ```bash
   git clone https://github.com/seuusuario/seurepositorio.git
