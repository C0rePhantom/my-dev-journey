#include "TaskManager.h"
#include <iostream>
#include <sstream>

int main()
{
    TaskManager tm;
    std::string line;

    std::cout << "ToDo CLI ready. Type 'help'\n";

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "exit")
        {
            break;
        }
        else if (cmd == "add")
        {
            std::string text;
            std::getline(ss >> std::ws, text);
            tm.addTask(text);
        }
        else if (cmd == "list")
        {
            tm.listTasks();
        }
        else if (cmd == "done")
        {
            int id;
            ss >> id;
            tm.markDone(id);
        }
        else if (cmd == "delete")
        {
            int id;
            ss >> id;
            tm.deleteTask(id);
        }
        else if (cmd == "stats")
        {
            tm.showStats();
        }
        else if (cmd == "help")
        {
            std::cout <<
                "Commands:\n"
                " add <text>\n"
                " list\n"
                " done <id>\n"
                " delete <id>\n"
                " stats\n"
                " exit\n";
        }
        else
        {
            std::cout << "Unknown command. Type 'help'\n";
        }
    }

    return 0;
}