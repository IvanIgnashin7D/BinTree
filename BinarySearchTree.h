#pragma once
#include <utility> // для std::move

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

    // Вспомогательная функция для рекурсивного удаления узлов
    void clear(Node* node) {
        if (node) {
            clear(node->left_);
            clear(node->right_);
            delete node;
        }
    }

public:
    // Конструктор по умолчанию
    BinarySearchTree() : root_(nullptr) {}

    // Конструктор перемещения
    BinarySearchTree(BinarySearchTree&& other) noexcept
        : root_(other.root_)
    {
        other.root_ = nullptr;
    }

    // Оператор перемещающего присваивания
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            clear(root_);      // Удаляем текущее дерево
            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~BinarySearchTree() {
        clear(root_);
    }

    // Удаляем копирующие операции (если дерево не должно копироваться)
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Дополнительные методы (для примера)
    bool empty() const { return root_ == nullptr; }
};