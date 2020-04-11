#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <pthread.h>
#include <ctype.h>

#define MAX 256

char filelama[MAX][MAX];
char directorylama[100];
char cwd[MAX];

const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) return "";
	return dot + 1;
}

void lower(char* s) {
	for (int i = 0; i < strlen(s); i++) {
		s[i] = tolower(s[i]);
	}
}

void* mindahfilepakefungsiini(void *filelama){
	char namafile[100];
	char *x = (char*)filelama;
	char *tmp = strrchr(x, '/');
	if(!tmp) strcpy(namafile,x);
	else strcpy(namafile,tmp);
	const char *ekstensifile = get_filename_ext(namafile);
	char filebaru[100];
	char ekstensifile2[100];	
	strcpy(ekstensifile2,ekstensifile);
	if (strcmp(ekstensifile,"")==0) strcpy(ekstensifile2,"UNKNOWN");
	lower(ekstensifile2);
	strcpy(filebaru,directorylama);
	strcat(filebaru,"/");
	strcat(filebaru,ekstensifile2);
	strcat(filebaru,"/");
	strcat(filebaru,namafile);
	mkdir(ekstensifile2,0755);
	rename(x,filebaru);
}

void* mindahfilepakefungsiyangsatunya(void *filelama){
	char namafile[100];
	char *x = (char*)filelama;
	char *tmp = strrchr(x, '/');
	if(!tmp) strcpy(namafile,x);
	else strcpy(namafile,tmp);
	const char *ekstensifile = get_filename_ext(namafile);
	char filebaru[100];
	char ekstensifile2[100];	
	strcpy(ekstensifile2,ekstensifile);
	if (strcmp(ekstensifile,"")==0) strcpy(ekstensifile2,"UNKNOWN");
	lower(ekstensifile2);
	strcpy(filebaru,directorylama);
	strcat(filebaru,"/");
	strcat(filebaru,ekstensifile2);
	strcat(filebaru,"/");
	strcat(filebaru,namafile);
	mkdir(ekstensifile2,0755);
	rename(x,filebaru);
}

void* mindahfilepakefungsiitu(void *filelama){
	char namafile[100];
	char *x = (char*)filelama;
	char *tmp = strrchr(x, '/');
	if(!tmp) strcpy(namafile,x);
	else strcpy(namafile,tmp);
	const char *ekstensifile = get_filename_ext(namafile);
	char filebaru[100];
	char ekstensifile2[100];	
	strcpy(ekstensifile2,ekstensifile);
	if (strcmp(ekstensifile,"")==0) strcpy(ekstensifile2,"UNKNOWN");
	lower(ekstensifile2);
	strcpy(filebaru,directorylama);
	strcat(filebaru,"/");
	strcat(filebaru,ekstensifile2);
	strcat(filebaru,namafile);
	mkdir(ekstensifile2,0755);
	rename(x,filebaru);
}

int main(int argc, char **argv){
	getcwd(directorylama, sizeof(directorylama));


	if (strcmp(argv[1],"-f")==0){
		if (argc<3){
			printf("Jumlah argumen kurang!\n");
			return 0;
		}
		pthread_t tid[argc-2];
		for(int t=2;t<argc;t++) pthread_create(&(tid[t-2]),NULL,mindahfilepakefungsiini,argv[t]);
			for(int x=0; x<argc-2; x++) pthread_join(tid[x],NULL);
		}

	else if (strcmp(argv[1],"*")==0){
		if (argc!=2){
			printf("Jumlah argumen kurang!\n");
			return 0;
		}
		struct dirent *de;
		DIR *dir = opendir("/home/kevinc45/koleksi/");

		if(!dir){
			printf("opendir() failed! Does it exist?\n");
			return 1;
		}

		unsigned long count=0;

		while(de = readdir(dir)){
			if (de->d_type==4) continue;
			sprintf(filelama[count], "%s", de->d_name);
			count++;
		}

		closedir(dir);
		pthread_t tid[count];
		for(int x=0; x<count; x++) pthread_create(&(tid[x]),NULL,mindahfilepakefungsiyangsatunya,filelama[x]);
			for(int x=0; x<count; x++) pthread_join(tid[x],NULL);

				return 0;
		}

		else if (strcmp(argv[1], "-d") == 0){
			if (argc<3){
				printf("Jumlah argumen kurang!\n");
				return 0;
			}
			struct dirent *de;
			DIR *dir = opendir(argv[2]);
			if(!dir){
				printf("opendir() failed! Does it exist?\n");
				return 1;
			}


			unsigned long count=0;

			while(de = readdir(dir)){
				if (de->d_type==4) continue;
				sprintf(filelama[count], "%s/%s", argv[2],de->d_name);
				count++;
			}

			closedir(dir);
			pthread_t tid[count];
			for(int x=0; x<count; x++) pthread_create(&(tid[x]),NULL,mindahfilepakefungsiitu,filelama[x]);
				for(int x=0; x<count; x++) pthread_join(tid[x],NULL);

					return 0;
			}
			else{printf("Inputan salah!\n");}

		}
