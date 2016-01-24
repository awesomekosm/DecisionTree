#include "xmlparser.h"

//divide raw xml file into sepparate tags
std::vector<std::string> sepparateTags(std::string &str) {
    std::vector<std::string> nodeVector;
    for (int i = 0; i < str.size();i++) {
        if (char(str.at(i)) == 60) {
            std::string temp;
            while (char(str.at(i)) != 62) {
                temp.push_back(str.at(i+1));
                i++;
            }
            nodeVector.push_back(temp);
            temp.clear();
        }
    }
    return nodeVector;
}

//generic method to retrieve a value from a tag; from behavior or from response
std::string XMLParser::getToken(std::string &str, std::string &token) {
    std::string finalString;
    std::size_t found = str.find(token);
    //if token string is present in the node
    if (found != std::string::npos) {
        //move the itterator to value's location
        found += token.size();
        for (int i = found; i < str.size();) {
            if (str.at(i) != '"') {
                finalString.push_back(str.at(i));
                i++;
            }
            else {
                break;
            }
        }
    }
    return finalString;
}

void whileChildNode(std::vector<std::string> &nodes, Tree *tree) {

}

void XMLParser::fillTree(std::vector<std::string> &nodes, Tree *tree) {
    //used for retrieving token values
    std::string behavior = "behavior=\"";
    std::string response = "response=\"";
    //sets the name of the root
    tree->getRoot()->behavior = ROOT_START;
    //stack controls the point pointer so we know which point to attach the child point(branch) to
    std::stack<Tree::point*> stack;

    Tree::point *p = tree->getRoot();
    for (auto i : nodes) {
        //when property of behavior is present add it to the tree and push the pointer to the stack
        if (!isBehaviorEmpty(i)) {
            p = tree->addPoint(p, getToken(i, behavior), std::string("")); 
            stack.push(p);     
        }
        //when property of response is present add it to the tree and push the pointer to the stack
        if (!isResponseEmpty(i)) {
            p = tree->addPoint(p, std::string(""), getToken(i, response));
            stack.push(p);      
        }
        //when /node is terminated pop the stack and set the current point to previous point
        if (isTerminator(i)) {
            stack.pop();
            //to prevent invalid access
            if (stack.size() == 0) {
                p = tree->getRoot();
            }
            else {
                p = stack.top();
            }          
        }
        //when the tag is closed with /> the pointer is set to its parent
        if (isLeafTerminator(i)) {
            stack.pop();
            if (stack.size() == 0) {
                p = tree->getRoot();
            }
            else {
                p = stack.top();
            }  
        }
    }
}


XMLParser::XMLParser(const char *fileName, Tree *tree){
    ReadFile rf;
    m_rawFile = rf.readFile(fileName);
    std::vector<std::string> nodes = sepparateTags(m_rawFile);
    fillTree(nodes, tree);
}

void XMLParser::removeSpaces(std::string & str)
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace));
}


XMLParser::~XMLParser()
{
}
