#ifndef BANK_H
#define BANK_H


// Declaração de tipo estruturado com dados necessários
struct client{
    char accnt[7];
    char pass[9];

    float balance;

    int check; // inicia com 0, é incrementado para um pela função de verificação de senha
    int block; // inicia com 0, é incrementado no terceiro erro da senha
};

/************************
* Protótipo das funções *
************************/

/* Tela do caixa eletrônico */
int bank_screen(char *accnt);
/* Leitura dos dados dos clientes */
void get_client(FILE *data, struct client *current);
/* Cabeçalho de apresentação do banco */
void header(void);
/* Tela para inserção de dados do cliente */
void login_screen(void);
/* Menu do banco */
int main_screen(void);
/* Registro de uma nova conta */
void new_account(FILE* data, char accnt[], char pass[], char dataset[]);
/* Gera o próximo numero de conta disponível de acordo com o dataset */
void num_login (FILE *data, char *n_accnt, char dataset[]);
/* Tela para inserção de senha */
void pass_screen(int);
/* Inserção de senha em uma nova conta  */
void register_screen(void);
/* "UPDATE DATABASE", realiza as atualizações após a finalização das operações */
void upd_db(FILE *data, struct client current[], int rows);

#endif