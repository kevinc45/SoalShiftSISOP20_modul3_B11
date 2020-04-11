    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <dirent.h>
    #include <signal.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/types.h>
    #include <sys/wait.h>

int* sharedpoke, sharedlullaby, sharedpokeball, sharedberry;
pthread_t t_restock,t_random;

void* restock(){
    for(;;){
        *sharedlullaby += 10;
        if(*sharedlullaby>200) *sharedlullaby=200;
        *sharedpokeball += 10;
        if(*sharedpokeball>200) *sharedpokeball=200;
        *sharedberry += 10;
        if(*sharedberry>200) *sharedberry=200;
        sleep(10);
    }
}

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

int main(){
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
    *sharedpoke=100;
    *sharedlullaby=100;
    *sharedpokeball=100;
    *sharedberry = 100;
    pthread_create(&t_restock,NULL,restock,NULL);
    pthread_create(&t_restock,NULL,randompokemon,NULL);
    
    printf("Shutdown Game? [Y/N]\n");
    printf("Input?")
    char x;
    scanf("%c",&x);
    if (x == 'Y'){
      DIR* dir = opendir("/proc");
      struct dirent* ent;
      char* endptr;
      while ((ent = readdir(dir)) != NULL) {
         long lpid = strtol(ent->d_name, &endptr, 10);
         if (*endptr != '\0') continue;
         char buf[512];
         snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
         FILE* fp = fopen(buf, "r");
         if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
               char* first = strtok(buf, " ");
               if (strcmp(first, "./soal2_traizone") == 0) {
                  pid_t child = fork();
                  if (child == 0) {
                     char cmd[500];
                     sprintf(cmd, "kill -INT %ld", lpid);
                     execl("/bin/sh", "sh", "-c", cmd, NULL);
                 }
             }
         }
         fclose(fp);
     }
 }
 closedir(dir);
 int stat;
 while(wait(&stat) > 0);
 shmdt(sharedpoke);
 shmctl(sharedidpoke,IPC_RMID,NULL);
 shmdt(sharedpokeball);
 shmctl(sharedidpokeball,IPC_RMID,NULL);
 shmdt(sharedberry);
 shmctl(sharedidberry,IPC_RMID,NULL);
 shmdt(sharedlullaby);
 shmctl(sharedidlullaby,IPC_RMID,NULL);
 exit(EXIT_SUCCESS);
}
}
