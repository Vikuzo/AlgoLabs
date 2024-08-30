#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N);
int majorityR(int *a, int N, int l, int r);
int ricomb(int *a, int l1, int r1, int l2, int r2, int m, int N);

int main(int argc, char* argv[]){
    int v[] = {0, 1, 0, 2, 3, 4, 0, 5}, r = majority(v, 8);

    if(r == -1)
        printf("Nessun maggioritario.");
    else
        printf("Il valore maggioritario e': %d", r);

    return 0;
}

int majority(int *a, int N){
    return majorityR(a, N, 0, N - 1);
}

int majorityR(int *a, int N, int l, int r){
    int ml = -1, mr = -1, res = -1, q;

    if(l == r)
        return a[l];

    q = (l + r)/2;
    ml = majorityR(a, N, l, q);
    mr = majorityR(a, N, q + 1, r);

    if(ml != -1)
        res = ricomb(a, l, q, q + 1, r, ml, N);
    
    if(mr != -1)
        res = ricomb(a, l, q, q + 1, r, mr, N);

    return res;
}

int ricomb(int *a, int l1, int r1, int l2, int r2, int m, int N){
    int counter = 0, occ = 0;

    for(int i = l1; i <= r1; i++){
        if(a[i] == m)
            occ++;
        counter++;
    }

    for(int i = l2; i <= r2; i++){
        if(a[i] == m)
            occ++;
        counter++;
    }

    if(occ > (counter/2))
        return m;
    return -1;
}