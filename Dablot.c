// Dablot v 0.2.2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define TAM_X_TAB 11
#define TAM_Y_TAB 13
#define TAM_VETOR 30
#define LIM_SUPERIOR 0
#define LIM_INFERIOR 12
#define LIM_ESQUERDO 0
#define LIM_DIREITO 10

char menu_inicial(void);
void inicializa_vetor_pecas(char[*], int);
void inicializa_matriz_posicao(char[TAM_VETOR], char[TAM_VETOR], char[TAM_X_TAB][TAM_Y_TAB]);
void imprime_tabuleiro(const char[TAM_X_TAB][TAM_Y_TAB]);
int pede_valida_jogada(char[TAM_X_TAB][TAM_Y_TAB], int, char[*], char[*]);
int faz_jogada(char[TAM_X_TAB][TAM_Y_TAB], int[*], int[*]);

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
        case 'N':
            puts("Começando um novo jogo!");
            puts("Primeiro vamos conhecer os jogadores...");
            char nome_jogador1[20], nome_jogador2[20];
            puts("Qual o nome do jogador 1, que vai comandar o [R]ei, o [p]ríncipe e os [g]uerreiros?");
            scanf("%s", nome_jogador1);
            puts("E o jogador 2, que vai comandar o [F]azendeiro, seu [f]ilho e os [c]amponeses?");
            scanf("%s", nome_jogador2);
            imprime_tabuleiro(matriz_posicao);

            // Vai repetir até o que o jogador informe uma jogada válida
            int fazer_jogada = 0;
            while (fazer_jogada == 0) {
                // Quando o sorteio de quem começa estiver pronto, colocar no lugar do 1 abaixo
                fazer_jogada = pede_valida_jogada(matriz_posicao, 1, nome_jogador1, nome_jogador2);
            }

            if (fazer_jogada) {
                puts("A jogada será realizada...");

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
    
    // Limpa a tela e printa o cabeçalho
    system("clear");
    puts("     A  B  C  D  E  F  G  H  I  J  K ");
    
    // Para cada linha, se o índice da linha for par ou ímpar, acontece algo diferente
    for (y = 0; y < TAM_Y_TAB; y++) {
        if (y % 2 == 0) {
            // Linha índice par (y = 0, linha = 1)
            // Imprime as coordenadas numerais da borda esquerda
            if (y < 10) {
                printf(" %d  [", y+1);
            } else {
                printf(" %d [", y+1);
            }
            // Imprime ou uma peça ou um separador
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

int pede_valida_jogada(char pos[TAM_X_TAB][TAM_Y_TAB], int jog_atual, char J1[], char J2[]) {
    
    // *** CRIAR VETOR PECA[X][Y] E DEST[X][Y] E SUBSTITUIR TUDO NA FUNÇÃO ***

    // coord_x - l = letra, n = número)
    char coord_x_l;
    int coord_x_n, coord_y;
    // Variáveis de controle do while. peca_valida = se a pessoa escolheu uma peça dela que pode se mover, jog_valida = se escolheu um destino válido
    int peca_valida = 0;
    int jog_valida = 0;

    // Enquanto a peca escolhida e o destino nao forem validos, solicita novamente para o jogador
    while ((peca_valida != 1) && (jog_valida != 1)) {
        // Pede as coordenadas, troca por algo que a matriz entende e valida
        if (jog_atual == 1) {
            printf("%s, sua vez!\n", J1);
        } else {
            printf("%s, sua vez!\n", J2);
        }
        printf("Digite a coordenada alfabética (eixo X) da peça que você quer mover: ");
        scanf(" %c", &coord_x_l);
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
        printf("Digite a coordenada numérica (eixo Y) da peça que você quer mover: ");
        scanf("%d", &coord_y);
        coord_y -= 1;

        // Verificar se jogador não digitou uma combinação inválida tipo A2
        // Ou se digitou algo fora da matriz de posição do tabuleiro
        // Princípio Coluna par Linha par / Coluna ímpar linha ímpar
        if ((coord_x_n >= LIM_ESQUERDO) && (coord_x_n <= LIM_DIREITO) && (coord_y >= LIM_SUPERIOR) && (coord_y <= LIM_INFERIOR)) {
            if (coord_x_n % 2 == 0) {
                if (coord_y % 2 == 0) {
                    peca_valida = 1;
                } else {
                    peca_valida = 0;
                    puts("Voce escolheu uma combinacao invalida, tente novamente...");
                    continue;
                }
            } else {
                if (coord_y % 2 == 1) {
                    peca_valida = 1;
                } else {
                    peca_valida = 0;
                    puts("Voce escolheu uma combinacao invalida, tente novamente...");
                    continue;
                }
            }
        } else {
            peca_valida = 0;
            puts("Voce escolheu uma combinacao invalida, tente novamente...");
            continue;
        }

        // Verifica as peças { R, p, g } ou { F, f, c } dependendo se é o jogador 1 ou 2
        // Se tiver um espaço, pede outra coordenada
        if (peca_valida == 1) {
            if (jog_atual == 1) {
                if ((pos[coord_x_n][coord_y] == 'R') || (pos[coord_x_n][coord_y] == 'p') || (pos[coord_x_n][coord_y] == 'g')) {
                    peca_valida = 1;
                } else if (pos[coord_x_n][coord_y] == ' ') {
                    peca_valida = 0;
                    printf("Esse espaco estah vazio...\n");
                    continue;
                } else {
                    peca_valida = 0;
                    printf("Voce escolheu uma peca do adversario...\n");
                    continue;
                }
            } else if (jog_atual == 2) {
                if ((pos[coord_x_n][coord_y] == 'F') || (pos[coord_x_n][coord_y] == 'f') || (pos[coord_x_n][coord_y] == 'c')) {
                    peca_valida = 1;
                } else if (pos[coord_x_n][coord_y] == ' ') {
                    peca_valida = 0;
                    printf("Esse espaco estah vazio...\n");
                    continue;
                } else {
                    peca_valida = 0;
                    printf("Voce escolheu uma peca do adversario...\n");
                    continue;
                }
            }
            // Pesquisando a matriz em volta da peça, se todas as posições tiverem uma letra, a peça está sem movimentos
            // Na diagonal (variando eixo x e y ao mesmo tempo), apenas uma casa 
            // Pedir pro jogador escolher outra peça caso não encontre nenhum ' '
            // Se o resultado da pesquisa achar pelo um ' ', a jogada é válida.
            // As peças próximas às bordas precisam de validação diferente para não sair da matriz

            // Conjunto de coordenadas cardeais
            const int x = 0, y = 1;
            int N[2] = { coord_x_n, (coord_y - 2) };
            int S[2] = { coord_x_n, (coord_y + 2) };
            int E[2] = { (coord_x_n + 2), coord_y };
            int O[2] = { (coord_x_n - 2), coord_y };
            int NE[2] = { (coord_x_n + 1), (coord_y - 1) };
            int SE[2] = { (coord_x_n + 1), (coord_y + 1) };
            int SO[2] = { (coord_x_n - 1), (coord_y + 1) };
            int NO[2] = { (coord_x_n - 1), (coord_y - 1) };

            // Verifica em cada coordenada cardeal se está dentro do tabuleiro e se tem espaço disponível
            // Linhas de índice par = todas as coordenadas
            // Linhas de índice ímpar = apenas as coordenadas subcardeais NE, SE, SO e NO
            if (coord_x_n % 2 == 0) {
                if ((N[y] >= LIM_SUPERIOR) && (pos[N[x]][N[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((S[y] <= LIM_INFERIOR) && (pos[S[x]][S[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((E[x] <= LIM_DIREITO) && (pos[E[x]][E[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((O[x] >= LIM_ESQUERDO) && (pos[O[x]][O[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((NE[x] <= LIM_DIREITO) && (NE[y] >= LIM_SUPERIOR) && (pos[NE[x]][NE[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((SE[x] <= LIM_DIREITO) && (SE[y] <= LIM_INFERIOR) && (pos[SE[x]][SE[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((SO[x] >= LIM_ESQUERDO) && (SO[y] <= LIM_INFERIOR) && (pos[SO[x]][SO[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((NO[x] >= LIM_ESQUERDO) && (NO[y] >= LIM_SUPERIOR) && (pos[NO[x]][NO[y]] == ' ')) {
                    peca_valida = 1;
                } else {
                    peca_valida = 0;
                    puts("Essa peca nao pode se mover, tente outra...");
                    continue;
                }
            } else {
                if ((NE[x] <= LIM_DIREITO) && (NE[y] >= LIM_SUPERIOR) && (pos[NE[x]][NE[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((SE[x] <= LIM_DIREITO) && (SE[y] <= LIM_INFERIOR) && (pos[SE[x]][SE[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((SO[x] >= LIM_ESQUERDO) && (SO[y] <= LIM_INFERIOR) && (pos[SO[x]][SO[y]] == ' ')) {
                    peca_valida = 1;
                } else if ((NO[x] >= LIM_ESQUERDO) && (NO[y] >= LIM_SUPERIOR) && (pos[NO[x]][NO[y]] == ' ')) {
                    peca_valida = 1;
                } else {
                    peca_valida = 0;
                    puts("Essa peca nao pode se mover, tente outra...");
                    continue;
                }
            }

            // Pede as coordenadas de destino para o jogador
            char coord_x_l_dest;
            int coord_x_n_dest, coord_y_dest;

            printf("Para qual coordenada alfabética (eixo X) você quer move-la? ");
            scanf(" %c", &coord_x_l_dest);
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
            printf("Para qual coordenada numérica (eixo Y) você quer move-la? ");
            scanf("%d", &coord_y_dest);
            coord_y_dest -= 1;

            // Verificando se as coordenadas de destino estão dentro do tabuleiro

            if ((coord_x_n_dest >= LIM_ESQUERDO) && (coord_x_n_dest <= LIM_DIREITO) && (coord_y_dest >= LIM_SUPERIOR) && (coord_y_dest <= LIM_INFERIOR)) {
                if (coord_x_n_dest % 2 == 0) {
                    if (coord_y_dest % 2 == 0) {
                        jog_valida = 1;
                    } else {
                        jog_valida = 0;
                        puts("Voce escolheu um destino invalido, tente novamente...");
                    }
                } else {
                    if (coord_y_dest % 2 == 1) {
                        jog_valida = 1;
                    } else {
                        jog_valida = 0;
                        puts("Voce escolheu um destino invalido, tente novamente...");
                        continue;
                    }
                }
            } else {
                jog_valida = 0;
                puts("Voce escolheu um destino invalido, tente novamente...");
                continue;
            }

            // Verifica se as coordenadas de destino estão no alcance da peça
            if (jog_valida == 1) {
                if (((coord_x_n_dest == N[x]) || (coord_x_n_dest == S[x]) || (coord_x_n_dest == E[x]) || (coord_x_n_dest == O[x]) 
                    || (coord_x_n_dest == NE[x]) || (coord_x_n_dest == SE[x]) || (coord_x_n_dest == SO[x]) || (coord_x_n_dest == NE[x]))
                    && ((coord_y_dest == N[y]) || (coord_y_dest == S[y]) || (coord_y_dest == E[y]) || (coord_y_dest == O[y]) 
                    || (coord_y_dest == NE[y]) || (coord_y_dest == SE[y]) || (coord_y_dest == SO[y]) || (coord_y_dest == NE[y]))) {
                    jog_valida = 1;
                } else {
                    jog_valida = 0;
                    puts("Essa coordenada estah fora do alcance da sua peca...");
                    continue;
                }
            }
            
            // Verificando se nessa coordenada tem um espaço
            if (jog_valida == 1) {
                if (pos[coord_x_n_dest][coord_y_dest] == ' '){
                    jog_valida = 1;
                    int peca[2], dest[2];
                    peca[0] = coord_x_n;
                    peca[1] = coord_y;
                    dest[0] = coord_x_n_dest;
                    dest[1] = coord_y_dest;
                    faz_jogada(pos, peca, dest);
                    return jog_valida;
                } else {
                    jog_valida = 0;
                    puts("Essa casa nao esta disponivel, tente outra...");
                    return jog_valida;
                }
            }
        }
    }   
    return 0;
}

int faz_jogada(char pos[TAM_X_TAB][TAM_Y_TAB], int coord_peca[2], int coord_destino[2]) {
    int x = 0, y = 1;
    char tmp_move_peca = pos[coord_destino[x]][coord_destino[y]];
    pos[coord_destino[x]][coord_destino[y]] = pos[coord_peca[x]][coord_peca[y]];
    pos[coord_peca[x]][coord_peca[y]] = tmp_move_peca;
    imprime_tabuleiro(pos);
    return 0;
}