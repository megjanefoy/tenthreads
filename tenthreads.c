#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Title: Lab 7
 * Semester: COP4338 - Spring 2021
 * Author Megan Jane Thompson
 *
 * This program creates 10 threads. Each thread loops 6 times
 * and adds its id value to shared_x each loop.
 */


/*create thread argument struct for thr_func()*/
typedef struct _thread_data_t{
  int tid;
}thread_data_t;


/*shared data between threads*/
int shared_x;
pthread_mutex_t lock_x;


/*****function that takes in a thread*****/
void *thr_func(void *arg){
  thread_data_t *tdata = (thread_data_t *)arg;
  int i;

  pthread_mutex_lock(&lock_x);							//locks x
  for(i = 0; i < 6; ++i){								//loops 6 times
	  shared_x += tdata->tid;							//adds id number to shared_x each loop
  }
  printf("Thread %d has finished.\n", tdata->tid);
  pthread_mutex_unlock(&lock_x);						//unlocks x
}


/*****main method*****/
int main(int argc, char **argv) {
  pthread_t thr[10];
  int i, rc;
  thread_data_t thr_data[10];							//create a thread_data_t argument array

  shared_x = 0;											//initialize shared data
  pthread_mutex_init(&lock_x, NULL);					//initialize pthread mutex protecting shared_x

  /*create 10 threads*/
  for (i = 0; i < 10; ++i) {
    thr_data[i].tid = i;
    if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }

  /*block until all threads complete*/
  for (i = 0; i < 10; ++i) {
    pthread_join(thr[i], NULL);
  }

  printf("The final value is: %d\n", shared_x);			//prints final value of shared_x
  pthread_exit(NULL);

  return EXIT_SUCCESS;
}
