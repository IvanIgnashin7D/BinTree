#pragma once
#include <iostream>

template <class T>
class BinarySearchTree
{
private:
    struct Node {
        T key_;
        Node* left_;
        Node* right_;
        Node* p_;
        Node(const T& key, Node* left = nullptr, Node* right = nullptr,
            Node* p = nullptr) :
            key_(key), left_(left), right_(right), p_(p) {
        }
    };

    Node* root_;
    static Node* staticroot_;

    void clear(Node* node) {
        if (node) {
            clear(node->left_);
            clear(node->right_);
            delete node;
        }
    }

public:
    BinarySearchTree() : root_(nullptr) { staticroot_ = root_; }

    BinarySearchTree(BinarySearchTree&& other) noexcept
        : root_(other.root_)
    {
        other.root_ = nullptr;
    }

    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            clear(root_);
            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }

    ~BinarySearchTree() {
        clear(root_);
    }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;


    Node* searchItem(T key) {
        if (root_ == nullptr)
            return nullptr;
        Node* current = root_;
        while (true) {
            if (current->key_ == key)
                return current;
            if (current->left_ && current->left_->key_ < key)
                current = current->left_;
            if (current->right_ && current->right_->key_ > key)
                current = current->right_;
            else
                return nullptr;
        }
    }

    bool insertItem(T key) {
        if (root_ == nullptr) {
            root_ = new Node(key);
            staticroot_ = root_;
            return true;
        }
        
        if (searchItem(key)) 
            return false;

        Node* current = root_;
        while (true) {
            if (current->left_ == nullptr && key < current->key_) {
                Node* newNode = new Node(key);
                current->left_ = newNode;
                return true;
            }
            if (current->right_ == nullptr && key > current->key_) {
                Node* newNode = new Node(key);
                current->right_ = newNode;
                return true;
            }
            if (current->left_ && current->key_ > key) {
                current = current->left_;
                continue;
            }
            if (current->right_ && current->key_ < key) {
                current = current->right_;
                continue;
            }
            if (current->left_ && current->left_->key_ < key && current->key_ > key) {
                Node* newNode = new Node(key);
                newNode->left_ = current->left_->left_;
                newNode->right_ = current->left_->right_;
                current->left_ = newNode;
                return true;
            }
            if (current->right_ && current->right_->key_ > key && current->key_ < key) {
                Node* newNode = new Node(key);
                newNode->left_ = current->right_->left_;
                newNode->right_ = current->right_->right_;
                current->right_ = newNode;
                return true;
            }
        }
    }

    void deleteItem(T key) {
        Node* current = searchItem(key);
        if (current == nullptr)
            return;
        if (current->right_ == nullptr) {
            current = current->left_;
            return;
        }
        if (current->right_->left_ == nullptr) {
            current->right_->left_ = current->left_;
            current = current->right_;
            return;
        }
        if (current->right_->left_ != nullptr) {
            Node* curMin = current;
            while (curMin->left_ != nullptr) {
                curMin = curMin->left_;
            }
            current = curMin;
            deleteItem(curMin->key_);
            return;
        }
    }

    void print(Node* node = staticroot_, int space = 0, int step = 4) {
        if (node == nullptr) {
            return;
        }

        space += step;

        print(node->right_, space);

        std::cout << '\n';
        for (int i = step; i < space; i++) {
            std::cout << ' ';
        }
        std::cout << "--(" << node->key_ << ')' << '\n';

        print(node->left_, space);
    }

    int howManyNodes(Node* node = staticroot_) {
        int res = 0;
        if (!node)
            return 0;
        if (node)
            res++;
        if (node->left_)
            res += howManyNodes(node->left_);
        if (node->right_)
            res += howManyNodes(node->right_);
        return res;
    }

    int getHeight(Node* node = staticroot_) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getHeight(node->left_);
        int rightHeight = getHeight(node->right_);
        return std::max(leftHeight, rightHeight) + 1;
    }
};

template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::staticroot_ = nullptr;