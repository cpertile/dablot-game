int sortear_jogador(void) {
    srand(time(0));
    int sorteio = rand() % 2 + 1;
    puts(CNZA "Vamos sortear quem vai comecar jogando...");
    sleep(3);
    printf("O jogador %d foi sorteado para comecar dessa vez...\n", sorteio);
    sleep(2);
    return sorteio;
}