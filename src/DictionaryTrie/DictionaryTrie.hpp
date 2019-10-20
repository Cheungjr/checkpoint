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
    // TODO: add private members and helper methods here
    const int ALP_SIZE = 26;

    class TrieNode{
      public:
	int freq;
	int numChild;
	struct TrieNode* children[ ALP_SIZE ];

	TrieNode( int freq ):freq(freq){
	  
	  for( int i = 0; i < ALP_SIZE; i++){
	    children[i] = nullptr;
          }
          numChild = 0;
	}//end constructor of TrieNode
    };

    //root node of Dictionary.
    TrieNode* root;
      
    //helper method to delete nodes recursively.
    static void deleteAll( TrieNode* node ) {
      if(node != nullptr && node->numChild == 0 ){
        delete node;
      }else{
	for( int i = 0; i < ALP_SIZE; i++){
	  deleteAll( node->children[i] );
        }
      }
    }

    //helper method for predict completion
    void completionHelper( TrieNode* node, string prefix,
	                                  vector< pair<string,int> > &preComple ){
      if( node->freq > 0 ){
        pair<string,int> predictPair( prefix, node->freq );

        preComple.push_back( predictPair );
      }
      
      for( int i = 0; i < ALP_SIZE; i ++ ){
        if( node->children[i] ){
	  string s = prefix + (char)('a'+i);
          completionHelper( node->children[i], s, preComple );
	}

      }



    }//end completionHelper
    

    //compare method for pair<string,int>
    bool comparePair(const pair<int, int>&i, const pair<int, int>&j) {
      return i.second < j.second;
    }
  
    
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
