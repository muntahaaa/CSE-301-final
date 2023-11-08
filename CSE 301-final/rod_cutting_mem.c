#include <stdio.h>
#include <limits.h>

int price[10];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int memoized_cut_rod_aux(int p[], int n, int r[]) {
    int q;
    if (r[n] >= 0) return r[n];
    if (n == 0) q = 0;
    else q = INT_MIN; 

    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
    }
    r[n] = q;

    return q;
}

int memoized_cut_rod(int p[], int n) {
    int r[n + 1];
    for (int i = 0; i <= n; i++) {
        r[i] = INT_MIN; 
    }
    return memoized_cut_rod_aux(p, n, r);
}

int main() {
    freopen("rodPrice.txt", "r", stdin);
    int len;
    scanf("%d", &len);
    for (int i = 1; i <= len; i++) {
        scanf("%d", &price[i]);
    }
    int result = memoized_cut_rod(price, len);
    printf("result: %d\n", result);
    return 0; 
}
