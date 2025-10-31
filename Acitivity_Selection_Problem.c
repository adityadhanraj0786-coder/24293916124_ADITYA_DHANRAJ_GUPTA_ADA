// Basic Activity Selection with static data (Greedy by earliest finish time)
#include <stdio.h>
int main(void) {
    // Static example data
    int s[] = {1, 3, 0, 5, 8, 5};
    int f[] = {2, 4, 6, 7, 9, 9};
    int n = sizeof(s) / sizeof(s[0]);
    // Bubble sort by finish time (keeps s and f paired)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (f[j] > f[j + 1]) {
                int tf = f[j]; f[j] = f[j + 1]; f[j + 1] = tf;
                int ts = s[j]; s[j] = s[j + 1]; s[j + 1] = ts;
            }
        }
    }
    // Greedy selection
    int last_finish = -1; // works since times are non-negative
    int count = 0;
    printf("Selected activities (start, finish):\n");
    for (int i = 0; i < n; i++) {
        if (s[i] >= last_finish) {        // non-overlapping condition
            printf("(%d, %d)\n", s[i], f[i]);
            last_finish = f[i];
            count++;
        }
    }
    printf("Maximum count = %d\n", count);
    return 0;
}
