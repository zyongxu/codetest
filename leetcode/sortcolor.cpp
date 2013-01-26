/*
 * Given an array with n objects colored red, white or blue, sort them so that
 * objects of the same color are adjacent, with the colors in the order red, white
 * and blue.
 * 
 * Here, we will use the integers 0, 1, and 2 to represent the color red, white,
 * and blue respectively.
 * 
 * An one-pass algorithm using only constant space!
 */

class Solution {
public:
    void sortColors(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int p1=0;
        int p2=0;

        for (int i=0; i<n; i++) {
            if(A[i]==0) {
                A[i]=2;
                A[p2]=1;
                p2++;
                A[p1]=0;
                p1++;
            } else if (A[i]==1) {
                A[i]=2;
                A[p2]=1;
                p2++;
            }
        }
    }
};
