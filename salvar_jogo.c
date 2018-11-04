int salvar_jogo(char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], char nome_jogador1[], char pecas_jog1[], char nome_jogador2[], char pecas_jog2[], int *jog_atual, size_t tam) {
    char nome_arquivo[34];
    char caractere_matriz;

    printf("Escolha um nome para o arquivo de jogo salvo: ");
    fpurge(stdin);
    fgets(nome_arquivo, 29, stdin);
    int i, j;
    for (i = 0; i < 29; i++) {
        if (nome_arquivo[i] == '\n') {
            nome_arquivo[i] = '\0';
            break;
        }
    }
    strcat(nome_arquivo, ".txt");
    // Tenta acessar o arquivo para ver se ele existe. Se existe, apaga antes de escrever novamente
    int arq_existe = access(nome_arquivo, W_OK);
    if (arq_existe) {
        remove(nome_arquivo);
    }
    FILE * jogosalvo = fopen(nome_arquivo, "w");
    if (jogosalvo == 0) {
        perror("ERRO: nao foi possivel criar o arquivo...");
        return 0;
    }

    // Salva a matriz da forma que o computador enxerga
    for (j = 0; j < TAM_Y_TAB; ++j) {
        for (i = 0; i < TAM_X_TAB; ++i) {
            caractere_matriz = matriz_posicao[i][j];
            fprintf(jogosalvo, "%c", caractere_matriz);
        }
        caractere_matriz = '\n';
        fprintf(jogosalvo, "%c", caractere_matriz);
    }
    
    // Salva os nomes dos jogadores, seus vetores de peças e 
    fprintf(jogosalvo, "%s\n", nome_jogador1);
    fprintf(jogosalvo, "%s\n", pecas_jog1);
    fprintf(jogosalvo, "%s\n", nome_jogador2);
    fprintf(jogosalvo, "%s\n", pecas_jog2);
    fprintf(jogosalvo, "%d", *jog_atual);

    fclose(jogosalvo);
    puts("Jogo salvo com sucesso...");
    sleep(1);
    return 1;
}