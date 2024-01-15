 /*  
   Autor: FOKO FOTSO
 */

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
    memset( matPath, 0, (NUMBER_OF_NODES-1)*paths_length*sizeof(int));
    int matResult[paths_length][RESULT_COL_SIZE];
    memset( matResult, 0, paths_length*RESULT_COL_SIZE*sizeof(int));

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
             generate_paths(NUMBER_OF_NODES, matPath);
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
              if (row == 4) {
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

void generate_paths(int num_nodes, int matPath[]) {

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int row = 0;

   if (num_nodes == 1) {
     printf("This program works with minimum 2 nodes and maximum 4 nodes!\n");
   }
   if (num_nodes >= 2) {
      for(i=1; i<=num_nodes; i++) {
        for(j=1; j<=num_nodes; j++) {
          if(i!=j){
            matPath[row] = 10*i+j;
            row++;
          }
        }
      }
   }
   if (num_nodes >= 3) {
      for(i=1; i<=num_nodes; i++) {
        for(j=1; j<=num_nodes; j++) {
          for(k=1; k<=num_nodes; k++) {
            if(i!=j && i!=k && j!=k){
               matPath[row] = 100*i+10*j+k;
               row++;
            }
          }
        }
      }
   }
   if (num_nodes == 4) {
      for(i=1; i<=num_nodes; i++) {
        for(j=1; j<=num_nodes; j++) {
          for(k=1; k<=num_nodes; k++) {
             for(l=1; l<=num_nodes; l++) {
                if(i!=j && i!=k && i!=l && j!=k && j!=l && k!=l){
                   matPath[row] = 1000*i+100*j+10*k+l;
                   row++;
                }
             }
          }
        }
      }
   }
}

void berechnung_laenge_fahrzeit(int matResult[][RESULT_COL_SIZE], int matPath[], int matDistance[][MAX_SIZE], int matVitesse[][MAX_SIZE], int paths_length){

    int path = 0;
    int count = 0; 
    char pathStr[5];
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    char ci[2];
    char cj[2];
    char ck[2];
    char cl[2];
    int col_result = 0;

    if(NUMBER_OF_NODES >= 2) {
       for(int col = 0; col < paths_length; col++) {
          if(matPath[col] != 0) {
              path = matPath[col];
              sprintf(pathStr, "%d", path);
              if (strlen(pathStr) == 2)
              {
                 ci[0] = pathStr[0];
                 cj[0] = pathStr[1];
                 i = atoi(ci);
                 j = atoi(cj);

                 matResult[col][0] = i;
                 matResult[col][1] = j;
                 matResult[col][4] = matDistance[i-1][j-1];
                 matResult[col][5] = (int)(matDistance[i-1][j-1]*60/matVitesse[i-1][j-1]);
                 ++col_result;
                 count  =  col_result;
                 printf("count %d and len %d \n", count, path);
              }
              else
              {
                 break;
              }
          }
       }
     }
     if(NUMBER_OF_NODES >= 3) {
       for(int col = col_result; col < paths_length; col++) {
        if(matPath[col] != 0) {
              path = matPath[col];
              sprintf(pathStr, "%d", path);
              if (lenTrimStr(pathStr) == 3)
              {
                 ci[0] = pathStr[0];
                 cj[0] = pathStr[1];
                 ck[0] = pathStr[2];
                 i = atoi(ci);
                 j = atoi(cj);
                 k = atoi(ck);          
                 matResult[col][0] = i;
                 matResult[col][1] = j;
                 matResult[col][2] = k;
                 matResult[col][4] = matDistance[i-1][j-1] + matDistance[j-1][k-1];
                 matResult[col][5] = TIME_STOP + round(((float)matDistance[i-1][j-1]*60/matVitesse[i-1][j-1])
                                               + ((float)matDistance[j-1][k-1]*60/matVitesse[j-1][k-1]));
                 ++col_result;
                 count  =  col_result;
                 printf("count %d and len %d \n", count, path);
              }
              else
              {
                 break;
              }
           }
         }
     }
     if(NUMBER_OF_NODES == 4) {
       for(int col = col_result; col < paths_length; col++) {
          if(matPath[col] != 0) {
              path = matPath[col];
              sprintf(pathStr, "%d", path);
              if (lenTrimStr(pathStr)== 4)
              {
                 ci[0] = pathStr[0];
                 cj[0] = pathStr[1];
                 ck[0] = pathStr[2];
                 cl[0] = pathStr[3];
                 i = atoi(ci);
                 j = atoi(cj);
                 k = atoi(ck);
                 l = atoi(cl);
                 matResult[col][0] = i;
                 matResult[col][1] = j;
                 matResult[col][2] = k;
                 matResult[col][3] = l;
                 matResult[col][4] = matDistance[i-1][j-1] + matDistance[j-1][k-1]
                                     + matDistance[k-1][l-1];
                 matResult[col][5] = 2*TIME_STOP + round(((float)matDistance[i-1][j-1]*60/matVitesse[i-1][j-1])
                                                 + ((float)matDistance[j-1][k-1]*60/matVitesse[j-1][k-1])
                                                 + ((float)matDistance[k-1][l-1]*60/matVitesse[k-1][l-1]));
                 printf("count %d and len %d \n", ++count, path);
              }
              else
              {
                 printf("length at position col is %lu \n", strlen(pathStr));
              }
           }
         }
     }
}


int lenTrimStr(char str[]) {
  int len = strlen(str);
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


void show(int matResult[][RESULT_COL_SIZE], int paths_length) {
      int i = 0;
      int j = 0;
      int k = 0;
      int l = 0;
      char space[] = "       ";
      int char_size = 0;
      int max_char_size = 150;
      char buffer[max_char_size];
      char str[2];

    printf("%s %s %s \n", "Strecke ", "Laenge [km]", " Fahrzeit [Min]");
     for(int row = 0; row < paths_length; row++) {
        i = matResult[row][0];
        j = matResult[row][1];
        k = matResult[row][2];
        l = matResult[row][3];
     // printf(" i %d \n", i);
     // printf(" j %d \n", j);
     // printf(" k %d \n", k);
     // printf(" l %d \n", l);
        char_size = snprintf ( buffer, max_char_size, "%d-%d", i, j);

       if (NUMBER_OF_NODES >= 3  &&  k != 0) {
           char_size = snprintf (buffer+char_size, (max_char_size-char_size), "-%d", k);
       }
       if (NUMBER_OF_NODES >= 4  && l != 0) {
          sprintf(str, "%d", l);
          strncat(buffer, "-", max_char_size);
          strncat(buffer, str, max_char_size);
       }
       printf("%s %s %d %s %d  \n", buffer, space, matResult[row][4], space, matResult[row][5]);
       // printf("End of the table\n \n");
     }
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

