
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <omp.h>
#include <fstream>

using namespace std;

#define Student 20

int main()
{
    srand(time(NULL));

    int Car = 2;
    int goodGOB = 0;
    // volatile bool flag = false;

    #pragma omp parallel num_threads(2) 
    {
        bool flag = false;
        #pragma omp for schedule (static, 1)
        for (int i = 0; i < Student; i++)
        {
            if (flag) continue;
            int crash = rand() % 12 + 1;

            if (crash == 1)
            {
                Car--;
                flag = true;
                if (Car == 0)
                {
                    cout << "ЕЩЕ АВАРИЯ! Ну приехали..." << endl;
                    
                } else {
                    cout << "АВАРИЯ! - Осталась одна машина" << endl;
                }
            } else {
                cout << i + 1 << " - сдал с первой попытки!" << endl; 
                goodGOB++;  
            }
        }
    }



    if (Car != 0)
    {
        cout << "Экзамен окончен! Все сдали!";
    }
    else
    {
        cout << "Кто учил водить этих....?" << endl;
        cout << "Ну хоть " << goodGOB << " человек смогли сдать.";
    }

    return 0;
}