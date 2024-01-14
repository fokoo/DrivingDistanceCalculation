
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUMBER_OF_NODES 4
#define MAX_SIZE 4
#define TIME_STOP 10
#define RESULT_COL_SIZE 6
#define PATH_LENGTH(x) ((x) == 4 ? 60 : (x == 3 ? 12 : 2))


void execute_program(FILE *file, int matResult[][RESULT_COL_SIZE], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int matPath[][PATH_LENGTH(NUMBER_OF_NODES)]);

void read_matrix(FILE *file, const size_t taille, int mat[][MAX_SIZE]);

void fill_matrix(int mat[][MAX_SIZE], char chaine[], size_t taille);

void generate_paths(int num_nodes, int matPath[][PATH_LENGTH(NUMBER_OF_NODES)]);

void berechnung_laenge_fahrzeit(int matResult[][RESULT_COL_SIZE], int matPath[][PATH_LENGTH(NUMBER_OF_NODES)], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE]);

void show(int matResult[][RESULT_COL_SIZE]);

// int number_of_path(int num_nodes);

// int fac(int n);

int lenTrimStr(char str[]);
