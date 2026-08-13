#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "Cache.h"
#include <unordered_map>
#include<iterator>
#include <list>
using namespace std;

class LRUCache: public Cache{

private:
    int capacity;
    list<pair<int,int>> cache;
    unordered_map<int, list<pair<int,int>> ::iterator> map;

public:
    LRUCache(int cap){
        this->capacity= cap;
    }

    int get(int key){
        if(map.find(key)== map.end()){
            return -1;
        }

        auto it= map[key];
        int value= it->second;
        cache.erase(it);
        cache.push_front({key, value});
        map[key]= cache.begin();

        return value;
    }

    void put(int key, int value){
        if(map.find(key)!= map.end()){
            cache.erase(map[key]);
        }

        cache.push_front({key, value});
        map[key]= cache.begin();

        if(cache.size()>capacity){
            auto last= cache.end();
            map.erase(last->first);
            cache.pop_back();
        }
    }
};

#endif