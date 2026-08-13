#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include "Cache.h"
#include <unordered_map>
#include <list>

using namespace std;

class LFUCache: public Cache{
private: 
    struct Node{
        int key; int value; int freq;
        Node(int k, int val, int f): key(k), value(val), freq(f) {};        
    };
    int capacity;
    int minFreq;

    // unordered_map<int, Node*> keyTable;
    // A better way is
    unordered_map<int, list<Node> ::iterator> keyTable;
    unordered_map<int, list<Node>> freqTable;

    void touch(int key){  //updates frequency and recency of a node when it is accessed
        auto it= keyTable[key];  //returns address of node in oldList
        int oldFreq= it->freq;
        int val= it->value;
        auto & oldList= freqTable[oldFreq];

        oldList.erase(it);

        freqTable[oldFreq+1].push_front(Node(key, val, oldFreq+1));

        keyTable[key] = freqTable[oldFreq+1].begin();

        if(oldList.empty()){
            freqTable.erase(oldFreq);
            if(minFreq== oldFreq){
                minFreq++;
            }
        }      
    }
public: 
    LFUCache(int cap): capacity(cap), minFreq(0) {};

    int get(int key){
        if(keyTable.find(key)== keyTable.end()){
            return -1;
        }

        int val= keyTable[key]->value;

        touch(key);        
        return val;
    }
    
    void put(int key, int val){
        if(capacity<=0){
            return;
        }

        if(keyTable.find(key)!= keyTable.end()){
            keyTable[key]->value= val;
            touch(key);
            return;
        }

        if(keyTable.size()>= capacity){
            auto &minList= freqTable[minFreq];
            int evictKey= minList.back().key;
            minList.pop_back();

            if(minList.empty()){
                freqTable.erase(minFreq);                
            }  
            keyTable.erase(evictKey);          
        }
//If the old key wasn't already existing, weiInsert it with its freq =1
        minFreq = 1;
        freqTable[1].push_front(Node(key, val, 1));
        keyTable[key] = freqTable[1].begin(); 
    }
};

#endif