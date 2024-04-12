#include <stdio.h>
#include <stdlib.h> // Added for malloc and exit

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};


struct Node {
    struct RecordType data;
    struct Node* next;
};

// Fill out this structure
struct HashType
{
    struct Node** array; 
    int size; 
};


int hash(int x, int size)
{
    return x % size; 
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;
if (inFile == NULL) {
    printf("Error opening file: %s\n", inputFileName);
    return -1;
}
    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct Node* current = pHashArray->array[i];
        while (current != NULL) {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);
	printf("Number of records parsed: %d\n", recordSz);
    
    int hashSize = recordSz * 2; 
    struct HashType hashTable;
    hashTable.size = hashSize;
    hashTable.array = (struct Node**)malloc(hashSize * sizeof(struct Node*));
    if (hashTable.array == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    for (int i = 0; i < hashSize; ++i) {
        hashTable.array[i] = NULL;
    }

    
    for (int i = 0; i < recordSz; ++i) {
        int index = hash(pRecords[i].id, hashSize);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        newNode->data = pRecords[i];
        newNode->next = NULL;
        if (hashTable.array[index] == NULL) {
            hashTable.array[index] = newNode;
        } else {
            
            newNode->next = hashTable.array[index];
            hashTable.array[index] = newNode;
        }
		printf("Index: %d\n", index);
    }

    
    displayRecordsInHash(&hashTable, hashSize);


    for (int i = 0; i < hashSize; ++i) {
        struct Node* current = hashTable.array[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable.array);
    free(pRecords);

    return 0;
}
