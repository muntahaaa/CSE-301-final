#include <bits/stdc++.h>>
#define mx 100
using namespace std;
int mat[mx][mx], size;

template <typename T>
class uniqueVector
{
public:
    void push(const T &e)
    {
        if (elementToIndex.find(e) == elementToIndex.end())  //if finds then 0, if not found then if(1)
        {
            elements.push_back(e);
            elementToIndex[e] = elements.size() - 1;
        }
    }

    bool contains(const T &e) const
    {
        return elementToIndex.find(e) != elementToIndex.end();  //if found make the 0 to 1 and return true
    }

    int getIndex(const T &e) const
    {
        auto it = elementToIndex.find(e);
        if (it != elementToIndex.end())
        {
            return it->second;
        }
        return -1;
    }
    void printAll() const
    {
        for (const T &element : elements)
        {
            cout << element << " ";
        }
        cout << endl;
    }

    int getElementToIndexCount() const
    {
        return static_cast<int>(elementToIndex.size());
    }

private:
    vector<T> elements;
    unordered_map<T, int> elementToIndex;
};

void initialize(uniqueVector<string> places)
{
    freopen("floyd.txt", "r", stdin);
    int test, wt, srcIndex, destIndex;

    cin >> test;
    for (int row = 0; row < mx; row++)
    {
        for (int col = 0; col < mx; col++)
        {
            if (row == col)
                mat[row][col] = 0;
            else
                mat[row][col] = INT_MAX;
        }
    }
    for (int i = 0; i < test; i++)
    {
        string src, dest;
        cin >> src >> dest;
        cin >> wt;
        places.push(src);
        places.push(dest);
        srcIndex = places.getIndex(src);
        cout << "src ind " << src << " " << srcIndex << endl;
        destIndex = places.getIndex(dest);
        cout << "dest ind " << dest << " " << destIndex << endl;
        mat[srcIndex][destIndex] = wt;
        size = places.getElementToIndexCount();
    }
}

void printMat(uniqueVector<string> places)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            cout << mat[i][j] << "\t  ";
        }
        cout << endl;
    }
}
void floydWarshall()
{
    int i, j, k;

    for (k = 0; k < size; k++)
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                if (mat[i][k] + mat[k][j] < mat[i][j] && mat[k][j] != INT_MAX && mat[i][k] != INT_MAX)
                {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
}

int main()
{
    uniqueVector<string> places;
    initialize(places);
    cout << "size: " << size << endl;
    cout << "Elements in the set: ";
   
    places.printAll();
    cout << endl;
    printMat(places);
    floydWarshall();
    cout << endl;
    printMat(places);
}
