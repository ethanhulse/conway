//Project Conway, by Ethan Hulse 2022
//Build Dependencies: Linux OS, SFML Graphics Library
//Todo 2023: Split some function initialization into a header file. Include build defs for windows executable target
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <experimental/random>
#include <utility>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::pair;

const int SIZE = 500; //Size of window square
const float CSIZE= 1.0f; //Zoom
const vector<pair<int,int>> COORDINATE_MAP = {{500,500},{502,502},{503,503},{504,504},{504,505},{504,506},{504,507}};
const char GENMODE = 'r';  //'r' for random, 'c' to read from COORDINATE_MAP, f to read from file MAPFILE;
const string MAPFILE = "src/test.txt"; //Bit map to read generation from


void mCopy(bool _m1[SIZE][SIZE],bool _m2[SIZE][SIZE]);

void mUpdate(bool _m1[SIZE][SIZE]);

void mDraw(sf::RenderTarget& t, bool _m1[SIZE][SIZE]);

void mRandGen(bool _m1[SIZE][SIZE]);

void mClear(bool _m1[SIZE][SIZE]);

void mCoordinateGen(bool _m1[SIZE][SIZE], vector<int[2][2]> _p);

void mGenerate(bool _m1[SIZE][SIZE]);

void mFile(bool _m1[SIZE][SIZE], string _filename);

int main()
{
    //Initial Map memory allocation
    bool m1[SIZE][SIZE];
    //SFML Window initialization
    sf::RenderWindow w(sf::VideoMode(SIZE, SIZE), "Project Conway", sf::Style::Close);
    w.setVerticalSyncEnabled(false);
    int n = 0;
    mGenerate(m1);
    //Key Polling
    while(w.isOpen())
    {
        sf::Event e;
        w.clear();
        mUpdate(m1);
        cout << "Frame: " << n << endl;
        ++n;
        mDraw(w,m1);
        w.display();
        //sf::sleep(sf::seconds(1.0f));
        while(w.pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::Closed:
                    w.close();
                    mClear(m1);
                    break;
                case sf::Event::KeyPressed:
                    switch(e.key.code)
                    {
                        case sf::Keyboard::Escape:
                            w.close();
                            mClear(m1);
                            break;
                        case sf::Keyboard::R:
                            w.clear();
                            mClear(m1);
                            mGenerate(m1);
                            n = 0;
                            break;
                    }
                    break;
            }
        }
    }
    return 0;
}
    

void mCopy(bool _m1[SIZE][SIZE],bool _m2[SIZE][SIZE])
{
    for(int x = 0; x < SIZE; x++)
    {
        for(int y = 0; y < SIZE; y++)
        {
            _m2[x][y] = _m1[x][y];
        }
    }
}

void mUpdate(bool _m1[SIZE][SIZE])
{
    bool _m2[SIZE][SIZE];
    mCopy(_m1, _m2);
    for(int a = 0; a < SIZE; a++)
    {
        for(int b = 0; b < SIZE; b++)
        {
            int alive = 0;
            for(int c = -1; c < 2; c++)
            {
                for(int d = -1; d < 2; d++)
                {
                    if(!(c == 0 && d == 0))
                    {
                        if(_m2[a+c][b+d])
                        {
                            ++alive;
                        }
                    }
                }
            }

            if(alive < 2)
            {
                _m1[a][b] = false;
            }
            else if(alive == 3)
            {
                _m1[a][b] = true;
            }
            else if(alive > 3)
            {
                _m1[a][b] = false;
            }
        }
    }
}

void mDraw(sf::RenderTarget& t, bool _m1[SIZE][SIZE])
{
    sf::Vector2f lw(CSIZE, CSIZE);
    for(int x = 0; x < SIZE; x++)
    {
        for(int y = 0; y < SIZE; y++)
        {
            sf::RectangleShape s(lw);
            switch(_m1[x][y])
            {
                case true:
                    s.setFillColor(sf::Color::White);
                    break;
                case false:
                    continue;
                    break;
            }
            sf::Vector2f xy((float)x * CSIZE, (float)y * CSIZE);
            s.setPosition(xy);
            t.draw(s);
        }
    }
}

void mRandGen(bool _m1[SIZE][SIZE])
{
    for(int a = 0; a < SIZE; a++)
    {
        for (int b = 0; b < SIZE; b++)
        {
            int _r = std::experimental::randint(0,1);
            bool r;
            switch(_r)
            {
                case 0:
                    r = false;
                    break;
                case 1:
                    r = true;
                    break;
            }

            _m1[a][b] = r;
        }
    }   
}

void mClear(bool _m1[SIZE][SIZE])
{
    for(int a = 0; a < SIZE; a++)
    {
        for(int b = 0; b < SIZE; b++)
        {
            _m1[a][b] = false;
        }
    }
}

void mCoordinateGen(bool _m1[SIZE][SIZE], vector<pair<int, int>> _p)
{
    int vecsize = _p.size();

    for(int i = 0; i < vecsize; i++)
    {
        int x = _p[i].first;
        int y = _p[i].second;
        _m1[x][y] = true;
    }
}

void mGenerate(bool _m1[SIZE][SIZE])
{
    switch(GENMODE)
    {
        case 'r':
            mRandGen(_m1);
            break;
        case 'c':
            mCoordinateGen(_m1, COORDINATE_MAP);
            break;
        case 'f':
            mFile(_m1, MAPFILE);
            break;
    }
}

void mFile(bool _m1[SIZE][SIZE], string _filename)
{
    ifstream in(_filename);
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if((bool)in != false && (bool)in != true)
            {
                _m1[i][j] = false;
            }
            else if((bool)in == true || (bool)in == false)
            {
                string aa;
                in >> aa;
                cout << aa << endl;
                //_m1[i][j] = (bool)std::stoi(aa);
                //(bool)in >> _m1[i][j];
            }

            //cout << _m1[i][j];
        }
    }

    in.close();
}