/* Alondra Rodriguez Manzueta
COP 3502C: Lab assignmnet 10*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* size[ALPHABET_SIZE];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode* root;
};

// Create a new Trie node
struct TrieNode* createTrieNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->size[i] = NULL;
    }
    newNode->count = 0;
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word) {
    struct TrieNode* curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->size[index] == NULL) {
            curr->size[index] = createTrieNode();
        }
        curr = curr->size[index];
    }
    curr->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word) {
    struct TrieNode* curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->size[index] == NULL) {
            return 0;
        }
        curr = curr->size[index];
    }
    return curr->count;
}

// Deallocate the trie node
struct TrieNode* deallocateTrieNode(struct TrieNode* pNode) {
    if (pNode == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->size[i] = deallocateTrieNode(pNode->size[i]);
    }
    free(pNode);
    return NULL;
}

// Deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie) {
    pTrie->root = deallocateTrieNode(pTrie->root);
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie* createTrie() {
    struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
    pTrie->root = createTrieNode();
    return pTrie;
}

// This function will read the dictionary file, count the number of words,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords) {
    FILE* fp;
    int numWords = 0;
    char word[256];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fscanf(fp, "%d", &numWords); // Read the number of words from the file

    for (int i = 0; i < numWords; ++i) {
        fscanf(fp, "%s", word);
        pInWords[i] = strdup(word);
    }

    fclose(fp);
    return numWords;
}

int main(void)
{
    char *inWords[256];
    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
        {
            printf("%s\n",inWords[i]);
        }

        struct Trie *pTrie = createTrie();
       for (int i=0;i<numWords;i++)
     {
       insert(pTrie, inWords[i]);
     }
     char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
     for (int i=0;i<5;i++)
     {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
     }
      pTrie = deallocateTrie(pTrie);
     if (pTrie != NULL)
    printf("There is an error in this program\n");
      return 0;
}