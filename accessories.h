#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define clr system("clear")
std::ostream &bold_on(std::ostream &os)
{
    return os << "\e[1m";
}

std::ostream &bold_off(std::ostream &os)
{
    return os << "\e[0m";
}
void press_i_togoBack(int i)
{
    cout << "\n\n";
    cout << bold_on << "Press "<<i<<" to return to Home Screen...\n"
         << bold_off;
    string s;
    while (s != "1")
    {
        cin >> s;
    }
}
void progressbar(string msg1)
{
    int count = 10;
    for (int i = 0; i < 5; i++)
    {
        clr;
        printspace(50);
        cout << bold_on << msg1 << bold_off << "\n\n";
        cout << "[";
        for (int j = 0; j < count; j++)
        {
            cout << "=";
        }
        cout << ">";
        printspace(50 - count);
        cout << "] " << bold_on << count * 2 << " %" << bold_off << endl;
        sleep(1);
        count += 10;
    }
}

void timer(int t, int spaces)
{
    int time = t;
    cout.flush();
    while (time > 0)
    {
        printspace(spaces);
        cout << bold_on << time << bold_off << "\r";
        time--;
        cout.flush(); // To de-buffer the cout
        sleep(1.5);   // sleep for 1 second
    }
}
bool if_file_exists(const string filename)
{
    ifstream infile(filename);
    return infile.good();
}
bool validateUser(string filename, string ans)
{
    ifstream myfile;
    myfile.open(filename);
    string password;
    for (int lineno = 1; getline(myfile, password) && lineno < 3; lineno++)
    {
        if (lineno == 2)
        {
            if (ans == password)
            {
                return true;
            }
        }
    }
    return false;
}
void printError(int count)
{

    if (count <=1)
    {
        cout << "Wrong Input!!\n";
    }
    else if (count == 2)
    {
        cout << "Again wrong Input!!\n";
    }
    else 
    {

        cout << "You must be blind.\n";
    }
    cout << "Now Please Try Again in\n";
    timer(count+2, 0);
}
