# SoalShiftSISOP20_modul3_B11

## Kelompok
 - Achmad Sofyan Pratama (05111840000061)
 - Kevin Christian Hadinata (05111840000066)

## Pembahasan Soal 1
Pada soal nomor 1, kita akan berpetualang sebagai seorang *Pokemon trainer* menggunakan bantuan *thread*, *mutual exclusion*, dan *shared memory*.

**Kata Kunci**
 - Thread
 - Mutual Exclusion
 - Shared Memory
 
Sebagai *title* game terbaru dari *franchise* permainan Pokemon, **Poke*ZONE** membagi permainannya menjadi 3 fungsi utama:
 1. Mencari Pokemon
 2. Membuka Pokedex
 3. Membeli di PokeMart/Shop

**Mencari Pokemon**
Saat kita ingin mencari pokemon, program akan meng-*generate* sebuah pokemon secara *random* setiap 10 detik dengan kemungkinan 60%.

Di program ```soal2_pokezone.c```, kita sudah membuat fungsi *Pokemon Randomizer* untuk menentukan pokemon dengan ID berapa yang akan muncul saat kita sedang mencari Pokemon.
```c
void* randompokemon(){
    for(;;){
        int pokemon;
        int randomizer = rand() % 100;
        int shinyrandomizer = rand() % 8000;
        if (randomizer < 5) pokemon = (rand() % 5) + 10;
        else if (randomizer < 15) pokemon = (rand() % 5) + 5;
        else pokemon = (rand() % 5);
        if (shinyrandomizer == 1)pokemon += 15;
        *sharedpoke = pokemon;
        sleep(1);
    }
}
```

Setelah itu, pada ```soal2_traizone.c```, kita menambahkan probabilitas sebesar 60% dan menjalankan fungsinya setiap 10 detik (menggunakan ```sleep(10)```).

```c
void *searchthread(){
	for(;;){
		sleep(10);
		if(rand() % 100 < 60){
			search = 0;
			pthread_mutex_lock(&pokemonc);
			capture = *sharedpoke;
			pthread_mutex_unlock(&pokemonc);
			pthread_exit(0);
		}
	}
}
```

Untuk melakukan perpindahan *value* antar program, kita menggunakan ***shared memory***. Menurut [Wikipedia](https://en.wikipedia.org/wiki/Shared_memory),
```
Shared Memory adalah memori yang dapat diakses secara bersamaan oleh beberapa program dengan tujuan menghubungkan program-program tersebut atau untuk menghindari salinan yang berlebihan/tidak penting.
```

**Membuka Pokedex**
Pokedex di

Selain digunakan untuk melakukan pengacakan pada pokemon yang sedang dicari, *shared memory* digunakan juga untuk melakukan pembaruan stok pada barang-barang yang dijual di toko.


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

Disitu pertama kita deklarasi matriks kemudian kita buat ada 3 thread 
dimana thread yang pertama digunakan untuk input matriks A
kemudian thread yang kedua digunakan untuk input matriks B 
dan yang terakhir untuk perkalian matriks A dana B

ketika memasuki int main kita menggunakan shared memory agar bisa tetap
terhubung dengan yang lain dan nantinya akan di faktorialkan hasil dari matriks ini.


```
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>


unsigned long long num; 
int row = 4, column = 5; 

unsigned long long factorial(unsigned long long a){  
    if(a==0 || a==1) return 1;
    else return a+ factorial(a-1); 
}

//fungsi faktorial
void *faktorial(void *arg){
    
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    
    printf("Hasil faktorial pertambahan matriks ialah: \n");
    
    for(int i=0;i<row;i++){ 
        for(int j=0;j<column;j++){ 
            num=value[i][j]; 
            printf("%llu\t", factorial(num)); 
        }
        printf("\n");
    }
    pthread_exit(0); // keluar thread
}

void main(){
    pthread_t thread;
    
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid,NULL ,0 );

    printf("Hasil perkalian dari matriks A dan B adalah: \n");
    
    for(int i=0;i< 4;i++){
        for(int j=0;j<5;j++){
            printf("%d\t", value[i][j]);
        }
        printf("\n");
    }
    pthread_create(&thread, NULL, faktorial, NULL); 
    pthread_join(thread,NULL); 
}

```

kita buat deklarasi matriks baru dengan menggunakan unsigned long long agar dapat menampung angka lebih banyak.
kemudian kita buat rekursif faktorial 

Setelah itu,  kita buat fungsi faktorial digunakan untuk menhitung satu persatu dari hasil matriks di code sebelumnya
dengan memanggil fungsi rekursif factorial 
dan tak lupa juga untuk menggunakan shared memory agar hasil dari code sebelumnya dapat terhubung.

didalam int main terdapat printf untuk menampilkan hasil dari code 4a 
kemudian pthread sendiri untuk menampilkan hasil dari faktorial yang ada di fungsi faktorial


```
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>
#include<unistd.h>


int main(){
    int p[2];
    pid_t pp;
    if(pipe(p) == -1)
    {
        fprintf(stderr, "pipe failed");
        return 1;
    }
    pp = fork();
    if(pp < 0){
        fprintf(stderr, "fork failed");
    }
    else if(pp !=  0) //parent process
    {
        close(0);
        dup2(p[0], 0);  
        close(p[0]);
        close(p[1]);
        char *argv[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argv);
    }
    else //child
    {
        close(0);
        dup2(p[1], 1);
        close(p[0]);
        close(p[1]);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
    }
    
    
}
```

Disoal ini kita di suruh untuk menghitung jumlah folder dan file di dalam direktori 
dengan menggunakan system command 'ls' dan 'wc -l'
dimana command ls digunakan untuk list folder dan file yang ada di sebuah direktori 
dan command wc -l sendiri biasanya digunakan untuk prints the number of lines in a file.
dalam kasus ini kami menggunakan dup2 dimana berfungsi untuk system call membuat salinan deskriptor file, 
dan nantinya akan ditulis dan dibaca oleh pipe dan dieksekusi dengan execv 

```
char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
```
dan 

```
 char *argv[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argv);
```
dimana kita dapat mengetahui command wc berada di /usr/bin/wc 
dan command ls berada di /bin/ls
cukup dengan menggunakan terminal dan ketik "whereis wc" dan "whereis ls"
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTc1MzE2ODg5Myw1NTQwNjExMDAsNjc1ND
Q5NTc4XX0=
-->