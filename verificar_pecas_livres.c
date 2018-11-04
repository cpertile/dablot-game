bool verificar_pecas_livres(char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], const int *jog_atual, int peca[], pontoCardeal *movimento, pontoCardeal *captura) {
    // Rodar a função validar_alcance() num loop para todas as peças do jogador atual na matriz
    // Caso validar_alcance() retorne verdadeiro, sair do laço e retornar verdadeiro
    // Caso validar_alcance() retorne falso, continuar verificando até chegar na última peça
    // Caso a última também retorne falso, todas as peças estão bloqueadas, retornar falso, esse jogador perdeu o jogo
    int x, y;
    const int X = 0;
    const int Y = 1;

    for (y = 0; y < TAM_Y_TAB; ++y) {
        for (x = 0; x < TAM_X_TAB; ++x) {
            if (*jog_atual == 1) {
                switch(matriz_posicao[x][y]) {
                    case 'R': case 'p': case 'g':
                    peca[X] = x;
                    peca[Y] = y;
                    if (validar_alcance(peca, matriz_posicao, movimento, captura)) {
                        return true;
                    }
                }
            } else {
                switch(matriz_posicao[x][y]) {
                    case 'F': case 'f': case 'c':
                    peca[X] = x;
                    peca[Y] = y;
                    if (validar_alcance(peca, matriz_posicao, movimento, captura)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}