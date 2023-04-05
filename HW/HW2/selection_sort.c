#include <stdio.h>

void exchange(int *, int *);
void find_min(int *, int, int, int *, int *);
void print_array (int *, int);

int main() {
    int series[] = {16,25,39,27,12,8,45,63,2,10,74,17,96,43,2};
    int size = sizeof(series)/4;  //The length of array
    int i,i_min,min;

    printf("The original array is : ");
    print_array(series,size);

    for (i=0;i<size-1;i++) {
        find_min(series+i,i,size-i,&min,&i_min);
        exchange(series+i,series+i_min);
    }

    printf("The sorted array is : ");
    print_array(series,size);
}

void exchange(int *x1, int *x2) {
    int temp = *x1;
    *x1 = *x2;
    *x2 = temp;
}

void find_min(int *array, int move, int len, int *min_value, int *i_min) {
    int i;
    *i_min = move;
    *min_value = *array;
    for (i=1;i<len;i++) {
        if (*min_value > *(array+i)) {
            *min_value = *(array+i);
            *i_min = i+move;
        }
    }
}

void print_array(int *array, int len) {
    int i=0;
    for (i=0;i<len;i++) {
        printf("%d, ", *(array+i));
    }
    printf("\n");
}
