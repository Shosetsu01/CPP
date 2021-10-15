#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <omp.h>

using namespace std;

double **u, **f, **u0;
int N, IterCnt = 0;
double eps, h;

double F(double x, double y) {
    return 0;
}

double G(double x, double y) {
    if (x==0) return 1-2*y;
    if (x==1) return -1+2*y;
    if (y==0) return 1-2*x;
    if (y==1) return -1+2*x;
    return 0;
}

void UOutput() {
    cout << fixed << setprecision(3);
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++)
        cout << setw(7) << u[i*(N+1)/10][j*(N+1)/10];
        cout << endl;
    }
}

void UOutput1() {
    cout << fixed << setprecision(5);
    // for (int i = 0; i < 11; i++) {
    //     for (int j = 0; j < 10; j++)
    //         cout << setw(8) << abs(u[i*(N+1)/10][j*(N+1)/10]-u0[i*(N+1)/10][j*(N+1)/10]);
    // }
    double d = 0;
    for (int i = 1; i < N+1; i++)
        for (int j = 1; j < N+1; j++)
            d += abs(u[i][j]-u0[i][j]);
            cout << endl << "d=" << d << endl;
}

void Init() {
    N = 99;
    eps = 0.0001;
    h = 1.0/(N+1);
    f = new double*[N];

    for (int i = 0; i < N; i++) {
        f[i] = new double[N];
        for (int j = 0; j < N; j++)
            f[i][j] = F((i+1)*h, (j+1)*h);
    }
    u = new double*[N+2];

    for (int i = 1; i < N+1; i++) {
        u[i] = new double[N+2];
        for (int j = 1; j < N+1; j++)
            u[i][j] = 0;
            u[i][0] = G(i*h, 0);
            u[i][N+1] = G(i*h, (N+1)*h);
    }
    u[0] = new double[N+2];
    u[N+1] = new double[N+2];

    for (int j = 0; j < N+2; j++) {
        u[0][j] = G(0,j*h);
        u[N+1][j] = G((N+1)*h,j*h);
    }
    UOutput();
}

void Calc() {
    double max;
    IterCnt = 0;
    do {
        IterCnt++;
        max = 0;
        for (int i = 1; i < N+1; i++)
            for (int j = 1; j < N+1; j++) {
                double u0 = u[i][j];
                u[i][j] = 0.25*(u[i-1][j] + u[i+1][j] + u[i][j-1] + u[i][j+1] - h*h*f[i-1][j-1]);
                double d = abs(u[i][j]-u0);
                if (d > max)
                    max = d;
            }
    }
    while (max > eps);
}

void OMPCalc() {
    double max;
    IterCnt = 0;
    do {
        IterCnt++;
        max = 0;
        #pragma omp parallel for shared(u,N,max) num_threads(4) schedule(static,1)
        for (int i = 1; i < N+1; i++) {
            double max0 = 0;
            for (int j = 1; j < N+1; j++) {
                double u0 = u[i][j];
                u[i][j] = 0.25*(u[i-1][j] + u[i+1][j]
                + u[i][j-1] + u[i][j+1] - h*h*f[i-1][j-1]);
                double d = abs(u[i][j]-u0);
                if (d > max0)
                    max0 = d;
            }
            if (max0 > max)
                #pragma omp critical
                if (max0 > max)
                    max = max0;
        }
    }
    while (max > eps);
}

int main(int argc, char **argv) {
    Init();
    double tt= omp_get_wtime();
    Calc();
    tt = omp_get_wtime() - tt;
    cout << "Time = " << tt << " IterCnt = " << IterCnt << endl;
    u0 = u;
    Init();
    double tt1= omp_get_wtime();
    OMPCalc();
    tt1 = omp_get_wtime() - tt1;
    cout << "Time = " << tt1 << " IterCnt = " << IterCnt << endl;
    cout << tt/tt1 << endl;
    UOutput1();
    cin.get();

    return 0;
}