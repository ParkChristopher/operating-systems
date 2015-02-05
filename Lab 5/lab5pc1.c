//Chris Park

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void * producer(void *ptr)
{
	int i;
	
	for(i = 0; i < MAX; i++)
	{
		printf("producer locking critical region\n");
		pthread_mutex_lock(&the_mutex);
		
		printf("producer producing %d\n", i);
		while(buffer != 0)
		{
			printf("buffer not empty, producer sleeping\n");
			pthread_cond_wait(&condp, &the_mutex);
		}
		
		buffer = i;
		
		printf("producer signaling consumer to wake up\n");
		pthread_cond_signal(&condc);
		
		printf("producer releasing lock on critical region\n");
		pthread_mutex_unlock(&the_mutex);
	}
}

void * consumer(void *ptr)
{
	int i;
	
	for(i = 1; i < MAX; i++)
	{
		printf("consumer locking critical region\n");
		pthread_mutex_lock(&the_mutex);
		
		printf("consumer consuming %d\n", i);
		while(buffer == 0)
		{
			printf("buffer is empty, consumer sleeping\n");
			pthread_cond_wait(&condc, &the_mutex);
		}
		
		buffer = 0;
		
		printf("consumer signaling producer to wake up\n");
		pthread_cond_signal(&condp);
		
		printf("consumer releasing lock on critical region\n");
		pthread_mutex_unlock(&the_mutex);
	}
}

int main()
{
	
	pthread_t pro, con;
	pthread_mutex_init(&the_mutex, 0);
	
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	
	pthread_create(&con, 0, consumer, NULL);
	pthread_create(&pro, 0, producer, NULL);
	pthread_join(pro, NULL);
	pthread_join(con, NULL);
	
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&the_mutex);
	
	return 0;
}
