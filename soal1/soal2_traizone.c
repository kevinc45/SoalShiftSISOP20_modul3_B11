#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int inputmenu,mode,search,capture,lullaby_a,slot,PokemonAP[8],pokemon[8],pokedollar, powder, pokeball, berry,choosepoke, nextinput, nextinput2,uangganti;
pthread_mutex_t pokemonslot,pokemonm,pokemonc;
pthread_t t_pokemon[8], t_lullaby, t_input, t_search;
int* sharedpoke, sharedlullaby, sharedpokeball, sharedberry;

char *namapokemon[35] = {
	"Bulbasaur",
	"Charmander",
	"Squirtle",
	"Rattata",
	"Caterpie",
	"Pikachu",
	"Eevee",
	"Jigglypuff",
	"Snorlax",
	"Dragonite",
	"Mew",
	"Mewtwo",
	"Moltres",
	"Zapdos",
	"Articuno",
	"Shiny Bulbasaur",
	"Shiny Charmander",
	"Shiny Squirtle",
	"Shiny Rattata",
	"Shiny Caterpie",
	"Shiny Pikachu",
	"Shiny Eevee",
	"Shiny Jigglypuff",
	"Shiny Snorlax",
	"Shiny Dragonite",
	"Shiny Mew",
	"Shiny Mewtwo",
	"Shiny Moltres",
	"Shiny Zapdos",
	"Shiny Articuno"
};

void *input() {scanf("%d",&inputmenu);}

void *lullabythread(){
	for(;;) sleep(10);
		lullaby_a=0;
	printf("Lullaby Powder habis!\n");
	pthread_exit(0);
}

void *capturethread(){
	int par = (capture % 15)/5;
	if (par == 0) par=5;
	else if (par == 1) par=10;
	else if (par == 2) par=20;
	if(capture >= 15) par += 5;
	for(;;){
		sleep(20);
		if(lullaby_a!=0){
			printf("Wild Pokemon fled!\n");
			pthread_mutex_lock(&pokemonc);
			capture = -1;
			pthread_mutex_unlock(&pokemonc);
			pthread(exit);
		}
		else continue;
	}
}

void *pokemonthread(){
	int s = slot;
	pthread_mutex_unlock(&pokemonslot);
	for(;;){
		sleep(10);
		if (mode==0){
			pthread_mutex_lock(&pokemonm);
			PokemonAP[s] -= 10;
			if (PokemonAP[s] <= 0){
				if (rand()%100>=90) PokemonAP[s] = 50;
				else {
					printf( "Pokemon-mu lepas!\n");
					pokemon[s] = -1;
					PokemonAP[s] = -1;
					pthread_exit(0);
				}
				pthread_mutex_unlock(&pokemonm);
			}
		}
		else continue;
	}
}

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

int main(){
	srand(time(NULL));
	key_t k_pokemon = 1111;
	key_t k_lullaby = 2222;
	key_t k_pokeball = 3333;
	key_t k_berry = 4444;
	int sharedidpoke = shmget(k_pokemon, sizeof(int), IPC_CREAT | 0666);
	sharedpoke = shmat(sharedidpoke, NULL, 0);
	int sharedidlullaby = shmget(k_lullaby,sizeof(int), IPC_CREAT | 0666);
	sharedlullaby = shmat(sharedidlullaby, NULL, 0);
	int sharedidpokeball = shmget(k_pokeball,sizeof(int), IPC_CREAT | 0666);
	sharedpokeball = shmat(sharedidpokeball, NULL, 0);
	int sharedidberry = shmget(k_berry,sizeof(int),IPC_CREAT | 0666);
	sharedberry = shmat(sharedidberry, NULL, 0);
	
	capture=-1;
	
	memset(pokemon,-1,sizeof(pokemon));
	memset(PokemonAP,-1,sizeof(PokemonAP));
	memset(t_pokemon,0,sizeof(t_pokemon));

	pthread_mutex_init(&pokemonslot, NULL);
	pthread_mutex_init(&pokemonc, NULL);
	pthread_mutex_init(&pokemonm, NULL);
	
	mode=0; search = 0;
	pokedollar=250;
	powder = 0; berry = 0; pokeball = 0;
	lullaby_a = 0, pokecount=0;
	for(;;){
		printf("Selamat datang di Poke*ZONE!\n");
		if (mode==0){
			if (search) printf("[NORMAL]\n1. Stop Search\n2. Pokedex\n3. Shop\n4. Go to Capture Mode\n");
			else printf("[NORMAL]\n1. Cari Pokemon\n2. Pokedex\n3. Shop\n4. Go to Capture Mode\n");
			pthread_create(&t_input,NULL,input,NULL);
			pthread_join(t_input,NULL);
			if (inputmenu == -1 ){
				printf("\n");
				continue;
			}
			elseif (inputmenu == 1){
				search=!search;
				if(search) pthread_create(&t_search,NULL,searchthread,NULL);
				else pthread_cancel(t_search);
			}
			else if (inputmenu == 2){
				printf("==POKEDEX==\n");
				printf("Slot Pokemon[AP]\n");
				for(int x=0;x<7;x++){
					printf("%d. ", x+1);
					if(pokemon[x]==-1) printf("- -\n");
					else printf("%-20s[%d]\n", namapokemon[pokemon[x]],PokemonAP[x]);
				}
				printf("\n==Pokedex Menu==\n1. Lepas Pokemon\n2. Berry time!\n3. Kembali\n");
				scanf("%d",&nextinput);
				if(nextinput==1){
					printf("Pilih Pokemon yang mau kamu lepas:\n");
					for(int x=0;x<7;x++){
						printf("%d. ", x+1);
						if(pokemon[x]==-1) printf("- -\n");
						else printf("%-20s\n", namapokemon[pokemon[x]]);
					}
					choosepoke=-1
					for(;;){
						scanf("%d",&choosepoke);
						if (choosepoke>0 && choosepoke<=7 && pokemon[choosepoke-1] != -1) break;
						else printf("Invalid Input!\n");
					}
					pthread_mutex_lock(&pokemonm);
					pthread_cancel(t_pokemon[choosepoke-1]);
					if (pokemon[choosepoke-1] >= 15)pokedollar += 5000;
					else if (pokemon[choosepoke-1] < 5)pokedollar +=80;
					else if (pokemon[choosepoke-1] < 10)pokedollar +=100;
					else if (pokemon[choosepoke-1] < 15)pokedollar +=200;
					pokeon[choosepoke-1] = -1;
					PokemonAP[choosepoke-1] = 0;
					pthread_mutex_unlock(&pokemonm);
					break;
				}

				else if(nextinput==2){
					if (berry==0) printf("Kamu tidak punya berry!\n");
					else{
						pthread_mutex_lock(&pokemonm);
						for (int x=0;x<7;x++){
							if(pokemon[x]!=-1) PokemonAP += 10;
						}
						pthread_mutex_unlock(&pokemonm);
						printf("Pokemon-mu terlihat senang!\n");
					}
				}
				else if(nextinput==3) printf("Pokedex ditutup.\n");
			}
			else if(inputmenu==3){
				printf("==Selamat datang di PokeMart!==\n");
				printf("No  Item            Inven  Stok  Harga\n");
				printf("---------------------------------------\n");
				printf("1.  Lullaby Powder  %-3d    %-3d   60\n", lullaby, *sharedlullaby);
				printf("2.  Pokeball        %-3d    %-3d   5\n", pokeball, *sharedpokeball);
				printf("3.  Berry           %-3d    %-3d   15\n", berry, *sharedberry);
				printf("4. Kembali\n");
				scanf("%d",&nextinput);
				printf("Jumlah: ");
				int am;
				scanf("%d", &am);
				if (am > 99) {
					printf("Pembelian Gagal.\n");
					return;
				}
				if (x == 1) {
					if (am <= *sharedlullaby && lullaby + am <= 99 && pokedollar >= am * 60) {
						*sharedlullaby -= am;
						pokedollar -= am * 60;
						lullaby += am;
						printf("%d Lullaby Powder berhasil dibeli!\n", am);
						return;
					}
				}
				else if (x == 2) {
					if (am <= *sharedpokeball && pokeball + am <= 99 && pokedollar >= am * 5) {
						*sharedpokeball -= am;
						pokedollar -= am * 5;
						pokeball += am;
						printf("%d Pokeball berhasil dibeli!\n", am);
						return;
					}
				}
				else if (x == 3) {
					if (am <= *sharedberry && berry + am <= 99 && pokedollar >= am * 15) {
						*sharedberry -= am;
						pokedollar -= am * 15;
						berry += am;
						printf("%d Berry berhasil dibeli!\n", am);
						return;
					}
				}
				else if (x == 4) return;
				printf("Gagal membeli.\n");
			}

		}
		else {
			if (capture != -1) printf("[CAPTURE]\nA Wild %s has appeared!\n1. Tangkap\n2. Item\n3. Keluar\n", namapokemon[capture]);
			else printf("[CAPTURE]\n1. Tangkap\n2. Item\n3. Keluar\n");
			pthread_create(&t_input,NULL,input,NULL);
			pthread_join(t_input,NULL);
			
			if(inputmenu==1){
				if (pokeball == 0) {
					printf("Tidak ada pokeball.\n");
					return;
				}
				if (capture == -1) {
					printf("Tidak ada pokemon.\n");
					return;
				}
				pokeball--;
				int par = (capture % 15) / 5;
				if (par == 0) par = 70;
				else if (par == 1) par = 50;
				else if (par == 2) par = 30;
				if (capture >= 15) par -= 20;
				if (lullaby_a) par += 20;
				if (rand() % 100 < par) {
					printf("Berhasil menangkap %s!\n", namapokemon[capture]);
					slot = -1;
					for (int x = 0; x < 7; x++){
						if (pokemon[x] == -1){
							slot = x;
							break;
						}
					}
					if (slot == -1){
						uangganti = (capture % 15) / 5;
						if (uangganti == 0) uangganti = 80;
						else if (uangganti == 1) uangganti = 100;
						else if (uangganti == 2) uangganti = 200;
						if (capture >= 15) uangganti += 5000;
						pokedollar += uangganti;
						printf("Slot pokemon penuh! Sebagai gantinya, kamu dapat Pokedollar sebanyak %d.\n", uangganti);
					}
					else{
						pthread_mutex_lock(&pokemonm);
						pokemon[slot] = capture;
						PokemonAP[slot] = 100;
						pthread_mutex_unlock(&pokemonm);
						pthread_mutex_lock(&pokemonslot);
						pokeslot = slot;
						pthread_create(&pokemon[slot], NULL, pokemonthread, NULL);
						pthread_cancel(capturethread);
						pthread_mutex_lock(&pokemonc);
						capture = -1;
						pthread_mutex_unlock(&pokemonc);
					}
				}
				else {
					printf("Gagal menangkap %s.\n", namapokemon[capture]);
				}
			}

			else if(inputmenu == 2){
				if(lullaby_a){
					printf("Lullaby Power masih aktif.\n");
				}
				if(lullaby <= 0){
					printf("Kamu tidak punya Lullaby Powder.\n");
				}
				else{
					lullaby--;
					lullaby_a = 1;
					pthread_create(&t_lullaby, NULL, lullabythread(), NULL);
				}
			}
			else if(inputmenu == 3){
				printf("Mengakhiri mode Capture.\n");
				mode = 0;
			}
		}
	}
	shmdt(sharedpoke);
	shmdt(sharedlullaby);
	shmdt(sharedpokeball);
	shmdt(sharedberry);
	shmctl(sharedidpoke, IPC_RMID, NULL);
	shmctl(sharedidberry, IPC_RMID, NULL);
	shmctl(sharedidpokeball, IPC_RMID, NULL);
	shmctl(sharedidlullaby, IPC_RMID, NULL);
	pthread_mutex_destroy(&pokemonslot);
	pthread_mutex_destroy(&pokemonm);
	pthread_mutex_destroy(&pokemonc);
	exit(EXIT_SUCCESS);
}
