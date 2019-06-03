#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
int glob = 0;

void * funz() {
    sleep(2);
    glob++;
    printf("\nRisultato: %d",glob);
}

int main()
{
    int n = 0;
    int i = 0;
    printf("\nInserisci intero: ");
    scanf("%d",&n);

    pthread_t tid[n];
    for(i=0;i<n;i++) {
        pthread_create(&tid[i],NULL,funz,NULL);
    }

    for(i=0;i<n;i++) {
        pthread_join(tid[i],NULL);
}

    return 0;
}
