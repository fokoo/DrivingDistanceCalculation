
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUMBER_OF_NODES 5
#define MAX_SIZE 5
#define TIME_STOP 10
#define RESULT_COL_SIZE (NUMBER_OF_NODES+2)



void execute_program(FILE *file, int matResult[][RESULT_COL_SIZE], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int matPath[], int paths_length);

void read_matrix(FILE *file, const size_t taille, int mat[][MAX_SIZE]);

void fill_matrix(int mat[][MAX_SIZE], char chaine[]);

void generate_paths(int paths_length, int matPath[]);

void berechnung_laenge_fahrzeit(int matResult[][RESULT_COL_SIZE], int matPath[], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int paths_length);

void show(int matResult[][RESULT_COL_SIZE], int paths_length);



int number_of_path(int num_nodes);

int lenTrimStr(char str[]);

int fac(int n);

int no_duplication(char str[]);

int no_high_number(char str[], int highest_number);

int calculate_distance(int matDistance[][MAX_SIZE], int matIndices[], int num_addition);

int calculate_vitesse(int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int matIndices[], int num_addition);