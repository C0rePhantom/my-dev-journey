#include "TaskManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

const std::string FILE_NAME = "tasks.json";

TaskManager::TaskManager()
{
    loadTasks();
}

void TaskManager::saveTasks() const
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

void TaskManager::loadTasks()
{
    std::ifstream file(FILE_NAME);
    if (!file.is_open()) return;

    std::string line;
    Task temp;

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

void TaskManager::addTask(const std::string& text)
{
    tasks.push_back({ nextId++, text, false });
    saveTasks();
}

void TaskManager::markDone(int id)
{
    for (auto& t : tasks)
    {
        if (t.id == id)
        {
            t.done = true;
            break;
        }
    }
    saveTasks();
}

void TaskManager::deleteTask(int id)
{
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
            [id](const Task& t) { return t.id == id; }),
        tasks.end()
    );

    saveTasks();
}

void TaskManager::editTask(int id)
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
    saveTasks();
}

void TaskManager::showStats() const
{
    int done = 0;

    for (const auto& t : tasks)
        if (t.done) done++;

    std::cout << "Total: " << tasks.size() << "\n";
    std::cout << "Done: " << done << "\n";
    std::cout << "Remaining: " << tasks.size() - done << "\n";
}

void TaskManager::listTasks() const
{
    for (const auto& t : tasks)
    {
        std::cout
            << "[" << (t.done ? "x" : " ") << "] "
            << t.id << " - "
            << t.text << "\n";
    }
}