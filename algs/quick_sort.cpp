#include <cstdio>
#include <cstdlib>
#include <ctime>

#define RANDOM

int Partition(int *array, int p, int r) {
  int cur_index = p-1;
  int temp;
#ifdef RANDOM
  int temp_index = rand()%(r-p+1) + p;
  temp = array[temp_index];
  array[temp_index] = array[r];
  array[r] = temp;
#endif // RANDOM
  int pivot = array[r];
  for (int i=p; i<r; i++) {
    if(array[i] <= pivot) {
      cur_index++;
      temp = array[i];
      array[i] = array[cur_index];
      array[cur_index] = temp;
    }
  }
  cur_index++;
  temp = array[r];
  array[r] = array[cur_index];
  array[cur_index] = temp;
 
  return cur_index;
}

void QuickSort(int *array, int p, int r) {
  /*****************************************
   * ERROR #1: forget to check bottom out! *
   * So it loops forever until segfault    *
   *****************************************/
  if(p<r) {
    int q = Partition(array, p, r);
    QuickSort(array, p, q-1);
    QuickSort(array, q+1, r);
  }
}

int main (int argc, char *argv[]) {
#ifdef RANDOM
  srand(time(NULL));
#endif // RANDOM
  int array[] = {4,7,6,9,1,3,2,0,5,8, 101, 45, 43, 87685};
  QuickSort(array, 0, 13);
  for (int i=0; i<14; i++) 
    printf("%d, ", array[i]);
  printf("\n");
  return 0;
}

