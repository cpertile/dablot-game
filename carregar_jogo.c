int carregar_jogo(char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], char nome_jogador1[], char pecas_jog1[], char nome_jogador2[], char pecas_jog2[], int *jog_atual,
    size_t tam, bool *game) {
    char caractere, descarte;
    char nome_arquivo[34];
    int i, j;

    printf("Digite o nome do arquivo salvo: ");
    fpurge(stdin);
    fgets(nome_arquivo, 29, stdin);
    for (i = 0; i < 29; i++) {
        if (nome_arquivo[i] == '\n') {
            nome_arquivo[i] = '\0';
            break;
        }
    }
    strcat(nome_arquivo, ".txt");
    FILE * jogosalvo = fopen(nome_arquivo, "r");
    if (jogosalvo == 0) {
        perror("ERRO: nao foi possivel abrir o arquivo...");
        return 0;
    }

    // Carregar matriz
    for (j = 0; j < TAM_Y_TAB; ++j) {
        for (i = 0; i < TAM_X_TAB; ++i) {
            caractere = fgetc(jogosalvo);
            if (caractere != '\n') {
                matriz_posicao[i][j] = caractere;
            }
        }
        descarte = fgetc(jogosalvo);
    }

    // Carregar nome do jogador 1
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            nome_jogador1[i] = caractere;
            i++;
        } else {
            nome_jogador1[i] = '\0';
        }
    } while (caractere != '\n');

    // Carregar peças do jogador 1
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            pecas_jog1[i] = caractere;
            i++;
        } else {
            descarte = caractere;
        }
    } while (caractere != '\n');

    // Carregar nome do jogador 2
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            nome_jogador2[i] = caractere;
            i++;
        } else {
            nome_jogador2[i] = '\0';
        }
    } while (caractere != '\n');

    // Carregar peças do jogador 2
    i = 0;
    do {
        caractere = fgetc(jogosalvo);
        if (caractere != '\n') {
            pecas_jog2[i] = caractere;
            i++;
        } else {
            descarte = caractere;
        }
    } while (caractere != '\n');

    // Carregadr jogador atual. O - '0' eh usado para converter de char '1' para inteiro 1
    char jog_lido = fgetc(jogosalvo);
    *jog_atual = jog_lido - '0';

    fclose(jogosalvo);
    puts("Jogo carregado, iniciando...");
    *game = true;
    sleep(1);
    return 1;
}