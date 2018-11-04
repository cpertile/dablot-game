void reiniciar_partida(char matriz_posicao[TAM_X_TAB][TAM_Y_TAB], char pecas_jog1[], char pecas_jog2[], size_t tam) {
    system("clear");
    puts("Reiniciando, aguarde...");
    sleep(1);
    inicializar_vetor_pecas(pecas_jog1, pecas_jog2, TAM_VETOR);
    inicializar_matriz_posicao(pecas_jog1, pecas_jog2, TAM_VETOR, matriz_posicao);
}