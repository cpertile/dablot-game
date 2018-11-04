void tutorial(void) {
    // Explicar o que é o Dablot, mostrar o tabuleiro e explicar como jogar
    system("clear");
    printf(CNZA "Bem-vindo ao Dablot, um jogo de tabuleiro do sec XIX cuja história se passa\n"
                "no Extremo Norte da Suecia entre o Rei Sami, seu principe e seus guerreiros\n"
                "contra o Fazendeiro, seu filho e os camponeses...\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "A mecanica do Dablot eh similar ao jogo Damas, onde as pecas se movimentam\n"
                "uma 'casa' por vez, e capturam as pecas adversarias saltando por cima delas.\n");
    sleep(6);
    printf("  @╔═════════════════════════════════════════╗\n"
           "  @║     A  B  C  D  E  F  G  H  I  J  K     ║\n"
           "  @║  1 [g]---[g]---[g]---[g]---[g]---[g] 1  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  2  | [g] | [g] | [g] | [g] | [g] |  2  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  3 [g]---[g]---[g]---[g]---[g]---[g] 3  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  4  | [g] | [g] | [g] | [g] | [g] |  4  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  5 [g]---[g]---[g]---[g]---[g]---[g] 5  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  6  | [p] | [ ] | [ ] | [ ] | [ ] |  6  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  7 [R]---[ ]---[ ]---[ ]---[ ]---[F] 7  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║  8  | [ ] | [ ] | [ ] | [ ] | [f] |  8  ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║  9 [c]---[c]---[c]---[c]---[c]---[c] 9  ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║ 10  | [c] | [c] | [c] | [c] | [c] |  10 ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║ 11 [c]---[c]---[c]---[c]---[c]---[c] 11 ║\n"
           "  @║     | \\ / | \\ / | \\ / | \\ / | \\ / |     ║\n"
           "  @║ 12  | [c] | [c] | [c] | [c] | [c] |  12 ║\n"
           "  @║     | / \\ | / \\ | / \\ | / \\ | / \\ |     ║\n"
           "  @║ 13 [c]---[c]---[c]---[c]---[c]---[c] 13 ║\n"
           "  @║     A  B  C  D  E  F  G  H  I  J  K     ║\n"
           "  @╚═════════════════════════════════════════╝\n");
    printf(CNZA "Este eh o tabuleiro do Dablot. Nele, as pecas se movimentam\n"
                "usando os espacos [ ] como casa. Cada peca pode andar 1 casa\n"
                "para qualquer direcao, as vezes tendo 4 e as vezes 8 direcoes\n"
                "possiveis para se locomover...\n");
    sleep(10);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Cada jogador tem um movimento por vez. A cada rodada,\n"
                "o computador pergunta as coordenadas da peca que o jogador\n"
                "deseja mover, e depois pergunta o destino.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "O jogador deve inserir as coordenadas como aparecem na tela:\n"
                "'A7', ou 'a7', sao coordenadas validas para uma peca.\n"
                "'B8' ou 'b8' eh um destino valido para essa peca.\n");
    sleep(6);
    printf(CNZA "A peca ira se mover pelo tabuleiro dessa maneira:\n"
                "@╔═════════════════════════════════════════╗\n"
                "@║     A  B  C                 A  B  C     ║\n"
                "@║  7 [R]---[ ]   ->    @║  7 [ ]---[ ]    ║\n"
                "@║     | \\ / |    ->    @║     | \\ / |     ║\n"
                "@║  8  | [ ] |    ->    @║  8  | [R] |     ║\n"
                "@║     | / \\ |    ->    @║     | / \\ |     ║\n"
                "@║  9 [c]---[c]   ->    @║  9 [c]---[c]    ║\n"
                "@║     A  B  C                 A  B  C     ║\n"
                "@╚═════════════════════════════════════════╝\n");
    sleep(10);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Para capturar uma peca do adversario, o destino informado\n"
                "deve ser uma coordenada que faca a peca dar um 'salto' sobre\n"
                "a peca adversario, como no jogo de Damas.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "As pecas possuem niveis diferentes, sendo que so podem\n"
                "capturar pecas de nivel igual ou inferior:\n"
                "- O Rei e o Fazendeiro tem nivel 3, o que significa que\n"
                "podem eliminar qualquer peca do time adversario.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "-O filho do fazendeiro e o principe sao nivel 2,\n"
                "enquanto os camponeses e guerreiros sao nivel 1...\n");
    sleep(4);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Ganha o jogador que:\n"
                "-Eliminar todas as pecas do adversario.\n"
                "-Trancar todas as pecas do adversario.\n");
    sleep(4);
    puts("════════════════════════════════════════════════════════");
    printf(CNZA "Além disso, caso a peca mais significativa de um jogador seja eliminada,\n"
                "ele tera a opcao de desistir ou continuar jogando.\n");
    sleep(6);
    puts("════════════════════════════════════════════════════════");
    char escolha = '?';
    while (escolha != 'N') {
        printf(CNZA "E ai, vamos jogar? Quando terminar de ler a explicacao,\n"
                    "eh soh digitar 'N' para comecar um Novo Jogo :)\n");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
    }
    system("clear");
}