#include <iostream>
#include <string>
using namespace std;


class TreeNode
{
private:
    int data;
    TreeNode *leftChild;
    TreeNode *rightChild;

public:
    TreeNode* getLeftChild() {return leftChild; }
    TreeNode* getRightChild() {return rightChild; }

    TreeNode(string dataField) {
        data = stoi(dataField); 
        leftChild = rightChild = NULL;
    }
    TreeNode(int dataField) {
        data = dataField; 
        leftChild = rightChild = NULL;
    }
    // ~TreeNode();

    friend class BinaryTree;
    friend class Monster;
};



class BinaryTree
{
private:
    const int rootData = -1;
    TreeNode *root;

public:
    TreeNode* getRoot() {return root; }
    void insertLeft(TreeNode *parent, int data);
    void insertRight(TreeNode *parent, int data);
    void bothInsertLeft(TreeNode *parent, int data);

    bool isleafNode(TreeNode *node);
    bool isFullNode(TreeNode *node);

    string visit(TreeNode *current);
    void preOrder(TreeNode *current, string& str);

    BinaryTree() {root = new TreeNode(rootData); }
};


class Monster: public BinaryTree
{
private:
    TreeNode* realWorld;

public:
    void summon(int star);
    int attack();
    bool isFull()  {return isFullNode(realWorld); } // Real world is full
    bool isEmpty() {return isleafNode(realWorld); } // Real world is empty
    char whichLowerStar(); /* Return 'L'/'R' if monster at left/right have lower star,
                              if two monster have same star, return 'S' 
                              if the real world is not full, return 'E'*/
    void preOrder(TreeNode *current, string& str); // Pre-order traversal wihout printing root node

    Monster() {realWorld = getRoot(); }
    // ~Monster();
};


void BinaryTree::insertLeft(TreeNode *parent, int data) {
    TreeNode *newNode = new TreeNode(data);
    newNode->leftChild = parent->leftChild;
    parent->leftChild = newNode;
}


void BinaryTree::insertRight(TreeNode *parent, int data) {
    TreeNode *newNode = new TreeNode(data);
    newNode->rightChild = parent->rightChild;
    parent->rightChild = newNode;
}


void BinaryTree::bothInsertLeft(TreeNode *parent, int data) {
    TreeNode *newNode = new TreeNode(data);
    newNode->leftChild = parent->leftChild;
    newNode->rightChild = parent->rightChild;
    parent->leftChild = newNode;
    parent->rightChild = NULL;
}

bool BinaryTree::isleafNode(TreeNode *node) {
    return node->leftChild==NULL && node->rightChild==NULL;
}

bool BinaryTree::isFullNode(TreeNode *node) {
    return node->leftChild!=NULL && node->rightChild!=NULL;
}

string BinaryTree::visit(TreeNode *current) {
    return to_string(current->data) + "* ";
}

void BinaryTree::preOrder(TreeNode *current, string& str) {
    if (current) {
        str += visit(current);
        preOrder(current->leftChild, str);
        preOrder(current->rightChild, str);
    }
}



char Monster::whichLowerStar() {
    if (!isFull())
        return 'E';
    else {
        int left = realWorld->leftChild->data;
        int right = realWorld->rightChild->data;

        if (left < right) 
            return 'L';
        else if (left == right)
            return 'S';
        else
            return 'R';
    }
}


void Monster::summon(int star) {

    if (star <= 4) {
        if (isEmpty()) 
            insertLeft(realWorld, star);
        else
            insertRight(realWorld, star);
    }

    else if (star>=5 && star<8) {
        if (isFull()) {
            if (whichLowerStar() == 'R')
                insertRight(realWorld, star);
            else 
                insertLeft(realWorld, star);
        }
        else
            insertLeft(realWorld, star);
    }

    else
        bothInsertLeft(realWorld, star);
}

int Monster::attack() {
    int leftStar, rightStar;  

    if (realWorld->leftChild)
        leftStar = realWorld->leftChild->data;
    else
        leftStar = 0;
    
    if (realWorld->rightChild)
        rightStar = realWorld->rightChild->data;
    else
        rightStar = 0;
    
    return leftStar + rightStar;
}


void Monster::preOrder(TreeNode *current, string& str) {
    if (current) {
        if (current!= realWorld)
            str += visit(current);
        preOrder(current->leftChild, str);
        preOrder(current->rightChild, str);
    }
}


int getNum(string input) {
    string num;
    for (int i = 0; i < input.length(); i++)
        if (isdigit(input[i])) num.push_back(input[i]); 

    return stoi(num);
}

int main() {

    string input, preOrderStr;
    Monster monsterTree;
    int star;
    int demage=0;
    int i=4;

    while (cin >> input)
    {
        if (input == "Summon") {
            i=1;
        }
        else if (input == "Attack") {
            demage += monsterTree.attack();
        }
        else if (input == "TheEnd")
            break;
        
        // Get the star of moster and then summon it
        if (i<3) 
            i++;
        else if (i==3) {
            star = getNum(input);
            monsterTree.summon(star);
            i++;
        }
    }
    

    // Pre-order traversal of the monster tree
    monsterTree.preOrder(monsterTree.getRoot(), preOrderStr);

    // Output the result
    cout << preOrderStr.erase(preOrderStr.length()-1);
    cout << "\n";
    cout << demage;
    cout << "\n";

    // monsterTree.preOrder(monsterTree.getRoot()->getLeftChild());

    return 0;
}