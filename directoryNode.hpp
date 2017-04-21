#include<iostream>
#include<vector>
#include "lex.hpp"

#ifndef __DIRECTORYN
#define __DIRECTORYN

class DirectoryNode {
public:
    DirectoryNode(): _parent(""), _path(""), _name(""), _type(""), _isFile(false), _isDirectory(false) {}
    DirectoryNode(Lex * tokens);

    bool isFile() { return _isFile; }  // is this a file directory type?
    bool isDirectory() { return _isDirectory; }  // is this a directory, directory type?
    void isFile(bool input) { _isFile = input; }
    void isDirectory(bool input) { _isDirectory = input; }


    void addDirectoryNode(DirectoryNode *list) { children.push_back(list); }
    int numEntries() { return children.size(); }
    std::vector<DirectoryNode *> getChildren() { return children; }

    std::string Parent() { return _parent; }
    void parent(std::string pStr) { _parent = pStr; }
    void addParentNode(DirectoryNode * parent) {parentNode = parent; }
    DirectoryNode * getParentNode() {return parentNode; }

    std::string path() { return _path; }
    void path(std::string pStr) { _path = pStr; }
    void adjustPaths(DirectoryNode * fromNode, DirectoryNode * toNode);
    void adjustPathsDupe(DirectoryNode * fromNode, DirectoryNode * toNode);



    std::string name() { return _name; }
    void name(std::string pStr) { _name = pStr; }

    std::string type() { return _type; }
    void type(std::string pStr) { _type = pStr; }

    int numChildren() {return children.size(); }
    void setChildren(std::vector<DirectoryNode *> newChildren) {children = newChildren;}



private:
    std::string _parent, _path, _name, _type;
    DirectoryNode *parentNode;
    std::vector<DirectoryNode *> children;
    bool _isFile, _isDirectory;

    DirectoryNode * buildStructure(Lex * lex);

};

#endif
