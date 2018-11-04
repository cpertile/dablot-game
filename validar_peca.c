bool validar_peca(const int *jog_atual, const int peca[], const char matriz_posicao[TAM_X_TAB][TAM_Y_TAB]) {
    const int x = 0, y = 1;
    // 1ª parte: validar se as coordenadas estão dentro do tabuleiro. Se não estiverem, retornar false
    // Princípio Coluna par Linha par / Coluna ímpar linha ímpar

    if ((peca[x] < LIM_ESQUERDO) || (peca[x] > LIM_DIREITO) || (peca[y] < LIM_SUPERIOR) || (peca[y] > LIM_INFERIOR)) {
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        sleep(2);
        return false;
    }

    if ((peca[x] % 2 == 0) && (peca[y] % 2 == 1)) {
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        sleep(2);
        return false;
    }

    if ((peca[x] % 2 == 1) && (peca[y] % 2 == 0)) {
        puts("Voce escolheu uma combinacao invalida, tente novamente...");
        sleep(2);
        return false;
    }

    // 2ª parte: validar o time da peça escolhida
    // Retornar falso se o jogador 1 escolher { F, f, c } ou se o jogador 2 escolher { R, p, g }
    // Retornar falso se qualquer jogador escolher um espaço

    if (*jog_atual == 1) {
        if ((matriz_posicao[peca[x]][peca[y]] == 'F') || (matriz_posicao[peca[x]][peca[y]] == 'f') || (matriz_posicao[peca[x]][peca[y]] == 'c')) {
            puts("Voce escolheu uma peca do adversario...");
            sleep(2);
            return false;
        }
    } else {
        if ((matriz_posicao[peca[x]][peca[y]] == 'R') || (matriz_posicao[peca[x]][peca[y]] == 'p') || (matriz_posicao[peca[x]][peca[y]] == 'g')) {
            puts("Voce escolheu uma peca do adversario...");
            sleep(2);
            return false;
        }
    }

    if (matriz_posicao[peca[x]][peca[y]] == ' ') {
        puts("Essa posicao estah vazia...");
        sleep(2);
        return false;
    }
    return true;
}