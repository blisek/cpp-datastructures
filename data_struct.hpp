#ifndef DATA_STRUCT
#define DATA_STRUCT

#include <utility>
#include <initializer_list>

#define DEBUG

#ifdef DEBUG
#include<iostream>
#define DP(x) (std::cout << #x " = " << x << std::endl);
#else
#define DP(x) ;
#endif

namespace cdstr
{
    
template<typename T>
class BinaryTree
{
    using val_type = T;
    
    struct Node {
        Node(const val_type& v) : value{v} {}
        val_type value;
        Node *left {nullptr};
        Node *right {nullptr};
        Node *parent {nullptr};
    };
    
    friend Node;
    Node* root {nullptr};
    val_type default_val;
    
    Node* find_node(const val_type& v) const
    {
        Node* n = root;
        while(n != nullptr)
        {
            if(n->value == v)
                return n;
            else if(n->value > v)
                n = n->left;
            else
                n = n->right;
        }
        return n;
    }
    
    Node* remove_node(Node* n)
    {
        if(!n)
            return nullptr;
        if(!n->left && !n->right)
        {
                // korzeń
                if(n == root) {
                    root = nullptr;
                    return n;
                }
                else
                {
                    if(n->parent->left == n)
                        n->parent->left = nullptr;
                    else
                        n->parent->right = nullptr;
                    n->parent = nullptr;
                    return n;
                }
        }
        else if(!n->left)
        {
            if(n == root) {
                root = n->right;
                n->right->parent = nullptr;
                return root;
            } else {
                n->right->parent = n->parent;
                if(n->parent->right == n)
                    n->parent->right = n->right;
                else
                    n->parent->left = n->right;
                return n->right;
            }
        }
        else if(!n->right)
        {
            if(n == root)
            {
                root = n->left;
                n->left->parent = nullptr;
                return root;
            }
            else
            {
                n->left->parent = n->parent;
                if(n->parent->left == n)
                    n->parent->left = n->left;
                else
                    n->parent->right = n->left;
                return n->left;
            }
        }
        else // podmienienie z następnikiem
        {
            Node* succ = successor(n);
            DP(n->value); DP(succ->value)
            std::swap(n->value, succ->value);
            return remove_node(succ);
        }
    }
    
    Node* successor(Node* n) const
    {
        if(n->right)
            return min(n->right);
        else
        {
            Node* tmp = n;
            while(tmp && tmp->parent->right == tmp)
                tmp = tmp->parent;
            return tmp;
        }
    }
    
    Node* min(Node* startNode) const
    {
        if(!startNode)
            return nullptr;
        Node* n = startNode;
        while(n->left != nullptr)
            n = n->left;
        return n;
    }
    
    Node* max(Node* startNode) const
    {
        if(!startNode)
            return nullptr;
        Node* n = startNode;
        while(n->right != nullptr)
            n = n->right;
        return n;
    }
    
public:
    BinaryTree(const val_type& default_value) : default_val{default_value} {}
    
    std::pair<bool, const val_type&> find(const val_type& v) const
    {
        Node* n = find_node(v);
        const val_type& ref = (n == nullptr) ? default_val : n->value;
        return std::make_pair<bool, const val_type&>(n != nullptr, ref);
    }
    
    void insert(const val_type& v)
    {
        Node* newNode = new Node{v};
        if(!root) {
            root = newNode;
            return;
        }
        
        Node* tmp = root;
        while(tmp)
        {
            if(tmp->value < v) {
                if(!tmp->right) {
                    tmp->right = newNode;
                    newNode->parent = tmp;
                    break;
                }
                else
                    tmp = tmp->right;
            } else {
                if(!tmp->left) {
                    tmp->left = newNode;
                    newNode->parent = tmp;
                    break;
                }
                else
                    tmp = tmp->left;
            }
        }
    }
    
    void insert(std::initializer_list<val_type> il)
    {
        for(auto& el : il)
            insert(el);
    }
    
    std::pair<bool, val_type> remove(const val_type& v) 
    {
        Node* n = remove_node(find_node(v));
        if(!n)
        {
            return std::make_pair(false, val_type{default_val});
        }
        else
        {
            auto pr = std::make_pair<bool, val_type>(true, std::move(n->value));
            delete n;
            return pr;
        }
    }
    
    std::pair<bool, const val_type&> min() const
    {
        Node* n = min(root);
        if(!n)
            return std::make_pair(false, default_val);
        else
            return std::make_pair(true, n->value);
    }
    
    std::pair<bool, const val_type&> max() const
    {
        Node* n = max(root);
        if(!n)
            return std::make_pair(false, default_val);
        else
            return std::make_pair(true, n->value);
    }
};




}
#endif // DATA_STRUCT