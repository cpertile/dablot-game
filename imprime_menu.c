#include <stdlib.h>
#include <stdio.h>
void gotoxy(int, int);

int main(void) {
	char tabuleiro[21,25];

	system("clear");

	for (i = 0; i < 21; ++i) {
		for (j = 0; j < 21; ++j) {
			gotoxy(i,j);
			printf("%c", tabuleiro[i,j]); // usar putchar(tabuleiro[i,j]) ????
		}
	}
		printf("*---*---*---*---*---*\n);
				|\\ /|\\ /|\\ /|\\ /|\\ /|\n
				| * | * | * | * | * |\n
				|/ \\|/ \\|/ \\|/ \\|/ \\|\n
				*---*---*---*---*---*\n
				|\\ /|           |\\ /|\n
				| * |           | * |\n
				|/ \\|           |/ \\|\n
				*---*           *---*\n
				|\\ /|           |\\ /|\n
				| * |   Dablot  | * |\n
				|/ \\|           |/ \\|\n
				*---*           *---*\n
				|\\ /|           |\\ /|\n
				| * |   v0.1    | * |\n
				|/ \\|           |/ \\|\n
				*---*           *---*\n
				|\\ /|           |\\ /|\n
				| * |           | * |\n
				|/ \\|           |/ \\|\n
				*---*---*---*---*---*\n
				|\\ /|\\ /|\\ /|\\ /|\\ /|\n
				| * | * | * | * | * |\n
				|/ \\|/ \\|/ \\|/ \\|/ \\|\n
				*---*---*---*---*---*");

	return EXIT_SUCCESS;
}

void gotoxy(int x,int y){
	printf("%c[%d;%df",0x1B,y,x);
}

/*
void imprime_menu(void) {
	textmode(C80);

}*/