void imprimir_tabuleiro(const char T[TAM_X_TAB][TAM_Y_TAB]) {
    // Imprime em tela o tabuleiro, sendo a matriz de posições + as strings da moldura
    // Se T[x][y] != '0', imprima em tela. Se == '0', imprima a string separadora
    // TODO: Usar %2d nos números para alinhas corretamente
    int x, y;
    
    // Limpa a tela e printa o cabeçalho
    system("clear");
    putchar('\n');
    puts(CNZA "  @╔═════════════════════════════════════════╗");
    puts(CNZA "  @║     "RST"A  "CNZA"B  "RST"C  "CNZA"D  "RST"E  "CNZA"F  "RST"G  "CNZA"H  "RST"I  "CNZA"J  "RST"K     "CNZA"║");
    
    // Para cada linha, se o índice da linha for par ou ímpar, acontece algo diferente
    for (y = 0; y < TAM_Y_TAB; y++) {
        if (y % 2 == 0) {
            // Linha índice par (y = 0, linha = 1)
            // Imprime as coordenadas numerais da borda esquerda
            if (y < 10) {
                printf(CNZA "  @║" RST "  %d " CNZA "[", y+1);
            } else {
                printf(CNZA "  @║" RST " %d " CNZA "[", y+1);
            }
            // Imprime ou uma peça ou um separador
            for (x = 0; x < TAM_X_TAB; x++) {
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
            if (y < 10) {
                printf(CNZA "]" RST " %d  " CNZA "║\n", y+1);
            } else {
                printf(CNZA "]" RST " %d " CNZA "║\n", y+1);
            }
            if (y < 12) {
                puts(CNZA "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║");
            }
        } else {
            // Linha índice ímpar (y = 1, linha = 2)
            if (y < 9) {
                printf(CNZA"  @║  %d  | [", y+1);                
            } else {
                printf(CNZA"  @║ %d  | [", y+1);                
            }
            for (x = 1; x < TAM_X_TAB-1; x++) {
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
            if (y < 9) {
                printf(CNZA "] |  %d  ║\n", y+1);               
            } else {
                printf(CNZA "] |  %d ║\n", y+1);               
            }
            puts(CNZA "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║");
        }
    }
    puts(CNZA "  @║     "RST"A  "CNZA"B  "RST"C  "CNZA"D  "RST"E  "CNZA"F  "RST"G  "CNZA"H  "RST"I  "CNZA"J  "RST"K     "CNZA"║");
    puts(CNZA "  @╚═════════════════════════════════════════╝");
    putchar('\n');
}