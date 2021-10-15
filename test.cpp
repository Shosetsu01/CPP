#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <intrin.h>


//

int const a=4, b=6;
int i, j, har[b], m[a][b], s=0;
using namespace std;
int main ()
{
    for (i=0; i<a; i++, cout<<endl)
        for (j=0; j<b; j++)
        {
            m[i][j]= ((i+j)&1) ? (__rdtsc()%515)*(-1)+1 : (-__rdtsc())%153;
            cout<< m[i][j] << "  ";
        }
 
    cout<<endl;
    for (i=0; i<b; i++)             // подсчет характеристик и вывод их на экран
    {
        for (j=0; j<a; j++)
            if (m[j][i]<0 && m[j][i]%2!=0)
                har[i]+=m[j][i];
        har[i]*=-1, cout<<har[i]<<" ";
    }
    cout<<"\n";
 
    int zz;
    for(int zzz = 0; zzz<a; zzz++)
        for(i = 0; i < b-1; ++i)
            if(har[i] >= har[i+1])
            {
                for(int k = 0; k < a; ++k)
                {
                    s=m[k][i];
                    m[k][i]=m[k][i+1];
                    m[k][i+1]=s;
                }
                zz= har[i];
                har[i] = har[i+1];
                har[i+1] = zz;
            }
 
    cout<<endl;
    for (i=0; i<a; i++)
    {  // вывод нового массива на экран
        for (j=0; j<b; j++)
            cout<< m[i][j] << "  ";
        cout << "\n";
    }
    system("pause");
    return 0;
}