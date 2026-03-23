#include <iostream>
#include <string>

int main()
{
	std::string command;

	std::cout << "CLI ToDo started\n";

	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, command);

		if (command == "exit") break;
		else if (command == "hello")
			std::cout << "Hello, dev!\n";
		else
			std::cout << "Unkown command!\n";
	}
	return 0;
}