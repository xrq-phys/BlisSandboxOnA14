#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include <chrono>
#include <cmath>

extern "C" {
#include "../sandbox/bli_sandbox.h"
}

#define PRINTMAT_INIT(FID, MM, NN, MAT, RS) \
    for (int i = 0; i < MM; ++i) { \
        for (int j = 0; j < NN; ++j) { \
            MAT[ i * (RS) + j ] = (double)rand() / RAND_MAX; \
            fprintf(FID, "%8f ", (double)(MAT[ i * (RS) + j ])); \
        } \
        fprintf(FID, "\n"); \
    }

#define PRINTMAT(FID, MM, NN, MAT, CS) \
    for (int i = 0; i < MM; ++i) { \
        for (int j = 0; j < NN; ++j) \
            fprintf(FID, "%8f ", (double)(MAT[ i + (CS) * j ])); \
        fprintf(FID, "\n"); \
    }

extern "C" int test_shgemm     (int M, int N, int K);
extern "C" int test_i16gemm    (int M, int N, int K);
extern "C" int test_s_shgemm   (int M, int N, int K);
extern "C" int test_i32_i16gemm(int M, int N, int K);

#define INSTANTIATE(TypeIn,TypeOut,TestName,KernelName) \
int TestName(int M, int N, int K) \
{ \
    TypeIn  *A = (TypeIn  *)malloc(M * K * sizeof(TypeIn )); \
    TypeIn  *B = (TypeIn  *)malloc(N * K * sizeof(TypeIn )); \
    TypeOut *C = (TypeOut *)malloc(M * N * sizeof(TypeOut)); \
\
    TypeOut alpha = 1.0; \
    TypeOut beta  = 0.0; \
\
    /*
     * FILE *fidA = fopen("A.dat", "w");
     * FILE *fidB = fopen("B.dat", "w");
     * FILE *fidC = fopen("C.dat", "w");

     * PRINTMAT_INIT(fidA, K, M, A, M)
     * PRINTMAT_INIT(fidB, K, N, B, N)
     * for (int i = 0; i < M * N; ++i)
     *     C[i] = 2.0;
    */ \
\
    int nexp = 80; \
    auto start = std::chrono::high_resolution_clock::now(); \
    for (int i = 0; i < nexp; ++i) \
        KernelName \
        ( \
          BLIS_NO_TRANSPOSE, \
          BLIS_NO_TRANSPOSE, \
          M, N, K, \
          &alpha,  \
          A, 1, M, \
          B, 1, K, \
          &beta,   \
          C, 1, M  \
        ); \
    auto elapsed = std::chrono::high_resolution_clock::now() - start; \
    /* fprintf(stderr, "Elapsed: %f ms\n",
     *         (double)elapsed / CLOCKS_PER_SEC * 1000);
     * fprintf(stderr, "%f GFlOps\n",
     *         (double)(2 * nexp * M * N * K) / 1000000000 /
     *         ((double)elapsed / CLOCKS_PER_SEC));

     * PRINTMAT(fidC, M, N, C, M)
     * fclose(fidA);
     * fclose(fidB);
     * fclose(fidC);
     */ \
\
    free(A); \
    free(B); \
    free(C); \
\
    return int(ceil( \
        ((double)2 * nexp * M * N * K) / \
        ((double)std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count()))); \
}

INSTANTIATE( float16_t, float16_t, test_shgemm     , bli_shgemm      )
INSTANTIATE( int16_t  , int16_t  , test_i16gemm    , bli_i16gemm     )
INSTANTIATE( float16_t, float32_t, test_s_shgemm   , bli_s_shgemm    )
INSTANTIATE( int16_t  , int32_t  , test_i32_i16gemm, bli_i32_i16gemm )

