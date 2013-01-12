#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

const int NUM_THREADS = 5;

void *wait (void *t) {
  long tid = (long) t;

  // POSIX function, cause the calling 
  // thread to be suspended for x seconds
  printf("sleeping in thread %ld\n", tid);
  sleep(1);
  printf("thread id = %ld, exit\n", tid);
  pthread_exit(NULL);
}

int main() {
  // threads is like a map:
  // key = [0,5], 
  // value = actual, non-portable, very long pthread_t handler
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  void *status;
  int rc;

  // Initialize attr and set thread joinable
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
  for (int i=0; i<NUM_THREADS; i++) {
    printf("main(): creating thread %d\n", i);
    rc = pthread_create(&threads[i], NULL, wait, (void *) i);
    if (rc) {
      printf("Error, thread = %d\n", rc);
      exit(-1);
    }
  }

  // free attr and wait for the other threads
  pthread_attr_destroy(&attr);
  // the thread of main() joins each thread it created, 
  // wait for their terminations before keep going
  for (int i=0; i<NUM_THREADS; i++) {
    printf("main(): joining thread %d\n", i);
    rc = pthread_join(threads[i], &status);
    if (rc) {
      printf("Error: Unable to join %d\n", rc);
      exit(-1);
    }
    printf("main(): thread %d is completed, exiting with status %d\n", i, (int) status);
  }

  printf("main(): main thread exit\n");
  pthread_exit(NULL);
}


