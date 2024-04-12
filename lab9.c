#include <stdio.h>
#include <stdlib.h>
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{	
	int id;
	char name;
	int order;

};

// Compute the hash function
int hash(int x)
{	return x % 10;

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

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
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

	for (i=0;i<hashSz;++i)
	{	
		printf("Index %d ->", i);
		struct HashType* current = pHashArray[i].order;
		while(current != NULL){
		printf("%d %c %d", pHashArray->id, pHashArray->name, pHashArray->order);
		
		}
	}
}

int main(void)
{	
	struct RecordType *pRecords;
	struct HashType *pHash;
	int recordSz = 0;
	int hashSz = 0;
	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	for(int i = 0; i < hashSz; i++){
		pHash[i].order = NULL;
	}
	for(int i = 0; i <recordSz; i++){
		int index = hash(pRecords[i].id);
		struct HashType* newNode = (struct HashType*)malloc(sizeof(struct HashType));
        if(newNode ==NULL){
			printf("Memory allocation failed.\n");
		}
		newNode->id = pRecords[i]; 
        newNode->order = pHash[index].order; 
        pHash[index].order = newNode;
	}
printf("Records in the hash table:\n");
    for (int i = 0; i < hashSz; ++i) {
        printf("Index %d -> ", i);
        struct HashType* current = pHash[i].order;
        while (current != NULL) {
            printf("%d %c %d -> ", current->id, current->name, current->order);
            current = current->order;
        }

}
}
