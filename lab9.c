#include <stdio.h>
#include <stdlib.h>


struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};


struct HashType
{
    struct RecordType* hptr;
};

int hash(int x, int hashSz)
{
    return x % hashSz;
}

int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &pRecord->id);
			
			fscanf(inFile, "%c ", &pRecord->name);
			
			fscanf(inFile, "%d ", &pRecord->order);
			pRecord->next = NULL;
            
		}

        fclose(inFile);
    }
    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords: \n");
    for (i=0;i<dataSz;++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

void insertRecord(struct HashType hashArray[], struct RecordType record, int hashSz)
{
    int index = hash(record.id, hashSz);

    if (hashArray[index].hptr == NULL)
    {
        hashArray[index].hptr = &record;
    }
    else
    {
        struct RecordType* curr = hashArray[index].hptr;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = &record;
    }
}

void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    //Still need to fix 
    int i;
    struct RecordType *currRec;

    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);

        currRec = pHashArray[i].hptr;
        while (currRec != NULL)
        {
            printf("\t%d %c %d\n", currRec->id, currRec->name, currRec->order);
            currRec = currRec->next;
        }
    }
}


int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    
    int hashSz = 10;
    struct HashType* hashArray = (struct HashType*)calloc(hashSz,  sizeof(struct HashType));
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashArray, *(pRecords + i), hashSz);
    }
    
    displayRecordsInHash(hashArray, hashSz);
    
    free(pRecords);
    free(hashArray);
    return 0;
}