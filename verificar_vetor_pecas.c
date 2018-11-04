int verificar_vetor_pecas(char pecas_jog1[], char pecas_jog2[], size_t tam, int *jog_atual) {
    int i;
    int perdedor = 0;
    for (i = 0; i < tam; ++i) {
        if (*jog_atual == 1) {
            if (pecas_jog1[i] != ' ') {
                return 1;
            } else {
                perdedor = 1;
                continue;
            }
        } else { // Jogador 2
            if (pecas_jog2[i] != ' ') {
                return 1;
            } else {
                perdedor = 2;
                continue;
            }
        }
    }
    printf("O jogador %d ficou sem pecas e perdeu! Fim de jogo!\n", perdedor);
    sleep(2);
    return 0;
}