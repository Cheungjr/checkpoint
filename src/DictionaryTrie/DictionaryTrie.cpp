/**
 * file name: DictionaryTrie.cpp
 * author: Jiarun Zhang, Sizhe Qiu
 * userid:  jiz727, siq001
 * description:The class for a dictionary ADT,
 * implemented as multiway trie.
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* constructor of DictionaryTrie */
DictionaryTrie::DictionaryTrie() {
  root = new TrieNode(0);
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
  if( find(word) || word == NULL){ return false;}

  TrieNode* temp = root;

  for( int i = 0; i < word.length(); i++){
    
    int index = word[i] - 'a'; 
    if (!temp->children[index]){
      temp->children[index] = new TrieNode(0);
    }

    temp = temp->children[index];
  }
  //the frequency of the word;
  temp->freq = freq;

  return true;
}

/**
 * func name: find( string word )
 * description: find whether the word is
 * stored in DictionaryTrie.
 *
 * param string word, the word to find.
 *
 * return bool
 */
bool DictionaryTrie::find(string word) const {
  TrieNode* temp = root
  
  for (int i = 0; i < word.length(); i++){ 
    int index = word[i] - 'a'; 
    if (!temp->children[index]) 
        return false; 
  
    temp = temp->children[index]; 
  } 
  
  return ( temp != NULL && temp->freq > 0); 	
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions){
    
    return {};
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}


/**
 * func name: ~DictionaryTrie()
 * description: delete all nodes.
 */
DictionaryTrie::~DictionaryTrie() {
  deleteAll( root );
}
