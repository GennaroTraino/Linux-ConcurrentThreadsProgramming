#define clear() printf("\033[H\033[J")
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/file.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

void * produce(void *);
void * consume(void *);

int buf[10];

struct
{
    pthread_mutex_t mutex;
    sem_t pieno,vuoto;
    int posizione;
}s;


int main(int argc, char const *argv[])
{
    int i,p,c,sec;
    printf("\nInserisci numero produttori: ");
    scanf("%d",&p);
    printf("\nInserisci numero consumatori: ");
    scanf("%d",&c);
    printf("\nPer quanti secondi vuoi che funzioni il programma?: ");
    scanf("%d",&sec);
    pthread_t tid[p+c];
    s.posizione = 0;
    for (i = 0; i < 10; i++)
    {
        buf[i] = 0;
        printf(" %d",buf[i]);
    }
    sleep(5);

    

    sem_init(&s.pieno,0,0);
    sem_init(&s.vuoto,0,10);
    
    for (i=0; i < p; i++)
        pthread_create(&tid[i],NULL,consume,NULL);
    
    for (i=p; i<p+c; i++)
        pthread_create(&tid[i],NULL,produce,NULL);    
    
    sleep(sec);
    exit(0);
    
}

void* produce(void *arg)
{
    int elem,i;
    while(1)
    {
        sem_wait(&s.vuoto);
        elem = 10 + rand() %10;
        pthread_mutex_lock(&s.mutex);
            buf[s.posizione] = elem;
            clear();
            printf("Posizione | Elemento");
            for (i=0; i<10; i++){
                printf("     %d        %d \n",i,buf[i]);
            }
            s.posizione += 1;
        pthread_mutex_unlock(&s.mutex);
        sem_post(&s.pieno);
        sleep(1);
    }
}

void* consume(void *arg)
{
    int mio,i;
    while(1)
    {
        sem_wait(&s.pieno);
        pthread_mutex_lock(&s.mutex);
            s.posizione -= 1;
            mio = buf[s.posizione];
            buf[s.posizione] = 0;
            clear();
            printf("Posizione | Elemento");
            for (i=0; i<10; i++){
                printf("     %d        %d \n",i,buf[i]);
            }
        pthread_mutex_unlock(&s.mutex);
        sem_post(&s.vuoto);
        sleep(1);
    }
}
