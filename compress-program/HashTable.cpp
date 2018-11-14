using namespace std;
#include <sstream>

enum EntryType { ACTIVE, EMPTY, DELETED };
template<typename K, typename V>
class HashNode
{
    public:
    V value;
    K key;
    EntryType info;
    //Constructor of hashnode 
	HashNode(EntryType i = EMPTY)
    {
		info = i;
    }
    HashNode(K key, V value, EntryType i = EMPTY)
    {
		info = i;
        this->value = value;
        this->key = key;
    }
};


template<typename K, typename V>
 
//Our own Hashmap class
class HashMap
{
    //hash element array
    HashNode<K,V> **arr;
    int capacity;
    //current size
    int size;
    //dummy node
    HashNode<K,V> *dummy;
    public:
    HashMap()
    {
        //Initial capacity of hash array
        capacity = 4095; //As given in homework pdf
        size=0;
        arr = new HashNode<K,V>*[capacity];
         
        //Initialise all elements of array as NULL
        for(int i=0 ; i < capacity ; i++)
            arr[i] = NULL;
         
        //dummy node with value DELETED
        dummy = new HashNode<K,V>(DELETED);
    }
    // This implements hash function to find index
    // for a key
    int hashCode(string key)
    {
		if(key.length()==1)
		{
			int x = int(key[0]);
			if(x<0)
			{
				int y = x;
				x = x -x;
				x += -y;
				return x;
			}
			else
			return x;
		}
		    else
				return 256;
    }
    //Function to add key value pair
    void insertNode(K key, V value)
    {
        HashNode<K,V> *temp = new HashNode<K,V>(key, value);
         
        // Apply hash function to find index for given key
        int hashIndex = hashCode(key);
         
        //find next free space 
        while(arr[hashIndex] != NULL && arr[hashIndex]->value != value
			&& arr[hashIndex]->info != DELETED)
        {
            hashIndex++;
            hashIndex %= capacity;
        }
         
        //if new node to be inserted increase the current size
		if(arr[hashIndex] == NULL)
            size++;
        arr[hashIndex] = temp;
    }
	void setCode(K key, V value)
	{
			 int hashIndex = hashCode(key);        
			arr[hashIndex]->value = value;
    }
     
    //Function to delete a key value pair
    V deleteNode(int key)
    {
        // Apply hash function to find index for given key
        int hashIndex = hashCode(key);
         
        //finding the node with given key
        while(arr[hashIndex] != NULL)
        {
            //if node found
            if(arr[hashIndex]->key == key)
            {
                HashNode<K,V> *temp = arr[hashIndex];
                 
                //Insert dummy node here for further use
                arr[hashIndex] = dummy;
                 
                // Reduce size
                size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;
 
        }
         
        //If not found return null
        return NULL;
    }
     
    //Function to search the value for a given key
    V get(K key)
    {
        // Apply hash function to find index for given key
        int hashIndex = hashCode(key);
 
        //finding the node with given key   
        while(arr[hashIndex] != NULL)
        {
            //if node found return its value
            if(arr[hashIndex]->key == key)
                return arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= capacity;
        }
         
        //If not found return null
        return NULL;
    }

	V getWithIndex(int index)
    {
        return arr[index];
    }
     

    //Return current size 
    int sizeofMap()
    {
        return size;
    }
     
    //Return true if size is 0
    bool isEmpty()
    {
        return size == 0;
    }
     bool doesExist(K GivenKey)
    {
		for(int i=0 ; i<capacity; i++)
        {
			if(arr[i] != NULL && arr[i]->info != DELETED)
			{
				if(arr[i]->key == GivenKey)
					return true;
			}
        }
		return false;
    }
    //Function to display the stored key value pairs
    void display()
    {
        for(int i=0 ; i<capacity ; i++)
        {
			if(arr[i] != NULL && arr[i]->info != DELETED)
                cout << "index = " << i
				<< " code= " << arr[i]->value
				<< " key = " << arr[i]->key
                    << endl;
        }
    }
};
 