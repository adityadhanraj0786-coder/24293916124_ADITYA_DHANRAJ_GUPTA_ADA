#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

int linearSearch(int arr[], int n, int key) { 
    for (int i = 0; i < n; i++) { 
        if (arr[i] == key) return i; 
    } 
    return -1; 
} 

int main() { 
    int n, key; 
    printf("Enter number of elements: "); 
    scanf("%d", &n); 
    
    // Validate input
    if (n <= 0) {
        printf("Invalid number of elements!\n");
        return 1;
    }
    
    // Allocate memory for array
    int *arr = malloc(n * sizeof(int)); 
    
    if (arr == NULL) { 
        printf("Memory allocation failed.\n"); 
        return 1; 
    } 
    
    // Initialize array with sorted values
    for (int i = 0; i < n; i++) { 
        arr[i] = i;  
    } 
    
    key = -2;  // Worst case - not present
    
    printf("Searching for key: %d (worst case)\n", key);
    printf("Performing 10000 searches...\n");
    
    // Record start time
    clock_t start = clock(); 
    
    // Perform searches
    for (int i = 0; i < 10000; i++) {
        linearSearch(arr, n, key); 
    } 
    
    // Record end time
    clock_t end = clock(); 
    
    // Calculate total ticks and time
    clock_t total_ticks = end - start;
    double total_time = ((double)total_ticks) / CLOCKS_PER_SEC;
    double avg_time = total_time / 10000;
    
    // Display detailed timing results
    printf("\n=== DETAILED TIMING RESULTS ===\n");
    printf("Start time (clock ticks): %ld\n", start);
    printf("End time (clock ticks):   %ld\n", end);
    printf("Total clock ticks:        %ld\n", total_ticks);
    printf("CLOCKS_PER_SEC constant:  %ld\n", CLOCKS_PER_SEC);
    
    printf("\n=== TIME CALCULATIONS ===\n");
    printf("Total time for 10000 searches: %.6f seconds\n", total_time);
    printf("Average time per search:        %.9f seconds\n", avg_time);
    printf("Average time per search:        %.6f milliseconds\n", avg_time * 1000);
    printf("Average time per search:        %.3f microseconds\n", avg_time * 1000000);
    
    printf("\n=== PERFORMANCE SUMMARY ===\n");
    printf("Array size: %d elements\n", n);
    printf("Number of searches: 10000\n");
    printf("Search type: Linear (worst case)\n");
    printf("Time complexity: O(n)\n");
    
    // Additional calculation verification
    printf("\n=== VERIFICATION ===\n");
    printf("Manual calculation: %ld ticks ÷ %ld CLOCKS_PER_SEC = %.6f seconds\n", 
           total_ticks, CLOCKS_PER_SEC, (double)total_ticks / CLOCKS_PER_SEC);
    
    free(arr); 
    return 0; 
}



