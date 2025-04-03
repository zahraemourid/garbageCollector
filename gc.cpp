#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10  // Nombre maximum de blocs de m�moire
#define BLOCK_SIZE 5   // Taille de chaque bloc en �l�ments

// Structure pour repr�senter un bloc de m�moire
typedef struct Block {
    int in_use;    // Marqueur : 1 si utilis�, 0 si inutilis�
    int* data;     // Pointeur vers la zone m�moire allou�e
} Block;

// Fonction d'allocation de m�moire pour un bloc
void allocateBlock(Block* block) {
    block->data = (int*)malloc(BLOCK_SIZE * sizeof(int));
    if (block->data != NULL) {
        block->in_use = 1;  // Marquer le bloc comme utilis�
        printf("Bloc allou�.\n");
    } else {
        printf("�chec de l'allocation de m�moire.\n");
    }
}

// Fonction pour lib�rer la m�moire d'un bloc
void freeBlock(Block* block) {
    if (block->data != NULL) {
        free(block->data);   // Lib�re la m�moire allou�e
        block->data = NULL;
        block->in_use = 0;    // Marque le bloc comme inutilis�
        printf("Bloc lib�r�.\n");
    }
}

// Fonction de compactage (d�place les blocs utilis�s vers le d�but)
void compactMemory(Block blocks[], int size) {
    int currentIndex = 0;  // Indice de la prochaine position pour un bloc actif

    printf("Compactage de la m�moire...\n");

    for (int i = 0; i < size; i++) {
        if (blocks[i].in_use) {
            // Si le bloc est utilis�, on le d�place vers le d�but
            if (i != currentIndex) {
                blocks[currentIndex].data = blocks[i].data;  // D�placer le bloc
                blocks[currentIndex].in_use = 1;
                blocks[i].data = NULL;  // R�initialiser l'ancien emplacement
                blocks[i].in_use = 0;
            }
            currentIndex++;  // Passer � l'emplacement suivant
        }
    }

    // Lib�rer les blocs inutilis�s restants
    for (int i = currentIndex; i < size; i++) {
        freeBlock(&blocks[i]);
    }

    printf("Compactage termin�. La m�moire a �t� lib�r�e.\n");
}

// Fonction principale pour tester le garbage collector
int main() {
    Block blocks[MAX_BLOCKS] = {0};  // Initialisation des blocs

    // Simulation d'allocations de blocs
    allocateBlock(&blocks[0]);
    allocateBlock(&blocks[2]);
    allocateBlock(&blocks[4]);
    allocateBlock(&blocks[7]);

    // Modification de l'�tat des blocs
    printf("Modification de l'�tat des blocs...\n");
    blocks[2].in_use = 0;  // Marquer le bloc 2 comme inutilis�
    blocks[7].in_use = 0;  // Marquer le bloc 7 comme inutilis�

    // Affichage avant compactage
    printf("Avant compactage:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Bloc %d: %s\n", i, blocks[i].in_use ? "utilis�" : "inutilis�");
    }

    // Lancer le garbage collector (compaction)
    compactMemory(blocks, MAX_BLOCKS);

    // Affichage apr�s compactage
    printf("\nApr�s compactage:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Bloc %d: %s\n", i, blocks[i].in_use ? "utilis�" : "inutilis�");
    }

    // Lib�rer la m�moire pour les blocs restants
    for (int i = 0; i < MAX_BLOCKS; i++) {
        freeBlock(&blocks[i]);
    }

    return 0;
}

