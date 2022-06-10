#include <iostream>
#include <cmath>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;


int* initIntArray(int length){
    int* v = new int[length];
    for(int i = 0; i<length; i++)
        v[i] = 0;
    
    return v;
}


double* initDoubleArray(int length){
    double* pi = new double[length];
    for(int i = 0; i<length; i++)
        pi[i] = 0;
    
    return pi;
}


double Chi_Square(int N, int* v, double* pi){
    double result = 0;
    for(int i = 0; i<5; i++){
        double base = v[i] - N*pi[i];
        result += pow(base, 2)/pi[i];
    }
    return result/N;
}


double factorial(int n)
{
    int result = 1;
    for(int i = 1; i <= n; i++)
    {
        result*=i;
    }
    return n;
}


double combinatory(int n, int k)
{
    if(k==0 || n == 0)
        return 1;
    return factorial(n)/(factorial(n-k)*factorial(k));
}


double combSum(int upper, int eta)
{
    double result = 0;
    for(int l = 1; l<upper; l++)
    {
        result+=combinatory(upper-1, l-1)*(pow(eta, l)/factorial(l));
    }
    return result;
}


double* calcPi(double eta, int K){
    double* pi = initDoubleArray(K+1);
    for(int i = 0; i<=K; i++)
    {
        pi[i] = eta*exp(-2*eta)/(1<<i)*combSum(i, eta);
    }
    return pi;
}

double igamc(double a, double x)
{
    double norm = x/5000;
    double upper, lower = 0;
    for(double i = norm; i<x; i+=norm)
    {
        upper += norm*exp(-1*(i+1))*pow(i+1, a-1);
        lower += norm*exp(-1*(i))*pow(i, a-1);
    }
    return 1-(abs(upper-lower));
}

double calcPvalue(int N, double chi){    //#TODO
    return igamc(N/2, chi/2);
}


int* calcMatches(int m, int n, char* seq, int M, int N, int K)
{
    int* v = initIntArray(K+1);
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
