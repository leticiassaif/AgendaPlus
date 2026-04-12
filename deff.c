#include "deff.h"

Contato *lerContato(char arquivo[], int *total, char delimitador) {
    char linha[1000], dStr[2];
    char *token;
    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL) return NULL;

    Contato *novo =  NULL;
    Contato *temp = NULL;

    sprintf(dStr, "%c", delimitador);
    while (fgets(linha, 1000, arq) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; 

        temp = (Contato *)realloc(novo, (*total + 1) * sizeof(Contato));
        if (temp == NULL) {
            free(novo);
            return NULL;
        }
        novo = temp;      

        token = strtok(linha, dStr);
        if (token) novo[*total].id = atoi(token);

        token = strtok(NULL, dStr);
        if (token) strcpy(novo[*total].nome, token);

        token = strtok(NULL, dStr);
        if (token) strcpy(novo[*total].telefone, token);

        token = strtok(NULL, dStr);
        if (token) strcpy(novo[*total].email, token);

        token = strtok(NULL, dStr);
        if (token) strcpy(novo[*total].trabalho, token);

        (*total)++;

    }

    fclose(arq);
    return novo;
}


int gravarContato(Contato *contatos, int totalCont, char arquivo[], char delimitador) {
    FILE *arq = fopen(arquivo, "w"); 
    if (arq == NULL) return 0;
    
    for (int i = 0; i < totalCont; i++) {
        fprintf(
            arq, "%d%c%s%c%s%c%s%c%s\n", contatos[i].id, delimitador, contatos[i].nome, delimitador, 
            contatos[i].telefone, delimitador, contatos[i].email, delimitador, contatos[i].trabalho);
    }

    fclose(arq);
    return 1;
}


Atividade *lerAtividade(char arquivo[], int *total, char delimitador) {
    char linha[1000], dStr[2];
    char *token;
    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL) return NULL;

    Atividade *atv =  NULL;
    Atividade *temp = NULL;

    sprintf(dStr, "%c", delimitador);
    while (fgets(linha, 1000, arq) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';

        temp = (Atividade *)realloc(atv, (*total + 1) * sizeof(Atividade));
        if (temp == NULL) {
            free(atv);
            return NULL;
        }
        atv = temp;      

        token = strtok(linha, dStr);
        if (token) strcpy(atv[*total].data, token);

        token = strtok(NULL, dStr);
        if (token) strcpy(atv[*total].horario, token);

        token = strtok(NULL, dStr);
        if (token) atv[*total].periodo = token[0];

        token = strtok(NULL, dStr);
        if (token) strcpy(atv[*total].tipo, token);

        token = strtok(NULL, dStr);
        if (token) atv[*total].acompanhante = atoi(token);

        (*total)++;
    }

    fclose(arq);
    return atv;
}


int gravarAtividade(Atividade *agenda, int totalAtv, char arquivo[], char delimitador) {
    FILE *arq = fopen(arquivo, "w");
    if (arq == NULL) return 0;

    for (int i = 0; i < totalAtv; i++) {
        fprintf(
            arq, "%s%c%s%c%c%c%s%c%d\n", agenda[i].data, delimitador, agenda[i].horario, delimitador,
            agenda[i].periodo, delimitador, agenda[i].tipo, delimitador, agenda[i].acompanhante);
    }

    fclose(arq);
    return 1;
}


/* Checa se já existe ou não um compromisso na data e hora escolhido */
int disponibilidade(Atividade *agenda, int total, char data[], char hora[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(data, agenda[i].data) == 0 && strcmp(hora, agenda[i].horario) == 0) {
            printf("O horario nessa data ja esta ocupado.\n");
            return 0;
        }
    }
    return 1;
}


/* Retorna o índice no vetor de um determinado contato pelo seu ID */
int encontrarID(Contato *contatos, int total, int idProcurado) {
    for (int i = 0; i < total; i++) {
        if (contatos[i].id == idProcurado) {
            return i;
        }
    }
    return -1;
}


void imprimirAtividade(
    int norma, Atividade *agenda, Contato *contatos, int totalCont, int indice, 
    char data[], char hora[], int diaSemana
) {
    int pessoa = encontrarID(contatos, totalCont, agenda[indice].acompanhante);
    int diaAtual, diaAtv, mesAtual, mesAtv, anoAtual, anoAtv;
    char periodo;
    struct tm dataAtv = {0}; // inicializa o valor

    if (norma == 3 || norma == 4) {
        sscanf(data, "%d/%d/%d", &diaAtual, &mesAtual, &anoAtual);
        sscanf(agenda[indice].data, "%d/%d/%d", &diaAtv, &mesAtv, &anoAtv);
    }

    switch (norma) {
        case 1:
            if (strcmp(hora, "12h00") < 0) periodo = 'M';
            else if (strcmp(hora, "18h00") < 0) periodo = 'T';
            else periodo = 'N';

            if ( (strcmp(data, agenda[indice].data) == 0) && (periodo == agenda[indice].periodo) ) {
                printf("%s :: [%s] - %s", agenda[indice].data, agenda[indice].horario, agenda[indice].tipo);
                if (agenda[indice].acompanhante == -1 || pessoa == -1) printf("\n");
                else printf(" com %s\n", contatos[pessoa].nome, contatos[pessoa].id);
            }
            break;

        case 2:
            if ( ( strcmp(data, agenda[indice].data) == 0 ) && ( strcmp(hora, agenda[indice].horario) <= 0 ) ) {
                printf("%s :: [%s] - %s", agenda[indice].data, agenda[indice].horario, agenda[indice].tipo);
                if (agenda[indice].acompanhante == -1 || pessoa == -1) printf("\n");
                else printf(" com %s\n", contatos[pessoa].nome);
            }
            break;

        case 3:
            dataAtv.tm_mday = diaAtv;
            dataAtv.tm_mon = mesAtv - 1;
            dataAtv.tm_year = anoAtv - 1900;
            mktime(&dataAtv);
            if ((anoAtual == anoAtv) && (mesAtual == mesAtv) && (diaAtual <= diaAtv) && (diaSemana <= dataAtv.tm_wday)) {
                 if (diaAtv <= (diaAtual + (6 - diaSemana))) {
                    printf("%s :: [%s] - %s", agenda[indice].data, agenda[indice].horario, agenda[indice].tipo);
                    if (agenda[indice].acompanhante == -1 || pessoa == -1) printf("\n");
                    else printf(" com %s (ID: %d)\n", contatos[pessoa].nome, contatos[pessoa].id);
                }
            }
            break;

        case 4:
            if ((anoAtual == anoAtv) && (mesAtual == mesAtv) && (diaAtual <= diaAtv)) {
                printf("%s :: [%s] - %s", agenda[indice].data, agenda[indice].horario, agenda[indice].tipo);
                if (agenda[indice].acompanhante == -1 || pessoa == -1) printf("\n");
                else printf(" com %s\n", contatos[pessoa].nome);
            }
            break;

        default:
            printf("!! Opcao errada!");
            break;
    }
}


void imprimirContatos(Contato *contatos, int totalCont) {
    printf("ID - NOME | EMAIL\n");
    for (int i = 0; i < totalCont; i++) {
        printf("%d - %s | %s\n", contatos[i].id, contatos[i].nome, contatos[i].email);
    }
}


void addAtividade(Atividade *nova, char data[], char horario[], char tipo[], int acompanhante) {
    strcpy(nova->data, data);
    strcpy(nova->horario, horario);
    if (strcmp(horario, "12h00") < 0) nova->periodo = 'M';
    else if (strcmp(horario, "18h00") < 0) nova->periodo = 'T';
    else nova->periodo = 'N';
    strcpy(nova->tipo, tipo);
    nova->acompanhante = acompanhante;
}


int removeAtividade(Atividade *agenda, int total, char data[], char hora[]) {
    int i, indice = -1;
    for (i = 0; i < total; i++) {
        if (strcmp(agenda[i].data, data) == 0 && strcmp(agenda[i].horario, hora) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) return 0;
    for (i = indice; i < total - 1; i++) {
        agenda[i] = agenda[i+1];
    }
    return 1;
}


int atualizarAtividade(
    Atividade *agenda, int totalAtv,
    char data[], char hora[], char dataNova[], char horaNova[], char tipoNova[], int acompanhanteNova
) {
    if (!disponibilidade(agenda, totalAtv, dataNova, horaNova)) return 0;

    for (int i = 0; i < totalAtv; i++) {
        if ((strcmp(data, agenda[i].data) == 0) && (strcmp(hora, agenda[i].horario) == 0)) {
            strcpy(agenda[i].data, dataNova);
            strcpy(agenda[i].horario, horaNova);
            strcpy(agenda[i].tipo, tipoNova);
            agenda[i].acompanhante = acompanhanteNova;
            return 1;
        }
    }

    return 0;
}


/* Substitui o ID do acompanhante por -1 quando esse contato é removido */
void removeAcompanhante(Atividade *agenda, int total, int id) {
    for (int i = 0; i < total; i++) {
        if (agenda[i].acompanhante == id) agenda[i].acompanhante = -1;
    }
}


void addContato(Contato *novo, int id, char nome[], char telefone[], char email[], char trabalho[]) {
    novo->id = id;
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    strcpy(novo->email, email);
    strcpy(novo->trabalho, trabalho);
}


int removeContato(Contato *contatos, int id, int total) {
    int i, indice = -1;
    for (i = 0; i < total; i++) {
        if (contatos[i].id == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) return 0;
    for (i = indice; i < total - 1; i++) {
        contatos[i] = contatos[i+1];
    }
    return 1;
}


int atualizarContato(
    Contato *contatos, int totalCont,
    int id, char nomeNovo[], char telefoneNovo[], char emailNovo[], char trabalhoNovo[]
) {
    int indice = encontrarID(contatos, totalCont, id);
    if (indice == -1) return 0;
    strcpy(contatos[indice].nome, nomeNovo);
    strcpy(contatos[indice].telefone, telefoneNovo);
    strcpy(contatos[indice].email, emailNovo);
    strcpy(contatos[indice].trabalho, trabalhoNovo);
    return 1;
}