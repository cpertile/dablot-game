void fazer_jogada(char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], const int peca[2], const int dest[2]) {
    const int x = 0, y = 1;
    char tmp_move_peca = matriz_posicao[dest[x]][dest[y]];
    matriz_posicao[dest[x]][dest[y]] = matriz_posicao[peca[x]][peca[y]];
    matriz_posicao[peca[x]][peca[y]] = tmp_move_peca;
}