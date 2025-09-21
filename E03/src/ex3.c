#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)
#define LARGEST_CACHE_SZ (8 * MB)
#define ARRAY_SIZE 100000
#define NUM_ITERATIONS 10
static unsigned char dummy_buffer[LARGEST_CACHE_SZ];

void clean_cache() {
    unsigned long long i;
    for (i = 0; i < LARGEST_CACHE_SZ; i++)
        dummy_buffer[i] += 1;
}


void bubble_sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void generate_random_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand() % 10000; 
    }
}

void copy_array(int source[], int dest[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void print_array(int arr[], int n) {
    int i;
    printf("Array: ");
    for (i = 0; i < n ; i++) { 
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void test_bubble_sort(int original_arr[], int n) {
    int *arr = malloc(n * sizeof(int));
    
    copy_array(original_arr, arr, n);
    clean_cache();
    
    bubble_sort(arr, n);
    print_array(arr, n);
    
    free(arr);
}

void test_selection_sort(int original_arr[], int n) {
    int *arr = malloc(n * sizeof(int));
    
    copy_array(original_arr, arr, n);
    clean_cache();
    
    selection_sort(arr, n);
    
    print_array(arr, n);
    
    free(arr);
}

void test_insertion_sort(int original_arr[], int n) {
    int *arr = malloc(n * sizeof(int));
    
    copy_array(original_arr, arr, n);
    clean_cache();
    
    insertion_sort(arr, n);
    
    print_array(arr, n);
    
    free(arr);
}


int main() {
    int *original_array = malloc(ARRAY_SIZE * sizeof(int));
    
    srand(time(NULL));
    
    generate_random_array(original_array, ARRAY_SIZE);
    
    for (int iteration = 1; iteration <= NUM_ITERATIONS; iteration++) {
        
        test_bubble_sort(original_array, ARRAY_SIZE);
        
        test_selection_sort(original_array, ARRAY_SIZE);
        
        test_insertion_sort(original_array, ARRAY_SIZE);
        
    }
    
    free(original_array);
    return 0;
}
