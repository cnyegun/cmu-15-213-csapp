/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
// #include <stdio.h>
#include "cachelab.h"
#include <assert.h>

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int a1,a2,a3,a4,a5,a6,a7,a8;
    int b = 8;

    if (M == 64 && N == 64) {
        for (int ii = 0; ii < N; ii += b) {
            for (int jj = 0; jj < M; jj += b) {
                for (int i = ii; i < ii + 4 && i < N; i++) {
                // Read whole block to register
                a1 = A[i][jj];
                if (jj + 1 < M) a2 = A[i][jj + 1];
                if (jj + 2 < M) a3 = A[i][jj + 2];
                if (jj + 3 < M) a4 = A[i][jj + 3];
                if (jj + 4 < M) a5 = A[i][jj + 4];
                if (jj + 5 < M) a6 = A[i][jj + 5];
                if (jj + 6 < M) a7 = A[i][jj + 6];
                if (jj + 7 < M) a8 = A[i][jj + 7];

                // Write half of it on the top left
                B[jj][i] = a1;
                if (jj + 1 < M) B[jj + 1][i] = a2;
                if (jj + 2 < M) B[jj + 2][i] = a3;
                if (jj + 3 < M) B[jj + 3][i] = a4;

                if (jj + 4 < M) B[jj    ][i + 4] = a5;
                if (jj + 5 < M) B[jj + 1][i + 4] = a6;
                if (jj + 6 < M) B[jj + 2][i + 4] = a7;
                if (jj + 7 < M) B[jj + 3][i + 4] = a8;
                }

                for (int k = 0; k < 4; k++) {
                    // Read first row of the parked data
                    a1 = B[jj + k][ii + 4];
                    a2 = B[jj + k][ii + 5];
                    a3 = B[jj + k][ii + 6];
                    a4 = B[jj + k][ii + 7];
                    
                    // Read A's bottom left column
                    a5 = A[ii + 4][jj + k];
                    a6 = A[ii + 5][jj + k];
                    a7 = A[ii + 6][jj + k];
                    a8 = A[ii + 7][jj + k];

                    // Write a5...a8 to B's top right (parked data prev place)
                    B[jj + k][ii + 4] = a5;
                    B[jj + k][ii + 5] = a6;
                    B[jj + k][ii + 6] = a7;
                    B[jj + k][ii + 7] = a8;
                    
                    // Write a1...a4 to B's bottom left (parked data)
                    B[jj + 4 + k][ii    ] = a1;
                    B[jj + 4 + k][ii + 1] = a2;
                    B[jj + 4 + k][ii + 2] = a3;
                    B[jj + 4 + k][ii + 3] = a4;
                }

                // A's bottom right
                for (int k = 4; k < 8; k++) {
                    a1 = A[ii + 4][jj + k];
                    a2 = A[ii + 5][jj + k];
                    a3 = A[ii + 6][jj + k];
                    a4 = A[ii + 7][jj + k];

                    B[jj + k][ii + 4] = a1;
                    B[jj + k][ii + 5] = a2;
                    B[jj + k][ii + 6] = a3;
                    B[jj + k][ii + 7] = a4;
                }
            }
        }
        return;
    }

    for (int ii = 0; ii < N; ii += b) {
        for (int jj = 0; jj < M; jj += b) {
            for (int i = ii; i < ii + b && i < N; i++) {
                // Read 
                a1 = A[i][jj];
                if (jj + 1 < M) a2 = A[i][jj + 1];
                if (jj + 2 < M) a3 = A[i][jj + 2];
                if (jj + 3 < M) a4 = A[i][jj + 3];
                if (jj + 4 < M) a5 = A[i][jj + 4];
                if (jj + 5 < M) a6 = A[i][jj + 5];
                if (jj + 6 < M) a7 = A[i][jj + 6];
                if (jj + 7 < M) a8 = A[i][jj + 7];

                // Write
                B[jj][i] = a1;
                if (jj + 1 < M) B[jj + 1][i] = a2;
                if (jj + 2 < M) B[jj + 2][i] = a3;
                if (jj + 3 < M) B[jj + 3][i] = a4;
                if (jj + 4 < M) B[jj + 4][i] = a5;
                if (jj + 5 < M) B[jj + 5][i] = a6;
                if (jj + 6 < M) B[jj + 6][i] = a7;
                if (jj + 7 < M) B[jj + 7][i] = a8;

            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

