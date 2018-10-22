// Dablot v 0.6.0

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#define TAM_X_TAB 11
#define TAM_Y_TAB 13
#define TAM_VETOR 30
#define LIM_SUPERIOR 0
#define LIM_INFERIOR 12
#define LIM_ESQUERDO 0
#define LIM_DIREITO 10

char menu_inicial(void);
void inicializar_vetor_pecas(char[*], int);
void inicializar_matriz_posicao(char[TAM_VETOR], char[TAM_VETOR], char[TAM_X_TAB][TAM_Y_TAB]);
void comecar_jogo(char[*], char[*], bool*);
void imprimir_tabuleiro(const char[TAM_X_TAB][TAM_Y_TAB]);
void pedir_peca(const int*, int[*], char[*], char[*]);
bool validar_peca(const int*, const int[*], const char[TAM_X_TAB][TAM_Y_TAB]);
bool validar_alcance(const int[*], const char[TAM_X_TAB][TAM_Y_TAB], int[*], int[*], int[*], int[*], int[*],
    int[*], int[*], int[*], int*, int *, int *, int *, int *, int *, int *, int *,
    int[*], int[*], int[*], int[*], int[*],
    int[*], int[*], int[*], int*, int *, int *, int *, int *, int *, int *, int *);
void pedir_destino(int[*]);
bool validar_destino(const int[*], const int[*], char[TAM_X_TAB][TAM_Y_TAB], int[*], int[*], int[*], int[*], int[*],
    int[*], int[*], int[*], int *, int *, int *, int *, int *, int *, int*, int*,
    int[*], int[*], int[*], int[*], int[*],
    int[*], int[*], int[*], int *, int *, int *, int *, int *, int *, int *, int *, char [*], char[*]);
void capturar_peca(int[*], char[TAM_X_TAB][TAM_Y_TAB], char[*], char[*]);
void fazer_jogada(char[TAM_X_TAB][TAM_Y_TAB], const int[*], const int [*]);
void trocar_turno(int*);


int main(void) {
    // Variáveis gerais de funcionamento
    bool game = false;
    char nome_jogador1[20], nome_jogador2[20];
    char matriz_posicao[TAM_X_TAB][TAM_Y_TAB];
    char pecas_jog1[30], pecas_jog2[30];
    int jog_atual = 1;
    int peca[2], dest[2];

    // Posições cardeais de movimento
    int N[2], S[2], E[2], O[2], NE[2], SE[2], SO[2], NO[2];
    int iN = 0, iS = 0, iE = 0, iO = 0, iNE = 0, iSE = 0, iSO = 0, iNO = 0;

    // Posições cardeais de captura
    int cN[2], cS[2], cE[2], cO[2], cNE[2], cSE[2], cSO[2], cNO[2];
    int icN = 0, icS = 0, icE = 0, icO = 0, icNE = 0, icSE = 0, icSO = 0, icNO = 0;

    // Inicialização dos vetores peças (vetor, nº do jogador)
    inicializar_vetor_pecas(pecas_jog1, 1);
    inicializar_vetor_pecas(pecas_jog2, 2);

    // Colocando as peças na matriz de posições (vetor jogador 1, vetor jogador 2 e matriz posição)
    inicializar_matriz_posicao(pecas_jog1, pecas_jog2, matriz_posicao);
    

    // Chama o menu inicial. Retorna a escolha do jogador
    switch(menu_inicial()) {
        case 'N':
            comecar_jogo(nome_jogador1, nome_jogador2, &game);
            while (game) {
                imprimir_tabuleiro(matriz_posicao);
                pedir_peca(&jog_atual, peca, nome_jogador1, nome_jogador2);
                if (!validar_peca(&jog_atual, peca, matriz_posicao)) continue;
                if (!validar_alcance(peca, matriz_posicao, N, S, E, O, NE, SE, SO, NO, &iN, &iS, &iE, &iO, &iNE, &iSE, &iSO, &iNO,
                    cN, cS, cE, cO, cNE, cSE, cSO, cNO, &icN, &icS, &icE, &icO, &icNE, &icSE, &icSO, &icNO)) continue;
                pedir_destino(dest);
                if (!validar_destino(peca, dest, matriz_posicao, N, S, E, O, NE, SE, SO, NO, &iN, &iS, &iE, &iO, &iNE, &iSE, &iSO, &iNO,
                    cN, cS, cE, cO, cNE, cSE, cSO, cNO, &icN, &icS, &icE, &icO, &icNE, &icSE, &icSO, &icNO, pecas_jog1, pecas_jog2)) continue;
                fazer_jogada(matriz_posicao, peca, dest);
                trocar_turno(&jog_atual);
            }
            break;
        case 'A': puts("Funcao APRENDA A JOGAR ainda nao desenvolvida..."); break;
        case 'C': puts("Funcao CARREGAR JOGO SALVO ainda nao desenvolvida..."); break;
        case 'S': puts("Saindo..."); break;
        default: puts("Opcao invalida...");
    }

    return EXIT_SUCCESS;
}

char menu_inicial() {
    char escolha = 'E';

    // Limpa a tela e imprime o menu inicial do jogo
    system("clear");
    putchar('\n');
    puts("  ╔══════════════════════════════╗");
    puts("  ║ Bem-vindo(a) ao jogo Dablot! ║");
    puts("  ╚══════════════════════════════╝");
    putchar('\n');
    while (escolha != 'S') {
        puts("╔══════════════════════════════════╗");
        puts("║ Digite (A) para Aprender a jogar ║");
        puts("║      Digite (I) para Iniciar     ║");
        puts("║       Digite (S) para Sair       ║");
        puts("╚══════════════════════════════════╝");
        putchar('\n');
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        if (escolha == 'I') {
            while ((escolha != 'N' || escolha != 'C')) {
                puts("╔═════════════════════════════════════════════════════╗");
                puts("║ Deseja um Novo Jogo (N) ou Carregar Jogo Salvo (C)? ║");
                puts("╚═════════════════════════════════════════════════════╝");
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                return escolha;
            }
        }
        return escolha;
    }
    return escolha;
}

void inicializar_vetor_pecas(char V[], int jog) {
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

void inicializar_matriz_posicao(char V1[TAM_VETOR], char V2[TAM_VETOR], char pos[TAM_X_TAB][TAM_Y_TAB]) {
    // Preenche as posições com as peças
    // Linhas pares = colunas pares
    // Linhas ímpares = colunas ímpares
    int i = 0, j = 0;
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

void comecar_jogo(char nome_jogador1[], char nome_jogador2[], bool *game) {
    puts("Começando um novo jogo!");
    *game = true;
    puts("Primeiro vamos conhecer os jogadores...");
    puts("Qual o nome do jogador 1, que vai comandar o [R]ei, o [p]ríncipe e os [g]uerreiros?");
    scanf("%s", nome_jogador1);
    puts("E o jogador 2, que vai comandar o [F]azendeiro, seu [f]ilho e os [c]amponeses?");
    scanf("%s", nome_jogador2);
}

void imprimir_tabuleiro(const char T[TAM_X_TAB][TAM_Y_TAB]) {
    // Imprime em tela o tabuleiro, sendo a matriz de posições + as strings da moldura
    // Se T[x][y] != '0', putchar. Se == '0', printf("string");
    int x, y;
    
    // Limpa a tela e printa o cabeçalho
    system("clear");
    puts("╔═════════════════════════════════════════╗");
    puts("║     A  B  C  D  E  F  G  H  I  J  K     ║");
    
    // Para cada linha, se o índice da linha for par ou ímpar, acontece algo diferente
    for (y = 0; y < TAM_Y_TAB; y++) {
        if (y % 2 == 0) {
            // Linha índice par (y = 0, linha = 1)
            // Imprime as coordenadas numerais da borda esquerda
            if (y < 10) {
                printf("║  %d [", y+1);
            } else {
                printf("║ %d [", y+1);
            }
            // Imprime ou uma peça ou um separador
            for (x = 0; x < TAM_X_TAB; x++) {
                if (T[x][y] != '0') {
                    putchar(T[x][y]);
                } else {
                    printf("]---[");
                }
            }
            if (y < 10) {
                printf("] %d  ║\n", y+1);
            } else {
                printf("] %d ║\n", y+1);
            }
            if (y < 12) {
                puts("║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║");
            }
        } else {
            // Linha índice ímpar (y = 1, linha = 2)
            if (y < 9) {
                printf("║  %d  | [", y+1);                
            } else {
                printf("║ %d  | [", y+1);                
            }
            for (x = 1; x < TAM_X_TAB-1; x++) {
                if (T[x][y] != '0') {
                    putchar(T[x][y]);
                } else {
                    printf("] | [");
                }
            }
            if (y < 9) {
                printf("] |  %d  ║\n", y+1);               
            } else {
                printf("] |  %d ║\n", y+1);               
            }
            puts("║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║");
        }
    }
    puts("║     A  B  C  D  E  F  G  H  I  J  K     ║");
    puts("╚═════════════════════════════════════════╝");
    putchar('\n');
}

void pedir_peca(const int *jog_atual, int peca[], char nome_jogador1[], char nome_jogador2[]) {
    // coord_x_l = coordenada na forma letra, depois traduzida para forma número
    const int x = 0, y = 1;
    char coord_x_l;
    int coord_x_n, coord_y;

    // Pede as coordenadas e troca por algo que a matriz entende
    if (*jog_atual == 1) {
        printf("%s, sua vez!\n", nome_jogador1);
    } else {
        printf("%s, sua vez!\n", nome_jogador2);
    }
    printf("Digite as coordenadas da peça que você quer mover (ex A8): ");
    scanf(" %c", &coord_x_l);
    scanf("%d", &coord_y);
    coord_x_l = toupper(coord_x_l);
    switch(coord_x_l) {
        case 'A': coord_x_n = 0; break;
        case 'B': coord_x_n = 1; break;
        case 'C': coord_x_n = 2; break;
        case 'D': coord_x_n = 3; break;
        case 'E': coord_x_n = 4; break;
        case 'F': coord_x_n = 5; break;
        case 'G': coord_x_n = 6; break;
        case 'H': coord_x_n = 7; break;
        case 'I': coord_x_n = 8; break;
        case 'J': coord_x_n = 9; break;
        case 'K': coord_x_n = 10; break;
        default: coord_x_n = 11;
    }
    coord_y -= 1;

    // Guarda as coordenadas no vetor
    peca[x] = coord_x_n;
    peca[y] = coord_y;
}

bool validar_peca(const int *jog_atual, const int peca[], const char matriz_posicao[TAM_X_TAB][TAM_Y_TAB]) {
    const int x = 0, y = 1;
    // 1ª parte: validar se as coordenadas estão dentro do tabuleiro. Se não estiverem, retornar false
    // Princípio Coluna par Linha par / Coluna ímpar linha ímpar

    if ((peca[x] < LIM_ESQUERDO) || (peca[x] > LIM_DIREITO) || (peca[y] < LIM_SUPERIOR) || (peca[y] > LIM_INFERIOR)) {
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        sleep(2);
        return false;
    }

    if ((peca[x] % 2 == 0) && (peca[y] % 2 == 1)) {
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        sleep(2);
        return false;
    }

    if ((peca[x] % 2 == 1) && (peca[y] % 2 == 0)) {
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        sleep(2);
        return false;
    }

    // 2ª parte: validar o time da peça escolhida
    // Retornar falso se o jogador 1 escolher { F, f, c } ou se o jogador 2 escolher { R, p, g }
    // Retornar falso se qualquer jogador escolher um espaço

    // TODO: trocar o if interno pra switch

    if (*jog_atual == 1) {
        if ((matriz_posicao[peca[x]][peca[y]] == 'F') || (matriz_posicao[peca[x]][peca[y]] == 'f') || (matriz_posicao[peca[x]][peca[y]] == 'c')) {
            puts("Voce escolheu uma peca do adversario...");
            sleep(2);
            return false;
        }
    } else {
        if ((matriz_posicao[peca[x]][peca[y]] == 'R') || (matriz_posicao[peca[x]][peca[y]] == 'p') || (matriz_posicao[peca[x]][peca[y]] == 'g')) {
            puts("Voce escolheu uma peca do adversario...");
            sleep(2);
            return false;
        }
    }

    if (matriz_posicao[peca[x]][peca[y]] == ' ') {
        puts("Essa posicao estah vazia...");
        sleep(2);
        return false;
    }
    return true;
}

bool validar_alcance(const int peca[], const char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], int N[], int S[], int E[], int O[], int NE[],
    int SE[], int SO[], int NO[], int *iN, int *iS, int *iE, int *iO, int *iNE, int *iSE, int *iSO, int *iNO, 
    int cN[], int cS[], int cE[], int cO[], int cNE[],
    int cSE[], int cSO[], int cNO[], int *icN, int *icS, int *icE, int *icO, int *icNE, int *icSE, int *icSO, int *icNO) {
    const int x = 0, y = 1;
    // Retornar true se a peça pode se mover. Se ela não puder, retornar mensagem de erro e false

    // Pesquisar a matriz nos pontos cardeais em volta da peça e registrar na flag correspondente:
        // 1 se estiver livre
        // 0 se estiver ocupada por peça amiga
        // -1 se estiver ocupada por peça inimiga
    // As peças próximas às bordas precisam de validação diferente para não sair da matriz
    // Peças em linhas pares têm 8 posições de movimento e de captura
    // Peças em linhas ímpares têm 4 posições de movimento e de captura

    // Posições cardeais de movimento
    N[x] = peca[x]; N[y] = (peca[y] - 2);
    S[x] = peca[x]; S[y] = (peca[y] + 2);
    E[x] = (peca[x] + 2); E[y] = peca[y];
    O[x] = (peca[x] - 2); O[y] =  peca[y];
    NE[x] = (peca[x] + 1); NE[y] = (peca[y] - 1);
    SE[x] = (peca[x] + 1); SE[y] = (peca[y] + 1);
    SO[x] = (peca[x] - 1); SO[y] = (peca[y] + 1);
    NO[x] = (peca[x] - 1); NO[y] = (peca[y] - 1);
    *iN = 0, *iS = 0, *iE = 0, *iO = 0, *iNE = 0, *iSE = 0, *iSO = 0, *iNO = 0;

    // Posições cardeais de captura
    cN[x] = peca[x]; cN[y] = (peca[y] - 4);
    cS[x] = peca[x]; cS[y] = (peca[y] + 4);
    cE[x] = (peca[x] + 4); cE[y] = peca[y];
    cO[x] = (peca[x] - 4); cE[y] = peca[y];
    cNE[x] = (peca[x] + 2); cNE[y] = (peca[y] - 2);
    cSE[x] = (peca[x] + 2); cSE[y] = (peca[y] + 2);
    cSO[x] = (peca[x] - 2); cSO[y] = (peca[y] + 2);
    cNO[x] = (peca[x] - 2); cNO[y] = (peca[y] - 2);
    *icN = 0, *icS = 0, *icE = 0, *icO = 0, *icNE = 0, *icSE = 0, *icSO = 0, *icNO = 0;

    // 1ª Parte: validar se as posições cardeais estão dentro do tabuleiro e se possuem um espaço
    // Se o conteúdo não for um espaço, verificar se é uma inimiga. Se for, registrar -1 na posição
    // Linhas de índice par = todas as coordenadas (N, S, E, O, NE, SE, SO e NO)
    // Linhas de índice ímpar = apenas as coordenadas subcardeais (NE, SE, SO e NO)
    // Jogador 1 verificar se { F, f, c }
    // Jogador 2 verificar se { R, p, g }

    if (peca[x] % 2 == 0) {
        if (N[y] >= LIM_SUPERIOR) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[N[x]][N[y]]) {
                    case ' ': *iN = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iN = -1;
                }
                case 'p':
                switch(matriz_posicao[N[x]][N[y]]) {
                    case ' ': *iN = 1; break;
                    case 'f': 
                    case 'c': *iN = -1; break;
                }
                case 'g':
                switch(matriz_posicao[N[x]][N[y]]) {
                    case ' ': *iN = 1; break;
                    case 'c': *iN = -1; break;
                }
                case 'F':
                switch(matriz_posicao[N[x]][N[y]]) {
                    case ' ': *iN = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iN = -1; break;
                }
                case 'f':
                switch(matriz_posicao[N[x]][N[y]]) {
                    case ' ': *iN = 1; break;
                    case 'p': 
                    case 'g': *iN = -1; break;
                }
                case 'c':
                switch(matriz_posicao[N[x]][N[y]]) {
                    case ' ': *iN = 1; break;
                    case 'g': *iN = -1; break;
                }
            }
        }
        if (S[y] <= LIM_INFERIOR) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[S[x]][S[y]]) {
                    case ' ': *iS = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iS = -1; break;
                }
                case 'p':
                switch(matriz_posicao[S[x]][S[y]]) {
                    case ' ': *iS = 1; break;
                    case 'f': 
                    case 'c': *iS = -1; break;
                }
                case 'g':
                switch(matriz_posicao[S[x]][S[y]]) {
                    case ' ': *iS = 1; break;
                    case 'c': *iS = -1; break;
                }
                case 'F':
                switch(matriz_posicao[S[x]][S[y]]) {
                    case ' ': *iS = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iS = -1; break;
                }
                case 'f':
                switch(matriz_posicao[S[x]][S[y]]) {
                    case ' ': *iS = 1; break;
                    case 'p': 
                    case 'g': *iS = -1; break;
                }
                case 'c':
                switch(matriz_posicao[S[x]][S[y]]) {
                    case ' ': *iS = 1; break;
                    case 'g': *iS = -1; break;
                }
            }
        }
        if (E[x] <= LIM_DIREITO) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[E[x]][E[y]]) {
                    case ' ': *iE = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[E[x]][E[y]]) {
                    case ' ': *iE = 1; break;
                    case 'f': 
                    case 'c': *iE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[E[x]][E[y]]) {
                    case ' ': *iE = 1; break;
                    case 'c': *iE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[E[x]][E[y]]) {
                    case ' ': *iE = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[E[x]][E[y]]) {
                    case ' ': *iE = 1; break;
                    case 'p': 
                    case 'g': *iE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[E[x]][E[y]]) {
                    case ' ': *iE = 1; break;
                    case 'g': *iE = -1; break;
                }
            }
        }
        if (O[x] >= LIM_ESQUERDO) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[O[x]][O[y]]) {
                    case ' ': *iO = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[O[x]][O[y]]) {
                    case ' ': *iO = 1; break;
                    case 'f': 
                    case 'c': *iO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[O[x]][O[y]]) {
                    case ' ': *iO = 1; break;
                    case 'c': *iO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[O[x]][O[y]]) {
                    case ' ': *iO = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[O[x]][O[y]]) {
                    case ' ': *iO = 1; break;
                    case 'p': 
                    case 'g': *iO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[O[x]][O[y]]) {
                    case ' ': *iO = 1; break;
                    case 'g': *iO = -1; break;
                }
            }
        }
        if ((NE[x] <= LIM_DIREITO) && (NE[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iNE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'f': 
                    case 'c': *iNE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'c': *iNE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iNE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'p': 
                    case 'g': *iNE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'g': *iNE = -1; break;
                }
            }
        }
        if ((SE[x] <= LIM_DIREITO) && (SE[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iSE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'f': 
                    case 'c': *iSE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'c': *iSE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iSE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'p': 
                    case 'g': *iSE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'g': *iSE = -1; break;
                }
            }
        }
        if ((SO[x] >= LIM_ESQUERDO) && (SO[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iSO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'f': 
                    case 'c': *iSO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'c': *iSO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iSO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'p': 
                    case 'g': *iSO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'g': *iSO = -1; break;
                }
            }
        }
        if ((NO[x] >= LIM_ESQUERDO) && (NO[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iNO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'f': 
                    case 'c': *iNO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'c': *iNO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iNO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'p': 
                    case 'g': *iNO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'g': *iNO = -1; break;
                }
            }
        }
    } else { // Linha ímpar
        if ((NE[x] <= LIM_DIREITO) && (NE[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iNE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'f': 
                    case 'c': *iNE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'c': *iNE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iNE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'p': 
                    case 'g': *iNE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[NE[x]][NE[y]]) {
                    case ' ': *iNE = 1; break;
                    case 'g': *iNE = -1; break;
                }
            }
        }
        if ((SE[x] <= LIM_DIREITO) && (SE[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iSE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'f': 
                    case 'c': *iSE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'c': *iSE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iSE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'p': 
                    case 'g': *iSE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[SE[x]][SE[y]]) {
                    case ' ': *iSE = 1; break;
                    case 'g': *iSE = -1; break;
                }
            }
        }
        if ((SO[x] >= LIM_ESQUERDO) && (SO[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iSO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'f': 
                    case 'c': *iSO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'c': *iSO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iSO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'p': 
                    case 'g': *iSO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[SO[x]][SO[y]]) {
                    case ' ': *iSO = 1; break;
                    case 'g': *iSO = -1; break;
                }
            }
        }
        if ((NO[x] >= LIM_ESQUERDO) && (NO[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'F':
                    case 'f': 
                    case 'c': *iNO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'f': 
                    case 'c': *iNO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'c': *iNO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'R':
                    case 'p': 
                    case 'g': *iNO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'p': 
                    case 'g': *iNO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[NO[x]][NO[y]]) {
                    case ' ': *iNO = 1; break;
                    case 'g': *iNO = -1; break;
                }
            }
        }
    }

    // 2ª Parte: validar se as posições de captura estão disponíveis, caso sejam necessárias
    // Se registrar -1 em alguma posição cardeal, verificar posição de captura correspondente:
        // Se tiver um espaço, habilitar (true)
        // Se não tiver espaço, desabilitar (false)

    if (peca[x] % 2 == 0) {
        if ((*iN == -1) && (cN[y] >= LIM_SUPERIOR) && (matriz_posicao[cN[x]][cN[y]] == ' ')) *icN = 1;
        if ((*iS == -1) && (cS[y] <= LIM_INFERIOR) && (matriz_posicao[cS[x]][cS[y]] == ' ')) *icS = 1;
        if ((*iE == -1) && (cE[x] <= LIM_DIREITO) && (matriz_posicao[cE[x]][cE[y]] == ' ')) *icE = 1;
        if ((*iO == -1) && (cO[x] >= LIM_ESQUERDO) && (matriz_posicao[cO[x]][cO[y]] == ' ')) *icO = 1;
        if ((*iNE == -1) && (cNE[x] <= LIM_DIREITO) && (cNE[y] >= LIM_SUPERIOR) && (matriz_posicao[cNE[x]][cNE[y]] == ' ')) *icNE = 1;
        if ((*iSE == -1) && (cSE[x] <= LIM_DIREITO) && (cSE[y] <= LIM_INFERIOR) && (matriz_posicao[cSE[x]][cSE[y]] == ' ')) *icSE = 1;
        if ((*iSO == -1) && (cSO[x] >= LIM_ESQUERDO) && (cSO[y] <= LIM_INFERIOR) && (matriz_posicao[cSO[x]][cSO[y]] == ' ')) *icSO = 1;
        if ((*iNO == -1) && (cNO[x] >= LIM_ESQUERDO) && (cNO[y] >= LIM_SUPERIOR) && (matriz_posicao[cNO[x]][cNO[y]] == ' ')) *icNO = 1;
    } else { // Linha ímpar
        if ((*iNE == -1) && (cNE[x] <= LIM_DIREITO) && (cNE[y] >= LIM_SUPERIOR) && (matriz_posicao[cNE[x]][cNE[y]] == ' ')) *icNE = 1;
        if ((*iSE == -1) && (cSE[x] <= LIM_DIREITO) && (cSE[y] <= LIM_INFERIOR) && (matriz_posicao[cSE[x]][cSE[y]] == ' ')) *icSE = 1;
        if ((*iSO == -1) && (cSO[x] >= LIM_ESQUERDO) && (cSO[y] <= LIM_INFERIOR) && (matriz_posicao[cSO[x]][cSO[y]] == ' ')) *icSO = 1;
        if ((*iNO == -1) && (cNO[x] >= LIM_ESQUERDO) && (cNO[y] >= LIM_SUPERIOR) && (matriz_posicao[cNO[x]][cNO[y]] == ' ')) *icNO = 1;
    }

    // Se todas as posições cardeais de movimento e captura forem 0 ou -1, o movimento da peça é impossível
    if ((*iN < 1) && (*iS < 1) && (*iE < 1) && (*iO < 1) && (*iNE < 1) && (*iSE < 1) && (*iSO < 1) && (*iNO < 1)) {
        puts("Essa peca nao pode se mover, tente outra...");
        sleep(2);
        return false;
    } else {        
    return true;
    }
}

void pedir_destino(int dest[]) {
    const int x = 0, y = 1;
    // Pedir as coordenadas de destino para o jogador
    char coord_x_l_dest;
    int coord_x_n_dest, coord_y_dest;

    printf("Digite as coordenadas de destino: (ex C11): ");
    scanf(" %c", &coord_x_l_dest);
    scanf("%d", &coord_y_dest);
    coord_x_l_dest = toupper(coord_x_l_dest);
    switch(coord_x_l_dest) {
        case 'A': coord_x_n_dest = 0; break;
        case 'B': coord_x_n_dest = 1; break;
        case 'C': coord_x_n_dest = 2; break;
        case 'D': coord_x_n_dest = 3; break;
        case 'E': coord_x_n_dest = 4; break;
        case 'F': coord_x_n_dest = 5; break;
        case 'G': coord_x_n_dest = 6; break;
        case 'H': coord_x_n_dest = 7; break;
        case 'I': coord_x_n_dest = 8; break;
        case 'J': coord_x_n_dest = 9; break;
        case 'K': coord_x_n_dest = 10; break;
        default: coord_x_n_dest = 11;
    }
    coord_y_dest -= 1;

    // Vetor com as coordenadas de destino
    dest[x] = coord_x_n_dest;
    dest[y] = coord_y_dest;
}

bool validar_destino(const int peca[], const int dest[], char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], int N[], int S[], int E[], int O[],
    int NE[], int SE[], int SO[], int NO[], int *iN, int *iS, int *iE, int *iO, int *iNE, int *iSE, int *iSO, int *iNO,
    int cN[], int cS[], int cE[], int cO[], int cNE[], int cSE[], int cSO[], int cNO[], int *icN, int *icS, int *icE, int *icO,
    int *icNE, int *icSE, int *icSO, int *icNO, char pecas_jog1[], char pecas_jog2[]) {
    const int x = 0, y = 1;
    // Retornar 0 para destino inválido, 1 para movimento normal, 2 para movimento de captura
    // 1ª parte: validar se o destino está dentro do tabuleiro. Se não estiver, retornar false
    // Princípio Coluna par Linha par / Coluna ímpar linha ímpar

    if ((dest[x] < LIM_ESQUERDO) || (dest[x] > LIM_DIREITO) || (dest[y] < LIM_SUPERIOR) || (dest[y] > LIM_INFERIOR)) {
        puts("Voce escolheu um destino invalido, tente novamente...");
        sleep(2);
        return false;
    }

    if ((dest[x] % 2 == 0) && (dest[y] % 2 == 1)) {
        puts("Voce escolheu um destino invalido, tente novamente...");
        sleep(2);
        return false;
    }

    if ((dest[x] % 2 == 1) && (dest[y] % 2 == 0)) {
        puts("Voce escolheu um destino invalido, tente novamente...");
        sleep(2);
        return false;
    }

    // 2ª Parte: validar se o destino não é igual à pelo menos uma das posições de movimento cardeal
    // Se não for de nenhuma coordenada de movimento cardeal, validar se é alguma coordenada de captura
    // Para ser uma captura válida, a cardeal de movimento == -1 e a cardeal de captura == 1
    // Se for captura válida, chamar a função capturar_peca(<posição movimento cardeal equivalente>)
    if (peca[x] % 2 == 0) {
        if ((((dest[x] == N[x]) && (dest[y] == N[y]) && (*iN == 1)))
        || (((dest[x] == S[x]) && (dest[y] == S[y]) && (*iS == 1)))
        || (((dest[x] == E[x]) && (dest[y] == E[y]) && (*iE == 1)))
        || (((dest[x] == O[x]) && (dest[y] == O[y]) && (*iO == 1)))
        || (((dest[x] == NE[x]) && (dest[y] == NE[y]) && (*iNE == 1)))
        || (((dest[x] == SE[x]) && (dest[y] == SE[y]) && (*iSE == 1)))
        || (((dest[x] == SO[x]) && (dest[y] == SO[y]) && (*iSO == 1)))
        || (((dest[x] == NO[x]) && (dest[y] == NO[y]) && (*iNO == 1)))){
        return true;            
        } else {
            if ((dest[x] == cN[x]) && (dest[y] == cN[y]) && (*iN == -1) && (*icN == 1)) {
                capturar_peca(N, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cS[x]) && (dest[y] == cS[y]) && (*iS == -1) && (*icS == 1)) {
                capturar_peca(S, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cE[x]) && (dest[y] == cE[y]) && (*iE == -1) && (*icE == 1)) {
                capturar_peca(E, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cO[x]) && (dest[y] == cO[y]) && (*iO == -1) && (*icO == 1)) {
                capturar_peca(O, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cNE[x]) && (dest[y] == cNE[y]) && (*iNE == -1) && (*icNE == 1)) {
                capturar_peca(NE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cSE[x]) && (dest[y] == cSE[y]) && (*iSE == -1) && (*icSE == 1)) {
                capturar_peca(SE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cSO[x]) && (dest[y] == cSO[y]) && (*iSO == -1) && (*icSO == 1)) {
                capturar_peca(SO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cNO[x]) && (dest[y] == cNO[y]) && (*iNO == -1) && (*icNO == 1)) {
                capturar_peca(NO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            puts("Destino invalido...");
            sleep(2);
            return false;
        }
    } else { // linha ímpar
        if ((((dest[x] == NE[x]) && (dest[y] == NE[y]) && (*iNE == 1)))
        || (((dest[x] == SE[x]) && (dest[y] == SE[y]) && (*iSE == 1)))
        || (((dest[x] == SO[x]) && (dest[y] == SO[y]) && (*iSO == 1)))
        || (((dest[x] == NO[x]) && (dest[y] == NO[y]) && (*iNO == 1)))) {
            return true;            
        } else {
            if ((dest[x] == cNE[x]) && (dest[y] == cNE[y]) && (*iNE == -1) && (*icNE == 1)) {
                capturar_peca(NE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cSE[x]) && (dest[y] == cSE[y]) && (*iSE == -1) && (*icSE == 1)) {
                capturar_peca(SE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cSO[x]) && (dest[y] == cSO[y]) && (*iSO == -1) && (*icSO == 1)) {
                capturar_peca(SO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == cNO[x]) && (dest[y] == cNO[y]) && (*iNO == -1) && (*icNO == 1)) {
                capturar_peca(NO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            puts("Destino invalido...");
            sleep(2);
            return false;
        }
    }

    // Se não caiu em nenhuma das validações aí em cima...
    puts("Destino estranho... Verificar");
    sleep(2);
    return false;
}

void capturar_peca(int coord_peca_capturada[], char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], char pecas_jog1[], char pecas_jog2[]) {
    const int x = 0, y = 1;
    int i;
    switch(matriz_posicao[coord_peca_capturada[x]][coord_peca_capturada[y]]) {
        case 'R': pecas_jog1[29] = ' '; break;
        case 'p': pecas_jog1[28] = ' '; break;
        case 'g':
            for (i = 0; i < 28;) {
                if (pecas_jog1[i] == 'g') {
                    pecas_jog1[i] = ' ';
                    break;
                } else { ++i; }
            }
        case 'F': pecas_jog2[29] = ' '; break;
        case 'f': pecas_jog2[28] = ' '; break;
        case 'c':
            for (i = 0; i < 28;) {
                if (pecas_jog2[i] == 'c') {
                    pecas_jog2[i] = ' ';
                    break;
                } else { ++i; }
            }
    }
    matriz_posicao[coord_peca_capturada[x]][coord_peca_capturada[y]] = ' ';
}

void fazer_jogada(char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], const int peca[2], const int dest[2]) {
    const int x = 0, y = 1;
    char tmp_move_peca = matriz_posicao[dest[x]][dest[y]];
    matriz_posicao[dest[x]][dest[y]] = matriz_posicao[peca[x]][peca[y]];
    matriz_posicao[peca[x]][peca[y]] = tmp_move_peca;
}

void trocar_turno(int *jog_atual) {
    if (*jog_atual == 1) {
        *jog_atual = 2;
    } else {
        *jog_atual = 1;
    }
}