#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"



int main()
{
    // Daten aus Datein abholen
    FILE* myFile = NULL;
    myFile = fopen("knoten.txt", "r");

    // Variable initialisieren
    const int paths_length = number_of_path(NUMBER_OF_NODES);
    int matDistance[MAX_SIZE][MAX_SIZE];
    int matVitesse[MAX_SIZE][MAX_SIZE];
    int matPath[ (NUMBER_OF_NODES-1) * paths_length];
    memset(matPath, 0, (NUMBER_OF_NODES-1)*paths_length*sizeof(int));
    int matResult[paths_length][RESULT_COL_SIZE];
    memset(matResult, 0, paths_length*RESULT_COL_SIZE*sizeof(int));

    //Programm Ausfuehren
    execute_program(myFile, matResult, matDistance, matVitesse, matPath, paths_length);

    return 0;
}

void execute_program(FILE *file, int matResult[][RESULT_COL_SIZE], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int matPath[], int paths_length)
{
    int max = MAX_SIZE * sizeof(int) + MAX_SIZE * sizeof(char);
    char chaine[max];
    size_t error = 0;

    if(NUMBER_OF_NODES > MAX_SIZE || NUMBER_OF_NODES == 1){
        printf("This program works with minimum 2 nodes and maximum 4 nodes!\n");
    }

    if (file != NULL)
    {
       size_t mat_size = 0;
       char temp[1];
       while( fgets(chaine, max, file) != NULL  && !error){
           if(chaine[0]=='D')
           {
             temp[0] = chaine[2];
             mat_size = atoi(temp);
             read_matrix(file, mat_size, matDistance);
           }
           else if(chaine[0]=='V')
           {
             temp[0] = chaine[2];
             mat_size = atoi(temp);
             read_matrix(file, mat_size, matVitesse);
           }
           else
           {
              error = 1;
              printf("Error in the file!\n");
           }

        }
        if(NUMBER_OF_NODES <= MAX_SIZE  && mat_size == MAX_SIZE){
             // Generiiert alle möglichen Strecken in ein 2d array
             generate_paths(paths_length, matPath);
             // Berechne Laenge und Fahrzeit und speiche in eine array
             berechnung_laenge_fahrzeit(matResult, matPath, matDistance, matVitesse, paths_length);
             // Gibt die Ergenisse aus
             show(matResult, paths_length);
        }
        fclose(file);
    }
    else
    {  // An error message is displayed
       printf("Open the file knoten.txt failed\n");
    }
}


void read_matrix(FILE *file, const size_t mat_size, int mat[][MAX_SIZE])
{
    int max = mat_size * sizeof(int) + mat_size * sizeof(char);
    int count = 0;
    char chaine[max];
    char nchaine[mat_size * max + mat_size * sizeof(char)];
    strcpy(nchaine, "\0");
    
    if (mat_size != MAX_SIZE){
       printf("Matrix-Size in knoten.txt is different to the setting MAX_SIZE\n");
       return ;
    }

    if (file != NULL)
    {
       while (count < mat_size)
       {
         // store file-lign content in chaine
         fgets(chaine, max, file);
         strcat(nchaine, chaine);
         nchaine[strlen(nchaine)-1] = ' ';
         ++count;
       }
       fill_matrix(mat, nchaine);
    }
    else
    {
       printf("Failled to open the file knoten.txt\n");
    }
}

void fill_matrix(int mat[][MAX_SIZE], char chaine[])
{
    int len = strlen(chaine);
    int row = 0;
    int col = 0;
    int i = 0;
    int tem = 0;
    int longest_number = len/(MAX_SIZE * MAX_SIZE); 
    char* arrint;
    arrint = (char *) malloc(longest_number * sizeof(char));

    while(len > 0)
    {
         if(chaine[tem] != ' ')
         {
           arrint[i] = chaine[tem];
           ++i;
         }
         if( chaine[tem] == ' '  &&  arrint[0] != ' ' )
         {
            mat[row][col] = atoi(arrint);
            ++col;
            if(col==MAX_SIZE) {
              col = 0;
              ++row;
              if (row == MAX_SIZE) {
                 break;
              }
            }
            i=0;
            free(arrint);
            arrint = (char *) malloc(len * sizeof(char));
            memset(arrint, ' ', sizeof(char) * longest_number);
         }
          ++tem;
          --len;
     }
}

void generate_paths(int paths_length, int matPath[]) {

    int num = 0;
    int path = 12;
    char pathStr[NUMBER_OF_NODES+1];

    if (NUMBER_OF_NODES == 1) {
       printf("This program works with minimum 2 nodes and maximum 4 nodes!\n");
    }  
    while (num < paths_length){
       sprintf(pathStr, "%d", path);
       if(no_high_number(pathStr, NUMBER_OF_NODES)){
          if(no_duplication(pathStr)){
                 matPath[num] = path;
                 ++num;
          }
       }
       ++path; 
    } 
}

void berechnung_laenge_fahrzeit(int matResult[][RESULT_COL_SIZE], int matPath[], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int paths_length){

    printf("berechnung_laenge_fahrzeit start\n");

    int path = 0;
    char pathStr[NUMBER_OF_NODES+3];
    int matIndices[NUMBER_OF_NODES];
    int len_path = 2;
    int mr = 0; 
    char cmr[2]; 
    int ind = 0;
   
    for(int col = 0; col < paths_length; col++) {
       if(matPath[col] != 0) {
           path = matPath[col];
           sprintf(pathStr, "%d", path);
           len_path = lenTrimStr(pathStr);
           if(lenTrimStr(pathStr) <= NUMBER_OF_NODES)
           {
              for(mr = 0; mr < len_path; mr++) {
                  cmr[0] = pathStr[mr];
                  ind = atoi(cmr);
                  matResult[col][mr] = ind;
                  matIndices[mr] = ind;
                  printf("ind %d \n", ind);
              }
              matResult[col][RESULT_COL_SIZE-2] = calculate_distance(matDistance, matIndices, len_path-1);
              matResult[col][RESULT_COL_SIZE-1] = calculate_vitesse(matDistance, matVitesse, matIndices, len_path-1);
              
//               printf("path %d \n", path);
            }
            else
            {
               break;
            }
        }
    }
    
     printf("berechnung_laenge_fahrzeit start\n");
}



void show(int matResult[][RESULT_COL_SIZE], int paths_length) {
      int mr = 0;
      int i = 0;
      char pathStr[NUMBER_OF_NODES * 2] = "";
      const int o = 48;  
      const char space[] = "       ";
      const char sep = '-';

      printf("%s %s %s \n", "Strecke ", "Laenge [km]", " Fahrzeit [Min]");
      for(int row = 0; row < paths_length; row++) {
        for(int col = 0; col < NUMBER_OF_NODES; col++) {
           if (matResult[row][col] != 0) {
               mr = (char)  o + matResult[row][col];
//                printf("mr %c \n", mr);
               if (col != 0) { 
                 pathStr[i] = sep;
                 ++i;
               }   
               pathStr[i] = mr;
               ++i;
//                 printf("pathStr %s \n", pathStr);
           }     
        }
        i = 0;
        printf("%s %s %d %s %d  \n", pathStr, space, matResult[row][RESULT_COL_SIZE-2], space, matResult[row][RESULT_COL_SIZE-1]);
     }
     printf("End of the table\n \n");
}


int number_of_path(int num_nodes) {
     int num_paths = 0;
     int denumerator = 1;
     int numerator = 0;
     if(num_nodes<2){
       return num_paths;
     }
     for(int k=2; k<=num_nodes; k++) {
        numerator = fac(num_nodes);
        denumerator = fac(num_nodes-k);
        if (denumerator !=0) {
          num_paths = num_paths + (int)(numerator/denumerator);
        }
     }
     return num_paths;
}


int lenTrimStr(char str[]) {
  const  int len = strlen(str);
  int l = 0;
  if (len == 0) {
    return 0;
  }
  for (int i=0; i<strlen(str); i++) {
      if (str[i] != ' '){
          ++l;
      }
  }
   return l;
}


int fac(int n) {
    if(n == 0 || n == 1){
     return 1;
    }
    if( n == 2){
     return 2;
    }
    else
    {
     return n * fac(n-1);
    }
}

int no_duplication(char str[]) {
   int res = 1;
   int j = 0;
   int k = 0;
   const int len = strlen(str);
   
   for(j=0; j<len; j++) {
     for(k=0; k<=len; k++) {
        if(str[j] == '0' || str[k] == '0'){  // remove 0 as path
            res = 0;
            break;
        }
        if(j!=k && str[j] == str[k] && str[j] != ' '){  // check duplicity
            res = 0;
            break;
        }
     }
   }
   return res;
}

int no_high_number(char str[], int highest_number) {
   int res = 1;
   int j = 0;
   const int len = strlen(str);
   int x = 0;
   for(j=0; j<len; j++) {
        x = str[j] - '0';
        if(x > highest_number){ 
            res = 0;
            break;
        }
   }  
   return res;
}

int calculate_distance(int matDistance[][MAX_SIZE], int matIndices[], int num_addition) {
   int result = 0;
   int i = 0;
   int j = 0;
   int k = 0;
 
   while (i < num_addition) {
     j  = matIndices[i];
     k  = matIndices[i+1];
     result += matDistance[j-1][k-1];
     ++i;
   }  
   return result;
}

int calculate_vitesse(int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int matIndices[], int num_addition) {
   double result = 0;
   int i = 0;
   const int hour_in_minute = 60;
   int j = 0;
   int k = 0;
   
   while (i < num_addition) {
     if (matVitesse[i][i+1] != 0) {
        j  = matIndices[i];
        k  = matIndices[i+1];
        result += matDistance[j-1][k-1]*hour_in_minute/matVitesse[j-1][k-1];
     }
     ++i;
   }  
   result += TIME_STOP*(num_addition-1);
   return round(result);
}