#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//#include "dablib.h" - fazer biblioteca funcionar

int imprime_menu(void);
int le_tabuleiro(void);
int imprime_tabuleiro(void);

// Matriz declarada globalmente para que todas as funções tenham acesso
char tabuleiro[37][26];

// Variável que controla quem é o jogador da vez (1 ou 2)
unsigned jogador_atual = 0;

int main(void) {
    imprime_menu();
	return EXIT_SUCCESS;
}

// Funções (incluir na biblioteca e tirar daqui)

int imprime_menu(void) {
    // Melhorar design dos printfs das escolhas
    // Incluir __fpurge ou fflush antes dos getchar() para não repetir o printf dentro do while
    char escolha = 'E';

    // Imprime o menu inicial do jogo
    printf("Bem-vindo(a) ao jogo Dablot!\n");
    while (escolha != 'S') {
        printf("Para INICIAR, digite I\nPara APRENDER A JOGAR, digite A\nPara sair, digite S\n");
        escolha = getchar();
        escolha = toupper(escolha);
        if (escolha == 'I') {
            while ((escolha != 'N' || escolha != 'C')) {
            printf("Deseja um Novo Jogo (N) ou Carregar Jogo Salvo (C)?\n");
            escolha = getchar();
            escolha = toupper(escolha);
                if (escolha == 'N') {
                    // Iniciar novo jogo
                    le_tabuleiro();
                    imprime_tabuleiro();
                    // Aqui deve vir a função pede_valida_jogada()?
                    return EXIT_SUCCESS;
                } else if (escolha == 'C') {
                    // Carregar jogo salvo
                }
            }
        } else if (escolha == 'A') {
            // Abrir tutorial
        }
    }
    if (escolha == 'S') {
        // Sair do jogo (colocar aqui função que desligue o terminal)
        printf("Saindo...\n");
    }
    return EXIT_SUCCESS;
}

int le_tabuleiro(void) {
    // Lê o tabuleiro padrão de início de jogo armazenado no arquivo matriz_tabuleiro.txt e grava na matriz global tabuleiro[][]
	char caractere;
    int i, j;

	FILE* stream = fopen("matriz_tabuleiro.txt", "r");
    if (stream == 0) {
        perror("Erro na abertura do arquivo");
        return EXIT_FAILURE;
    }
    while (!feof(stream)) { 
        for (i = 0; i < 37; ++i) {
            for (j = 0; j < 26; ++j) {
            	caractere = fgetc(stream);
                if (caractere == EOF) {
                    if (ferror(stream)) {
                        perror("Erro na leitura do arquivo");
                        fclose(stream);
                        return EXIT_FAILURE;
                    }
                } else {
                	tabuleiro[i][j] = caractere;
                }
            }
        }
    }
    // Fechamento da stream, fim do acesso ao arquivo
    fclose(stream);
    return EXIT_SUCCESS;
}

int imprime_tabuleiro(void) {
    // Imprime o tabuleiro armezenado na matriz global tabuleiro[][]
    int i, j;
    system("clear");
    for (i = 0; i < 37; ++i) {
        for (j = 0; j < 26; ++j) {
            putchar(tabuleiro[i][j]);
            }
        }
    printf("\n");
    return EXIT_SUCCESS;
}
/*
int pede_valida_jogada(void) {
    // Pede as coordenadas para o jogador da vez, valida se o jogador escolheu uma posição que possui uma peça e se essa peça é do seu próprio time
    // se jogador_atual = 1 deve validar com as peças R, p e g.
    // se jogador_atual = 2 deve validar com as peças F, f e c.
    printf("Digite a coordenada alfabetica seguida da coordenada numeral (ex A10): ");
    scanf();
}

int valida_jogada(int ?????) {
    // Valida se o jogador escolheu um destino correto para sua peça
    // se posição = vazio
    // se posição = ocupada por inimigo && próxima posição = vazio
}

int faz_jogada(void) {
    // Realiza a jogada propriamente dita
    // Precisa de variável para armazenar onde a peça estava (e colocar um espaço em branco)
    // Ao fim da função, mudar jogador_atual
}*/