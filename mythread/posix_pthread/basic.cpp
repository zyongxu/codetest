/*       * POSIX multithreading example with Pthread library *
 *
 * Multithreading is a specialized form of multitasking and a multitasking is the 
 * feature that allows your computer to run two or more programs concurrently. 
 * In general, there are two types of multitasking: process-based and 
 * thread-based.
 *
 * Process-based multitasking handles the concurrent execution of programs.
 * Thread-based multitasking deals with the concurrent execution of pieces of
 * the same program.
 *
 * A multithreaded program contains two or more parts that can run
 * concurrently. Each part of such a program is called a thread, and each
 * thread defines a separate path of execution.
 */
#include <cstdio>
#include <cstdlib>
#include <pthread.h>

const int NUM_THREADS = 5;

void *PrintThread (void *thread_id) {
  long tid;
  tid = reinterpret_cast<long> (thread_id);
  printf("This is Thread with ID = %li\n", tid);
  /* pthread_exit(void *status) is used to explicitly exit a thread. 
   *   [status] is the return value of the thread
   *
   * Typically, the pthread_exit() routine is called after a thread has
   * completed its work and is no longer required to exist.
   *
   * If main() finishes before the threads it has created, and exits with
   * pthread_exit(), the other threads will continue to execute. Otherwise,
   * they will be automatically terminated when main() finishes.
   */
  pthread_exit(NULL);
}



int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int rc;
  
  for (int i=0; i<NUM_THREADS; i++) {
    printf("main(): creating thread, %d\n", i);

    /* pthread_create(pthread_t *thread, pthread_attr_t *attr,
     *                void *(*thread_func) (void *), void *func_argu) 
     * 
     *   [thread] is a handler for the new thread
     *   [attr] is config of the new thread, set to NULL to use default
     *   [thread_func] is the function the new thread is executing, the thread
     *   will terminate when this function terminates, or it is explicitly
     *   killed by calling pthread_exit(). 
     *   [func_argu] is a void* pointer which is passed as the only argument to
     *   the thread_func
     *
     * pthread_create() creates a new thread and makes it executable. This
     * routine can be called any number of times from anywhere within your code.
     * Once created, threads are peers, and may create other threads. There is
     * no implied hierarchy or dependency between threads.
     *
     * returns 0 on success
     */
    
    rc = pthread_create(&threads[i], NULL, PrintThread, (void*) i);
    if (rc) {
      printf("Error: unable to create thread %d\n", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);
}


  


