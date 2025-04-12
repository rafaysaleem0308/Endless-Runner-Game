#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <Windows.h>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>
#include<fstream>
const int KEY_READER = 224;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_RIGHT = 77;
const int KEY_LEFT = 75;
const unsigned int Space = 32;
const int Num_3 = 120;
void board(char zone[15][3]);
void give(char zone[15][3]);
int find(char zone[15][3]);
void makemoves(char zone[15][3], int& lives);
void obstacles(char zone[15][3]);
void collect_coin(char zone[15][3], int& coinsCollected);
void Save_Game(std::string a, int b);
int coins_collected = 0;
int score = 0;
int lives = 3;
using namespace std;
std::string playername = "";
int main()
{
    char zone[15][3];
    char a = '^'; // car symbol
    system("color F0");
    cout << "\t\t\t\t\t|--------------------------------|\n";
    cout << "\t\t\t\t\t  Welcome to Endless Runner Game!\n";
    cout << "\t\t\t\t\t|--------------------------------|\n\n";
    cout << "\n\n";
    cout << "\t\t\t\t\tEnter Playername: "; getline(cin, playername);
    char choice;
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\tENDLESS RUNNER" << endl;
    cout << "\t\t\t\t\t\t[1] Start Game: " << endl;
    cout << "\t\t\t\t\t\t[2] Exit Game: " << endl;

    choice = _getch();
    system("cls");
    if (choice == '1')
    {
        give(zone);
        obstacles(zone);
        while (true)
        {
            board(zone);
            makemoves(zone, lives);
			Sleep(100);
            system("cls");

        }
    }
    else if (choice == '2')
    {
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\tThank you for playing!" << endl;
        cout << "\t\t\t\t\t\tExiting Game..." << endl;
        Sleep(2000);
    }

    else
    {
        cout << "INVALID INPUT!!!" << endl;
        cout << "Exiting Game...";
        Sleep(2000);
    }
    system("pause");
}

void give(char zone[15][3])
{
    char a = '^';
    char c = 'O'; // coins symbol
    int n = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 14 && j == 1)
                zone[i][j] = a;
            else if (rand() % 10 == 0)
                zone[i][j] = c;
            else
                zone[i][j] = n;
        }
    }
}

int find(char zone[15][3])
{
    char a = '^';

    for (int j = 0; j < 45; j++)
    {
        if (zone[0][j] == a)
        {
            return j;
        }
    }
}

void board(char zone[15][3])
{
    char t = '2';
    char w = '1'; // obstacles symbol
    char c = 'O';
    int x = 0;
    char a = '^';

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "|";
            if (zone[i][j] == a)
            {
                cout << "   " << a << "   ";
            }
            else if (zone[i][j] == w)
            {
                cout << "   " << w << "   ";
            }
            else if (zone[i][j] == t)
            {
                cout << "   " << t << "   ";
            }
            else if (zone[i][j] == c)
            {
                cout << "   " << c << "   ";
            }
            else
            {
                cout << "       ";
            }
            if (j == 2)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "LIVES: " << lives << endl;
    cout << "SCORE: " << score << endl;
    cout << "COINS COLLECTED: " << coins_collected << endl;
    cout << "Press x to save game";
}

void collect_coin(char zone[15][3], int& coinsCollected)
{
    char a = '^';
    char c = 'O';
    int x = find(zone);
    bool coinCollected = false;

    for (int i = 0; i < 15; i++)
    {
        if (zone[i][x] == c)
        {
            zone[i][x] = ' '; // Remove the collected coin
            coinsCollected++;
            coinCollected = true;
        }
    }
    if (coinCollected)
    {
        // Generating new coins
        int coin_row = rand() % 15;
        int coin_col = rand() % 3;

        while (zone[coin_row][coin_col] != ' ')
        {
            coin_row = rand() % 15;
            coin_col = rand() % 3;
        }
        zone[coin_row][coin_col] = c;
    }
}

void makemoves(char zone[15][3], int& lives)
{
    static int delayCounter = 0; // Counter to introduce delay between automatic upward movements
    int x = 0;
    collect_coin(zone, coins_collected);
    x = find(zone);
    int c = 0;
    if (_kbhit())
    {
        c = _getch();
    }
    else
    {
        delayCounter++;
        if (delayCounter < 3)
        {
            return; // Skip automatic movement for a few iterations to introduce delay
        }
        else
        {
            delayCounter = 0;
        }
    }
    switch (int(c))
    {
    case KEY_UP:
        if (x > 2)
        {
            if (zone[0][x - 3] == '1') // Collision detection
            {
                swap(zone[0][x], zone[0][x - 3]);
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << endl;
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0

                }
            }
            else
                swap(zone[0][x], zone[0][x - 3]);
        }
        else
        {
            if (zone[0][x + 42] == '1') // Collision detection
            {
                swap(zone[0][x], zone[0][x + 42]);
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            else
                swap(zone[0][x], zone[0][x + 42]);
            give(zone);
            obstacles(zone);
        }
        score++;
        break;

    case KEY_DOWN:
        if (x < 42)
        {
            if (zone[0][x + 3] == '1') // Collision detection
            {
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            swap(zone[0][x], zone[0][x + 3]);
        }
        else
        {
            swap(zone[0][x], zone[0][x - 42]);
        }
        score++;
        break;

    case KEY_LEFT:
        if (x % 3 == 0)
        {
            if (zone[0][x + 2] == '1') // Collision detection
            {
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            swap(zone[0][x], zone[0][x + 2]);
        }
        else
        {
            swap(zone[0][x], zone[0][x - 1]);
        }
        score++;
        break;

    case KEY_RIGHT:
        if (x % 3 == 2)
        {
            if (zone[0][x - 2] == '1') // Collision detection
            {
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            swap(zone[0][x], zone[0][x - 2]);
        }
        else
        {
            swap(zone[0][x], zone[0][x + 1]);
        }
        score++;
        break;

    case Space:
        if (x < 6)
        {
            give(zone);
            obstacles(zone);
            if (zone[0][x + 6] == '1') // Collision detection
            {
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            swap(zone[0][x], zone[0][x + 6]);
        }
        else
        {
            if (zone[0][x - 6] == '1') // Collision detection
            {
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            swap(zone[0][x], zone[0][x - 6]);
        }
        score += 2;
        break;
    case Num_3:
        Save_Game(playername, score);
        exit(1);

    default:
        if (x > 2)
        {
            if (zone[0][x - 3] == '1') // Collision detection
            {
                swap(zone[0][x], zone[0][x - 3]);
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0

                }
            }
            else
                swap(zone[0][x], zone[0][x - 3]);
        }
        else
        {
            if (zone[0][x + 42] == '1') // Collision detection
            {
                swap(zone[0][x], zone[0][x + 42]);
                lives--; // Decrease lives on collision
                if (lives == 0)
                {
                    cout << "Game Over! Lives reached 0." << endl;
                    exit(0); // End the game if lives reach 0
                }
            }
            else
                swap(zone[0][x], zone[0][x + 42]);
            give(zone);
            obstacles(zone);
        }
        score++;
        break;
    }
}

void obstacles(char zone[15][3])
{
    char a = '^';
    char w = '1';

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (zone[i][j] == w)
            {
                zone[i][j] = ' ';
            }
        }
    }
    srand(time(0));
    int n = 0;
    int k = 0;
    for (int j = 0; j < 8; j++)
    {
        k = rand() % 15;
        n = rand() % 3;
        if (zone[k][n] == a)
        {
            continue;
        }
        else
            zone[k][n] = w;
    }
}

void Save_Game(string a, int b)
{
    ofstream writer;
    writer.open("EndlessGameScore.txt", ios_base::app);
    if (writer.is_open())
    {
        writer << a << '\t' << b << '\n';
        writer.close();
    }
    else
    {
        cout << "\nError! Can't open the file\n";
    }

}