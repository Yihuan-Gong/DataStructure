#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;


struct Fruit {
    std::string      name;
    std::vector<int> hyperFeatures;
};

struct GradBinHyperWeight {
    int                featureIdx;
    double             gradSlider;
    int                binThreshold;
    GradBinHyperWeight *backwardContinuation = nullptr;
    GradBinHyperWeight *forwardContinuation = nullptr;
    
    bool isItem = false;
    string fruitName;
    int usedFeatrue;
    
    bool shouldBackward(Fruit& f) const
    {
        return f.hyperFeatures[featureIdx] < binThreshold;
    }
    void applyGradSlider(Fruit& f) const
    {
        // cout << "binThreshold = " << binThreshold << endl;
        // cout << "featureIdx = " << featureIdx << endl;
        // cout << "f.name = " << f.name << endl;
        // cout << "f.hyperFeatures[featureIdx] = " << f.hyperFeatures[featureIdx] << endl;
        f.hyperFeatures[featureIdx] = (int) ((double) f.hyperFeatures[featureIdx] * gradSlider);
    }
};

struct Data {
    int                featureIdx;
    double             gradSlider;
    int                binThreshold;
};


class TreeGBHW
{
private:
    int nodes;
    GradBinHyperWeight *root;
    GradBinHyperWeight *prev, *current;
    vector<GradBinHyperWeight*> ArrTree;

public:
    TreeGBHW();
    
    void assignRoot(Data data);
    void insert(Data data);
    void HyperLearning(vector<Fruit>& fruitInputArr);
    void visit(GradBinHyperWeight *node);
    void midOrder(GradBinHyperWeight *current);
    GradBinHyperWeight* createLinkListTree(int i);
    GradBinHyperWeight* getRoot() { return root; }
};


TreeGBHW::TreeGBHW()
{
    GradBinHyperWeight *header = new GradBinHyperWeight;

    ArrTree.push_back(header);
    nodes = 0;
}

void TreeGBHW::assignRoot(Data data)
{
    root = new GradBinHyperWeight;
    root->featureIdx = data.featureIdx;
    root->gradSlider = data.gradSlider;
    root->binThreshold = data.binThreshold;

    ArrTree.push_back(root);
    nodes = 1;
}

void TreeGBHW::insert(Data data)
{
    // Create a new node
    GradBinHyperWeight *newGradBinHyperWeight = new GradBinHyperWeight;
    newGradBinHyperWeight->featureIdx = data.featureIdx;
    newGradBinHyperWeight->gradSlider = data.gradSlider;
    newGradBinHyperWeight->binThreshold = data.binThreshold;

    // Add the new node to the tree
    ArrTree.push_back(newGradBinHyperWeight);
    nodes++;

    // // Find out the node to insert a new node
    // // "prev" is the node we can insert a new node at below
    // current = root;
    // while (current)
    // {
    //     prev = current;

    //     if (data.binThreshold < current->binThreshold)
    //         current = current->backwardContinuation;
    //     else
    //         current = current->forwardContinuation;  
    // }  
     
    // // Insert the new node below "prev"
    // if (data.binThreshold < prev->binThreshold) {
    //     newGradBinHyperWeight->backwardContinuation = prev->backwardContinuation;
    //     prev->backwardContinuation = newGradBinHyperWeight;
    // }
    // else {
    //     newGradBinHyperWeight->forwardContinuation = prev->forwardContinuation;
    //     prev->forwardContinuation = newGradBinHyperWeight;
    // }

}

GradBinHyperWeight* TreeGBHW::createLinkListTree(int i) 
{
    if (i > nodes) 
        return nullptr;

    ArrTree[i]->backwardContinuation = createLinkListTree(2*i);
    ArrTree[i]->forwardContinuation  = createLinkListTree(2*i+1);

    return ArrTree[i];
}



void TreeGBHW::HyperLearning(vector<Fruit>& fruitInputArr)
{
    int feature;

    for (int i = 0; i < fruitInputArr.size(); i++)
    {
        // Reach the leafe
        current = root;
        while (current) {
            prev = current;

            // Apply gradient slide
            // cout << "at i = " << i << endl; // Debug
            // cout << "fruitInputArr[i].name             = " << fruitInputArr[i].name << endl;
            // cout << "fruitInputArr[i].hyperFeatures[0] = " << fruitInputArr[i].hyperFeatures[0] << endl;
            current->applyGradSlider( fruitInputArr[i] );
            feature = fruitInputArr[i].hyperFeatures[current->featureIdx];
            
            // Bin classifier
            if (feature < current->binThreshold) 
                current = current->backwardContinuation;
            else
                current = current->forwardContinuation;
        }

        // Create a new node under that leafe
        GradBinHyperWeight *newItem = new GradBinHyperWeight;
        newItem->isItem      = true;
        newItem->fruitName   = fruitInputArr[i].name;
        newItem->usedFeatrue = feature;

        if (feature < prev->binThreshold) {
            newItem->backwardContinuation = prev->backwardContinuation;
            prev->backwardContinuation = newItem;
        }
        else {
            newItem->forwardContinuation = prev->forwardContinuation;
            prev->forwardContinuation = newItem;
        }        
    }
}


void TreeGBHW::visit(GradBinHyperWeight *node) 
{
    if (node->isItem) {
        cout << node->fruitName << " ";
        cout << node->usedFeatrue << "\n";
    }

    // cout << node->binThreshold << "  ";
}


void TreeGBHW::midOrder(GradBinHyperWeight *current) 
{
    if (current) {
        midOrder(current->backwardContinuation);
        visit(current);
        midOrder(current->forwardContinuation);
    }
}



int main() {

    string input;
    Fruit fruit;
    vector<Fruit> fruitInputArr;
    Data data;
    TreeGBHW Hyper;
    int numFruit, numHyperFeatures;
    int numGBHW; // Number of GradBinHyperWeight
    bool assignRoot = true;
    int i=1;

    while (cin >> input)
    {
        if (i==1) {
            numFruit = stoi(input);
        }  
        else if (i==2) {
            numHyperFeatures = stoi(input);
            fruit.hyperFeatures.resize(numHyperFeatures);
        }
        else if ((i-3)/(numHyperFeatures+1) < numFruit)  // Construct the fruit array
        {
            int index = (i-3)%(numHyperFeatures+1);

            /* index = 0  : fruit.name
               index = 1  : fruit.hyperFeatures[0]
               index = 2  : fruit.hyperFeatures[1]
               ...
               index = numHyperFeatures : fruit.hyperFeatures[numHyperFeatures-1]
            */
            
            if ( index == 0 ) 
                fruit.name = input;
            else
                fruit.hyperFeatures[index-1] = stoi(input);
            
            // Fruit setting finished, so push the fruit to fruit array
            if ( index == numHyperFeatures )
                fruitInputArr.push_back(fruit);
        }
        else 
        {
            int index = i - (2 + (numHyperFeatures+1)*numFruit) - 2;

            if (index == -1)
                numGBHW = stoi(input);
            else if (index%numGBHW == 0)
                data.featureIdx = stoi(input);
            else if (index%numGBHW == 1)
                data.gradSlider = stod(input);
            else 
            {
                data.binThreshold = stoi(input);

                // Data input completed, so construct GBHW Tree
                if (assignRoot) {
                    Hyper.assignRoot(data);
                    assignRoot = false;
                }
                else 
                    Hyper.insert(data);

                // Test
                // cout << "Inserted node : " << data.featureIdx << " ";
                // cout << data.gradSlider << " ";
                // cout << data.binThreshold << "\n";
            }      
        }
        i++;
    }
    
    Hyper.createLinkListTree(1);
    Hyper.HyperLearning(fruitInputArr);
    Hyper.midOrder(Hyper.getRoot());

    return 0;
}
