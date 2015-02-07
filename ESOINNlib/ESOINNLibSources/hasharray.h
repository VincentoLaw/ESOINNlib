#ifndef HASHARRAY_H
#define HASHARRAY_H
#include <list>
#include <algorithm>


template<class dataType>
class HashArray
{
private:
    int hash(int x){
        if (x < 0)
            x = -x;
        return x % arraySize;
    }

public:
    int arraySize;
    int currentSize;
    dataType * dataOffset;
    std::list<dataType *> * array;
    HashArray(int array_size)
    {
        currentSize = 0;
        arraySize = array_size;
        dataOffset = 0;
        array = new std::list<dataType *>[arraySize];
    }
    void push(dataType * data){
        if (!dataOffset){
            dataOffset = data;
        }
        array[hash(data - dataOffset)].push_back(data);
        currentSize++;
    }
    void remove(dataType *data){
        bool found = exist(data);
        if (found){
            array[hash(data - dataOffset)].remove(data);
            currentSize--;
        }
    }
    bool exist(dataType * data){
        return (std::find(array[hash(data - dataOffset)].begin(), array[hash(data - dataOffset)].end(), data) != array[hash(data - dataOffset)].end());
    }

    ~HashArray();
};

#endif // HASHARRAY_H
