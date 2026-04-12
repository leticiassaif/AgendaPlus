#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define AGENDA_OUTPUT "arquivos/agenda.csv"
#define CONTATOS_OUTPUT "arquivos/contatos.csv"


typedef struct {
    int id;
    char nome[100];
    char telefone[16];
    char email[100];
    char trabalho[100];
} Contato;


typedef struct {
    char data[11];
    char horario[6];
    char periodo;
    char tipo[100];
    int acompanhante; // baseado no id, uma vez que o nome da pessoa pode repetir
} Atividade;


/* 
organização dos períodos
    Manhã ('M'): 0h até 11h59
    Tarde ('T'): 12h até 17h59
    Noite ('N'): 18h até 23h59
!! o própio código vai decidir o período, de acordo com a hora dada pelo usuário
*/


Contato *lerContato(char arquivo[], int *total, char delimitador);
int gravarContato(Contato *contatos, int totalCont, char arquivo[], char delimitador);
Atividade *lerAtividade(char arquivo[], int *total, char delimitador);
int gravarAtividade(Atividade *agenda, int totalAtv, char arquivo[], char delimitador);


int disponibilidade(Atividade *agenda, int total, char data[], char hora[]);
int encontrarID(Contato *contatos, int total, int idProcurado);
void imprimirAtividade(
    int norma, Atividade *agenda, Contato *contatos, int totalCont, int indice, 
    char data[], char hora[], int diaSemana
);
void imprimirContatos(Contato *contatos, int totalCont); // saber o id para a atualização de um contato, imprime apenas o nome, id e email (p/ nomes repetidos)


void addAtividade(Atividade *nova, char data[], char horario[], char tipo[], int acompanhante);
int removeAtividade(Atividade *agenda, int total, char data[], char hora[]);
int atualizarAtividade(
    Atividade *agenda, int totalAtv,
    char data[], char hora[], char dataNova[], char horaNova[], char tipoNova[], int acompanhanteNova
);
void removeAcompanhante(Atividade *agenda, int total, int id);


void addContato(Contato *novo, int id, char nome[], char telefone[], char email[], char trabalho[]);
int removeContato(Contato *contatos, int id, int total);
int atualizarContato(
    Contato *contatos, int totalCont,
    int id, char nomeNovo[], char telefoneNovo[], char emailNovo[], char trabalhoNovo[]
);