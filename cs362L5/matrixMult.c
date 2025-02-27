/*
 * Name: Rafael Diaz
 * date: feb 26 2025
 * COMP 362 Operating Systems - Section 1 - Spring 2024
 */

#include "matrixMult.h"

int
main(int argc, char** argv)
{
   // Input file should be passed to the program: ./matrixMult in.txt
   if (freopen(argv[1], "r", stdin) == 0) {
      oops("Cannot open the input file.\n", -1);
   }

   // two pairs of matrices
   int** a1,** b1,** c1; 
   int** a2,** b2,** c2;

   // dimensions of the matrices m x k and k x n
   int m1, k1, n1;
   int m2, k2, n2; 

   allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
   allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

   // the real magic happens in there

   pthread_t** tids1 = multiply(a1, b1, c1, m1, k1, n1);
   pthread_t** tids2 = multiply(a2, b2, c2, m2, k2, n2);

   free_thread_ids(tids1, m1);
   free_thread_ids(tids2, m2);


   // display results of matrix multiplication

   printf("\nMATRIX A1\n");
   displayMatrix(a1, m1, k1);
   freeMatrix(a1, m1);
   printf("\nMATRIX B1\n");
   displayMatrix(b1, k1, n1);
   freeMatrix(b1, k1);
   printf("\nMATRIX A1 x B1\n");
   displayMatrix(c1, m1, n1);
   freeMatrix(c1, m1);

   printf("\nMATRIX A2\n");
   displayMatrix(a2, m2, k2);
   freeMatrix(a2, m2);
   printf("\nMATRIX B2\n");
   displayMatrix(b2, k2, n2);
   freeMatrix(b2, k2);
   printf("\nMATRIX A2 x B2\n");
   displayMatrix(c2, m2, n2);
   freeMatrix(c2, m2);

   return 0;
}
int** allocMat(int* m, int* n) {
   int **mallocMatrix = malloc(*m * sizeof(int *));

      for (int i = 0; i < *m; i++) {
         mallocMatrix[i] = malloc(*n *  sizeof(int));
   }
   return mallocMatrix;
}
void allocateAndLoadMatrices(int*** a, int*** b, int*** c, int* m, int* k, int* n)
// takes pointers to two-dimensional matrices, so they can be allocated in here
// and used by the caller
{
   if (scanf("%d %d %d", m, k, n) == 0)
      oops("Cannot read matrix sizes.\n", -2);

      *a = allocMat(m, k);
      *b = allocMat(k, n);
      *c = allocMat(m, n);


      loadMatrix(a, *m, *k);
      loadMatrix(b, *k, *n);

   }



void loadMatrix(int*** matrix, int m, int n) {
   // done?
   for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++) {
         scanf("%d", &(*matrix)[i][j]);
      }
   }
}


void displayMatrix(int **matrix, int m, int n) {
   // done?
   for(int i = 0; i < m; i++) {
      for(int j = 0; j < n; j++) {
         printf("%3d", matrix[i][j]);
      }
      printf("\n");
   }
}
pthread_t** alloc_tids(int m, int n){ //done
   pthread_t **tids = (pthread_t **) malloc( sizeof(pthread_t *) * m + sizeof(pthread_t *) * n * m);
   pthread_t *rowPoint = (pthread_t *) (tids + m);
      for(int i = 0; i < m; i++)
         (tids[i]) = (rowPoint + n * i);


   return tids;
}

pthread_t** multiply(int** a, int** b, int** c, int m, int k, int n) { //done
   pthread_t** tids = alloc_tids(m, n);

   for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) {

         MATRIX_CELL *cell = (MATRIX_CELL *) malloc(sizeof(MATRIX_CELL));
         cell->i = i;
         cell->j = j;
         cell->k = k;
         cell->a = a;
         cell->b = b;
         cell->c = c;
         pthread_create(&((tids)[i][j]), NULL, matrixThread, (void *) cell);

      }
   join(tids, m, n);
   return tids;
}

void* matrixThread(void* param) {
   // map the parameter onto the structure
   MATRIX_CELL *cell = (MATRIX_CELL *)param;
   int threadTotal = 0;

   for (int index = 0; index < cell->k; index++) {
      threadTotal += cell->a[cell->i][index] * cell->b[index][cell->j];
   }
   cell->c[cell->i][cell->j] = threadTotal;
   free(cell);

   return NULL;
}

void join(pthread_t** tids, int m, int n) {
   for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
         if (pthread_join(tids[i][j], NULL) != 0)
            oops("Cannot join thread.\n", -2);
}

void free_thread_ids(pthread_t** tids, int m) { //done

   free(tids);

   }

void freeMatrix(int** matrix, int m) { //done
   for (int i = 0; i < m; i++) {
      free(matrix[i]);
   }
   free(matrix);
}
