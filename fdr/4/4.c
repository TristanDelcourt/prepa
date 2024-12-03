#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

bool* false_tab(int n){
    bool* t = malloc(n * sizeof(bool));

    int i = 0;
    while(i<n){
        t[i++] = false;
    }

    return t;
}

int* ints(int n){
    int* t = malloc(n*sizeof(int));

    for(int i = 0; i<n; i++){
        t[i] = i+1;
    }

    return t;
}

int* rand_ints(int n, int a, int b){
    srand(time(NULL));

    int* t = malloc(n*sizeof(int));

    for(int i = 0; i<n; i++){
        t[i] = rand() % (b-a) + a;
    }

    return t;
}

bool zero_exist(int* t, int n){
    for(int i = 0; i<n; i++){
        if(t[i] == 0) return true;
    }

    return false;
}

int premier_zero(int* t, int n){
    int zero = -1;

    int i = 0;
    while(i<n && zero < 0){
        if(t[i] == 0) zero = i;
        i++;
    }

    return zero;
}

int premier_zero2(int* t, int n){
    int i = 0;

    while(i<n){
        if(t[i] == 0) return i;
        i++;
    }

    return -1;
}

int premier_zero3(int* t, int n){
    int zero = -1;

    int i = 0;
    for(int i = 0; i<n && zero < 0; i++){
        if(t[i] == 0) zero = i;
    }

    return zero;
}

int sum(int* t, int n){
    int s = 0;

    for(int i = 0; i<n; i++){
        s += t[i];
    }

    return s;
}

int min(int* t, int n){
    int imin = 0;

    for(int i = 0; i<n; i++){
        if(t[imin] > t[i]) imin = i;
    }

    return imin;
}

bool conjonction(bool* t, int n){
    bool out = t[0];
    
    int i = 0;
    while(i<n){
        t[i] = out && t[i];
        i++;
    }

    return out;
}

int maxocc(int* t, int n, int m){
    int* occ = malloc(n * sizeof(int));

    int i = 0;
    while(i<n){
        occ[i++] = 0;
    }

    int mmax = 0;
    for(int i = 0; i<n; i++){
        occ[t[i]]++;
        if(occ[t[i]] > occ[mmax]) mmax = t[i];
    }


    free(occ);
    return mmax;
}


int main(void){
    int n = 5;
    bool* t1 = false_tab(n);
    for(int i = 0; i<n; i++){
        assert(t1[i] == false);
    }
    free(t1);

    int* t2 = ints(n);
    for(int i = 0; i<n; i++){
        assert(t2[i] == i + 1);
    }
    free(t2);

    int* t3 = rand_ints(n, -8, 3);
    for(int i = 0; i<n; i++){
        assert(t3[i] >= -8 && t3[i] < 3);
    }
    free(t3);

    int t4[10] = {2,5,8,7,4,0,3,5,0,5};
    assert(zero_exist(t4, 10) == true);
    assert(premier_zero(t4, 10) == 5);
    assert(premier_zero2(t4, 10) == 5);
    assert(premier_zero3(t4, 10) == 5);
    assert(sum(t4, 10) == 39);
    assert(min(t4, 10) == 5);

    bool t5[5] = {false, true, true, false, true};
    assert(conjonction(t5, 5) == false);

    assert(maxocc(t4, 10, 8) == 5);

    return 0;
}