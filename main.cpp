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
