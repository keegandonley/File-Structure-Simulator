#include "directoryNode.hpp"
#include "directoryEntry.hpp"
#include "lex.hpp"
#include "token.hpp"
#include "string"
#include <fstream>
#include <cstdlib>

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

    // TEST PWD()
    std::cout << "\nTesting pwd()..." << std::endl;
    std::cout << directory -> pwd() << std::endl;
    std::cout << "Done testing pwd()" << std::endl;

    // TEST cd(STR)
    // TODO: Handle not finding the directory in question
    // TODO: Does the path matter?
    std::cout << "\nTesting cd(std::string)..." << std::endl;
    std::cout << "Looking for \"project1/RomanCalculatorStudentFiles\", got to directory: " << directory -> cd("project1/RomanCalculatorStudentFiles") << std::endl;
    std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    // std::cout << "Looking for \"tasks\", got to directory: " << directory -> cd("tasks") << std::endl;
    // std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    std::cout << "Done testing cd(std::string)" << std::endl;

    // TEST cd()
    std::cout << "\nTesting cd(std::string)..." << std::endl;
    std::cout << "Changed to directory: " << directory -> cd() << std::endl;
    std::cout << "pwd is now: " << directory -> pwd() << std::endl;
    std::cout << "Done testing cd(std::string)" << std::endl;

    // TEST ls()
    std::cout << "\nTesting ls()..." << std::endl;
    std::vector<std::string> files = directory -> ls();
    for (auto file : files)
        std::cout << file << std::endl;
    std::cout << "Done testing ls()" << std::endl;
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
