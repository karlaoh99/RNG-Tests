#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


int* initArray(int length){
    int* v = new int[length];
    for(int i = 0; i<length; i++)
        v[i] = 0;
    
    return v;
}


double Chi_Square(int N, int* v, double* pi){
    double result = 0;
    for(int i = 0; i<5; i++){
        double base = v[i] - N*pi[i];
        result += pow(base, 2)/pi[i];
    }
    return result/N;
}


double* calcPi(double eta, int K){    //#TODO
    return 0;
    int* pi = initArray(K+1);
    for(int i = 0; i<=K; i++)
    {
        pi[i] = eta*exp(-2*eta)/pow(2,i);// * hipergeometric_func(i+1,2,eta);
    }
}


double calcPvalue(int N, double chi){    //#TODO
    return 0;
    //return igamc_func(N/2, chi/2);
}


int* calcMatches(int m, int n, char* seq, int M, int N, int K)
{
    int* v = initArray(K+1);
    for(int i = 0; i < N; i++)
    {
        int counter = 0;
        for(int j = i*M; j < (i+1)*M ; j++)
        {
            bool matches = true;
            for(int k = 0; k < (M-m)+1; k++)
            {
                if(!(int(seq[j+k] - '0') & 1))
                {
                    matches = false;
                    break;
                }
            }
            if(matches)
                counter++;
        }
        v[K ? counter > K-1 : counter] ++;
    }
    return v;
}


void OverlappingTemplateMatching(int m,  int n, char* seq, int M, int N, int K){
    int* v = calcMatches(m, n, seq, M, N, K);

    double lambda = (M-m+1)/1<<m;
    double eta = lambda/2;

    double* pi = calcPi(eta, K);
    double chi = Chi_Square(N, v, pi);
    double Pvalue = calcPvalue(N, chi);

    if(Pvalue >= 0.01)
        cout<< "Correct"<<endl;
    else
        cout<< "Incorrect"<<endl;

}


int main(int argc, char** argv){

    cout << "Enter n, m, M, N, K.\n";
    int n, m, M, N, K;
    cin >> n >> m >> M >> N >> K;
    
    cout << "Enter teh sequence.\n";
    char* seq = new char[n];
    cin >> seq;

    OverlappingTemplateMatching(m, n, seq, M, N, K);

    return 0;
}
