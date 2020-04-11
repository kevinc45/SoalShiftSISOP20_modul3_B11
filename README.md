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
Pokedex diakses untuk mengetahui apa saja Pokemon yang sudah kita tangkap, memberikan informasi soal AP yang dimiliki, melepas pokemon, dan memberikan *berry* ke semua pokemon yang dimiliki.

Apabila kita melepas Pokemon, maka kita akan mendapat *Pokedollar* dengan jumlah tertentu sesuai dengan *rarity* pokemon tersebut.

Pokemon juga dilengkapi dengan AP yang merupakan *Affection Points* yang menjadi parameter apakah pokemon kita akan lepas atau tetap menjadi pokemon yang berpetualang bersama kita.

Semua proses yang 

Selain digunakan untuk melakukan pengacakan pada pokemon yang sedang dicari, *shared memory* digunakan juga untuk melakukan pembaruan stok pada barang-barang yang dijual di toko.

## Pembahasan Soal 2

>Screen 1 :
1. Login
2. Register
Choices : {your input}
★ Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter
anda diminta untuk menginputkan username dan password seperti berikut
Screen 1 :
1. Login
2. Register
Choices : login
Username : { ex : qiqi }
Password : { ex : aku nggak marah!! }
★ Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal
akan menampilkan pesan “login failed” (pengecekan login hanya mengecek
username dan password, maka dapat multi autentikasi dengan username dan
password yang sama)
★ Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan
enter anda diminta untuk menginputkan username dan password sama
halnya seperti login
★ Pada register tidak ada pengecekan unique username, maka setelah register
akan langsung menampilkan pesan “register success” dan dapat terjadi
double account
★ Setelah login berhasil maka anda berpindah ke screen 2 dimana
menampilkan 2 fitur seperti berikut.

Screen 2 :
1. Find Match
2. Logout
Choices : {your input}
★ Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan
kembali ke screen 1
★ Pada screen 2 anda dapat menginputkan “find”, setelah itu akan
menampilkan pesan “Waiting for player ...” print terus sampai menemukan
lawan
★ Jika menemukan lawan maka akan menampilkan pesan “Game dimulai
silahkan tap tap secepat mungkin !!”
★ Pada saat game dimulai diberikan variable health = 100,dan anda dapat
men-tap (menekan space pada keyboard tanpa harus menekan enter)
★ Pada saat anda men-tap maka akan menampilkan pesan “hit !!”, dan pada
lawan healthnya akan berkurang sebanyak 10 kemudian pada lawan
menampilkan pesan status healthnya sekarang. (conclusion : anda tidak bisa
melihat status health lawan)
★ Jika health anda <= 0 maka akan menampilkan pesan “Game berakhir kamu
kalah”, apabila lawan anda healthnya <= 0 maka akan menampilkan pesan
”Game berakhir kamu menang”
★ Setelah menang atau kalah maka akan kembali ke screen 2

SERVER SIDE

★ Pada saat program pertama kali dijalankan maka program akan membuat file
akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan
username dan password
★ Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika
gagal “Auth Failed”
★ Pada saat user sukses meregister maka akan menampilkan List account yang
terdaftar (username dan password harus terlihat)


Berikut code Screen satu, untuk menangani login dan register :
```
printf("1. Login\n2. Register\nChoices : ");
    scanf("%s", arr1);
    if(strcmp(arr1, "login") == 0)
    {
        strcpy(username, "l ");
        printf("Username : ");
        getchar();
        scanf("%[^\n]", username);
        strcat(username, temp);
        printf("Password : ");
        getchar();
        scanf("%[^\n]", password);
        strcat(username, "\t");
        strcat(username, password);
        send(sock, username, strlen(username), 0);
        int back;
        read(sock, &back, sizeof(back));
        if(back)
        {
            printf("login success\n");
            send(sock, "sukses", 6, 0);
            screen2:
            printf("1.MENCARI...\n2. Logout\nChoices : ");
            scanf("%s", arr2);
            if(strcmp(arr2, "logout") == 0)
            {
                send(sock, arr2, strlen(arr2), 0);
                goto screen1;
            
            else if(strcmp(arr2, "find") == 0)
            {
                int start;
                send(sock, arr2, strlen(arr2), 0);
                pthread_t th;
                pthread_create(&th, NULL, MencariPlayer, NULL);
                read(sock, &start, sizeof(start));
                pthread_cancel(th);
                printf("Game dimulai silahkan \e[3mtap tap\e[0m secepat mungkin !!\n");
                struct termios prev, cur;
                tcgetattr(0, &prev);
                cur = prev;
                cur.c_lflag &= -ICANON;
                cur.c_lflag &= -ECHO;
                tcsetattr(0, TCSANOW, &cur);
                pthread_t th2;
                pthread_create(&th2, NULL, GO, (void *) &sock);
                int health = 100;
                while(1)
                {
                    read(sock, &health, sizeof(health));
                    if(health == -1) break;
                    printf("Health: %d\n", health);
                }
                pthread_cancel(th2);
                bool cek;
                read(sock, &cek, sizeof(cek));
                if(cek) printf("Game over YOU WIN\n");
                else printf("Game over YOU LOSE\n");
                tcsetattr(0, TCSANOW, &prev);
                goto screen2;
            }
            else
            {
                printf("invalid input\n");
                goto screen2;
            }
            
        }
        else
        {
            printf("login failed\n");
            goto screen1;
        }
    }
    else if(strcmp(arr1, "register") == 0)
    {
        strcpy(username, "r ");
        printf("Username : ");
        getchar();
        scanf("%[^\n]", temp);
        strcat(username, temp);
        printf("Password : ");
        getchar();
        scanf("%[^\n]", pass);
        strcat(username, "\t");
        strcat(username, pass);
        send(sock, username, strlen(username), 0);
        printf("register success\n");
        goto screen1;
    }
    else
    {
        printf("invalid input\n");
        goto screen1;
    }

```
Untuk memberikan value ke string pada variabel harus menggunkan strcpy karena ini 
digunnakan untuk string copy,sedangkan untuk menggabuingkan string digunnakan fungsi strcat
artinya membaca 2 varibel string tersebut atau berarti string concat
untuk mengatasi username dan password memiliki spasi karena scanf standard tidak bisa digunakan  
sehingga harus menggnakan scanf("%[\n]", &str); 

dimana scanf tersebut berfungsi scan terus inputan tersebut sampai menemui karakter \n.

dibagian ini input username dan pass dari login akan register akan dipassing menggunakan
system call send() untuk membedakan input login dan register kita menambahkan karakter huruf
untuk membedakanya saat ingin dipassing

Untuk screen 2, akan ada 2 thread yang dijalankan thread pertama untuk mencetak "Menunggu Pemain ..." ketika belum ditemukan client lain yang sedang mencari match juga. Thread ini akan terus berjalan setiap detik, sampai dicancel saat sudah menemukan player lain. Untuk mengecek apakah sudah ada player lain yang dapat bermain, digunakan fungsi read();, di mana variabel start akan dipassing dari server side yang menandakan bahwa game sudah siap dimulai karena sudah ada 2 client yang terkoneksi ke server di waktu yang sama. Kemudian di sini kami juga menggunakan fungsi termios agar saat bermain, saat user menginputkan karakter spasi, langsung terbaca menembak musuh tanpa harus menekan enter. Saat bermain maka akan dijalankan thread yang berfungsi menunggu player saat menginput spasi untuk menembak musuh. Saat health salah satu player sudah habis (<= 0), maka server akan mengirimkan socket value health -1, yang menandakan game dihentikan, kemudian server mengirimkan kode ke masing-masing player apakah ia menang atau kalah.



Berikut code Screen 2, untuk menangani find player agar dapat memulai game:

```
void *MencariPlayer()
{
    while(1)
    {   
        printf("Menunggu player...\n");
        sleep(1);
    }
}

void *GO(void *arg)
{
    while(1)
    {
        char ch = getchar();
        if(ch == ' ') 
        {
            printf("hit !!\n");
            send(*(int*) arg, &ch, sizeof(ch), 0);
        }
    }
}


 screen2:
            printf("1.MENCARI...\n2. Logout\nChoices : ");
            scanf("%s", arr2);
            if(strcmp(arr2, "logout") == 0)
            {
                send(sock, arr2, strlen(arr2), 0);
                goto screen1;
            
            else if(strcmp(arr2, "find") == 0)
            {
                int start;
                send(sock, arr2, strlen(arr2), 0);
                pthread_t th;
                pthread_create(&th, NULL, MencariPlayer, NULL);
                read(sock, &start, sizeof(start));
                pthread_cancel(th);
                printf("Game dimulai silahkan \e[3mtap tap\e[0m secepat mungkin !!\n");
                struct termios prev, cur;
                tcgetattr(0, &prev);
                cur = prev;
                cur.c_lflag &= -ICANON;
                cur.c_lflag &= -ECHO;
                tcsetattr(0, TCSANOW, &cur);
                pthread_t th2;
                pthread_create(&th2, NULL, GO, (void *) &sock);
                int health = 100;
                while(1)
                {
                    read(sock, &health, sizeof(health));
                    if(health == -1) break;
                    printf("Health: %d\n", health);
                }
                pthread_cancel(th2);
                bool cek;
                read(sock, &cek, sizeof(cek));
                if(cek) printf("Game over YOU WIN\n");
                else printf("Game over YOU LOSE\n");
                tcsetattr(0, TCSANOW, &prev);
                goto screen2;
            }
            else
            {
                printf("invalid input\n");
                goto screen2;
            }
            
        }
```

Code Server side  :
```
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
#define PORT 8080

typedef struct account {
    char a[1024];
    char b[1024];
} account;

typedef struct client_serv {
    int cid;
    int login;
} client_serv;

typedef struct player {
    int cidp, cide;
    int *healthp, *healthe;
} player;

account list_akun[100];
bool cekakun, cekfile, cekel;
int lk, akun_n;

void *ready(void *arg)
{
    client_serv cl = *(client_serv *) arg;
    int cid = cl.cid;
    int log = cl.login;
    if(log)
    {
        screen1:;
        char data[1024], a[1024], b[1024], kode;
        memset(data, 0, sizeof(data));
        read(cid, data, sizeof(data));
        kode = data[0];
        int id = 0;
        for(int i = 2; i < strlen(data); i++)
        {
            if(data[i] == '\t') break;
            a[id] = data[i];
            id++;
        }
       
        int id2 = 0;
        id += 3;
        for(int j = id; j < strlen(data); j++)
        {
            b[id2] = data[j];
            id2++;
        }
       
        if(kode == 'l')
        {
            bool done = 0;
            while(cekakun);
            for(int i = 0; i < akun_n; i++)
            {
                if((strcmp(a, list_akun[i].a) == 0) && (strcmp(b, list_akun[i].b) == 0))
                {
                    done = 1;
                    break;
                }
            }
            send(cid, &done, sizeof(done), 0);
            if(done) printf("Auth success\n");
            else
            {
                printf("Auth Failed\n");
                goto screen1;
            }
        }
        else if(kode == 'r')
        {
            cekakun = 1;
            account akun_pendaftaran;
            strcpy(akun_pendaftaran.a, a);
            strcpy(akun_pendaftaran.b, b);
            list_akun[akun_n] = akun_pendaftaran;
            akun_n++;
            while(cekfile);
            cekfile = 1;
            FILE *fptr = fopen("akun.txt", "a");
            fprintf(fptr, "%s\t%s\n", a, b);
            fclose(fptr);
            cekfile = 0;
            cekakun = 0;
            printf("Username\tPassword\n");
            for(int i = 0; i < akun_n; i++)
            {
                account cur = list_akun[i];
                printf("%s\t%s\n", cur.a, cur.b);
            }
        }
    }
    log = 1;
    char cmdt;
    read(cid, &cmdt, strlen(&cmdt));
    if(strcmp(&cmdt, "logout") == 0) goto screen1;
    else if(strcmp(&cmdt, "find") == 0)
    {
        while(cekel);
        cekel = 1;
        lk++;
        cekel = 0;
        while(lk < 2);
    }
    pthread_exit(0);
}

void *play(void *arg)
{
    player p = *(player *) arg;
    int *he = p.healthe;
    int start = 1;
    send(p.cidp, &start, sizeof(start), 0);
    while(1)
    {
        char ch;
        read(p.cidp, &ch, sizeof(ch));
        *he -= 10;
        send(p.cide, he, sizeof(*he), 0);
    }
}

int main(int argc, char const *argv[])
{
    int c = 0;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(0);
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(0);
    }

    if(listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(0);
    }

    FILE *fp;
    char ch, a[1024], b[1024];
    int id = 0;
    fp = fopen("akun.txt", "a+");
    if(fp == NULL) exit(0);
    while(fscanf(fp, "%[^\t]\t%[^\n]\n", a, b) != EOF)
    {
        account akun_baru;
        strcpy(akun_baru.a, a);
        strcpy(akun_baru.b, b);
        list_akun[id] = akun_baru;
        id++;
    }
    fclose(fp);
    akun_n = id;
    cekakun = 0;
    cekfile = 0;
    lk = 0;
    cekel = 0;

    pthread_t th[2];
    int client[2];
    for(int i = 0; i < 2; i++)
    {
        client[i] = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
        if(client[i] < 0)
        {
            perror("can't accept client\n");
            i--;
            continue;
        }
        printf("client accepted\n");
        client_serv client_baru;
        client_baru.cid = client[i];
        client_baru.login = 1;
        pthread_create(&th[i], NULL, ready, (void *) &client_baru);
    }

    while(1)
    {
        bool player1_cek = 0;
        bool player2_cek = 0;
        int darah1 = 100;
        int darah2 = 100;
        player pemain1, pemain2;
        pemain1.cidp = client[0];
        pemain1.cide = client[1];
        pemain1.healthp = &darah1;
        pemain1.healthe = &darah2;
        pemain2.cidp = client[1];
        pemain2.cide = client[0];
        pemain2.healthp = &darah2;
        pemain2.healthe = &darah1;
        pthread_create(&th[0], NULL, play, (void *) &pemain1);
        pthread_create(&th[1], NULL, play, (void *) &pemain2);
        while(1) if(darah1 <= 0 || darah2 <= 0) break;
        pthread_cancel(th[0]);
        pthread_cancel(th[1]);
        int fin = -1, win = 1, lose = 0;
        send(client[0], &fin, sizeof(fin), 0);
        send(client[1], &fin, sizeof(fin), 0);
        lk -= 2;
        if(darah1 <= 0)
        {
            send(client[0], &lose, sizeof(lose), 0);
            send(client[1], &win, sizeof(win), 0);
        }
        else if(darah2 <= 0)
        {
            send(client[0], &win, sizeof(win), 0);
            send(client[1], &lose, sizeof(lose), 0);
        }
        for(int i = 0; i < 2; i++)
        {
            client_serv p;
            p.cid = client[i];
            p.login = 1;
            pthread_create(&th[i], NULL, ready, (void *) &p);
        }
        pthread_join(th[0], NULL);
        pthread_join(th[1], NULL);
    }
    return 0;
}

```
Pada Server Side, digunakan untuk verifikasi client yang sedang login/register, untuk penyimpanan data ke akun.txt
, serta pengecekan data saat login apakah akun sudah terdaftar. 

Kemudian pada server side, juga berfungsi untuk mencari player-player yang dapat saling terkoneksi, ketika banyak yang terkoneksi ada 2 player, maka game akan segera dimulai. 

Ketika sudah selesai, maka koneksi mereka akan diputus menjadi bukan yang sedang bermain. Ruang bermain hanya dibatasi 2 player saja, yang masing-masing mempunyai thread sendiri.

Untuk menyimpan data suatu player, yaitu thread sendiri, thread musuh, health sendiri, dan health musuh, digunakan struct player yang menyimpan itu semua.

## Pembahasan Soal 3

Untuk mendapatkan ekstensi dari file-file yang terdapat dalam folder `koleksi`, kelompok kami menggunakan potongan *code* yang terdapat [di sini](https://stackoverflow.com/questions/5309471/getting-file-extension-in-c).

Menggunakan fungsi `strrchr`, kita dapat mengambil *extension* dari mendeteksi simbol titik (.) pada nama *file*.

Untuk memindah *file* dari satu *directory* ke *directory* lain, kita dapat menggunakan fungsi `rename()` yang terdapat dalam *header* `stdio.h` seperti yang dilakukan dalam [situs ini](https://www.daniweb.com/programming/software-development/threads/66448/moving-files-in-c-and-c).

## Kendala Nomor 3
KC: Belum menguasai *thread* sehingga masih belum dapat melakukan implementasi.


## Pembahasan nomer 4
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
eyJoaXN0b3J5IjpbLTQ1MjgxNjIzMiw1NTQwNjExMDAsNjc1ND
Q5NTc4XX0=
-->
