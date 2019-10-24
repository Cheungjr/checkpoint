/**
 * file name: DictionaryTrie.hpp
 * author: Jiarun Zhang, Sizhe Qiu
 * userid:  jiz727, siq001
 * description:The class for a dictionary ADT,
 * implemented as multiway trie.
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:

    class TrieNode{
      public:
	TriNode * left;
	TriNode * mid;
	TriNode * right;
	//if acceptable
	bool state;
	unsigned int freq;
	char data;
	
	TrieNode(char data) :data(Data){
	  left = mid = right = nullptr;
	  state = false;
	  freq = 0;
	};

  /*
   * func name: getFreq()
   * description: get the freqency of the word
   * param:TrieNode* node - node representing last char of a word
   * return: 0 for not in struct, freqency otherwise
   */
  //int getFreq( TrieNode* node ){
  //  return freq;
  //}

  /**
   * func name: findHelper( string word )
   * description: find whether the word is stored in DictionaryTrie.
   * param: string word - the word to find.
   *	    curr - the ptr pointing to where to start the find
   * return true if find the word in the dic, false otherwise
   */
  bool DictionaryTrie::findHelper(string word, TrieNode* curr) const {
  
    int length = word.length();
    //get the char string
    char cstr[length + 1];
    strcpy(cstr, &word[0]);
	
    //find the anchor point
    while( cstr[0] != curr->data ){
      //goto the left child
      if( cstr[0] < curr->data && curr->left){
        curr = curr->left;
      }//go right
      else if( cstr[0] > curr->data && curr-> right ){
        curr = curr->right;
      }//not find
      else{ return false; }
    }//end of finding the anchor point
	
    // loop through each char
    for( int 1 = 0;  i < length - 1; i ++){ 
      if(cstr[i] == curr->data && curr->mid){
      //set curr to mid child go for next char
      curr = curr->mid;
      }
      if( cstr[0] < curr->data && curr->left){
        curr = curr->left;
      }//go right
      else if( cstr[0] > curr->data && curr-> right ){
        curr = curr->right;
      }//not find
      else{ return false; }
    } 
	  
    //find  if the word in dic
    return (curr->data == cstr[height-1] && curr->freq != 0);
  }
	/*
	 * func name: compare()
	 * description: helper method to compare the given char with data
	 * param: char input - the char to compare
	 * return: -1 for smaller, 0 for same, 1 for bigger
	 */
	//int compare(char input){
	//  this.
	//}
	
    };

    //helper method to delete nodes recursively.
    static void deleteAll( TrieNode* node ) {
      if(!root){ return; }
      if( node->left != nullptr ){ deleteAll( node->left ); }
      if( node->mid != nullptr ){ deleteAll( node->mid ); }
      if( node->right != nullptr ){ deleteAll( node->right ); }
      delete node;
    }

    //helper method for predict completion
    void completionHelper( TrieNode* node, string prefix,
	                                vector< pair<string,int> > &preComple ){
      //return case
      if(!node){ return; }

      //concate word, freq>0 means word exist, push into vector
      if( node->freq > 0 ){
        pair<string,int> predictPair( prefix, node->freq );

        preComple.push_back( predictPair );
      }
      string s;
      //recursion call to do DFS and concate the possible word
      if( node->left ){
	s = prefix + node->data;
        completionHelper( node->left, s, preComple );
      }
      if( node->right ){
	s = prefix + node->data;
        completionHelper( node->right, s, preComple );
      }
      if( node->mid ){
	s = prefix + node->data;
        completionHelper( node->mid, s, preComple );
      }

      }

    }//end completionHelper
    

    //compare method for pair<string,int>
    bool comparePair(const pair<int, int>&i, const pair<int, int>&j) {
      return i.second < j.second;
    }
  
    //root node of Dictionary.
    TrieNode* root;
      
    
  public:
    /* constructor */
    DictionaryTrie();

    /* insert method  */
    bool insert(string word, unsigned int freq);

    /* find method*/
    bool find(string word) const;

    /* predict completion */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Destructor of DictionaryTrie */
    ~DictionaryTrie()
};

#endif  // DICTIONARY_TRIE_HPP
