
# SoalShiftSISOP20_modul3_B11






## Kendala & penjelasan nomer 4.a
>Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri
jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap
pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda.
Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat
mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di
pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada
batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan
matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.

```
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

```



```
int A [M][K] = { {1,4}, {2,5}, {3,6}, {3,6} }; 
int B [K][N] = { {8,7,7,8}, {5,4,2,9} }; 
int C [M][N]; 
 

struct v
{
 int i; 
 int j; };
 
 ```
 
 
 Pertama-tama saya tentukan array dimana array pertama dengan orgo M*K yang disimpan di integer A 
 begitupun yang B dengan ordo K*N didimpan di B
 
 untuk integer C ialah hasil dimana hasil perkalian A dan B adalah M*N
 
 terus disitu saya buat struct v untuk mempassing data thread 
 didalam struct tersebut ada integer i dan j ditunjukkan untuk menunjukkan baris dan kolom 
 
 
 kemudian buat fungsi untuk melakukan perkalian matriks dengan nama runner
 
```
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
```

didalam runner saya mengeset objek structure v bernama par dengan param
setelah itu mengeset nilai i dengan nilai i pada par begitu pula dengan j
next hasil didefiniskan dengan menambahkan semua hasil perkalian baris i kolom h dengan baris h kolom j
kemudian mengeset nilai matriks C pada baris i dan kolom j dengan hasil
 
 
```
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
 
 ```
 
 Disini kita masuk di main 
 Array of thread bernama tid dengan size M*N dan disitu saya buat integer indeks 
 untuk menunjukkan indeks pada array of thread 
 
 kemudian masuk di proses 2x looping 
 ``` struct v *data = (struct v*) malloc (sizeof (struct v)); ```
 membuat objek structure v bernama data dengan mengalokasikan memori 
 sebesar size dari structure v
  
 Kemudian mengeset nilai i dan j pada objek structure v bernama data dengan nilainya sendiri ( i dan j )
 
 Setelah itu membuat thread pada array of thread tid pada indeks ke-indeks dengan memanggil fungsi runner 
 dengan parameter data menggunakan pthread_create


kemudian nelakukan join untuk menggabungkan thread-thread yang ada
```
for (indeks = 0; indeks < M*N; indeks++)
 {
 pthread_join (tid[indeks], NULL); 
 }
```

Kemudian print hasil
 ```
 printf ("Hasil:\n");
 for (i = 0; i < M; i++){
     for (j = 0; j < N; j++)
        {
       
       
        printf ("\t\t%d ", C[i][j]);
    
    }
    
    
    printf ("\n");
    
    
    }
 
 ```

## kendala

Belum bisa outputnya keluar 4x5  

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTk5MTMyNTM4MF19
-->