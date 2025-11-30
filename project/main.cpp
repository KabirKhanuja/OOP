#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

using namespace std;

class FileException : public std::runtime_error
{
public:
    explicit FileException(const std::string &msg) : std::runtime_error(msg) {}
};

class User
{
private:
    string username;
    string password;
    static int totalUsers;

    bool usernameExists(string &u)
    {
        ifstream fin("users.txt");
        string fu, fp;

        while (fin >> fu >> fp)
        {
            if (fu == u)
            {
                fin.close();
                return true;
            }
        }

        fin.close();
        return false;
    }

public:
    User()
    {
        username = "";
        password = "";
    }

    User(string &username, string &password)
    {
        this->username = username;
        this->password = password;
    }

    ~User()
    {
        if (!username.empty())
        {
            cout << "Destructor called for User : " << username << endl;
        }
    }

    static void userCount()
    {
        ifstream fin("users.txt");
        string u, p;
        int count = 0;

        while (fin >> u >> p)
        {
            count++;
        }

        fin.close();
        totalUsers = count;
    }

    static int getTotalUsers()
    {
        return totalUsers;
    }

    bool login()
    {
        ifstream fin("users.txt");

        if (!fin)
        {
            throw FileException("User database not found!");
        }

        bool found = false;
        string u;
        string p;

        cout << "\n---------- Login ----------\n";
        cout << "Enter username : ";
        cin >> username;
        cout << "Enter password : ";
        cin >> password;

        while (fin >> u >> p)
        {
            if (u == username && p == password)
            {
                found = true;
                break;
            }
        }

        fin.close();

        if (found)
        {
            cout << "User login successful! \nWelcome to SkillSprint." << endl;
            return true;
        }
        else
        {
            cout << "User not found! \nTry entering the username and password again. \nOR \nPlease signup.";
            return false;
        }
    }

    void signup()
    {
        ofstream fout("users.txt", ios::app);
        if (!fout)
        {
            throw FileException("Unable to open user database for writing!");
        }
        cout << "\n---------- Signup ----------\n";
        cout << "Enter username : ";
        cin >> username;

        if (usernameExists(username))
        {
            cout << "Username already exists! \nChoose a different username \nOR \nLogin";
            return;
        }

        cout << "Enter password : ";
        cin >> password;

        fout << username << " " << password << endl;
        fout.close();

        totalUsers++;

        cout << "User signup successful! \nProceed to login." << endl;
        cout << "Total registered users : " << getTotalUsers() << endl;
    }

    string getUsername()
    {
        return username;
    }
};

int User::totalUsers = 0;

class Skill
{
protected:
    string skillName;

public:
    virtual void showTasks(string username) = 0;

    int getSavedProgress(string username)
    {
        string filename = username + "_" + skillName + ".txt";
        ifstream fin(filename);

        int day = 1;
        if (fin)
        {
            fin >> day;
        }
        fin.close();
        return day;
    }

    void saveProgress(string username, int day)
    {
        string filename = username + "_" + skillName + ".txt";
        ofstream fout(filename);
        fout << day;
        fout.close();
    }
};

class TechSkill : public Skill
{
public:
    TechSkill()
    {
        skillName = "C_Programming";
    }

    void showTasks(string username) override
    {
        ifstream fin("C_Programming.txt");
        if (!fin)
        {
            cout << "C Programming skill not found!" << endl;
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day C Programming Challenge ----------\n";
        cout << "\nResuming from Day " << day << endl;

        while (getline(fin, task))
        {

            if (currentDay < day)
            {
                currentDay++;
                continue;
            }

            cout << "\n"
                 << task << endl;
            cout << "Enter Y when completed : ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                currentDay++;
                saveProgress(username, currentDay);
            }
            else
            {
                cout << "Progress saved. Come back tomorrow!" << endl;
                break;
            }
        }

        fin.close();
    }
};

class FitnessSkill : public Skill
{
public:
    FitnessSkill()
    {
        skillName = "Fitness";
    }

    void showTasks(string username) override
    {
        ifstream fin("Fitness.txt");
        if (!fin)
        {
            cout << "Fitness skill not found!\n";
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day Fitness Challenge ----------\n";
        cout << "\nResuming from Day " << day << endl;

        while (getline(fin, task))
        {
            if (currentDay < day)
            {
                currentDay++;
                continue;
            }

            cout << "\n"
                 << task << endl;
            cout << "Enter Y when completed : ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                currentDay++;
                saveProgress(username, currentDay);
            }
            else
            {
                cout << "Progress saved. Come back tomorrow!" << endl;
                break;
            }
        }

        fin.close();
    }
};


int main()
{
    try
    {
        User::userCount();
        User u;
        int choice;

        while (1)
        {
            cout << "\n---------- SkillSprint ----------\n";
            cout << "1. Login" << endl;
            cout << "2. Signup" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice number : ";
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid input! Try again." << endl;
                continue;
            }

            switch (choice)
            {
            case 1:
                if (u.login())
                {
                    cout << "\nAvailable Skills : \n";
                    cout << "1. C Programming" << endl;
                    cout << "2. Fitness" << endl;

                    cout << "Select a skill : ";
                    int sc;
                    cin >> sc;

                    Skill *s = NULL;

                    if (sc == 1)
                    {
                        s = new TechSkill();
                    }
                    else if (sc == 2)
                    {
                        s = new FitnessSkill();
                    }
                    else
                    {
                        cout << "Invalid choice!" << endl;
                        continue;
                    }

                    try
                    {
                        s->showTasks(u.getUsername());
                    }
                    catch (const FileException& fe)
                    {
                        cout << "Skill error: " << fe.what() << endl;
                    }

                    delete s;
                }
                break;

            case 2:
                u.signup();
                break;

            case 3:
                cout << "Thank you for using SkillSprint!";
                exit(0);

            default:
                cout << "Invalid choice! Try again." << endl;
            }
        }
    }
    catch (const std::exception& e)
    {
        cout << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}
