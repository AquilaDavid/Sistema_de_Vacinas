
# Sistema de Vacinação

Este projeto implementa um sistema de vacinação simples, onde pessoas são adicionadas a uma fila para serem vacinadas. O sistema gerencia a quantidade de doses disponíveis em frascos e remove pessoas da fila à medida que são vacinadas.

## Bibliotecas Utilizadas

```cpp
#include <iostream>  // Biblioteca padrão para entrada e saída de dados.
#include <queue>     // Biblioteca que fornece a estrutura de dados 'queue' (fila).
#include <stack>     // Biblioteca que fornece a estrutura de dados 'stack' (pilha).
#include <string>    // Biblioteca para manipulação de strings.
```

## Namespace

Utilizamos o namespace `std` para simplificar a utilização de funções como `cout`, `cin` e outras funções da biblioteca padrão.

```cpp
using namespace std;
```

## Estruturas

### Estrutura `Pessoa`

A estrutura `Pessoa` contém as informações básicas de cada pessoa que será vacinada: CPF, nome e idade.

```cpp
struct Pessoa {
    string cpf;   // CPF da pessoa.
    string nome;  // Nome da pessoa.
    int idade;    // Idade da pessoa.
};
```

### Estrutura `Frasco`

A estrutura `Frasco` controla o número de doses disponíveis por frasco. Cada frasco começa com 5 doses.

```cpp
struct Frasco {
    int dosesDisponiveis = 5; // Cada frasco começa com 5 doses.
};
```

## Variáveis Globais

- `fila`: Fila de pessoas aguardando para serem vacinadas.
- `pilhaFrascos`: Pilha de frascos de vacina, cada um com 5 doses.
- `totalVacinados`: Contador que armazena o total de pessoas vacinadas até o momento.

```cpp
queue<Pessoa> fila;             // Fila de pessoas esperando para vacinar.
stack<Frasco> pilhaFrascos;     // Pilha de frascos de vacina.
int totalVacinados = 0;         // Contador de vacinados.
```

## Funções

### Função `inicializarFrascos`

Essa função inicializa 3 frascos de vacina, empilhando-os na estrutura `pilhaFrascos`. Cada frasco contém 5 doses.

```cpp
void inicializarFrascos() {
    for (int i = 0; i < 3; i++) {          // Adiciona 3 frascos com 5 doses cada.
        pilhaFrascos.push(Frasco());       // Empilha cada frasco na pilha.
    }
}
```

### Função `adicionarPessoa`

Essa função adiciona uma nova pessoa à fila de vacinação, desde que haja menos de 15 pessoas na fila e ainda existam frascos de vacina disponíveis.

```cpp
void adicionarPessoa() {
    if (fila.size() < 15 && !pilhaFrascos.empty()) {   // Verifica se há menos de 15 pessoas na fila e frascos disponíveis.
        Pessoa novaPessoa;
        cout << "Digite o CPF: ";
        cin >> novaPessoa.cpf;
        cout << "Digite o nome: ";
        cin >> novaPessoa.nome;
        cout << "Digite a idade: ";
        cin >> novaPessoa.idade;

        fila.push(novaPessoa);        // Adiciona a pessoa à fila de vacinação.
        cout << "Pessoa adicionada à fila.
";
    } else {
        cout << "Fila cheia ou sem frascos disponíveis.
";  // Mensagem de erro caso a fila esteja cheia ou não haja frascos.
    }
}
```

### Função `tirarPessoa`

Remove a pessoa da frente da fila e administra uma dose de vacina, utilizando o frasco atual. Se o frasco esvaziar, ele é removido da pilha.

```cpp
void tirarPessoa() {
    if (!fila.empty()) {                        // Verifica se há pessoas na fila.
        Pessoa pessoa = fila.front();           // Obtém a primeira pessoa da fila.
        fila.pop();                             // Remove a pessoa da fila.

        if (!pilhaFrascos.empty()) {            // Verifica se há frascos disponíveis.
            Frasco& frascoAtual = pilhaFrascos.top();  // Obtém o frasco atual (no topo da pilha).
            frascoAtual.dosesDisponiveis--;     // Diminui uma dose do frasco.

            cout << "Pessoa vacinada: " << pessoa.nome << " (CPF: " << pessoa.cpf << ")
";  // Confirma a vacinação.
            totalVacinados++;                   // Incrementa o contador de vacinados.

            // Se o frasco não tiver mais doses, ele é removido.
            if (frascoAtual.dosesDisponiveis == 0) {
                cout << "Desempilhando frasco com 0 doses restantes.
";  // Informa que o frasco está vazio.
                pilhaFrascos.pop();  // Remove o frasco vazio da pilha.
            }
        }
    } else {
        cout << "Não há pessoas na fila.
";  // Mensagem caso a fila esteja vazia.
    }
}
```

### Função `imprimirFila`

Exibe os nomes de todas as pessoas atualmente na fila de vacinação. A fila original não é alterada, pois é criada uma cópia temporária para impressão.

```cpp
void imprimirFila() {
    if (fila.empty()) {          // Verifica se a fila está vazia.
        cout << "Fila vazia.
"; // Mensagem caso a fila esteja vazia.
        return;
    }

    cout << "Pessoas na fila:
";
    queue<Pessoa> temp = fila;   // Cria uma cópia temporária da fila para impressão.
    while (!temp.empty()) {      // Itera sobre a fila.
        cout << "- " << temp.front().nome << "
";  // Exibe o nome da pessoa.
        temp.pop();                                  // Remove a pessoa da fila temporária.
    }
}
```

### Função `exibirTotalVacinados`

Exibe o total de pessoas que foram vacinadas até o momento.

```cpp
void exibirTotalVacinados() {
    cout << "Total de pessoas vacinadas: " << totalVacinados << "
";  // Exibe o número total de vacinados.
}
```

### Função `menu`

Essa função exibe um menu de opções para o usuário, permitindo que ele adicione pessoas à fila, vacine-as, veja a fila de espera ou o número de vacinados.

```cpp
void menu() {
    inicializarFrascos();  // Inicializa os frascos de vacina com 5 doses cada.
    int opcao;             // Variável para armazenar a escolha do usuário.

    do {
        cout << "
Menu:
";
        cout << "1. Adicionar pessoa na fila
";
        cout << "2. Tirar pessoa da fila
";
        cout << "3. Imprimir nomes da fila
";
        cout << "4. Exibir total de vacinados
";
        cout << "0. Sair
";
        cout << "Escolha uma opção: ";
        cin >> opcao;  // Lê a opção do usuário.

        switch (opcao) {
            case 1: adicionarPessoa(); break;   // Adiciona uma pessoa à fila.
            case 2: tirarPessoa(); break;       // Remove e vacina uma pessoa.
            case 3: imprimirFila(); break;      // Imprime os nomes na fila.
            case 4: exibirTotalVacinados(); break;  // Exibe o total de vacinados.
            case 0: cout << "Saindo...
"; break;  // Sai do programa.
            default: cout << "Opção inválida!
";  // Exibe mensagem de erro para opções inválidas.
        }
    } while (opcao != 0);  // Continua rodando o menu até que o usuário escolha a opção de sair.
}
```

### Função `main`

Ponto de entrada do programa. Ele chama a função `menu()` para iniciar a interação com o usuário.

```cpp
int main() {
    menu();  // Inicia o menu, que gerencia a execução do programa.
    return 0; // Retorna 0, indicando que o programa terminou corretamente.
}
```

## Como Rodar o Programa

1. Compile o código usando um compilador C++:
   ```bash
   g++ -o sistema_vacinacao sistema_vacinacao.cpp
   ```

2. Execute o programa:
   ```bash
   ./sistema_vacinacao
   ```

## Funcionalidades

- Adicionar pessoas à fila para vacinação.
- Vacinar pessoas removendo-as da fila.
- Imprimir a lista de pessoas na fila.
- Exibir o número total de pessoas vacinadas.

---

Esse layout permite uma fácil leitura e compreensão do código em um repositório GitHub. Você pode simplesmente salvar este conteúdo em um arquivo `README.md` e adicionar ao repositório.
