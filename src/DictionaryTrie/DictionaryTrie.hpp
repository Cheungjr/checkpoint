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
  
  /**
   * func name: findNode( )
   * description: find a "root" char DictionaryTrie.
   * param: char data - the data of the node to find.
   *	    curr - the ptr pointing to where to start the find
   *
   *	    overRide - if set to true, return all the "root"s
   * return: void
   */
  void findNode( char data, TrieNode* curr, vector<TrieNode*> &anchors, 
  						bool overrides ) const{
    //if first char is _, set override to T, push every node into vector
    if( overrides ){
      anchors.push_back(curr);
    }else if( curr->data == data ){
      anchors.push_back(curr);
    }
    
    if( curr->left ){
      findNode( data, curr->left, anchors, overrides );
    }
    if( curr->right ){
      findNode( data, curr->right, anchors, overrides );
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
    
  /**
   * func name: completionHelper( )
   * description: helper method for auto complete that recurse on each node.
   * param: node - the node curently at.
   *        prefix - the prefix string 
   *        precomple - the return vector
   *        first - if it is first node after the prefix ( edge case )
   * return: void
   */
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
      else predictPair = pair<string, int>( prefix+node->data, node->freq );
      preComple.push_back( predictPair );
    }
    string s = prefix;
    //recursion call to do DFS and concate the possible word
    //&& first for prefix's last char -> left/right child is actually not in
    //the dic
    if( node->left && !first && node != root){
      completionHelper( node->left, s, preComple, false );
    }
    if( node->right && !first && node != root){
      completionHelper( node->right, s, preComple, false );
    }
    if( node->mid ){
      if(!first) s = prefix + node->data;
      completionHelper( node->mid, s, preComple, false );
    }
       
  }//end completionHelper
    

  /**
   * func name: underscoreHelper( )
   * description: find whether the word is stored in DictionaryTrie. edge case 
   * of _xxx is handled in predictunderscore()
   * param: node - node currently at.
   *	    pattern - the pattern to find
   *	    index - index of the pattern
   *	    result - to store the possible result
   *	    flag - '_'
   *	    preUnderscore - vector stores the final results
   * return true if find the word in the dic, false otherwise
   */
  void underscoreHelper( TrieNode* node, string pattern, unsigned int index, 
  	string result, char flag, vector< pair<string, int> > &preUnderscore ){
    //safe return
    if( !node ) return;

    pair<string,int> predictPair;

    // if comes to the last of the node, return case
    if( index == pattern.length() - 1 ){
      if(node->data == pattern[index] && node->freq > 0){
        predictPair = pair<string, int>( result+node->data, node->freq );
        preUnderscore.push_back( predictPair );
      }
      //if the last char is an underscore, all nodes with >1 freq would work
      if( pattern[index] == flag){
        vector<TrieNode*> temp;
        findNode(pattern[index], node, temp, true );
	for( int i = 0; i < temp.size(); i ++ ){
	  TrieNode* curr = temp[i];
	  if( curr->freq > 0 ){
            predictPair = pair<string, int>( result+curr->data, curr->freq );
            preUnderscore.push_back( predictPair );
	  }
	}
      }
    }
    //normal case, traverse to mid child
    if( node->data == pattern[index] ){
      result = result + node->data;
      underscoreHelper( node->mid, pattern, index + 1, result, 
      						flag, preUnderscore );
    }//if looking at a flag, traverse down
    else if( pattern[index] == flag ){
      result = result + node->data;
      underscoreHelper( node->mid, pattern, index + 1, result, 
      						flag, preUnderscore );
    }//not fit, return
    else{ return; }

    //if the next pattern[index] is a '_', try all child
    if( index < pattern.length() - 1 && pattern[index + 1] == flag ){
      if( node->left ){
        result = result + node->data;
        underscoreHelper( node->left, pattern, index + 1, result, 
						flag, preUnderscore );
      }
      if( node->right ){
        result = result + node->data;
        underscoreHelper( node->right, pattern, index + 1, result, 
						flag, preUnderscore );
      }
    }

  }//end of underscore helper
    
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
