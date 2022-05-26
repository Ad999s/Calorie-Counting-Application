#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define clr system("clear")
void printspace(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " ";
    }
}
void initFile(string filename, int val)
{
    ofstream MyFile(filename);
    if (val != -1)
        MyFile << val << endl;
    MyFile.close();
}
float hndlerror(float data, string name, string units)
{
    if (units != "-")
    {
        cout << name << "(" << units << ")"
             << ": ";
    }
    else
    {
        cout << name << ": ";
    }
    while (data <= 0)
    {
        cin >> data;
        if (data <= 0)
        {
            cout << name << " cant be <=0!!\n";
        }
    }
    return data;
}
class User
{
    string usrname, password, fname, surname;
    char gender;
    int age = 0;
    float weight = 0, height = 0;

public:
    void InputLoginData(string Username)
    {
        string filename = Username + ".txt";
        // getting values
        usrname = Username;
        string pass2;
        cout << "Let's Setup Password for Your account:\n";
        cin >> password;
        while (password.size() < 8)
        {
            cout << "Password length can't be less than 8!\n";
            cin >> password;
        }
        ofstream MyFile(filename);
        MyFile << usrname << endl;
        MyFile << password << endl;
        MyFile.close();
    }
    void InputPersonaldata()
    {
        printspace(42);
        cout << "Enter personal details Below\n"
             << endl;
        cout << "First name: \n";
        cin >> fname;
        cout << "Surname: \n";
        cin >> surname;
        cout << "'M'for male and 'F' for female: \n";
        cin >> gender;
        while (gender != 'M' && gender != 'm' && gender != 'f' && gender != 'F')
        {
            cout << "That wont work lets try that again!!\n";
            cin >> gender;
        }
        age = hndlerror(age, "Age", "yrs");
        weight = hndlerror(weight, "Weight", "kgs");
        height = hndlerror(height, "Height", "cms");
    }
    int getcal()
    {
        float bmr;
        if (gender == 'M' || gender == 'm')
        {
            bmr = 66.47 + (13.75 * weight) + (5.003 * height) - (6.755 * age);
        }
        else
        {
            bmr = 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age);
        }
        float amr = bmr;
        int activityLevel = 0;
        cout << "1 for Sedentary (little or no exercise)\n";
        cout << "2 for Lightly active (exercise 1-3 days/week)\n";
        cout << "3 for Moderately active (exercise 3-5 days/week)\n";
        cout << "4 for Active (exercise 6-7 days/week)\n";
        cout << "5 for Very active (hard exercise 6-7 days/week)\n";
        cin >> activityLevel;
        while (activityLevel < 1 || activityLevel > 5)
        {
            cout << "Please enter values between from 1 to 5!\n";
            cin >> activityLevel;
        }
        switch (activityLevel)
        {
        case 1:
            amr *= 1.2;
            break;
        case 2:
            amr *= 1.375;
            break;
        case 3:
            amr *= 1.55;
            break;
        case 4:
            amr *= 1.725;
            break;
        case 5:
            amr *= 1.9;
            break;
        default:
            break;
        }
        return amr;
    }
    void write_tofile(string filename)
    {
        ofstream MyFile;
        MyFile.open(filename, ios_base::app); // append instead of overwrite
        int maintCal = getcal();
        initFile(usrname + "food_log.txt", -1);
        initFile(usrname + "cal_log.txt", maintCal);
        initFile(usrname + "protein_log.txt", 0);
        initFile(usrname + "carbs_log.txt", 0);
        initFile(usrname + "fats_log.txt", 0);
        MyFile << "User Details :" << endl;
        MyFile << "                         First Name : " << fname << endl;
        MyFile << "                         Last  Name : " << surname << endl;
        MyFile << "                             Gender : " << gender << endl;
        MyFile << "                                Age : " << age << endl;
        MyFile << "                        Weight(kgs) : " << weight << endl;
        MyFile << "                        Height(cms) : " << height << endl;
        MyFile << "         Maintenance Calories(kcal) : " << maintCal << endl;
        MyFile.close();
    }
};
class fooditem
{
    string name;
    int netCalories;
    int protein, carbs, fats, weight;

public:
    fooditem(string n, int a, int b, int c, int d, int e)
    {
        name = n;
        netCalories = a;
        protein = b;
        carbs = c;
        fats = d;
        weight = e;
    }
    void writetofile(string filename)
    {
        ofstream MyFile;
        MyFile.open(filename, ios_base::app);
        MyFile << name << " [Cal:" << netCalories << "(Kcal)] [ P:" << protein << "(gms) C:" << carbs << "(gms) F:" << fats << "(gms) ] "
               << "[weight:" << weight << "(gms)]. " << endl;
        MyFile.close();
    }
};
