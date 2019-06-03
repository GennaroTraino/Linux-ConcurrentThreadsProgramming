#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_t ntid;

void print(const char *s){
    printf("%s",s);
    pthread_t tid = pthread_self(); /* tid conterrà il tid */
    printf(" %u",(unsigned int)tid); /* Per print di tid il cast unsigned */
}

void * fun_t(void *arg) {
    print("sono il thread! Mio Tid: ");
    return ((void *)0);
}

int main() {
    if(pthread_create(&ntid,NULL,fun_t,NULL) != 0)
	printf("NON HO CREATO IL THREAD");
    else
	printf("HO CREATO IL THREAD\n");
    sleep(1); /* necessità di non terminare per far eseguire il thread */
    return 0;
}
