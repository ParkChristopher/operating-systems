//Chris Park

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (i % N)
#define RIGHT ((i + 1) % N)


void takefork(int i);
void putfork(int i);
void test(int i);


int state[N];
pthread_mutex_t the_mutex;
pthread_mutex_t thefork[N];

void * phil(void *ptr)
{
	int i = *((int*)ptr);
	
	while(1)
	{
		printf("Philosopher %d is Thinking...\n", i);
		takefork(LEFT);
		printf("Philosopher %d is Eating.\n", i);
		putfork(LEFT);
	}
}

void takefork(int i)
{	
	//printf("take: Philosopher %d is locking mutex\n", i);
	pthread_mutex_lock(&the_mutex);
	
	state[i] = HUNGRY;
	printf("Philosopher %d is Hungry!\n", i);
	test(i);
	
	//printf("take: Philosopher %d is unclocking mutex\n", i);
	pthread_mutex_unlock(&the_mutex);

	//printf("take: Philosopher %d is waiting\n", i);
	pthread_mutex_lock(&thefork[i]);
}

void putfork(int i)
{
	//printf("put: Philosopher %d is locking mutex\n", i);
	pthread_mutex_lock(&the_mutex);
	
	state[i] = THINKING;
	
	test(LEFT);
	test(RIGHT);
	
	//printf("Philosopher %d is unlocking mutex\n", i);
	pthread_mutex_unlock(&the_mutex);
}

void test(int i)
{
	if (state[i] == HUNGRY && state[LEFT] != EATING &&
		state[RIGHT] != EATING)
	{
		state[i] = EATING;
		//printf("put: Philosopher %d is signaling wakeup\n", i);
		pthread_mutex_unlock(&thefork[i]);
	}
}

int main()
{
	int i;
	int id[N];
	pthread_t philosopher[N];
	
	pthread_mutex_init(&the_mutex, 0);
	
	for(i = 0; i < N; i++)
	{
		id[i] = i;
		state[i] = THINKING;
		pthread_mutex_init(&thefork[i], 0);
	}
	
	for(i = 0; i < N; i ++)
		pthread_create(&philosopher[i], 0, phil, (void *) &id[i]);
	
	for(i = 0; i < N; i ++)
		pthread_join(philosopher[i], NULL);
		
	pthread_mutex_destroy(&the_mutex);
	for(i = 0; i < N; i++)
		pthread_mutex_destroy(&thefork[i]);

	return 0;
}

