#include "funkcje.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 12

int main(int argc, char **argv){

    /*Kontrola bledow*/
    if(argc < 2) { 
        fprintf(stderr, "Przy wywolywaniu programu musimy podac plik z danymi oraz kolejno szerokosc i wysokosc labiryntu\n");
        return 1;
    }
    else if(argc < 3) {
        fprintf(stderr, "Brak podanej szerokosci oraz wysokosci labiryntu\n");
        return 2;
    }
    else if(argc < 4) {
        fprintf(stderr,"Brak podanej szerokosci labiryntu\n");
        return 3;
    }

    FILE *in= argc > 1 ? fopen(argv[1], "r") : stdin;

    srand( time( NULL ) );

    /*Wysokosc, szerokosc, ilosc wszystkich segmentow*/
    int m = atoi( argv[2] );
    int n = atoi( argv[3] );
    int nodes = n * m;

    /*Zmienna bedzie potrzebna przy okreslaniu najkrotszej drogi w labiryncie*/
    double minimum = 1000;
    printf("\n~Labirynt ma postac\n");
    printf("Wysokosc: %d    Szerokosc: %d\n", m, n);

    /*Kontrola bledow zwiazana z maksymalna wysokoscia oraz szerokoscia labiryntu*/
    if(n > 10 || m > 10) {
        fprintf(stderr, "Labirynt jest za duzy - Maksymalne wymiary 10x10\n");
        return 4;
    }

    /*Przepisywanie labiryntu z pliku .txt do tablicy dwuwymiarowej*/
    int i;
    int r = 0;
    int labirynt[BUFSIZE][BUFSIZE];
    char row[BUFSIZE];
    
    while( fgets(row, BUFSIZE, in) != NULL) {        

        for(i = 0; i < n; i++) {

            labirynt[r][i] = row[i] - '0';
            if(labirynt[r][i] < 0 || labirynt[r][i] > 3) {
                fprintf(stderr, "Znaleziono znak inny niż 0,1,2,3 - Rzad[%d] Kolumna[%d] w pliku %s\n", r, i, argv[1]);
                return 5;
            }

        }
        r++;

    }


    /*Tworzenie macierzy zawierajacej koneksje miedzy wierzcholkami*/
	int **graf = (int**) malloc(nodes * sizeof(int*));
	for(i = 0; i < nodes; i++)
		graf[i] = (int*) calloc(nodes, sizeof(int));
	
	/*Tworzenie macierzy zawierajacej wagi w poszczegolnych krawedziach*/
	double **wagi = (double**) malloc(nodes * sizeof(double*));
	for(i = 0; i < nodes; i++) /* tu tez uzyj calloc*/
		wagi[i] = (double*) malloc(nodes *sizeof(double*));

	/*Tworzenie tablicy przechowujacej informajce o odwiedzeniu wierzcholka*/
	int *seen = calloc(nodes, sizeof *seen);


    /*Poczatkowa wizaulizacja labiryntu*/
    vizualizer( n, m, labirynt );


    /*Tworzenie grafu z wykorzystaniem macierzy sasiedztwa*/
    graphcreator(seen, graf, wagi, labirynt, n, m);

    /*Numerowanie kazdego z segmentow labiryntu*/
    printf("\n~Numerowa reprezentacja kazdego z wiercholkow/segmentow\n");
    for(i = 0; i < m; i++) {

        for(int j = 0; j < n; j++) 
            printf("%d ", (i*n) + j);

        printf("\n");
    
    }
    printf("\n");
    
    /*Zapelnienie tablicy zerami, 
    poza pierwsza wartoscia bo ta bedzie odwiedzona po pierwszym wywolaniu funkcji DFS*/
    for(i = 1; i < n * m; i++) seen[i] = 0;
        
    int j;
    /*Wypisanie wszystkich wag miedzy wezlami*/

    printf("\n~Wagi na krawedziach:\n");
    for(i = 0; i < nodes; i++) 
        for(j = 0; j < nodes; j++) 
            if(graf[i][j] != 0)
                printf("(%d) -> (%d) %g\n", i, j, wagi[i][j]);
    

    /*Wyszukiwanie najszybszej sciezki w labiryncie*/
    printf("\n~~DZIALANIE ALGORYTMU~~\n\n");
    dijkstra(seen, graf, wagi, n, m, 0, 0, &minimum);

    printf("\n*Najszybsza droga ma dlugosc: %g", minimum);
    
    /*Zwolnienie pamieci*/  
    for(i = 0; i < nodes; i++) {
        free(wagi[i]);
        free(graf[i]);
    }

    free(wagi);
    free(graf);
    free(seen);
}
