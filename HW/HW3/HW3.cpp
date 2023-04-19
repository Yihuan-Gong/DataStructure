#include <iostream>
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

    void visit(TreeNode *current);
    void preOrder(TreeNode *current);
    void preOrder(TreeNode *current, bool visitRoot);

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
    void preOrderPrint() {preOrder(realWorld, false); }

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

void BinaryTree::visit(TreeNode *current) {
    cout << current->data << "* ";
}

void BinaryTree::preOrder(TreeNode *current) {
    if (current) {
        visit(current);
        preOrder(current->leftChild);
        preOrder(current->rightChild);
    }
}

void BinaryTree::preOrder(TreeNode *current, bool visitRoot) {
    if (current) {
        if (current != root)
            visit(current);
        else if (current == root && visitRoot)
            visit(current);
            
        preOrder(current->leftChild);
        preOrder(current->rightChild);
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
    int leftStar  = realWorld->leftChild->data;
    int rightStar = realWorld->rightChild->data;
    return leftStar + rightStar;
}

int getNum(string input) {
    string num;
    for (int i = 0; i < input.length(); i++)
        if (isdigit(input[i])) num.push_back(input[i]); 

    return stoi(num);
}

int main() {


    string input;
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
    

    // Output the result
    monsterTree.preOrderPrint();
    cout << endl;
    cout << demage;

    // monsterTree.preOrder(monsterTree.getRoot()->getLeftChild());

    return 0;
}