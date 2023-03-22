#include <iostream>
using namespace std;

//Required resources
void needRes(int n, int m, int** allocation, int** max, int** need)
{
    cout << "Matrix need[n][m]:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

//Security Algorithm
void SecurityAlgorithm(int n, int m, int** need, int** allocation, bool* finish, int* work)
{
    for (int k = 0; k < n; k++)
    {
        while (finish[k] != 1)
        {
            for (int i = 0; i < n; i++)
            {
                if (finish[i] == 0)
                {
                    for (int j = 0; j < m; j++)
                    {
                        if (need[i][j] <= work[j])
                        {
                            work[j] = work[j] + allocation[i][j];
                            finish[i] = 1;
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    cout << "The system is in a safe state!" << endl;
                }
            }
        }
    }
}

//Fixing indexes
void FixingIndexes(int n, int m, int** need, int* available, int** allocation, int* safe)
{
    int* f;
    f = new int[n];
    int index = 0;
    for (int k = 0; k < n; k++) f[k] = 0;
    int y = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0)
            {
                int fl = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        fl = 1;
                        break;
                    }
                }
                if (fl == 0)
                {
                    safe[index++] = i;
                    for (y = 0; y < m; y++) available[y] += allocation[i][y];
                    f[i] = 1;
                }
            }
        }
    }
}

//Banker 's Algorithm
void BankersAlgorithm(int n, int m, int** need, int* available, int** allocation, int* requesti, int** max)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            requesti[j] = max[i][j];
            if (requesti[j] <= need[i][j])
            {
                if (requesti[j] <= available[j])
                {
                    available[j] = available[j] - requesti[j];
                    allocation[i][j] = allocation[i][j] + requesti[j];
                    need[i][j] = need[i][j] - requesti[j];
                }
                else {
                    cout << endl << "The process should expect" << endl;
                }
            }
            else {
                cout << endl << "The process exceeded the maximum requirements" << endl;
            }
        }
    }
}

//Safe sequence output
void print(int n, int* safe, bool* finish)
{
    cout << endl << "Print:" << endl;
    int fl = 1;
    for (int i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            fl = 0;
            cout << "The given sequence is not safe";
            break;
        }
    }
    if (fl == 1)
    {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n - 1; i++)
            cout << "P" << safe[i] << " ->";
        cout << "P" << safe[n - 1] << endl;
    }
}


int main()
{
    int n, m;
    cout << "Enter N and M: ";
    cin >> n >> m;
    //Dynamic memory
    cout << "Available: ";
    int* available;
    available = new int[m];
    for (int i = 0; i < m; i++) cin >> available[i];

    cout << "Allocation: ";
    int** allocation = new int* [n];
    for (int i = 0; i < n; i++) allocation[i] = new int[m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) cin >> allocation[i][j];
    }

    cout << "Max: ";
    int** max = new int* [n];
    for (int i = 0; i < n; i++) max[i] = new int[m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) cin >> max[i][j];
    }

    int** need = new int* [n];
    for (int i = 0; i < n; i++) need[i] = new int[m];
    bool* finish;
    finish = new bool[n];
    int* work;
    work = new int[m];
    int* requesti;
    requesti = new int[m];
    for (int i = 0; i < m; i++) work[i] = available[i];
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
        for (int j = 0; j < m; j++) need[i][j] = 0;
    }

    int* safe;
    safe = new int[n];

    needRes(n, m, allocation, max, need);

    SecurityAlgorithm(n, m, need, allocation, finish, work);

    FixingIndexes(n, m, need, available, allocation, safe);

    BankersAlgorithm(n, m, need, available, allocation, requesti, max);

    print(n, safe, finish);

    //Delete
    delete[] available;
    delete[] finish;
    delete[] work;
    delete[] requesti;
    for (int i = 0; i < n; i++)
    {
        delete[] allocation[i];
        delete[] max[i];
        delete[] need[i];
    }
    delete[] allocation;
    delete[] max;
    delete[] need;
    return 0;
}