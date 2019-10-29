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
 * The class for a dictionary ADT, implemented as ternary search tree.
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
   * func name: findH( string word )
   * description: find whether the word is stored in DictionaryTrie.
   * param: string word - the word to find.
   *	    curr - the ptr pointing to where to start the find
   *	    index index of char in word
   * return true if find the word in the dic, false otherwise
   */

  bool findH( string word, TrieNode* curr, int index) const{
    if( !curr ){ return false;}
    int i = index;
    if(word[i] < curr->data ){
	    curr = curr->left;
      return findH( word, curr, index );
    }else if( word[i] > curr->data ){
	    curr = curr->right;
      return findH( word,curr, index);
    }else{
      i++;
      if( i >= word.length() ){
	return ( curr->freq != 0 );
      }

      curr = curr->mid;
      return findH( word, curr, index + 1);
    }

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
	                     vector< pair<string,int> > &preComple,bool first ){
      //return case
      if(!node){ return; }
      
      pair<string,int> predictPair;
      //concate word, freq>0 means word exist, push into vector
      if( node->freq > 0 ){
        //cause curr is on the last node of prefix when first entering
	//should void the case of adding the last char twice
        if(first) predictPair = pair<string, int>( prefix, node->freq );
	else  predictPair = pair<string, int>( prefix+node->data, node->freq );

        preComple.push_back( predictPair );
      }
      string s = prefix;
      //recursion call to do DFS and concate the possible word
      //&& first for prefix's last char -> left/right child is actually not in
      //the dic
      if( node->left && !first && node != root){
      	//if(!first ) s = prefix + node->data;
        completionHelper( node->left, s, preComple, false );
      }
      if( node->right && !first && node != root){
	//if(!first) s = prefix + node->data;
        completionHelper( node->right, s, preComple, false );
      }
      if( node->mid ){
	if(!first) s = prefix + node->data;
        completionHelper( node->mid, s, preComple, false );
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
