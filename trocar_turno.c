void trocar_turno(int *jog_atual) {
    if (*jog_atual == 1) {
        *jog_atual = 2;
    } else {
        *jog_atual = 1;
    }
}