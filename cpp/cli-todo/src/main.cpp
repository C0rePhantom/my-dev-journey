#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include "Task.h"

const std::string FILE_NAME = "data/tasks.json";

// -------------------- SAVE --------------------
void saveTasks(const std::vector<Task>& tasks)
{
    std::ofstream file(FILE_NAME);

    file << "{\n  \"tasks\": [\n";

    for (size_t i = 0; i < tasks.size(); i++)
    {
        const auto& t = tasks[i];

        file << "    {\n";
        file << "      \"id\": " << t.id << ",\n";
        file << "      \"done\": " << (t.done ? "true" : "false") << ",\n";
        file << "      \"text\": \"" << t.text << "\"\n";
        file << "    }";

        if (i + 1 != tasks.size())
            file << ",";

        file << "\n";
    }

    file << "  ]\n}";
}

// -------------------- LOAD --------------------
void loadTasks(std::vector<Task>& tasks, int& nextId)
{
    std::ifstream file(FILE_NAME);
    if (!file.is_open()) return;

    std::string line;
    Task temp;
    bool readingTask = false;

    while (std::getline(file, line))
    {
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        if (line.find("\"id\":") != std::string::npos)
        {
            temp.id = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("\"done\":") != std::string::npos)
        {
            temp.done = (line.find("true") != std::string::npos);
        }
        else if (line.find("\"text\":") != std::string::npos)
        {
            size_t start = line.find("\"", line.find(":")) + 1;
            size_t end = line.find_last_of("\"");
            temp.text = line.substr(start, end - start);

            tasks.push_back(temp);
            nextId = std::max(nextId, temp.id + 1);
        }
    }
}

// -------------------- OPERATIONS --------------------
void addTask(std::vector<Task>& tasks, int& nextId, const std::string& text)
{
    tasks.push_back({ nextId++, text, false });
    saveTasks(tasks);
}

void markDone(std::vector<Task>& tasks, int id)
{
    for (auto& t : tasks)
    {
        if (t.id == id)
        {
            t.done = true;
            break;
        }
    }
    saveTasks(tasks);
}

void deleteTask(std::vector<Task>& tasks, int id)
{
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
            [id](const Task& t) { return t.id == id; }),
        tasks.end()
    );

    saveTasks(tasks);
}

void editTask(std::vector<Task>& tasks, int id)
{
    for (auto& t : tasks)
    {
        if (t.id == id)
        {
            std::cout << "New text: ";
            std::getline(std::cin >> std::ws, t.text);
            break;
        }
    }
    saveTasks(tasks);
}

void showStats(const std::vector<Task>& tasks)
{
    int done = 0;

    for (const auto& t : tasks)
        if (t.done) done++;

    std::cout << "Total: " << tasks.size() << "\n";
    std::cout << "Done: " << done << "\n";
    std::cout << "Remaining: " << tasks.size() - done << "\n";
}

// -------------------- MAIN --------------------
int main()
{
    std::cout << "=========================\n";
    std::cout << "     CLI TODO APP\n";
    std::cout << "        v1.1\n";
    std::cout << "=========================\n\n";

    std::vector<Task> tasks;
    int nextId = 1;
    std::string command;
    std::string text;

    loadTasks(tasks, nextId);

    std::cout << "Type 'help' for commands\n\n";

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        std::transform(command.begin(), command.end(), command.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (command == "add")
        {
            std::cout << "Enter task: ";
            std::getline(std::cin >> std::ws, text);

            addTask(tasks, nextId, text);
            std::cout << "Task added!\n";
        }
        else if (command == "list")
        {
            std::sort(tasks.begin(), tasks.end(),
                [](const Task& a, const Task& b)
                {
                    return a.done < b.done;
                });

            for (const auto& t : tasks)
            {
                std::cout << "[" << t.id << "] "
                    << (t.done ? "(x) " : "() ")
                    << t.text << "\n";
            }
        }
        else if (command == "done")
        {
            int id;
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            markDone(tasks, id);
            std::cout << "Done!\n";
        }
        else if (command == "delete")
        {
            int id;
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            deleteTask(tasks, id);
            std::cout << "Deleted!\n";
        }
        else if (command == "edit")
        {
            int id;
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            editTask(tasks, id);
        }
        else if (command == "stats")
        {
            showStats(tasks);
        }
        else if (command == "help")
        {
            std::cout << "\nCommands:\n";
            std::cout << " add    - add task\n";
            std::cout << " list   - show tasks\n";
            std::cout << " done   - mark done\n";
            std::cout << " delete - delete task\n";
            std::cout << " edit   - edit task\n";
            std::cout << " stats  - show stats\n";
            std::cout << " exit   - quit\n\n";
        }
        else if (command == "exit")
        {
            saveTasks(tasks);
            std::cout << "Bye!\n";
            break;
        }
        else
        {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}