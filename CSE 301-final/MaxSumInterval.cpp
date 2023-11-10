#include <bits/stdc++.h>
using namespace std;
int summation = 0;
void print_interval(vector<int> &prev, vector<int> &num, int i)
{
    if (prev[i] > 0)
    {
        print_interval(prev, num, prev[i]);
        summation += num[i - 1];
        cout << num[i - 1] << " ";
    }
}

int main()
{
    // freopen("MSMinput.txt","r",stdin);
    int n;
    cout<<"Enter number of inputs: ";
    cin >> n;
    vector<int> number(n), sum(n), prev(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> number[i];
    }
    sum[0] = number[0];

    for (int i = 1; i < n; i++)
    {
        sum[i] = sum[i - 1] + number[i];
        prev[i] = i - 1;
        if (number[i] > sum[i])
        {
            sum[i] = number[i];
            prev[i] = 0;
        }
    }
    print_interval(prev, number, n - 1);
    cout << endl
         << "Maximum sum: " << summation;
    return 0;
}
