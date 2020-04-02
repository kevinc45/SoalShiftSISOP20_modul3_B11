#include <stdio.h>
#include <string.h>

int caripokemon(int modetype){

}

int pokedex(int jumlahpokemon){
char namapokemon[25];


if (jumlahpokemon == 0){
return 0;
}


for(int i=0;i<jumlahpokemon;i++){
indexpoke=pokedex[i];

if (pokedex[i]==0) strcpy(namapokemon,"Bulbasaur");
else if (pokedex[i]==1) strcpy(namapokemon,"Charmander");
else if (pokedex[i]==2) strcpy(namapokemon,"Squirtle");
else if (pokedex[i]==3) strcpy(namapokemon,"Rattata");
else if (pokedex[i]==4) strcpy(namapokemon,"Caterpie");
else if (pokedex[i]==5) strcpy(namapokemon,"Pikachu");
else if (pokedex[i]==6) strcpy(namapokemon,"Eevee");
else if (pokedex[i]==7) strcpy(namapokemon,"Jigglypuff");
else if (pokedex[i]==8) strcpy(namapokemon,"Snorlax");
else if (pokedex[i]==9) strcpy(namapokemon,"Dragonite");
else if (pokedex[i]==10) strcpy(namapokemon,"Mew");
else if (pokedex[i]==11) strcpy(namapokemon,"Mewtwo");
else if (pokedex[i]==12) strcpy(namapokemon,"Moltres");
else if (pokedex[i]==13) strcpy(namapokemon,"Zapdos");
else if (pokedex[i]==14) strcpy(namapokemon,"Articuno");
else if (pokedex[i]==15) strcpy(namapokemon,"Shiny Bulbasaur");
else if (pokedex[i]==16) strcpy(namapokemon,"Shiny Charmander");
else if (pokedex[i]==17) strcpy(namapokemon,"Shiny Squirtle");
else if (pokedex[i]==18) strcpy(namapokemon,"Shiny Rattata");
else if (pokedex[i]==19) strcpy(namapokemon,"Shiny Caterpie");
else if (pokedex[i]==20) strcpy(namapokemon,"Shiny Pikachu");
else if (pokedex[i]==21) strcpy(namapokemon,"Shiny Eevee");
else if (pokedex[i]==22) strcpy(namapokemon,"Shiny Jigglypuff");
else if (pokedex[i]==23) strcpy(namapokemon,"Shiny Snorlax");
else if (pokedex[i]==24) strcpy(namapokemon,"Shiny Dragonite");
else if (pokedex[i]==25) strcpy(namapokemon,"Shiny Mew");
else if (pokedex[i]==26) strcpy(namapokemon,"Shiny Mewtwo");
else if (pokedex[i]==27) strcpy(namapokemon,"Shiny Moltres");
else if (pokedex[i]==28) strcpy(namapokemon,"Shiny Zapdos");
else if (pokedex[i]==29) strcpy(namapokemon,"Shiny Articuno");

printf("%s\n",namapokemon);

}

}


int shop(){}





int main(){

int menu;
int modetypea=1;
int modetypeb=0;
int tampilanpokedex;
int jumlahpokemon;
int pokedex[10];

printf("Selamat datang di Poke*ZONE.\n");

while(1){

if(modetypea)
printf("Masukkan perintah yang ingin dijalankan:\n1. Cari Pokemon\n2. Pokedex\n3. Shop\n");
else printf("Masukkan perintah yang ingin dijalankan:\n1. Berhenti Mencari\n2. Pokedex\n3. Shop\n");

scanf("%d",&menu);

if (menu==1 && modetypea==0){

}

else if (menu==1 && modetypea==1){

}

else if (menu==2){

printf("Menu Pokedex:\n1. Tampilkan Pokemon yang dimiliki\n2. Jual Pokemon\n3. Berikan Berry ke Pokemon\n");
scanf("%d",&tampilanpokedex);
if (tampilanpokedex==1){
if (pokedex(jumlahpokemon)==0) printf("Kamu belum punya Pokemon!\n");
}}

else {

}
}
}
