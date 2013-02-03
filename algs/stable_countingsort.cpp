#include <cstdio>
#include <cstdlib>

void StableCountingSort(int *A, int *B, int length, int k) {
  int C[k];
  for(int i=0; i<=k; i++)
    C[i]=0;

  for(int i=0; i<length; i++)
    C[A[i]]++;
    
  for(int i=1; i<=k; i++)
    C[i] += C[i-1];

  /********************************
   * To make sure this is stable, *
   * starts from n downto 1       *
   ********************************/
  for(int i=length-1; i>=0; i--) {
    /**************************************
     * ERROR #1: C[A[i]] is the # of k's, *
     * should -1 before used as index     *
     **************************************/
    B[C[A[i]]-1] = A[i];
    C[A[i]]--;
  }
}


int main (int argc, char *argv[]) {
  int array[] = {3,3,3,1,2,3,2,2,1,2};
  int out[10];
  StableCountingSort(array, out, 10, 3);
  for(int i=0; i<10; i++)
    printf("%d  ", out[i]);
  printf("\n");
  return 0;
}
