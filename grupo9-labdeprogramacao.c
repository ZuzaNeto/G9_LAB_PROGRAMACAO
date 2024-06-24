#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Alunos: André Vitor Abreu Moreira (2021053190) Bryan Windson Queiroz de Souza (2021065987) João Guiulherme Miranda Lago (2021017881) José Nunes de Sousa Neto (2022003263)

// Definindo a estrutura para representar um time de futebol
typedef struct {
    char nome[50];
    int pontos; // Para armazenar os pontos do time
    char historico[500]; // Para armazenar o histórico de jogos do time
} Time;

void adicionarHistorico(Time* time, const char* adversario, const char* resultado) {
    char entrada[100];
    snprintf(entrada, sizeof(entrada), "%s contra %s: %s\n", time->nome, adversario, resultado);
    strncat(time->historico, entrada, sizeof(time->historico) - strlen(time->historico) - 1);
}

void sortearPartidas(Time* grupo, int tamanho) {
    printf("\nPartidas do grupo:\n");
    for (int i = 0; i < tamanho; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            printf("%s x %s\n", grupo[i].nome, grupo[j].nome);
            printf("%s x %s\n", grupo[j].nome, grupo[i].nome);
        }
    }
}

void registrarResultados(Time* grupo, int tamanho) {
    printf("\nDigite os resultados das partidas:\n");
    for (int i = 0; i < tamanho; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            int resultado;
            printf("Resultado para a partida %s x %s (1 para %s, 2 para empate, 3 para %s): ", grupo[i].nome, grupo[j].nome, grupo[i].nome, grupo[j].nome);
            scanf("%d", &resultado);
            if (resultado == 1) {
                grupo[i].pontos += 3; // Vitória para o primeiro time
                adicionarHistorico(&grupo[i], grupo[j].nome, "Venceu");
                adicionarHistorico(&grupo[j], grupo[i].nome, "Perdeu");
            } else if (resultado == 2) {
                grupo[i].pontos += 1; // Empate
                grupo[j].pontos += 1; // Empate
                adicionarHistorico(&grupo[i], grupo[j].nome, "Empatou");
                adicionarHistorico(&grupo[j], grupo[i].nome, "Empatou");
            } else if (resultado == 3) {
                grupo[j].pontos += 3; // Vitória para o segundo time
                adicionarHistorico(&grupo[i], grupo[j].nome, "Perdeu");
                adicionarHistorico(&grupo[j], grupo[i].nome, "Venceu");
            } else {
                printf("Opção inválida. Por favor, insira 1, 2 ou 3.\n");
                j -= 1; // Repetir a entrada para esta partida
                continue;
            }

            printf("Resultado para a partida %s x %s (1 para %s, 2 para empate, 3 para %s): ", grupo[j].nome, grupo[i].nome, grupo[j].nome, grupo[i].nome);
            scanf("%d", &resultado);
            if (resultado == 1) {
                grupo[j].pontos += 3; // Vitória para o primeiro time (agora é grupo[j])
                adicionarHistorico(&grupo[j], grupo[i].nome, "Venceu");
                adicionarHistorico(&grupo[i], grupo[j].nome, "Perdeu");
            } else if (resultado == 2) {
                grupo[i].pontos += 1; // Empate
                grupo[j].pontos += 1; // Empate
                adicionarHistorico(&grupo[i], grupo[j].nome, "Empatou");
                adicionarHistorico(&grupo[j], grupo[i].nome, "Empatou");
            } else if (resultado == 3) {
                grupo[i].pontos += 3; // Vitória para o segundo time (agora é grupo[i])
                adicionarHistorico(&grupo[j], grupo[i].nome, "Perdeu");
                adicionarHistorico(&grupo[i], grupo[j].nome, "Venceu");
            } else {
                printf("Opção inválida. Por favor, insira 1, 2 ou 3.\n");
                j -= 1; // Repetir a entrada para esta partida
                continue;
            }
        }
    }
}

void exibirClassificacao(Time* times, int numTimes, const char* grupoNome) {
    // Ordenar os times pelo número de pontos (decrescente)
    for (int i = 0; i < numTimes - 1; ++i) {
        for (int j = i + 1; j < numTimes; ++j) {
            if (times[i].pontos < times[j].pontos) {
                Time temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
        }
    }

    printf("\n----- Classificação Final do Grupo %s -----\n", grupoNome);
    for (int i = 0; i < numTimes; ++i) {
        printf("Time %d: %s - Pontos: %d\n", i + 1, times[i].nome, times[i].pontos);
    }
}

void exibirTitulo() {
    printf("========================================\n");
    printf("          TORNEIO DE FUTEBOL CODADO     \n");
    printf("========================================\n\n");
}

void exibirTituloMataMata() {
    printf("========================================\n");
    printf("             TORNEIO MATA-MATA          \n");
    printf("========================================\n\n");
}

void exibirTituloFaseDeGrupos() {
    printf("========================================\n");
    printf("          TORNEIO FASE DE GRUPOS        \n");
    printf("========================================\n\n");
}

int main() {
    exibirTitulo(); // Exibir o título no início do programa

    int numTimes;
    char modalidade[20];

    // Solicita o número de times e a modalidade do torneio
    while (1) {
        printf("Digite o número de times no torneio (2, 4 ou 8): ");
        scanf("%d", &numTimes);
        if (numTimes == 2 || numTimes == 4 || numTimes == 8) {
            break;
        }
        printf("Número de times inválido. Por favor, insira 2, 4 ou 8.\n");
    }
    getchar(); // Limpar o buffer do teclado

    while (1) {
        printf("Digite a modalidade do torneio (mata-mata ou fase de grupos): ");
        fgets(modalidade, sizeof(modalidade), stdin);
        modalidade[strcspn(modalidade, "\n")] = '\0'; // Remove newline

        if ((strcmp(modalidade, "mata-mata") == 0) ||
            (strcmp(modalidade, "fase de grupos") == 0 && (numTimes == 4 || numTimes == 8))) {
            break;
        }
        printf("Modalidade inválida ou número de times incompatível. Por favor, insira 'mata-mata' ou 'fase de grupos' (somente 4 ou 8 times).\n");
    }

    Time times[numTimes]; // Vetor para armazenar os times

    // Entrada dos nomes dos times
    for (int i = 0; i < numTimes; ++i) {
        printf("Digite o nome do time %d: ", i + 1);
        fgets(times[i].nome, sizeof(times[i].nome), stdin);
        times[i].nome[strcspn(times[i].nome, "\n")] = '\0'; // Remove newline

        times[i].pontos = 0; // Inicializa os pontos do time
        times[i].historico[0] = '\0'; // Inicializa o histórico do time
    }

    // Embaralhar os times aleatoriamente
    srand(time(0)); // Semente para geração de números aleatórios
    for (int i = 0; i < numTimes; ++i) {
        int j = rand() % numTimes;
        Time temp = times[i];
        times[i] = times[j];
        times[j] = temp;
    }

    if (strcmp(modalidade, "fase de grupos") == 0) {
        exibirTituloFaseDeGrupos();

        int numGrupos = (numTimes == 8) ? 2 : 1;
        int timesPorGrupo = numTimes / numGrupos;

        // Exibir os times sorteados em grupos
        printf("\n----- Times em grupos -----\n");
        for (int grupo = 0; grupo < numGrupos; ++grupo) {
            printf("\nGrupo %c:\n", 'A' + grupo);
            Time grupoTimes[timesPorGrupo];

            // Copiar times para o grupo atual
            for (int i = 0; i < timesPorGrupo; ++i) {
                grupoTimes[i] = times[grupo * timesPorGrupo + i];
            }

            // Ordenar e exibir os times do grupo
            for (int i = 0; i < timesPorGrupo; ++i) {
                for (int j = i + 1; j < timesPorGrupo; ++j) {
                    if (strcmp(grupoTimes[i].nome, grupoTimes[j].nome) > 0) {
                        Time temp = grupoTimes[i];
                        grupoTimes[i] = grupoTimes[j];
                        grupoTimes[j] = temp;
                    }
                }
            }

            for (int i = 0; i < timesPorGrupo; ++i) {
                printf("%s\n", grupoTimes[i].nome);
            }

            // Sortear e registrar resultados das partidas
            sortearPartidas(grupoTimes, timesPorGrupo);
            registrarResultados(grupoTimes, timesPorGrupo);

            // Atualizar os pontos dos times no vetor principal
            for (int i = 0; i < timesPorGrupo; ++i) {
                times[grupo * timesPorGrupo + i] = grupoTimes[i];
            }

            // Exibir classificação final do grupo
            exibirClassificacao(grupoTimes, timesPorGrupo, grupo == 0 ? "A" : "B");

            // Atualizar os times do grupo no vetor principal
            for (int i = 0; i < timesPorGrupo; ++i) {
                times[grupo * timesPorGrupo + i] = grupoTimes[i];
            }
        }

        // Determinar os campeões de cada grupo e realizar a partida final se necessário
        if (numGrupos == 2) {
            Time grupoA[timesPorGrupo];
            Time grupoB[timesPorGrupo];

            for (int i = 0; i < timesPorGrupo; ++i) {
                grupoA[i] = times[i];
                grupoB[i] = times[timesPorGrupo + i];
            }

            // Campeão do Grupo A e Grupo B
            printf("\nCampeão do Grupo A: %s\n", grupoA[0].nome);
            printf("\nCampeão do Grupo B: %s\n", grupoB[0].nome);

            // Partida final entre os campeões dos grupos
            printf("\n----- Partida Final entre Campeões dos Grupos -----\n");
            while (1) {
                int resultado;
                printf("Resultado para a partida %s x %s (1 para %s, 2 para %s): ", grupoA[0].nome, grupoB[0].nome, grupoA[0].nome, grupoB[0].nome);
                scanf("%d", &resultado);
                getchar(); // Limpar o buffer do teclado

                if (resultado == 1) {
                    adicionarHistorico(&grupoA[0], grupoB[0].nome, "Venceu");
                    adicionarHistorico(&grupoB[0], grupoA[0].nome, "Perdeu");
                    printf("\nO campeão do torneio é: %s\n", grupoA[0].nome);
                    printf("\nCaminho percorrido pelo campeão %s:\n%s", grupoA[0].nome, grupoA[0].historico);
                    break;
                } else if (resultado == 2) {
                    adicionarHistorico(&grupoB[0], grupoA[0].nome, "Venceu");
                    adicionarHistorico(&grupoA[0], grupoB[0].nome, "Perdeu");
                    printf("\nO campeão do torneio é: %s\n", grupoB[0].nome);
                    printf("\nCaminho percorrido pelo campeão %s:\n%s", grupoB[0].nome, grupoB[0].historico);
                    break;
                } else {
                    printf("Opção inválida. Por favor, insira 1 ou 2.\n");
                }
            }
        } else {
            exibirClassificacao(times, numTimes, "Único");
            printf("\nCaminho percorrido pelo campeão %s:\n%s", times[0].nome, times[0].historico);
        }

    } else if (strcmp(modalidade, "mata-mata") == 0) {
        exibirTituloMataMata();

        printf("\n----- Torneio Mata-Mata -----\n");

        while (numTimes > 1) {
            for (int i = 0; i < numTimes; i += 2) {
                printf("Partida: %s x %s\n", times[i].nome, times[i + 1].nome);
                int resultado;
                printf("Digite o resultado (1 para %s, 2 para %s): ", times[i].nome, times[i + 1].nome);
                scanf("%d", &resultado);
                getchar(); // Limpar o buffer do teclado

                if (resultado == 1) {
                    times[i].pontos += 3;
                    adicionarHistorico(&times[i], times[i + 1].nome, "Venceu");
                    adicionarHistorico(&times[i + 1], times[i].nome, "Perdeu");
                } else if (resultado == 2) {
                    times[i + 1].pontos += 3;
                    adicionarHistorico(&times[i], times[i + 1].nome, "Perdeu");
                    adicionarHistorico(&times[i + 1], times[i].nome, "Venceu");
                } else {
                    printf("Opção inválida. Por favor, insira 1 ou 2.\n");
                    i -= 2;
                    continue;
                }
            }

            // Atualizar número de times para próxima fase
            Time vencedores[numTimes / 2];
            int j = 0;
            for (int i = 0; i < numTimes; i++) {
                if (times[i].pontos > 0) {
                    vencedores[j++] = times[i];
                }
            }

            // Copiar vencedores para a próxima rodada
            numTimes /= 2;
            for (int i = 0; i < numTimes; i++) {
                times[i] = vencedores[i];
                times[i].pontos = 0; // Reinicializar pontos para próxima rodada
            }

            if (numTimes == 4 || numTimes == 2) {
                printf("\n- - - - - - - - - - - - - -\n");
            }

            if (numTimes == 1) {
                printf("\nO campeão é: %s\n", times[0].nome);
                printf("\nCaminho percorrido pelo campeão %s:\n%s", times[0].nome, times[0].historico);
                break;
            }
        }
    }

    return 0;
}
