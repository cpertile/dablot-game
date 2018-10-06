#include <stdlib.h>
#include <stdio.h>
//#include "dablib.h" - fazer biblioteca funcionar

int le_tabuleiro(void);
int imprime_tabuleiro(void);

char tabuleiro[37][26];
int main(void) {
	printf("Bem vindo ao Dablot\n");
	printf("O tabuleiro serah lido agora\n");
	le_tabuleiro();
	printf("O tabuleiro foi lido com sucesso\n");
	printf("O tabuleiro sera impresso agora\n");
	imprime_tabuleiro();
	printf("O tabuleiro foi impresso\n");
	return EXIT_SUCCESS;
}

// Funções (incluir na biblioteca e tirar daqui)
int le_tabuleiro(void) {
	char caractere;
    int i, j;

	FILE* stream = fopen("matriz_tabuleiro.txt", "r");
    if (stream == 0) {
        // Houve erro, imprime o que aconteceu
        perror("Erro na abertura do arquivo");
        return EXIT_FAILURE;
    }
    while (!feof(stream)) { // Enquanto NAO encontra o fim do arquivo...
        for (i = 0; i < 37; ++i) {
            for (j = 0; j < 26; ++j) {
            	caractere = fgetc(stream);
                if (caractere == EOF) {
                    if (ferror(stream)) {
                        perror("Erro na leitura do arquivo");
                        fclose(stream); // fecha o arquivo que estah aberto
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
    int i, j;
    for (i = 0; i < 37; ++i) {
        for (j = 0; j < 26; ++j) {
            putchar(tabuleiro[i][j]);
            }
        }
    printf("\n");
    return EXIT_SUCCESS;
}