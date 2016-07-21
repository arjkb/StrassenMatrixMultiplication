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

#define Q_TOP_LEFT 1
#define Q_TOP_RIGHT 2
#define Q_BOTTOM_LEFT 3
#define Q_BOTTOM_RIGHT 4


int str_to_int(const char *numstring);
long** allocate_matrix(const int N);
long** generate_matrix(const int N, const int SEED);
long** naive_multiply(long **matA, long **matB, const int N);
void print_matrix(long **matrix, const int N);

long** naive_multiply(long **matA, long **matB, const int N);

void display4(long **matrix, const int N);
long **extract_quadrant(long **matrix, const int N, const int QUADRANT);


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

  display4(result_naive, N);

  return 0;
}

// long** naive_multiply(long **matA, long **matB, const int N)  {
//   if(N == 1)  {
//     // Base case
//     return
//   }
// }

void display4(long **matrix, const int N) {
  // long **matrix_q1 = allocate_matrix(N/2);
  // long **matrix_q2 = allocate_matrix(N/2);
  // long **matrix_q3 = allocate_matrix(N/2);
  // long **matrix_q4 = allocate_matrix(N/2);

  long **A = extract_quadrant(matrix, N, Q_TOP_LEFT);
  long **B = extract_quadrant(matrix, N, Q_TOP_RIGHT);
  long **C = extract_quadrant(matrix, N, Q_BOTTOM_LEFT);
  long **D = extract_quadrant(matrix, N, Q_BOTTOM_RIGHT);

  printf("\n Quadrant A: \n");
  print_matrix(A, N/2);

  printf("\n Quadrant B: \n");
  print_matrix(B, N/2);

  printf("\n Quadrant C: \n");
  print_matrix(C, N/2);

  printf("\n Quadrant D: \n");
  print_matrix(D, N/2);

}

long **extract_quadrant(long **matrix, const int N, const int QUADRANT)  {

  long **matrix_result = allocate_matrix(N/2);

  int start_row = -1;
  int start_col = -1;

  int i, j;

  // printf("\n Quadrant %d", QUADRANT);

  switch (QUADRANT) {
    case Q_TOP_LEFT:
                  start_row = 0;
                  start_col = 0;
                  break;

    case Q_TOP_RIGHT:
                  start_row = 0;
                  start_col = N/2;
                  break;

    case Q_BOTTOM_LEFT:
                  start_row = N/2;
                  start_col = 0;
                  break;

    case Q_BOTTOM_RIGHT:
                  start_row = N/2;
                  start_col = N/2;
                  break;
    default:
                  fprintf(stderr, " Error: Invalid QUADRANT index\n");
                  break;
  }

  // printf("\n Q%d %d %d\n", QUADRANT, start_row, start_col);

  for(i = start_row; i < (start_row + N/2); i++)  {
    for(j = start_col; j < (start_col + N/2); j++)  {
      // printf(" Assigning: %ld\n", matrix[i][j]);
      matrix_result[i - start_row][j - start_col] = matrix[i][j];
    }
  }

  return matrix_result;
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
