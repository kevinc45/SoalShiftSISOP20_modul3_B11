# SoalShiftSISOP20_modul3_B11

## Kelompok
 - Achmad Sofyan Pratama (05111840000061)
 - Kevin Christian Hadinata (05111840000066)


## Pembahasan Soal 1
>Poke*ZONE adalah sebuah game berbasis text terminal mirip dengan Pokemon GO.
Ketentuan permainan sebagai berikut:
a. Menggunakan IPC-shared memory, thread, fork-exec.
b. Kalian bebas berkreasi dengan game ini asal tidak konflik dengan
requirements yang ada. (Contoh: memberi nama trainer, memberi notifikasi
kalau barang di shop sudah penuh, dan lain-lain).
c. Terdapat 2 code yaitu soal2_traizone.c dan soal2_pokezone.c.
d. soal2_traizone.c mengandung fitur:
i. Normal Mode (3 Menu)
1. Cari Pokemon
a. Jika diaktifkan maka setiap 10 detik akan memiliki
60% chance untuk menemui pokemon bertipe normal,
rare, legendary dengan encounter rate sesuai pada
tabel di bawah (Gunakan Thread).
b. Cari pokemon hanya mengatur dia menemukan
pokemon atau tidak. Untuk tipe pokemon dan pokemon
tersebut shiny atau tidak diatur oleh soal2_pokezone.c.
c. Opsi “Cari Pokemon” akan berubah jadi “Berhenti
Mencari” ketika state mencari pokemon aktif.
d. State mencari pokemon hanya bisa dihentikan ketika
pokemon sudah ditemukan atau trainer memilih untuk
berhenti pada menu.
e. Jika menemui pokemon maka akan masuk ke Capture
Mode.
f. Untuk mempermudah boleh menambah menu go to
capture mode untuk berpindah dari mode normal ke
mode capture setelah menemukan pokemon dari
thread Cari Pokemon.

2. Pokedex
a. Melihat list pokemon beserta Affection Point (AP) yang
dimiliki.
b. Maksimal 7 pokemon yang dimiliki.
c. Jika menangkap lebih dari 7 maka pokemon yang baru
saja ditangkap akan langsung dilepas dan
mendapatkan pokedollar sesuai dengan tabel dibawah.
d. Setiap pokemon yang dimiliki, mempunyai Affection
Point (AP) dengan initial value 100 dan akan terus
berkurang sebanyak -10 AP/10 detik dimulai dari
waktu ditangkap (Gunakan Thread).
e. Jika AP bernilai 0, maka pokemon tersebut memiliki
90% chance untuk lepas tanpa memberikan pokedollar
ke trainer atau 10% chance untuk reset AP menjadi 50
AP.
f. AP tidak akan berkurang jika dalam Capture Mode.

g. Di Pokedex trainer juga bisa melepas pokemon yang
ditangkap dan mendapat pokedollar sesuai dengan
tabel dibawah.
h. Bisa memberi berry ke semua pokemon yang dimiliki
untuk meningkatkan AP sebesar +10 (1 berry untuk
semua pokemon yang ada di pokedex).

3. Shop
a. Membeli item dari soal2_pokezone.
b. Maksimal masing-masing item yang dapat dibeli dan
dipunya oleh trainer adalah 99.

ii. Capture Mode (3 Menu)
1. Tangkap → Menangkap menggunakan pokeball. Berhasil
ditangkap maupun tidak, pokeball di inventory -1 setiap
digunakan.
2. Item → Menggunakan item sesuai dengan tabel item dibawah
(hanya lullaby powder).
3. Keluar → Keluar dari Capture Mode menuju Normal Mode.
● Pokemon tersebut memiliki peluang untuk lari dari trainer
sesuai dengan persentase escape rate pada tabel dibawah
(gunakan thread).
e. soal2_pokezone.c mengandung fitur:
i. Shutdown game → Mematikan program soal2_pokezone dan
soal2_traizone (Gunakan fork-exec).
ii. Jual Item (Gunakan Thread)
1. Stock awal semua item adalah 100.
2. Masing-masing item akan bertambah +10 item/10 detik.
3. Maximum item yang dalam shop adalah 200.
4. List item ada pada tabel dibawah.
No Nama Item Effect Harga
(Pokedollar)
Durasi
(Detik)
Capture
Mode

Normal
Mode

1 Lullaby
Powder

● Meningkatkan chance untuk
menangkap sebesar 20%
(misal normal pokemon jadi
90% capture ratenya).
● Menurunkan escape rate jadi
0% sehingga Pokemon tidak
bisa lari.

60 10 Yes No

2 Pokeball Menangkap pokemon. 5 - Yes No
3 Berry Meningkatkan AP semua
pokemon yang ada di pokedex
sebesar +10.

15 - No Yes

5. Gunakan thread untuk implementasi lullaby powder dibuatkan
masing-masing 1 thread.

iii. Menyediakan Random Pokemon (Gunakan Thread)
1. Setiap tipe pokemon memiliki peluang 1/8000 untuk jadi shiny
pokemon. (Random dulu antara normal, rare, legendary sesuai
rate mereka, baru setelah itu di random dengan peluang
1/8000 untuk tahu dia shiny atau tidak).
2. Shiny Pokemon meningkatkan escape rate sebesar +5%
(misal: tipe normal jadi 10%), capture rate berkurang menjadi
-20% (misal: tipe rare jadi 30%), dan pokedollar dari melepas
+5000 (misal: tipe legendary jadi 5200 pokedollar).
3. Setiap 1 detik thread ini akan mengkalkulasi random ulang lagi
untuk nantinya diberikan ke soal2_traizone.

No Pokemon Type Encounter
Rate

Escape
Rate

Capture
Rate

Pokedollar
dari
melepas

List Nama Pokemon
(random)

1 Normal 80% 5% setiap
20 detik

70% 80 ● Bulbasaur
● Charmander
● Squirtle
● Rattata
● Caterpie

2 Rare 15% 10% setiap
20 detik

50% 100 ● Pikachu
● Eevee
● Jigglypuff
● Snorlax
● Dragonite

3 Legendary 5% 20% setiap
20 detik

30% 200 ● Mew
● Mewtwo
● Moltres
● Zapdos
● Articuno
## Pembahasan Soal 3
>Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan
memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah
sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working
directory ketika program kategori tersebut dijalankan.
● Semisal program dijalankan:
#File kategori terletak di /home/izone/kategori
$ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zi
● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
dikategorikan sebanyak yang user inginkan seperti contoh di atas.
● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
maka dia akan disimpan dalam folder “Unknown”.
● Program kategori ini juga menerima perintah (*) seperti di bawah;
$ ./kategori \*
● Artinya mengkategori seluruh file yang ada di working directory ketika
menjalankan program C tersebut.
● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori
pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory
saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
$ ./kategori -d /path/to/directory/
● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan
hasilnya akan disimpan di working directory di mana program C tersebut
berjalan (hasil kategori filenya bukan di /path/to/directory).
● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
tersebut tidak dihiraukan, cukup file pada 1 level saja.
● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang
juga menggunakan fork-exec dan system.
● Silahkan download soal3.zip sebagai percobaan. Namun silahkan
dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin
belum ada di soal3.zip.

## **Solution!**
Untuk mendapatkan ekstensi dari file-file yang terdapat dalam folder `koleksi`, kelompok kami menggunakan potongan *code* yang terdapat [di sini](https://stackoverflow.com/questions/5309471/getting-file-extension-in-c).

Menggunakan fungsi `strrchr`, kita dapat mengambil *extension* dari mendeteksi simbol titik (.) pada nama *file*.

Untuk memindah *file* dari satu *directory* ke *directory* lain, kita dapat menggunakan fungsi `rename()` yang terdapat dalam *header* `stdio.h` seperti yang dilakukan dalam [situs ini](https://www.daniweb.com/programming/software-development/threads/66448/moving-files-in-c-and-c).

## Kendala Nomor 3
KC: Belum menguasai *thread* sehingga masih belum dapat melakukan implementasi.


## Kendala & Penjelasan nomer 4.a
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
eyJoaXN0b3J5IjpbMzEyODMyNDldfQ==
-->