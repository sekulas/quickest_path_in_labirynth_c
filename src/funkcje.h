#ifndef _FUNKCJE_H_
#define _FUNKCJE_H_

#define BUFSIZE 12 

/*BUFSIZE - MAKSYMALNA WIELKOSC LABIRYNTU (WARNING JAK DASZ 5, A MASZ 5X5 LABIRYNT TO DEOS NOT WORK)
 *n, m - wymiary labiryntu
 *seen - tablica sprawdzajaca czy juz bylismy w danym wezle
 *labirynt - tablica przechowujaca zmienne z pliku tekstowego
 *wagi - tablica dwuwymiarowa z wagami
 *graf - macierz sasiedztwa okreslajaca polaczenia miedzy wiercholkami
 *cy, cx - zmienne przchowujace wartosci dla ktorej komorki tablicy (dla jakiego wezla zostala funkcja wywolana)
*/


void vizualizer(int n, int m, int labirynt[BUFSIZE][BUFSIZE]);
void graphcreator(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int n, int m);

void up(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m);
void down(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m);
void left(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m);
void right(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m);

void dijkstra(int *seen, int **graf, double **wagi, int n, int m, double length, int node, double* minimum);

#endif
