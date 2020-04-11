#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<termios.h>
#include<stdbool.h>
#define PORT 8080

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

int main(int argc, char const *argv[])
{
    struct sockaddr_in alamat;
    int sock = 0, valread;
    struct sockaddr_in alamat_serv;
    int addrlen = sizeof(alamat);
    char buff[1024] = {0};
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error\n");
        return -1;
    }

    memset(&alamat_serv, '0', sizeof(alamat_serv));
    alamat_serv.sin_family = AF_INET;
    alamat_serv.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &alamat_serv.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }

    if(connect(sock, (struct sockaddr *) &alamat_serv, sizeof(alamat_serv)) < 0)
    {
        printf("\nConnection Failed\n");
        return -1;
    }
    char arr1[1024], arr2[1024], username[1024], password[1024], temp[1024];
    screen1:
    
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
    return 0;
}
