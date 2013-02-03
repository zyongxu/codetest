/* Merge sort practice
 * 1. Be careful with INDEX and LENGTH when
 *    passing array and returning array from/to 
 *    functions
 * 2. After finishing a function, check for each 'new'
 *    and write deleting calls for each pointer with a 
 *    'new'.
 *    ATTENTION: if the pointer has been modified, such as by
 *    "*ptr++", then a "delete [] ptr" will casue segfault 
 *    or memory problem
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

void Merge(int *array, int p, int q, int r) {
  int *l_array = NULL, *r_array = NULL;
  l_array = new int [q-p+2];
  r_array = new int [r-q+1];

  /**************************************************
   * ERROR #5: Second parameter is the starting index, does not
   * simplly 'array'. Third parameter in memcpy is num of bytes,
   * not num of elements
   * ************************************************/ 
  if(!memcpy(l_array, (array+p), (q-p+1)*sizeof(int))) {
    printf("could not copy input array to local lbuffer\n");
    exit(1);
  }
  if(!memcpy(r_array, (array+q+1), (r-q)*sizeof(int))) {
    printf("could not copy input array to local rbuffer\n");
    exit(1);
  }

  /**********************************
   * ERROR #2: the index was wrong, *
   * used to be q+1, and r-q+1      *
   **********************************/
  l_array[q-p+1] = 0x7fffffff;
  r_array[r-q] = 0x7fffffff;

  /******************************************
   * ERROR #3: r is an index instead of num *
   * of elements. So should use <=, not <   *
   ******************************************/
  int li = 0, ri = 0;
  for(int k = p; k<=r; k++) {
    if(l_array[li] >= r_array[ri]) {
      array[k] = r_array[ri];
      ri++;
    } else {
      array[k] = l_array[li];
      li++;
    }
  }

  /***********************************************
   * ERROR #4: forgot to delete two local arrays *
   ***********************************************/
  if(l_array)
    delete [] l_array;
  if(r_array)
    delete [] r_array;
}

void MergeSort(int *array, int start_ind, int end_ind) {
  if (start_ind < end_ind) {
    /************************************************
     * ERROR #1: should be "+" instead of "-" here! *
     * **********************************************/
    int middle_ind = floor((end_ind + start_ind)/2);
    MergeSort(array, start_ind, middle_ind);
    MergeSort(array, middle_ind+1, end_ind);
    Merge(array, start_ind, middle_ind, end_ind);
  } else {
    return;
  }
}

int main() {
  int seq[] = {4, 9, 6, 3, 5, 1, 2, 8, 7, 0};
  MergeSort(seq, 0, 9);
}
