#include <cstdio>
#include <cstdlib>

bool FindSum(int *array, int length, int x) {
  int l_ind = 0;
  int r_ind = length-1;
  int temp_sum;
  while (l_ind < r_ind) {
    temp_sum = array[l_ind]+array[r_ind];
    if(temp_sum == x) {
      printf("idx1 = %d, idx2 = %d\n", l_ind, r_ind);
      return true;
    }
    else if(temp_sum < x)
      l_ind++;
    else
      r_ind--;
  }
  return false;
}

int main(int argc, char *argv[]) {
  int arr[] = {0,1,2,3,4,5,6,7,8,9};
  int sum = atoi(argv[1]);

  FindSum(arr, 10, sum);
  return 0;
}
