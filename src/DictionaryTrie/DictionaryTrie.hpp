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
#include <queue>
#include <algorithm>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as ternary search tree.
 * TST can insert words that are not currently in the dic can do prediction
 * based on given prefix or pattern
 */
class DictionaryTrie {
  private:

    class TrieNode{
      public:
	TrieNode * left;
	TrieNode * mid;
	TrieNode * right;
	//if acceptable
	unsigned int freq;
	char data;
	int maxBelow;
	
	TrieNode(char data) :data(data){
	  left = mid = right = nullptr;
	  freq = 0;
	  maxBelow = 0;
	};
      
    };
  
  //root node of Dictionary.
  TrieNode * root;
    struct compareMin{
      bool operator()(const pair<string, int>&i, const pair<string, int>&j)const{
        if( i.second != j.second ){
	  return i.second > j.second;
        }
	return i.first < j.first;
      }
    }; 
    struct compareMinH{
      bool operator()( const int &i, const int &j)const{
        return (i > j);
      }
    };
  
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
  
  /**
   * func name: completionHelper( )
   * description: helper method for auto complete that recurse on each node.
   * param: node - the node curently at.
   *        prefix - the prefix string 
   *        precomple - the return vector
   *        first - if it is first node after the prefix ( edge case )
   * return: void
   */
    void completionH( TrieNode* node, string prefix,
    	priority_queue <pair<string,int>, vector<pair<string,int>>,compareMin> 
	&preComple, priority_queue <int, vector<int>, compareMinH> & maxList,
	                 bool first, int maxium, int numC ){

      if(!node) { return; }
      if(node->maxBelow < maxList.top()){ return; }

      //add next max into pq.
      //find the guess best n freq	
      if( node->left && !first){
	if(maxList.size() < numC){      
          maxList.push( node->left->maxBelow);
	}else{
          if( node->left->maxBelow > maxList.top() ){
	     maxList.pop();
	     maxList.push( node->left->maxBelow );
          }
	}
      }
      if( node->right && !first){
	if(maxList.size() < numC){      
          maxList.push( node->right->maxBelow);
	}else{
          if( node->right->maxBelow > maxList.top() ){
	     maxList.pop();
	     maxList.push( node->right->maxBelow );
          }
	}
      }

      pair<string,int> prePair;

      if( node->freq >0 ){
	if(first) { prePair= pair<string,int>( prefix, node->freq );}
	else{ prePair=pair<string,int> (prefix + node->data, node->freq );}

        if( preComple.size() >= numC ){ 
	  if( prePair.second > preComple.top().second ){
	    preComple.pop();
	    preComple.push( prePair );
          }else if( prePair.second == preComple.top().second &&
		    prePair.first < preComple.top().first){

	    preComple.pop();
	    preComple.push( prePair );
	  }
	}else{
        //push when queue not filled.
	preComple.push( prePair );
	}
      }

      string s = prefix;

      //get the best max for 3 children
      int leftMax;
      int rightMax;
      int midMax;
      if( node-> left){
        leftMax = node->left->maxBelow;
      }else{ leftMax = 0; }
      if( node-> right){
        rightMax = node->right->maxBelow;
      }else{ rightMax = 0; }
      if( node-> mid){
        midMax = node->mid->maxBelow;
      }else{ midMax = 0; }

      int bestMax = max(max(leftMax,rightMax),midMax);
      string str = s;
	
      //goto best max subtree first
      if(bestMax == leftMax){
        if( node->left){
          if(!first && node!=root){
	     completionH( node->left,s,preComple,maxList,false,maxium,numC);
          }
        }//recurse left	
	//find the second best from the rest of the two
	if( max(rightMax, midMax) == rightMax ){
	  //right is 2
          if( node->right){
            if(!first && node!=root){
	       completionH( node->right,s,preComple,maxList,false,maxium,numC);
            }
          }//recurse right
          if( node->mid){
	    if(!first) s = prefix + node->data;
            completionH( node->mid, s, preComple,maxList, false,maxium,numC );
          }//recurse mid
	}else{
          if( node->mid){
	    if(!first) str = prefix + node->data;
            completionH( node->mid, str, preComple,maxList, false,maxium,numC );
          }//recurse mid
          if( node->right){
            if(!first && node!=root){
	       completionH( node->right,s,preComple,maxList,false,maxium,numC);
            }
          }//recurse right
	}
      }else if(bestMax == rightMax){
        if( node->right){
          if(!first && node!=root){
	     completionH( node->right,s,preComple,maxList,false,maxium,numC);
          }
        }//recurse right
	if( max(leftMax, midMax) == leftMax ){
	  //left is 2
          if( node->left){
            if(!first && node!=root){
	       completionH( node->left,s,preComple,maxList,false,maxium,numC);
            }
	  }//recuese left
          if( node->mid){
	    if(!first) str = prefix + node->data;
            completionH( node->mid, str, preComple,maxList, false,maxium,numC );
          }//recurse mid
	}else{
          if( node->mid){
	    if(!first) str = prefix + node->data;
            completionH( node->mid, str, preComple,maxList, false,maxium,numC );
          }//recurse mid
          if( node->left){
            if(!first && node!=root){
	      completionH( node->left,s,preComple,maxList,false,maxium,numC);
            }
	  }//recuese left
	}
      }else{
        if( node->mid){
	  if(!first) str = prefix + node->data;
          completionH( node->mid, str, preComple,maxList, false,maxium,numC );
        }//recurse mid
	if( max(leftMax, rightMax) == leftMax ){
          if( node->left){
            if(!first && node!=root){
	      completionH( node->left,s,preComple,maxList,false,maxium,numC);
            }
	  }//recuese left
          if( node->right){
            if(!first && node!=root){
	      completionH( node->right,s,preComple,maxList,false,maxium,numC);
            }
          }//recurse right
	}else{
          if( node->right){
            if(!first && node!=root){
	      completionH( node->right,s,preComple,maxList,false,maxium,numC);
            }
          }//recurse right
          if( node->left){
            if(!first && node!=root){
	      completionH( node->left,s,preComple,maxList,false,maxium,numC);
            }
	  }//recuese left/*
	}
      }

    }
		    
  /**
   * func name: underscoreHelper( )
   * description: find whether the word is stored in DictionaryTrie.
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
      //if the and only if the first char is a flag
      if(pattern[index] == flag && node->freq > 0){
        predictPair = pair<string, int>( result+node->data, node->freq );
        preUnderscore.push_back( predictPair );
      }
      //go left and right to see if the accept node is on the side
      //if(index != 0){
        underscoreHelper(node->left, pattern, index, result, 
      						flag, preUnderscore );
        underscoreHelper(node->right, pattern, index, result, 
      						flag, preUnderscore );
      //}
      return;
    }
    //normal case, traverse to mid child
    if( node->data == pattern[index] ){
      underscoreHelper( node->mid, pattern, index + 1, result + node->data, 
      						flag, preUnderscore );
    }//if looking at a flag, traverse down
    else if( pattern[index] == flag ){
      underscoreHelper( node->mid, pattern, index + 1, result + node->data, 
      						flag, preUnderscore );
      underscoreHelper(node->left, pattern, index, result, 
     						flag, preUnderscore );
      underscoreHelper(node->right, pattern, index, result, 
      						flag, preUnderscore );
    }else{
      //if(index != 0 ){
        underscoreHelper(node->left, pattern, index, result, 
      						flag, preUnderscore );
        underscoreHelper(node->right, pattern, index, result, 
      						flag, preUnderscore );
    }//not fit, return

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

    /* predict certain pattern of words */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Destructor of DictionaryTrie */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
