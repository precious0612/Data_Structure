#include <stdio.h>

#define LENGTH 8

int find_max (int *array, int n) {
    // base case: if one element then it's the max
    if (n < 2)
        return array[n];
    
    //recursively find max in the rest of the array 
    int max = find_max(array, --n);

    //compare max of the rest of array with current element
    return array[n] > max ? array[n] : max;
}

int main() {
    int numbers[LENGTH] = {8,9,3,2,4,1,7,5};
    int n = LENGTH;
    printf("%d\n", find_max(numbers, n));  
    return 0;
}
