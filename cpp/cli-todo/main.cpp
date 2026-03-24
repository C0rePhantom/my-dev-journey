#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> tasks;
    std::string command;
    std::string task;

    std::cout << "CLI ToDo started\n";
    std::cout << "Type 'help' for commands\n";

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        // привести команду к нижнему регистру
        std::transform(command.begin(), command.end(), command.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (command == "add")
        {
            std::cout << "Enter task: ";
            std::getline(std::cin >> std::ws, task);
            tasks.push_back(task);
            std::cout << "Task added!\n";
        }
        else if (command == "list")
        {
            if (tasks.empty())
            {
                std::cout << "No tasks yet\n";
                continue;
            }

            for (size_t i = 0; i < tasks.size(); i++)
            {
                std::cout << i + 1 << ". " << tasks[i] << std::endl;
            }
        }
        else if (command == "help")
        {
            std::cout << "Commands:\n";
            std::cout << "add  - add new task\n";
            std::cout << "list - show all tasks\n";
            std::cout << "exit - quit program\n";
        }
        else if (command == "exit")
        {
            std::cout << "Bye!\n";
            break;
        }
        else
        {
            std::cout << "Unknown command. Type 'help'\n";
        }
    }

    return 0;
}