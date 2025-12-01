#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

template <typename T>
void logEvent(const T &message)
{
    ofstream fout("log.txt", ios::app);
    fout << message << endl;
    fout.close();
}

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

        try
        {
            if (!fin)
                throw runtime_error("User database not found!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            return false;
        }
        catch (...)
        {
            cout << "Unknown error while opening user database!" << endl;
            logEvent("Unknown login error");
            return false;
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
        try
        {
            if (!fin)
                throw runtime_error("C Programming file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
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
            try
            {
                try
                {
                    cout << "Enter Y when completed : ";
                    cin >> choice;

                    if (!cin)
                        throw invalid_argument("Invalid character input!");
                }
                catch (invalid_argument &e)
                {
                    cout << e.what() << endl;
                    logEvent(e.what());
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
            }
            catch (...)
            {
                cout << "Unexpected error occurred!" << endl;
                logEvent("Nested try failure");
            }

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
        try
        {
            if (!fin)
                throw runtime_error("Fitness file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
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

class CookingSkill : public Skill
{
public:
    CookingSkill()
    {
        skillName = "Cooking";
    }

    void showTasks(string username) override
    {
        ifstream fin("Cooking.txt");
        try
        {
            if (!fin)
                throw runtime_error("Cooking file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day Cooking Challenge ----------\n";
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

class DrawingSkill : public Skill
{
public:
    DrawingSkill()
    {
        skillName = "Drawing";
    }

    void showTasks(string username) override
    {
        ifstream fin("Drawing.txt");
        try
        {
            if (!fin)
                throw runtime_error("Drawing file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day Drawing Challenge ----------\n";
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

class GuitarSkill : public Skill
{
public:
    GuitarSkill()
    {
        skillName = "Guitar";
    }

    void showTasks(string username) override
    {
        ifstream fin("Guitar.txt");
        try
        {
            if (!fin)
                throw runtime_error("Guitar file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day Guitar Challenge ----------\n";
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

class JournalingSkill : public Skill
{
public:
    JournalingSkill()
    {
        skillName = "Journaling";
    }

    void showTasks(string username) override
    {
        ifstream fin("Journaling.txt");
        try
        {
            if (!fin)
                throw runtime_error("Journaling file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day Journaling Challenge ----------\n";
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

class SingingSkill : public Skill
{
public:
    SingingSkill()
    {
        skillName = "Singing";
    }

    void showTasks(string username) override
    {
        ifstream fin("Singing.txt");
        try
        {
            if (!fin)
                throw runtime_error("Singing file missing!");
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            return;
        }

        int day = getSavedProgress(username);
        string task;
        int currentDay = 1;
        char choice;

        cout << "\n---------- 30 Day Singing Challenge ----------\n";
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
        try
        {
            if (!(cin >> choice))
                throw invalid_argument("Non-numeric menu input!");
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << endl;
            logEvent(e.what());
            cin.clear();
            cin.ignore(1000, '\n');
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
                cout << "3. Cooking" << endl;
                cout << "4. Drawing" << endl;
                cout << "5. Guitar" << endl;
                cout << "6. Journaling" << endl;
                cout << "7. Singing" << endl;

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
                else if (sc == 3)
                {
                    s = new CookingSkill();
                }
                else if (sc == 4)
                {
                    s = new DrawingSkill();
                }
                else if (sc == 5)
                {
                    s = new GuitarSkill();
                }
                else if (sc == 6)
                {
                    s = new JournalingSkill();
                }
                else if (sc == 7)
                {
                    s = new SingingSkill();
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                    continue;
                }

                s->showTasks(u.getUsername());
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

    return 0;
}
