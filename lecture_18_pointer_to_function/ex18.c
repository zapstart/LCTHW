/*************************************************************************************
* Function pointer
* 
* 1. Function pointer Declaring
*   1)int (*func_ptr)(int, int);
*     A pointer to a function which receives 2 ints and returns an int
*   
*   2)int *func_ptr(int, int);
*     A function which receives 2 ints and return an pointer to int
*
*   3)One more example: 
*     int * (*FuncPtr)(int, int);
*     A pointer to a function which receives 2 ints and returns a pointer to int
* 
* 2. Function return function pointer
*   There are two ways to do this:
*   
*   This is a function called functionFactory which receives parameter n 
*   and returns a pointer to another function which receives two ints 
*   and it returns another int  
*   1) int (*functionFactory(int n))(int, int); 
*
*   This is a pointer called myFuncDef point to a function which receives two ints 
*   2) typedef int (*myFuncDef)(int, int); a
*      myFuncDef functionFactory(int n);
*
*   int (* A)(int, int): (1)if A is not a function, A is function pointer which 
*                        receives two ints 
*                        (2)if A is a function, A is a function that will return a 
*                        function pointer which receives two ints 
* 
* 3. Callback
*   void populate_array(int *array, size_t arraySize, int (*getNextValue)(void)) {
        for (size_t i=0; i<arraySize; i++)
            array[i] = getNextValue();
    }

    int getNextRandomValue(void) {
        return rand();
    }

    int main(void) {
        int myarray[10];
        populate_array(myarray, 10, getNextRandomValue);
        ...
    }
*************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

/*
 * A classic bubble sort function that uses the 
 * compare_cb to do the sorting. 
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j < count - 1; j++) {
            if(cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/** 
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}


int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);

    return 0;
}
