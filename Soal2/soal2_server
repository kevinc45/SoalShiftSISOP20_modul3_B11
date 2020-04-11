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
