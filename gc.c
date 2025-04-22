#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10   
#define BLOCK_SIZE 5  

typedef struct Block {
    int in_use;     
    int* data;      
} Block;

// Fonction d'allocation de mémoire pour un bloc
void allocateBlock(Block* block) {
    block->data = (int*)malloc(BLOCK_SIZE * sizeof(int));
    if (block->data != NULL) {
        block->in_use = 1;  // Marquer le bloc comme utilisé
        printf("Bloc alloué.\n");
    } else {
        printf("Échec de l'allocation de mémoire.\n");
    }
}

// Fonction pour libérer la mémoire d'un bloc
void freeBlock(Block* block) {
    if (block->data != NULL) {
        free(block->data);    
        block->data = NULL;
        block->in_use = 0;     
        printf("Bloc libéré.\n");
    }
}

// Fonction de compactage (déplace les blocs utilisés vers le début)
void compactMemory(Block blocks[], int size) {
    int currentIndex = 0;  // Indice de la prochaine position pour un bloc actif

    printf("Compactage de la mémoire...\n");

    for (int i = 0; i < size; i++) {
        if (blocks[i].in_use) {
            if (i != currentIndex) {
                blocks[currentIndex].data = blocks[i].data;  // Déplacer le bloc
                blocks[currentIndex].in_use = 1;
                blocks[i].data = NULL;  // Réinitialiser l'ancien emplacement
                blocks[i].in_use = 0;
            }
            currentIndex++;  // Passer à l'emplacement suivant
        }
    }

    // Libérer les blocs inutilisés restants
    for (int i = currentIndex; i < size; i++) {
        freeBlock(&blocks[i]);
    }

    printf("Compactage terminé. La mémoire a été libérée.\n");
}

// Fonction principale pour tester le garbage collector
int main() {
    Block blocks[MAX_BLOCKS] = {0};  // Initialisation des blocs

    // Simulation d'allocations de blocs
    allocateBlock(&blocks[0]);
    allocateBlock(&blocks[2]);
    allocateBlock(&blocks[4]);
    allocateBlock(&blocks[7]);

    // Modification de l'état des blocs
    printf("Modification de l'état des blocs...\n");
    blocks[2].in_use = 0;  // Marquer le bloc 2 comme inutilisé
    blocks[7].in_use = 0;  // Marquer le bloc 7 comme inutilisé

    // Affichage avant compactage
    printf("Avant compactage:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Bloc %d: %s\n", i, blocks[i].in_use ? "utilisé" : "inutilisé");
    }

    // Lancer le garbage collector (compaction)
    compactMemory(blocks, MAX_BLOCKS);

    // Affichage après compactage
    printf("\nAprès compactage:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Bloc %d: %s\n", i, blocks[i].in_use ? "utilisé" : "inutilisé");
    }

    // Libérer la mémoire pour les blocs restants
    for (int i = 0; i < MAX_BLOCKS; i++) {
        freeBlock(&blocks[i]);
    }

    return 0;
}

