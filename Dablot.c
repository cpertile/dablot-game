// Dablot v 0.2.2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define TAM_X_TAB 11
#define TAM_Y_TAB 13
#define TAM_VETOR 30

char menu_inicial(void);
void inicializa_vetor_pecas(char[*], int);
void inicializa_matriz_posicao(char[TAM_VETOR], char[TAM_VETOR], char[TAM_X_TAB][TAM_Y_TAB]);
void imprime_tabuleiro(const char [*][TAM_Y_TAB]);

int main(void) {
    // Declaração de vetores peças
    char pecas_jog1[30], pecas_jog2[30];
    // Inicialização dos vetores peças (vetor, nº do jogador)
    inicializa_vetor_pecas(pecas_jog1, 1);
    inicializa_vetor_pecas(pecas_jog2, 2);

    // Matriz de posições disponíveis para as peças
    char matriz_posicao[TAM_X_TAB][TAM_Y_TAB];
    // Colocando as peças na matriz de posições (vetor jogador 1, vetor jogador 2 e matriz posição)
    inicializa_matriz_posicao(pecas_jog1, pecas_jog2, matriz_posicao);

    // Chama o menu inicial. Retorna a escolha do jogador
    switch(menu_inicial()) {
        case 'N': imprime_tabuleiro(matriz_posicao); break;
        case 'A': printf("Funcao APRENDA A JOGAR ainda nao desenvolvida...\n"); break;
        case 'C': printf("Funcao CARREGAR JOGO SALVO ainda nao desenvolvida...\n"); break;
        case 'S': printf("Saindo...\n"); break;
    }
    return EXIT_SUCCESS;
}

char menu_inicial() {
    // Melhorar design dos printfs das escolhas
    char escolha = 'E';

    // Imprime o menu inicial do jogo
    printf("Bem-vindo(a) ao jogo Dablot!\n");
    while (escolha != 'S') {
        printf("Digite 'I' para Iniciar\nPara APRENDER A JOGAR, digite 'A'\nPara sair, digite 'S'\n");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        if (escolha == 'I') {
            while ((escolha != 'N' || escolha != 'C')) {
            printf("Deseja um Novo Jogo (N) ou Carregar Jogo Salvo (C)?\n");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);
            return escolha;
            }
        }
        return escolha;
    }
    return escolha;
}

void inicializa_vetor_pecas(char V[], int jog) {
    // Preenche o vetor passado com as peças correspondentes ao jogador 1 ou 2
    int i;
    if (jog == 1) {
        for (i = 0; i < 30; ++i) {
            if (i < 28) {
                V[i] = 'g';
            } else  if (i < 29) {
                  V[i] = 'p';
               } else {
                    V[i] = 'R';
            }
        }
    }
    if (jog == 2) {
        for (i = 0; i < 30; ++i) {
            if (i < 28) {
                V[i] = 'c';
            } else  if (i < 29) {
                  V[i] = 'f';
               } else {
                    V[i] = 'F';
            }
        }
    }
}

void inicializa_matriz_posicao(char V1[TAM_VETOR], char V2[TAM_VETOR], char pos[TAM_X_TAB][TAM_Y_TAB]) {
    // Preenche as posições com as peças
    // Linhas pares = colunas pares
    // Linhas ímpares = colunas ímpares
    int i = 0;
    int j = 0;
    int x, y;

    // Para cada linha, da 0 até a 4
    for (y = 0; y < 5; ++y) {
        for (x = 0; x < TAM_X_TAB; x++) {
            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    pos[x][y] = V1[i];  // Se a linha for par e a coluna for par, coloque a peça do vetor na matriz
                    i++;
                } else {
                    pos[x][y] = '0';      // Se a coluna for ímpar, recebe 0
                }
            } else {
                if (x % 2 == 1) {       // Se a linha for ímpar e a coluna for ímpar, coloque a peça do vetor na matriz
                    pos[x][y] = V1[i];
                    i++;
                } else {                // Se a coluna for par, recebe 0
                    pos[x][y] = '0';
                }
            }
        }
    }

    // Para cada linha, da 12 até a 8
    for (y = 12; y > 7; --y) {
        for (x = 0; x < TAM_X_TAB; x++) {
            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    pos[x][y] = V2[j];  // Se a linha for par e a coluna for par, coloque a peça do vetor na matriz
                    j++;
                } else {
                    pos[x][y] = '0';      // Se a coluna for ímpar, recebe 0
                }
            } else {
                if (x % 2 == 1) {       // Se a linha for ímpar e a coluna for ímpar, coloque a peça do vetor na matriz
                    pos[x][y] = V2[j];
                    j++;
                } else {                // Se a coluna for par, recebe 0
                    pos[x][y] = '0';
                }
            }
        }
    }

    // Para a linha 5, se a coluna for par recebe 0
    // Se a coluna for ímpar, se for 1 recebe V1[28], se for outro número recebe espaço (' ')
    for (x = 0; x < TAM_X_TAB; x++) {
        if (x % 2 == 0) {
            pos[x][5] = '0';
        } else {
            if (x == 1) {
                pos[x][5] = V1[28];
            } else {
                pos[x][5] = ' ';            
            }
        }
    }

    // Para a linha 6, se a coluna for ímpar, recebe 0
    // Se a coluna for par e 0, coloque a peça V1[29] na posição pos[0][6], se for 10, a peça V2[29] na pos[10][6], e outro núm recebe espaço (' ')
    for (x = 0; x < TAM_X_TAB; x++) {
        if (x % 2 == 1) {
            pos[x][6] = '0';
        } else {
            if (x == 0) {
                pos[x][6] = V1[29];
            } else if (x == 10) {
                pos[x][6] = V2[29];
            } else {
                pos[x][6] = ' ';            
            }
        }
    }
    
    // Para a linha 7, se a coluna for par recebe 0
    // Se a coluna for ímpar, se for 9 recebe a peça V2[28], se não recebe espaço (' ')
    for (x = 0; x < TAM_X_TAB; x++) {
        if (x % 2 == 0) {
            pos[x][7] = '0';
        } else {
            if (x == 9) {
                pos[x][7] = V2[28];
            } else {
                pos[x][7] = ' ';
            }
        }
    }
}

void imprime_tabuleiro(const char T[TAM_X_TAB][TAM_Y_TAB]) {
    // Imprime em tela o tabuleiro, sendo a matriz de posições + as strings da moldura
    // Se T[x][y] != '0', putchar. Se == '0', printf("string");
    int x, y;
    
    // Cabeçalho
    puts("     A  B  C  D  E  F  G  H  I  J  K ");
    
    // Para cada linha, se o índice da linha for par ou ímpar, acontece algo diferente
    for (y = 0; y < TAM_Y_TAB; y++) {
        if (y % 2 == 0) {
            // Linha índice par (y = 0, linha = 1)
            if (y < 10) {
                printf(" %d  [", y+1);
            } else {
                printf(" %d [", y+1);
            }
            for (x = 0; x < TAM_X_TAB; x++) {
                if (T[x][y] != '0') {
                    putchar(T[x][y]);
                } else {
                    printf("]---[");
                }
            }
            puts("]");
            if (y < 12) {
                puts("     | \\ / | \\ / | \\ / | \\ / | \\ / | ");
            }
        } else {
            // Linha índice ímpar (y = 1, linha = 2)
            if (y < 9) {
                printf(" %d   | [", y+1);                
            } else {
                printf(" %d  | [", y+1);                
            }
            for (x = 1; x < TAM_X_TAB-1; x++) {
                if (T[x][y] != '0') {
                    putchar(T[x][y]);
                } else {
                    printf("] | [");
                }
            }
            puts("] | ");
            puts("     | / \\ | / \\ | / \\ | / \\ | / \\ | ");
        }
    }
}

/* void iniciar_jogo(void) {
    while (!fim_jogo()) 
}*/