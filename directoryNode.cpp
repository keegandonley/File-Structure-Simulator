#include "directoryNode.hpp"
#include "lex.hpp"
#include "token.hpp"
#include <cstdlib>

#define dev false
#define print false

DirectoryNode::DirectoryNode(Lex * tokens) {
    DirectoryNode * temp = buildStructure(tokens);
    _isFile = temp -> isFile();
    _isDirectory = temp -> isDirectory();
    _parent = temp -> Parent();
    _path = temp -> path();
    _name = temp -> name();
    _type = temp -> type();
    children = temp -> getChildren();
}

DirectoryNode * DirectoryNode::buildStructure(Lex * tokens) {
    DirectoryNode * node = new DirectoryNode();
    Token current = tokens -> getToken();

    if (! current.isLeftBrace()) {
        if (dev) {
            std::cout << "1: Exiting due to bad list...\nThe token is: ->";
            current.printToken();
            std::cout << "<-" << std::endl;
        }
        exit (1);
    }

    // At this point we saw a left brace
    current = tokens ->  getToken();


    while (current.isKey()) {
        // We need to determine what the key is....
        // It can be parent, path, name, type, or children

        // Get the key
        std::string key = current.getName();

        // Key must be followed by a colon
        current = tokens -> getToken();
        if (! current.isColon()) {
            exit (2);
        }

        // colon must be followed by a value for the key-value pair
        current = tokens -> getToken();
        if (! (current.isQuotedString() || key == "children" )) {
            exit (3);
        }
        if (dev && key != "children") { std::cout << key << ": " << current.getName() << std::endl; }

        // Assign the value
        if (key == "parent") {
            node -> parent(current.getName());
        } else if (key == "path") {
            node -> path(current.getName());
        } else if (key == "name") {
            node -> name(current.getName());
        } else if (key == "type") {
            node -> type(current.getName());
        }

        if (current.isLeftBracket()) {
            current = tokens -> getToken();
            while (current.isLeftBrace()) {
                if (dev) {std::cout << "\n\n" << std::endl;}
                tokens -> ungetToken();
                DirectoryNode * temp = buildStructure(tokens);
                temp -> addParentNode(node);
                node -> addDirectoryNode(temp);
                current = tokens -> getToken();
                if (current.isComma())
                    current = tokens -> getToken();
            }
            if(!current.isRightBracket()) {
                if (dev) {
                    std::cout << "5: Exiting due to bad list...\nThe token is: ->";
                    current.printToken();
                    std::cout << "<-" << std::endl;
                }
                exit (5);
            }
        }

        current = tokens -> getToken();

        if (current.isRightBrace()) {
            return node;
        }
        if (current.isComma()) {
            current = tokens -> getToken();
        }
        // If the next token isn't a brace or a comma, we need to put it back...
        // else if (current.isLeftBrace()){
        //     while (current.isLeftBrace()) {
        //         tokens -> ungetToken();
        //         DirectoryNode * temp = buildStructure(tokens);
        //         node -> addDirectoryNode(temp);
        //         current.printToken();
        //     }
        //
        // } else {
        //     current = tokens -> getToken();
        // }


    }
    std::cout << "Returning" << std::endl;
    return node;
}


void DirectoryNode::adjustPaths(DirectoryNode * fromNode, DirectoryNode * toNode) {
    std::vector<DirectoryNode *> children = fromNode -> getChildren();
    for (auto child : children) {
        std::string newPath = child -> getParentNode() -> path() + "/" + child -> name();
        std::cout << "the new path is: " << newPath << std::endl;
        child -> path(newPath);
        if (child -> numChildren() > 0) {
            adjustPaths(child, toNode);
        }
    }
}
