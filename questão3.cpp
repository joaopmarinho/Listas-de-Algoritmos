#include <iostream>
//#include <bits/stdc++.h>

using namespace std;

struct Node
{
public:
    int value = 0;
    Node *right = nullptr;
    Node *left = nullptr;
};

void BST_search(Node *root)
{
}

int height(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int heightLeft, heightRight;
    heightLeft = height(root->left);
    heightRight = height(root->right);
    return 1 + max(heightLeft, heightRight);
}

Node *insert(Node *root, int value)
{
    if (root == nullptr)
    {
        Node *node;
        node = new Node[1];
        node->value = value;
        return node;
    }
    if (value < root->value)
    {
        root->left = insert(root->left, value);
        return root;
    }
    else
    {
        root->right = insert(root->right, value);
        return root;
    }
}

Node *rotateLeft(Node *root)
{
    Node *right, *rightLeft;
    right = root->right;
    rightLeft = right->left;
    right->left = root;
    root->right = rightLeft;
    return right;
}

Node *rotateRight(Node *root)
{
    Node *left, *leftRight;
    left = root->left;
    leftRight = left->right;
    left->right = root;
    root->left = leftRight;
    return left;
}

Node *first(Node *root, int *left)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        return root;
    }
    while (root->right != nullptr)
    {
        root = rotateLeft(root); // atualizando a raiz
        (*left)++;
    }
    root->left = first(root->left, left);
    return root;
}

Node *second(Node *root, int *left, int *right)
{
    if (root == nullptr)
    {
        return root;
    }
    if (root->right == nullptr)
    {
        int T;
        cin >> T;
        while (root->value != T)
        {
            root = rotateRight(root);
            (*right)++;
        }
    }
    else
    {
        if (root->left == nullptr)
        {
            int T;
            cin >> T;
            while (root->value != T)
            {
                root = rotateLeft(root);
                (*left)++;
            }
        }
    }
    root->left = second(root->left, left, right);
    root->right = second(root->right, left, right);
    return root;
}

void print(Node *root, int tam, int *i)
{
    if (root == nullptr)
    {
        return; //comando de uma funÃ§Ã£o void para paradas bruscas
    }
    print(root->left, tam, i);
    print(root->right, tam, i);
    (*i) = (*i) + 1;
    if((*i) == tam){
        cout << root->value << endl;    
    }else
    cout << root->value << " ";
}

bool check(bool *avl, Node* root){
    if(root == nullptr){
        return (*avl);
    }
    if(height(root->right)- height(root->left)>1 || height(root->right)- height(root->left)<-1){
        (*avl) = false;
    }
    (*avl) = check(avl, root->left);
    (*avl) = check(avl, root->right);
    return (*avl);
}

int main(void)
{
    Node *root = nullptr;
    int value, left = 0, right = 0;
    int tam, i;
    
    while(scanf("%d", &tam) != EOF)//nao precisa de usar o eof quando tem o cin
    {
        root = nullptr;
        left = right = 0;
        bool avl = true;
        for (i = 0; i < tam; i++)
        {
            cin >> value;
            root = insert(root, value); // as funcoes atualizam a raiz, logo devemos retornar seus valores p/ variavel
            //cout << root->value << endl;
        }
        root = first(root, &left);
        root = second(root, &left, &right);
        cout << left << " " << right << endl;
        i=0;
        print(root, tam, &i);
        
        avl = check(&avl, root);
        
        if(avl){
        cout << "true" << endl;
        }else
        cout << "false" << endl;
        cout << "\n";
    } 
    return 0;
}