# Sistema de Gerenciamento de Sessões de Recarga

Sistema desenvolvido em linguagem **C** para gerenciamento e análise de sessões de recarga de veículos elétricos.

O programa permite cadastrar sessões de recarga, consultar informações, listar os registros, ordenar os dados e visualizar estatísticas.

## Funcionalidades

* **Nova sessão de recarga**

  * Cadastro de uma nova sessão.
  * Registro do ID da sessão.
  * Registro da energia utilizada.
  * Registro do tempo de recarga.
  * Registro do custo.
  * Registro da bateria inicial e final.
  * Registro da tarifa por kWh.
  * Registro do horário da sessão.

* **Listar sessões**

  * Exibe todas as sessões cadastradas.

* **Buscar sessão**

  * Permite localizar uma sessão através do seu ID.

* **Ordenar sessões**

  * Ordenação por:

    * ID
    * Energia
    * Custo
    * Tempo
    * Bateria inicial
  * Permite ordenar em ordem crescente ou decrescente.
  * Utiliza o algoritmo **Bubble Sort**.

* **Estatísticas**

  * Apresenta informações e cálculos relacionados às sessões cadastradas.

## Tecnologias utilizadas

* **C**
* **GCC**
* **Visual Studio Code**
* **Git e GitHub**

## Conceitos de programação utilizados

O projeto foi desenvolvido utilizando conceitos fundamentais da linguagem C, como:

* `struct`
* `typedef`
* Vetores
* Funções
* Ponteiros
* Estruturas condicionais
* Estruturas de repetição
* Entrada e saída de dados
* Organização de código em funções
* Busca sequencial
* Ordenação por Bubble Sort
* Análise de complexidade com **Big O**

## Estrutura dos dados

As sessões são armazenadas utilizando a estrutura `Sessao`:

```c
typedef struct
{
    int id;
    float energia;
    float tempo;
    float custo;
    float bateria_inicial;
    float bateria_final;
    float tarifa_por_kwh;
    int horario_sessao;
} Sessao;
```

As sessões cadastradas são armazenadas em um vetor com capacidade para até **100 registros**.

## Complexidade

Duas das funções do projeto foram analisadas utilizando a notação Big O.

### Busca por ID

A função de busca percorre as sessões até encontrar o ID informado.

**Complexidade no pior caso:**

```text
O(n)
```

No pior caso, todas as `n` sessões precisam ser verificadas.

### Ordenação

A função de ordenação utiliza o algoritmo **Bubble Sort**, que possui dois laços de repetição aninhados.

**Complexidade:**

```text
O(n²)
```

Além da ordenação, a função também exibe as sessões ao final. Como a listagem possui complexidade `O(n)`, a complexidade dominante continua sendo:

```text
O(n²)
```

## Como executar

### 1. Clone o repositório

```bash
git clone URL_DO_REPOSITORIO
```

### 2. Acesse a pasta do projeto

```bash
cd nome-do-projeto
```

### 3. Compile o programa

Utilizando o GCC:

```bash
gcc main.c -o main.exe
```

### 4. Execute

No Windows:

```bash
main.exe
```

Ou:

```bash
.\main.exe
```

## Observação

Os arquivos executáveis gerados durante a compilação, como `main.exe` e `a.exe`, não devem ser versionados no repositório. Eles são ignorados pelo `.gitignore`.

## Projeto acadêmico

Projeto desenvolvido como parte dos estudos de **Ciência da Computação**, com foco na aplicação prática de conceitos de programação em C, estruturas de dados, algoritmos e análise de complexidade.
