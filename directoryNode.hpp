#include<iostream>
#include<vector>
#include "lex.hpp"

#ifndef __DIRECTORYN
#define __DIRECTORYN

class DirectoryNode {
public:
    DirectoryNode(): _isFile(false), _isDirectory(false), _parent(""), _path(""), _name(""), _type("") {}
    DirectoryNode(Lex * tokens);

    bool isFile() { return _isFile; }  // is this a file directory type?
    bool isDirectory() { return _isDirectory; }  // is this a directory, directory type?

    void addDirectoryNode(DirectoryNode *list) { children.push_back(list); }
    int numEntries() { return children.size(); }
    std::vector<DirectoryNode *> getChildren() { return children; }

    std::string Parent() { return _parent; }
    void parent(std::string pStr) { _parent = pStr; }
    void addParentNode(DirectoryNode * parent) {parentNode = parent; }
    DirectoryNode * getParentNode() {return parentNode; }

    std::string path() { return _path; }
    void path(std::string pStr) { _path = pStr; }

    std::string name() { return _name; }
    void name(std::string pStr) { _name = pStr; }

    std::string type() { return _type; }
    void type(std::string pStr) { _type = pStr; }

    int numChildren() {return children.size(); }



private:
    std::string _parent, _path, _name, _type;
    DirectoryNode *parentNode;
    std::vector<DirectoryNode *> children;
    bool _isFile, _isDirectory;

    DirectoryNode * buildStructure(Lex * lex);

};

#endif
