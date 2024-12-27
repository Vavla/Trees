// RedBlackTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
std::regex re ("(0[1 - 9] | [12][0 - 9] | 3[01])\.(0[1-9]|1[012])\.(1[0-9][0-9][0-9]|2[0][0-2][0-9])");
std::regex re2("(0[1 - 9] | [12][0 - 9] | 3[01])\.(0[1-9]|1[012])");
std::regex re3("(0[1-9]|[1|2][0-9]|3[0|1])\.(0[1-9]|1[0-2])\.(1[0-9][0-9][0-9]|2[0][0-2][0-9])");
typedef struct List {
    int data;
    List* next;
    List* pred;
} List;
typedef struct Date {
    int day;
    int mouth;
    int year;
}Date;
typedef struct Node {
    Node* parent;
    Node* left;
    Node* right;
    Date* date;
    List* list;
    bool isBlack;
} Node;



bool validalDate(std::string s) {
    if (regex_match(s.begin(), s.end(), re3)) return 1;
    else return 0;

}

void PrintList(List* head) {
    
    List* temp = head;
    if (not(head == nullptr)) {
        while (not(temp->next == head)) {
           
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << temp->data << " " << "\n";
    }
    else std::cout << "Head is nullptr" << "\n";
   
}



void AddElem(List*& head, int newElem) {
    bool IsAdded = false;
    List* temp = head;
    List* addElem = new List;
    addElem->data = newElem;
    if (not(head == nullptr)) {
        while (not(temp->next == head)) {

            if ((temp->data <= newElem) && (((temp->next)->data) >= newElem) && IsAdded == false) {

                temp->next->pred = addElem;
                addElem->next = temp->next;
                temp->next = addElem;
                addElem->pred = temp;
                IsAdded = true;
                break;
            }

            temp = temp->next;
        }
        if ((temp == head) && (temp->data <= newElem) && IsAdded == false) {

            addElem->pred = temp;
            addElem->next = temp;
            temp->pred = addElem;
            temp->next = addElem;

        }
        else if ((temp->data <= newElem) && (IsAdded == false)) {
            addElem->pred = temp;
            addElem->next = temp->next;
            temp->next->pred = addElem;
            temp->next = addElem;

        }
        else if ((temp->data > newElem) && (temp->next->data >= newElem) && (IsAdded == false)) {

            addElem->pred = temp;
            addElem->next = temp->next;
            temp->next->pred = addElem;
            temp->next = addElem;
            head = addElem;

        }
    }
    else cout << "List is deleted" << endl;
}
void DeleteAllNeededElem(List*& head, int elem)
{
    bool IsDelete = false;
    List* temp = head;
    List* deletedEl = temp;
    if (not(head == nullptr)) {
        while (not(temp->next == head)) {

            if (temp == head && temp->data == elem) {

                deletedEl = temp;
                if (not(temp->data == temp->next->data)) IsDelete = true;
                temp->next->pred = temp->pred;
                temp->pred->next = temp->next;
                temp = temp->next;
                deletedEl->pred = nullptr;
                head = temp;
                deletedEl->next = nullptr;
                delete(deletedEl);

            }
            else if (not(temp == head) && (temp->data == elem)) {
                deletedEl = temp;
                temp->next->pred = temp->pred;
                temp->pred->next = temp->next;
                temp = temp->next;
                deletedEl->next = nullptr;
                deletedEl->pred = nullptr;

                delete(deletedEl);

            }

            else { temp = temp->next; }
        }
        if ((temp == head) && (temp->data == elem)) {
           
            head = nullptr;

        }
        else if (not(temp == head) && (temp->data == elem) && IsDelete == false) {
            deletedEl = temp;
            temp->next->pred = temp->pred;
            temp->pred->next = temp->next;
            deletedEl->next = nullptr;
            deletedEl->pred = nullptr;
            delete(deletedEl);

        }
    }
    else cout << "List is deleted" << endl;


}
List* CreateList(int count) {

    List* head = new List;
    List* temp = head;
    head->data = count;
    head->next = head;
    head->pred = head;
    
    return head;
} 
void deleteElemList(Node* &elem,List* head,int number) {

    bool isThere = false;
    List* temp = head;
    do {
        if (temp->data != number)
            temp = temp->next;
        if (temp->data == number) isThere = true;
    } while (temp != head);
    if (isThere) {
        DeleteAllNeededElem(head, number);
        elem->list = head;
        PrintList(head);
    }
    else std::cout << "No elements with number" << endl;
}
void initialization(Node* &node,int number,int day,int mouth,int year) {

    node = new Node;
    Date* date = new Date;
    date->day = day;
    date->mouth = mouth;
    date->year = year;
    node->date = date;
    node->parent = nullptr;
    node->right = nullptr;
    node->left = nullptr;
    node->isBlack = 1;
    node->list = CreateList(number);


}
void printNode(Node* node, int l)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
   
    if (not(node == nullptr)) {
        
        printNode(node->right, l + 1);
        for (int i = 0; i < l; i++) std::cout << "          ";
        if (node->isBlack == 0)
            SetConsoleTextAttribute(console, FOREGROUND_RED);
        printf("%2ld", node->date->day);
        std::cout << '.' << node->date->mouth << '.' << node->date->year;
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        printNode(node->left, l + 1);
    }
    cout  << endl;


}

void print_Node(Node* node, int l) {

    Node* temp = node;
    printNode(temp, l);
    if (node == nullptr) cout << "Nullptr" << endl;

}
bool cmpFirstBefore(Node* node,Node* node2) {
    if (node->date->year > node2->date->year) return 1;
    else if (node->date->year < node2->date->year) return 0;
    else {
        if (node->date->mouth > node2->date->mouth) return 1;
        else if (node->date->mouth < node2->date->mouth) return 0;
        else {
            if (node->date->day > node2->date->day) return 1;
            else return 0;
        }
    }
}

bool cmpFirstBeforeDelete(Node* node, int day,int mouth,int year) {
    if (node->date->year > year) return 1;
    else if (node->date->year < year) return 0;
    else {
        if (node->date->mouth > mouth) return 1;
        else if (node->date->mouth < mouth) return 0;
        else {
            if (node->date->day > day) return 1;
            else return 0;
        }
    }
}

bool isChangeDirection(Node* downNode, bool isLeftChild) {
    
    if (downNode->parent->parent->left == downNode->parent && isLeftChild == 0 ) return 1;
    else if (downNode->parent->parent->right == downNode->parent && isLeftChild == 1) return 1;
    else return 0;

}
void preOrder(Node* node) {    //вывод прямого обхода по построенному дереву
    Node* temp = node;
    if (not (temp == nullptr)) {
        std::cout << temp->date->day << "." << temp->date->mouth << "." << temp->date->year << endl;
        preOrder(temp->left);
        preOrder(temp->right);
    }
}
Node* deleteAllNode(Node* node) {
  

    if (not (node == nullptr)) {

        deleteAllNode(node->left);

        deleteAllNode(node->right);
        Node* del = node;
        del->parent->left = nullptr;
        del->parent->right = nullptr;
        del->parent = nullptr;
        delete(del);
    /*std:cout << "del" << endl;*/

    }
    return node = nullptr;
    
}
void repaint(Node* downNode,bool isLeftChild,Node* &node) {
    Node* uncle;
    Node* grandfather = downNode->parent->parent;
    Node* father = downNode->parent;
    
    
    while (not(downNode == node) and ((downNode->parent->isBlack == 0))) {
        father = downNode->parent;
        grandfather = downNode->parent->parent;
        if(not(grandfather->left == downNode->parent)) uncle = grandfather->left;
        else uncle = grandfather->right;
        if (downNode->parent->left == downNode) isLeftChild = 1;
        else isLeftChild = 0;
        if ((uncle == nullptr or uncle->isBlack == 1) and isChangeDirection(downNode, isLeftChild))    /// uncle is black and the direction has changed
        {
            
            if (not isLeftChild) grandfather->left = downNode;
            else grandfather->right = downNode;
            father->parent = downNode;

            if (isLeftChild) {
                father->left = downNode->right;
                downNode->right = father;
            }
            else {
                father->right = downNode->left;
                downNode->left = father;
            }

            downNode->parent = grandfather;
            downNode = father;
            
            print_Node(node,1);
            preOrder(node);
            downNode->parent->isBlack = 0;
            
        }
        else if ((uncle == nullptr or uncle->isBlack == 1) and not(isChangeDirection(downNode, isLeftChild)))  /// uncle is black and the direction has not changed
        {
            downNode->parent->isBlack = 1;
            grandfather->isBlack = 0;
            if (not(downNode->parent->parent->parent == nullptr)) {
                if (downNode->parent->parent->parent->left == downNode->parent->parent) downNode->parent->parent->parent->left = downNode->parent; //child of grandgrandpa
                else if (downNode->parent->parent->parent->right == downNode->parent->parent) downNode->parent->parent->parent->right = downNode->parent;
            }
            if (isLeftChild)
            {
                Node* temp = downNode->parent->right;
                downNode->parent->right = downNode->parent->parent;
                grandfather->left = temp;

            }
            else {
                Node* temp = downNode->parent->left;
                downNode->parent->left = downNode->parent->parent;
                grandfather->right = temp;
            }
            if (not(downNode->parent->parent->parent == nullptr)) downNode->parent->parent = downNode->parent->parent->parent; // parent of pa is grandgrandpa
            else downNode->parent->parent = nullptr;
            grandfather->parent = downNode->parent;
            if (father == node) node = father;
            if (downNode->parent->parent == nullptr) node = downNode->parent;
            
            downNode = downNode->parent;
        }
        else if (uncle->isBlack == 0) {   /// uncle is red
            uncle->isBlack = 1;
            downNode->parent->isBlack = not(downNode->parent->isBlack);
            grandfather->isBlack = not(grandfather->isBlack);
            downNode = grandfather;
            print_Node(node, 1);
            preOrder(node);
        }

    }
}

void insert(Node* &node,int i,int day,int mouth, int year) {
    Node* newNode = new Node;
    Node* temp = node;
    Node* changeNode = temp;
    Date* date = new Date;
    date->day = day;
    date->mouth = mouth;
    date->year = year;
    newNode->date = date;
    newNode->list = CreateList(i);
    newNode->right = nullptr;
    newNode->left = nullptr;
    bool isLeftChild = 0;
    do 
    {
        changeNode = temp;
        if (cmpFirstBefore(temp, newNode)) {
            isLeftChild = 1;
            temp = temp->left;

        }
        else {
            isLeftChild = 0;
            temp = temp->right;
        }
            
        
    }
    while (not(temp == nullptr));

    newNode->parent = changeNode;
   
    newNode->isBlack = 0;
    if (isLeftChild) changeNode->left = newNode;
    else changeNode->right = newNode;
    if (not(newNode->parent->parent == nullptr)) repaint(newNode,isLeftChild,node);
    node->isBlack = 1;
}
void balance_delete(Node* &node, Node* deleteNode)
{
    Node* needNode = deleteNode;
    Node* brother;
    Node* external;
    while (not(deleteNode == node) and ((deleteNode->isBlack == 1))) {
        if (deleteNode->parent->left == deleteNode) {
            brother = deleteNode->parent->right; external = brother->right;
        }
        else { brother = deleteNode->parent->left; external = brother->left; }
        Node* father = deleteNode->parent;
        
        if (brother->isBlack == 0)  //red brother
        {
            //if (not(deleteNode->parent->parent == nullptr)) {
            //    if (deleteNode->parent->parent->left == deleteNode->parent) deleteNode->parent->parent->left = deleteNode->parent->right; //child of grandgrandpa
            //    else if (deleteNode->parent->parent->right == deleteNode->parent) deleteNode->parent->parent->right = deleteNode->parent->right;
            //}
            //Node* temp = deleteNode->parent->right;
            //deleteNode->parent->right->left->parent = deleteNode->parent->right;
            //deleteNode->parent->right = deleteNode->parent->right->left;
            //temp->left = deleteNode->parent;
            //deleteNode->parent->parent = temp;
            //temp->isBlack = 1;
            //deleteNode->parent->isBlack = 0;
            //print_Node(node,2);

            Node* child;
            if (brother->parent->left == brother) child = brother->left;
            else child = brother->right;
            Node* temp;
            child->parent->isBlack = 1;
            father->isBlack = 0;
            if (not(child->parent->parent->parent == nullptr)) {
                if (child->parent->parent->parent->left == child->parent->parent) child->parent->parent->parent->left = child->parent; //child of grandgrandpa
                else if (child->parent->parent->parent->right == child->parent->parent) child->parent->parent->parent->right = child->parent;
            }
            if (brother->parent->left == brother)
            {
                 temp = brother->right;
                brother->right = father;
                father->left = temp;
                

            }
            else {
                temp = brother->left;
                brother->left = father;
                father->right = temp;
            }
            temp->parent = father;
            if (not(child->parent->parent == nullptr)) {
                if (not(child->parent->parent->parent == nullptr)) child->parent->parent = child->parent->parent->parent; // parent of pa is grandgrandpa
                else child->parent->parent = nullptr;
            }
            father->parent = brother;
      
            if (child->parent->parent == nullptr) node = child->parent;

            deleteNode = needNode;
        }

       
        else if (external != nullptr and external->isBlack == 0)
        {
            
            
            external->isBlack = 1; 
            
            if (not(father->parent == nullptr)) {
               
                if (father->parent->left == father) father->parent->left = brother; //child of grandgrandpa
                else if (father->parent->right == father) father->parent->right = brother;
            }

            Node* child = brother->left;
            if (child == external) child = brother->right;
            brother->isBlack = father->isBlack;
            if (father->parent == nullptr) {
                brother->parent = nullptr; node = brother;
            }
            else brother->parent = father->parent;
            if (child != nullptr) child->parent = father;
            if (brother == father->right) {
                father->right = child;
                brother->left = father;
            }
            else {
                father->left = child;
                brother->right = father;
            }
            father->parent = brother;
            brother->isBlack = father->isBlack;
            father->isBlack = 1;
            print_Node(node, 1);
            
            deleteNode = node;
            continue;
        }
        else if ((brother->left == nullptr and brother->right == nullptr))
        {
            brother->isBlack = 0;
            if (not deleteNode->parent->isBlack) {
                deleteNode->parent->isBlack = 1;
                break;
            }
            else deleteNode->parent->isBlack = 1;
            deleteNode = deleteNode->parent;
            
        }
        else if ((brother->left != nullptr and brother->right != nullptr)and(brother->left->isBlack == 1 and brother->right->isBlack == 1)) {
            brother->isBlack = 0;
            if (not deleteNode->parent->isBlack) {
                deleteNode->parent->isBlack = 1;
                break;
            }
            else deleteNode->parent->isBlack = 1;
            deleteNode = deleteNode->parent;
        }
        else if (external == nullptr or external->isBlack == 1)
        {
            

            Node* child = brother->left;
            if (child == external) child = brother->right;
            brother->isBlack = 0;
            child->isBlack = 1;
            if (child != nullptr) 
            child->isBlack = 1;
            if (brother == father->right) {
                father->right = child;
                brother->left = child->right;
                child->right = brother;
            }
            else {
                father->left = child;
                brother->right = child->left;
                child->left = brother;
            }

           child->parent = father;
            brother->parent = child;
           
            print_Node(node,2);
           
            
           

        }
       
        
    }
}
void delete_Node(Node*& node, string date, int number)
{
    Node* temp = node;

    if (validalDate(date)) {
        int day = (date[0] - '0') * 10 + (date[1] - '0');
        int mouth = (date[3] - '0') * 10 + (date[4] - '0');
        int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

        while (temp != nullptr and not(temp->date->day == day and temp->date->mouth == mouth and temp->date->year == year)) {
            if (cmpFirstBeforeDelete(temp, day, mouth, year)) temp = temp->left;
            else temp = temp->right;
        }
        if (temp != nullptr) {
            if (temp->list != nullptr) deleteElemList(temp, temp->list, number);
            if (temp->list == nullptr) {

                if (temp->left == nullptr and temp->right == nullptr) {
                    if (temp->isBlack) balance_delete(node, temp);
                    if (temp->parent->left == temp) temp->parent->left = nullptr;
                    else temp->parent->right = nullptr;
                    temp->parent = nullptr;
                    delete(temp);

                }
                else if ((temp->left == nullptr and not(temp->right == nullptr))) {

                    temp->date = temp->right->date;
                    if (temp->right->isBlack) balance_delete(node, temp);
                    temp->right->isBlack = temp->isBlack;
                    temp->right->parent = temp->parent;
                    if (temp->parent->left == temp) temp->parent->left = temp->right;
                    else temp->parent->right = temp->right;
                    temp->right = nullptr;
                    temp->parent = nullptr;
                    delete(temp);
                }
                else if ((temp->right == nullptr and not(temp->left == nullptr))) {
                    temp->date = temp->left->date;
                    if (temp->left->isBlack) balance_delete(node, temp);
                    temp->left->isBlack = temp->isBlack;
                    temp->left->parent = temp->parent;
                    if (temp->parent->left == temp) temp->parent->left = temp->left;
                    else temp->parent->right = temp->left;
                    temp->left = nullptr;
                    temp->parent = nullptr;
                    delete(temp);
                }
                else {
                    Node* deletedNode = temp;
                    bool isFirst = 1;
                    do {
                        if (isFirst) {
                            temp = temp->right;
                            isFirst = 0;
                        }
                        else temp = temp->left;
                    } while (not(temp->left == nullptr));
                    deletedNode->date = temp->date;

                    if (temp->isBlack) balance_delete(node, temp);

                    if (temp->parent->left == temp) temp->parent->left = temp->right;
                    else temp->parent->right = temp->right;
                    if (not(temp->right == nullptr)) {
                        temp->right->parent = temp->parent;

                    }
                    temp->parent = nullptr;
                    temp->right = nullptr;
                    delete(temp);


                }
            }
        }
    }
}

void addListNode(Node* node,int numberStr,int day, int mouth,int year)
{
    Node* temp = node;
    while (not(temp->date->day == day and temp->date->mouth == mouth and temp->date->year == year)) {
        if (cmpFirstBeforeDelete(temp, day, mouth, year)) temp = temp->left;
        else temp = temp->right;
    }
    AddElem(temp->list, numberStr);
    PrintList(temp->list);
}

bool searchNode(Node* node,int day, int mouth,int year) {

    Node* temp = node;
    while (not(temp->date->day == day and temp->date->mouth == mouth and temp->date->year == year)) {
        if (cmpFirstBeforeDelete(temp, day, mouth, year)) temp = temp->left;
        else temp = temp->right;
        if (temp == nullptr) break;
    }
    if (temp == nullptr) return 0;
    else return 1;
}


int main()
{
    Node* node = nullptr;
    string s = ""; // считанные строки
    int numberStr = 0;
    ifstream file; 
    file.open("dates.txt", std::ios::in);
    if (!file.is_open()) // если файл не был открыт
    {
        cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщение
     
    }
    if (file.is_open()) {
        
        while (getline(file, s)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
            numberStr++;
            if (validalDate(s)) {
                
                cout << s << endl;
                int day = (s[0] - '0') * 10 + (s[1] - '0');
                int mouth = (s[3] - '0') * 10 + (s[4] - '0');
                int year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
                if (node == nullptr) {
                    
                    initialization(node, numberStr,day,mouth,year);
                    print_Node(node,1);
                }
                else {
                    int day = (s[0] - '0') * 10 + (s[1] - '0');
                    int mouth = (s[3] - '0') * 10 + (s[4] - '0');
                    int year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
                    if (searchNode(node, day, mouth, year) == 0) insert(node, numberStr, day, mouth, year);
                    else addListNode(node,numberStr, day, mouth, year);
                    print_Node(node,1);
                }
            }
             
        }
    }

    file.close();

    preOrder(node);

    delete_Node(node,"18/02/2000",3);
    print_Node(node, 1);
    delete_Node(node, "04/02/2000", 5);
    print_Node(node, 1);
    delete_Node(node, "02/02/2000", 8);
    print_Node(node, 1);
    delete_Node(node, "14/02/2000", 17);
    print_Node(node, 1);
    delete_Node(node, "18/02/2000", 3);
    print_Node(node, 1);
    delete_Node(node, "31/04/2000", 18);
    print_Node(node, 1);
    delete_Node(node, "30/03/2000", 9);
    print_Node(node, 1);
    
    node = deleteAllNode(node->left);
    print_Node(node,2);

    /*delete_Node(node, "12.02.2000",2);
    print_Node(node, 1);
    delete_Node(node, "17/09/2001", 6);
    print_Node(node, 1);
    delete_Node(node, "18/09/2001", 8);
    print_Node(node, 1);
    delete_Node(node, "07/10/2001", 13);
    print_Node(node, 1);
    delete_Node(node, "20/03/2003", 5);
    print_Node(node, 1);
    delete_Node(node, "20/03/2003", 18);
    print_Node(node, 1);
    preOrder(node);*/
    
    
    
}

