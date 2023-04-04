#include <iostream>
#include <string>
#include <fstream>
using namespace std;


string simplifyTag(string tag) {

    // Function:
    //   input:  a tag (ex: "TR", "SILVER")
    //   output: a simplifed tag composed by only one letter (ex: "R", "S")

    string simpfiedTag;

    if (tag == "TL")
        simpfiedTag = "L"; 
    else if (tag == "TR")
        simpfiedTag = "R";
    else if (tag == "GOLD")
        simpfiedTag = "G";
    else if (tag == "SILVER") 
        simpfiedTag = "S";
    else if (tag == "MISS")
        simpfiedTag = "M";
    else  // The tag is useless
        simpfiedTag = " ";
    
    return simpfiedTag;
}

string simplifyInput(string input) {

    // Function
    //   input:   A string composed by many tags (ex: "TL\nTR\nSILVER\nTR\nMISS\n")
    //   output:  A simpified string that replace each tag with a letter, see simplifyTag

    string tag, simplifiedInput, simplifiedTag;
    int len;

    len = input.length();

    for (int i = 0; i < len; i++)
    {
        if (input[i]=='\n'){  // Detect the seperator of tags

            // Simplifies the tag (e.g. TL -> L; SILVER -> S)
            simplifiedTag = simplifyTag(tag); 

            if (simplifiedTag != " ")  // If the tag is not useless
                simplifiedInput.append(simplifiedTag);
            
            // After converting the tag into simplified tag,
            // Reset the tag
            tag = "";
        }
        else{
            // Get the tag from the input
            tag += input[i];
        }
    }
    return simplifiedInput;
}


void seperator(string simplifiedInput, string *group1, string *group2) {

    // simplifiedInput: A string with only "L", "R", "G", "S", "M"
    // group1:          A string with only "L", "R"
    // group2:          A string with only "G", "S", "M"
    // Function:        Seperate simplifiedInput into group1 and group2

    int len = simplifiedInput.length();

    for (int i = 0; i < len; i++)
    {
        if (simplifiedInput[i]=='L' || simplifiedInput[i]=='R')
            *group1 += simplifiedInput[i];
        else
            *group2 += simplifiedInput[i];
    }
}

void swap(char *a, char *b) {
    // Function: Swap the value between two input a and b
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


string reverse(string str) {

    // Function: 
    //   input:   any string
    //   output:  a reversed string

    int len;
    len = str.length();

    // Reversing string
    for (int i=0; i<len/2; i++) {
        swap(str[i], str[len-i-1]);
    }

    return str; 
}


string LRinverse(string LRstr) { 

    // Function:  
    //   input:  a group1 string (A string with only "L", "R")
    //   output: replace each char in the input string
    //           as "L" -> "R"; "R" -> "L"

    int len;
    len = LRstr.length();

    for (int i = 0; i < len; i++)
    {
        if (LRstr[i]=='L')
            LRstr[i]='R';
        else
            LRstr[i]='L';
    }
    return LRstr;
}

string getGroup1Out(string group1) {

    // Function
    //   input:   A group1 string, which is processed by 
    //            reverse() and LRinverse() before 
    //   output:  "L" -> "TL"; "R" -> "TR"; add "->" in between
    //   example: "RRLR" -> "TR->TR->TL->TR"

    string group1Out;
    int len = group1.length();

    for (int i = 0; i < len; i++) {
        if (group1[i]=='L')
            group1Out += "TL";
        else
            group1Out += "TR";
        
        if (i != len-1)
            group1Out += "->";
    }
    return group1Out;
}


int getPoints(string treasures) {

    // Function
    //   input:  A string of 3 treasures (ex: "GSS")
    //   output: The point you get from the input treasure set (ex" "GSS" -> 150)

    int len=3, gold=0;
    int points;

    for (int i = 0; i < len; i++)
    {
        // Count num of gold
        if (treasures[i] == 'G')
            gold += 1;
        
        // Calculate the point by num of gold
        switch (gold)
        {
        case 3:
            points = 500;
            break;
        case 2:
            points = 300;
            break;
        case 1:
            points = 150;
            break;
        default:
            points = 50;
            break;
        }
    }
    // cout << "Treasures = " << treasures << endl;
    // cout << "points = " << points << endl;
    return points;
}


int totalPoints(string group2, bool miss)  {

    // Functions
    // 
    //   input 
    //      group2:  A group2 string
    //      miss:    true,  if 4 treasures will be ignored after "MISS" tag
    //               false, no treasures will be ignored after "MISS" tag
    // 
    //   output:  
    //      points:  The total points you shold get 
    // 

    string treasures; // Store 3 treasures
    int len, delTreasure=0, points=0, tNum=0;
    len = group2.length();

    for (int i = 0; i < len; i++)
    {
        if (group2[i] == 'M' ) {
            if (miss)
                delTreasure = 4;  // Ignore the next four treasures
        }
        else {
            
            if (delTreasure == 0) { 
                // Add the treasure into treasure set
                treasures += group2[i];
                tNum += 1;

                // If the num of treasure equal 3, calculate the pts you get
                // and reset the string treasures
                if (tNum == 3) { 
                    points += getPoints(treasures);
                    tNum = 0;  // Reset tNum for next set of 3 treasures
                    treasures = "";
                }
            }
            else
                delTreasure --;  // One treasure has been ignored (if delTreasure>0)
        }
    }

    return points;
}

int main(void) {

    string input, text;
    string simplifiedInput;
    string group1; // Contains 'L' or 'R' ("TL" or "TR")
    string group2; // Contains 'G', 'S' or 'M' ("GOLD", "SILVER" or "MISS")
    string group1Out;
    int group2Out, group2OutM;

    // Take the input from OJ system
    while (cin >> text)
    {   
        input += text;
        input += '\n';
    }
    
    // Simplify the input as, e.g., ("TL\nTR\nGOLD" -> "LRG")
    simplifiedInput = simplifyInput(input);
    seperator(simplifiedInput, &group1, &group2);

    // For group 1 
    group1 = reverse(group1);   // Reverse the string: group1       (LRLL -> LLRL)
    group1 = LRinverse(group1); // Replace "L" -> "R"; "R" -> "L"   (LLRL -> RRLR)
    group1Out = getGroup1Out(group1);

    // For group 2
    group2Out  = totalPoints(group2, false);
    group2OutM = totalPoints(group2, true);

    cout << group1Out << "\n" << group2OutM << "\n" << group2Out << "\n";

    return 0;
}