#include <stdlib.h>
#include <stdio.h>

#define TAM_X_TAB 11
#define TAM_Y_TAB 13
#define TAM_VETOR 30

void inicializa_vetor_pecas(char[*], int);
void inicializa_matriz_posicao(char[TAM_VETOR], char[TAM_VETOR], char[TAM_X_TAB][TAM_Y_TAB]);
void imprime_tabuleiro(const char [*][TAM_Y_TAB]);

int main(void) {
    printf("Dablot v0.2\n");
    // Declaração de vetores peças
    char pecas_jog1[30], pecas_jog2[30];
    // Inicialização dos vetores peças (vetor, nº do jogador)
    inicializa_vetor_pecas(pecas_jog1, 1);
    inicializa_vetor_pecas(pecas_jog2, 2);

    // Matriz de posições disponíveis para as peças
    char matriz_posicao[TAM_X_TAB][TAM_Y_TAB];
    // Colocando as peças na matriz de posições (vetor jogador 1, vetor jogador 2 e matriz posição)
    inicializa_matriz_posicao(pecas_jog1, pecas_jog2, matriz_posicao);

    // Primeira impressão da matriz posição, sem o tabuleiro junto
    imprime_tabuleiro(matriz_posicao);
    return EXIT_SUCCESS;
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
    // Só usa a posição da matriz se ela não tiver um 0, ou seja, for válida
    int x, y;
    puts("    A  B  C  D  E  F  G  H  I  J  K ");
    // Para as linhas pares, 
    for (y = 0; y < TAM_Y_TAB; y++) {
        for (x = 0; x < TAM_X_TAB; x++) {
            if (T[x][y] != 0) {
                putchar(T[x][y]);
            }
        }
        putchar('\n');
    }
}