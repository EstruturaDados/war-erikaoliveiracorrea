#include <stdio.h>
#include <string.h>

#define NUM_TERRITORIO  5
#define TAM_MAX_STRING 30

struct Territorio {
    char nome[TAM_MAX_STRING];
    char cor[10];
    int tropas;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio territorios[NUM_TERRITORIO];
    int totalTerritorio = 0;
    int opcao;

    do {
        printf("\n----------------------------\n");
        printf("======== JOGO DO WAR ========\n");
        printf("----------------------------\n");
        printf("1- Cadastrar Territorio \n");
        printf("2- Listar todos os territorios \n");
        printf("0- Sair\n");
        printf("----------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                printf("\nCadastro de territorio\n");
                if(totalTerritorio < NUM_TERRITORIO) {
                    printf("Digite o nome do territorio: ");
                    fgets(territorios[totalTerritorio].nome, TAM_MAX_STRING, stdin);
                    territorios[totalTerritorio].nome[strcspn(territorios[totalTerritorio].nome, "\n")] = 0;

                    printf("Digite a cor: ");
                    fgets(territorios[totalTerritorio].cor, 10, stdin);
                    territorios[totalTerritorio].cor[strcspn(territorios[totalTerritorio].cor, "\n")] = 0;

                    printf("Digite o numero de tropas: ");
                    scanf("%d", &territorios[totalTerritorio].tropas);
                    limparBufferEntrada();

                    totalTerritorio++; 
                    printf("\nTerritorio cadastrado com sucesso!!\n");
                } else {
                    printf("Limite atingido!\n");
                }
                printf("Pressione Enter para continuar...");
                getchar();
                break;

            case 2:
                printf("\n--- Lista de Territorios ---\n");
                if(totalTerritorio == 0) {
                    printf("Nenhum cadastrado!\n");
                } else {
                    for(int i = 0; i < totalTerritorio; i++) {
                        printf("%d. %s (%s) - Tropas: %d\n", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        } // Fim do Switch
    } while(opcao != 0); // Fim do Do-While

    return 0;
}
//COMENTÁRIOS (DICAS) DA PROFESSORA.
// 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
