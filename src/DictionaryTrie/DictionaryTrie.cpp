/**
 * file name: DictionaryTrie.cpp
 * author: Jiarun Zhang, Sizhe Qiu
 * userid:  jiz727, siq001
 * description:The class for a dictionary ADT,
 * implemented as multiway trie.
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/* constructor of DictionaryTrie */
DictionaryTrie::DictionaryTrie() {
  this->root = nullptr;
}

/**
 * func name: insert( string word, unsigned int freq )
 * description: insert word into DictionaryTrie
 *
 * param string word, the word to insert.
 * param unsigned int freq, frequency of the word.
 *
 * return bool
 */
bool DictionaryTrie::insert(string word, unsigned int freq) {
  //if word already existed or null, return false.
  if( word.empty() || find(word) ){ return false; }
  if( !root ) {
    unsigned char c = word[0];
    root = new TrieNode(c);
    TrieNode* curr = root;
    for( int i = 1; i < word.length(); i++ ){
      unsigned char a = word[i];
      curr->mid = new TrieNode(a);
      curr= curr->mid;
    }
    curr->freq++;
    return true;
  }

  TrieNode* curr = root;
  int i = 0;
  while( curr&& i < word.length() ){
    char s = word[i];
    if( curr->data < s ){
      if(! curr->right ){
	curr->right = new TrieNode(s);
	curr = curr->right;
      }else{
	curr = curr->right;
      }
    }else if( curr->data > s){
      if(!curr->left){
	curr->left = new TrieNode(s);
	curr = curr->left;
      }else{
	curr = curr->left;
      }
    }else{
      if( i == word.length() - 1 ){
	curr->freq++;
	return true;
      }
      if( curr->mid){
	curr=curr->mid;
	i++;
      }else{
	i++;
	s=word[i];
	curr->mid = new TrieNode(s);
	curr = curr->mid;
      }
    }
  }//end while


  return false;
}

/**
 * func name: find( string word )
 * description: find whether the word is
 * stored in DictionaryTrie.
 *
 * param string word, the word to find.
 *
 * return true if find the word in the dic, false otherwise
 */
bool DictionaryTrie::find(string word) const {
  
  if( word.empty() ){ return false; }
  if( root == nullptr ){ return false; }
  TrieNode* curr = root;
  return findH(word, curr, 0);
}
    
//helper method to compare method for pair<string,int>
bool comparePair(const pair<string, int>&i, const pair<string, int>&j) {
  return i.second < j.second;
}


/**
 * func name:predictCompletions( string prefix,
 *                    unsigned int numCompletions )
 *
 * description: find whether the word is
 *
 * param string prefix, the prefix to predict complete word.
 *
 * param unsigned int numCompletions number of
 *   words stored in predict completion list.
 *
 * return vector<string>
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions){
  TrieNode* curr = root;
  TrieNode* anchor;
  vector<string> predict;//the list of completions to return.
  int length = prefix.length();
  int i = 0;
  if( prefix.empty() || root == nullptr ){ return predict; }
  
  while( curr && i < length){
    if(prefix[i] < curr->data){
      if(!curr->left){ return predict; }
      curr = curr->left;
    }
    else if(prefix[i] > curr->data){
      if(!curr->right){ return predict; }
      curr = curr->right;
    }
    else{
      if(i == length -1) { 
        anchor = curr; 
	break;
      }
      curr = curr->mid;
      i++;
    }
  }
  if(i >= length) { return predict; }

  vector<pair<string,int>> compleList; 
  completionHelper( anchor, prefix, compleList, true); 

  //sort the compleList
  sort( compleList.begin(), compleList.end(), comparePair );
  //push most frequent words into the list.
  if( compleList.size() < numCompletions ){
    for( int i = 0; i < compleList.size(); i++ ){
      predict.push_back( compleList[i].first );
    }
  }else{
    for( int i = 0; i < numCompletions; i ++ ){
      predict.push_back( compleList[i].first );
    } 
  }
  string temp;
  for(int i = 0; i < predict.size()/2; i ++){
	  temp = predict[i];
	 predict[i] = predict[predict.size()-i-1];
	predict[predict.size()-i-1] = temp;
  }	
  return predict;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    vector<string> preUnderscore;

    return preUnderscore;
}


/**
 * func name: ~DictionaryTrie()
 * description: delete all nodes.
 */
DictionaryTrie::~DictionaryTrie() {
  deleteAll( root );
}
