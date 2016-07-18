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
long** allocate_matrix(const int N);
long** generate_matrix(const int N, const int SEED);
long** naive_multiply(long **matA, long **matB, const int N);
void print_matrix(long **matrix, const int N);

int main(int argc, char **argv)  {
  int N;

  long **matrix_A = NULL;
  long **matrix_B = NULL;

  long **result_naive = NULL;

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

  // generate_matrix(matrix_A, N);
  matrix_B = generate_matrix(N, SEED_MATRIX_B);
  printf("\n Matrix B: \n");
  print_matrix(matrix_B, N);

  result_naive = naive_multiply(matrix_A, matrix_B, N);
  printf("\n Naive Multiply Result: \n");
  print_matrix(result_naive, N);

  return 0;
}

long** naive_multiply(long **matA, long **matB, const int N) {
  int i, j, k;

  long **result = allocate_matrix(N);
  assert(result != NULL);

  for(i = 0; i < N; i++)  {
    for(j = 0; j < N; j++)  {
      result[i][j] = 0;
      for(k = 0; k < N; k++)  {
        result[i][j] += matA[i][k] * matB[k][j];
      }
    }
  }

  return result;
}

long** generate_matrix(const int N, const int SEED) {
  int i, j;

  // allocate memory for the matrix

  long **matrix = allocate_matrix(N);
  assert(matrix != NULL);

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

long** allocate_matrix(const int N)  {
  int i;

  long **matrix = malloc(N * sizeof(long *));
  assert(matrix != NULL);
  for(i = 0; i < N; i++)  {
    matrix[i] = malloc(N * sizeof(long));
    assert(matrix[i] != NULL);
  }

  return matrix;
}

void print_matrix(long **matrix, const int N)  {
  int i, j;

  if(matrix != NULL)  {
    for(i = 0; i < N; i++)  {
      for(j = 0; j < N; j++)  {
        printf("\t%d", matrix[i][j]);
      }
      printf("\n");
    }
  }
  else  {
    fprintf(stderr, " Error: print_matrix(): matrix parameter is NULL\n");
  }
}

int str_to_int(const char *numstring) {
  int result_number = 0;
  int digit;

  int i;

  for(i = 0; numstring[i] != '\0'; i++) {
    if( isdigit(numstring[i]) ) {
      digit = numstring[i] - '0';
      result_number = (result_number * 10) + digit;
      // printf(" DEBUG: Number: %d, %d %d\n", i, result_number, digit);
    }
    else  {
      printf(" Error: str_to_int(%s): not a digit\n", numstring);
      return 0;
    }
  }
  return result_number;
}
