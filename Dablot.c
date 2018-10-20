// Dablot v 0.2.2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

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
void comeca_jogo(int *, char[*], char[*], bool *);
void imprime_tabuleiro(const char[TAM_X_TAB][TAM_Y_TAB]);
void pede_valida_jogada(char[TAM_X_TAB][TAM_Y_TAB], int *, char[*], char[*]);
void faz_jogada(char[TAM_X_TAB][TAM_Y_TAB], int[*], int [*]);
void troca_turno(int *);
int valida_peca(char pos[TAM_X_TAB][TAM_Y_TAB], int [*], int *, char);


int main(void) {
    // Variáveis gerais de funcionamento
    bool game = false;
    char nome_jogador1[20], nome_jogador2[20];

    // Declaração de vetores peças
    char pecas_jog1[30], pecas_jog2[30];
    // Inicialização dos vetores peças (vetor, nº do jogador)
    inicializa_vetor_pecas(pecas_jog1, 1);
    inicializa_vetor_pecas(pecas_jog2, 2);

    // Matriz de posições disponíveis para as peças
    char matriz_posicao[TAM_X_TAB][TAM_Y_TAB];
    // Colocando as peças na matriz de posições (vetor jogador 1, vetor jogador 2 e matriz posição)
    inicializa_matriz_posicao(pecas_jog1, pecas_jog2, matriz_posicao);

    // Quando o sorteio de quem começa estiver pronto, colocar no lugar do 1 abaixo
    int jog_atual = 1;

    // Chama o menu inicial. Retorna a escolha do jogador
    switch(menu_inicial()) {
        case 'N':
            comeca_jogo(&jog_atual, nome_jogador1, nome_jogador2, &game);
            while (game) {
                imprime_tabuleiro(matriz_posicao);
                
                int peca[2];
                do {
                    pedir_peca(&jog_atual, peca);
                } while (!validar_peca(&jog_atual, peca));


                pede_valida_jogada(matriz_posicao, &jog_atual, nome_jogador1, nome_jogador2);
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

void comeca_jogo(int *jog_atual, char nome_jogador1[], char nome_jogador2[], bool *game) {
    puts("Começando um novo jogo!");
    *game = true;
    puts("Primeiro vamos conhecer os jogadores...");
    puts("Qual o nome do jogador 1, que vai comandar o [R]ei, o [p]ríncipe e os [g]uerreiros?");
    scanf("%s", nome_jogador1);
    puts("E o jogador 2, que vai comandar o [F]azendeiro, seu [f]ilho e os [c]amponeses?");
    scanf("%s", nome_jogador2);
}

void imprime_tabuleiro(const char T[TAM_X_TAB][TAM_Y_TAB]) {
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

void pedir_peca(int *jog_atual, char peca) {
    // coord_x_l = coordenada na forma letra, depois traduzida para forma número
    // x e y apenas para facilitar a escrita
    char coord_x_l;
    int coord_x_n, coord_y;
    const int x = 0, y = 1;

    // Variáveis de controle do while
    int peca_valida = 0;

    // Enquanto a peca escolhida e o destino nao forem validos, solicita novamente para o jogador
    while (!peca_valida) {
        // Pede as coordenadas e troca por algo que a matriz entende
        if (*jog_atual == 1) {
            printf("%s, sua vez!\n", NJ1);
        } else {
            printf("%s, sua vez!\n", NJ2);
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

        // Guarda as coordenadas no vetor
        peca[2] = { coord_x_n, coord_y };
    }
}

bool validar_peca(int *jog_atual, char peca) {
    // Verificar se jogador não digitou uma combinação inválida tipo A2
    // Ou se digitou algo fora da matriz de posição do tabuleiro
    // Princípio Coluna par Linha par / Coluna ímpar linha ímpar
    const int x = 0, y = 1;
    int coord_valida = 0;

    if ((peca[x] >= LIM_ESQUERDO) && (peca[x] <= LIM_DIREITO) && (peca[y] >= LIM_SUPERIOR) && (peca[y] <= LIM_INFERIOR)) {
        if (peca[x] % 2 == 0) {
            if (peca[y] % 2 == 0) {
                coord_valida = 1;
            } else {
                coord_valida = 0;
                puts("Voce escolheu uma combinacao invalida, tente novamente...");
                return false;
            }
        } else {
            if (coord_y % 2 == 1) {
                coord_valida = 1;
            } else {
                coord_valida = 0;
                puts("Voce escolheu uma combinacao invalida, tente novamente...");
                return false;
            }
        }
    } else {
        coord_valida = 0;
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        return false;
    }


}

void pede_valida_jogada(char pos[TAM_X_TAB][TAM_Y_TAB], int *jog_atual, char NJ1[], char NJ2[]) {
/*
    // coord_x_l = coordenada na forma letra, depois traduzida para forma número
    // x e y apenas para facilitar a escrita
    char coord_x_l;
    int coord_x_n, coord_y;
    int x = 0, y = 1;
    
    // Variáveis de controle do while. peca_valida = se a pessoa escolheu uma peça dela que pode se mover, jog_valida = se escolheu um destino válido
    int peca_valida = 0;
    int jog_valida = 0;

    // Enquanto a peca escolhida e o destino nao forem validos, solicita novamente para o jogador
    while ((peca_valida == 0) || (jog_valida == 0)) {
        // Pede as coordenadas, troca por algo que a matriz entende e valida
        if (*jog_atual == 1) {
            printf("%s, sua vez!\n", NJ1);
        } else {
            printf("%s, sua vez!\n", NJ2);
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

        // Criado vetor para guardar as coordenadas da peça escolhida
        int peca[2] = { coord_x_n, coord_y };


        // Verificar se jogador não digitou uma combinação inválida tipo A2
        // Ou se digitou algo fora da matriz de posição do tabuleiro
        // Princípio Coluna par Linha par / Coluna ímpar linha ímpar
        if ((peca[x] >= LIM_ESQUERDO) && (peca[x] <= LIM_DIREITO) && (peca[y] >= LIM_SUPERIOR) && (peca[y] <= LIM_INFERIOR)) {
            if (peca[x] % 2 == 0) {
                if (peca[y] % 2 == 0) {
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
*/
        // Verifica as peças { R, p, g } ou { F, f, c } dependendo se é o jogador 1 ou 2
        // Se tiver um espaço, pede outra coordenada

        // *** ACHO QUE DA PRA REMOVER ESSE PRIMEIRO IF PORQUE USA CONTINUE EM CIMA ***
        if (peca_valida == 1) {
            peca_valida = valida_peca(pos, peca, jog_atual, 'M');
            if (peca_valida == 0){
                continue;
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
            // Caso encontre um adversário, verifica se a posição de captura está disponível

            // Biblioteca de posições de captura
            int cN[2] = { coord_x_n, (coord_y - 4) };
            int cS[2] = { coord_x_n, (coord_y + 4) };
            int cE[2] = { (coord_x_n + 4), coord_y };
            int cO[2] = { (coord_x_n - 4), coord_y };
            int cNE[2] = { (coord_x_n + 2), (coord_y - 2) };
            int cSE[2] = { (coord_x_n + 2), (coord_y + 2) };
            int cSO[2] = { (coord_x_n - 2), (coord_y + 2) };
            int cNO[2] = { (coord_x_n - 2), (coord_y - 2) };

            // Código abaixo vai virar a função valida_alcance
            // Deve ser atualizada para a situação onde a peça está cercada de adversários mas pode eliminar pelo menos um deles
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

            // Vetor com as coordenadas de destino
            int dest[2] = { coord_x_n_dest, coord_y_dest };

            // Verificando se as coordenadas de destino estão dentro do tabuleiro
            // Usa também a validação linha-coluna par, linha-coluna ímpar
            if ((dest[x] >= LIM_ESQUERDO) && (dest[x] <= LIM_DIREITO) && (dest[y] >= LIM_SUPERIOR) && (dest[y] <= LIM_INFERIOR)) {
                if (dest[x] % 2 == 0) {
                    if (dest[y] % 2 == 0) {
                        jog_valida = 1;
                    } else {
                        jog_valida = 0;
                        puts("Voce escolheu um destino invalido, tente novamente...");
                    }
                } else {
                    if (dest[y] % 2 == 1) {
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
            // Se não for nenhum do alcance normal de movimento, verifica se é do alcance de captura

            if (jog_valida == 1) {
                if (peca[y] % 2 == 0) { // Linha índice par
                    if ((dest[x] == N[x]) && (dest[y] == N[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == S[x]) && (dest[y] == S[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == E[x]) && (dest[y] == E[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == O[x]) && (dest[y] == O[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == NE[x]) && (dest[y] == NE[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == SE[x]) && (dest[y] == SE[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == SO[x]) && (dest[y] == SO[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == NO[x]) && (dest[y] == NO[y])) {
                        jog_valida = 1;
                    } else {
                        jog_valida = 0;
                        puts("Essa coordenada estah fora do alcance da sua peca...");
                        continue;
                    }
                } else { // Linha índice ímpar
                    if ((dest[x] == NE[x]) && (dest[y] == NE[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == SE[x]) && (dest[y] == SE[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == SO[x]) && (dest[y] == SO[y])) {
                        jog_valida = 1;
                    } else if ((dest[x] == NO[x]) && (dest[y] == NO[y])) {
                        jog_valida = 1;
                    } else {
                        jog_valida = 0;
                        puts("Essa coordenada estah fora do alcance da sua peca...");
                        continue;
                    }
                }
            }
            
            // Verificando se nessa coordenada tem um espaço
            if (jog_valida == 1) {
                if (pos[dest[x]][dest[y]] == ' ') {
                    faz_jogada(pos, peca, dest);
                    troca_turno(jog_atual);
                } else {
                    jog_valida = 0;
                    puts("Essa casa nao esta disponivel, tente outra...");
                    continue;
                }
            }
        }
    }
}

void faz_jogada(char pos[TAM_X_TAB][TAM_Y_TAB], int coord_peca[2], int coord_destino[2]) {
    int x = 0, y = 1;
    char tmp_move_peca = pos[coord_destino[x]][coord_destino[y]];
    pos[coord_destino[x]][coord_destino[y]] = pos[coord_peca[x]][coord_peca[y]];
    pos[coord_peca[x]][coord_peca[y]] = tmp_move_peca;
    imprime_tabuleiro(pos);
}

void troca_turno(int *jog_atual) {
    if (*jog_atual == 1) {
        *jog_atual = 2;
    } else {
        *jog_atual = 1;
    }
}

int valida_peca(char pos[TAM_X_TAB][TAM_Y_TAB], int coord[2], int *jog_atual, char time_peca) {
    int x = 0, y = 1;
    // Recebe a matriz posição, as coordenadas de destino, o jogador atual e um identificador da peça
    // char time_peca: 'M' = peça do Meu time, 'O' = peça do Outro time
    // Verifica peças { R, p, g } ou { F, f, c } dependendo se jogador 1 ou 2
    // Se tiver um espaço, pede outra coordenada

    if (*jog_atual == 1) {
        if (time_peca == 'M') {
            if ((pos[coord[x]][coord[y]] == 'R') || (pos[coord[x]][coord[y]] == 'p') || (pos[coord[x]][coord[y]] == 'g')) {
                return 1;
            } else if (pos[coord[x]][coord[y]] == ' ') {
                puts("Esse espaco estah vazio...");
                return 0;
            } else {        
                puts("Voce escolheu uma peca do adversario...");
                return 0;
            }
        } else { // Jogador 1 e Outro time
            if ((pos[coord[x]][coord[y]] == 'F') || (pos[coord[x]][coord[y]] == 'f') || (pos[coord[x]][coord[y]] == 'c')) {
                return 1;
            } else if (pos[coord[x]][coord[y]] == ' ') {
                puts("Esse espaco estah vazio...");
                return 0;
            } else {
                puts("Voce escolheu uma peca do adversario...");
                return 0;
            }
        }
    } else { // Jogador 2
        if (time_peca == 'M') {
            if ((pos[coord[x]][coord[y]] == 'F') || (pos[coord[x]][coord[y]] == 'f') || (pos[coord[x]][coord[y]] == 'c')) {
                return 1;
            } else if (pos[coord[x]][coord[y]] == ' ') {
                puts("Esse espaco estah vazio...");
                return 0;
            } else {
                puts("Voce escolheu uma peca do adversario...");
                return 0;
            }
        } else { // Jogador 2 e Outro time
            if ((pos[coord[x]][coord[y]] == 'R') || (pos[coord[x]][coord[y]] == 'p') || (pos[coord[x]][coord[y]] == 'g')) {
                return 1;
            } else if (pos[coord[x]][coord[y]] == ' ') {
                puts("Esse espaco estah vazio...");
                return 0;
            } else {        
                puts("Voce escolheu uma peca do adversario...");
                return 0;
            }
        }
    }
}
