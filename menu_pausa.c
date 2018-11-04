char menu_pausa(void) {
    char escolha = '?';
    while (escolha == '?') {
        system("clear");
        puts(CNZA "                  ╔════════════════╗");
        puts(CNZA "                  ║" RST "  JOGO PAUSADO  " CNZA "║");
        puts(CNZA "                  ╚════════════════╝");
        puts(CNZA "  ╔═════════════════════════════════════════════════╗");
        puts(CNZA "  ║" RST "  (R) Reiniciar partida com os mesmos jogadores  " CNZA "║");
        puts(CNZA "  ║" RST "  (S) Salvar jogo para continuar depois          " CNZA "║");
        puts(CNZA "  ║" RST "  (C) Carregar jogo salvo anteriormente          " CNZA "║");
        puts(CNZA "  ║" RST "  (X) Sair da partida e recomeçar                " CNZA "║");
        puts(CNZA "  ║" RST "  (V) Voltar ao jogo atual                       " CNZA "║");
        puts(CNZA "  ║" RST "  (0) Sair do jogo                               " CNZA "║");
        puts(CNZA "  ╚═════════════════════════════════════════════════╝");  
        putchar('\n');
        fpurge(stdin);
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        switch(escolha) {
            case 'R': escolha = 'R'; break;
            case 'S': escolha = 'S'; break;
            case 'C': escolha = 'C'; break;
            case 'X': escolha = 'X'; break;
            case 'V': escolha = 'V'; break;
            case '0': escolha = '0'; break;
            default:
                puts("Escolha uma das opcoes...");
                escolha = '?';
                sleep(1);
                continue;
        }
    }
    return escolha;
}