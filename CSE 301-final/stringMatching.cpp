#include <bits/stdc++.h>
#include <vector>
using namespace std;
vector<char> text;
vector<char> pattern;
vector<int> lps;

void computeLPS()
{
    int j = 0, count = 0;
    lps.resize(pattern.size(), 0);

    for (int i = 1; i < pattern.size();)
    {
        if (pattern[i] == pattern[j])
        {
            lps[i] = j + 1;
            i++;
            j++;
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void KMPsearch()
{
    computeLPS();
    int j = 0;
    for (int i = 0; i < text.size();)
    {

        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        if (j == pattern.size())
        {
            cout << "Pattern found at index " << i - pattern.size() << endl;
            j = lps[j - 1];
        }
        else if (i < text.size() && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}
int main()
{
    char textElement, patternElement;
    cout << "Enter text (enter '.' to end): " << endl;
    while (cin >> textElement && textElement != '.')
    {
        text.push_back(textElement);
    }

    cout << "Enter pattern (enter '.' to end): " << endl;

    while (cin >> patternElement && patternElement != '.')
    {
        pattern.push_back(patternElement);
    }

    KMPsearch();

    return 0;
}
