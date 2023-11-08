#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;
vector<int> price(10);

int max(int a, int b) {
    return (a > b) ? a : b;
}

int memoized_cut_rod_aux(vector<int>& p, int n, vector<int>& r) {
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

int memoized_cut_rod(vector<int>& p, int n) {
    vector<int> r(n + 1, INT_MIN);
    return memoized_cut_rod_aux(p, n, r);
}

int main() {
    ifstream input("rodPrice.txt");
    if (!input.is_open()) {
        cerr << "Error opening file." << std::endl;
        return 1;
    }

    int len;
    input >> len;
    for (int i = 1; i <= len; i++) {
        input >> price[i];
    }
    input.close();

    int result = memoized_cut_rod(price, len);
    cout << "result: " << result << endl;
    return 0;
}
