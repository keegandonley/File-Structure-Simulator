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

// Traverses the structure one directory at a time in the path.
// This means that I can't cd to a directory that isn't a child of my current working directory
// without entering the full path.
// It doesn't care whether the node is a file or a directory. This helper function just returns the given
// node, and the calling function handles errors.
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
    // Above, we have checked for a few special characters. This allows for commands such as:
    // cd ~/project1/../project3

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

// Depth counts the slashes in the path to determine how many structures down it is.
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

// Throws an error message if the returned node isn't a directory
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
    DirectoryNode * result = duplicate(cwd);
    result -> path("");
    result -> parent("..");
    result -> adjustPathsDupe(rootDir, nullptr);
    return new DirectoryEntry(result);
}

DirectoryEntry *DirectoryEntry::duplicate(std::string path) {
    DirectoryNode * result = duplicate(this -> getNode(path));
    result -> path("");
    result -> parent("..");
    result -> adjustPathsDupe(result, nullptr);
    return new DirectoryEntry(result);
}

DirectoryNode *DirectoryEntry::duplicate(DirectoryNode * current) {
    DirectoryNode * structure = new DirectoryNode();
    structure -> isFile(current -> isFile());
    structure -> isDirectory(current -> isDirectory());
    structure -> parent(current -> Parent());
    structure -> path(current -> path());
    structure -> name(current -> name());
    structure -> type(current -> type());
    structure -> addParentNode(nullptr);
    if (current -> numChildren() > 0) {
        std::vector<DirectoryNode *> children = current -> getChildren();
        for (auto child : children) {
            DirectoryNode * temp = duplicate(child);
            temp -> addParentNode(structure);
            structure -> addDirectoryNode(temp);
        }
    }
    return structure;

}

std::vector<std::string> DirectoryEntry::find(std::string path) {
    std::vector<std::string> * files = new std::vector<std::string>();
    DirectoryNode * current = getNode(path);
    if (current -> isFile()) {
        files -> push_back(current -> name());
        return *files;
    } else {
        files -> push_back(current -> path());
        find(current, files);
        return *files;
    }
}

void DirectoryEntry::find(DirectoryNode * current, std::vector<std::string> * files) {
    if (current == nullptr)
        return;
    if (current -> isFile()) {
        files -> push_back(current -> name());
        return;
    }
    std::vector<DirectoryNode *> children = current -> getChildren();
    for (auto child : children) {
        if (child -> numChildren() == 0) {
            files -> push_back(child->path());
        } else {
            files -> push_back(child->path());
            find(child, files);
        }
    }

}

bool DirectoryEntry::hasSubstructure(DirectoryEntry *dirEntry) {
    std::string newdir = findSubStart(this -> rootDir, dirEntry -> rootDir);
    std::vector<std::string> current = this -> find(newdir);
    std::vector<std::string> dirEnt = dirEntry -> find("~");
    for (int i = 0; i != current.size(); ++i) {
        if (current[i] != dirEnt[i]) {
            return false;
        }

    }
    return true;
}

std::string DirectoryEntry::findSubStart(DirectoryNode * current, DirectoryNode * target) {
    if (isEqual(current, target))
        return current -> path();
    std::vector<DirectoryNode *> children = current -> getChildren();
    for (auto child : children) {
        if (isEqual(child, target))
            return child -> path();
        if (child -> isDirectory())
            return findSubStart(child, target);
    }
    return "~";
}

bool DirectoryEntry::isEqual(DirectoryNode * A, DirectoryNode * B) {
    return (A->isFile() == B->isFile() && A->name() == B->name() && A->type() == B->type());
}

bool DirectoryEntry::areTheSame(DirectoryEntry *dirEntry) {
    std::vector<std::string> current = this -> find("~");
    std::vector<std::string> dirEnt = dirEntry -> find("~");
    for (int i = 0; i != current.size(); ++i) {
        if (current[i] != dirEnt[i])
            return false;
    }
    return true;
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
