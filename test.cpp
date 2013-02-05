#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char cptr1[] = {'a', 'b'};
    printf("sizeof(): %lu, strlen(): %zd\n", sizeof(cptr1), strlen(cptr1));
    
    char *cptr2 = "ab";
    printf("sizeof(): %lu, strlen(): %zd\n", sizeof(cptr2), strlen(cptr2));
    return 0;
}
