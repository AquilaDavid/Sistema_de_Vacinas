#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Estrutura para armazenar informações de cada pessoa
struct Pessoa {
    string cpf;
    string nome;
    int idade;
};

// Estrutura para controlar as doses do frasco
struct Frasco {
    int dosesDisponiveis = 5; // Cada frasco começa com 5 doses
};

// Variáveis globais
queue<Pessoa> fila;             // Fila de pessoas esperando para vacinar
stack<Frasco> pilhaFrascos;     // Pilha de frascos de vacina
int totalVacinados = 0;         // Contador de vacinados

// Função para empilhar os frascos iniciais
void inicializarFrascos() {
    for (int i = 0; i < 3; i++) {
        pilhaFrascos.push(Frasco());
    }
}

// Função para adicionar uma pessoa na fila
void adicionarPessoa() {
    if (fila.size() < 15 && !pilhaFrascos.empty()) {
        Pessoa novaPessoa;
        cout << "Digite o CPF: ";
        cin >> novaPessoa.cpf;
        cout << "Digite o nome: ";
        cin >> novaPessoa.nome;
        cout << "Digite a idade: ";
        cin >> novaPessoa.idade;

        fila.push(novaPessoa); // Adiciona a pessoa à fila
        cout << "Pessoa adicionada à fila.\n";
    } else {
        cout << "Fila cheia ou sem frascos disponíveis.\n";
    }
}

// Função para vacinar e remover a pessoa da fila
void tirarPessoa() {
    if (!fila.empty()) {
        Pessoa pessoa = fila.front(); // Pega a pessoa da frente
        fila.pop(); // Remove da fila

        if (!pilhaFrascos.empty()) {
            Frasco& frascoAtual = pilhaFrascos.top(); // Pega o frasco atual
            frascoAtual.dosesDisponiveis--; // Diminui uma dose

            cout << "Pessoa vacinada: " << pessoa.nome << " (CPF: " << pessoa.cpf << ")\n";
            totalVacinados++;

            // Se o frasco acabou as doses
            if (frascoAtual.dosesDisponiveis == 0) {
                cout << "Desempilhando frasco com 0 doses restantes.\n";
                pilhaFrascos.pop(); // Remove o frasco
            }
        }
    } else {
        cout << "Não há pessoas na fila.\n";
    }
}

// Função para imprimir os nomes na fila
void imprimirFila() {
    if (fila.empty()) {
        cout << "Fila vazia.\n";
        return;
    }

    cout << "Pessoas na fila:\n";
    queue<Pessoa> temp = fila; // Cópia da fila para impressão
    while (!temp.empty()) {
        cout << "- " << temp.front().nome << "\n"; // Imprime o nome
        temp.pop(); // Remove da cópia
    }
}

// Função para exibir o total de vacinados
void exibirTotalVacinados() {
    cout << "Total de pessoas vacinadas: " << totalVacinados << "\n";
}

// Função do menu
void menu() {
    inicializarFrascos(); // Inicializa os frascos
    int opcao;

    do {
        cout << "\nMenu:\n";
        cout << "1. Adicionar pessoa na fila\n";
        cout << "2. Tirar pessoa da fila\n";
        cout << "3. Imprimir nomes da fila\n";
        cout << "4. Exibir total de vacinados\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao; // Lê a opção do usuário

        switch (opcao) {
            case 1: adicionarPessoa(); break; // Adiciona
            case 2: tirarPessoa(); break; // Remove
            case 3: imprimirFila(); break; // Imprime
            case 4: exibirTotalVacinados(); break; // Total
            case 0: cout << "Saindo...\n"; break; // Sair
            default: cout << "Opção inválida!\n"; // Erro
        }
    } while (opcao != 0); // Continua até sair
}

int main() {
    menu(); // Executa o menu
    return 0; // Retorno padrão
}
