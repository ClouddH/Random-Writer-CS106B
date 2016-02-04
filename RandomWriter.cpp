/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include<fstream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "map.h"
#include "vector.h"
#include"stack.h"
#include "random.h"
using namespace std;






Map<string,Vector<string> > analyzeSourceText(ifstream &infile,int order);
string findMostFrequentSeed(Map<string,Vector<string> > &markovModel);
string randomTextGeneration(Map<string,Vector<string> >&markovModel,string startingSeed);
string chooseNextChar(string currentSeed,Map<string,Vector<string> > &markovModel);

int main() {
    // [TODO: fill in the code]
    ifstream infile;
    Map<string,Vector<string> > markovModel;
    string startingSeed;
    string result;
    
    cout<<"filename: ";
    string filename=promptUserForFile(infile);
    int order=getInteger("Order: ");
    
    cout<<"processing file....."<<endl;
    
    
    markovModel=analyzeSourceText(infile,order);
    
    
    startingSeed=findMostFrequentSeed(markovModel);
    
    result=randomTextGeneration(markovModel,startingSeed);
    
    
    cout<< result<<endl;
   
   
    return 0;
}


Map<string,Vector<string> > analyzeSourceText(ifstream &infile,int order){
    
    Map<string,Vector<string> > markovModel;
    
    
    Vector<string> followingCharFrequence;
    
    char ch;
    while(infile.get(ch)){
        
        string currentSeed="";
        for(int i=0;i<order;i++){
            currentSeed+=ch;
            infile.get(ch);
        }
        if(!markovModel.containsKey(currentSeed)) {
            Vector<string> copy=followingCharFrequence;
            markovModel.put(currentSeed,copy);
        }
        string followedCharS="";
        followedCharS+=ch;
        
        markovModel[currentSeed].add(followedCharS);
        
        
        for(int i=0;i<order;i++){
            infile.unget();
        }

    }
    return markovModel;
}





string findMostFrequentSeed(Map<string, Vector<string> > & markovModel){
    
    int maxSize=0;
    string maxKey="";
    for( string key:markovModel){
        
        if(markovModel[key].size()>maxSize){
            maxSize=(markovModel[key]).size();
            maxKey=key;
        }
        
    }
    
    
    return maxKey;
}



string randomTextGeneration(Map<string,Vector<string> >&markoveModel,string startingSeed){
    
    string result;
    string currentSeed=startingSeed;
    string nextChar;
    
    
    
    result+=startingSeed;
    
    for(int i=0; i<2000-startingSeed.size();i++){
        
        if(!markoveModel.containsKey(currentSeed)) return result;
        
        string nextChar=chooseNextChar(currentSeed,markoveModel );
    
        result+=nextChar;
        
        currentSeed= currentSeed.substr(1)+nextChar;
    }
    
    return result;
}


string  chooseNextChar(string currentSeed,Map<string,Vector<string> > &markoveModel){
    
    string result;
    
    int randomRange=markoveModel[currentSeed].size()-1;
    
    int randomIndex= randomInteger(0, randomRange);
    
    result=markoveModel[currentSeed].get(randomIndex);
    
    return result;
    
    
    
}



