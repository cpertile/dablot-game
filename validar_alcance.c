bool validar_alcance(const int peca[], const char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], pontoCardeal * movimento, pontoCardeal * captura) {
    // TODO: Criar struct pontos_cardeais; pontos_subcardeais (?)
    const int x = 0, y = 1;
    // Retornar true se a peça pode se mover. Se ela não puder, retornar mensagem de erro e false

    // Pesquisar a matriz nos pontos cardeais em volta da peça e registrar na flag correspondente:
        // 1 se estiver livre
        // 0 se estiver ocupada por peça amiga
        // -1 se estiver ocupada por peça inimiga
    // As peças próximas às bordas precisam de validação diferente para não sair da matriz
    // Peças em linhas pares têm 8 posições de movimento e de captura
    // Peças em linhas ímpares têm 4 posições de movimento e de captura

    // Posições cardeais de movimento
    movimento->N[x] = peca[x]; movimento->N[y] = (peca[y] - 2);
    movimento->S[x] = peca[x]; movimento->S[y] = (peca[y] + 2);
    movimento->E[x] = (peca[x] + 2); movimento->E[y] = peca[y];
    movimento->O[x] = (peca[x] - 2); movimento->O[y] =  peca[y];
    movimento->NE[x] = (peca[x] + 1); movimento->NE[y] = (peca[y] - 1);
    movimento->SE[x] = (peca[x] + 1); movimento->SE[y] = (peca[y] + 1);
    movimento->SO[x] = (peca[x] - 1); movimento->SO[y] = (peca[y] + 1);
    movimento->NO[x] = (peca[x] - 1); movimento->NO[y] = (peca[y] - 1);
    movimento->iN = 0, movimento->iS = 0, movimento->iE = 0, movimento->iO = 0, movimento->iNE = 0, movimento->iSE = 0, movimento->iSO = 0, movimento->iNO = 0;

    // Posições cardeais de captura
    captura->N[x] = peca[x]; captura->N[y] = (peca[y] - 4);
    captura->S[x] = peca[x]; captura->S[y] = (peca[y] + 4);
    captura->E[x] = (peca[x] + 4); captura->E[y] = peca[y];
    captura->O[x] = (peca[x] - 4); captura->O[y] = peca[y];
    captura->NE[x] = (peca[x] + 2); captura->NE[y] = (peca[y] - 2);
    captura->SE[x] = (peca[x] + 2); captura->SE[y] = (peca[y] + 2);
    captura->SO[x] = (peca[x] - 2); captura->SO[y] = (peca[y] + 2);
    captura->NO[x] = (peca[x] - 2); captura->NO[y] = (peca[y] - 2);
    captura->iN = 0, captura->iS = 0, captura->iE = 0, captura->iO = 0, captura->iNE = 0, captura->iSE = 0, captura->iSO = 0, captura->iNO = 0;

    // 1ª Parte: validar se as posições cardeais de movimento estão dentro do tabuleiro e se possuem um espaço
    // Se o conteúdo não for um espaço, verificar se é uma inimiga. Se for, registrar -1 na posição
    // Linhas de índice par = todas as coordenadas (N, S, E, O, NE, SE, SO e NO)
    // Linhas de índice ímpar = apenas as coordenadas subcardeais (NE, SE, SO e NO)
    // Jogador 1 verificar se { F, f, c }
    // Jogador 2 verificar se { R, p, g }

    if (peca[y] % 2 == 0) {
        if (movimento->N[y] >= LIM_SUPERIOR) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'F': case 'f': case 'c': movimento->iN = -1;
                }
                case 'p':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'f': case 'c': movimento->iN = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'c': movimento->iN = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'R': case 'p': case 'g': movimento->iN = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'p': case 'g': movimento->iN = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->N[x]][movimento->N[y]]) {
                    case ' ': movimento->iN = 1; break;
                    case 'g': movimento->iN = -1; break;
                }
            }
        }
        if (movimento->S[y] <= LIM_INFERIOR) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'F': case 'f': case 'c': movimento->iS = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'f': case 'c': movimento->iS = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'c': movimento->iS = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'R': case 'p': case 'g': movimento->iS = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'p': case 'g': movimento->iS = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->S[x]][movimento->S[y]]) {
                    case ' ': movimento->iS = 1; break;
                    case 'g': movimento->iS = -1; break;
                }
            }
        }
        if (movimento->E[x] <= LIM_DIREITO) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'f': case 'c': movimento->iE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'c': movimento->iE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'p': case 'g': movimento->iE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->E[x]][movimento->E[y]]) {
                    case ' ': movimento->iE = 1; break;
                    case 'g': movimento->iE = -1; break;
                }
            }
        }
        if (movimento->O[x] >= LIM_ESQUERDO) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'f': case 'c': movimento->iO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'c': movimento->iO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'p': case 'g': movimento->iO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->O[x]][movimento->O[y]]) {
                    case ' ': movimento->iO = 1; break;
                    case 'g': movimento->iO = -1; break;
                }
            }
        }
        if ((movimento->NE[x] <= LIM_DIREITO) && (movimento->NE[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'c': movimento->iNE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'g': movimento->iNE = -1; break;
                }
            }
        }
        if ((movimento->SE[x] <= LIM_DIREITO) && (movimento->SE[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'c': movimento->iSE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'g': movimento->iSE = -1; break;
                }
            }
        }
        if ((movimento->SO[x] >= LIM_ESQUERDO) && (movimento->SO[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'c': movimento->iSO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'g': movimento->iSO = -1; break;
                }
            }
        }
        if ((movimento->NO[x] >= LIM_ESQUERDO) && (movimento->NO[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'c': movimento->iNO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'g': movimento->iNO = -1; break;
                }
            }
        }
    } else { // Linha ímpar
        if ((movimento->NE[x] <= LIM_DIREITO) && (movimento->NE[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'f': case 'c': movimento->iNE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'c': movimento->iNE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'p': case 'g': movimento->iNE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NE[x]][movimento->NE[y]]) {
                    case ' ': movimento->iNE = 1; break;
                    case 'g': movimento->iNE = -1; break;
                }
            }
        }
        if ((movimento->SE[x] <= LIM_DIREITO) && (movimento->SE[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'f': case 'c': movimento->iSE = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'c': movimento->iSE = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'p': case 'g': movimento->iSE = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SE[x]][movimento->SE[y]]) {
                    case ' ': movimento->iSE = 1; break;
                    case 'g': movimento->iSE = -1; break;
                }
            }
        }
        if ((movimento->SO[x] >= LIM_ESQUERDO) && (movimento->SO[y] <= LIM_INFERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'f': case 'c': movimento->iSO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'c': movimento->iSO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'p': case 'g': movimento->iSO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->SO[x]][movimento->SO[y]]) {
                    case ' ': movimento->iSO = 1; break;
                    case 'g': movimento->iSO = -1; break;
                }
            }
        }
        if ((movimento->NO[x] >= LIM_ESQUERDO) && (movimento->NO[y] >= LIM_SUPERIOR)) {
            switch(matriz_posicao[peca[x]][peca[y]]) {
                case 'R':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'F': case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'p':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'f': case 'c': movimento->iNO = -1; break;
                }
                case 'g':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'c': movimento->iNO = -1; break;
                }
                case 'F':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'R': case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'f':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'p': case 'g': movimento->iNO = -1; break;
                }
                case 'c':
                switch(matriz_posicao[movimento->NO[x]][movimento->NO[y]]) {
                    case ' ': movimento->iNO = 1; break;
                    case 'g': movimento->iNO = -1; break;
                }
            }
        }
    }

    // 2ª Parte: validar se as posições de captura estão disponíveis, caso sejam necessárias
    // Se registrar -1 em alguma posição cardeal, verificar posição de captura correspondente:
        // Se tiver um espaço, habilitar (true)
        // Se não tiver espaço, desabilitar (false)

    if (peca[y] % 2 == 0) {
        if ((movimento->iN == -1) && (captura->N[y] >= LIM_SUPERIOR) && (matriz_posicao[captura->N[x]][captura->N[y]] == ' ')) captura->iN = 1;
        if ((movimento->iS == -1) && (captura->S[y] <= LIM_INFERIOR) && (matriz_posicao[captura->S[x]][captura->S[y]] == ' ')) captura->iS = 1;
        if ((movimento->iE == -1) && (captura->E[x] <= LIM_DIREITO) && (matriz_posicao[captura->E[x]][captura->E[y]] == ' ')) captura->iE = 1;
        if ((movimento->iO == -1) && (captura->O[x] >= LIM_ESQUERDO) && (matriz_posicao[captura->O[x]][captura->O[y]] == ' ')) captura->iO = 1;
        if ((movimento->iNE == -1) && (captura->NE[x] <= LIM_DIREITO) && (captura->NE[y] >= LIM_SUPERIOR)
            && (matriz_posicao[captura->NE[x]][captura->NE[y]] == ' ')) captura->iNE = 1;
        if ((movimento->iSE == -1) && (captura->SE[x] <= LIM_DIREITO) && (captura->SE[y] <= LIM_INFERIOR)
            && (matriz_posicao[captura->SE[x]][captura->SE[y]] == ' ')) captura->iSE = 1;
        if ((movimento->iSO == -1) && (captura->SO[x] >= LIM_ESQUERDO) && (captura->SO[y] <= LIM_INFERIOR)
            && (matriz_posicao[captura->SO[x]][captura->SO[y]] == ' ')) captura->iSO = 1;
        if ((movimento->iNO == -1) && (captura->NO[x] >= LIM_ESQUERDO) && (captura->NO[y] >= LIM_SUPERIOR)
            && (matriz_posicao[captura->NO[x]][captura->NO[y]] == ' ')) captura->iNO = 1;
    } else { // Linha ímpar
        if ((captura->iNE == -1) && (captura->NE[x] <= LIM_DIREITO) && (captura->NE[y] >= LIM_SUPERIOR) && (matriz_posicao[captura->NE[x]][captura->NE[y]] == ' ')) captura->iNE = 1;
        if ((captura->iSE == -1) && (captura->SE[x] <= LIM_DIREITO) && (captura->SE[y] <= LIM_INFERIOR) && (matriz_posicao[captura->SE[x]][captura->SE[y]] == ' ')) captura->iSE = 1;
        if ((captura->iSO == -1) && (captura->SO[x] >= LIM_ESQUERDO) && (captura->SO[y] <= LIM_INFERIOR) && (matriz_posicao[captura->SO[x]][captura->SO[y]] == ' ')) captura->iSO = 1;
        if ((captura->iNO == -1) && (captura->NO[x] >= LIM_ESQUERDO) && (captura->NO[y] >= LIM_SUPERIOR) && (matriz_posicao[captura->NO[x]][captura->NO[y]] == ' ')) captura->iNO = 1;
    }

    // Se todas as posições cardeais de movimento e captura forem 0 ou -1, o movimento da peça é impossível
    if (((movimento->iN < 1) && (movimento->iS < 1) && (movimento->iE < 1) && (movimento->iO < 1) && (movimento->iNE < 1) && (movimento->iSE < 1) && (movimento->iSO < 1) && (movimento->iNO < 1))
        && ((captura->iN < 1) && (captura->iS < 1) && (captura->iE < 1) && (captura->iO < 1) && (captura->iNE < 1) && (captura->iSE < 1) && (captura->iSO < 1) && (captura->iNO < 1))) {
        return false;
    } else {        
    return true;
    }
}