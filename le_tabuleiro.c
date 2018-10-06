int le_tabuleiro(void) {
	char tabuleiro[36][26];
    int i, j;

	FILE* stream = fopen("matriz_tabuleiro.txt", "r");
    if (stream == 0) {
        // Houve erro, imprime o que aconteceu
        perror("Erro na abertura do arquivo");
        return EXIT_FAILURE;
    }
    while (!feof(stream)) { // Enquanto NAO encontra o fim do arquivo...
        for (i = 0; i < 36; i++) {
            for (j = 0; j < 26; j++) {
                tabuleiro[i][j] = fgetc(stream);
                if (tabuleiro[i][j] == EOF) {
                    if (ferror(stream)) {
                        perror("Erro na leitura do arquivo");
                        fclose(stream); // fecha o arquivo que estah aberto
                        return EXIT_FAILURE;
                    }
                }
            }
        }
    }
    // Fechamento da stream, fim do acesso ao arquivo
    fclose(stream);
    return EXIT_SUCCESS;
}