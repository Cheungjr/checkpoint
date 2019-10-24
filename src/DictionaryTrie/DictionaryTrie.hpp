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
#include <stdio.h>
#include <cstring>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:

    class TrieNode{
      public:
	TrieNode * left;
	TrieNode * mid;
	TrieNode * right;
	//if acceptable
	bool state;
	unsigned int freq;
	char data;
	
	TrieNode(char data) :data(data){
	  left = mid = right = nullptr;
	  state = false;
	  freq = 0;
	};

      
    };
  
  //root node of Dictionary.
  TrieNode * root;
  
  /**
   * func name: findHelper( string word )
   * description: find whether the word is stored in DictionaryTrie.
   * param: string word - the word to find.
   *	    curr - the ptr pointing to where to start the find
   * return true if find the word in the dic, false otherwise
   */
  bool findHelper(string word, TrieNode* curr) const {
  
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
    for( int i = 0;  i < length - 1; i ++){ 
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
    return (curr->data == cstr[length-1] && curr->freq != 0);
  }

    //helper method to delete nodes recursively.
    static void deleteAll( TrieNode* node ) {
      if(!node){ return; }
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

    }//end completionHelper
    

  
    
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
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
