// Dablot v 0.8.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "dablotlib.h"
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
#define BCPT "\x1B[30;47m"
#define BNCO "\x1B[37m"
#define CIAN "\x1B[96m"
#define CNZA "\x1B[90m"
#define MGNT "\x1B[95m" 
#define VERD "\x1B[32m"
#define VRML "\x1B[91m"
#define RST  "\x1B[0m"

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
    inicializar_matriz_posicao(pecas_jog1, pecas_jog2, TAM_VETOR, matriz_posicao);
    
    // Chamada do menu inicial para início do jogo
    char escolha = menu_inicial();
    switch(escolha) {
        case 'A': tutorial(); escolha = 'N';
        case 'C':
        case 'N':
            if (escolha == 'C') {
                carregar_jogo(matriz_posicao, nome_jogador1, pecas_jog1, nome_jogador2, pecas_jog2, &jog_atual, TAM_VETOR, &game);
            } else {
                comecar_jogo(nome_jogador1, nome_jogador2, &game);
                jog_atual = sortear_jogador();
            }
            while (game) {
                imprimir_tabuleiro(matriz_posicao);

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

                if (!verificar_pecas_livres(matriz_posicao, &jog_atual, peca, &movimento, &captura)) {
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
                        case 'C': carregar_jogo(matriz_posicao, nome_jogador1, pecas_jog1, nome_jogador2, pecas_jog2, &jog_atual, TAM_VETOR, &game); continue;
                        case 'S': salvar_jogo(matriz_posicao, nome_jogador1, pecas_jog1, nome_jogador2, pecas_jog2, &jog_atual, TAM_VETOR); continue;
                        case 'R': reiniciar_partida(matriz_posicao, pecas_jog1, pecas_jog2, TAM_VETOR); jog_atual = sortear_jogador(); continue;
                        case 'X': reiniciar_partida(matriz_posicao, pecas_jog1, pecas_jog2, TAM_VETOR); jog_atual = sortear_jogador();
                        comecar_jogo(nome_jogador1, nome_jogador2, &game); continue;
                        case '0': game = false; continue;
                    }
                }

                if (!validar_peca(&jog_atual, peca, matriz_posicao)) continue;

                if (!validar_alcance(peca, matriz_posicao, &movimento, &captura)) {
                    puts("Essa peca nao pode se mover, tente outra...");
                    sleep(2);
                    continue;
                }

                pedir_destino(dest);
                if (!validar_destino(peca, dest, matriz_posicao, movimento, captura, pecas_jog1, pecas_jog2)) continue;
                fazer_jogada(matriz_posicao, peca, dest);
                trocar_turno(&jog_atual);
            }
        case 'S': puts("Saindo do jogo... Obrigado por jogar Dablot :) ");
        sleep(3);
    }
    return EXIT_SUCCESS;
}