int imprime_tabuleiro(void) {
    char tabuleiro[36][26];
    int i, j;
    for (i = 0; i < 36; i++) {
        for (j = 0; j < 26; j++) {
            putchar(tabuleiro[i][j]);
            }
        }
    printf("\n");
    return EXIT_SUCCESS;
}