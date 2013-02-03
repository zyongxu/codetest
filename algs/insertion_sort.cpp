#include <cstdio>
#include <cstdlib>


void InsertionSort(int* in_array, int length) {
  int key, j;
  for (int i = 1; i < length; i++) {
    key = in_array[i];
    printf("sorting key = %d\n", key);
    j = i-1;
    while (j>=0 && in_array[j] > key) {
      in_array[j+1] = in_array[j];
      j--;
    }
    in_array[j+1] = key;
  }
}

int main() {
  int seq[10] = {4, 6, 9, 1, 3, 5, 2, 8, 7, 0};
  InsertionSort(seq, 10);
  for(int i=0; i<10; i++) {
    printf("%d\n", seq[i]);
  }
  return 0;
}
