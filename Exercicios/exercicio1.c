#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo *esquerda;
    struct Nodo *direita;
} Nodo;

Nodo* criarNodo(int valor) {
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if (!novo) {
        fprintf(stderr, "Erro ao pegar memoria\n");
        exit(EXIT_FAILURE);
    }
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Nodo* inserir(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        return criarNodo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

Nodo* encontrarMinimo(Nodo *raiz) {
    while (raiz && raiz->esquerda) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

Nodo* excluir(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = excluir(raiz->esquerda, valor);
    } 
    else if (valor > raiz->valor) {
        raiz->direita = excluir(raiz->direita, valor);
    } 
    else {
        if (raiz->esquerda == NULL) {
            Nodo *temp = raiz->direita;
            free(raiz);
            return temp;
            
        } else if (raiz->direita == NULL) {
            Nodo *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        Nodo *temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = excluir(raiz->direita, temp->valor);
    }
    return raiz;
}

int pesquisar(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        return 0;  
    }
    if (valor == raiz->valor) {
        return 1;  
    } else if (valor < raiz->valor) {
        return pesquisar(raiz->esquerda, valor);
    } else {
        return pesquisar(raiz->direita, valor);
    }
}

int main() {
    Nodo *raiz = NULL;

    raiz = inserir(raiz, 50);
    
    inserir(raiz, 42);
    
    inserir(raiz, 51);
    
    inserir(raiz, 39);
    
    inserir(raiz, 10);
    
    inserir(raiz, 11);
    
    inserir(raiz, 12);

    int valor = 12;
    if (pesquisar(raiz, valor)) {
        printf("Valor %d encontrado na árvore.\n", valor);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valor);
    }

    raiz = excluir(raiz, 51);
    
    int valor2 = 51;
    if (pesquisar(raiz, valor2)) {
        printf("Valor %d encontrado na arvore.\n", valor2);
    } else {
        printf("Valor %d não encontrado na arvore.\n", valor2);
    }
    return 0;
}
