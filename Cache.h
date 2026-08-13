#ifndef CACHE_H
#define CACHE_H

// Abstract Base Class / Interface
class Cache {
public:
    virtual void put(int key, int value) = 0;
    virtual int get(int key) = 0;
    virtual ~Cache() {} // Virtual destructor for proper memory cleanup
};

#endif