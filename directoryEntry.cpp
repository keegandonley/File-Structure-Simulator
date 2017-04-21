#include "directoryEntry.hpp"
#include "directoryNode.hpp"
#include <iostream>
#include <string>

const int LSLINELENGTH = 40;

DirectoryEntry::DirectoryEntry() {
    rootDir = nullptr;
    cwd = nullptr;
}

DirectoryEntry::DirectoryEntry(DirectoryNode * root) {
    rootDir = root;
    cwd = root;
}


DirectoryNode *DirectoryEntry::getNode(std::string path) {

    std::string directory = "";
    DirectoryNode * current;
    DirectoryNode * restore = cwd;
    for (char i : path) {
        if (i != '/') {
            directory += i;
        } else if (i == '/') {
            current = getNodeHelp(directory);
            if (current == nullptr) {
                cwd = restore;
                return cwd;
            }
            cwd = current;
            directory = "";
        }

    }
    current = getNodeHelp(directory);
    if (current == nullptr) {
        return restore;
    }
    cwd = restore;
    return current;
}

DirectoryNode * DirectoryEntry::getNodeHelp(std::string target) {
    if (target == "")
        return cwd;
    else if (target == "..") {
        if (cwd -> getParentNode() != nullptr) {
            return cwd -> getParentNode();
        } else {
            return cwd;
        }
    } else if (target == ".") {
        return cwd;
    } else if (target == "~") {
        return rootDir;
    }

    if (cwd -> numChildren() > 0) {
        std::vector<DirectoryNode *> childrenTemp = cwd -> getChildren();
        for ( auto child : childrenTemp) {
            if (child -> name() == target) {
                return child;
            }
        }
    }
    std::cout << "cd: " << target << ": No such file or directory" << std::endl;
    return cwd;
}

int DirectoryEntry::depth() {
    std::string currentDir = cwd -> path();
    if (cwd -> path() == rootDir -> path())
        return 0;
    int count = 0;
    for (char i : currentDir )
        if (i == '/')
            count++;
    return count + 1;
}


std::string DirectoryEntry::pwd() {
    return rootDir -> name() + '/' + cwd -> path();
}

std::string DirectoryEntry::cd(std::string path) {
    DirectoryNode * temp = getNode(path);
    if (temp -> type() != "directory") {
        std::cout << "cd: " << temp -> name() << ": Not a directory" << std::endl;
        return cwd -> name();
    }
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
        std::string entry = child -> name();
        for (int i = 0; i < (LSLINELENGTH-child->name().size()); i++)
            entry += " ";
        entry += child -> type();
        files.push_back(entry);
    }
    return files;
}

std::vector<std::string> DirectoryEntry::ls(std::string target) {
    std::vector<DirectoryNode*> children = getNode(target) -> getChildren();
    std::vector<std::string> files;
    for (auto child : children) {
        std::string entry = child -> name();
    	for (int i = 0; i < (LSLINELENGTH-child->name().size()); i++)
    		entry += " ";
    	entry += child -> type();
            files.push_back(entry);
    }
    return files;
}

DirectoryEntry *DirectoryEntry::duplicate() {
    return duplicate(rootDir);
}

DirectoryEntry *DirectoryEntry::duplicate(DirectoryNode * current) {
    return new DirectoryEntry();
}

void DirectoryEntry::move(std::string fromPath, std::string toPath) {
    if (fromPath == toPath || toPath == ".")
        return;
    DirectoryNode * fromNode = getNode(fromPath);
    DirectoryNode * toLocation = getNode(toPath);
    if (toLocation -> type() != "directory"){
        std::cout << toLocation -> name() << " is not a directory" << std::endl;
        return;
    }
    std::vector<DirectoryNode *> children = fromNode -> getParentNode() -> getChildren();
    std::vector<DirectoryNode *> temp;
    for (auto child : children)
        if (child -> path() != fromNode -> path()) {
            temp.push_back(child);
        }
    fromNode -> getParentNode() -> setChildren(temp);
    std::string newPath = toLocation -> path() + "/" + fromNode -> name();
    fromNode -> path(newPath);
    fromNode -> adjustPaths(fromNode, toLocation);
    fromNode -> addParentNode(toLocation);
    toLocation -> addDirectoryNode(fromNode);
}
