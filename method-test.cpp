
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int function(int a, int x, int p) {
	int i(0);
	int *x2 = new int[30];
    while(x >= 1)
    {
        x2[i] = x%2;
        x /= 2;
		i++;
	}
	//cout << i << endl;
	int n = i;
	//cout << n << endl;

	int *arr = new int[n];
	while( a < 0) 
	{
		a+=p;
	}
    arr[0] = a;
    //cout << arr[0] << endl;
    for(int i = 1; i < n; i++ ) {
        arr[i] = (arr[i-1]* arr[i-1])%p;
        //cout << arr[i] << endl;
    }
    //cout << arr[2] << endl;
    //int j = n;
    //cout << "sdsad" << x2[6] << endl;
    long long unsigned int proizv = 1;
    for(int j = 0; j < n; j++) {
        if (x2[j] > 0){
            proizv*= x2[j]* arr[j];
            //cout << proizv << endl;
		}
	}
	int ostatok = proizv%p;
	return ostatok;
}
bool prostoe(int a)
{
	bool pr = true;
	for (int i=2; i < a; i++)
	{
		if (a%i==0)
		{
			pr=false;
		}
	}
return pr;
}
int evklid(int a, int b) 
{
	int q = 0;
	int U[3] = { a, 1, 0};
	int V[3] = { b, 0, 1};
	int T[3];

	while(V[0] != 0 ) 
	{
		q = U[0]/V[0];
		T[0] = U[0]%V[0];
		T[1] = U[1]-q*V[1];
		T[2] = U[2]-q*V[2];
		for(int i = 0; i < 3; i++ ) {
			U[i] = V[i];
			V[i] = T[i];
		}
	}
	return U[0];
}
int evklid3(int a, int b) 
{
	int q = 0;
	int U[3] = { a, 1, 0};
	int V[3] = { b, 0, 1};
	int T[3];

	while(V[0] != 0 ) 
	{
		q = U[0]/V[0];
		T[0] = U[0]%V[0];
		T[1] = U[1]-q*V[1];
		T[2] = U[2]-q*V[2];
		for(int i = 0; i < 3; i++ ) {
			U[i] = V[i];
			V[i] = T[i];
		}
	}
	return U[2];
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int m = 10;//исходное сообщение
	int p = 23; //так выбрали
	int Ca, Cb;
	int count;
	//генерируем Ca и Cb, чтобы они были взаимо простыми с p-1
	for(int i = 2; i < p; i++ )
	{
		if(evklid(p-1, i) == 1 )
		{
			Ca = i;
			count = i;
			break;
		}
	}
	for(int i = count+1; i < p; i++ )
	{
		if(evklid(p-1, i) == 1 )
		{
			Cb = i;
			break;
		}
	}
	//int Ca = 7;
	//int Cb = 5;
	cout << "»сходное сообщение m = " << m << endl;
	cout << "—генерированы Ca = " << Ca << " Cb = " << Cb << endl;
	int da, db;
	da = function(evklid3(p-1, Ca), 1, p-1);
	db = function(evklid3(p-1, Cb), 1, p-1);
	cout << "da = " << da << endl;
	cout << "db = " << db << endl;
	int x1 = function(m, Ca, p);
	int x2 = function(x1, Cb, p);
	int x3 = function(x2, da, p);
	int x4 = function(x3, db, p);
	cout <<"ѕолученное сообщение x4 = " << x4 << endl;
	
		
	_getch(); // 
	return 0;
}