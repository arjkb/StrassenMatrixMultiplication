/* Program to implement strassen's matrix multiplication
  Arjun Krishna Babu
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int str_to_int(const char *numstring);
int** generate_matrix(const int N);
// void generate_matrix(int **matrix, const int N);
void print_matrix(int **matrix, const int N);

int main(int argc, char **argv)  {
  int N;

  int **matrix_A = NULL;
  int **matrix_B = NULL;

  printf(" argc: %d\n", argc);

  if(argc < 2) {
    fprintf(stderr, " Error: FATAL: Insufficient arguments\n");
    exit(1);
  }

  // printing out the command-line arguments.
  // Picks argv[1] as N, and ignores the rest of the arguments if any
  // int i;
  // for(i = 0; i < argc; i++) {
  //   printf(" argv[%d]: %s\n", i, argv[i]);
  // }

  N = str_to_int(argv[1]);

  printf(" N = %d\n", N);

  // generate_matrix(matrix_A, N);
  matrix_A = generate_matrix(N);
  print_matrix(matrix_A, N);

  return 0;
}


int** generate_matrix(const int N) {
  int i, j;

  // allocate memory for the matrix
  int **matrix;
  int *temp;

  // matrix = (int **)malloc(N * sizeof(int *));
  // temp = malloc(N * N * sizeof(int));
  matrix = malloc(N * sizeof(int *));

  for(i = 0; i < N; i++)  {
    matrix[i] = malloc(N * sizeof(int));
    // matrix[i] = temp + (i * N);
  }

  // assign values to the matrix
  for(i = 0; i < N; i++)  {
    for(j = 0; j < N; j++)  {
      matrix[i][j] = 3;
    }
  }

  return matrix;
}

void print_matrix(int **matrix, const int N)  {
  int i, j;
  for(i = 0; i < N; i++)  {
    for(j = 0; j < N; j++)  {
      printf(" %d", matrix[i][j]);
    }
    printf("\n");
  }
}

int str_to_int(const char *numstring) {
  int number = 0;
  int i;
  int digit = 0;

  for(i = 0; numstring[i] != '\0'; i++) {
    if( isdigit(numstring[i]) ) {
      digit = numstring[i] - '0';
      number = (number * 10) + digit;
      // printf(" DEBUG: Number: %d, %d %d\n", i, number, digit);
    }
    else  {
      printf(" Error: str_to_int(%s): not a digit\n", numstring);
      return 0;
    }
  }
  return number;
}
