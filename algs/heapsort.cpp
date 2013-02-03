#include <cstdio>
#include <cstdlib>
#include <cmath>

/**********************************************
 * If index starts from zero, then the indices 
 * of children are 2i+1 and 2i+2
 **********************************************/
inline int LEFT(int i) { return 2*i+1; }
inline int RIGHT(int i) { return 2*i+2; }
inline int PARENT(int i) { return ceil(i/2)-1; }

void MaxHeapify(int *array, int i, int length) {
  int l = LEFT(i);
  int r = RIGHT(i);
  int largest = i, temp;

  if(l<length && array[l]>array[largest])
    largest = l;

  if(r<length && array[r]>array[largest])
    largest = r;

  if(largest != i) {
    temp = array[i];
    array[i]=array[largest];
    array[largest] = temp;
    MaxHeapify(array, largest, length);
  }
  return;
}

void BuildMaxHeap(int *array, int length) {
  for(int i=floor((length-1)/2); i>=0; i--)
    MaxHeapify(array, i, length);
  return;
}

void HeapSort(int *array, int length) {
  BuildMaxHeap(array, length);
  int temp;
  int heap_size = length;
  while(heap_size > 1) {
    temp = array[0];
    array[0] = array[heap_size-1];
    array[heap_size-1] = temp;
    MaxHeapify(array, 0, --heap_size);
  }
}

int main() {
  int array[] = {1,3,7,9,14,8,4,2,10,16};
  HeapSort(array, 10);
  for(int i=0; i<10; i++)
    printf("%d  ", array[i]);
  printf("\n");
  return 0;
}
