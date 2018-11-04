void inicializar_vetor_pecas(char V1[], char V2[], size_t tam) {
    // Preenche o vetor passado com as peças correspondentes ao jogador 1 ou 2
    int i;

    for (i = 0; i < tam; ++i) {
        if (i < tam-2) {
            V1[i] = 'g';
            V2[i] = 'c';
        } else if (i < tam-1) {
            V1[i] = 'p';
            V2[i] = 'f';
        } else {
            V1[i] = 'R';
            V2[i] = 'F';
        }
    }
}