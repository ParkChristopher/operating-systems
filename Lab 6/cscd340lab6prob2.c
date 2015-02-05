//Chris Park

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t cnt_mutex, db_mutex, the_mutex;
pthread_cond_t request;
int reader_count = 0;
int writer_count = 0;

void * reader(void *ptr);
void * writer(void *ptr);


void * reader(void *ptr)
{
	while(1)
	{	
		
		pthread_mutex_lock(&the_mutex);
		
		pthread_mutex_lock(&cnt_mutex);
		reader_count = reader_count + 1;
		
		
		if(reader_count == 1)
			pthread_mutex_lock(&db_mutex);
		
		pthread_mutex_unlock(&cnt_mutex);
		
		printf("Reading from database\n");
		
		pthread_mutex_lock(&cnt_mutex);
		reader_count = reader_count - 1;
		pthread_mutex_unlock(&cnt_mutex);
		
		if(writer_count > 0 || reader_count == 0)
		{
			pthread_mutex_unlock(&db_mutex);
			pthread_cond_wait(&request, &the_mutex);
		}
		
		pthread_mutex_unlock(&the_mutex);
	}
}

void * writer(void *ptr)
{
	while(1)
	{
		pthread_mutex_lock(&the_mutex);
		
		pthread_mutex_lock(&cnt_mutex);
		writer_count = writer_count + 1;
		pthread_mutex_unlock(&cnt_mutex);
		
		pthread_mutex_lock(&db_mutex);
		
		printf("Writing to database\n");
		
		pthread_mutex_lock(&cnt_mutex);
		writer_count =  writer_count - 1;
		pthread_mutex_unlock(&cnt_mutex);
	
		pthread_cond_broadcast(&request);		
		//pthread_cond_signal(&request);
		
		pthread_mutex_unlock(&db_mutex);
		
		pthread_mutex_unlock(&the_mutex);
	}
}

int main()
{
	pthread_t read1, read2, write;
	
	pthread_mutex_init(&cnt_mutex, 0);
	pthread_mutex_init(&db_mutex, 0);
	pthread_mutex_init(&the_mutex, 0);
	
	pthread_cond_init(&request, 0);
	
	pthread_create(&read1, 0, reader, NULL);
	pthread_create(&read2, 0, reader, NULL);
	pthread_create(&write, 0, writer, NULL);
	
	pthread_join(read1, NULL);
	pthread_join(read2, NULL);
	pthread_join(write, NULL);
	
	return 0;
}
