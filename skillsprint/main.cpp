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

    // i kept these data members private because i wanted encapsulation
    // i access them only through member functions so i can control how they change

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
        // i made this constructor to initialize my user safely and keep the state consistent (encapsulation)
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
            // i added this to notice object lifetime, still the data stays hidden (encapsulation)
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
        // i expose only what i need via a getter (encapsulation)
        return username;
    }
};

int User::totalUsers = 0;

class Skill
{
protected:
    string skillName;

public:
    // i declared a pure virtual function here to make this class an abstraction
    // i use it so different skills can implement their own behavior (polymorphism)
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

    int getStreak(string username)
    {
        string filename = username + "_" + skillName + "_streak.txt";
        ifstream fin(filename);
        int streak = 0;
        if (fin)
        {
            fin >> streak;
        }
        fin.close();
        return streak;
    }

    void updateStreak(string username, bool completed)
    {
        string filename = username + "_" + skillName + "_streak.txt";
        int streak = getStreak(username);

        if (completed)
            streak++;
        else
            streak = 0;

        ofstream fout(filename);
        fout << streak;
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
        // i override the abstract method here to provide specific behavior (abstraction in the base, concrete in the derived)
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
                cout << "Progress saved. Come back tomorrow!" << endl;
                break;
            }
        }

        fin.close();
    }
};

class Leaderboard
{
public:
    void showLeaderboard()
    {
        ifstream fin("users.txt");
        if (!fin)
        {
            cout << "No users to display leaderboard!" << endl;
            return;
        }

        string u, p;
        struct Entry
        {
            string name;
            int totalStreak;
        };
        Entry leaderboard[100];
        int index = 0;

        while (fin >> u >> p)
        {
            int totalStreak = 0;
            string skills[7] = {"C_Programming", "Fitness", "Cooking", "Drawing", "Guitar", "Journaling", "Singing"};
            for (int i = 0; i < 7; i++)
            {
                string filename = u + "_" + skills[i] + "_streak.txt";
                ifstream sf(filename);
                int streak = 0;
                if (sf)
                    sf >> streak;
                totalStreak += streak;
                sf.close();
            }
            leaderboard[index++] = {u, totalStreak};
        }
        fin.close();

        for (int i = 0; i < index - 1; i++)
        {
            for (int j = 0; j < index - i - 1; j++)
            {
                if (leaderboard[j].totalStreak < leaderboard[j + 1].totalStreak)
                {
                    Entry temp = leaderboard[j];
                    leaderboard[j] = leaderboard[j + 1];
                    leaderboard[j + 1] = temp;
                }
            }
        }

        cout << "\n----- Leaderboard (Total Streaks) -----\n";
        for (int i = 0; i < index; i++)
        {
            cout << i + 1 << ". " << leaderboard[i].name << " - " << leaderboard[i].totalStreak << " days" << endl;
        }
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
        // i am using the same abstract interface and giving a fitness-specific implementation
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
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
        // i implement the abstract showTasks for cooking, still accessed via the base type
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
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
        // i implement drawing tasks through the same abstract method, showing substitution
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
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
        // i keep the interface identical so i can swap skills transparently (abstraction + liskov)
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
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
        // i provide journaling behavior under the same abstract contract
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
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
        // i use the abstract showTasks and customize for singing
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
                updateStreak(username, true);
            }
            else
            {
                updateStreak(username, false);
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
        cout << "3. Leaderboard" << endl;
        cout << "4. Exit" << endl;
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
                // i use a pointer to the abstract base (abstraction) and assign different concrete skills

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

                // i call the abstract function through the base pointer to show runtime polymorphism
                s->showTasks(u.getUsername());
                delete s;
            }
            break;

        case 2:
            u.signup();
            break;

        case 3:
            Leaderboard lb;
            lb.showLeaderboard();
            break;

        case 4:
            cout << "Thank you for using SkillSprint!";
            exit(0);

        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
