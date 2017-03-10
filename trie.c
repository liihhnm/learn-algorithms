#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define FREE(p) free(p); \
                p = NULL;
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isLeaf;
};

struct TrieNode* getNode()
{
    struct TrieNode* pNode = NULL;
    pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;
        pNode->isLeaf = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
    return pNode;
}

void insert(struct TrieNode* root, const char* key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode* pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isLeaf = true;
}

bool search(struct TrieNode* root, const char* key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode* pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isLeaf);
}

bool leafNode(struct TrieNode* root)
{
    return root->isLeaf;
}

bool isItFreeNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
            return false;
    }
    return true;
}

bool deleteHelper(struct TrieNode* root, char* key, int level, int len)
{
    if (root)
    {
        if (level == len)
        {
            if (root->isLeaf)
            {
                root->isLeaf = false;
                if (isItFreeNode(root)) //check if key is other's prefix !
                    return true;
            }
            return false;
        }
        else
        {
            int index = CHAR_TO_INDEX(key[level]);

            if (deleteHelper(root->children[index], key, level + 1, len))
            {
                FREE(root->children[index]);
                return (!leafNode(root) && isItFreeNode(root)); //check if key inlcude other key
                                                                //and check if is the common branch
            }
        }
    }
    return false;
}

void deleteKey(struct TrieNode* root, char* key)
{
    int length = strlen(key);
    if (length > 0)
    {
        deleteHelper(root, key, 0, length);
    }
}

int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = { "the", "a", "there", "answer", "any",
        "by", "bye", "their" };

    char output[][32] = { "Not present in trie", "Present in trie" };


    struct TrieNode *root = getNode();

    // Construct trie
    int i;
    for (i = 0; i < ARRAY_SIZE(keys); i++)
        insert(root, keys[i]);
    deleteKey(root, "a");
    deleteKey(root, "there");

    // Search for different keys
    printf("%s --- %s\n", "the", output[search(root, "the")]);
    printf("%s --- %s\n", "there", output[search(root, "there")]);
    printf("%s --- %s\n", "these", output[search(root, "these")]);
    printf("%s --- %s\n", "their", output[search(root, "their")]);
    printf("%s --- %s\n", "thaw", output[search(root, "thaw")]);
    printf("%s --- %s\n", "a", output[search(root, "a")]);

    return 0;
}

