#include <iostream>
#include <string.h>
using namespace std;


class Card
{
private:
    int points;
    string pattern;
    Card *leftChild;
    Card *rightChild;

public:
    Card(string pattern);
    friend class CardTree;
};

Card::Card(string pattern)
{
    this->pattern = pattern;

    if (pattern == "Clubs")
        points = 1;
    else if (pattern == "Diamond")
        points = 3;
    else
        points = 0;

    leftChild = rightChild = NULL;
}


class CardTree
{
private:
    Card *root;

public:
    void coverLeft(string pattern);   // called by Diamond or Clubs
    void coverRight(string pattern);  // called by Diamond
    void coverBothToLeft(); //called by Heart

    Card* getRoot() {return root; }
    bool isTableEmpty();
    bool isTableFull();
    void preOrder(Card *current, int& totalPoints, int factor);

    void putCard(string pattern);
    int countPoints();
    void preOrderOnlyHeart(Card *current, int& totalPoints);

    CardTree() {root = new Card("table"); }
};

void CardTree::coverLeft(string pattern) {
    Card *newCard = new Card(pattern);
    newCard->leftChild = root->leftChild;
    root->leftChild = newCard;
}

void CardTree::coverRight(string pattern) {
    Card *newCard = new Card(pattern);
    newCard->rightChild = root->rightChild;
    root->rightChild = newCard;
}

void CardTree::coverBothToLeft () {
    Card *newCard = new Card("Heart");
    newCard->leftChild = root->leftChild;
    newCard->rightChild = root->rightChild;
    root->leftChild = newCard;
    root->rightChild = NULL;
}




bool CardTree::isTableEmpty() {
    return root->leftChild==NULL && root->rightChild==NULL;
}

bool CardTree::isTableFull() {
    return root->leftChild!=NULL && root->rightChild!=NULL;
}

void CardTree::preOrder(Card *current, int& totalPoints, int factor) {
    if (current) {
        totalPoints += (current->points)*factor;
        preOrder(current->leftChild, totalPoints, factor);
        preOrder(current->rightChild, totalPoints, factor);
    }
}




void CardTree::putCard (string pattern) {

    if (pattern=="Clubs" && !isTableFull()) {
        if (isTableEmpty())
            coverLeft(pattern);
        else
            coverRight(pattern);
    }

    else if (pattern=="Diamond" && !isTableEmpty()) {
        if (isTableFull()) {
            if (root->leftChild->points <= root->rightChild->points)
                coverLeft(pattern);
            else
                coverRight(pattern);
        }
        else
            coverLeft(pattern);
    }

    else if (pattern=="Heart" && isTableFull()) {
        int pointsToHeart = countPoints();
        coverBothToLeft();
        root->leftChild->points = pointsToHeart;
    }
    
}

int CardTree::countPoints() {
    int heartPoints=0;
    preOrder(root->leftChild, heartPoints, 1);
    preOrder(root->rightChild, heartPoints, -1);
    return heartPoints;
}

void CardTree::preOrderOnlyHeart(Card *current, int& totalPoints) {
    if (current) {
        if (current->pattern == "Heart")
            totalPoints += (current->points);
        preOrderOnlyHeart(current->leftChild, totalPoints);
        preOrderOnlyHeart(current->rightChild, totalPoints);
    }
}




int main() {

    int totalHeartPoints=0;
    string input;
    CardTree Game;

    while (cin >> input)
    {
        if (input != "Spade")
            Game.putCard(input);
        else
            break;
    }

    // Calculate total heart points
    Game.preOrderOnlyHeart(Game.getRoot(), totalHeartPoints);

    cout << totalHeartPoints << endl;
    

    return 0;
}