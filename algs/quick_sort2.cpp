#include <cstdio>
#include <cstdlib>

int Partition (int *array, int p, int q) {
  int pivot = array[q];

  int i = p-1;
  int temp;

  for (int j=p; j<q; j++) {
    if (array[j] < pivot) {
      i++;
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }
  i++;
  array[q] = array[i];
  array[i] = pivot;
  return i;
}

void PartitionSort(int *array, int p, int q) {
  if(p>=q)
    return;
  int mid = Partition(array, p, q);
  printf("%d %d %d\n", p, mid, q);
  PartitionSort(array, p, mid-1);
  PartitionSort(array, mid+1, q);
}

int main () {
  int test [] = {4,5,1,6,2, 4325,2352345, 2340,2354985};

  PartitionSort(test, 0, 8);

  for (int i=0; i<9; i++)
    printf("%d ", test[i]);

  printf("\n");

  return 0;
}

