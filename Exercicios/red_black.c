#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

// Estrutura de um nó da árvore
typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

// Função para criar um novo nó
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED; // Novos nós são sempre vermelhos
    node->left = node->right = node->parent = NULL;
    return node;
}

// Função para realizar a rotação para a esquerda
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL) y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Função para realizar a rotação para a direita
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NULL) x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Função para corrigir as propriedades de uma árvore Red-Black após a inserção
void fixInsertion(Node** root, Node* z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) { // Caso 1: Tio é vermelho
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { // Caso 2: z é filho à direita
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK; // Caso 3: z é filho à esquerda
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) { // Caso 1: Tio é vermelho
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { // Caso 2: z é filho à esquerda
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK; // Caso 3: z é filho à direita
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; // A raiz deve ser sempre preta
}

// Função para inserir um novo nó na árvore Red-Black
void insert(Node** root, int data) {
    Node* z = newNode(data);
    Node* y = NULL;
    Node* x = *root;

    // Insere o nó z na árvore binária de busca padrão
    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    // Corrige as propriedades da árvore Red-Black após a inserção
    fixInsertion(root, z);
}

// Função para imprimir a árvore (em pré-ordem)
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d (%s) ", root->data, root->color == RED ? "R" : "B");
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = NULL;

    // Inserindo valores na árvore
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);

    printf("Árvore Red-Black em pré-ordem:\n");
    preOrder(root);

    return 0;
}
