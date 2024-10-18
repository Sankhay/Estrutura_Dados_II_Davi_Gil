#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int chave;
    struct Nodo *esquerda, *direita;
} Nodo;

Nodo* criarNodo(int chave) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->chave = chave;
    novoNodo->esquerda = novoNodo->direita = NULL;
    return novoNodo;
}

Nodo* inserir(Nodo* raiz, int chave) {
    if (raiz == NULL) {
        return criarNodo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = inserir(raiz->direita, chave);
    }

    return raiz;
}

Nodo* buscar(Nodo* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    if (chave < raiz->chave) {
        return buscar(raiz->esquerda, chave);
    } else {
        return buscar(raiz->direita, chave);
    }
}

Nodo* minValorNodo(Nodo* nodo) {
    Nodo* atual = nodo;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Nodo* remover(Nodo* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = remover(raiz->direita, chave);
    } else {
        if (raiz->esquerda == NULL) {
            Nodo* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Nodo* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Nodo* temp = minValorNodo(raiz->direita);
        raiz->chave = temp->chave;
        raiz->direita = remover(raiz->direita, temp->chave);
    }

    return raiz;
}

int main() {
    Nodo* raiz = NULL;
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Busca por 40: %s\n", buscar(raiz, 40) != NULL ? "Encontrado" : "Não encontrado");

printf("Busca por 20: %s\n", buscar(raiz, 20) != NULL ? "Encontrado" : "Não encontrado");
    raiz = remover(raiz, 20);
    printf("Busca por 20: %s\n", buscar(raiz, 20) != NULL ? "Encontrado" : "Não encontrado");

    printf("Busca por 70: %s\n", buscar(raiz, 70) != NULL ? "Encontrado" : "Não encontrado");

    return 0;
}
