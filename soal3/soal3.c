#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h> 
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <ctype.h>


int main(int argc, char **argv){


if (strcmp(argv[1],"-f")==0){

}

else if (strcmp(argv[1],"*")==0){
	char direc[100];	
	struct dirent *de;
	DIR *dir = opendir("/home/kevinc45/koleksi");
	
	if(!dir){
        printf("opendir() failed! Does it exist?\n");
        return 1;
    	}

	unsigned long count=0;
        
	while(de = readdir(dir)){
	if (strcmp(de->d_name,".") && strcmp(de->d_name,"..")){
	strcpy(direc,"/home/kevinc45/");
	strcat(direc,de->d_name);
	if(de->d_type == 8){
	
	}
	++count;
}
    	closedir(dir);
    	
            }
    return 0;

}
else if (strcmp(argv[1], "-d") == 0){}
else{printf("Inputan salah!\n");}

}
