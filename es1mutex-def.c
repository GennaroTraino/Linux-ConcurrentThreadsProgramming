/* Si realizzi un programma in C e Posix sotto Linux che, utilizzando la libreria Pthread
    • lancia n thread per cercare un elemento in una matrice nxn di caratteri
    • Ognuno dei thread cerca l'elemento in una delle righe della matrice
    • Non appena un thread ha trovato l'elemento cercato, rende note agli altri thread
      le coordinate dell'elemento e tutti i thread terminano (sono cancellati) */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

char *mat;
char key;
int n;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *cerca(void *arg)
{
    int indice = *(int *) arg;
    int v = 0;
    /* Locking Mutex */
    pthread_mutex_lock(&mutex);
    for(v=0; v<n; v++) {
        if(*(mat+indice*n+v) == key) {
                printf("\nSono %d Trovato in posizione %d %d\n",indice,indice,v);
                exit(0);
        }
    }
    pthread_mutex_unlock(&mutex);
    /* Unlocking Mutex */
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    int i,j;
    printf("\nInserisci la dimensione della matrice: ");
    scanf("%d",&n);
    /* Genera Matrice di char rand*/
    mat = malloc(n*n*sizeof(char));
    for(i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            *(mat+i*n+j) = 65 + rand() %25;
            printf("%c ",*(mat+i*n+j));
        }
        printf("\n");
    }

    /* Prendi in input la chiave */
    printf("\n Inserisci la chiave: ");
    scanf(" %c",&key);
    
    /* Creazione e lancio dei Thread */
    pthread_t tid[n];
    int index[n];
    for (i=0; i<n; i++)
    {
        index[i] = i;
        pthread_create(&tid[i],NULL,cerca,(void *)&index[i]);
    }
    
    /* Join dei Thread */
    for(i=0; i<n; i++)
        pthread_join(tid[i],NULL);
    return 0;
}
