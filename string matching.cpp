#include <stdio.h>
#include <string.h>
#include <time.h>

// Naive String Matching Algorithm
void naiveSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            printf("Pattern found at index %d (Naive)\n", i);
        }
    }
}

// Rabin-Karp String Matching Algorithm
void rabinKarp(char* text, char* pattern, int prime) {
    int n = strlen(text);
    int m = strlen(pattern);
    int h = 1, pHash = 0, tHash = 0;
    int d = 256; // Number of characters in the input alphabet

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % prime;
    }

    for (int i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % prime;
        tHash = (d * tHash + text[i]) % prime;
    }

    for (int i = 0; i <= n - m; i++) {
        if (pHash == tHash) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                printf("Pattern found at index %d (Rabin-Karp)\n", i);
            }
        }
        if (i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + m]) % prime;
            if (tHash < 0) {
                tHash += prime;
            }
        }
    }
}

// Knuth-Morris-Pratt (KMP) String Matching Algorithm
void computeLPSArray(char* pattern, int m, int* lps) {
    int length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmpSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];

    computeLPSArray(pattern, m, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("Pattern found at index %d (KMP)\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    char text[1000], pattern[100];
    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);

    clock_t start, end;

    start = clock();
    naiveSearch(text, pattern);
    end = clock();
    printf("Naive Algorithm Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    rabinKarp(text, pattern, 101);
    end = clock();
    printf("Rabin-Karp Algorithm Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    kmpSearch(text, pattern);
    end = clock();
    printf("KMP Algorithm Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
