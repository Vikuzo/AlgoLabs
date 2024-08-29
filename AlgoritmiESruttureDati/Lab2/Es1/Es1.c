#include <stdio.h>

int gcd(int a, int b);

int main(int agrc, char* argv[]){
    int a, b;
    
    printf("Inserire il primo numero: ");
    scanf("%d", &a);
    printf("Inserire il secondo numero: ");
    scanf("%d", &b);

    printf("Il massimo comune divisore fra i due e': %d", gcd(a, b));

    return 0;
}

int gcd(int a, int b){
    if(a < b)
        return gcd(b, a);

    if(b == 0)
        return a;

    if((a % 2) == 0 && (b % 2) == 0)
        return 2*gcd(a/2, b/2);
    else if((a % 2) != 0 && (b % 2) == 0)
        return gcd(a, b/2);
    else if((a % 2) != 0 && (b % 2) != 0)
        return gcd((a - b)/2, b);
    else
        return gcd(a/2, b);
}