// *Written by Aditya Kotwal*
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "userclass.h"
#include <bits/stdc++.h>
#include <fstream>
#include "accessories.h"
using namespace std;
#define clr system("clear")
void initFoodlist()
{
    ofstream MyFile("foodlist.txt");
    MyFile << "Food List:" << endl;
    MyFile.close();
    // name cal p c f weight
    fooditem f1("chips       ", 500, 6, 53, 34, 100);
    f1.writetofile("foodlist.txt");
    fooditem f2("chocolate   ", 500, 7, 58, 29, 100);
    f2.writetofile("foodlist.txt");
    fooditem f3("milk        ", 75, 3, 8, 4, 100);
    f3.writetofile("foodlist.txt");
    fooditem f4("ice-cream   ", 120, 4, 10, 5, 100);
    f4.writetofile("foodlist.txt");
    fooditem f5("tomato sauce", 20, 0.2, 5, 0.02, 15);
    f5.writetofile("foodlist.txt");
    fooditem f6("maggi       ", 427, 8, 63, 16, 100);
    f6.writetofile("foodlist.txt");
    fooditem f7("coke zero   ", 0, 0, 0, 0, 100);
    f7.writetofile("foodlist.txt");
}
void get_userData(string usrname, string filename)
{
    User u;
    u.InputLoginData(usrname);
    clr;
    u.InputPersonaldata();
    clr;
    u.write_tofile(filename);
}
bool signUp()
{
    clr;
    printspace(50);
    cout << bold_on << "Welcome To SignUp Page\n"
         << bold_off;
    string usrname;
    cout << "Enter Username:\n";
    cin >> usrname;
    if (if_file_exists(usrname + ".txt"))
    {
        return false;
    }
    get_userData(usrname, usrname + ".txt");
    return true;
}
string get_ith_Food(int index)
{
    ifstream myfile;
    myfile.open("foodlist.txt");
    string food;
    int i = 0;
    while (i <= index)
    {
        getline(myfile, food);
        i++;
    }
    myfile.close();
    return food;
}
int getLatestVal(string filename)
{
    ifstream myfile;
    myfile.open(filename);
    string preval, currentval;
    while (getline(myfile, currentval))
    {
        if (currentval != " ")
        {
            preval = currentval;
        }
    }
    myfile.close();
    if (preval == "")
    {
        return 0;
    }
    return stoi(preval);
}
void printFoodlog(string usrname)
{
    clr;
    printspace(40);
    int calories = getLatestVal(usrname + "cal_log.txt");
    cout << bold_on << "Calories Left for the day: " << calories << "(Kcal)" << bold_off << endl;
    ifstream myFile;
    myFile.open(usrname + "food_log.txt");
    string item;
    for (int lineno = 2; getline(myFile, item); lineno++)
    {
        cout << endl
             << lineno - 1 << ": " << item << endl;
    }
    press_i_togoBack(1);
}
void printMacros(string usrname)
{
    clr;
    int p = getLatestVal(usrname + "protein_log.txt");
    int c = getLatestVal(usrname + "carbs_log.txt");
    int f = getLatestVal(usrname + "fats_log.txt");
    cout << bold_on << "Protein: " << p << " grams" << endl;
    cout << "Carbs: " << c << "grams" << endl;
    cout << "Fats: " << f << "grams" << bold_off << endl;
    press_i_togoBack(1);
}
void Mydiary(string usrname)
{
    clr;
    // Getting Current Calories
    string ch;
    int count = 0;
    while (1)
    {
        clr;
        printspace(40);
        cout << bold_on << "My Diary" << bold_off << endl;
        cout << "1 Today's Macros\n";
        cout << "2 Food Log\n";
        cout << "3 Back to main menu\n";
        cin >> ch;
        if (ch == "1")
        {
            // print macros
            printMacros(usrname);
        }
        else if (ch == "2")
        {
            // print food log
            printFoodlog(usrname);
        }
        else if (ch == "3")
        {
            return;
        }
        else
        {
            count++;
            printError(count);
        }
    }
    // printing current Cal
}
int UpdateUserfiles(string usrname, float weight, string food, bool add)
{
    // fodd =Chips [Cal:100(Kcal)] [ P:10(gms) C:10(gms) F:10(gms) ] [weight:100].
    // getting numbers
    // Decoding STRING food
    vector<int> nums;
    string foodname;
    int s = 0;
    for (int i = 0; i < food.size(); i++)
    {
        if (food[i] == ' ' && s == 0)
        {
            foodname = food.substr(0, i);
        }
        if (food[i] == ':')
        {
            s = i;
        }
        if (food[i] == '(')
        {
            // cout << food.substr(s+1, i - s);
            int num = stoi(food.substr(s + 1, i - s));
            nums.push_back(num);
        }
    }
    // adjusting food by quantity
    if (add)
    {
        for (int i = 0; i <= 4; i++)
        {
            float ratio = (float)weight / nums[4];
            nums[i] = nums[i] * ratio;
            // cout << nums[i] << " ";
        }
        // create food itme object cuz it will write itself to file
        // updating user food log
        fooditem food1(foodname, nums[0], nums[1], nums[2], nums[3], nums[4]);
        food1.writetofile(usrname + "food_log.txt");
    }
    // updating pcf log
    int cal = getLatestVal(usrname + "cal_log.txt");
    int p = getLatestVal(usrname + "protein_log.txt");
    int c = getLatestVal(usrname + "carbs_log.txt");
    int f = getLatestVal(usrname + "fats_log.txt");
    // updating all other 3 files
    ofstream MyFile;
    MyFile.open(usrname + "cal_log.txt", ios_base::app);
    if (add)
    {
        MyFile << cal - nums[0] << endl;
    }
    else
    {
        MyFile << cal + nums[0] << endl;
    }
    MyFile.close();
    MyFile.open(usrname + "protein_log.txt", ios_base::app);
    if (add)
    {
        MyFile << p + nums[1] << endl;
    }
    else
    {
        MyFile << p - nums[1] << endl;
    }
    MyFile.close();
    MyFile.open(usrname + "carbs_log.txt", ios_base::app);
    if (add)
    {
        MyFile << c + nums[2] << endl;
    }
    else
    {
        MyFile << c - nums[2] << endl;
    }
    MyFile.close();
    MyFile.open(usrname + "fats_log.txt", ios_base::app);
    if (add)
    {
        MyFile << f + nums[3] << endl;
    }
    else
    {
        MyFile << f - nums[3] << endl;
    }
    MyFile.close();
    return nums[0];
}
bool showFoodList(string usrname, bool update, string filename)
{
    clr;
    // DISPLAYING FOOD LIST FROM foodlist.txt

    ifstream myfile;
    myfile.open(filename);
    string Food;
    int options = 0, lineno = 1;
    if (!update)
        lineno = 2;
    for (lineno; getline(myfile, Food); lineno++)
    {
        if (lineno == 1 && update)
        {
            cout << bold_on << "Food List: " << bold_off << endl;
        }
        else
        {

            cout << lineno - 1 << ": " << Food << endl;
            options++;
        }
    }
    if (options == 0)
    {
        return false;
    }
    myfile.close();
    // GETTING OPTIONS and QUANTITY FROM USER WHAT FOOD THEY WANT TO ADD

    if (update)
    {
        int choice = 0;
        cout << "\nEnter Food Number: ";
        cin >> choice;
        while (choice <= 0 || choice > options)
        {
            cout << "----Enter Food Number between 0 to " << options + 1 << "\n";
            cin >> choice;
        }
        float weight = 0;
        cout << "\nEnter Weight(gms):\n";
        cin >> weight;
        while (weight <= 0)
        {
            cout << "--Enter weight>0" << options + 1 << "\n";
            cin >> weight;
        }
        // RETRIEVING FOOD DETAILS
        string food = get_ith_Food(choice);
        //
        UpdateUserfiles(usrname, weight, food, true);
    }
    return true;
}
void addFood(string usrname)
{
    // for add food add new food to usernamefood_log and update calories in calories log
    showFoodList(usrname, true, "foodlist.txt");
}
void removeFood(string usrname)
{
    bool f = showFoodList(usrname, false, usrname + "food_log.txt");
    string food;
    int ch;
    cout << bold_on << "Enter food Number: " << bold_off;
    cin >> ch;
    while (ch <= 0)
    {
        cout << "-Enter value >0\n";
        cin >> ch;
    }
    if (f)
    {

        string line;
        ifstream fin;
        string filename = usrname + "food_log.txt";
        fin.open(usrname + "food_log.txt");
        ofstream temp;
        temp.open("temp.txt");
        int i = 1;
        while (getline(fin, line))
        {
            if (i != ch)
            {
                temp << line << endl;
            }
            else
            {
                food = line;
            }
            i++;
        }
        UpdateUserfiles(usrname, 0, food, false);
        temp.close();
        fin.close();
        const char *p = filename.c_str();
        remove(p);
        rename("temp.txt", p);
    }
    else
    {
        clr;
        cout << bold_on << "Please Eat Something so that You can remove Something." << bold_off << endl;
        sleep(3);
    }
}
void mainMenu(string usrname)
{
    string ch;
    int count = 0;
    while (1)
    {
        clr;
        printspace(45);
        cout << bold_on << "Home Screen" << bold_off << endl;
        cout << "1 My Diary\n";
        cout << "2 Add Food \n";
        cout << "3 Remove food\n";
        cout << "4 Log Out\n\n";
        cin >> ch;
        if (ch == "1")
        {
            Mydiary(usrname);
        }
        else if (ch == "2")
        {
            addFood(usrname);
        }
        else if (ch == "3")
        {
            removeFood(usrname);
        }
        else if (ch == "4")
        {
            return;
        }
        else
        {
            count++;
            printError(count);
        }
    }
}
void signInpage()
{
    clr;
    printspace(50);
    cout << bold_on << "Welcome To SignIn Page\n"
         << bold_off;
    string username;
    cout << "Enter Username:\n";
    cin >> username;
    clr;
    if (if_file_exists(username + ".txt"))
    {
        string ans;
        cout << "Enter Password:\n";
        cin >> ans;
        if (validateUser(username + ".txt", ans))
        {
            clr;
            cout << "Successfully Logged in.\n";
            sleep(1);
            progressbar("Loading " + username + "'s Account");
            mainMenu(username);
        }
        else
        {
            cout << "Incorrect password!\n----Lets Try that Again in\n";
            timer(3, 0);
            signInpage();
        }
    }
    else
    {
        cout << "Account with Username \"" << username << "\" Doesn't exists!!\n";
        sleep(2);
        return;
    }
}
int main()
{
    initFoodlist();
    string ch;
    int count = 0;
    while (1)
    {
        clr;
        printspace(40);
        cout << bold_on << "MyFitness Pal" << bold_off << endl;
        cout << bold_on << "(Press '1' for SignIn || '2' for SignUp || '3' for Exit)\n"
             << bold_off;
        cin >> ch;
        if (ch == "1")
        {
            signInpage();
            // break;
        }
        else if (ch == "2")
        {
            if (!signUp())
            {
                clr;
                printspace(42);
                cout << bold_on << "Seems like User Already Exists!!\n\n"
                     << bold_off;
                sleep(2);
                clr;
                cout << "Now Moving to Sign in page in\n";
                timer(3, 0);
            }
            else
            {
                clr;
                printspace(42);
                cout << bold_on << "User Successfully created Redirecting to Sign In Page in\n"
                     << bold_off;
                timer(3, 0);
            }
            clr;
            signInpage();
            break;
        }
        else if (ch == "3")
        {
            break;
        }
        else
        {

            printError(count);
            count++;
        }
    }
    clr;
    cout << "Thanks For Using our application( Whole code Written By " << bold_on << "Aditya Kotwal" << bold_off << ".)" << endl;
    sleep(4);
    return 0;
}
