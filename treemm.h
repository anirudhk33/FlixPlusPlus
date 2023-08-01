#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
#include <string>
#include <vector>



template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
    public:
        Iterator():m_size(0)
        {}
        
        Iterator(typename std::vector<ValueType>::iterator itr, int size):m_itr(itr),m_size(size)
        {}

        ValueType& get_value() const
        {
            return *m_itr;
        }

//        Validity is tracked by the size of the vector whose iterator is passed in
        bool is_valid() const
        {
          return m_size>0;
        }

        void advance()
        {
            if(m_size>0){
                m_itr++;
                m_size--;
            }
        }

        private:
        typename std::vector<ValueType>::iterator m_itr;
        int m_size;
  };

    TreeMultimap():head(nullptr)
    {}

    ~TreeMultimap()
    {
        demolishTree(head);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
//        Note that key, value is not passed by reference, therefore, making a copy
        insertHelper(key, value);
    }
    
    Iterator find(const KeyType& key) const
    {
        if(head == nullptr)
        {
            return Iterator();
        }
//        Helper find function enables recursion
        return find(key, head);
    }
    
  private:
    
    struct Node{
        Node(const KeyType& key, const ValueType& value):m_key(key),rightChild(nullptr),leftChild(nullptr)
        {
            values.push_back(value);
        }
        KeyType m_key;
        Node* rightChild;
        Node* leftChild;
        std::vector<ValueType> values;
    };
    
    
    void insertHelper(const KeyType key, const ValueType value)
    {
        if(head == nullptr){
            head = new Node(key, value);
            return;
        }
//        Simple BST Insert Algorithm
        Node* cur = head;
        for(;;){
            if(key < cur->m_key){
                if(cur->leftChild!=nullptr){
                    cur = cur->leftChild;
                }
                else{
                    cur->leftChild = new Node(key,value);
                    return;
                }
            }
            if(key > cur->m_key){
                if(cur->rightChild!=nullptr){
                    cur = cur->rightChild;
                }
                else{
                    cur->rightChild = new Node(key,value);
                    return;
                }
            }
            if(key == cur->m_key){
                cur->values.push_back(value);
                return;
            }
        }
    }
    
    Iterator find(const KeyType& key, Node* ptr) const
    {
        if(ptr == nullptr) return Iterator();
        
//        returns Iterator with two arguments: second argument helps check validity of Iterator
        if(key == ptr->m_key) return Iterator(ptr->values.begin(), ptr->values.size());
        
        if(key < ptr->m_key)
        {
            return find(key, ptr->leftChild);
        }
        else
        {
            return find(key, ptr->rightChild);
        }
    }
    
// Recursive deletion of tree
    void demolishTree(Node* node)
    {
        if(node == nullptr) return;
        demolishTree(node->leftChild);
        demolishTree(node->rightChild);
        delete node;
    }
    Node* head;
};

#endif // TREEMULTIMAP_INCLUDED


