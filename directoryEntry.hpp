#include <string>
#include <vector>
#include "directoryNode.hpp"

#ifndef __DIRECTORYE
#define __DIRECTORYE

class DirectoryEntry {
public:
    DirectoryEntry();
    DirectoryEntry(DirectoryNode * root);
    int depth();
    std::string pwd();
    std::string cd();
    std::string cd(std::string path);
    std::vector<std::string> ls();
    std::vector<std::string> ls(std::string path);
    DirectoryEntry *duplicate();
    DirectoryEntry *duplicate(std::string path);
    std::vector<std::string> find(std::string path);
    bool hasSubstructure(DirectoryEntry *dirEntry);
    bool areTheSame(DirectoryEntry *dirEntry);
    void move(std::string fromPath, std::string toPath);

private:
    DirectoryNode *rootDir;
    DirectoryNode *cwd;
    DirectoryNode *getNode(std::string);
    DirectoryNode *getNodeHelp(std::string target);
};

#endif
