/*
 * Name: Rafael Diaz
 * date: feb 20 2025
 * COMP 362 - Spring 2024
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

   // dimensions of the matices m x k and k x n
   int m1, k1, n1;
   int m2, k2, n2; 

   allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
   allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

   // the real magic happens in there

   // TODO: implement

   // dispaly results of matrix multiplication

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

void
allocateAndLoadMatrices(int*** a, int*** b, int*** c, int* m, int* k, int* n)
// takes pointers to two-dimensional matrices, so they can be allocated in here
// and used by the caller
{
   if (scanf("%d %d %d", m, k, n) == 0) {
      oops("Cannot read matrix sizes.\n", -2);
   } 
   else if (scanf("%d %d %d", m, k, n) > 0) { // not sure if thats right

   }
   // TODO: implement
   //
}

void
loadMatrix(int*** matrix, int m, int n)
{ // done?
   for(int i = 0; i < m; i++) {
   	for(int j = 0; j < n; j++) {
		(*matrix)[i][j] = i * n + j;
	}	
   }
}

void
displayMatrix(int** matrix, int m, int n)
{ // done?
   for(int i = 0; i < m; i++) {
  	for(int j = 0; j < n; j++) {
		printf("%3d", matrix[i][j]);
   }
	printf("\n");
}

pthread_t**
alloc_tids(int m, int n)
{
   pthread_t **tids;

   // TODO: implement

   return tids;
}

pthread_t**
multiply(int** a, int** b, int** c, int m, int k, int n)
{
   pthread_t** thread_ids = alloc_tids(m, n);

   // TODO: implement

   return thread_ids;
}

void*
matrixThread(void* param)
{
   // map the parameter onto the structure
   MATRIX_CELL *cell = (MATRIX_CELL *)param;

   // TODO: implement

   free(cell);

   return NULL;
}

void
join(pthread_t** tids, int m, int n)
{
   // TODO: implement
}

void
free_thread_ids(pthread_t** tids, int m)
{
   // TODO: implement
}

void
freeMatrix(int** matrix, int m)
{
   // TODO: implement
}
