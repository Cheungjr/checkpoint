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
#include <csstring>

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


  int length = word.length();
  //get the char string
  char cstr[length + 1];
  strcpy(cstr, &word[0]);
  
  TrieNode* curr = nullptr;
 // TrieNode* temp = nullptr;
  
  //if the tree is empty
  if(root == nullptr){
    //set the root;
    root = new TrieNode(cstr[0]);
    curr = root;
    //build the tri
    for(int i = 1; i < length; i++){
      curr->mid = new TrieNode(cstr[i]);
      curr = curr->mid;
    }
  }else{
    
    //get the curr
    curr = root;
   // temp = curr;
    for( int i = 0; i < length; i++ ){
      //if char == node->data goto mid child
      if(cstr[i] == curr->data){
        //if the mid child is empty, insert all, break the i-loop, case x
        if(curr->mid == nullptr){ 
	  for(int j = i+1; j < length; j++){
	    curr->mid = new TrieNode(cstr[j]);
	    curr = curr->mid;
	  }
	  break;
	}//mid child not empty, update curr, goto next i-loop
	else{
	  curr = curr->mid;
	}
      }//goto left
      else if(cstr[i] < curr->data){
        if( curr->left == nullptr ){
	  curr->left = new TrieNode(cstr[i]);
	  curr = curr->left;
	  //let i loop go through [i] one more time to enter case x
	  i --;
	}//not empy, traverse left
	else{
	  curr = curr->left;
	}
      }//goto right
      else{
        if( curr->right == nullptr ){
	  curr->right = new TrieNode(cstr[i]);
	  curr = curr->right;
	  //let i loop go through [i] one more time to enter case x
	  i --;
	}//not empy, traverse left
	else{
	  curr = curr->right;
	}
      }
    }//end of i=loop
  }
  //set frequency at the end
  curr->freq = freq;

  return true;
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
  return findHelper(word, curr);
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
  vector<string> predict;//the list of completions to return.
  if( prefix.empty() || root == nullptr ){ return predict; }

  TriNode* curr = root;
  // if the prefix not find in dic
  if( findHelper(prefix, curr) == false ){
    return predict;
  }else{
    vector<pair<string,int>> compleList 
    completionHelper( temp, prefix, compleList); 

    //sort the compleList
    sort( compleList.begin(), compleList.end(), comparePair );
    //push most frequent words into the list.
    if( compleList.size() < numCompletions ){
      for( int i = 0; i < compleList.size(); i++ ){
	preComple.push_back( compleList[i].first );
      }
    }else{
      for( int i = 0; i < numCompletions; i ++ ){
	preComple.push_back( compleList[i].first );
      } 
    }

    return preComplete;
  }
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    //vector<string> preUnderscore;

    return {};
}


/**
 * func name: ~DictionaryTrie()
 * description: delete all nodes.
 */
DictionaryTrie::~DictionaryTrie() {
  deleteAll( root );
}
