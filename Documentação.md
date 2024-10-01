#include <iostream>  // Biblioteca padrão para entrada e saída.
#include <queue>     // Biblioteca que fornece a estrutura de dados 'queue' (fila).
#include <stack>     // Biblioteca que fornece a estrutura de dados 'stack' (pilha).
#include <string>    // Biblioteca para manipulação de strings.

using namespace std; // Usando o namespace padrão 'std', que facilita o uso de cout, cin, etc., sem precisar prefixá-los com 'std::'.

// Estrutura para armazenar informações de cada pessoa
struct Pessoa {
    string cpf;   // Armazena o CPF da pessoa.
    string nome;  // Armazena o nome da pessoa.
    int idade;    // Armazena a idade da pessoa.
};

// Estrutura para controlar as doses do frasco
struct Frasco {
    int dosesDisponiveis = 5; // Cada frasco começa com 5 doses.
};

// Variáveis globais
queue<Pessoa> fila;             // Fila de pessoas esperando para vacinar.
stack<Frasco> pilhaFrascos;     // Pilha de frascos de vacina.
int totalVacinados = 0;         // Contador global para o total de pessoas vacinadas.

// Função para empilhar os frascos iniciais.
void inicializarFrascos() {
    for (int i = 0; i < 3; i++) {          // Adiciona 3 frascos com 5 doses cada.
        pilhaFrascos.push(Frasco());       // Cada iteração empilha um novo frasco.
    }
}

// Função para adicionar uma pessoa na fila.
void adicionarPessoa() {
    if (fila.size() < 15 && !pilhaFrascos.empty()) {   // Verifica se há menos de 15 pessoas na fila e se há frascos disponíveis.
        Pessoa novaPessoa;           // Cria uma nova estrutura 'Pessoa'.
        cout << "Digite o CPF: ";     // Solicita o CPF da pessoa.
        cin >> novaPessoa.cpf;        // Lê o CPF digitado.
        cout << "Digite o nome: ";    // Solicita o nome da pessoa.
        cin >> novaPessoa.nome;       // Lê o nome digitado.
        cout << "Digite a idade: ";   // Solicita a idade da pessoa.
        cin >> novaPessoa.idade;      // Lê a idade digitada.

        fila.push(novaPessoa);        // Adiciona a nova pessoa à fila.
        cout << "Pessoa adicionada à fila.\n";  // Confirma que a pessoa foi adicionada.
    } else {
        cout << "Fila cheia ou sem frascos disponíveis.\n";  // Mensagem de erro se a fila estiver cheia ou não houver frascos.
    }
}

// Função para vacinar e remover a pessoa da fila.
void tirarPessoa() {
    if (!fila.empty()) {                        // Verifica se há pessoas na fila.
        Pessoa pessoa = fila.front();           // Obtém a primeira pessoa da fila.
        fila.pop();                             // Remove a pessoa da fila.

        if (!pilhaFrascos.empty()) {            // Verifica se há frascos disponíveis.
            Frasco& frascoAtual = pilhaFrascos.top();  // Obtém o frasco no topo da pilha.
            frascoAtual.dosesDisponiveis--;           // Diminui uma dose do frasco.

            cout << "Pessoa vacinada: " << pessoa.nome << " (CPF: " << pessoa.cpf << ")\n";  // Exibe a confirmação da vacinação.
            totalVacinados++;  // Incrementa o contador de vacinados.

            // Se o frasco não tiver mais doses, ele é removido.
            if (frascoAtual.dosesDisponiveis == 0) {
                cout << "Desempilhando frasco com 0 doses restantes.\n";  // Informa que o frasco foi esvaziado.
                pilhaFrascos.pop();  // Remove o frasco vazio da pilha.
            }
        }
    } else {
        cout << "Não há pessoas na fila.\n";  // Mensagem caso a fila esteja vazia.
    }
}

// Função para imprimir os nomes das pessoas na fila.
void imprimirFila() {
    if (fila.empty()) {          // Verifica se a fila está vazia.
        cout << "Fila vazia.\n"; // Mensagem se não houver pessoas na fila.
        return;                  // Sai da função.
    }

    cout << "Pessoas na fila:\n";     // Exibe cabeçalho.
    queue<Pessoa> temp = fila;        // Faz uma cópia da fila para não alterar a fila original.
    while (!temp.empty()) {           // Enquanto houver pessoas na fila.
        cout << "- " << temp.front().nome << "\n";  // Exibe o nome da pessoa.
        temp.pop();                   // Remove a pessoa da fila temporária.
    }
}

// Função para exibir o total de pessoas vacinadas.
void exibirTotalVacinados() {
    cout << "Total de pessoas vacinadas: " << totalVacinados << "\n";  // Exibe o total de vacinados.
}

// Função do menu que oferece opções ao usuário.
void menu() {
    inicializarFrascos();  // Inicializa os frascos de vacina com 5 doses cada.
    int opcao;             // Variável para armazenar a opção do usuário.

    do {
        cout << "\\nMenu:\\n";
        cout << "1. Adicionar pessoa na fila\\n";
        cout << "2. Tirar pessoa da fila\\n";
        cout << "3. Imprimir nomes da fila\\n";
        cout << "4. Exibir total de vacinados\\n";
        cout << "0. Sair\\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;  // Lê a opção escolhida pelo usuário.

        switch (opcao) {
            case 1: adicionarPessoa(); break;   // Chama a função para adicionar uma pessoa na fila.
            case 2: tirarPessoa(); break;       // Chama a função para vacinar uma pessoa.
            case 3: imprimirFila(); break;      // Chama a função para imprimir os nomes das pessoas na fila.
            case 4: exibirTotalVacinados(); break;  // Chama a função para exibir o total de vacinados.
            case 0: cout << "Saindo...\\n"; break;  // Exibe uma mensagem de saída.
            default: cout << "Opção inválida!\\n";  // Exibe mensagem de erro para opções inválidas.
        }
    } while (opcao != 0);  // O menu continua rodando até que o usuário escolha a opção de sair.
}

int main() {
    menu();  // Inicia o menu, onde o programa começa sua execução.
    return 0;} // Retorna 0, indicando que o programa terminou corretamente.

