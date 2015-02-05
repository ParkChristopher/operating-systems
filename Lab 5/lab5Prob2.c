//Chris Park

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int _num = 100;
int* _array;
int _element = 0;

void * fill_array(void * tid)
{
	printf("thread %d is filling array element %d with %d\n", *((int*)tid),
		_element, _num);
	
	_array[_element] = _num;
	_num++;
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr, "arguments required: 2\n");
		exit(-1);
	}
	
	int num_iters = atoi(argv[1]);
	int num_threads = atoi(argv[2]);
	
	pthread_t tid[num_threads];
	int thread_count[num_threads];
	int status, i, j;
	
	_array = malloc(num_iters * sizeof(int));
	
	for(i = 0; i < num_threads; i++)
		thread_count[i] = i;
	
	for(i = 0, j = 0; i < num_iters; i++, j++)
	{
		_element = i;
		
		if(j == num_threads)
			j = 0;
		
		status = pthread_create(&tid[j], NULL, fill_array,
			(void*) &thread_count[j]);
	
		if(status != 0)
		{
			fprintf(stderr, "thread failure\n");
			exit(-1);
		}
		
		pthread_join(tid[j], NULL);
	}
	
	free(_array);
	return 0;
}

