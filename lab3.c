#include <stdio.h>

void strcpy2(char *tab1, char *tab2);
void strcpyinverted(char *tab1, char *tab2);
int f1(void);
int f2(void);
void dodawaniemacierzy(double tab1[3][3], double tab2[3][3], double wynik[3][3]);
void mnozeniemacierzy(double tab1[3][3], double tab2[3][3], double wynik[3][3]);
void wczytajmacierz(double tab[3][3]);
void wypisz(double tab[3][3]);
void zamien_na_duze(char *text);

int main() {
/*  int a, *ws, tab[10] = {5,4,1,8,2,6,5,11,10,3};
    ws = tab+2; //1

    printf("%d\n", *ws);
    printf("%p\n", ws);
// ---------------------------
    a = tab[4]; //2
    printf("%d\n", a);
    a = *(tab+4); //2
    printf("%d\n", a);
    a = *ws; // 1
    printf("%d\n", a);
    a = *ws+3; // 4
    printf("%d\n", a);
    a = *(ws+3); // 6
    printf("%d\n", a);
// ---------------------------
    ws = tab;
    printf("%p\n", ws);

    ws++;
    printf("%p\n", ws);

    ws+=4;
    printf("%p\n", ws);*/
// ---------------------------
    /*unsigned char t1[4] = {51,52,53,54}, t2[4] = {11,12,13,14}, a, b, c ,*w;
    printf("%d\n%d", t1[6], t2[6]);
    a = 11, b = 12, c = 13;
    w = &b;
    printf("%d\n", *(w+1));
    printf("%p\n", &a);
    printf("%p\n", &b);
    printf("%p\n", &c);*/
// ---------------------------
    /*int *tabw[10], tab[10] = {1,3,2,4,8,5,9,6,10,7}, j=0;

    for (int i=9; i >= 0; i--) {
        tabw[i] = &tab[j++];
    }

    for (int i=0; i < 10; i++) {
        printf("%d ", *tabw[i]);
    }*/
// ---------------------------

    /*int tab[4][3] = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}}, (*w)[3];
    printf("%p %p", tab+1, tab[0]+1);
    w = tab[0];
    printf("\n%p\n", w);
    w = tab;
    printf("%p\n", w);
    w+=1;
    printf("%p\n", w);
    w[0+1];
    printf("%p\n", w);*/
// ---------------------------

    /*int a = 5, *w1, **w2, ***w3, ****w4;

    w1 = &a;
    w2 = &w1;
    w3 = &w2;
    w4 = &w3;

    printf("%d\n", ****w4);
    printf("%p\n", ***w4);
    printf("%p\n", **w4);
    printf("%p\n", *w4);
    printf("%p\n", w4);
    printf("%d\n", **w2);
// ---------------------------

    if (f1() || f2()) printf("Spełniono!");
    double tab[3][3];
    double tab1[3][3];
    double tab2[3][3];


    wczytajmacierz(tab1);
    wczytajmacierz(tab2);

    dodawaniemacierzy(tab1, tab2, tab);
    wypisz(tab);
    mnozeniemacierzy(tab1, tab2, tab);
    wypisz(tab);

// ---------------------------

    char tekst[10] = "HelloWorld";
    zamien_na_duze(tekst);

    int a = 8;
    int *wsk;
    wsk = &a;
    int **w;
    w = &wsk;
    printf("%p\n", *w);
    printf("Wartość: %d\nAdres w pamięci: %p", a, wsk);  */

}

void strcpy2(char *tab1, char *tab2) {

    while (*tab2++ = *tab1++);
}

void strcpyinverted(char *tab1, char *tab2) {

    int count = 0;
    while (*tab1) count++;
    int j=0;

    for(int i = count; i >= 0;i--) {
        tab2[j++] = tab1[i];
    }
}

int f1(void) {
    printf("Wywołano f1\n");
    return 1;
}

int f2(void) {
    printf("Wywołano f2\n");
    return 1;
}

void dodawaniemacierzy(double tab1[3][3], double tab2[3][3], double wynik[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            wynik[i][j] = tab1[i][j] + tab2[i][j];
        }
    }
}

void mnozeniemacierzy(double tab1[3][3], double tab2[3][3], double wynik[3][3]) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j< 3; j++) {
            wynik[i][j] = tab1[i][j] * tab2[i][j];
        }
    }
}

void wczytajmacierz(double tab[3][3]) {
    printf("Podaj 9 liczb: ");

    for (int i = 0; i < 3; ++i) {
        for (int j=0; j < 3; j++) {
            scanf("%lf", &tab[i][j]);
        }
    }
}

void zamien_na_duze(char *text) { // TODO -> za pomocą ASCII ('A'-'a') na wskaźnikach!

    while (*text++) {
        if (*text >= 70) {
            *text = 'A' - 'a';
        }
    }
}

void wypisz(double tab[3][3]) {

    for (int i = 0; i < 3; ++i) {
        for (int j=0; j < 3; j++) {
            printf(" %f ", tab[i][j]);
        }
    }
}