#pragma once
#include <algorithm>
#include <stack>
#include "ReadFile.h"
#include "tree.h"

#define INITIATOR "node"
#define LEAF_TERMINATOR "/>"
#define NODE_TERMINATOR "/node"
#define ROOT_START "root"
#define ROOT_END "/root"

class XMLParser
{
public:
	XMLParser(const char *, Tree *);
    
    std::string getToken(std::string &str, std::string &token);
    void fillTree(std::vector<std::string> &nodes, Tree *tree);
    void removeSpaces(std::string &str);

    inline void printFile() {
        std::cout << m_rawFile;
    }

    ~XMLParser();
private:
    bool isBehaviorEmpty(std::string &str) {
        return (str.find("behavior=\"\"") != std::string::npos || str.find("behavior") == std::string::npos);
    }
    bool isResponseEmpty(std::string &str) {
        return (str.find("response=\"\"") != std::string::npos || str.find("response") == std::string::npos);
    }
    bool isLeafTerminator(std::string &str) {
        return (str.find(LEAF_TERMINATOR) != std::string::npos);
    }
    bool isTerminator(std::string &str) {
        return (str.find(NODE_TERMINATOR) != std::string::npos);
    }
    bool isInitiator(std::string &str) {
        return (str.find(INITIATOR) != std::string::npos);
    }
    bool isRootStart(std::string &str) {
        return (str.find(ROOT_START) != std::string::npos);
    }
    bool isRootEnd(std::string &str) {
        return (str.find(ROOT_END) != std::string::npos);
    }

    std::string m_rawFile;
	std::vector<Tree::point> m_VectorNodes;
};

