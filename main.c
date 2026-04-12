#include "deff.h"

int main(){
    int i, opcao;
    char delimitador = ';';

    // obter data e hora
    time_t tempoAtual = time(NULL);
    struct tm *tempoInfo = localtime(&tempoAtual);

    int dia = tempoInfo->tm_mday, mes = tempoInfo->tm_mon + 1, ano = tempoInfo->tm_year + 1900;
    int hora = tempoInfo->tm_hour, min = tempoInfo->tm_min, diaSemana = tempoInfo->tm_wday;

    // variáveis usadas no menu
    int idProcurado, idRemove, visualizar, acompanhanteNova, acompanhanteAdd, normaAtv; // case 3, 2, 2, 6, 4 e 7 (respectivamente)
    char nomeNovo[100], telefoneNovo[16], emailNovo[100], trabalhoNovo[100]; // case 3
    char dataAtv[11], horaAtv[6], dataNova[11], horaNova[6], tipoNova[100]; // case 6
    char nomeAdd[100], telefoneAdd[16], emailAdd[100], trabalhoAdd[100]; // case 1
    char dataAdd[11], horaAdd[6], tipoAdd[100]; // case 4
    char dataRemove[11], horaRemove[6];
    Contato *temp = NULL; // case 1
    Atividade *aux = NULL; // case 4


    // transformação em string
    char dataAtual[11];
    sprintf(dataAtual, "%02d/%02d/%d", dia, mes, ano);
    char horaAtual[6];
    sprintf(horaAtual, "%02dh%02d", hora, min);

    int totalContatos = 0;
    int totalId = 1;
    Contato *contatos = lerContato(CONTATOS_OUTPUT, &totalContatos, delimitador);
    if (contatos == NULL) {
        printf("Dados anteriores nao encontrados. Inicializando a lista de contatos nula.\n");
    }
    else totalId = contatos[totalContatos - 1].id + 1;

    int totalAtividades = 0;
    Atividade *agenda = lerAtividade(AGENDA_OUTPUT, &totalAtividades, delimitador);
    if (agenda == NULL) {
        printf("Dados anteriores nao encontrados. Inicializando a agenda nula.\n");
    }

    printf("============================\n");
    printf("\tAgendaPlus\n");
    printf("============================\n");

    printf("Data: %s\tHora %s\n", dataAtual, horaAtual);
    printf("\n\n");

    printf("!! ALERTAS !!\n");
    printf("----------------------------\n");
    for (i = 0; i < totalAtividades; i++) {
        imprimirAtividade(2, agenda, contatos, totalContatos, i, dataAtual, horaAtual, diaSemana);
    }
    printf("----------------------------\n");

    printf("\n");

    do {
        printf("OPCOES PRINCIPAIS:\n");
        printf("\t1. Cadastrar contato\n");
        printf("\t2. Excluir contato\n");
        printf("\t3. Atualizar contato\n");
        printf("\t4. Cadastrar atividade\n");
        printf("\t5. Remover atividade\n");
        printf("\t6. Atualizar atividade\n");
        printf("\t7. Consultar atividade (periodo, dia, semana ou mes)\n");
        printf("\t0. Sair do menu\n");

        printf("Digite a opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("\n--- CADASTRAR CONTATO ---\n");
                temp = (Contato *)realloc(contatos, (totalContatos + 1) * sizeof(Contato));
                if (temp == NULL) {
                    printf("Erro na alocacao!");
                    break;
                }
                contatos = temp;

                printf("Digite o nome do contato novo: ");
                scanf("%99[^\n]", nomeAdd);

                getchar();
                printf("Digite o telefone do contato novo [(xx) xxxxx-xxxx]: ");
                scanf("%15[^\n]", telefoneAdd);

                printf("Digite o email do contato novo: ");
                scanf("%99s", emailAdd);

                getchar();
                printf("Digite o local de trabalho do contato novo: ");
                scanf("%99[^\n]", trabalhoAdd);

                addContato(&contatos[totalContatos], totalId, nomeAdd, telefoneAdd, emailAdd, trabalhoAdd);
                totalContatos++;
                printf("Contato com ID %d criado com sucesso!\n", totalId);
                totalId++;
                break;

            case 2:
                printf("\n--- REMOVER CONTATO ---\n");
                printf("1 para SIM\t0 para NAO\nVoce deseja visualizar a lista de contatos para saber os IDs?\n");
                scanf("%d", &visualizar);
                if (visualizar) imprimirContatos(contatos, totalContatos);

                printf("Digite o ID do contato que deseja excluir: ");
                scanf("%d", &idRemove);

                if (removeContato(contatos, idRemove, totalContatos)) {
                    printf("Contato deletado com sucesso!\n");
                    removeAcompanhante(agenda, totalAtividades, idRemove);
                    totalContatos--;
                    temp = (Contato *)realloc(contatos, (totalContatos) * sizeof(Contato));
                    if (temp == NULL) {
                        printf("Erro na alocacao!");
                        break;
                    }
                    contatos = temp;
                }

                else printf("ID nao achado.\n");
                break;

            case 3: 
                printf("\n--- ATUALIZAR CONTATO ---\n");
                printf("1 para SIM\t0 para NAO\nVoce deseja visualizar a lista de contatos para saber os IDs?\n");
                scanf("%d", &visualizar);
                if (visualizar) imprimirContatos(contatos, totalContatos);

                printf("Digite o ID: ");
                scanf("%d", &idProcurado);

                getchar();
                printf("Digite o novo nome: ");
                scanf("%99[^\n]", nomeNovo);
                
                getchar();
                printf("Digite o novo telefone: ");
                scanf("%15[^\n]", telefoneNovo);

                printf("Digite o novo email: ");
                scanf("%99s", emailNovo);

                getchar();
                printf("Digite o novo local de trabalho: ");
                scanf("%99[^\n]", trabalhoNovo);

                if (atualizarContato(contatos, totalContatos, idProcurado, nomeNovo, telefoneNovo, emailNovo, trabalhoNovo))
                    printf("Informacoes atualizadas com sucesso!\n");
                else
                    printf("Erro na atualizacao.\n");
                break;

            case 4:
                printf("\n--- CADASTRAR ATIVIDADE ---\n");
                aux = (Atividade *)realloc(agenda, (totalAtividades + 1) * sizeof(Atividade));
                if (aux == NULL) {
                    printf("Erro na alocação!");
                    break;
                }
                agenda = aux;

                printf("Digite a data (DD/MM/AAAA) da nova atividade: ");
                scanf("%10s", dataAdd);

                printf("Digite a hora (HHhMM) da nova atividade: ");
                scanf("%5s", horaAdd);

                getchar();
                printf("Digite o tipo da nova atividade: ");
                scanf("%99[^\n]", tipoAdd);

                printf("Digite o ID do acompanhante (-1 caso nao haja): ");
                scanf("%d", &acompanhanteAdd);

                addAtividade(&agenda[totalAtividades], dataAdd, horaAdd, tipoAdd, acompanhanteAdd);
                totalAtividades++;
                printf("Atividade criada com sucesso!\n");
                break;

            case 5:
                printf("\n--- REMOVER ATIVIDADE ---\n");
                printf("Digite a data (DD/MM/AAAA) da atividade que deseja excluir: ");
                scanf(" %10s", dataRemove);
                printf("Digite a hora (HHhMM) da atividade que deseja excluir: ");
                scanf(" %5s", horaRemove);

                if (removeAtividade(agenda, totalAtividades, dataRemove, horaRemove)) {
                    printf("Atividade deletada com sucesso!\n");
                    totalAtividades--;
                    aux = (Atividade *)realloc(agenda, (totalAtividades) * sizeof(Atividade));
                    if (aux == NULL) {
                        printf("Erro na alocacao!");
                        break;
                    }
                    agenda = aux;
                }
                else printf("Ativdade nao achada.\n");
                break;

            case 6:
                printf("\n--- ATUALIZAR ATIVIDADE ---\n");
                printf("Voce deseja atualizar a atividade de qual data e hora?\nData (DD/MM/AAAA): ");
                scanf("%10s", dataAtv);
                printf("Hora (HHhMM): ");
                scanf("%5s", horaAtv);

                printf("Digite a nova data (DD/MM/AAAA): ");
                scanf("%10s", dataNova);

                printf("Digite a nova hora (HHhMM): ");
                scanf("%5s", horaNova);

                getchar();
                printf("Digite o novo tipo: ");
                scanf("%99[^\n]", tipoNova);

                printf("Digite o ID do acompanhante (-1 caso nao haja): ");
                scanf("%d", &acompanhanteNova);
                getchar();
                
                if (atualizarAtividade(agenda, totalAtividades, dataAtv, horaAtv, dataNova, horaNova, tipoNova, acompanhanteNova))
                    printf("Informacoes atualizadas com sucesso!\n");
                else
                    printf("Erro na atualizacao (horario indisponível / atividade nao encontrada).\n");
                break;
            
            case 7:
                printf("\n--- CONSULTAR ATIVIDADE ---\n");
                printf("Escolha se voce deseja visualizar a atividade do\n");
                printf("\t1. Periodo do dia atual\n");
                printf("\t2. Restante do dia\n");
                printf("\t3. Restante da semana\n");
                printf("\t4. Restante do mes\n");
                printf("Digite a opcao: ");
                scanf("%d", &normaAtv);
                getchar();

                for (i = 0; i < totalAtividades; i++) {
                    imprimirAtividade(normaAtv, agenda, contatos, totalContatos, i, dataAtual, horaAtual, diaSemana);
                }
                break;

            case 0:
                printf("Salvando dados . . .\n");
                if (gravarContato(contatos, totalContatos, CONTATOS_OUTPUT, delimitador))
                    printf("Contatos salvos com sucesso!\n");
                else
                    printf("Erro ao abrir o arquivo.\n");
                if (gravarAtividade(agenda, totalAtividades, AGENDA_OUTPUT, delimitador))
                    printf("Agenda salva com sucesso!\n");
                else
                    printf("Erro ao abrir o arquivo.\n");
                printf("Saindo do menu.\n");
                break;

            default:
                printf("!! Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    free(agenda);
    free(contatos);
    return 0;
}