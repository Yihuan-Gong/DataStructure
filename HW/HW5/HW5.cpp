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
    
    bool shouldBackward(Fruit& f) const
    {
        return f.hyperFeatures[featureIdx] < binThreshold;
    }
    void applyGradSlider(Fruit& f) const
    {
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
    GradBinHyperWeight *root;
    GradBinHyperWeight *prev, *current;

public:
    TreeGBHW() { root = new GradBinHyperWeight; }
    
    void assignRoot(Data data);
    void insert(Data data);
};



void TreeGBHW::assignRoot(Data data)
{
    root->featureIdx = data.featureIdx;
    root->gradSlider = data.gradSlider;
    root->binThreshold = data.binThreshold;
}

void TreeGBHW::insert(Data data)
{
    // Create a new node
    GradBinHyperWeight *newGradBinHyperWeight = new GradBinHyperWeight;
    newGradBinHyperWeight->featureIdx = data.featureIdx;
    newGradBinHyperWeight->gradSlider = data.gradSlider;
    newGradBinHyperWeight->binThreshold = data.binThreshold;

    // Find out the node to insert a new node
    // "prev" is the node we can insert a new node at below
    current = root;
    while (current)
    {
        prev = current;

        if (data.binThreshold < current->binThreshold)
            current = current->backwardContinuation;
        else
            current = current->forwardContinuation;  
    }  
     
    // Insert the new node below "prev"
    if (prev->binThreshold < data.binThreshold) {
        newGradBinHyperWeight->backwardContinuation = prev->backwardContinuation;
        prev->backwardContinuation = newGradBinHyperWeight;
    }
    else {
        newGradBinHyperWeight->forwardContinuation = prev->forwardContinuation;
        prev->forwardContinuation = newGradBinHyperWeight;
    }
}


int main() {

    string input;
    Fruit fruit;
    vector<Fruit> fruitArr;
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
            fruit.hyperFeatures.reserve(numHyperFeatures);
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
                fruitArr.push_back(fruit);
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

                cout << "Inserted node : " << data.featureIdx << " ";
                cout << data.gradSlider << " ";
                cout << data.binThreshold << "\n";
            }      
        }

        i++;
    }
    



    return 0;
}
