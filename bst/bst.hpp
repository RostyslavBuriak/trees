#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>

template<typename T>
class bst{
    private:
        struct Node
        {
            Node(): 
            data(data()), left(nullptr), right(nullptr){}

            template <typename T2>
            Node(const T2& val):
            data(val),
            left(nullptr),
            right(nullptr){}

            T data;

            Node * left;
            Node * right;
        };

        Node * root;

        template <typename TT>
        Node * add(TT&& val, Node *& temp){
            if(!temp){
                temp = new Node(val);
                return temp;
            }
            if(val > temp->data)
                temp->right = add(std::forward<TT>(val),temp->right);
            else if(val < temp->data)
                temp->left = add(std::forward<TT>(val),temp->left);
            return temp;
        }

        template <typename TT>
        Node * find(TT&& val,Node * temp){
            if(!temp)
                return nullptr;
            if(val > temp->data)
                return find(val,temp->right);
            if(val < temp->data)
                return find(val,temp->left);

            return temp;
        }

        Node * find_parent(Node * temp,Node * parent){
            if(parent->right == temp || parent->left == temp)
                return parent;
            
            if(temp->data > parent->data)
                return find_parent(temp,parent->right);
            if(temp->data < parent->data)
                return find_parent(temp,parent->left);

            return nullptr;
        }

        Node * find_low(Node * temp){
            if(!temp->left)
                return temp;
            return find_low(temp->left);
        }
        
        Node * find_big(Node * temp){
            if(!temp->right)
                return temp;
            return find_low(temp->right);
        }
        
        template <typename TT>
        void remove(TT&& val,Node * temp){
            if(root->data == val){
                delete root;
                root = nullptr;
                return;
            }
            Node * del =  find(std::forward<TT>(val),temp);
            Node * del_parent = find_parent(del,root);
            if(del->right && del->left){ //for node with 2 children
                Node * low = find_low(del->right);
                Node * low_parent = find_parent(low,root);
                if(del){
                    if(del_parent->right == del){
                        del_parent->right = low;
                    }
                    if(del_parent->left == del){
                        del_parent->left = low;
                    }
                    low->left = del->left;
                    low_parent->left = low->right;
                    low->right = del->right;
                    delete del;
                }
            }
            else if(del->right || del->left){ //for node with 1 child
                if(del_parent->right == del){
                    if(del->right)
                        del_parent->right = del->right;
                    if(del->left)
                        del_parent->right = del->left;
                }
                if(del_parent->left == del){
                    if(del->right)
                        del_parent->left = del->right;
                    if(del->left)
                        del_parent->left = del->left;
                }
                delete del;
            }
            else{
                if(del_parent->right == del)
                    del_parent->right = nullptr;
                if(del_parent->left == del)
                    del_parent->left = nullptr;
                delete del;
            }
        }

        std::size_t height(Node * temp){
            if(!temp)
                return 0;
            return std::max(height(temp->left),height(temp->right)) + 1; 
        }

        std::size_t depth(Node * node,Node * temp){
            if(node == temp)
                return 0;
            if(temp->data > node->data)
                return depth(node->right,temp) + 1;
            if(temp->data < node->data)
                return depth(node->left,temp) + 1;
            return 0;
        }

        void print_node_r(Node* node,std::size_t h,std::size_t spaces){
            if(!node){
                spaces*=std::pow(2,h-1);
                spaces+=std::pow(2,h-1);
                while (spaces--){
                    std::cout << " ";
                }
                return;
            }
            else if(h == 1){
                while(spaces--)
                    std::cout << " ";
                std::cout << node->data;
                return;
            }
            else if(h > 1){
                print_node_r(node->left,h-1,spaces);
                print_node_r(node->right,h-1,spaces);
            }
        }
    
        void tree_cut_down(Node * temp){
            if(!temp)
                return;
            tree_cut_down(temp->left);
            tree_cut_down(temp->right);
            delete temp;
        }
    public:
        bst():root(nullptr){}

        ~bst(){
            tree_cut_down(root);
            root = nullptr;
        }

        template <typename TT>
        Node * add(TT&& val){
            return add(std::forward<TT>(val),root);
        }

        template <typename TT>
        void remove(TT&& val){
            remove(std::forward<TT>(val),root);
        }

        void print_tree(){ //test implementation ,made it for fun :)
            std::size_t h = height(root);
            std::size_t max_spaces = std::pow(2,h)*2 + 1;
            for(int i = h;i>=0;--i){
                print_node_r(root,h-i,max_spaces / (std::pow(2,h-i)+1));
                std::cout << std::endl;
            }
        }
};