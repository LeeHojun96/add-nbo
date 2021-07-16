#include <QCoreApplication>
#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <stdlib.h> // for reading bin file
#include <netinet/in.h> // for ntoh


void dump(void* p, size_t n) {
    uint8_t* u8 = static_cast<uint8_t*>(p);
    size_t i = 0;
    while (true) {
        printf("%02X ", *u8++);
        if (++i >= n) break;
        if (i % 8 == 0) printf(" ");
        if (i % 16 == 0) printf("\n");
    }
    printf("\n");
    printf("%d\n", *(uint32_t*)p);
}

FILE* readBin(char * name) {
    return fopen(name, "r");
}

void closeBin(FILE * fp) {
    fclose(fp);
}


int main(int argc, char *argv[])
{
    FILE *arg1, *arg2;
    uint32_t nNum1, nNum2, hNum1, hNum2, result;

    // read bin file
    arg1 = readBin(argv[1]);
    arg2 = readBin(argv[2]);

    fread(&nNum1, sizeof(nNum1),1 ,arg1);
    fread(&nNum2, sizeof(nNum2),1 ,arg2);


    // ntoh
    hNum1 = ntohl(nNum1);
    hNum2 = ntohl(nNum2);
    // exec add
    result = hNum1 + hNum2;

    //print result
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", hNum2, hNum2, hNum1, hNum1, result, result);

    // close fp
    closeBin(arg1);
    closeBin(arg2);

    return 0;
}
