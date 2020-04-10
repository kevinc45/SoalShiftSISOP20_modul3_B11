# SoalShiftSISOP20_modul3_B11

## Kelompok
 - Achmad Sofyan Pratama (05111840000061)
 - Kevin Christian Hadinata (05111840000066)


## Pembahasan Soal 1
Belum dapat terselesaikan karena terkendala belum menguasai thread.

## Pembahasan Soal 3

Untuk mendapatkan ekstensi dari file-file yang terdapat dalam folder `koleksi`, kelompok kami menggunakan potongan *code* yang terdapat [di sini](https://stackoverflow.com/questions/5309471/getting-file-extension-in-c).

Menggunakan fungsi `strrchr`, kita dapat mengambil *extension* dari mendeteksi simbol titik (.) pada nama *file*.

Untuk memindah *file* dari satu *directory* ke *directory* lain, kita dapat menggunakan fungsi `rename()` yang terdapat dalam *header* `stdio.h` seperti yang dilakukan dalam [situs ini](https://www.daniweb.com/programming/software-development/threads/66448/moving-files-in-c-and-c).

## Kendala Nomor 3
KC: Belum menguasai *thread* sehingga masih belum dapat melakukan implementasi.


## Kendala & Penjelasan nomer 4.a
>4a.)
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan
matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.
> 4b.) 
1. Buatlah program C kedua dengan nama "4b.c". Program ini akan
mengambil variabel hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(Catatan!: gunakan shared memory)
2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan
format seperti matriks.
>4c.)
1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.


```
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/ipc.h>


int (*value)[10];
int hasil = 0;
int matA[10][10], matB[10][10], 
                        RowOf_A =4 , ColumnOf_A=2, RowOf_B=2, ColumnOf_B=5; 
pthread_t thread1, thread2, final; 

//matriks pertama
void *A(void *arg) { 
   matA[0][0]=2; 
   matA[0][1]=1; 
   matA[1][0]=4; 
   matA[1][1]=3; 
   matA[2][0]=2; 
   matA[2][1]=1; 
   matA[3][0]=4; 
   matA[3][1]=3;
   return NULL;
}

void *B(void *arg){
   matB[0][0]=4;
   matB[0][1]=1; 
   matB[0][2]=2;
   matB[0][3]=3; 
   matB[0][4]=1; 
   matB[1][0]=2;
   matB[1][1]=1; 
   matB[1][2]=3; 
   matB[1][3]=1; 
   matB[1][4]=3; 
   return NULL;
}

void *matrix_multiplication(void *arg){
   for(int i=0;i<RowOf_A;i++){
      for(int j=0;j<ColumnOf_B;j++){
         for(int k=0;k<ColumnOf_A;k++){
            hasil+=matA[i][k] * matB[k][j]; 
         }
         value[i][j]= hasil; 
         hasil = 0; 
      }
   }
   return NULL;
}

int main(){
   
   key_t key = 1234;
   int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666); 
   value = shmat(shmid, 0, 0);

   pthread_create(&thread1, NULL, A, NULL); 
   pthread_join(thread1,NULL);

   pthread_create(&thread2, NULL, B, NULL); 
   pthread_join(thread2,NULL);

   for(int i=0;i<RowOf_A;i++){
      for(int j=0;j<ColumnOf_B;j++){ 
         value[i][j]=0;
      }
      pthread_create(&final, NULL, matrix_multiplication, NULL); 
      pthread_join(final,NULL);
   }

  
   printf("A*B : \n");
   for(int i=0; i<RowOf_A; i++){ 
      for(int j=0;j<ColumnOf_B;j++){  
         printf("%d\t", value[i][j]); 
      }
      printf("\n");
   }
}
```

