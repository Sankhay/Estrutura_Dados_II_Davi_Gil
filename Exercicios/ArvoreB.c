#include <stdio.h>
#include <stdlib.h>

#define GRAU_MINIMO 3

typedef struct NoArvoreB {
    int *chaves; // Array de chaves
    int grau; // Grau mínimo
    struct NoArvoreB **filhos; // Array de ponteiros para filhos
    int numChaves; // Número atual de chaves
    int folha; // Verdadeiro se o nó é folha
} NoArvoreB;

// Função para criar um novo nó da árvore B
NoArvoreB* criarNo(int grau, int folha) {
    NoArvoreB* novoNo = (NoArvoreB*)malloc(sizeof(NoArvoreB));
    novoNo->grau = grau;
    novoNo->folha = folha;
    novoNo->chaves = (int*)malloc((2 * grau - 1) * sizeof(int));
    novoNo->filhos = (NoArvoreB**)malloc(2 * grau * sizeof(NoArvoreB*));
    novoNo->numChaves = 0;
    return novoNo;
}

// Função para percorrer a árvore
void percorrer(NoArvoreB* raiz) {
    int i;
    for (i = 0; i < raiz->numChaves; i++) {
        if (!raiz->folha) {
            percorrer(raiz->filhos[i]);
        }
        printf(" %d", raiz->chaves[i]);
    }
    if (!raiz->folha) {
        percorrer(raiz->filhos[i]);
    }
}

// Função para buscar uma chave na árvore
NoArvoreB* buscar(NoArvoreB* raiz, int chave) {
    int i = 0;
    while (i < raiz->numChaves && chave > raiz->chaves[i]) {
        i++;
    }
    if (i < raiz->numChaves && raiz->chaves[i] == chave) {
        return raiz;
    }
    if (raiz->folha) {
        return NULL;
    }
    return buscar(raiz->filhos[i], chave);
}

// Função para inserir uma nova chave na árvore
void inserir(NoArvoreB** raiz, int chave) {
    NoArvoreB* r = *raiz;
    if (r->numChaves == 2 * GRAU_MINIMO - 1) {
        NoArvoreB* s = criarNo(r->grau, 0);
        *raiz = s;
        s->filhos[0] = r;
        dividirFilho(s, 0, r);
        inserirNaoCheio(s, chave);
    } else {
        inserirNaoCheio(r, chave);
    }
}

// Função para inserir uma chave em um nó não cheio
void inserirNaoCheio(NoArvoreB* no, int chave) {
    int i = no->numChaves - 1;
    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        if (no->filhos[i + 1]->numChaves == 2 * GRAU_MINIMO - 1) {
            dividirFilho(no, i + 1, no->filhos[i + 1]);
            if (no->chaves[i + 1] < chave) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i + 1], chave);
    }
}

// Função para dividir um nó filho cheio
void dividirFilho(NoArvoreB* no, int i, NoArvoreB* filho) {
    NoArvoreB* novoFilho = criarNo(filho->grau, filho->folha);
    novoFilho->numChaves = GRAU_MINIMO - 1;
    
    for (int j = 0; j < GRAU_MINIMO - 1; j++) {
        novoFilho->chaves[j] = filho->chaves[j + GRAU_MINIMO];
    }
    
    if (!filho->folha) {
        for (int j = 0; j < GRAU_MINIMO; j++) {
            novoFilho->filhos[j] = filho->filhos[j + GRAU_MINIMO];
        }
    }
    
    filho->numChaves = GRAU_MINIMO - 1;
    
    for (int j = no->numChaves; j >= i + 1; j--) {
        no->filhos[j + 1] = no->filhos[j];
    }
    no->filhos[i + 1] = novoFilho;
    
    for (int j = no->numChaves - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
    }
    no->chaves[i] = filho->chaves[GRAU_MINIMO - 1];
    no->numChaves++;
}

int main() {
    NoArvoreB* raiz = criarNo(GRAU_MINIMO, 1);
    inserir(&raiz, 10);
    inserir(&raiz, 20);
    inserir(&raiz, 5);
    inserir(&raiz, 6);
    inserir(&raiz, 12);
    inserir(&raiz, 30);
    inserir(&raiz, 7);
    inserir(&raiz, 17);

    printf("Percorrendo a árvore construída:\n");
    percorrer(raiz);

    int chave = 6;
    buscar(raiz, chave) != NULL ? printf("\nPresente") : printf("\nNão Presente");

    chave = 15;
    buscar(raiz, chave) != NULL ? printf("\nPresente") : printf("\nNão Presente");

    return 0;
}
