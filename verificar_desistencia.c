bool verificar_desistencia(int jog_atual, char nome_jogador1[], char nome_jogador2[], size_t tam_nome,
    char pecas_jog1[], char pecas_jog2[], size_t tam_vetor_pecas) {
    // Verificar nos vetores peças se o jogador perdeu sua peça mais significativa ('R' ou 'F') e perguntar se deseja desistir do jogo
    // Se for jogador 1, vai olhar para o vetor de peças 1 na posição do 'R'
    // Jogador 2, olha o vetor de peças 2 na posição 'F'
    char escolha = '?';

    if (jog_atual == 1) {
        if (pecas_jog1[tam_vetor_pecas-1] != 'R') {
            while ((escolha != 'S') && (escolha != 'N')) {
                printf(VRML "%s" CNZA ", o Rei foi eliminado... Deseja desistir do jogo? [ (S) - (N) ]", nome_jogador1);
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                switch (escolha) {
                    case 'S': return true;
                    case 'N': return false;
                    default: continue;
                }
            }
        }
    } else {
        if (pecas_jog2[tam_vetor_pecas-1] != 'F') {
            while ((escolha != 'S') && (escolha != 'N')) {
                printf(VERD "%s" CNZA ", o Fazendeiro foi eliminado... Deseja desistir do jogo? [ (S) - (N) ]", nome_jogador2);
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
                switch (escolha) {
                    case 'S': return true;
                    case 'N': return false;
                    default: continue;
                }
            }
        }
    }
    return false;
}