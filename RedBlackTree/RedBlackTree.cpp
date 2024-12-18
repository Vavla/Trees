// RedBlackTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

typedef struct Node {
    Node* parent;
    int day;
    int mouth;
    int year;
    Node* left;
    Node* right;
    int blackHeight;
    bool isBlack;
} Node;

void initialization(Node* &node) {

    std::cin >> node->day;
    std::cin >> node->mouth;
    std::cin >> node->year;

    node->parent = nullptr;
    node->blackHeight = 0;
    node->right = nullptr;
    node->left = nullptr;
    node->isBlack = 1;



}




int main()
{
    Node* node = new Node;
    initialization(node);
    std::cout << node->day;
    std::cout << node->isBlack;
}

