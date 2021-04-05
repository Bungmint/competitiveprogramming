#include <bits/stdc++.h>

using namespace std;
int arr[1 << (12)], mat[6][6], mat_copy[6][6];

int black_sq(int num1, int num2, int h, int w)
{
    for (int i = 0; i < h; i++)
    {
        if ((num1 & (1 << i)) != 0)
        {
            for (int j = 0; j < w; j++)
            {
                mat_copy[i][j] = 2;
            }
        }
    }
    for (int j = 0; j < w; j++)
    {
        if ((num2 & (1 << j)) != 0)
        {
            for (int i = 0; i < h; i++)
            {
                mat_copy[i][j] = 2;
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (mat_copy[i][j] == 1)
                counter++;
        }
    }

    return counter;
}

int main()
{
    int h, w, k;
    cin >> h >> w >> k;
    for (int i = 0; i < h; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < w; j++)
        {
            if (s[j] == '.')
                mat[i][j] = 0;
            else
                mat[i][j] = 1;
        }
    }

    int total = 0;
    for (int i = 0; i < (1 << (h)); i++)
    {
        for (int m = 0; m < (1 << (w)); m++)
        {
            for (int l = 0; l < h; l++)
            {
                for (int j = 0; j < w; j++)
                {
                    mat_copy[l][j] = mat[l][j];
                }
            }
            if (black_sq(i, m, h, w) == k)
                total++;
        }
    }
    cout << total << "\n";
    return 0;
}