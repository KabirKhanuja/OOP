# SkillSprint – Technical Report

## 1. Introduction

SkillSprint is a simple console-based C++ application that helps a user build habits and learn new skills via 30-day challenges. It is intentionally designed to demonstrate:

- Pre-OOP fundamentals (I/O, conditionals, loops, functions)
- Core OOP concepts (classes, encapsulation, inheritance, polymorphism)
- Basic file handling in C++
- Exception handling (custom exception types, `try`/`catch` blocks)
- A small use of templates (generics)
- Introductory SOLID principles (SRP, OCP, LSP, DIP)

The application allows a user to:

1. Sign up and log in using a simple file-based user database.
2. Choose a skill challenge (C Programming, Fitness, Cooking, Singing, Drawing).
3. Progress through a series of daily tasks, with progress saved and resumed across runs.

The goal is educational: keep the implementation readable and straightforward while naturally integrating modern C++ concepts.

---

## 2. High-Level Design

### 2.1 Main Components

The project centers around three main kinds of components:

- **User management** – handled by the `User` class (`users.txt` as a simple database).
- **Skills and challenges** – handled by the `Skill` base class and its derived classes.
- **Application control flow** – handled in `main()` and a few small helper functions.

### 2.2 Class Overview

- `User`
  - Manages user data (`username`, `password`) and total user count.
  - Handles `login()` and `signup()` workflows with file-based storage.

- `Skill` (abstract base class)
  - Holds the `skillName` for a skill.
  - Declares a pure virtual method `showTasks(string username)`.
  - Provides common progress logic via `getSavedProgress()` and `saveProgress()`.

- Derived skills:
  - `TechSkill` – C Programming challenge (`C_Programming.txt`).
  - `FitnessSkill` – Fitness challenge (`Fitness.txt`).
  - `CookingSkill` – Cooking challenge (`Cooking.txt`).
  - `SingingSkill` – Singing challenge (`Singing.txt`).
  - `DrawingSkill` – Drawing challenge (`Drawing.txt`).

- Exception utility classes:
  - `FileException` – represents file-related errors.
  - `InputException` – represents invalid or malformed user input.

- Small utility/template functions:
  - `template <typename T> T clampValue(const T &value, const T &minValue, const T &maxValue)` – generic function to clamp a value into a range.
  - `printMainMenu()` – prints the main menu.
  - `showAbout()` – prints a short "About" section at runtime.
  - `chooseSkill()` – lets the user select a skill and returns a `Skill*`.
  - `resetSkillProgress(const string &username)` – resets saved progress to Day 1 for a chosen skill.

---

## 3. User Flow

### 3.1 Start-Up

1. Program starts and calls `User::userCount()` to initialize the total user count from `users.txt`.
2. The program then enters an infinite loop, showing the main menu via `printMainMenu()`.

Main menu options:

1. **Login**
2. **Signup**
3. **About / Help**
4. **Exit**

### 3.2 Signup

- When the user chooses **Signup**:
  - `User::signup()` is called.
  - It opens `users.txt` in append mode.
  - Asks for a username and checks if it already exists using the private method `usernameExists()`.
  - If the username is unique, it prompts for a password and writes `username password` into `users.txt`.
  - Increments the static `totalUsers` counter.

### 3.3 Login

- When the user chooses **Login**:
  - `User::login()` opens `users.txt`.
  - If opening the file fails, it throws `FileException`.
  - Prompts for username and password.
  - Scans the file line by line; if a matching pair is found, login succeeds.
  - On success, the user is shown the available skills.

### 3.4 Skill Selection and Task Flow

After a successful login:

1. `chooseSkill()` displays the list of skills:
   - C Programming
   - Fitness
   - Cooking
   - Singing
   - Drawing
2. The user selects a skill by entering a number.
3. `chooseSkill()` validates the input, throwing `InputException` if the value is invalid.
4. A concrete `Skill` object is constructed (`TechSkill`, `FitnessSkill`, etc.) and returned as a `Skill*`.
5. `s->showTasks(u.getUsername())` is called inside a `try` block.

Inside each `showTasks` method:

- The corresponding skill file (e.g., `C_Programming.txt`) is opened.
- The current day is determined using `getSavedProgress(username)`.
- The user is shown tasks one by one starting from the current day.
- After each task, the user is prompted to enter `Y` when completed:
  - On `Y`/`y`: `currentDay` is incremented and progress is saved via `saveProgress()`.
  - On any other input: a message is printed and the loop breaks, saving current progress.

### 3.5 Resetting Progress (Helper Feature)

The function `resetSkillProgress(const string &username)` allows resetting progress:

- It shows a list of all skills.
- The user selects which skill's progress to reset.
- The corresponding `<username>_<Skill>.txt` file is overwritten with `1` (Day 1).
- This demonstrates targeted file writing and reuse of the same naming convention as in `Skill`.

(You can wire this into an additional submenu after login if desired.)

---

## 4. File Handling Design

### 4.1 User Database – `users.txt`

- Each line: `username password`
- Used by `User::signup()` and `User::login()`.
- `User::userCount()` counts lines to determine total users.

### 4.2 Skill Task Files

Located in the project folder:

- `C_Programming.txt`
- `Fitness.txt`
- `Cooking.txt`
- `Singing.txt`
- `Drawing.txt`

Each file contains 30 lines (Day 1 to Day 30), each describing a daily task. The `showTasks` functions read these line by line using `std::getline`.

### 4.3 Progress Files

For each `(username, skill)` pair, progress is stored in a separate file:

- File name format: `username_skillName.txt`
  - Example: `kabir_C_Programming.txt`, `kabir_Fitness.txt`, `kabir_Cooking.txt`, etc.
- Content: a single integer representing the next day to start from.
- `Skill::getSavedProgress()` reads this integer and defaults to `1` if the file does not exist.
- `Skill::saveProgress()` writes the new day back to the same file.

This approach keeps the implementation simple while cleanly separating progress for each user and skill.

---

## 5. Exception Handling

The project uses basic exception handling to handle non-trivial error conditions.

### 5.1 Custom Exceptions

- `FileException : public std::runtime_error`
  - Thrown when file operations fail (e.g., `users.txt` not found, progress file cannot be written).

- `InputException : public std::runtime_error`
  - Thrown when user input is invalid or out of an expected range (e.g., wrong menu choice when selecting a skill).

Both exceptions carry a message string and can be caught as `std::exception` thanks to inheritance from `std::runtime_error`.

### 5.2 Try/Catch Usage

At the top level, `main()` wraps the main loop in a `try` block:

- Catches `std::exception &` to handle all standard and custom exceptions.
- Prints a user-friendly message if an unexpected error occurs.

Nested `try/catch` is used when showing tasks for a selected skill:

- The call to `chooseSkill()` and `s->showTasks(...)` is wrapped in another `try` block.
- Catches:
  - `FileException` for skill file errors.
  - `InputException` for invalid skill choice.

This structure demonstrates:

- Uncaught vs. caught exceptions at different layers.
- Multiple `catch` clauses for different exception types.
- Clean separation between error detection (in `User`, `Skill`, helpers) and error reporting (in `main`).

---

## 6. Templates (Generics)

The project uses one simple, clear template function:

```cpp
template <typename T>
T clampValue(const T &value, const T &minValue, const T &maxValue)
{
    if (value < minValue)
        return minValue;
    if (value > maxValue)
        return maxValue;
    return value;
}
```

Usage:

- In `Skill::getSavedProgress`, the day read from the progress file is clamped between 1 and 30 using `clampValue`.
- This ensures that even if the file content is out of bounds, the program will still behave sensibly.
- Demonstrates a simple, realistic use of generics without overcomplicating the code.

---

## 7. SOLID Principles (Light Introduction)

The design hints at several SOLID principles in a gentle, beginner-friendly way.

### 7.1 Single Responsibility Principle (SRP)

- `User` focuses on user-related data and authentication operations.
- `Skill` and its derived classes focus on skill-specific task display and progress management.
- Helper functions such as `printMainMenu()`, `showAbout()`, and `chooseSkill()` keep UI/menu logic out of the core classes.

### 7.2 Open/Closed Principle (OCP)

- The `Skill` base class is open for extension via new derived classes.
- Adding `CookingSkill`, `SingingSkill`, or `DrawingSkill` did not require modifying the `Skill` class itself.
- Only minimal modifications in `chooseSkill()` were needed to support new skills in the menu.

### 7.3 Liskov Substitution Principle (LSP)

- `Skill* s = new TechSkill();` or `new FitnessSkill()`, `new CookingSkill()`, etc., are all used interchangeably via the `Skill` interface.
- `main()` never needs to know the exact derived type; it just calls `s->showTasks(...)`.
- Any new skill class that correctly implements `showTasks` can be slotted in without breaking existing logic.

### 7.4 Interface Segregation Principle (ISP)

- `Skill` acts as a very small interface: it only requires `showTasks` and uses common progress helpers.
- Clients (like `main`) depend only on what they actually need: `showTasks`.

### 7.5 Dependency Inversion Principle (DIP)

- `main()` and `chooseSkill()` rely on the abstraction `Skill` instead of concrete types, except where instances are created.
- The core logic operates on `Skill*` rather than specific classes like `TechSkill` or `FitnessSkill`.

These are intentionally simple and light touches; the goal is to recognize the patterns in an approachable codebase rather than implement every SOLID principle in a fully industrial way.

---

## 8. Building and Running

### 8.1 Requirements

- A C++17-compatible compiler (e.g., `g++`, `clang++`).
- The project files, including:
  - `main.cpp`
  - `users.txt` (optional at first; will be created/used by the program)
  - Skill task files: `C_Programming.txt`, `Fitness.txt`, `Cooking.txt`, `Singing.txt`, `Drawing.txt`

### 8.2 Build Command (macOS / Linux)

From the `project` folder:

```bash
cd /Users/kabirkhanuja/My_drive/CS/OOP/project

g++ -std=c++17 main.cpp -o skillsprint
./skillsprint
```

On Windows (using g++ from MinGW or similar):

```bash
g++ -std=c++17 main.cpp -o skillsprint.exe
skillsprint.exe
```

---

## 9. Possible Extensions

The current design is intentionally minimal but can be extended in several directions:

- Add a logged-in submenu to:
  - View progress across all skills.
  - Reset progress for a specific skill (using `resetSkillProgress`).
- Add new skills simply by:
  - Creating a new `*Skill` class derived from `Skill`.
  - Adding a corresponding `.txt` file with 30 tasks.
  - Registering the new skill in `chooseSkill()`.
- Improve security slightly by hashing passwords instead of storing them in plain text.
- Persist additional user data (e.g., last login time, number of completed challenges).

These changes can all be made while keeping the core structure and educational purpose of the project intact.

---

## 10. Conclusion

SkillSprint is a compact yet concept-rich C++ project that:

- Combines basic console I/O, file handling, and control flow.
- Demonstrates object-oriented concepts via `User` and `Skill` hierarchies.
- Introduces exception handling and simple templates in a practical way.
- Lightly illustrates key SOLID ideas.

This makes it a strong stepping stone from pre-OOP fundamentals into more advanced C++ and object-oriented design topics.
