void capturar_peca(int coord_peca_capturada[], char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], char pecas_jog1[], char pecas_jog2[]) {
    const int x = 0, y = 1;
    int i;
    switch(matriz_posicao[coord_peca_capturada[x]][coord_peca_capturada[y]]) {
        case 'R': pecas_jog1[29] = ' '; break;
        case 'p': pecas_jog1[28] = ' '; break;
        case 'g':
            for (i = 0; i < 28;) {
                if (pecas_jog1[i] == 'g') {
                    pecas_jog1[i] = ' ';
                    break;
                } else { ++i; }
            }
        case 'F': pecas_jog2[29] = ' '; break;
        case 'f': pecas_jog2[28] = ' '; break;
        case 'c':
            for (i = 0; i < 28;) {
                if (pecas_jog2[i] == 'c') {
                    pecas_jog2[i] = ' ';
                    break;
                } else { ++i; }
            }
    }
    matriz_posicao[coord_peca_capturada[x]][coord_peca_capturada[y]] = ' ';
}