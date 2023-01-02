//Test program to get filestream reading working


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

const int SIZ = 5;

using namespace std;

bool MAP[50][50];



int main()
{
        string filename = "src/test.txt";

        ifstream in(filename);
        for(int i = 0; i < 50; i++)
        {
            if(i != 0)
            {
                cout << endl;
            }
            for(int j = 0; j < 50; j++)
            {
                    (bool)in >> MAP[i][j];
                    cout << MAP[i][j];
            }
        }

        in.close();


    /*for(int a = 0; a < SIZ; a++)
    {
        for(int b = 0; b < SIZ; b++)
        {
            cout << grid[a][b] << endl;
        }
    }
    */
    return 0;
}
