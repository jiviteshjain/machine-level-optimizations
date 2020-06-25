#include<stdio.h>
#include<stdlib.h>

typedef struct Matrix
{
    int matrix[1000][1000];
}Matrix;

Matrix *matrix_multiply(Matrix *a,Matrix *b,int p,int q,int r)
{
    Matrix *result;
    result=malloc(sizeof(Matrix));
    /*
    size of matrix a is pxq
    size of matrix b is qxr
    Maximum value of p,q or r can be 1000.
    Your Code goes here. The output of their matrix multiplication
    should be stored in result and returned. Just code this function,
    no need to write anything in main(). This function will be called directly.
    We are dealing with pointers so use result->matrix and not result.matrix

    Also note you can write any other function that you might need.
    */

#define N 1000

    int stridei = 20, stridek = 512, stridej = 20, i, j, k, gotill;
    register int *arow;
    register int *brow;
    register int ii, jj, kk, tmp;

    for(ii = 0; ii < p; ii++){
        for(jj = 0; jj < r; jj++){
            result->matrix[ii][jj] = 0;
        }
    }

#define min(x, y) (y^((x^y) & -(x<y)))

    for(i = 0; i < N; i++){
        for(j = 0; j < i; j++){
            tmp = b->matrix[i][j];
            b->matrix[i][j] = b->matrix[j][i];
            b->matrix[j][i] = tmp;
        }
    }

    for(i = 0; i < p; i += stridei){
        for(j = 0; j < r; j += stridej){
            for(k = 0; k < q; k += stridek){
                for(ii = i; ii < min(i + stridei, p); ii++){
                    arow = a->matrix[ii];
                    for(jj = j; jj < min(j + stridej, r); jj++){
                        gotill = min(k + stridek, q);
                        tmp = 0;
                        brow = b->matrix[jj];
                        for(kk = k; kk + 15 < gotill; kk+=16){
                            tmp += arow[kk + 0] * brow[kk + 0]
                                +  arow[kk + 1] * brow[kk + 1]
                                +  arow[kk + 2] * brow[kk + 2]
                                +  arow[kk + 3] * brow[kk + 3]
                                +  arow[kk + 4] * brow[kk + 4]
                                +  arow[kk + 5] * brow[kk + 5]
                                +  arow[kk + 6] * brow[kk + 6]
                                +  arow[kk + 7] * brow[kk + 7]
                                +  arow[kk + 8] * brow[kk + 8]
                                +  arow[kk + 9] * brow[kk + 9]
                                +  arow[kk + 10] * brow[kk + 10]
                                +  arow[kk + 11] * brow[kk + 11]
                                +  arow[kk + 12] * brow[kk + 12]
                                +  arow[kk + 13] * brow[kk + 13]
                                +  arow[kk + 14] * brow[kk + 14]
                                +  arow[kk + 15] * brow[kk + 15];
                        }
                        while(kk < gotill){
                            tmp += arow[kk] * brow[kk];
                            kk++;
                        }
                        result->matrix[ii][jj] += tmp;
                    }
                }
            }
        }
    }
    return result;
}

int main()
{
    return 0;
}
