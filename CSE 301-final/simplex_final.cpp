#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#define Max 10
using namespace std;

vector<string> variable;
int numVar, numEq;
int equations[Max + 1][Max + Max + 1];
double table[Max + 1][Max + Max + 1];
string basicVar[Max + 1];
int keyCol, keyRow;
double rhsByKey[Max + 1];

void tablePrinting();
void simplex();
void input();
void equationsPrinting();
void simplexInitialization();

void input()
{
    cout << "Enter the number of variables in z :";
    cin >> numVar;
    cout << "Enter the number of Equations :";
    cin >> numEq;
    for (int i = 1; i <= numVar; i++)
    {
        variable.push_back("x" + to_string(i));
    }
    for (int j = 1; j <= numEq; j++)
    {
        variable.push_back("s" + to_string(j));
    }

    for (int i = 0; i < variable.size(); i++)
    {
        cout << variable[i] << endl;
    }
    // for (const string& var : variable) {
    //     cout << var << endl;
    // }

    for (int i = 0; i < numEq + 1; i++)
    {
        for (int j = 0; j < numVar + numEq + 1; j++)
        {
            equations[i][j] = 0;
        }
    }

    for (int i = 0; i < numEq + 1; i++)
    {
        if (i == 0)
        {
            cout << "z ==" << endl;
            for (int j = 0; j < numVar; j++)
            {
                cout << "Enter the coefficient of" << variable[j] << " :";
                cin >> equations[i][j];
                equations[i][j] = -equations[i][j];
            }
        }
        else
        {
            cout << "Equation " << i << " :" << endl;
            for (int j = 0; j < numVar; j++)
            {
                cout << "Enter the coefficient of" << variable[j] << " :";
                cin >> equations[i][j];
            }
            cout << "Enter the RHS :";
            cin >> equations[i][numEq + numVar];
            equations[i][i + numVar - 1] = 1;
        }
    }
}

void equationsPrinting()
{
    for (int i = 0; i < numEq + 1; i++)
    {
        if (i == 0)
        {
            cout << "z ";
        }
        for (int j = 0; j < numEq + numVar + 1; j++)
        {
            if (j == numEq + numVar)
                cout << "=";
            cout << equations[i][j] << variable[j] << " ";
        }
        cout << endl;
    }
}

void simplexInitialization()
{
    for (int i = 0; i < numEq + 1; i++)
    {
        if (i == 0)
            basicVar[i] = "z";
        else
            basicVar[i] = variable[numVar + i - 1];
    }

    cout << "basic variables :" << endl;
    for (int i = 0; i < numEq + 1; i++)
    {
        cout << basicVar[i] << endl;
    }

    for (int i = 0; i < numEq + 1; i++)
    {
        for (int j = 0; j < numEq + numVar + 1; j++)
        {
            table[i][j] = equations[i][j];
        }
    }
}

void simplex()
{
    bool flag = true;
    int initial = 0;

    while (flag)
    {
        if (initial == 0)
        {
            simplexInitialization();
        }
        int min = 0;
        for (int i = 0; i < numVar + numEq; i++)
        {
            if (table[0][i] < min)
            {
                min = table[0][i];
                keyCol = i;
            }
        }
        if(min==0){
            break;
        }
        for (int i = 0; i < numEq + 1; i++)
        {
            rhsByKey[i] = (double)table[i][numVar + numEq] / table[i][keyCol];
        }

        if (initial == 0)
        {
            tablePrinting();
            initial++;
        }

        double max = 123456;
        for (int i = 0; i < numEq + 1; i++)
        {
            if (rhsByKey[i] < max && rhsByKey[i] > 0)
            {
                max = rhsByKey[i];
                keyRow = i;
                cout << "hi  :" << max << "  " << keyRow << endl;
            }
        }
    

    cout << "Key col :" << keyCol << endl;
    cout << "Key row :" << keyRow << endl;

    double pivotElement = table[keyRow][keyCol];

    if (pivotElement == 0.0)
    {
        cout << "Pivot element is zero. The problem may be unbounded." << endl;
        return; // Exit or handle the unbounded case as needed
    }

    // Perform division only if the pivot element is not zero
    for (int i = 0; i < numEq + numVar + 1; i++)
    {
        table[keyRow][i] = table[keyRow][i] / pivotElement;
    }

    for (int i = 0; i < numEq + 1; i++)
    {
        if (i != keyRow)
        {
            double temPivot = table[i][keyCol];
            for (int j = 0; j < numEq + numVar + 1; j++)
            {
                table[i][j] = table[i][j] - temPivot * table[keyRow][j];
            }
        }
    }
    basicVar[keyRow] = variable[keyCol];

    tablePrinting();

    }
}

void tablePrinting()
{
    cout << endl
         << endl
         << endl;

    // Set column width for fixed-width output
    int columnWidth = 10;
    cout << left;

    // Header
    cout << setw(columnWidth) << "BasicVar";
    for (int j = 0; j < numVar + numEq; j++)
    {
        cout << setw(columnWidth) << variable[j];
    }
    cout << setw(columnWidth) << "RHS";
    cout << setw(columnWidth) << "RHS/key" << endl;

    // Table rows
    cout.precision(2); // Set precision for floating-point numbers
    cout << fixed;     // Use fixed-point notation
    for (int i = 0; i < numEq + 1; i++)
    {
        cout << setw(columnWidth) << basicVar[i];
        for (int j = 0; j < numVar + numEq + 1; j++)
        {
            cout << setw(columnWidth) << table[i][j];
        }
        cout << setw(columnWidth) << rhsByKey[i] << endl;
    }
}

// void tablePrinting()
// {
//     cout << endl
//          << endl
//          << endl;

//     for (int i = 0; i <= 3; i++)
//     {
//         if (i == 0)
//             cout << "BasicVar"
//                  << " ";
//         else if (i == 1)
//         {
//             for (int j = 0; j < numVar + numEq; j++)
//             {
//                 cout << variable[j] << "   ";
//             }
//         }
//         else if (i == 2)
//         {
//             cout << "RHS  ";
//         }
//         else
//         {
//             cout << "RHS/key ";
//         }
//     }
//     cout << endl;

//     for (int i = 0; i < numEq + 1; i++)
//     {
//         cout << basicVar[i] << "        ";
//         for (int j = 0; j < numVar + numEq + 1; j++)
//         {
//             cout << table[i][j] << "    ";
//         }
//         cout <<" " <<rhsByKey[i] << endl;
//     }
// }

int main()
{
    input();
    equationsPrinting();
    simplex();

    cout<<endl<<endl<<endl;
    cout<<"The optimal solution is"<<table[0][numVar+numEq]<<endl;
    for(int i=0;i<numVar;i++){
        bool flag=true;
        for(int j=0;j<numEq;j++){
            if(basicVar[j]==variable[i]){
                cout<<basicVar[j]<<" :"<<table[j][numVar+numEq]<<endl;
                flag=false;
            }
            
        }
        if(flag)
        cout<<variable[i]<<" :"<<" 0"<<endl;
    }
}