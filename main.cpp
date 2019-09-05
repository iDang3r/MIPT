//  Problem - Onegin
//  main.cpp
//  DeD32
//
//  Created by Александр on 02/09/2019.
//  Copyright © 2019 Alex. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <math.h>

const int MAX_LINES = 5000;
const int MAX_CHARS = 100;

int input (char*, char**);
void output (char*, char**, int);
int comparator (char*, char*);
void q_sort (char**, int);
int partition (char**, int);
void swap (char**, char**);
void check_enter (char*);
int is_empty (char*);

int main() {
    char name_in_f[] = "/Users/alex/Desktop/XCode/DeD32/DeD32/in.txt";
    char name_out_f[] = "/Users/alex/Desktop/XCode/DeD32/DeD32/out.txt";
    
    char text[MAX_LINES + 1][MAX_CHARS + 1] = {};
    char* index[MAX_LINES + 1];
    for (int i = 0; i < MAX_LINES; ++i)
        index[i] = text[i];
    
    int lines_num = input(name_in_f, index);
    
    check_enter(index[lines_num - 1]);
    
//    printf("кол-во строк: %d\n", lines_num);
    
    q_sort(index, lines_num);
    
    output(name_out_f, index, lines_num);
//    printf("End of program\n");
    return 0;
}

int input (char* name_f, char** index) {
    assert(index != nullptr);
    FILE* F_read = fopen(name_f, "r");
    assert(F_read != nullptr);
    int lines_num = 0;
    while (lines_num < MAX_LINES && fgets(index[lines_num], MAX_CHARS, F_read)) {
        if (is_empty(index[lines_num]))
            continue;
        ++lines_num;
    }
    assert(lines_num <= MAX_LINES);
    fclose(F_read);
    return lines_num;
}

void output (char* name_f, char** index, int lines_num) {
    assert(index != nullptr);
    FILE* F_write = fopen(name_f, "w");
    assert(F_write != nullptr);
    for (int i = 0; i < lines_num; ++i)
        fputs(index[i], F_write);
    fclose(F_write);
}

int comparator (char* s1, char* s2) {
    assert(s1 != nullptr);
    assert(s2 != nullptr);
    for (; *s1 == *s2; ++s1, ++s2)
        if (*s1 == '\0')
            return 0;
    return int(*s1 - *s2);
}

void q_sort (char** index, int n) {
    assert(index != nullptr);
    assert(0 <= n && n <= MAX_LINES);
    int part = partition(index, n);
    if (part > 0)
        q_sort(index, part);
    if (part < n - 1)
        q_sort(index + part + 1, n - (part + 1));
}

int partition (char** index, int n) {
    assert(index != nullptr);
    assert(0 <= n && n <= MAX_LINES);
    if (n <= 1)
        return 0;
    char* pivot = index[n - 1];
    assert(n >= 2);
    int i = 0, j = n - 2;
    while (i <= j) {
        for (; comparator(index[i], pivot) < 0; ++i);
        for (; j >= 0 && comparator(index[j], pivot) >= 0; --j);
        if (i < j)
            swap(&index[i], &index[j]);
    }
    swap(&index[i], &index[n - 1]);
    return i;
}

void swap (char** x, char** y) {
    assert(x != nullptr);
    assert(y != nullptr);
    char* t = *x;
    *x = *y;
    *y = t;
}

void check_enter (char* s) {
    assert(s != nullptr);
    int pos = 0;
    for (; s[pos] != '\n' && s[pos] != '\0'; ++pos);
    if (s[pos] == '\n')
        return;
    assert(pos < MAX_LINES);
    s[pos] = '\n';
    s[pos + 1] = '\0';
}

int is_empty (char* s) {
    assert(s != nullptr);
    while (*s == '\n' || *s == ' ' || *s == '\t')
        ++s;
    return (*s == '\0') ? 1 : 0;
}
