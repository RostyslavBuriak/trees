#include <utility>

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

        template <typename T3>
        Node * add(T3&& val, Node *& temp){
            if(!temp){
                temp = new Node(val);
                return temp;
            }
            if(val > temp->data)
                temp->right = add(std::forward<T3>(val),temp->right);
            else if(val < temp->data)
                temp->left = add(std::forward<T3>(val),temp->left);
            return temp;
        }
    public:
        bst():root(nullptr){}

        template <typename T1>
        Node * add(T1&& val){
            return add(std::forward<T1>(val),root);
        }
};