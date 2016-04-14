//
//  main.cpp
//  debuggingAssignment4
//
//  Created by Carlee Bettler on 4/13/16.
//  Copyright (c) 2016 Carlee Bettler. All rights reserved.
//

//
//  main.cpp
//  debuggingAssignment3
//
//  Created by Carlee Bettler on 4/12/16.
//  Copyright (c) 2016 Carlee Bettler. All rights reserved.
//

#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

class BTreeNode
{
public:
    char Data;
    BTreeNode *Lchild;  //r or R
    BTreeNode *Rchild;  //y or Y
};


/******************************************** CLASSES ADDED *****************************************************/
/************************************************************************************************
 / Class BTree. Left Child will be to R/r nodes. Right Child will be to Y/y nodes.
 ************************************************************************************************/
class BTree
{
public:
    BTreeNode *Root;
    BTree();
    bool add_word_to_tree(string word);
    bool is_word_in_tree(string word);
    int maxDepth(BTreeNode* node);
    void InorderR(BTreeNode* rt/*Root*/);
    string InorderR2(BTreeNode* rt);
    bool TestIfSearchCorrect();
private:
    bool add_node(BTreeNode *parent, char Data);
};

/// default constructor for the binary tree class
BTree::BTree()
{
    Root = new BTreeNode;
    Root->Data='-';
    Root->Lchild=Root->Rchild=NULL;
}

/// function will determine if the word is in the tree returning true, else returns false
bool BTree::is_word_in_tree(string word)
{
    int i;
    BTreeNode *ptr=Root;
    for(i=0;i<word.length();i++)
    {
        if(word[i]=='r' || word[i]=='R')
        {
            if(ptr->Lchild==NULL) return false;
            else ptr=ptr->Lchild;
        }
        else if(word[i]=='y' || word[i]=='Y')
        {
            if(ptr->Rchild==NULL) return false;
            else ptr=ptr->Rchild;
        }
        else return false;
    }
    return true;
}

/// when a new node needs to be added to the tree, this function is called by add_word_to_tree
bool BTree::add_node(BTreeNode *parent, char Data)
{
    BTreeNode *newNode = new BTreeNode;
    newNode->Data = Data;
    newNode->Lchild = newNode->Rchild = NULL;
    if(Data=='r' || Data=='R') {parent->Lchild=newNode; return true;}
    if(Data=='y' || Data=='Y') {parent->Rchild=newNode; return true;}
    return false;
}

/// function will add a word to the tree in the event that it is a new word
bool BTree::add_word_to_tree(string word)
{
    int i;
    BTreeNode *ptr=Root;
    for(i=0;i<word.length();i++)
    {
        if(word[i]=='r' || word[i]=='R')
        {
            if(ptr->Lchild==NULL)
            {
                //add new node
                add_node(ptr,word[i]);
                ptr=ptr->Lchild;
            }
            else ptr=ptr->Lchild;
        }
        else if(word[i]=='y' || word[i]=='Y')
        {
            if(ptr->Rchild==NULL)
            {
                //add new node
                add_node(ptr,word[i]);
                ptr=ptr->Rchild;
            }
            else ptr=ptr->Rchild;
        }
        else return false;
    }
    return true;
}

void BTree::InorderR(BTreeNode* rt)
{
    if(rt !=NULL)
    {
        InorderR(rt->Lchild);
        cout << rt->Data <<endl;
        InorderR(rt->Rchild);
    }
    
}


string BTree::InorderR2(BTreeNode* rt){
 string output = "";
 
 if(rt !=NULL)
 {
 InorderR2(rt->Lchild);
 cout<< rt->Data<<endl;
 InorderR2(rt->Rchild);
 }
 return output;
    
 }

bool BTree:: TestIfSearchCorrect(){
    
    vector<string> testVector;
    
    BTree *test = new BTree();
    
    testVector.push_back("yyy");
    testVector.push_back("rrr");
    testVector.push_back("ryry");

    
    for(int i=0;i<testVector.size();i++) {
        test->add_word_to_tree(testVector[i]);
    }
    
    for(int i = 0; i<testVector.size();i++) {
     if(test-> is_word_in_tree(testVector[i]) == 1) {
     continue;
     }
     else {
     cout<< "Your search function does not work correctly" <<endl;
     return 0;
     }
     
     }
     cout<<"Your search function works correctly"<<endl;
     return 1;

}



//build tree out of vector called words, search in teh vector called words
//take vector called words, trace to see if you can find each item in vector reads
//you get the yes and nos from last assignment, search the 35000 words

/*********************************************************************************************************************/

//functions supplied in assignment
bool get_words(char * file_name, vector<string> &w);
bool get_reads(char * file_name, vector<string> &r);
bool write_vector_to_screen(vector<string> v);
bool write_vector_to_file(vector<string> v, char * file_name);

int main()
{
    vector<string> words;
    char * genome_file_name="/Users/carleebettler/Documents/Comp 271/input1.txt";      //make certain to place this file in the correct folder. Do not change path.
    if(!get_words(genome_file_name,words))     //will get the words as binary
        return 1;
    
    //1. Create a tree --> transforming the vector of words into the tree
    BTree *b;
    b=new BTree;
    for(int i=0;i<words.size();i++)
        b->add_word_to_tree(words[i]);
    
    /** TEST 1 -- IS THE TREE CORRECTLY SET UP AND POPULATED **/
    
    
    vector<string> reads;
    char * reads_file_name="/Users/carleebettler/Documents/Comp 271/input2.txt";       //make certain to place this file in the correct folder. Do not change path.
    if(!get_reads(reads_file_name,reads))      //will get the reads as binary
        return 1;
    
    //2. for each read, map it through the tree. If it follows a path in the tree, this read belongs to this genome.
    bool *is_in=new bool [reads.size()];
    for(int i=0;i<reads.size();i++)
        is_in[i]=b->is_word_in_tree(reads[i]);
    
    /** TEST 2 -- IS THE TREE CORRECTLY SEARCHED **/
    
    
    delete is_in;
    
    
    vector<string> testVector;
    BTree *test = new BTree();
    
   
    testVector.push_back("rr");
    testVector.push_back("ry");
    
    for(int i=0;i<testVector.size();i++) {
        test->add_word_to_tree(testVector[i]);
    }
    
    test -> InorderR(test->Root);
    
    cout<<"You is equal Y or N?"<<endl;
    
    if (cin>>"Y") {
        cout<<"Your tree was set up correctly"<<endl;
    }
    else if(cin>>"N")
        cout<<Your tree was not set up correctly"<<endl;
    else
        cout<<"Invalid input"<<endl;
    
    
    test -> TestIfSearchCorrect();
    
}




/*******************************************************************************
 This function takes the genome file name to read and reads all overlapping
 words of size 10 that are present in the file and stores each word in a vector.
 The vector is passed to this function as a parameter -- by reference such
 that the calling function has access to the vector of words.
 *******************************************************************************/
bool get_words(char * file_name, vector<string> &w)
{
    int i,j;
    int len=0;
    ifstream in;
    in.open(file_name);
    if(!in.is_open()) {cout << "The genome file could not be opened. Check the location.\t"; return false;}
    
    char * word=new char [11];                              //this is a default, we'll be looking at words of size 10
    while(in.peek()!=EOF) {in>>word[0]; len++;}             //gets the length of the sequence
    in.clear(); in.close(); in.open(file_name);             //have to close and reopen file to reset filestream to beginning of file
    
    for(i=0; i<10; i++)
    {
        in>> word[i];
        if(word[i]<97) word[i]+=32;     //makes it lowercase
        if(word[i]=='a' || word[i]== 'g') word[i]='r';  //purine
        else word[i]='y';   //pyrimidine
    }
    word[10]='\0';
    w.push_back(word);
    for(i=1; i<(len-10-1); i++)   //read until the end of the file
    {
        //shift
        for(j=0; j<9; j++) word[j]=word[j+1];
        in>> word[9];
        if(word[9]<97) word[9]+=32;     //makes it lowercase
        if(word[9]=='a' || word[9]== 'g') word[9]='r';  //purine
        else word[9]='y';   //pyrimidine
        word[10]='\0';
        //strcpy(w[i],word);
        //cout << i << "\t" << word << endl; cout.flush();
        w.push_back(word);
    }
    in.clear(); in.close();
    
    return true;
}

/*******************************************************************************
 This function takes the reads file name to read and reads each individual word
 in the file and stores each word in a vector.
 The vector is passed to this function as a parameter -- by reference such
 that the calling function has access to the vector of words.
 *******************************************************************************/
bool get_reads(char * file_name, vector<string> &r)
{
    int i;
    ifstream in;
    in.open(file_name);
    if(!in.is_open()) {cout << "The read file could not be opened. Check the location.\t"; return false;}
    
    char * word=new char [20];                              //this is a default, we'll be looking at words of size 10
    
    while(in.peek()!=EOF)
    {
        in.getline(word,20,'\n');
        for(i=0; i<10; i++) {if(word[i]<97) word[i]+=32;}     //makes it lowercase
        for(i=0; i<10; i++)
        {
            if(word[i]=='a' || word[i]== 'g') word[i]='r';  //purine
            else word[i]='y';   //pyrimidine
        }
        r.push_back(word);
    }
    in.clear(); in.close();
    delete word;
    return true;
}

bool write_vector_to_screen(vector<string> v)
{
    int i;
    for(i=0; i<v.size(); i++)
        cout << v[i] << endl;
    return true;
}

bool write_vector_to_file(vector<string> v, char * file_name)
{
    ofstream out;
    out.open(file_name);
    int i;
    for(i=0; i<v.size(); i++)
        out << v[i] << endl;
    out.clear();
    out.close();
    return true;
}




