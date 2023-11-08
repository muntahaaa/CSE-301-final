#include <iostream>
#include <string>
int minOfThree(int a, int b, int c)
{
    return std::min(std::min(a, b), c);
}
using namespace std;
int c[50][50];
char arrow[50][50];
char x[] = "heater";
char y[] = "speak";

void print_path(int lenX, int lenY)
{
    if (!lenX)
    {
        cout << "insert " << y[lenY - 1] << endl;
        return;
    }
    if (!lenY)
    {
        cout << "delete " << x[lenX - 1] << endl;
        return;
    }
    if (arrow[lenX][lenY] == 's')
    {
        print_path(lenX - 1, lenY - 1);
        cout << "substitute " << x[lenX - 1] << " with " << y[lenY - 1] << endl;
    }
    else if (arrow[lenX][lenY] == 'd' && lenY)
    {
        print_path(lenX - 1, lenY);
        cout << "delete " << x[lenX - 1] << endl;
    }
    else if (arrow[lenX][lenY] == 'i' && lenX)
    {
        print_path(lenX, lenY - 1);
        cout << "insert " << y[lenY - 1] << endl;
    }
    else if (arrow[lenX][lenY] == 'n')
    {
        print_path(lenX - 1, lenY - 1);
    }
}

void edit_dist(int lenX, int lenY)
{
    int subs, del, insert;
    for (int i = 0; i <= lenX; i++)
    {
        c[i][0] = i;
        arrow[i][0] = 'd';
    }
    for (int j = 0; j <= lenY; j++)
    {
        c[0][j] = j;
        arrow[0][j] = 'i';
    }
    for (int i = 1; i <= lenX; i++)
    {
        for (int j = 1; j <= lenY; j++)
        {
            if (x[i - 1] == y[j - 1]) // x[i-1] cuz 2D array 1 based index but x,y string is 0 based indexed
            {
                c[i][j] = c[i - 1][j - 1];
                arrow[i][j] = 'n';
            }
            else
            {
                subs = c[i - 1][j - 1] + 1;
                del = c[i - 1][j] + 1;
                insert = c[i][j - 1] + 1;

                if (subs <= minOfThree(subs, del, insert))
                {
                    c[i][j] = subs;
                    arrow[i][j] = 's';
                }
                else if (del <= minOfThree(subs, del, insert))
                {
                    c[i][j] = del;
                    arrow[i][j] = 'd';
                }
                else
                {
                    c[i][j] = insert;
                    arrow[i][j] = 'i';
                }
            }
        }
    }
}
void print(int lenX, int lenY)
{
    for (int i = 0; i <= lenX; i++)
    {
        for (int j = 0; j <= lenY; j++)
        {
            cout << c[i][j];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i <= lenX; i++)
    {
        for (int j = 0; j <= lenY; j++)
        {
            cout << arrow[i][j];
        }
        cout << endl;
    }
}
int main()
{

    int lenX = sizeof(x) - 1;

    int lenY = sizeof(y) - 1;

    edit_dist(lenX, lenY);
    // print(lenX,lenY);
    printf("\nedit dist: %d\n", c[lenX][lenY]);
    cout << endl;
    print_path(lenX, lenY);
}