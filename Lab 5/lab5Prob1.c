//Chris Park

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *  print_hello(void * tid)
{
        printf("hello from thread %d\n", *((int*)tid) + 1);
        pthread_exit(NULL);
}

void * print_goodbye(void * tid)
{
	printf("goodbye from thread %d\n", *((int*)tid) + 1);
	pthread_exit(NULL);
}

int main()
{
        pthread_t tid[6];
        int status, x;
        int array[6];
        
        for(x = 0; x < 6; x++)
        	array[x] = x;
        
        for(x  = 0; x < 6; x++)
        {	
        	if(x % 2 != 0)
            	status = pthread_create(&tid[x], NULL,
                		print_goodbye, (void*) &array[x]);
            else    	
            	status = pthread_create(&tid[x], NULL, 
               			print_hello, (void*) &array[x]);
                
           if(status  != 0)
           {
           	   printf("failed\n");
               exit(-1);
           }
        }

        for(x = 0; x < 6; x++)
        	pthread_join(tid[x], NULL);

        return 0;
}// end 


