#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "bank.h"

using namespace std;

// Tela do caixa eletrônico
int bank_screen(char *accnt) {
    int op;

    header();

    cout << "Bem-vindo " << accnt << endl;
    cout << "1 - Consultar saldo" << endl;
    cout << "2 - Deposito" << endl;
    cout << "3 - Saque" << endl;
    cout << "0 - Sair" << endl;

    cout << "Escolha uma opcao: ";
    cin >> op;

    return op;
}

// Função para a leitura dos dados de um cliente
void get_client(FILE *data, struct client *current) {
    char grb;

    fgets(current->accnt, 7, data);
    fscanf(data, "%c", &grb); // ignorando caracteres que não compõem os dados pertinentes
    fgets(current->pass, 9, data);
    fscanf(data, "%c", &grb);
    fscanf(data, "%d", &current->block);
    fscanf(data, "%c", &grb);
    fscanf(data, "%f", &current->balance);
    fscanf(data, "%c", &grb);

    current->check = 0;
}

// Cabeçalho do banco
void header(void) {    
    cout << "===========================================================================" << endl;
    cout << "===========================================================================" << endl;
    cout << "                               BANCO PARAIBA                               " << endl;
    cout << "===========================================================================" << endl;
    cout << "===========================================================================" << endl;
}

// Função para a apresentação da tela de captura de conta
void login_screen(void) {
    header();

    cout << "Insira o numero da sua conta: ";
}

// Função para a apresentação da tela inicial
int main_screen(void) {
    int op;

    header();

    cout << "1 - Fazer login" << endl;
    cout << "2 - Criar uma conta" << endl;
    cout << "0 - Sair" << endl;

    cout << "Escolha uma opcao: ";
    cin >> op;

    return op;
}

void new_account(FILE *data, char accnt[], char pass[], char dataset[]) {
    data = fopen(dataset, "a");
    fprintf(data, "\n%s;%s;0;0.000000", accnt, pass);

    fflush(data);
    fclose(data);
}

void num_login (FILE *data, char *n_accnt, char dataset[]) {
    char grb[24];

    data = fopen(dataset, "r+");

    // Leitura de todo o dataset até o último número de conta
    while (!feof(data)) {
        fgets(n_accnt, 7, data);
        fgets(grb, 40, data); // ignorando caracteres que não compõem os dados pertinentes
    }

    n_accnt[5]++;
}

void pass_screen(int att) {

    header();

    if (att)
        cout << "Restam " << 3 - att << " tentativas!\nInsira sua senha: ";
    else
        cout << "Insira sua senha: ";
}

// Função para a apresentação da tela de criação de conta
void register_screen(void) {
    int op;

    header();

    cout << "Insira uma senha com 8 caracteres: ";
}

// Função para a atualização do arquivo com o dataset
void upd_db(FILE *data, struct client current[], int rows) {
    rewind(data);

    for (int j=0; j<rows; j++) {
        if (j == (rows-1))
            fprintf(data, "%s;%s;%d;%f", current[j].accnt, current[j].pass, current[j].block, current[j].balance);
        else
            fprintf(data, "%s;%s;%d;%f\n", current[j].accnt, current[j].pass, current[j].block, current[j].balance);
    }

    fclose(data);
}
