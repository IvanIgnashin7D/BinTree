#pragma once
#include <utility> // ��� std::move

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

    // ��������������� ������� ��� ������������ �������� �����
    void clear(Node* node) {
        if (node) {
            clear(node->left_);
            clear(node->right_);
            delete node;
        }
    }

public:
    // ����������� �� ���������
    BinarySearchTree() : root_(nullptr) {}

    // ����������� �����������
    BinarySearchTree(BinarySearchTree&& other) noexcept
        : root_(other.root_)
    {
        other.root_ = nullptr;
    }

    // �������� ������������� ������������
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            clear(root_);      // ������� ������� ������
            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }

    // ����������
    ~BinarySearchTree() {
        clear(root_);
    }

    // ������� ���������� �������� (���� ������ �� ������ ������������)
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // �������������� ������ (��� �������)
    bool empty() const { return root_ == nullptr; }
};