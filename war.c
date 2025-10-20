#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// IGOR FREIRE
#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// ---------- PROTÓTIPOS ----------
void inicializarTerritorios(Territorio *mapa, int n);
void mostrarMapa(const Territorio *mapa, int n);
void batalha(Territorio *atacante, Territorio *defensor);
void menuPrincipal(Territorio *mapa, int n);
int verificarMissao(const Territorio *mapa, int n, const char *corJogador);

// ---------- FUNÇÕES ----------
void inicializarTerritorios(Territorio *mapa, int n) {
    const char *nomesPadrao[] = {"Brasil", "Argentina", "Chile", "Peru", "Colômbia"};
    const char *coresPadrao[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Roxo"};
    int tropasPadrao[] = {5, 4, 6, 3, 7};

    for (int i = 0; i < n; i++) {
        strcpy(mapa[i].nome, nomesPadrao[i]);
        strcpy(mapa[i].cor, coresPadrao[i]);
        mapa[i].tropas = tropasPadrao[i];
    }
}

void mostrarMapa(const Territorio *mapa, int n) {
    printf("\n🌍 ESTADO ATUAL DO MAPA:\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Exército: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

void batalha(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n⚠️ O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\n⚔️ BATALHA ENTRE %s (Atacante - %s) E %s (Defensor - %s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("🎲 Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas -= 1;
        printf("🔥 O atacante venceu! O defensor perdeu 1 tropa.\n");

        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas - 1;
            atacante->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
            printf("🏴‍☠️ O território %s foi CONQUISTADO pelo exército %s!\n", defensor->nome, defensor->cor);
        }
    } else {
        atacante->tropas -= 1;
        printf("🛡️ O defensor resistiu! O atacante perdeu 1 tropa.\n");
    }
}

int verificarMissao(const Territorio *mapa, int n, const char *corJogador) {
    int conquistados = 0;
    int verdeDestruido = 1; // começa verdadeiro, vira falso se ainda existir verde

    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0)
            conquistados++;

        if (strcmp(mapa[i].cor, "Verde") == 0)
            verdeDestruido = 0;
    }

    printf("\n🎯 STATUS DA MISSÃO:\n");
    printf("  - Territórios conquistados: %d\n", conquistados);
    printf("  - Exército verde %s\n", verdeDestruido ? "foi destruído ✅" : "ainda existe ❌");

    if (verdeDestruido && conquistados >= 3) {
        printf("\n🏆 MISSÃO CUMPRIDA! Você venceu o jogo!\n");
        return 1;
    }

    printf("  ➜ Continue jogando!\n");
    return 0;
}

void menuPrincipal(Territorio *mapa, int n) {
    int opcao;
    char corJogador[TAM_COR] = "Vermelho"; // jogador principal

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            mostrarMapa(mapa, n);
            int atq, def;
            printf("\nEscolha o território atacante (1 a %d): ", n);
            scanf("%d", &atq);
            getchar();
            printf("Escolha o território defensor (1 a %d): ", n);
            scanf("%d", &def);
            getchar();

            atq -= 1;
            def -= 1;

            if (atq < 0 || def < 0 || atq >= n || def >= n || atq == def) {
                printf("\n❌ Escolha inválida!\n");
                continue;
            }

            if (strcmp(mapa[atq].cor, corJogador) != 0) {
                printf("\n⚠️ Você só pode atacar com territórios do seu exército (%s)!\n", corJogador);
                continue;
            }

            batalha(&mapa[atq], &mapa[def]);
        }
        else if (opcao == 2) {
            if (verificarMissao(mapa, n, corJogador))
                break;
        }
        else if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
            break;
        }
        else {
            printf("\nOpção inválida!\n");
        }

    } while (1);
}

// ---------- PROGRAMA PRINCIPAL ----------
int main() {
    srand(time(NULL));
    int n = MAX_TERRITORIOS;

    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarTerritorios(mapa, n);
    menuPrincipal(mapa, n);

    free(mapa);
    printf("\nJogo encerrado.\n");
    return 0;
}
