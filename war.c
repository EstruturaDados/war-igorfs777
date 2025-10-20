#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o \n
        printf("\n");
    }
}

// Função para mostrar o mapa atual
void mostrarMapa(Territorio *mapa, int n) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Exército: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função para simular uma batalha
void batalha(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n⚠️ O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtq = rand() % 6 + 1; // valores entre 1 e 6
    int dadoDef = rand() % 6 + 1;

    printf("\n🎲 BATALHA ENTRE %s (Atacante) E %s (Defensor)\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas -= 1;
        printf("🔥 O atacante venceu! O defensor perdeu 1 tropa.\n");

        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas - 1;
            atacante->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
            printf("🏴‍☠️ O território %s foi CONQUISTADO pelo exército %s!\n", defensor->nome, atacante->cor);
        }
    } else {
        atacante->tropas -= 1;
        printf("🛡️ O defensor resistiu! O atacante perdeu 1 tropa.\n");
    }
}

int main() {
    srand(time(NULL));
    int n = MAX_TERRITORIOS;
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== CADASTRO DOS TERRITÓRIOS ===\n\n");
    cadastrarTerritorios(mapa, n);

    int opcao;
    do {
        mostrarMapa(mapa, n);
        printf("\nEscolha o território atacante (1 a %d, 0 para sair): ", n);
        scanf("%d", &opcao);
        getchar();
        if (opcao == 0) break;

        int atacante = opcao - 1;
        printf("Escolha o território defensor (1 a %d): ", n);
        int defensor;
        scanf("%d", &defensor);
        getchar();

        defensor -= 1;

        if (atacante == defensor || atacante < 0 || defensor < 0 || atacante >= n || defensor >= n) {
            printf("\n❌ Escolha inválida! Tente novamente.\n");
            continue;
        }

        batalha(&mapa[atacante], &mapa[defensor]);

    } while (1);

    free(mapa);
    printf("\nJogo encerrado.\n");
    return 0;
}
