#include "funkcje.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>

#define BUFSIZE 12

void vizualizer(int n, int m, int labirynt[BUFSIZE][BUFSIZE]){

    int i;
    int j;

    for(i = 0; i < 2 * n; i++) {
            if( i > 1 )
                printf("_");
            else 
                printf(" ");
    }
        
    printf("\n");

    for(i = 0; i < m; i++) {

        for(j = 0; j < n; j++) {

            if(j == 0) 
                printf("|");
                

            if(labirynt[i][j] == 3) printf("_|");
            else if(labirynt[i][j] == 2) printf(" |");
            else if(labirynt[i][j] == 1) printf("__");
            else printf("  ");

        }

        printf("\n");

    }

}

void graphcreator(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int n, int m) {

    seen[0]++;

    right(seen, graf, wagi, labirynt, 0, 1, n, m);
    down(seen, graf, wagi, labirynt, 1, 0, n, m);

    /*
    for(int i = 0; i < n * m; i++) {

        printf("\n\nCurrnet: (%d)\n", i);

        for(int j = 0; j < n * m; j++) {

            if(graf[i][j] > 0) printf("--%g-->(%d)\n", wagi[i][j], j);

        }

    }
    */

}


	

void up(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m) {

    int ln = ((cy+1) * n) + cx;
    int cn = (cy * n) + cx;
    int lx = cx;
    int ly = cy + 1;

    if( labirynt[ cy ][ cx ] == 0 || labirynt[ cy ][ cx ] == 2 ) {

        graf[ ln ][ cn ] = 1;
        wagi[ ln ][ cn ] = (double)rand() / (RAND_MAX/10);
        graf[ cn ][ ln ] = 1;
        wagi[ cn ][ ln ] = wagi[ ln ][ cn ];

        if( seen[ cn ] == 1 )
            return;
        else
            seen[ cn ] = 1;

        if( cx != n - 1 ) right(seen, graf, wagi, labirynt, cy, cx + 1, n, m);
        if( cy != m - 1 ) down(seen, graf, wagi, labirynt, cy + 1, cx, n, m);
        if( cx != 0 ) left(seen, graf, wagi, labirynt, cy, cx - 1, n, m);
        if( cy != 0 ) up(seen, graf, wagi, labirynt, cy - 1, cx, n, m);
    } 

}

void down(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m) {

    int ln = ((cy-1) * n) + cx;
    int cn = (cy * n) + cx;
    int lx = cx;
    int ly = cy - 1;

    if( labirynt[ ly ][ lx ] == 0 || labirynt[ ly ][ lx ] == 2 ) {

        graf[ ln ][ cn ] = 1;
        wagi[ ln ][ cn ] = (double)rand() / (RAND_MAX/10);
        graf[ cn ][ ln ] = 1;
        wagi[ cn ][ ln ] = wagi[ ln ][ cn ];

        if( seen[ cn ] == 1 )
            return;
        else
            seen[ cn ] = 1;

        if( cx != n - 1 ) right(seen, graf, wagi, labirynt, cy, cx + 1, n, m);
        if( cy != m - 1 ) down(seen, graf, wagi, labirynt, cy + 1, cx, n, m);
        if( cx != 0 ) left(seen, graf, wagi, labirynt, cy, cx - 1, n, m);
        if( cy != 0 ) up(seen, graf, wagi, labirynt, cy - 1, cx, n, m);

    } 

}

void left(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m) {

    int ln = (cy * n) + cx + 1;
    int cn = (cy * n) + cx;
    int lx = cx + 1;
    int ly = cy;

    if( labirynt[ cy ][ cx ] == 0 || labirynt[ cy ][ cx ] == 1 ) {

        graf[ ln ][ cn ] = 1;
        wagi[ ln ][ cn ] = (double)rand() / (RAND_MAX/10);
        graf[ cn ][ ln ] = 1;
        wagi[ cn ][ ln ] = wagi[ ln ][ cn ];

        if( seen[ cn ] == 1 )
            return;
        else
            seen[ cn ] = 1;

        if( cx != n - 1 ) right(seen, graf, wagi, labirynt, cy, cx + 1, n, m);
        if( cy != m - 1 ) down(seen, graf, wagi, labirynt, cy + 1, cx, n, m);
        if( cx != 0 ) left(seen, graf, wagi, labirynt, cy, cx - 1, n, m);
        if( cy != 0 ) up(seen, graf, wagi, labirynt, cy - 1, cx, n, m);
    } 

}

void right(int *seen, int **graf, double **wagi, int labirynt[BUFSIZE][BUFSIZE], int cy, int cx, int n, int m) {

    int ln = (cy * n) + cx - 1;
    int cn = (cy * n) + cx;
    int lx = cx - 1;
    int ly = cy;

    if( labirynt[ ly ][ lx ] == 0 || labirynt[ ly ][ lx ] == 1 )  {

        graf[ ln ][ cn ] = 1;
        wagi[ ln ][ cn ] = (double)rand() / (RAND_MAX/10);
        graf[ cn ][ ln ] = 1;
        wagi[ cn ][ ln ] = wagi[ ln ][ cn ];

        if( seen[ cn ] == 1 )
            return;
        else
            seen[ cn ] = 1;

        if( cx != n - 1 ) right(seen, graf, wagi, labirynt, cy, cx + 1, n, m);
        if( cy != m - 1 ) down(seen, graf, wagi, labirynt, cy + 1, cx, n, m);
        if( cx != 0 ) left(seen, graf, wagi, labirynt, cy, cx - 1, n, m);
        if( cy != 0 ) up(seen, graf, wagi, labirynt, cy - 1, cx, n, m);
    }

}

void dijkstra(int *seen, int **graf, double **wagi, int n, int m, double length, int node, double* minimum) {
    int i, j;

    /*Obecny wierzcholek, oraz dlugosc ktora trzeba przebyc, aby sie do niego dostac*/
	printf("%d %g\n", node, length);

    /*Jesli to ostatni wierzcholek to:
      sprawdz czy dlugosc jest mniejsza od minimalnej
      jak dotad przebytej drogi oraz wypisz odwiedzone
      wierzcholki*/
	if(node == n * m - 1) {

		if(length < *minimum)
			*minimum = length;

	    printf("\nDlugoosc przebytej drogi: \n%g\n", length);
        printf("Wszystkie segmenty, z ktorych sklada sie droga:\n");
        
		for(j = 0; j < m * n; j++) 
			if(seen[j] != 0)
				printf("%d ", j);
			
		puts("\n");
		return;
	}

    /*Wywolanie dijkstra, dla kazdego z wierzcholkow*/
    for(i = 0; i < n * m; i++) 
        if(graf[node][i] == 1 && seen[i] == 0) {
			seen[i] = 1;
			dijkstra(seen, graf, wagi, n, m, length + wagi[node][i], i, minimum);
			seen[i] = 0;
        }
    
}



