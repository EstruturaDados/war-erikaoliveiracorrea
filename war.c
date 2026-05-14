#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MAX_STRING 30

// Struct dos territórios
struct Territorio {
    char nome[TAM_MAX_STRING];
    char cor[10];
    int tropas;
};

// Função para limpar buffer
void limparBufferEntrada() {

    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar território
void cadastrarTerritorio(struct Territorio *territorio) {

    printf("Digite o nome do territorio: ");
    fgets(territorio->nome, TAM_MAX_STRING, stdin);
    territorio->nome[strcspn(territorio->nome, "\n")] = 0;

    printf("Digite a cor do exercito: ");
    fgets(territorio->cor, 10, stdin);
    territorio->cor[strcspn(territorio->cor, "\n")] = 0;

    printf("Digite o numero de tropas: ");
    scanf("%d", &territorio->tropas);

    limparBufferEntrada();

    printf("\nTerritorio cadastrado com sucesso!\n");
}

// Função para listar territórios
void listarTerritorios(struct Territorio *territorios,
                       int totalTerritorios) {

    printf("\n===== LISTA DE TERRITORIOS =====\n");

    if(totalTerritorios == 0) {

        printf("Nenhum territorio cadastrado!\n");

        return;
    }

    for(int i = 0; i < totalTerritorios; i++) {

        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }
}

// Função de ataque
void atacar(struct Territorio *atacante,
            struct Territorio *defensor) {

    int dadoAtacante;
    int dadoDefensor;

    // Verifica se são da mesma cor
    if(strcmp(atacante->cor, defensor->cor) == 0) {

        printf("\nVoce nao pode atacar um territorio da mesma cor!\n");

        return;
    }

    // Verifica se atacante possui tropas suficientes
    if(atacante->tropas <= 1) {

        printf("\nO territorio atacante nao possui tropas suficientes!\n");

        return;
    }

    // Sorteio dos dados
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("\n======= BATALHA =======\n");

    printf("Atacante (%s) tirou: %d\n",
           atacante->nome,
           dadoAtacante);

    printf("Defensor (%s) tirou: %d\n",
           defensor->nome,
           dadoDefensor);

    // Vitória do atacante
    if(dadoAtacante > dadoDefensor) {

        printf("\nO atacante venceu a batalha!\n");

        // Defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas vai para o defensor
        defensor->tropas = atacante->tropas / 2;

        // Atacante perde metade das tropas
        atacante->tropas = atacante->tropas / 2;
    }
    else {

        printf("\nO defensor venceu a batalha!\n");

        // Atacante perde 1 tropa
        atacante->tropas--;
    }
}

// Função para atribuir missão
void atribuirMissao(char *destino,
                    char *missoes[],
                    int totalMissoes) {

    int sorteio = rand() % totalMissoes;

    strcpy(destino, missoes[sorteio]);
}

// Função para exibir missão
void exibirMissao(char *missao,
                  int jogador) {

    printf("\n===== MISSAO DO JOGADOR %d =====\n",
           jogador);

    printf("%s\n", missao);
}

// Função para verificar missão
int verificarMissao(char *missao,
                    struct Territorio *mapa,
                    int tamanho) {

    int contadorAzul = 0;
    int contadorVermelho = 0;

    for(int i = 0; i < tamanho; i++) {

        if(strcmp(mapa[i].cor, "Azul") == 0) {

            contadorAzul++;
        }

        if(strcmp(mapa[i].cor, "Vermelho") == 0) {

            contadorVermelho++;
        }
    }

    // Missão Azul
    if(strcmp(missao,
       "Conquistar 3 territorios da cor Azul") == 0) {

        if(contadorAzul >= 3) {

            return 1;
        }
    }

    // Missão Vermelho
    if(strcmp(missao,
       "Conquistar 3 territorios da cor Vermelho") == 0) {

        if(contadorVermelho >= 3) {

            return 1;
        }
    }

    return 0;
}

// Função para liberar memória
void liberarMemoria(struct Territorio *mapa,
                    char *missaoJogador1,
                    char *missaoJogador2) {

    free(mapa);

    free(missaoJogador1);

    free(missaoJogador2);

    printf("\nMemoria liberada com sucesso!\n");
}

int main() {

    int quantidadeTerritorios;
    int totalTerritorios = 0;
    int opcao;

    srand(time(NULL));

    // Vetor de missões
    char *missoes[] = {

        "Conquistar 3 territorios da cor Azul",

        "Conquistar 3 territorios da cor Vermelho",

        "Eliminar tropas inimigas",

        "Dominar metade do mapa",

        "Vencer 2 batalhas seguidas"
    };

    int totalMissoes = 5;

    printf("Quantos territorios deseja cadastrar? ");

    scanf("%d", &quantidadeTerritorios);

    limparBufferEntrada();

    // Alocação dinâmica dos territórios
    struct Territorio *territorios;

    territorios = (struct Territorio *)
                  calloc(quantidadeTerritorios,
                  sizeof(struct Territorio));

    if(territorios == NULL) {

        printf("Erro ao alocar memoria!\n");

        return 1;
    }

    // Alocação dinâmica das missões
    char *missaoJogador1 =
        (char *) malloc(100 * sizeof(char));

    char *missaoJogador2 =
        (char *) malloc(100 * sizeof(char));

    if(missaoJogador1 == NULL ||
       missaoJogador2 == NULL) {

        printf("Erro ao alocar memoria das missoes!\n");

        return 1;
    }

    // Sorteio das missões
    atribuirMissao(
        missaoJogador1,
        missoes,
        totalMissoes
    );

    atribuirMissao(
        missaoJogador2,
        missoes,
        totalMissoes
    );

    // Exibe missão apenas uma vez
    exibirMissao(missaoJogador1, 1);

    exibirMissao(missaoJogador2, 2);

    do {

        printf("\n----------------------------\n");
        printf("======== JOGO WAR ==========\n");
        printf("----------------------------\n");

        printf("1 - Cadastrar Territorio\n");
        printf("2 - Listar Territorios\n");
        printf("3 - Atacar Territorio\n");
        printf("0 - Sair\n");

        printf("----------------------------\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        limparBufferEntrada();

        switch(opcao) {

            case 1:

                if(totalTerritorios < quantidadeTerritorios) {

                    cadastrarTerritorio(
                        &territorios[totalTerritorios]
                    );

                    totalTerritorios++;
                }
                else {

                    printf("\nLimite de territorios atingido!\n");
                }

                break;

            case 2:

                listarTerritorios(
                    territorios,
                    totalTerritorios
                );

                break;

            case 3: {

                int atacante;
                int defensor;

                listarTerritorios(
                    territorios,
                    totalTerritorios
                );

                printf("\nEscolha o territorio atacante: ");
                scanf("%d", &atacante);

                printf("Escolha o territorio defensor: ");
                scanf("%d", &defensor);

                limparBufferEntrada();

                // Validação
                if(atacante < 1 ||
                   atacante > totalTerritorios ||
                   defensor < 1 ||
                   defensor > totalTerritorios) {

                    printf("\nTerritorio invalido!\n");
                }
                else {

                    atacar(
                        &territorios[atacante - 1],
                        &territorios[defensor - 1]
                    );

                    printf("\n===== ESTADO ATUAL =====\n");

                    listarTerritorios(
                        territorios,
                        totalTerritorios
                    );

                    // Verifica missão jogador 1
                    if(verificarMissao(
                        missaoJogador1,
                        territorios,
                        totalTerritorios)) {

                        printf("\n========================\n");
                        printf("JOGADOR 1 VENCEU!\n");
                        printf("Missao cumprida!\n");
                        printf("========================\n");
                    }

                    // Verifica missão jogador 2
                    if(verificarMissao(
                        missaoJogador2,
                        territorios,
                        totalTerritorios)) {

                        printf("\n========================\n");
                        printf("JOGADOR 2 VENCEU!\n");
                        printf("Missao cumprida!\n");
                        printf("========================\n");
                    }
                }

                break;
            }

            case 0:

                printf("\nSaindo do jogo...\n");

                break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    // Liberação da memória
    liberarMemoria(
        territorios,
        missaoJogador1,
        missaoJogador2
    );

    return 0;
}