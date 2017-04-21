#include "directoryNode.hpp"
#include "directoryEntry.hpp"
#include "lex.hpp"
#include "token.hpp"
#include "string"
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <regex>


std::string getFileContents(std::string fileName);

int main(int argc, const char * const argv[]) {
    // Validate input argument
    if (argc < 2) {
		std::cout << "Please enter a file" << std::endl;
        return 1;
    }

    // Get the contents of the file
    std::string input = getFileContents(argv[1]);

    // Tokenize using Lex
    Lex * tokens = new Lex(input);

	DirectoryNode * structure = new DirectoryNode(tokens);
    DirectoryEntry * directory = new DirectoryEntry(structure);


    // TEST depth()
    directory -> cd("project1/RomanCalculatorStudentFiles");
    std::cout << "\nTesting depth()..." << std::endl;
    int depth = directory -> depth();
    std::cout << depth << std::endl;
    std::cout << "Done testing depth()" << std::endl;

    // TEST PWD()
    std::cout << "\nTesting pwd()..." << std::endl;
    std::cout << directory -> pwd() << std::endl;
    std::cout << "Done testing pwd()" << std::endl;

    directory -> cd();

    // TEST cd(STR)
    std::cout << "\nTesting cd(std::string)..." << std::endl;
    std::cout << "Looking for \"project3/dir_to_json\", got to directory: " << directory -> cd("project3/dir_to_json") << std::endl;
    std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    std::cout << "Looking for \"node_modules\", got to directory: " << directory -> cd("node_modules") << std::endl;
    std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    std::cout << "Looking for \"..\", got to directory: " << directory -> cd("..") << std::endl;
    std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    std::cout << "Done testing cd(std::string)" << std::endl;

    // TEST cd()
    std::cout << "\nTesting cd()..." << std::endl;
    std::cout << "Changed to directory: " << directory -> cd() << std::endl;
    std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    std::cout << "Done testing cd()" << std::endl;

    // TEST ls(std::string)
    std::cout << "\nTesting ls(std::string)..." << std::endl;
    std::vector<std::string> files = directory -> ls("project1");
    for (auto file : files)
        std::cout << file << std::endl;
    std::cout << "Done testing ls(std::string)" << std::endl;

    // TEST ls()
    std::cout << "\nTesting ls()..." << std::endl;
    std::vector<std::string> filess = directory -> ls();
    for (auto file : filess)
        std::cout << file << std::endl;
    std::cout << "Done testing ls()" << std::endl;

    // TEST move()
    // std::cout << "\nTesting move()..." << std::endl;
    // directory -> move("lala","oops");
    // std::cout << "Done testing move()" << std::endl;


    // Interactive tests
    directory -> cd();
    std::cout << "\n\nInteractive demo for directory structure functions\n";
    std::cout << "Enter commands as you would in a normal shell\n";
    std::cout << "Type logout to exit\n";


    std::string command, argument;
    std::cout << "\n[demo@sample ~]$ ";
    std::cin >> command;
    if (command == "logout")
        return 0;
    std::getline(std::cin, argument);
    argument.erase(argument.begin());
    while (command != "logout" && argument != "logout") {

        if (command == "cd") {
            if (argument != "") {
                directory -> cd(argument);
            } else {
                directory -> cd();
            }
        } else if (command == "ls") {
            std::vector<std::string> files;
            if (argument != "") {
                files = directory -> ls(argument);
            } else {
                files = directory -> ls();
            }
            for (auto file : files) {
                std::cout << file << std::endl;
            }
        } else if (command == "pwd") {
            std::cout << directory -> pwd() << std::endl;
        } else if (command == "depth") {
            std::cout << directory -> depth() << std::endl;
        } else {
            std::cout << "Invalid command "<< command << std::endl;
        }


        std::cout << "[demo@sample ~]$ ";
        std::cin >> command;
        if (command == "logout")
            return 0;
        std::getline(std::cin, argument);
        argument.erase(argument.begin());
    }


    return 0;
}




std::string getFileContents(std::string fileName) {
    std::string fileContents = "";
    std::string temp;

    // Open & read from file
    std::ifstream infile(fileName.c_str());
	if (!infile) {
	   std::cout << "Please enter a valid file!" << std::endl;
	   exit(2);
   }
    while (std::getline(infile, temp))
        fileContents += temp;

    return fileContents;
}
