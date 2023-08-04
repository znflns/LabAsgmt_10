#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    struct TrieNode *children[26]; 
    int count; 
};

struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < 26; ++i) {
        node->children[i] = NULL;
    }
    node->count = 0;
    return node;
}

void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->count++;
}

int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
    } 
    return current->count;
}

void deallocateTrie(struct TrieNode *node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 26; ++i) {
        deallocateTrie(node->children[i]);
    }
    free(node);
}

int readDictionary(char *filename, char ***words) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        exit(1);
    }

    int numWords;
    fscanf(file, "%d", &numWords);
    *words = (char **)malloc(numWords * sizeof(char *));
    
    for (int i = 0; i < numWords; ++i) {
        (*words)[i] = (char *)malloc(100 * sizeof(char));
        fscanf(file, "%s", (*words)[i]);
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char **words = NULL;

    int numWords = readDictionary("dictionary.txt", &words);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", words[i]);
    }

    struct TrieNode *root = createTrieNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, words[i]);
    }

    char *testWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", testWords[i], numberOfOccurrences(root, testWords[i]));
    }

    deallocateTrie(root);
    
    for (int i = 0; i < numWords; ++i) {
        free(words[i]);
    }
    free(words);

    return 0;
}
