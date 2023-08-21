#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <iostream>
#include <vector>
#include <string>

template <typename KeyType, typename ValueType>

class TreeMultimap
{
    public:
    
        class Iterator
        {
            public:

                Iterator() // an invalid iterator has an invalid of false
                {
                    m_pos = 0;
                    m_valid = false;
                }
            
                Iterator(KeyType key, std::vector<ValueType> val) // Iterator keeps track of the key and values in node
                {
                    m_key = key;
                    m_values = val;
                    m_valid = true;
                    m_pos = 0;
                }
                
                ValueType& get_value() //returns value of index
                {
                    return m_values.at(m_pos);
                }

                bool is_valid() const
                {
                    return m_valid;
                }

                void advance() // advances the index only if its valid
                {
                    if(m_pos >= m_values.size() - 1)
                    {
                        m_valid = false;
                        return;
                    }
                    if(m_valid)
                    {
                        m_pos++;
                    }
                    
                }
        
            private:
            
                KeyType m_key;
                std::vector<ValueType> m_values;
                int m_pos;
                bool m_valid;
        };

        TreeMultimap()
        {
            m_root = nullptr;
        }

        ~TreeMultimap() //calls recursive destructor
        {
            DestroyRecursive(m_root);
        }

    void insert(const KeyType& key, const ValueType& value)
        {        
        
            if (m_root == nullptr) //No nodes in tree
            {
                m_root = new Node(key, value);
                return;
            }
        
            Node *cur = m_root;
            for (;;)
            {
                if (key == cur->key) // matching key
                {
                    cur->value.push_back(value);
                    return;
                }
                else if (key < cur->key)
                {
                    if (cur->left != nullptr) //traverse farther left
                        cur = cur->left;
                    else
                    {
                        cur->left = new Node(key, value); //new left node
                        return;
                    }
                }
                else if(key > cur->key)
                {
                    if (cur->right != nullptr) // traverse farther right
                        cur = cur->right;
                    else
                    {
                        cur->right = new Node(key, value); // new right node
                        return;
                    }
                }
            }
        }
    
    Iterator find(const KeyType& key) const
    {
        Node* cur = m_root;
        
        while (cur != nullptr)
        {
            if (key == cur->key) // found
                return Iterator(cur->key, cur->value);
            else if (key < cur->key) //traverse left
                cur = cur->left;
            else //traverse right
                cur = cur->right;
        }
        return Iterator(); // not found
    }
    

    private:
    
        struct Node
        {
            Node(const KeyType& k, const ValueType& val) // node constructed with a key and value
            {
                key = k;
                value.push_back(val);
                left = nullptr;
                right = nullptr;
            }
            
            KeyType key;
            std::vector<ValueType> value; // keeps track of duplicates
            Node* left;
            Node* right;
            
        };
        
        Node* m_root;
    
        void DestroyRecursive(Node* m_head) // destructor helper
        {
            if (m_head == nullptr)
                return;

            DestroyRecursive(m_head->left);
            DestroyRecursive(m_head->right);
            delete m_head;
        }
};

#endif // TREEMULTIMAP_INCLUDED
