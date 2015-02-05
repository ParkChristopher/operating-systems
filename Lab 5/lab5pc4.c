//Chris Park

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp, condp2;
int buffer[MAX];
int i = 0;

void * producer(void *ptr)
{	
	while(1)
	{
		printf("producer locking critical region\n");
		pthread_mutex_lock(&the_mutex);
		
		while( i == MAX)
		{
			printf("buffer not empty, producer sleeping\n");
			pthread_cond_wait(&condp, &the_mutex);
		}
		
		printf("producer producing element %d\n", i);
		buffer[i] = i;
		i++;
		
		printf("producer signaling consumer to wake up\n");
		pthread_cond_signal(&condc);
		
		printf("producer releasing lock on critical region\n");
		pthread_mutex_unlock(&the_mutex);
	}
}

void * producer2(void *ptr)
{	
	while(1)
	{
		printf("producer2 locking critical region\n");
		pthread_mutex_lock(&the_mutex);
		
		while( i == MAX)
		{
			printf("buffer not empty, producer2 sleeping\n");
			pthread_cond_wait(&condp2, &the_mutex);
		}
		
		printf("producer2 producing element %d\n", i);
		buffer[i] = i;
		i++;
		
		printf("producer2 signaling consumer to wake up\n");
		pthread_cond_signal(&condc);
		
		printf("producer2 releasing lock on critical region\n");
		pthread_mutex_unlock(&the_mutex);
	}
}


void * consumer(void *ptr)
{	
	while(1)
	{
		printf("consumer locking critical region\n");
		pthread_mutex_lock(&the_mutex);
		
		while(i == -1)
		{
			i = 0;
			printf("buffer is empty, consumer sleeping\n");
			pthread_cond_wait(&condc, &the_mutex);
		}
		
		printf("consumer consuming element %d\n", i);
		buffer[i] = 0;
		i--;
		
		printf("consumer signaling producer(s) to wake up\n");
		pthread_cond_signal(&condp);
		pthread_cond_signal(&condp2);
		
		printf("consumer releasing lock on critical region\n");
		pthread_mutex_unlock(&the_mutex);
	}
}

int main()
{
	
	pthread_t pro, pro2, con;
	pthread_mutex_init(&the_mutex, 0);
	
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	
	pthread_create(&con, 0, consumer, NULL);
	pthread_create(&pro, 0, producer, NULL);
	pthread_create(&pro2, 0, producer2, NULL);
	
	pthread_join(pro, NULL);
	pthread_join(pro2, NULL);
	pthread_join(con, NULL);
	
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_cond_destroy(&condp2);
	pthread_mutex_destroy(&the_mutex);
	
	return 0;
}
