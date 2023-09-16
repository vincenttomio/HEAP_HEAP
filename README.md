# Heap, Heap, UPA! (2022)

Este repositório contém o código-fonte em C para o Trabalho Prático 2 (2022) intitulado "Heap, Heap, UPA!". O programa simula uma fila de prioridades implementada com uma estrutura de dados de heap. Ele permite cadastrar pacientes com nomes e prioridades, atualizar as prioridades, chamar pacientes da fila com maior prioridade e realizar simulações/testes.

## Informações Gerais

- **Autores:** Vincent Tomio
- **Disciplina:** Algoritmos II
- **Data da última atualização:** 2022/8
- **Link para a disciplina:** [Trabalho Prático 2](https://www.inf.ufpr.br/vvsbt20)

## Compilação e Execução

Para compilar e executar o programa, siga as etapas abaixo:

1. Certifique-se de ter um ambiente de desenvolvimento C instalado.
2. Salve o código-fonte em um arquivo chamado `main.c`.
3. Abra um terminal e navegue até o diretório onde o arquivo `main.c` está localizado.
4. Execute os seguintes comandos:

```bash
gcc -o programa main.c
./programa
```

## Funcionalidades

- Cadastrar Paciente: O programa permite cadastrar pacientes com nomes e prioridades. Os pacientes são inseridos na fila de prioridades implementada com uma estrutura de heap.
- Atualizar Cadastro: É possível alterar a prioridade de um paciente já cadastrado na fila, mantendo a estrutura de heap.
- Imprimir Fila: O programa imprime a fila de pacientes, mostrando suas prioridades e nomes.
- Chamar Paciente: O programa remove o paciente com a maior prioridade da fila e o exibe na tela.
- SIMULAÇÃO/TESTE: O programa possui uma opção para realizar simulações e testes. Ele cria uma fila com elementos não ordenados, transforma a fila em um heap, atualiza prioridades aleatoriamente, realiza o heapsort para ordenar a fila e chama todos os pacientes da fila.

## Estrutura do Código

O código está estruturado da seguinte forma:

- Bibliotecas Utilizadas: Inclusão das bibliotecas `stdio.h` e `time.h`.
- Constantes: Definição de constantes como `TamMaxFila` (tamanho máximo da fila) e `TamMaxNome` (tamanho máximo do nome do paciente).
- Estruturas: Definição das estruturas `Paciente` e `FilaHeap`.
- Funções: Implementação de várias funções para manipulação da fila de prioridades, incluindo inserção, remoção, correção de heap, simulações/testes e outras funcionalidades.

## Uso do Programa

1. O programa exibirá um menu onde você pode escolher várias opções, incluindo cadastrar paciente, atualizar cadastro, imprimir fila, chamar paciente, realizar simulações/testes ou sair do programa.
2. Se escolher cadastrar paciente, você poderá inserir um nome e uma prioridade para o paciente.
3. Se escolher atualizar cadastro, você poderá escolher um paciente da fila e alterar sua prioridade.
4. Se escolher imprimir fila, o programa exibirá a fila de pacientes com suas prioridades e nomes.
5. Se escolher chamar paciente, o paciente com maior prioridade será removido da fila e exibido.
6. Se escolher simulações/testes, o programa realizará várias operações para testar a funcionalidade da fila de prioridades.
7. O programa continuará em execução até você escolher sair

## Observações

- O código contém comentários explicativos em várias partes para auxiliar na compreensão das funções e operações realizadas.