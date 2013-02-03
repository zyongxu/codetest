#include <cstdio>
#include <cstdlib>
#include <cstring>

void Merge (int *array, int p, int q, int r) {
  int *L = new int [q-p+2];
  int *R = new int [r-q+1];

  if (!memcpy(L, array+p, sizeof(*array)*(q-p+1)))
    return;
  if (!memcpy(R, array+q+1, sizeof(*array)*(r-q)))
    return;

  L[q-p+1] = 0x7fffffff;
  int *ltemp = L;
  R[r-q] = 0x7fffffff;
  int *rtemp = R;

  for (int i=p; i<=r; i++) {
    if(*ltemp < *rtemp) {
      array[i] = *ltemp;
      ltemp++;
    } else {
      array[i] = *rtemp;
      rtemp++;
    }
  }

  delete [] L;
  delete [] R;
}

void MergeSort(int *array, int p, int r) {
  if (p >= r)
    return;
  
  MergeSort(array, p, (p+r)/2);
  MergeSort(array, (p+r)/2+1, r);
  Merge(array, p, (p+r)/2, r);

}

int main () {
  int test [] ={4,5,3,2,1};

  MergeSort(test, 0, 4);
  for(int i=0; i<5; i++)
    printf("%d ", test[i]);

  printf("\n");
  return 0;
}

