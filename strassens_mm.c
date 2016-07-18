/* Program to implement strassen's matrix multiplication
  Arjun Krishna Babu
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <ctype.h>
#include <math.h>

#define RANDOM_LIMIT 100
#define SEED_MATRIX_A 20
#define SEED_MATRIX_B 21


int str_to_int(const char *numstring);
int** allocate_matrix(const int N);
int** generate_matrix(const int N, const int SEED);
int** naive_multiply(int **matA, int **matB, const int N);
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
  matrix_A = generate_matrix(N, SEED_MATRIX_A);
  printf(" Matrix A: \n");
  print_matrix(matrix_A, N);

  printf("\n");

  // generate_matrix(matrix_A, N);
  matrix_B = generate_matrix(N, SEED_MATRIX_B);
  printf(" Matrix B: \n");
  print_matrix(matrix_B, N);

  return 0;
}

int** naive_multiply(int **matA, int **matB, const int N) {
  int i, j;

  int **result = allocate_matrix(N);
  assert(result != NULL);

  return result;
}

int** generate_matrix(const int N, const int SEED) {
  int i, j;

  // allocate memory for the matrix

  int **matrix = allocate_matrix(N);
  assert(matrix != NULL);
  // int **matrix = malloc(N * sizeof(int *));
  // assert(matrix != NULL);
  // for(i = 0; i < N; i++)  {
  //   matrix[i] = malloc(N * sizeof(int));
  //   assert(matrix[i] != NULL);
  // }

  // assign random values to the matrix
  // Fixed seed value ensures that the outputs can be reproduced.
  // Useful for debugging purposes.
  srandom(SEED);
  for(i = 0; i < N; i++)  {
    for(j = 0; j < N; j++)  {
      matrix[i][j] = (random() % RANDOM_LIMIT);
    }
  }
  return matrix;
}

int** allocate_matrix(const int N)  {
  int i;

  int **matrix = malloc(N * sizeof(int *));
  assert(matrix != NULL);
  for(i = 0; i < N; i++)  {
    matrix[i] = malloc(N * sizeof(int));
    assert(matrix[i] != NULL);
  }

  return matrix;
}

void print_matrix(int **matrix, const int N)  {
  int i, j;

  if(matrix != NULL)  {
    for(i = 0; i < N; i++)  {
      for(j = 0; j < N; j++)  {
        printf(" %d", matrix[i][j]);
      }
      printf("\n");
    }
  }
  else  {
    fprintf(stderr, " Error: print_matrix(): matrix parameter is NULL\n");
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
