#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

int semid;

typedef struct __counter_t {
	int value;
} counter_t;

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

unsigned int loop_cnt;
counter_t counter;

void sema_lock(){
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = -1;
	s.sem_flg = 0;
	semop(semid,&s,1);
}

void sema_unlock(){
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = 1;
	s.sem_flg = 0;
	semop(semid,&s,1);
}

void init(counter_t *c) {
	c->value = 0;
}

void increment(counter_t *c) {
	sema_lock();
	c->value++;
	sema_unlock();
}

void decrement(counter_t *c) {
	sema_lock();
	c->value--;
	sema_unlock();
}

int get(counter_t *c) {
	sema_lock();
	int rc = c->value;
	sema_unlock();
	return rc;
}

void *mythread(void *arg)
{
	char *letter = arg;
	int i;

	printf("%s: begin\n", letter);
	for (i = 0; i < loop_cnt; i++) {
	increment(&counter);
	}
	printf("%s: done\n", letter);
	return NULL;
}

                                                                             
int main(int argc, char *argv[])
{                    
	// using clock function to measure execution time
	clock_t start, end;
	float time;
	start = clock();

	loop_cnt = atoi(argv[1]);
	union semun su;

	// using setget to get semid
	// using IPC_PRIVATE to create key
	if((semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0660)) == -1){
		printf("semet() fail \n");
		exit(0);
        }

        su.val=1;
        if(semctl(semid,0,SETVAL, su) == -1){
                printf("semctl fail\n");
                exit(0);
        }


	init(&counter);

	pthread_t p1, p2;
	printf("main: begin [counter = %d]\n", get(&counter));
	pthread_create(&p1, NULL, mythread, "A"); 
	pthread_create(&p2, NULL, mythread, "B");
	// join waits for the threads to finish
	pthread_join(p1, NULL); 
	pthread_join(p2, NULL); 
	printf("main: done [counter: %d] [should be: %d]\n", get(&counter), loop_cnt * 2);

	// destroy the semid using semctl
	if(semctl(semid, 0, IPC_RMID, su) == -1){
		 printf("semctl() fail\n");
		 exit(0);
	}

	end = clock();
	time = (float)(end - start)/CLOCKS_PER_SEC;
	printf("Execution time for semaphore : %.3f \n", time);

	return 0;
}
