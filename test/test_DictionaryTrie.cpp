
/**
 * file name: test_DictionaryTrie.cpp
 * author: Jiarun Zhang, Sizhe Qiu
 * userid:  jiz727, siq001
 * description:test methods in DictionaryTrie
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

//test insert function
TEST(DictTrieTests, INSERT__TEST_01) {
    DictionaryTrie dict;
    dict.insert("obama", 10 );
    ASSERT_EQ(dict.find("obama"), true );
}

//test insert a list of words and find
TEST(DictTrieTests, INSERT_TEST_02) {
    DictionaryTrie dict;

    dict.insert("make", 1 );
    dict.insert("fake", 2 );
    dict.insert("fate", 10 );
    dict.insert("fat", 3 );
    dict.insert("face", 6 );
    dict.insert("take", 5 );
    dict.insert("cake", 5 );
    ASSERT_EQ(dict.find("abrakadabra"), false);
    ASSERT_EQ(dict.find("make"), true);
    ASSERT_EQ(dict.find("mak"), false);//no mak in tree
    ASSERT_EQ(dict.find("cak"), false);//no cak in tree
    ASSERT_EQ(dict.find("tak"), false);//no tak in tree
    ASSERT_EQ(dict.find("fake"), true);
    ASSERT_EQ(dict.find("fate"), true);
    ASSERT_EQ(dict.find("fat"), true);
    ASSERT_EQ(dict.find("face"), true);
    ASSERT_EQ(dict.find("take"), true);
    ASSERT_EQ(dict.find("cake"), true);
}

//test the case that all nodes are added to left.
TEST(DictTrieTests, INSERT_ALL_LEFT) {
    DictionaryTrie dict;
    dict.insert("october",1);
    dict.insert("null",1);
    dict.insert("mother",1);
    dict.insert("height",1);
    dict.insert("google",1);
    dict.insert("forest",1);
    dict.insert("english",1);
    dict.insert("dog",1);

    ASSERT_EQ(dict.find("october"), true);
    ASSERT_EQ(dict.find("null"), true);
    ASSERT_EQ(dict.find("mother"), true);
    ASSERT_EQ(dict.find("height"), true);
    ASSERT_EQ(dict.find("google"), true);
    ASSERT_EQ(dict.find("forest"), true);
    ASSERT_EQ(dict.find("english"), true);
    ASSERT_EQ(dict.find("dog"), true);
}

//test the case that words are in upper
//and lower cases.
TEST(DictTrieTests, INSERT_UPPCASE) {
    DictionaryTrie dict;
    dict.insert( "MaKe", 5);
    dict.insert( "doG", 5);
    dict.insert( "GooglE", 5);
    dict.insert( "ForeSt", 5);
    dict.insert( "enGlish", 5);
    dict.insert( "EnglisH", 5);
    dict.insert( "MothEr", 5);
    dict.insert( "NulL", 5);
    dict.insert( "mother", 5);
    dict.insert( "doesn` t",9);
    

    ASSERT_EQ(dict.find("doG"), true);
    ASSERT_EQ(dict.find("dog"), false);
    ASSERT_EQ(dict.find("doesn` t"), true);
    ASSERT_EQ(dict.find("ForeSt"), true);
    ASSERT_EQ(dict.find("GooglE"), true);
    ASSERT_EQ(dict.find("NulL"), true);
}

//test inserting words are all in subsets
TEST(DictTrieTests, SUBSET_WORDS ) {
    DictionaryTrie dict;
    dict.insert("abcdefghijk",7);
    dict.insert("abcdefghij",7);
    dict.insert("abcdefghi",7);
    dict.insert("abcdefgh",7);
    dict.insert("abcdefg",7);
    dict.insert("abcdef",7);
    dict.insert("abcde",7);
    dict.insert("abcd",7);
    dict.insert("abc",7);


    ASSERT_EQ(dict.find("abc"), true);
    ASSERT_EQ(dict.find("abcde"), true);
    ASSERT_EQ(dict.find("abcdefg"), true);
    ASSERT_EQ(dict.find("abcdefghij"), true);
    ASSERT_EQ(dict.find("abcdefghi"), true);
    ASSERT_EQ(dict.find("abcdefghijk"), true);
}

//test autoCompletion function.
TEST(DictTrieTests, AUTOCOMPLE_TEST_01 ) {
    DictionaryTrie dict;
    vector<string> autoComplete;

    dict.insert("doesn`t",5);
    dict.insert("does want",6);
    dict.insert("does not",10);
    dict.insert("don`t",9);
    dict.insert("does nothing",8);
    dict.insert("doesdoes",11);
    dict.insert("does something",2);
    dict.insert("do not",7);
    dict.insert("donut",6);

    autoComplete = dict.predictCompletions("does",4);
    ASSERT_EQ(autoComplete.size(), 4 );//test vector size.

    ASSERT_EQ(autoComplete[0], "doesdoes" );
    ASSERT_EQ(autoComplete[1], "does not" );
    ASSERT_EQ(autoComplete[2], "does nothing" );
    ASSERT_EQ(autoComplete[3], "does want" );


}

//test autoComplete
//apple,5; add,6; delete,10; deer,6;demon,10; applet,10;apply,9;
TEST(DictTrieTests, AUTOCOMPLE_TEST_02) {
    DictionaryTrie dict;
    vector<string> autoComplete;

    dict.insert("apple",5);
    dict.insert("add",6);
    dict.insert("delete",10);
    dict.insert("deer",6);
    dict.insert("demon",10);
    dict.insert("applet",10);
    dict.insert("apply",9);

    
    autoComplete = dict.predictCompletions("app",4);

    ASSERT_EQ(autoComplete.size(), 3 );

    ASSERT_EQ(autoComplete[0], "applet" );
    ASSERT_EQ(autoComplete[1], "apply" );
    ASSERT_EQ(autoComplete[2], "apple" );
}


TEST(DictTrieTests, AUTOCOMPLE_TEST_03) {
    DictionaryTrie dict;
    vector<string> autoComplete;

    dict.insert("apfle",5);
    dict.insert("add",6);
    dict.insert("be",10);
    dict.insert("apfly",9);

    
    autoComplete = dict.predictCompletions("apf",4);
    ASSERT_EQ(dict.find("apfle"), true);
    ASSERT_EQ(autoComplete.size(), 2 );

    ASSERT_EQ(autoComplete[0], "apfly" );
    ASSERT_EQ(autoComplete[1], "apfle" );
}



TEST(DictTrieTests, AUTOCOMPLE_TEST_04) {
    DictionaryTrie dict;
    vector<string> autoComplete;

    dict.insert("apple",10);
    dict.insert("appendix",20);
    dict.insert("application",15);
    dict.insert("add",100);
    dict.insert("addiction", 50);
    dict.insert("app", 30);
    dict.insert("apply", 70);
    dict.insert("applaz", 55);
    dict.insert("applaa", 55);
    dict.insert("applac", 55);
    dict.insert("applaq", 55);

    
    autoComplete = dict.predictCompletions("app",20);

    ASSERT_EQ(autoComplete.size(), 9 );
}


//test for final submission
//same frequency predcit complete
TEST(DictTrieTests, AUTOCOMPLE_SAME_FREQ) {
    DictionaryTrie dict;
    vector<string> autoComplete;

    dict.insert("thatand",5);
    dict.insert("thatant",5);
    dict.insert("thatend",5);
    dict.insert("thatent",5);


    autoComplete = dict.predictCompletions("that",3);
    ASSERT_EQ( autoComplete.size(), 3);

    ASSERT_EQ(autoComplete[0], "thatand" );
    ASSERT_EQ(autoComplete[1], "thatant" );
    ASSERT_EQ(autoComplete[2], "thatend" );
}

//test predict underscore.
TEST(DictTrieTests, UNDERSCORE_01 ) {
    DictionaryTrie dict;
    vector<string> under_1;
    vector<string> under_2;

    dict.insert("door",10);
    dict.insert("deer",2);
    dict.insert("insect",5);
    dict.insert("insert",6);
    dict.insert("intern",7);


    under_1 = dict.predictUnderscores("d__r",2);
    under_2 = dict.predictUnderscores("in____",2);

    ASSERT_EQ( under_1.size(), 2);
    ASSERT_EQ( under_2.size(), 2);

    
    ASSERT_EQ( under_2[1], "insert");
    ASSERT_EQ( under_2[0], "intern");
    ASSERT_EQ( under_1[0], "door");
    ASSERT_EQ( under_1[1], "deer");

}

//___ple;end with sub word.
TEST(DictTrieTests, UNDERSCORE_02) {
    DictionaryTrie dict;
    vector<string> under;

    dict.insert("dipple",6);
    dict.insert("aapple",10);
    dict.insert("criple",8);
    dict.insert("nipple",9);
    dict.insert("temple",7);

    under = dict.predictUnderscores("___ple",3);
    ASSERT_EQ( under.size(), 3);
    ASSERT_EQ( under[0], "aapple");
    ASSERT_EQ( under[1], "nipple");
    ASSERT_EQ( under[2], "criple");

}

//test two under scores and alphabetical order.
//____lie__
TEST(DictTrieTests, TWO_UNDER) {
    DictionaryTrie dict;
    vector<string> under;
    vector<string> und; 

    dict.insert("loveliest",6);
    dict.insert("loneliest",6);
    dict.insert("unbelieve",4);
    dict.insert("resilient",5);
    dict.insert("ebullient",10);

    under = dict.predictUnderscores("____lie__",3);
    und = dict.predictUnderscores("____lie__",5);

    ASSERT_EQ( under[0], "ebullient");
    ASSERT_EQ( under[1], "loneliest");
    ASSERT_EQ( under[2], "loveliest");

    ASSERT_EQ( und[3], "resilient");
    ASSERT_EQ( und[4], "unbelieve");


}

//test three under scores
//__st_r____
TEST(DictTrieTests, THREE_UNDER) {
    DictionaryTrie dict;
    vector<string> under;

    dict.insert("historical",7);
    dict.insert("restartjob",9);
    dict.insert("dostirtank",6);

    under = dict.predictUnderscores("__st_r____",3);
    ASSERT_EQ( under[0], "restartjob");
    ASSERT_EQ( under[1], "historical");
    ASSERT_EQ( under[2], "dostirtank");


}





