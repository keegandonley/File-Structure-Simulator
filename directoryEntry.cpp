#include "directoryEntry.hpp"
#include "directoryNode.hpp"
#include <iostream>
#include <string>


DirectoryEntry::DirectoryEntry(DirectoryNode * root) {
    std::cout << "Constructor set the root and cwd of the directory!" << std::endl;
    rootDir = root;
    cwd = root;
}


DirectoryNode *DirectoryEntry::getNode(std::string path) {

    std::string directory = "";
    DirectoryNode * current;
    for (char i : path) {
        if (i != '/') {
            directory += i;
        } else if (i == '/') {
            current = getNodeHelp(directory);
            if (current == nullptr) {
                delete current;
                exit (1);
            }
            cwd = current;
            directory = "";
        }

    }
    current = getNodeHelp(directory);
    if (current == nullptr) {
        delete current;
        std::cout << "Invalid directory" << std::endl;
        exit (1);
    }
    return current;
}

DirectoryNode * DirectoryEntry::getNodeHelp(std::string target) {
    if (target == "")
        return nullptr;

    if (cwd -> numChildren() > 0) {
        std::vector<DirectoryNode *> childrenTemp = cwd -> getChildren();
        for ( auto child : childrenTemp) {
            if (child -> name() == target) {
                if (child -> type() != "directory") {
                    std::cout << "Not a directory" << std::endl;
                    return nullptr;
                } else {
                    return child;
                }
            }
        }
    }
    return nullptr;
}

std::string DirectoryEntry::pwd() {
    return cwd -> path();
}

std::string DirectoryEntry::cd(std::string path) {
    DirectoryNode * temp = getNode(path);
    cwd = temp;
    return temp -> name();
}

std::string DirectoryEntry::cd() {
    cwd = rootDir;
    return rootDir -> name();
}

std::vector<std::string> DirectoryEntry::ls() {
    std::vector<DirectoryNode*> children = cwd -> getChildren();
    std::vector<std::string> files;
    for (auto child : children) {
        std::string entry = child -> name() + "\t" + child -> type();
        files.push_back(entry);
    }
    return files;
}
