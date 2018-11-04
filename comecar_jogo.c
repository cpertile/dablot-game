void comecar_jogo(char nome_jogador1[], char nome_jogador2[], bool *game) {
    *game = true;
    puts("Começando um novo jogo!");
    puts("Primeiro vamos conhecer os jogadores...");
    puts("Qual o nome do jogador 1, que vai comandar o [" VRML "R" CNZA "]ei, o [" VRML "p" CNZA "]ríncipe e os [" VRML "g" CNZA "]uerreiros?" VRML);
    fpurge(stdin);
    fgets(nome_jogador1, TAM_NOME, stdin);
    // Ao usar fgets, o caracter \n é adicionado à string. O laço abaixo troca pelo caracter que indica fim de string.
    int i;
    for (i = 0; i < TAM_NOME; i++) {
        if (nome_jogador1[i] == '\n') {
            nome_jogador1[i] = '\0';
            break;
        }
    }
    puts(CNZA "E o jogador 2, que vai comandar o [" VERD "F" CNZA "]azendeiro, seu [" VERD "f" CNZA "]ilho e os [" VERD "c" CNZA "]amponeses?" VERD);
    fpurge(stdin);
    fgets(nome_jogador2, TAM_NOME, stdin);
    i = 0;
    for (i = 0; i < TAM_NOME; i++) {
        if (nome_jogador2[i] == '\n') {
            nome_jogador2[i] = '\0';
            break;
        }
    }
}