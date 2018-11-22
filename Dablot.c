/*

*** --- Dablot v0.8
*** Universidade Tuiuti do Parana
*** Programação Estruturada 
*** Professor: Douglas Koerich
*** Aluno: Cleberson Pertile

*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "pontoCardeal.h"

#define TAM_X_TAB 11
#define TAM_Y_TAB 13
#define TAM_VETOR 30
#define TAM_NOME 30
#define LIM_SUPERIOR 0
#define LIM_INFERIOR 12
#define LIM_ESQUERDO 0
#define LIM_DIREITO 10

#define AMRL "\x1B[33m"
#define AZUL "\x1B[34m"
#define BNCO "\x1B[37m"
#define CIAN "\x1B[96m"
#define CNZA "\x1B[90m"
#define MGNT "\x1B[95m" 
#define VERD "\x1B[32m"
#define VRML "\x1B[91m"
#define RST  "\x1B[0m"

bool validar_alcance(const int[*], size_t, size_t, const char[*][*], pontoCardeal*, pontoCardeal*);
bool validar_destino(const int[*], const int[*], size_t, size_t, char[*][*], pontoCardeal, pontoCardeal, char[*], char[*]);
bool validar_peca(const int*, const int[*], size_t, size_t, const char[*][*]);
bool verificar_desistencia(int, char[*], char[*], size_t, char[*], char[*], size_t);
bool verificar_pecas_livres(size_t, size_t, char[*][*], const int*, int[*], pontoCardeal*, pontoCardeal*);
char menu_inicial(void);
char menu_pausa(void);
int carregar_jogo(size_t, size_t, char[*][*], char[*], char[*], char[*], char[*], int*, bool*);
int pedir_entrada(const int*, int[*], char[*], char[*]);
int salvar_jogo(size_t, size_t, char[*][*], char[*], char[*], char[*], char[*], int*);
int sortear_jogador(void);
int verificar_vetor_pecas(char[*], char[*], size_t, int*);
void capturar_peca(int[*], size_t, size_t, char[*][*], size_t, char[*], char[*]);
void comecar_jogo(char[*], char[*], bool*);
void fazer_jogada(size_t, size_t, char[*][*], const int[*], const int[*]);
void imprimir_tabuleiro(size_t, size_t, const char[*][*]);
void inicializar_matriz_posicao(char[*], char[*], size_t, size_t, size_t, char[*][*]);
void inicializar_vetor_pecas(char[*], char[*], size_t);
void pedir_destino(int[*]);
void reiniciar_partida(size_t, size_t, char[*][*], char[*], char[*], size_t);
void trocar_turno(int*);
void tutorial(void);

int main(void) {
    // Variáveis gerais de funcionamento
    bool game = false;
    char matriz_posicao[TAM_X_TAB][TAM_Y_TAB];
    char nome_jogador1[TAM_NOME], nome_jogador2[TAM_NOME];
    char pecas_jog1[TAM_VETOR], pecas_jog2[TAM_VETOR];
    int jog_atual = 0;
    int peca[2], dest[2];

    // Posições cardeais de movimento e captura
    pontoCardeal movimento;
    pontoCardeal captura;

    // Inicialização dos vetores peças
    inicializar_vetor_pecas(pecas_jog1, pecas_jog2, TAM_VETOR);

    // Inicialização da matriz de posições
    inicializar_matriz_posicao(pecas_jog1, pecas_jog2, TAM_VETOR, TAM_X_TAB, TAM_Y_TAB, matriz_posicao);
    
    // Chamada do menu inicial para início do jogo
    char escolha = menu_inicial();
    switch(escolha) {
        case 'A': tutorial(); escolha = 'N';
        case 'C':
        case 'N':
            if (escolha == 'C') {
                carregar_jogo(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, nome_jogador1, pecas_jog1, nome_jogador2, pecas_jog2, &jog_atual, &game);
            } else {
                comecar_jogo(nome_jogador1, nome_jogador2, &game);
                jog_atual = sortear_jogador();
            }
            while (game) {
                imprimir_tabuleiro(TAM_X_TAB, TAM_Y_TAB, matriz_posicao);

                if (!verificar_vetor_pecas(pecas_jog1, pecas_jog2, TAM_VETOR, &jog_atual)) {
                    if (jog_atual == 1) {
                        printf(VRML "%s" CNZA ", todas as suas pecas foram eliminadas! Voce perdeu...\n", nome_jogador1);
                        printf(VERD "%s" CNZA " ganhou essa partida!\n", nome_jogador2);
                    } else {
                        printf(VERD "%s" CNZA ", todas as suas pecas foram eliminadas! Voce perdeu...\n", nome_jogador2);
                        printf(VRML "%s" CNZA " ganhou essa partida!\n", nome_jogador1);
                    }
                    sleep(2);
                    game = false; break;
                }

                if (!verificar_pecas_livres(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, &jog_atual, peca, &movimento, &captura)) {
                    if (jog_atual == 1) {
                        printf(VRML "%s" CNZA ", suas pecas estao todas sem movimento! Voce perdeu...\n", nome_jogador1);
                        printf(VERD "%s" CNZA " ganhou essa partida!\n", nome_jogador2);
                    } else {
                        printf(VERD "%s" CNZA ", suas pecas estao todas sem movimento! Voce perdeu...\n", nome_jogador2);
                        printf(VRML "%s" CNZA " ganhou essa partida!\n", nome_jogador1);
                    }
                    sleep(2);
                    game = false; break;
                }

                if (verificar_desistencia(jog_atual, nome_jogador1, nome_jogador2, TAM_NOME, pecas_jog1, pecas_jog2, TAM_VETOR)) {
                    puts("Por desistência, jogo encerrado...");
                    game = false; break;
                }

                if (!pedir_entrada(&jog_atual, peca, nome_jogador1, nome_jogador2)) {
                    switch(menu_pausa()) {
                        case 'V': continue;
                        case 'C': carregar_jogo(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, nome_jogador1, pecas_jog1, nome_jogador2, pecas_jog2, &jog_atual, &game); continue;
                        case 'S': salvar_jogo(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, nome_jogador1, pecas_jog1, nome_jogador2, pecas_jog2, &jog_atual); continue;
                        case 'R': reiniciar_partida(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, pecas_jog1, pecas_jog2, TAM_VETOR); jog_atual = sortear_jogador(); continue;
                        case 'X': reiniciar_partida(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, pecas_jog1, pecas_jog2, TAM_VETOR); jog_atual = sortear_jogador();
                        comecar_jogo(nome_jogador1, nome_jogador2, &game); continue;
                        case '0': game = false; continue;
                    }
                }

                if (!validar_peca(&jog_atual, peca, TAM_X_TAB, TAM_Y_TAB, matriz_posicao)) continue;

                if (!validar_alcance(peca, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, &movimento, &captura)) {
                    puts("Essa peca nao pode se mover, tente outra...");
                    sleep(2);
                    continue;
                }

                pedir_destino(dest);
                if (!validar_destino(peca, dest, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, movimento, captura, pecas_jog1, pecas_jog2)) continue;
                fazer_jogada(TAM_X_TAB, TAM_Y_TAB, matriz_posicao, peca, dest);
                trocar_turno(&jog_atual);
            }
        case 'S': puts("Saindo do jogo... Obrigado por jogar Dablot :) ");
        sleep(3);
    }
    return EXIT_SUCCESS;
}

void tutorial(void) {
    // Explicar o que é o Dablot, mostrar o tabuleiro e explicar como jogar
    system("clear");
    printf(CNZA "Bem-vindo ao Dablot, um jogo de tabuleiro do sec XIX cuja história se passa\n"
                "no Extremo Norte da Suecia entre o Rei Sami, seu principe e seus guerreiros\n"
                "contra o Fazendeiro, seu filho e os camponeses...\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "A mecanica do Dablot eh similar ao jogo Damas, onde as pecas se movimentam\n"
                "uma 'casa' por vez, e capturam as pecas adversarias saltando por cima delas.\n");
    sleep(6);
    printf("  @╔═════════════════════════════════════════╗\n"
           "  @║     A  B  C  D  E  F  G  H  I  J  K     ║\n"
           "  @║  1 [g]---[g]---[g]---[g]---[g]---[g] 1  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  2  | [g] | [g] | [g] | [g] | [g] |  2  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  3 [g]---[g]---[g]---[g]---[g]---[g] 3  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  4  | [g] | [g] | [g] | [g] | [g] |  4  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  5 [g]---[g]---[g]---[g]---[g]---[g] 5  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  6  | [p] | [ ] | [ ] | [ ] | [ ] |  6  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  7 [R]---[ ]---[ ]---[ ]---[ ]---[F] 7  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  8  | [ ] | [ ] | [ ] | [ ] | [f] |  8  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  9 [c]---[c]---[c]---[c]---[c]---[c] 9  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║ 10  | [c] | [c] | [c] | [c] | [c] |  10 ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║ 11 [c]---[c]---[c]---[c]---[c]---[c] 11 ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║ 12  | [c] | [c] | [c] | [c] | [c] |  12 ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║ 13 [c]---[c]---[c]---[c]---[c]---[c] 13 ║\n"
           "  @║     A  B  C  D  E  F  G  H  I  J  K     ║\n"
           "  @╚═════════════════════════════════════════╝\n");
    printf(CNZA "Este eh o tabuleiro do Dablot. Nele, as pecas se movimentam\n"
                "usando os espacos [ ] como casa. Cada peca pode andar 1 casa\n"
                "para qualquer direcao, as vezes tendo 4 e as vezes 8 direcoes\n"
                "possiveis para se locomover...\n");
    sleep(10);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Cada jogador tem um movimento por vez. A cada rodada,\n"
                "o computador pergunta as coordenadas da peca que o jogador\n"
                "deseja mover, e depois pergunta o destino.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "O jogador deve inserir as coordenadas como aparecem na tela:\n"
                "'A7', ou 'a7', sao coordenadas validas para uma peca.\n"
                "'B8' ou 'b8' eh um destino valido para essa peca.\n");
    sleep(6);
    printf(CNZA "A peca ira se mover pelo tabuleiro dessa maneira:\n"
                "@╔═════════════════════════════════════════╗\n"
                "@║     A  B  C                 A  B  C     ║\n"
                "@║  7 [R]---[ ]   ->    @║  7 [ ]---[ ]    ║\n"
                "@║     | \\ / |    ->    @║     | \\ / |     ║\n"
                "@║  8  | [ ] |    ->    @║  8  | [R] |     ║\n"
                "@║     | / \\ |    ->    @║     | / \\ |     ║\n"
                "@║  9 [c]---[c]   ->    @║  9 [c]---[c]    ║\n"
                "@║     A  B  C                 A  B  C     ║\n"
                "@╚═════════════════════════════════════════╝\n");
    sleep(10);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Para capturar uma peca do adversario, o destino informado\n"
                "deve ser uma coordenada que faca a peca dar um 'salto' sobre\n"
                "a peca adversario, como no jogo de Damas.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "As pecas possuem niveis diferentes, sendo que so podem\n"
                "capturar pecas de nivel igual ou inferior:\n"
                "- O Rei e o Fazendeiro tem nivel 3, o que significa que\n"
                "podem eliminar qualquer peca do time adversario.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "-O filho do fazendeiro e o principe sao nivel 2,\n"
                "enquanto os camponeses e guerreiros sao nivel 1...\n");
    sleep(4);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Ganha o jogador que:\n"
                "-Eliminar todas as pecas do adversario.\n"
                "-Trancar todas as pecas do adversario.\n");
    sleep(4);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Além disso, caso a peca mais significativa de um jogador seja eliminada,\n"
                "ele tera a opcao de desistir ou continuar jogando.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    char escolha = '?';
    while (escolha != 'N') {
        printf(CNZA "E ai, vamos jogar? Quando terminar de ler a explicacao,\n"
                    "eh soh digitar 'N' para comecar um Novo Jogo :)\n");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
    }
    system("clear");
}

bool verificar_desistencia(int jog_atual, char nome_jogador1[], char nome_jogador2[], size_t tam_nome,
    char pecas_jog1[], char pecas_jog2[], size_t tam_vetor_pecas) {
    // Verificar nos vetores peças se o jogador perdeu sua peça mais significativa ('R' ou 'F') e perguntar se deseja desistir do jogo
    // Se for jogador 1, vai olhar para o vetor de peças 1 na posição do 'R'
    // Jogador 2, olha o vetor de peças 2 na posição do 'F'
    char escolha = '?';

    if (jog_atual == 1) {
        if (pecas_jog1[tam_vetor_pecas - 1] != 'R') {
            while ((escolha != 'S') && (escolha != 'N')) {
                printf(VRML "%s" CNZA ", o Rei foi eliminado... Deseja desistir do jogo? (S) / (N) ", nome_jogador1);
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                switch (escolha) {
                    case 'S': return true;
                    case 'N': return false;
                    default: continue;
                }
            }
        }
    } else {
        if (pecas_jog2[tam_vetor_pecas - 1] != 'F') {
            while ((escolha != 'S') && (escolha != 'N')) {
                printf(VERD "%s" CNZA ", o Fazendeiro foi eliminado... Deseja desistir do jogo? (S) / (N) ", nome_jogador2);
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                switch (escolha) {
                    case 'S': return true;
                    case 'N': return false;
                    default: continue;
                }
            }
        }
    }
    return false;

}

bool verificar_pecas_livres(size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], const int *jog_atual, int peca[], pontoCardeal *movimento, pontoCardeal *captura) {
    // Rodar a função validar_alcance() num loop para todas as peças do jogador atual na matriz
    // Caso validar_alcance() retorne verdadeiro, sair do laço e retornar verdadeiro
    // Caso validar_alcance() retorne falso, continuar verificando até chegar na última peça
    // Caso a última também retorne falso, todas as peças estão bloqueadas, retornar falso, esse jogador perdeu o jogo
    int x, y;
    const int X = 0;
    const int Y = 1;

    for (y = 0; y < tam_y; ++y) {
        for (x = 0; x < tam_x; ++x) {
            if (*jog_atual == 1) {
                switch(matriz_posicao[x][y]) {
                    case 'R': case 'p': case 'g':
                    peca[X] = x;
                    peca[Y] = y;
                    if (validar_alcance(peca, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, movimento, captura)) {
                        return true;
                    }
                }
            } else {
                switch(matriz_posicao[x][y]) {
                    case 'F': case 'f': case 'c':
                    peca[X] = x;
                    peca[Y] = y;
                    if (validar_alcance(peca, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, movimento, captura)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int sortear_jogador(void) {
    srand(time(0));
    int sorteio = rand() % 2 + 1;
    puts(CNZA "Vamos sortear quem vai comecar jogando...");
    sleep(3);
    printf("O jogador %d foi sorteado para comecar dessa vez...\n", sorteio);
    sleep(2);
    return sorteio;
}

char menu_inicial(void) {
    char escolha = '?';

    // Limpa a tela e imprime o menu inicial do jogo
    system("clear");
    putchar('\n');
    puts(CNZA "   ╔══════════════════════════════╗");
    puts(CNZA "   ║" RST " Bem-vindo(a) ao jogo Dablot!" CNZA " ║");
    puts(CNZA "   ╚══════════════════════════════╝");
    putchar('\n');
    while (escolha == '?') {
        puts(CNZA " ╔══════════════════════════════════╗");
        puts(CNZA " ║" RST " Digite (A) para Aprender a jogar " CNZA "║");
        puts(CNZA " ║" RST "      Digite (I) para Iniciar     " CNZA "║");
        puts(CNZA " ║" RST "       Digite (S) para Sair       " CNZA "║");
        puts(CNZA " ╚══════════════════════════════════╝");
        putchar('\n');
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        switch(escolha) {
            case 'A': return escolha;
            case 'I':
                puts(CNZA " ╔═════════════════════════════════════════════════════╗");
                puts(CNZA " ║" RST " Deseja um Novo Jogo (N) ou Carregar Jogo Salvo (C)? " CNZA "║");
                puts(CNZA " ╚═════════════════════════════════════════════════════╝");
                putchar('\n');
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                switch(escolha) {
                    case 'N': return escolha;
                    case 'C': return escolha;
                    default: escolha = '?'; continue;
                }
            case 'S': return escolha;
            default: escolha = '?'; continue;
        }
    }
    return escolha;
}

char menu_pausa(void) {
    char escolha = '?';
    while (escolha == '?') {
        system("clear");
        puts(CNZA "                  ╔════════════════╗");
        puts(CNZA "                  ║" RST "  JOGO PAUSADO  " CNZA "║");
        puts(CNZA "                  ╚════════════════╝");
        puts(CNZA "  ╔═════════════════════════════════════════════════╗");
        puts(CNZA "  ║" RST "  (R) Reiniciar partida com os mesmos jogadores  " CNZA "║");
        puts(CNZA "  ║" RST "  (S) Salvar jogo para continuar depois          " CNZA "║");
        puts(CNZA "  ║" RST "  (C) Carregar jogo salvo anteriormente          " CNZA "║");
        puts(CNZA "  ║" RST "  (X) Sair da partida e recomeçar                " CNZA "║");
        puts(CNZA "  ║" RST "  (V) Voltar ao jogo atual                       " CNZA "║");
        puts(CNZA "  ║" RST "  (0) Sair do jogo                               " CNZA "║");
        puts(CNZA "  ╚═════════════════════════════════════════════════╝");  
        putchar('\n');
        fpurge(stdin);
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        switch(escolha) {
            case 'R': escolha = 'R'; break;
            case 'S': escolha = 'S'; break;
            case 'C': escolha = 'C'; break;
            case 'X': escolha = 'X'; break;
            case 'V': escolha = 'V'; break;
            case '0': escolha = '0'; break;
            default:
                puts("Escolha uma das opcoes...");
                escolha = '?';
                sleep(1);
                continue;
        }
    }
    return escolha;
}

void inicializar_vetor_pecas(char V1[], char V2[], size_t tam) {
    // Preenche o vetor passado com as peças correspondentes ao jogador 1 ou 2
    int i;

    for (i = 0; i < tam; ++i) {
        if (i < tam-2) {
            V1[i] = 'g';
            V2[i] = 'c';
        } else if (i < tam-1) {
            V1[i] = 'p';
            V2[i] = 'f';
        } else {
            V1[i] = 'R';
            V2[i] = 'F';
        }
    }
}

void inicializar_matriz_posicao(char V1[], char V2[], size_t tam, size_t tam_x, size_t tam_y, char pos[tam_x][tam_y]) {
    // Preenche as posições com as peças
    // Linhas pares = colunas pares
    // Linhas ímpares = colunas ímpares
    int i = 0, j = 0;
    int x, y;

    // Para cada linha, da 0 até a 4
    for (y = 0; y < 5; ++y) {
        for (x = 0; x < tam_x; x++) {
            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    pos[x][y] = V1[i];  // Se a linha for par e a coluna for par, coloque a peça do vetor na matriz
                    i++;
                } else {
                    pos[x][y] = '0';    // Se a coluna for ímpar, recebe 0
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
        for (x = 0; x < tam_x; x++) {
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
    for (x = 0; x < tam_x; x++) {
        if (x % 2 == 0) {
            pos[x][5] = '0';
        } else {
            if (x == 1) {
                pos[x][5] = V1[tam - 2];
            } else {
                pos[x][5] = ' ';            
            }
        }
    }

    // Para a linha 6, se a coluna for ímpar, recebe 0
    // Se a coluna for par e 0, coloque a peça V1[29] na posição pos[0][6], se for 10, a peça V2[29] na pos[10][6], e outro núm recebe espaço (' ')
    for (x = 0; x < tam_x; x++) {
        if (x % 2 == 1) {
            pos[x][6] = '0';
        } else {
            if (x == 0) {
                pos[x][6] = V1[tam - 1];
            } else if (x == 10) {
                pos[x][6] = V2[tam - 1];
            } else {
                pos[x][6] = ' ';            
            }
        }
    }
    
    // Para a linha 7, se a coluna for par recebe 0
    // Se a coluna for ímpar, se for 9 recebe a peça V2[28], se não recebe espaço (' ')
    for (x = 0; x < tam_x; x++) {
        if (x % 2 == 0) {
            pos[x][7] = '0';
        } else {
            if (x == 9) {
                pos[x][7] = V2[tam - 2];
            } else {
                pos[x][7] = ' ';
            }
        }
    }
}

void comecar_jogo(char nome_jogador1[], char nome_jogador2[], bool *game) {
    *game = true;
    puts("Começando um novo jogo!");
    puts("Primeiro vamos conhecer os jogadores...");
    puts("Qual o nome do jogador 1, que vai comandar o [" VRML "R" CNZA "]ei, o [" VRML "p" CNZA "]ríncipe e os [" VRML "g" CNZA "]uerreiros?" VRML);
    fpurge(stdin);
    fgets(nome_jogador1, TAM_NOME, stdin);
    // Ao usar fgets, o caracter \n é adicionado à string. O laço abaixo troca pelo caracter que indica fim de string.
    int i;
    for (i = 0; i < TAM_NOME; i++) {
        if (nome_jogador1[i] == '\n') {
            nome_jogador1[i] = '\0';
            break;
        }
    }
    puts(CNZA "E o jogador 2, que vai comandar o [" VERD "F" CNZA "]azendeiro, seu [" VERD "f" CNZA "]ilho e os [" VERD "c" CNZA "]amponeses?" VERD);
    fpurge(stdin);
    fgets(nome_jogador2, TAM_NOME, stdin);
    i = 0;
    for (i = 0; i < TAM_NOME; i++) {
        if (nome_jogador2[i] == '\n') {
            nome_jogador2[i] = '\0';
            break;
        }
    }
}

void reiniciar_partida(size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], char pecas_jog1[], char pecas_jog2[], size_t tam) {
    system("clear");
    puts("Reiniciando, aguarde...");
    sleep(1);
    inicializar_vetor_pecas(pecas_jog1, pecas_jog2, tam);
    inicializar_matriz_posicao(pecas_jog1, pecas_jog2, tam, tam_x, tam_y, matriz_posicao);
}

void imprimir_tabuleiro(size_t tam_x, size_t tam_y, const char T[tam_x][tam_y]) {
    // Imprime em tela o tabuleiro, sendo a matriz de posições + as strings da moldura
    // Se T[x][y] != '0', imprima o conteúdo em tela. Se == '0', imprima a string separadora
    int x, y;
    
    // Limpa a tela e imprime o cabeçalho
    system("clear");
    putchar('\n');
    puts(CNZA "  @╔═════════════════════════════════════════╗");
    puts(CNZA "  @║     "RST"A  "CNZA"B  "RST"C  "CNZA"D  "RST"E  "CNZA"F  "RST"G  "CNZA"H  "RST"I  "CNZA"J  "RST"K     "CNZA"║");
    
    // Para cada linha, se o índice da linha for par ou ímpar, acontece algo diferente
    for (y = 0; y < tam_y; y++) {
        if (y % 2 == 0) {
            // Linha índice par (y = 0, linha = 1)
            // Imprime as coordenadas numerais da borda esquerda
            printf(CNZA "  @║" RST " %2d " CNZA "[", y+1);
            // Imprime ou uma peça ou um separador
            for (x = 0; x < tam_x; x++) {
                if (T[x][y] != '0') {
                    switch(T[x][y]) {
                        case ' ': putchar(T[x][y]); break;
                        case 'g': case 'p': case 'R': printf(VRML "%c", T[x][y]); break;
                        case 'c': case 'f': case 'F': printf(VERD "%c", T[x][y]); break;
                    }
                } else {
                    printf(CNZA "]---[");
                }
            }
            printf(CNZA "]" RST " %2d " CNZA "║\n", y+1);
            if (y < 12) {
                puts(CNZA "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║");
            }
        } else {
            // Linha índice ímpar (y = 1, linha = 2)
            printf(CNZA"  @║ %2d  | [", y+1);
            for (x = 1; x < tam_x - 1; x++) {
                if (T[x][y] != '0') {
                    switch(T[x][y]) {
                        case ' ': putchar(T[x][y]); break;
                        case 'g': case 'p': case 'R': printf(VRML "%c", T[x][y]); break;
                        case 'c': case 'f': case 'F': printf(VERD "%c", T[x][y]); break;
                    }
                } else {
                    printf(CNZA"] | [");
                }
            }
            printf(CNZA "] |  %2d ║\n", y+1);
            puts(CNZA "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║");
        }
    }
    puts(CNZA "  @║     "RST"A  "CNZA"B  "RST"C  "CNZA"D  "RST"E  "CNZA"F  "RST"G  "CNZA"H  "RST"I  "CNZA"J  "RST"K     "CNZA"║");
    puts(CNZA "  @╚═════════════════════════════════════════╝");
    putchar('\n');
}

int pedir_entrada(const int *jog_atual, int peca[], char nome_jogador1[], char nome_jogador2[]) {
    // coord_x_l = coordenada na forma letra, depois traduzida para forma número
    const int x = 0, y = 1;
    char coord_x_l;
    int coord_x_n, coord_y;

    // Pede as coordenadas e troca por algo que a matriz entende
    if (*jog_atual == 1) {
        printf(VRML "%s, sua vez!\n" CNZA, nome_jogador1);
    } else {
        printf(VERD "%s, sua vez!\n" CNZA, nome_jogador2);
    }
    printf("Digite as coordenadas (A0) da peça que você quer mover ou (P) para pausar o jogo: ");
    fpurge(stdin);
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
        // O case abaixo contempla a chamada do menu_pausa
        case 'P': return 0;
    }
    scanf("%d", &coord_y);
    coord_y -= 1;

    // Guarda as coordenadas no vetor
    peca[x] = coord_x_n;
    peca[y] = coord_y;
    return 1;
}

bool validar_peca(const int *jog_atual, const int peca[], size_t tam_x, size_t tam_y, const char matriz_posicao[tam_x][tam_y]) {
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

    // 3ª Parte: retornar falso se qualquer jogador escolher um espaço

    if (matriz_posicao[peca[x]][peca[y]] == ' ') {
        puts("Essa posicao estah vazia...");
        sleep(2);
        return false;
    }
    return true;
}

bool validar_alcance(const int peca[], size_t tam_x, size_t tam_y, const char matriz_posicao[tam_x][tam_y], pontoCardeal * movimento, pontoCardeal * captura) {
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
    movimento->N[x] = peca[x]; movimento->N[y] = (peca[y] - 2);
    movimento->S[x] = peca[x]; movimento->S[y] = (peca[y] + 2);
    movimento->E[x] = (peca[x] + 2); movimento->E[y] = peca[y];
    movimento->O[x] = (peca[x] - 2); movimento->O[y] =  peca[y];
    movimento->NE[x] = (peca[x] + 1); movimento->NE[y] = (peca[y] - 1);
    movimento->SE[x] = (peca[x] + 1); movimento->SE[y] = (peca[y] + 1);
    movimento->SO[x] = (peca[x] - 1); movimento->SO[y] = (peca[y] + 1);
    movimento->NO[x] = (peca[x] - 1); movimento->NO[y] = (peca[y] - 1);
    movimento->iN = 0, movimento->iS = 0, movimento->iE = 0, movimento->iO = 0, movimento->iNE = 0, movimento->iSE = 0, movimento->iSO = 0, movimento->iNO = 0;

    // Posições cardeais de captura
    captura->N[x] = peca[x]; captura->N[y] = (peca[y] - 4);
    captura->S[x] = peca[x]; captura->S[y] = (peca[y] + 4);
    captura->E[x] = (peca[x] + 4); captura->E[y] = peca[y];
    captura->O[x] = (peca[x] - 4); captura->O[y] = peca[y];
    captura->NE[x] = (peca[x] + 2); captura->NE[y] = (peca[y] - 2);
    captura->SE[x] = (peca[x] + 2); captura->SE[y] = (peca[y] + 2);
    captura->SO[x] = (peca[x] - 2); captura->SO[y] = (peca[y] + 2);
    captura->NO[x] = (peca[x] - 2); captura->NO[y] = (peca[y] - 2);
    captura->iN = 0, captura->iS = 0, captura->iE = 0, captura->iO = 0, captura->iNE = 0, captura->iSE = 0, captura->iSO = 0, captura->iNO = 0;

    // 1ª Parte: validar se as posições cardeais de movimento estão dentro do tabuleiro e se possuem um espaço
    // Se o conteúdo não for um espaço, verificar se é uma inimiga. Se for, registrar -1 na posição
    // Linhas de índice par = todas as coordenadas (N, S, E, O, NE, SE, SO e NO)
    // Linhas de índice ímpar = apenas as coordenadas subcardeais (NE, SE, SO e NO)
    // Jogador 1 verificar se { F, f, c }
    // Jogador 2 verificar se { R, p, g }

    if (peca[y] % 2 == 0) {
        if (movimento->N[y] >= LIM_SUPERIOR) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'F': case 'f': case 'c': movimento->iN = -1;
                }
                case 'p':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'f': case 'c': movimento->iN = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'c': movimento->iN = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'R': case 'p': case 'g': movimento->iN = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'p': case 'g': movimento->iN = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'g': movimento->iN = -1; break;
                }
            }
        }
        if (movimento->S[y] <= LIM_INFERIOR) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'F': case 'f': case 'c': movimento->iS = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'f': case 'c': movimento->iS = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'c': movimento->iS = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'R': case 'p': case 'g': movimento->iS = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'p': case 'g': movimento->iS = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'g': movimento->iS = -1; break;
                }
            }
        }
        if (movimento->E[x] <= LIM_DIREITO) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'f': case 'c': movimento->iE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'c': movimento->iE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'p': case 'g': movimento->iE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'g': movimento->iE = -1; break;
                }
            }
        }
        if (movimento->O[x] >= LIM_ESQUERDO) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'f': case 'c': movimento->iO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'c': movimento->iO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'p': case 'g': movimento->iO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'g': movimento->iO = -1; break;
                }
            }
        }
        if ((movimento->NE[x] <= LIM_DIREITO) && (movimento->NE[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'c': movimento->iNE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'g': movimento->iNE = -1; break;
                }
            }
        }
        if ((movimento->SE[x] <= LIM_DIREITO) && (movimento->SE[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'c': movimento->iSE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'g': movimento->iSE = -1; break;
                }
            }
        }
        if ((movimento->SO[x] >= LIM_ESQUERDO) && (movimento->SO[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'c': movimento->iSO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'g': movimento->iSO = -1; break;
                }
            }
        }
        if ((movimento->NO[x] >= LIM_ESQUERDO) && (movimento->NO[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'c': movimento->iNO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'g': movimento->iNO = -1; break;
                }
            }
        }
    } else { // Linha ímpar
        if ((movimento->NE[x] <= LIM_DIREITO) && (movimento->NE[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'c': movimento->iNE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'g': movimento->iNE = -1; break;
                }
            }
        }
        if ((movimento->SE[x] <= LIM_DIREITO) && (movimento->SE[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'c': movimento->iSE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'g': movimento->iSE = -1; break;
                }
            }
        }
        if ((movimento->SO[x] >= LIM_ESQUERDO) && (movimento->SO[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'c': movimento->iSO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'g': movimento->iSO = -1; break;
                }
            }
        }
        if ((movimento->NO[x] >= LIM_ESQUERDO) && (movimento->NO[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'c': movimento->iNO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'g': movimento->iNO = -1; break;
                }
            }
        }
    }

    // 2ª Parte: validar se as posições de captura estão disponíveis, caso sejam necessárias
    // Se registrar -1 em alguma posição cardeal, verificar posição de captura correspondente:
        // Se tiver um espaço, habilitar (true)
        // Se não tiver espaço, desabilitar (false)

    if (peca[y] % 2 == 0) {
        if ((movimento->iN == -1) && (captura->N[y] >= LIM_SUPERIOR) && (matriz_posicao[captura->N[x]][captura->N[y]] == ' ')) captura->iN = 1;
        if ((movimento->iS == -1) && (captura->S[y] <= LIM_INFERIOR) && (matriz_posicao[captura->S[x]][captura->S[y]] == ' ')) captura->iS = 1;
        if ((movimento->iE == -1) && (captura->E[x] <= LIM_DIREITO) && (matriz_posicao[captura->E[x]][captura->E[y]] == ' ')) captura->iE = 1;
        if ((movimento->iO == -1) && (captura->O[x] >= LIM_ESQUERDO) && (matriz_posicao[captura->O[x]][captura->O[y]] == ' ')) captura->iO = 1;
        if ((movimento->iNE == -1) && (captura->NE[x] <= LIM_DIREITO) && (captura->NE[y] >= LIM_SUPERIOR)
            && (matriz_posicao[captura->NE[x]][captura->NE[y]] == ' ')) captura->iNE = 1;
        if ((movimento->iSE == -1) && (captura->SE[x] <= LIM_DIREITO) && (captura->SE[y] <= LIM_INFERIOR)
            && (matriz_posicao[captura->SE[x]][captura->SE[y]] == ' ')) captura->iSE = 1;
        if ((movimento->iSO == -1) && (captura->SO[x] >= LIM_ESQUERDO) && (captura->SO[y] <= LIM_INFERIOR)
            && (matriz_posicao[captura->SO[x]][captura->SO[y]] == ' ')) captura->iSO = 1;
        if ((movimento->iNO == -1) && (captura->NO[x] >= LIM_ESQUERDO) && (captura->NO[y] >= LIM_SUPERIOR)
            && (matriz_posicao[captura->NO[x]][captura->NO[y]] == ' ')) captura->iNO = 1;
    } else { // Linha ímpar
        if ((captura->iNE == -1) && (captura->NE[x] <= LIM_DIREITO) && (captura->NE[y] >= LIM_SUPERIOR) && (matriz_posicao[captura->NE[x]][captura->NE[y]] == ' ')) captura->iNE = 1;
        if ((captura->iSE == -1) && (captura->SE[x] <= LIM_DIREITO) && (captura->SE[y] <= LIM_INFERIOR) && (matriz_posicao[captura->SE[x]][captura->SE[y]] == ' ')) captura->iSE = 1;
        if ((captura->iSO == -1) && (captura->SO[x] >= LIM_ESQUERDO) && (captura->SO[y] <= LIM_INFERIOR) && (matriz_posicao[captura->SO[x]][captura->SO[y]] == ' ')) captura->iSO = 1;
        if ((captura->iNO == -1) && (captura->NO[x] >= LIM_ESQUERDO) && (captura->NO[y] >= LIM_SUPERIOR) && (matriz_posicao[captura->NO[x]][captura->NO[y]] == ' ')) captura->iNO = 1;
    }

    // Se todas as posições cardeais de movimento e captura forem 0 ou -1, o movimento da peça é impossível
    if (((movimento->iN < 1) && (movimento->iS < 1) && (movimento->iE < 1) && (movimento->iO < 1) && (movimento->iNE < 1) && (movimento->iSE < 1) && (movimento->iSO < 1) && (movimento->iNO < 1))
        && ((captura->iN < 1) && (captura->iS < 1) && (captura->iE < 1) && (captura->iO < 1) && (captura->iNE < 1) && (captura->iSE < 1) && (captura->iSO < 1) && (captura->iNO < 1))) {
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

    printf("Digite as coordenadas de destino: ");
    scanf(" %c", &coord_x_l_dest);
    scanf("%d", &coord_y_dest);
    coord_x_l_dest = toupper(coord_x_l_dest);

    // Troca a coordenada alfabética digitada por uma coordenada numérica
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

bool validar_destino(const int peca[], const int dest[], size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], pontoCardeal movimento, pontoCardeal captura, char pecas_jog1[], char pecas_jog2[]) {
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
    if (peca[y] % 2 == 0) {
        if ((((dest[x] == movimento.N[x]) && (dest[y] == movimento.N[y]) && (movimento.iN == 1)))
        || (((dest[x] == movimento.S[x]) && (dest[y] == movimento.S[y]) && (movimento.iS == 1)))
        || (((dest[x] == movimento.E[x]) && (dest[y] == movimento.E[y]) && (movimento.iE == 1)))
        || (((dest[x] == movimento.O[x]) && (dest[y] == movimento.O[y]) && (movimento.iO == 1)))
        || (((dest[x] == movimento.NE[x]) && (dest[y] == movimento.NE[y]) && (movimento.iNE == 1)))
        || (((dest[x] == movimento.SE[x]) && (dest[y] == movimento.SE[y]) && (movimento.iSE == 1)))
        || (((dest[x] == movimento.SO[x]) && (dest[y] == movimento.SO[y]) && (movimento.iSO == 1)))
        || (((dest[x] == movimento.NO[x]) && (dest[y] == movimento.NO[y]) && (movimento.iNO == 1)))) {
            return true;            
        } else {
            if ((dest[x] == captura.N[x]) && (dest[y] == captura.N[y]) && (movimento.iN == -1) && (captura.iN == 1)) {
                capturar_peca(movimento.N, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.S[x]) && (dest[y] == captura.S[y]) && (movimento.iS == -1) && (captura.iS == 1)) {
                capturar_peca(movimento.S, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.E[x]) && (dest[y] == captura.E[y]) && (movimento.iE == -1) && (captura.iE == 1)) {
                capturar_peca(movimento.E, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.O[x]) && (dest[y] == captura.O[y]) && (movimento.iO == -1) && (captura.iO == 1)) {
                capturar_peca(movimento.O, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.NE[x]) && (dest[y] == captura.NE[y]) && (movimento.iNE == -1) && (captura.iNE == 1)) {
                capturar_peca(movimento.NE, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SE[x]) && (dest[y] == captura.SE[y]) && (movimento.iSE == -1) && (captura.iSE == 1)) {
                capturar_peca(movimento.SE, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SO[x]) && (dest[y] == captura.SO[y]) && (movimento.iSO == -1) && (captura.iSO == 1)) {
                capturar_peca(movimento.SO, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.NO[x]) && (dest[y] == captura.NO[y]) && (movimento.iNO == -1) && (captura.iNO == 1)) {
                capturar_peca(movimento.NO, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            puts("Destino invalido...");
            sleep(2);
            return false;
        }
    } else { // linha ímpar
        if ((((dest[x] == movimento.NE[x]) && (dest[y] == movimento.NE[y]) && (movimento.iNE == 1)))
        || (((dest[x] == movimento.SE[x]) && (dest[y] == movimento.SE[y]) && (movimento.iSE == 1)))
        || (((dest[x] == movimento.SO[x]) && (dest[y] == movimento.SO[y]) && (movimento.iSO == 1)))
        || (((dest[x] == movimento.NO[x]) && (dest[y] == movimento.NO[y]) && (movimento.iNO == 1)))) {
            return true;            
        } else {
            if ((dest[x] == captura.NE[x]) && (dest[y] == captura.NE[y]) && (movimento.iNE == -1) && (captura.iNE == 1)) {
                capturar_peca(movimento.NE, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SE[x]) && (dest[y] == captura.SE[y]) && (movimento.iSE == -1) && (captura.iSE == 1)) {
                capturar_peca(movimento.SE, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SO[x]) && (dest[y] == captura.SO[y]) && (movimento.iSO == -1) && (captura.iSO == 1)) {
                capturar_peca(movimento.SO, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.NO[x]) && (dest[y] == captura.NO[y]) && (movimento.iNO == -1) && (captura.iNO == 1)) {
                capturar_peca(movimento.NO, TAM_X_TAB, TAM_Y_TAB, matriz_posicao, TAM_VETOR, pecas_jog1, pecas_jog2);
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

void capturar_peca(int coord_peca_capturada[], size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], size_t tam_vetor, char pecas_jog1[], char pecas_jog2[]) {
    // Verifica qual a peça capturada, e coloca um espaço em branco no seu lugar correspondente dentro do vetor de peças do jogador
    // Para as peças g e c que se repetem, começa verificando na primeira posição e vai até a 28ª

    const int x = 0, y = 1;
    int i;
    switch(matriz_posicao[coord_peca_capturada[x]][coord_peca_capturada[y]]) {
        case 'R': pecas_jog1[tam_vetor - 1] = ' '; break;
        case 'p': pecas_jog1[tam_vetor - 2] = ' '; break;
        case 'g':
            for (i = 0; i < tam_vetor - 2;) {
                if (pecas_jog1[i] == 'g') {
                    pecas_jog1[i] = ' ';
                    break;
                } else { ++i; }
            }
        case 'F': pecas_jog2[tam_vetor - 1] = ' '; break;
        case 'f': pecas_jog2[tam_vetor - 2] = ' '; break;
        case 'c':
            for (i = 0; i < tam_vetor - 2;) {
                if (pecas_jog2[i] == 'c') {
                    pecas_jog2[i] = ' ';
                    break;
                } else { ++i; }
            }
    }
    matriz_posicao[coord_peca_capturada[x]][coord_peca_capturada[y]] = ' ';
}

void fazer_jogada(size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], const int peca[2], const int dest[2]) {
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

int verificar_vetor_pecas(char pecas_jog1[], char pecas_jog2[], size_t tam, int *jog_atual) {
	// Percorre o vetor peças de cada jogador. Caso não encontre nenhuma, é porque o jogador perdeu
    int i;
    int perdedor = 0;
    for (i = 0; i < tam; ++i) {
        if (*jog_atual == 1) {
            if (pecas_jog1[i] != ' ') {
                return 1;
            } else {
                perdedor = 1;
                continue;
            }
        } else { // Jogador 2
            if (pecas_jog2[i] != ' ') {
                return 1;
            } else {
                perdedor = 2;
                continue;
            }
        }
    }
    printf("O jogador %d ficou sem pecas e perdeu! Fim de jogo!\n", perdedor);
    sleep(2);
    return 0;
}

int salvar_jogo(size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], char nome_jogador1[], char pecas_jog1[], char nome_jogador2[], char pecas_jog2[], int *jog_atual) {
    char nome_arquivo[34];
    char caractere_matriz;

    printf("Escolha um nome para o arquivo de jogo salvo: ");
    fpurge(stdin);
    fgets(nome_arquivo, 29, stdin);
    int i, j;
    for (i = 0; i < 29; i++) {
        if (nome_arquivo[i] == '\n') {
            nome_arquivo[i] = '\0';
            break;
        }
    }
    strcat(nome_arquivo, ".txt");
    // Tenta acessar o arquivo para ver se ele existe. Se existe, apaga antes de escrever novamente
    int arq_existe = access(nome_arquivo, W_OK);
    if (arq_existe) {
        remove(nome_arquivo);
    }
    FILE * jogosalvo = fopen(nome_arquivo, "w");
    if (jogosalvo == 0) {
        perror("ERRO: nao foi possivel criar o arquivo...");
        return 0;
    }

    // Salva a matriz da forma que o computador enxerga
    for (j = 0; j < TAM_Y_TAB; ++j) {
        for (i = 0; i < TAM_X_TAB; ++i) {
            caractere_matriz = matriz_posicao[i][j];
            fprintf(jogosalvo, "%c", caractere_matriz);
        }
        caractere_matriz = '\n';
        fprintf(jogosalvo, "%c", caractere_matriz);
    }
    
    // Salva os nomes dos jogadores, seus vetores de peças e o jogador atual
    fprintf(jogosalvo, "%s\n", nome_jogador1);
    fprintf(jogosalvo, "%s\n", pecas_jog1);
    fprintf(jogosalvo, "%s\n", nome_jogador2);
    fprintf(jogosalvo, "%s\n", pecas_jog2);
    fprintf(jogosalvo, "%d", *jog_atual);

    fclose(jogosalvo);
    puts("Jogo salvo com sucesso...");
    sleep(1);
    return 1;
}

int carregar_jogo(size_t tam_x, size_t tam_y, char matriz_posicao[tam_x][tam_y], char nome_jogador1[], char pecas_jog1[], char nome_jogador2[], char pecas_jog2[], int *jog_atual, bool *game) {
    char caractere, descarte;
    char nome_arquivo[34];
    int i, j;

    printf("Digite o nome do arquivo salvo: ");
    fpurge(stdin);
    fgets(nome_arquivo, 29, stdin);
    for (i = 0; i < 29; i++) {
        if (nome_arquivo[i] == '\n') {
            nome_arquivo[i] = '\0';
            break;
        }
    }
    // Concatena o nome do arquivo salvo com o '.txt' 
    strcat(nome_arquivo, ".txt");
    FILE * jogosalvo = fopen(nome_arquivo, "r");
    if (jogosalvo == 0) {
        perror("ERRO: nao foi possivel abrir o arquivo...");
        sleep(2);
        return 0;
    }

    // Carregar matriz
    for (j = 0; j < tam_y; ++j) {
        for (i = 0; i < tam_x; ++i) {
            caractere = fgetc(jogosalvo);
            if (caractere != '\n') {
                matriz_posicao[i][j] = caractere;
            }
        }
        descarte = fgetc(jogosalvo);
    }

    // Carregar nome do jogador 1
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            nome_jogador1[i] = caractere;
            i++;
        } else {
            nome_jogador1[i] = '\0';
        }
    } while (caractere != '\n');

    // Carregar peças do jogador 1
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            pecas_jog1[i] = caractere;
            i++;
        } else {
            descarte = caractere;
        }
    } while (caractere != '\n');

    // Carregar nome do jogador 2
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            nome_jogador2[i] = caractere;
            i++;
        } else {
            nome_jogador2[i] = '\0';
        }
    } while (caractere != '\n');

    // Carregar peças do jogador 2
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            pecas_jog2[i] = caractere;
            i++;
        } else {
            descarte = caractere;
        }
    } while (caractere != '\n');

    // Carregadr jogador atual. O - '0' eh usado para converter de char '1' para inteiro 1
    char jog_lido = fgetc(jogosalvo);
    *jog_atual = jog_lido - '0';

    fclose(jogosalvo);
    puts("Jogo carregado, iniciando...");
    *game = true;
    sleep(1);
    return 1;
}