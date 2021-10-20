#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0

void findFirstOccurance(char text[], char word[]);
void findMultipleOccurances(char text[], char word[]);
void printTable(int table[], int size);
void stringCopy(char text1[], char text2[]);
void stringConcatenation(char text1[], char text2[]);
void stringComparison(char text1[], char text2[]);
void bubbleSort(int tab[], int size);
void pointerSearch(int tab[], int size, int num);

int main() {
    // TODO
    //  Funkcje z biblioteki <string.h>
    //  --> strlen(),  done
    //  --> strcat(),  done
    //  --> strcmp(),  done
    //  --> strncmp(), ?
    //  --> strstr(),  ?
    //  --> strcpy(),  done
}

void findFirstOccurance(char text[], char word[]) {
    int found, i=0, j=0;

    while (text[i] != '\0') {
        if (text[i] == word[0]) {
            found = TRUE;
            while (word[j] != '\0') {
                if (text[i+j] != word[j]) {
                    found = FALSE;
                    break;
                }
                j++;
            }
        }
        if (found == TRUE) break;
        i++;
    }
    if (found == TRUE) printf("Found it at index %d!", i);
}

void findMultipleOccurances(char text[], char word[]) {
    int i=0, j=1, found, counter=0;
    int indexes[MAX_SIZE];

    while (text[i] != '\0') {
        found = FALSE;
        if (text[i] == word[0]) {
            found = TRUE;
            while (word[j] != '\0') {
                if (word[j] != text[i+j]) {
                    found = FALSE;
                    break;
                }
                j++;
            }
        }
        if (found == TRUE) indexes[counter++] = i;
        i++;
    }
    if (counter != 0) {
        printf("Word you were looking for occurs %d times, at index: ", counter);
        printTable(indexes, counter);
    }
}

void printTable(int table[], int size) {

    for (int i=0; i < size; i++) {
        printf("%d ", table[i]);
    }
}

void stringCopy(char text1[], char text2[]) {
    int len1 = (int) strlen(text1);
    int len2 = (int) strlen(text2);

    for (int i=0; i < len1; i++) {
        text2[i] = text1[i];
        printf("%c", text2[i]);
    }
}

void stringConcatenation(char text1[], char text2[]) {
    int len1 = (int) strlen(text1);
    int len2 = (int) strlen(text2);

    if (len1 + len2 > MAX_SIZE) {
        printf("Strings are too big - could not perform concatenation ...");
        return;
    } else {
        for (int i=len1; i < len1 + len2; i++) text1[i] = text2[i-len1];
    }
}

void stringComparison(char text1[], char text2[]) {
    int len1 = (int) strlen(text1);
    int len2 = (int) strlen(text2);

    if (len1 != len2 || len1==0 || len2==0) {
        printf("Texts are not the same.");
        return;
    } else {
        for (size_t i=0; i<len1; i++) {
            if (text1[i] != text2[i]) {
                printf("Texts are not the same.");
                return;
            }
        }
        printf("Texts are the same!");
    }
}

void bubbleSort(int tab[], int size) {
    // Sorting
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                int k = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = k;
            }
        }
    }
}

void pointerSearch(int tab[], int size, int num)  {
    //create pointers
    int a = 0, b = size-1, middle;
    //sort table
    bubbleSort(tab, size);
    //search for number
    if (num < tab[0] || num > tab[size-1]) {
        printf("Number you are looking for is not in the array.");
    } else {
        while (a <= b) {
            middle = (a+b)/2;
            if (num > tab[middle]) {
                a = middle+1;
            } else if (num < tab[middle]) {
                b = middle-1;
            } else {
                printf("Found it on index %d!", middle);
                return;
            }
        }
        printf("Couldn't find the number %d in the aray ...", num);
    }
}
