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