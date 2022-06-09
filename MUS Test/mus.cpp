#include <iostream>
#include <cmath>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;


int varianceL [11] = {
    2.954, 3.125, 3.238,
    3.311, 3.356, 3.384,
    3.401, 3.410, 3.416,
    3.419, 3.421
};

int expectedValueL [11] = {
    5.2177052, 6.1962507, 7.1836656,
    8.1764248, 9.1723243, 10.170032,
    11.168765, 12.168070, 13.167693,
    14.167488, 15.167379
};


int toDecimal(char* seq, int init, int end)
{
    int result = 0;
    int exp = 0;
    for(int i = end-1; i>=init; i--, exp++)
    {
        result += int(seq[i] - '0') * (1<<exp);
    }
    return result;
}


int* buildTable(char* seq, int n, int Q, int L, double* accumSum)
{
    int* table = new int[1 << L];
    int K = n/L - Q;

    for(int i = 0; i < Q; i++)
    {
        table[toDecimal(seq, i*L, (i+1)*L)] = i+1;
    }

    for(int i = Q+1; i < Q+K; i++)
    {

        int index = toDecimal(seq, i*L, (i+1)*L);
        *accumSum += log2(i-table[index]);
        table[index] = i+1;
    }

    return table;
}


void UniversalStatical(char* seq, int n, int Q, int L)
{
    int K = n/L - Q;
    double accumSum = 0;
    int* table = buildTable(seq, n, Q, L, &accumSum);

    double fn = accumSum/K;
    double c = 0.7 - 0.8/L + (4+32/L)*pow(K,-3/L)/15;
    double standardDev = c*sqrt(varianceL[L-6]/K);


    double Pvalue = erfc(abs((fn - expectedValueL[L-6])/(sqrt(2)*standardDev)));

    if(Pvalue >= 0.01)
        cout<< "Correct"<<endl;
    else
        cout<< "Incorrect"<<endl;
}


int main(int argc, char** argv){

    int Q, L, n;
    cout << "Enter Q, L, n.\n";
    cin >> Q >> L >> n;

    char* seq = new char[n];
    cout << "Enter the sequence.\n";
    cin >> seq;

    UniversalStatical(seq, n, Q, L);

    return 0;
}