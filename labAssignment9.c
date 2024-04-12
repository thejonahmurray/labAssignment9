//Jonah Murray
//COP3502C
//041024

#include <stdio.h>
#include <stdlib.h>

struct RecordType {
    int id;
    char name;
    int order;
};

//Node for recordType
struct ListNode {
    struct RecordType data;
    struct ListNode* next;
};

//Hashtype struct
struct HashType {
    struct ListNode** array;
    int size;
};

//Create new list node
struct ListNode* newListNode(struct RecordType data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int hash(int x, int hashSize) {
    return x % hashSize;
}

//Insert record function
void insertRecord(struct HashType* hashTable, struct RecordType data) {
    int index = hash(data.id, hashTable->size);
    struct ListNode* newNode = newListNode(data);
    newNode->next = hashTable->array[index];
    hashTable->array[index] = newNode;
}

//Function to display records in the hash table
void displayRecordsInHash(struct HashType *hashTable) {
    printf("\nHash Table:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct ListNode* node = hashTable->array[i];
        if (node != NULL) {
            printf("Index %d -> ", i);
            while (node != NULL) {
                printf("%d %c %d -> ", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

//Parses through data
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

//Print
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


int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;
    const int hashSz = 10;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    //Intialize table
    struct HashType hashTable;
    hashTable.size = hashSz;
    hashTable.array = (struct ListNode**)malloc(hashSz * sizeof(struct ListNode*));
    for (int i = 0; i < hashSz; ++i) {
        hashTable.array[i] = NULL;
    }

    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hashTable, pRecords[i]);
    }
    displayRecordsInHash(&hashTable);

    return 0;
}