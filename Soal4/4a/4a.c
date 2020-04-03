#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define M 4
#define K 2
#define N 4
 
void *runner (void *param);
 
int A [M][K] = { {1,4}, {2,5}, {3,6}, {3,6} }; 
int B [K][N] = { {8,7,7,8}, {5,4,2,9} }; 
int C [M][N]; 
 

struct v
{
 int i; 
 int j; };
 
int main()
{
 pthread_t tid [M*N]; 
 int i; 
 int j; 
 int indeks; 
 
 for (i = 0; i < M; i++){
    for (j = 0; j < N; j++){
 struct v *data = (struct v*) malloc (sizeof (struct v)); 
 data -> i = i;
 data -> j = j; 
 pthread_create (&tid[indeks++], NULL, runner, (void *) data); 
 
        }
    }
 
 for (indeks = 0; indeks < M*N; indeks++){
 
 
 pthread_join (tid[indeks], NULL); 
 
 
 }
 

 printf ("Hasil:\n");
 for (i = 0; i < M; i++){
     for (j = 0; j < N; j++)
        {
       
       
        printf ("\t\t%d ", C[i][j]);
    
    }
    
    
    printf ("\n");
    
    
    }
}
 

void *runner (void *param)
{
 struct v *par = (struct v*) param; 
 int h; 
 int i = par -> i; 
 int j = par -> j; 
 int hasil = 0; 
 
 for (h = 0; h < K; h++){
 hasil += A[i][h] * B[h][j]; 
 C[i][j] = hasil; 
    }
}
