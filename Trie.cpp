#include <string>
#include <iostream>
#pragma once

using namespace std;

class TrieNode{
public:
    TrieNode *child[26];
    bool end;

    TrieNode(){
        end = 0;
        for(int i = 0;i < 26;++i){
            child[i] = nullptr;
        }
    }
};

class Trie{
private:
    TrieNode *root;
public:
    Trie(){
        root = new TrieNode();
    }

    void insert(string s){
        TrieNode *cur = root;
        for(char c : s){
            if(cur->child[c - 'a'] == nullptr){
                TrieNode *newnode = new TrieNode();
                cur->child[c - 'a'] = newnode;
            }
            cur = cur->child[c - 'a'];
        }
        cur->end = 1;
    }

    bool searchByWord(string s){
        TrieNode *cur = root;
        for(char c : s){
            if(cur->child[c - 'a'] == nullptr){
                return 0;
            }
            cur = cur->child[c - 'a'];
        }
        return cur->end;
    }
};
