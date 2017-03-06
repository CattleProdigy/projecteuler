#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <list>


struct Node
{
    int val;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    int maxAccumVal = 0;
};
using NodePtr = std::shared_ptr<Node>;

NodePtr loadTriangleTreeFromFile(const char* file)
{
    std::ifstream ifs(file);

    NodePtr rootNode(new Node);
    ifs >> rootNode->val;
    std::string dummy; std::getline(ifs, dummy); // go to next line

    std::vector<NodePtr> previousRowNodes;
    previousRowNodes.push_back(rootNode);

    std::string lineString;
    while (std::getline(ifs, lineString))
    {
        std::vector<NodePtr> currentRowNodes;
        std::stringstream ss(lineString);
        int currentVal;
        int rowValIndex = 0;
        while (ss >> currentVal)
        {
            NodePtr newNode(new Node);
            newNode->val = currentVal;

            if (rowValIndex < previousRowNodes.size())
                previousRowNodes[rowValIndex]->left = newNode;

            if (rowValIndex >= 1)
                previousRowNodes[rowValIndex-1]->right = newNode;

            currentRowNodes.push_back(newNode);
            rowValIndex++;
        }
        previousRowNodes = std::move(currentRowNodes);
    }

    return rootNode;
}

int maxRoute(NodePtr node)
{
    // In order traversal
    std::list<NodePtr> traversalList;

    int maxRoute = 0;

    NodePtr tNode(new Node);
    *tNode = *node;

    traversalList.push_back(tNode);
    tNode->maxAccumVal = tNode->val;
    while (!traversalList.empty())
    {
        NodePtr currentNode = traversalList.front();
        traversalList.pop_front();

        if (currentNode->left) // not a leaf
        {
            Node& left = *currentNode->left;
            if (left.maxAccumVal < currentNode->maxAccumVal + left.val)
            {
                traversalList.push_front(currentNode->left);
                left.maxAccumVal = currentNode->maxAccumVal + left.val;
            }

            Node& right = *currentNode->right;
            if (right.maxAccumVal < currentNode->maxAccumVal + right.val)
            {
                traversalList.push_front(currentNode->right);
                right.maxAccumVal = currentNode->maxAccumVal + right.val;
            }

        }
        else // a leaf
        {
            maxRoute = std::max(currentNode->maxAccumVal, maxRoute);
        }
    }

    return maxRoute;
}

int
main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Give a file" << std::endl;
        return -1;
    }

    NodePtr rootNode = loadTriangleTreeFromFile(argv[1]);

    std::cout << maxRoute(rootNode) << std::endl;

    return 0;
}
