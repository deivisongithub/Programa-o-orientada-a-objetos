#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "bank.h" // funções e struct cliente para funcionalidade do caixa eletrônico
#define DATASET "database.txt"

using namespace std;

int main(void) {
    FILE *archive;
    struct client users[10];
    char account[7], passw[9];
    int n_clients, op, att;
    int user;
    float value;

    // Ciclo das telas do caixa eletrônico
    do {
        // Limpeza inicial do terminal
        // Apresentação da tela inicial e solicitação de número da conta
        system("cls");
        op = main_screen();

        // Captura de login e verificação no database.txt
        if (op == 1) {

            user = -1;
            while ((op) && (user == -1)) {
                system("cls");
                login_screen();
                cin >> account;

               /*************************************************************************************
                * Abertura do arquivo com o dataset dos clientes                                    *
                * O dataset é composto n linhas, cada uma representando um cliente                  *
                * Cada linha possui as seguintes informações sobre o cliente (separadas por ;):     *
                * número de conta;                                                                  *
                * senha;                                                                            *
                * informação a respeito do bloqueio da conta;                                       *
                * saldo.                                                                            *
                *************************************************************************************/

                archive = fopen("database.txt", "r+");

                // Leitura de todo o dataset atribuindo a user a posição do usuário de acordo com o número de conta informada
                n_clients = 0;
                while (!feof(archive)) {
                    get_client(archive, &users[n_clients]);
                    
                    if (!strcmp(users[n_clients].accnt, account)) // Verificando igualdade entre conta informada e o número de conta lido
                        user = n_clients;

                    n_clients += 1;
                }

                if (user == -1) {
                    system("cls");
                    header();
                    cout << "Numero de conta invalido!" << endl;

                    cout << "1 - Tela inicial" << endl;
                    cout << "2 - Tente novamente" << endl;
                    cout << "0 - Sair" << endl;

                    cout << "Escolha uma opcao: ";
                    cin >> op;
                } else {

                    // Verificação de bloqueio de conta
                    if (users[user].block) {
                        system("cls");
                        header();
                        cout << "Conta bloqueada!\nProcure a sua agencia." << endl;

                        exit(1);
                    }

                    /* Verificação de senha, possíveis caminhos:
                     * Senha correta e tela do caixa;
                     * Senha incorreta, tentar novamente;
                     * Máximo de tentativas excedido, conta bloqueada.
                     */
                    att = 0;
                    while ((att < 3) && (!users[user].check)) {
                        system("cls");
                        pass_screen(att);
                        cin >> passw;

                        if (!strcmp(users[user].pass, passw))
                            users[user].check = 1;
                        
                        att++;
                    }

                    if (users[user].check) {
                        do {
                            system("cls");
                            op = bank_screen(account);

                            if (op == 1) {
                                cout << "Seu saldo eh " << users[user].balance << endl;
                                system("pause");
                            } else if (op == 2) {
                                system("cls");
                                header();
                                cout << "Valor para deposito: ";
                                cin >> value;

                                users[user].balance += value;
                            } else if (op == 3) {
                                system("cls");
                                header();
                                cout << "Valor para saque: ";
                                cin >> value;

                                if (value < users[user].balance) {
                                    cout << "Saldo indisponivel" << endl;
                                    system("pause");
                                } else {
                                    users[user].balance -= value;
                                }
                            }
                        } while (op);

                        // Update do dataset pela reescrita dos dados com as alterações realizadas
                        upd_db(archive, users, n_clients);
                    } else {
                        users[user].block = 1;

                        system("cls");
                        header();
                        cout << "Maxima de tentativas excedido!\nConta bloqueada" << endl;

                        upd_db(archive, users, n_clients);
                        exit(1);
                    }
                }
                
                if (op == 1)
                    break;
            }
        }

        // Cadastro de nova conta
        if (op == 2) {
            while (1) {
                system("cls");
                register_screen();
                cin >> passw;

                if (strlen(passw) != 8) {
                    cout << "Senha invalida!" << endl;
                    system("pause");
                    continue;
                }

                break;
            }

            num_login(archive, account, (char *) DATASET);
            new_account(archive, account, passw, (char *) DATASET);

            system("cls");
            header();
            cout << "Conta criada com sucesso!" << endl;
            cout << "Sua conta sera " << account << endl;

            cout << "1 - Tela inicial" << endl;
            cout << "0 - Sair" << endl;
            cout << "Escolha uma opcao: ";
            cin >> op;
        }
    } while (op);
    
    // Finalizando o programa
    system("cls");
    header();
    cout << "\n                               VOLTE SEMPRE!!!                             \n" << endl;
    //fclose(archive);
    return 0;
}
