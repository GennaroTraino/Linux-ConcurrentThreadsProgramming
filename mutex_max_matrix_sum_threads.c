/* Si realizzi un programma che crei una matrice di interi di dimensione n x n con n dispari fornito da riga di comando,
che provveda a sommare in modo concorrente con quattro thread, gli elementi delle due diagonali,
della riga centrale e della colonna centrale della matrice e ne determini il massimo da assegnare ad un'opportuna variabile.*/

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/file.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<pthread.h>

void * diag1(void *);
void * diag2(void *);
void * colcentr(void *);
void * rigcentr(void *);

struct 
{
    pthread_mutex_t mutex;
    int **matrix;
    int n;
    int max;
}s;


int main(int argc, char const *argv[])
{
    int i,j;
    pthread_t tid[4];
    s.max = 0;
    printf("\nInserisci n: ");
    scanf("%d",&s.n);

    s.matrix = malloc(s.n * sizeof(int*));
    for(i=0;i<s.n;i++) 
        s.matrix[i] = malloc(s.n*sizeof(int));


	for(i=0; i<s.n; i++){
		for(j=0; j<s.n; j++)
        {
			s.matrix[i][j] = rand()%11;
			printf("%d  ", s.matrix[i][j]);
		}
		printf("\n");
	}

    pthread_create(&tid[0],NULL,diag1,NULL);
    pthread_create(&tid[1],NULL,diag2,NULL);
    pthread_create(&tid[2],NULL,colcentr,NULL);
    pthread_create(&tid[3],NULL,rigcentr,NULL);

    for (i = 0; i < 4; i++)
    {
        pthread_join(tid[i],NULL);
    }
    
    printf("\n The max value is: %d",s.max);
    return 0;
}

void* diag1(void * arg)
{
    int i,sum=0;
    for(i=0;i<s.n;i++)
        sum += s.matrix[i][i];
    printf("ciao sono il 1 somma: %d \n",sum);
    pthread_mutex_lock(&s.mutex);
        if(s.max < sum)
            s.max = sum;
    pthread_mutex_unlock(&s.mutex);
}

void* diag2(void * arg)
{
    int i,sum=0;
    for(i=0;i<s.n;i++)
        sum += s.matrix[((s.n) - 1) - i][i];
    printf("ciao sono il 2 somma: %d \n",sum);
    pthread_mutex_lock(&s.mutex);
        if(s.max < sum)
            s.max = sum;
    pthread_mutex_unlock(&s.mutex);
}

void* rigcentr(void *arg)
{
    int i,j,sum=0;
    i=(s.n)/2;
    for (j=0;j<s.n;j++)
        sum += s.matrix[i][j];
    printf("ciao sono il 3 somma: %d \n",sum);
    pthread_mutex_lock(&s.mutex);
        if(s.max < sum)
            s.max = sum;
    pthread_mutex_unlock(&s.mutex);
}

void* colcentr(void *arg)
{
    int i,j,sum=0;
    j=(s.n)/2;
    for (i=0;i<s.n;i++)
        sum += s.matrix[i][j];
    printf("ciao sono il 4 somma: %d \n",sum);
    pthread_mutex_lock(&s.mutex);
        if(s.max < sum)
            s.max = sum;
    pthread_mutex_unlock(&s.mutex);
}
