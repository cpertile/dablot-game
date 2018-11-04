void pedir_destino(int dest[]) {
    const int x = 0, y = 1;
    // Pedir as coordenadas de destino para o jogador
    char coord_x_l_dest;
    int coord_x_n_dest, coord_y_dest;

    printf("Digite as coordenadas de destino: ");
    scanf(" %c", &coord_x_l_dest);
    scanf("%d", &coord_y_dest);
    coord_x_l_dest = toupper(coord_x_l_dest);
    switch(coord_x_l_dest) {
        case 'A': coord_x_n_dest = 0; break;
        case 'B': coord_x_n_dest = 1; break;
        case 'C': coord_x_n_dest = 2; break;
        case 'D': coord_x_n_dest = 3; break;
        case 'E': coord_x_n_dest = 4; break;
        case 'F': coord_x_n_dest = 5; break;
        case 'G': coord_x_n_dest = 6; break;
        case 'H': coord_x_n_dest = 7; break;
        case 'I': coord_x_n_dest = 8; break;
        case 'J': coord_x_n_dest = 9; break;
        case 'K': coord_x_n_dest = 10; break;
        default: coord_x_n_dest = 11;
    }
    coord_y_dest -= 1;

    // Vetor com as coordenadas de destino
    dest[x] = coord_x_n_dest;
    dest[y] = coord_y_dest;
}