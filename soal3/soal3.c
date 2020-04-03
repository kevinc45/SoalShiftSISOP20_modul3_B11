#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

char directorymenu[100];
char directorylama[100];
char filebaru[100];

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int main(int argc, char **argv){


if (strcmp(argv[1],"-f")==0){

}

else if (strcmp(argv[1],"*")==0){
	char direc[100];	
	struct dirent *de;
	DIR *dir = opendir("/home/kevinc45/koleksi/");
	
	if(!dir){
        printf("opendir() failed! Does it exist?\n");
        return 1;
    	}

	unsigned long count=0;
        
	while(de = readdir(dir)){
	if (de->d_type==4) continue;
	
	strcpy(directorylama,"/home/kevinc45/koleksi/");
	strcat(directorylama,de->d_name);

	strcpy(directorymenu,"/home/kevinc45/");
	strcat(directorymenu,get_filename_ext(de->d_name));
	
	strcpy(filebaru,directorymenu);
	strcat(filebaru,de->d_name);
	

	DIR *dir2 = opendir(directorymenu);
	mkdir(get_filename_ext(de->d_name),0755);		
	rename(directorylama,filebaru);
   	closedir(dir2);	
	count++;
	}

    	closedir(dir);
    return 0;
}
else if (strcmp(argv[1], "-d") == 0){}
else{printf("Inputan salah!\n");}

}
