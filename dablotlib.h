#ifndef DABLOTLIB_H
#define DABLOTLIB_H

bool validar_alcance(const int[*], const char[TAM_X_TAB][TAM_Y_TAB], pontoCardeal*, pontoCardeal*);
bool validar_destino(const int[*], const int[*], char[TAM_X_TAB][TAM_Y_TAB], pontoCardeal, pontoCardeal, char[*], char[*]);
bool validar_peca(const int*, const int[*], const char[TAM_X_TAB][TAM_Y_TAB]);
bool verificar_desistencia(int, char[*], char[*], size_t, char[*], char[*], size_t);
bool verificar_pecas_livres(char[TAM_X_TAB][TAM_Y_TAB], const int*, int[*], pontoCardeal*, pontoCardeal*);
char menu_inicial(void);
char menu_pausa(void);
int carregar_jogo(char[TAM_X_TAB][TAM_Y_TAB], char[*], char[*], char[*], char[*], int*, size_t, bool*);
int pedir_entrada(const int*, int[*], char[*], char[*]);
int salvar_jogo(char[TAM_X_TAB][TAM_Y_TAB], char[*], char[*], char[*], char[*], int*, size_t);
int sortear_jogador(void);
int verificar_vetor_pecas(char[*], char[*], size_t, int*);
void capturar_peca(int[*], char[TAM_X_TAB][TAM_Y_TAB], char[*], char[*]);
void comecar_jogo(char[*], char[*], bool*);
void fazer_jogada(char[TAM_X_TAB][TAM_Y_TAB], const int[*], const int [*]);
void imprimir_tabuleiro(const char[TAM_X_TAB][TAM_Y_TAB]);
void inicializar_matriz_posicao(char[*], char[*], size_t, char[TAM_X_TAB][TAM_Y_TAB]);
void inicializar_vetor_pecas(char[*], char[*], size_t);
void pedir_destino(int[*]);
void reiniciar_partida(char[TAM_X_TAB][TAM_Y_TAB], char[*], char[*], size_t);
void trocar_turno(int*);
void tutorial(void);

#endif