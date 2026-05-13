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
void listarTerritorios(struct Territorio *territorios, int totalTerritorios) {

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
void atacar(struct Territorio *atacante, struct Territorio *defensor) {

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

        // Metade das tropas do atacante vai para o defensor
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

// Função para liberar memória
void liberarMemoria(struct Territorio *mapa) {

    free(mapa);

    printf("\nMemoria liberada com sucesso!\n");
}

int main() {

    int quantidadeTerritorios;
    int totalTerritorios = 0;
    int opcao;

    srand(time(NULL));

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidadeTerritorios);

    limparBufferEntrada();

    // Alocação dinâmica de memória
    struct Territorio *territorios;

    territorios = (struct Territorio *)
                  calloc(quantidadeTerritorios,
                  sizeof(struct Territorio));

    if(territorios == NULL) {

        printf("Erro ao alocar memoria!\n");

        return 1;
    }

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
                if(atacante < 1 || atacante > totalTerritorios ||
                   defensor < 1 || defensor > totalTerritorios) {

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
    liberarMemoria(territorios);

    return 0;
}