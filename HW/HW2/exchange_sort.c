#include <stdio.h>

void exchange(int *, int *);
void print_array (int *, int);

int main(){
    int series[] = {16,25,39,27,12,8,45,63,2,10,74,17,96,43,2,87,11,6,80,90};
    int size = sizeof(series)/4;  //The length of array
    int i,j;

    printf("The original array is : ");
    print_array(series,size);

    while (j>0) {
        j = 0;
        for (i=0;i<(size-1);i++) {
            if (series[i+1]<series[i]) {
                exchange(series+i,series+i+1);
                j += 1;
            }
        }
    }

    printf("The sorted array is : ");
    print_array(series,size);
}

void exchange(int *x1, int *x2) {
    int temp = *x1;
    *x1 = *x2;
    *x2 = temp;
}

void print_array(int *array, int len) {
    int i=0;
    for (i=0;i<len;i++) {
        printf("%d, ", *(array+i));
    }
    printf("\n");
}
