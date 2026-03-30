#pragma once
#include <vector>
#include "Task.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId = 1;

    void saveTasks() const;
    void loadTasks();

public:
    TaskManager();

    void addTask(const std::string& text);
    void markDone(int id);
    void deleteTask(int id);
    void editTask(int id);
    void listTasks() const;
    void showStats() const;
};