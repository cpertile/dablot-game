bool validar_destino(const int peca[], const int dest[], char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], pontoCardeal movimento, pontoCardeal captura, char pecas_jog1[], char pecas_jog2[]) {
    const int x = 0, y = 1;
    // Retornar 0 para destino inválido, 1 para movimento normal, 2 para movimento de captura
    // 1ª parte: validar se o destino está dentro do tabuleiro. Se não estiver, retornar false
    // Princípio Coluna par Linha par / Coluna ímpar linha ímpar

    if ((dest[x] < LIM_ESQUERDO) || (dest[x] > LIM_DIREITO) || (dest[y] < LIM_SUPERIOR) || (dest[y] > LIM_INFERIOR)) {
        puts("Voce escolheu um destino invalido, tente novamente...");
        sleep(2);
        return false;
    }

    if ((dest[x] % 2 == 0) && (dest[y] % 2 == 1)) {
        puts("Voce escolheu um destino invalido, tente novamente...");
        sleep(2);
        return false;
    }

    if ((dest[x] % 2 == 1) && (dest[y] % 2 == 0)) {
        puts("Voce escolheu um destino invalido, tente novamente...");
        sleep(2);
        return false;
    }
    // 2ª Parte: validar se o destino não é igual à pelo menos uma das posições de movimento cardeal
    // Se não for de nenhuma coordenada de movimento cardeal, validar se é alguma coordenada de captura
    // Para ser uma captura válida, a cardeal de movimento == -1 e a cardeal de captura == 1
    // Se for captura válida, chamar a função capturar_peca(<posição movimento cardeal equivalente>)
    if (peca[y] % 2 == 0) {
        if ((((dest[x] == movimento.N[x]) && (dest[y] == movimento.N[y]) && (movimento.iN == 1)))
        || (((dest[x] == movimento.S[x]) && (dest[y] == movimento.S[y]) && (movimento.iS == 1)))
        || (((dest[x] == movimento.E[x]) && (dest[y] == movimento.E[y]) && (movimento.iE == 1)))
        || (((dest[x] == movimento.O[x]) && (dest[y] == movimento.O[y]) && (movimento.iO == 1)))
        || (((dest[x] == movimento.NE[x]) && (dest[y] == movimento.NE[y]) && (movimento.iNE == 1)))
        || (((dest[x] == movimento.SE[x]) && (dest[y] == movimento.SE[y]) && (movimento.iSE == 1)))
        || (((dest[x] == movimento.SO[x]) && (dest[y] == movimento.SO[y]) && (movimento.iSO == 1)))
        || (((dest[x] == movimento.NO[x]) && (dest[y] == movimento.NO[y]) && (movimento.iNO == 1)))) {
            return true;            
        } else {
            if ((dest[x] == captura.N[x]) && (dest[y] == captura.N[y]) && (movimento.iN == -1) && (captura.iN == 1)) {
                capturar_peca(movimento.N, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.S[x]) && (dest[y] == captura.S[y]) && (movimento.iS == -1) && (captura.iS == 1)) {
                capturar_peca(movimento.S, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.E[x]) && (dest[y] == captura.E[y]) && (movimento.iE == -1) && (captura.iE == 1)) {
                capturar_peca(movimento.E, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.O[x]) && (dest[y] == captura.O[y]) && (movimento.iO == -1) && (captura.iO == 1)) {
                capturar_peca(movimento.O, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.NE[x]) && (dest[y] == captura.NE[y]) && (movimento.iNE == -1) && (captura.iNE == 1)) {
                capturar_peca(movimento.NE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SE[x]) && (dest[y] == captura.SE[y]) && (movimento.iSE == -1) && (captura.iSE == 1)) {
                capturar_peca(movimento.SE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SO[x]) && (dest[y] == captura.SO[y]) && (movimento.iSO == -1) && (captura.iSO == 1)) {
                capturar_peca(movimento.SO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.NO[x]) && (dest[y] == captura.NO[y]) && (movimento.iNO == -1) && (captura.iNO == 1)) {
                capturar_peca(movimento.NO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            puts("Destino invalido...");
            sleep(2);
            return false;
        }
    } else { // linha ímpar
        if ((((dest[x] == movimento.NE[x]) && (dest[y] == movimento.NE[y]) && (movimento.iNE == 1)))
        || (((dest[x] == movimento.SE[x]) && (dest[y] == movimento.SE[y]) && (movimento.iSE == 1)))
        || (((dest[x] == movimento.SO[x]) && (dest[y] == movimento.SO[y]) && (movimento.iSO == 1)))
        || (((dest[x] == movimento.NO[x]) && (dest[y] == movimento.NO[y]) && (movimento.iNO == 1)))) {
            return true;            
        } else {
            if ((dest[x] == captura.NE[x]) && (dest[y] == captura.NE[y]) && (movimento.iNE == -1) && (captura.iNE == 1)) {
                capturar_peca(movimento.NE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SE[x]) && (dest[y] == captura.SE[y]) && (movimento.iSE == -1) && (captura.iSE == 1)) {
                capturar_peca(movimento.SE, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.SO[x]) && (dest[y] == captura.SO[y]) && (movimento.iSO == -1) && (captura.iSO == 1)) {
                capturar_peca(movimento.SO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            if ((dest[x] == captura.NO[x]) && (dest[y] == captura.NO[y]) && (movimento.iNO == -1) && (captura.iNO == 1)) {
                capturar_peca(movimento.NO, matriz_posicao, pecas_jog1, pecas_jog2);
                return true;
            }
            puts("Destino invalido...");
            sleep(2);
            return false;
        }
    }

    // Se não caiu em nenhuma das validações aí em cima...
    puts("Destino estranho... Verificar");
    sleep(2);
    return false;
}