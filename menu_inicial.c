char menu_inicial() {
    char escolha = '?';

    // Limpa a tela e imprime o menu inicial do jogo
    system("clear");
    putchar('\n');
    puts(CNZA "   ╔══════════════════════════════╗");
    puts(CNZA "   ║" RST " Bem-vindo(a) ao jogo Dablot!" CNZA " ║");
    puts(CNZA "   ╚══════════════════════════════╝");
    putchar('\n');
    while (escolha == '?') {
        puts(CNZA " ╔══════════════════════════════════╗");
        puts(CNZA " ║" RST " Digite (A) para Aprender a jogar " CNZA "║");
        puts(CNZA " ║" RST "      Digite (I) para Iniciar     " CNZA "║");
        puts(CNZA " ║" RST "       Digite (S) para Sair       " CNZA "║");
        puts(CNZA " ╚══════════════════════════════════╝");
        putchar('\n');
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        switch(escolha) {
            case 'A': return escolha;
            case 'I':
                puts(CNZA " ╔═════════════════════════════════════════════════════╗");
                puts(CNZA " ║" RST " Deseja um Novo Jogo (N) ou Carregar Jogo Salvo (C)? " CNZA "║");
                puts(CNZA " ╚═════════════════════════════════════════════════════╝");
                putchar('\n');
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                switch(escolha) {
                    case 'N': return escolha;
                    case 'C': return escolha;
                    default: escolha = '?'; continue;
                }
            case 'S': return escolha;
            default: escolha = '?'; continue;
        }
    }
    return escolha;
}