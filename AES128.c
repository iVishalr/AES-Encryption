//This is a quick and simple AES Encryption implementation using C Programming Language
//The below code takes in a Base64 encoded string(message) and and Base64 encoded Key from the 
//user and encrypts it according to AES algorithms and standards.
//As of now only 128 - bit level encryption is supported.

/*
  WARNING : THIS IMPLEMENTATION MUST NOT BE USED TO ENCRYPT AND DECRYPT TEXT,FILES OR ANYTHING
            AS IT IS VULNERABLE TO CACHE ATTACKS AND MANY OTHER ATTACKS AND HE OR SHE WHO IS 
            ATTACKING CAN READ THE BYTES SUBSTITUTED FROM S_BOX BY TIMING THEIR ATTACK WHILE
            THE ENCRYPTION IS TAKING PLACE.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"AES.h"
#include"AES_Encrypt.h"
#include"AES_Decrypt.h"

int system(const char* command);
void readMessage(unsigned char * message){

    printf("Enter the message to be encrypted in Base64 : ");
    unsigned char ch;
    int index = 0;
    while((ch=getchar())!='\n'){
        message[index] = ch;
        index++;
    }
}
void readKey(unsigned char * key){

    unsigned char c1;
    int index2=0;
    fflush(stdin);
    printf("Enter the key in Base64 : ");
    while((c1=getchar())!='\n' && index2<16){
        key[index2] = c1;
        index2++;
    }
}
void readMessageHex(unsigned char *message){

    int index=0;
    printf("\nEnter the message you want to decrypt : \nNote: Your message must be in Hexadecimal Format (eg. ae 7a 9b...) and must be separated by spaces.\n");
    printf("Message (Hex) : ");
    fflush(stdin);
    for(int i=0;i<index+16;i++){
        scanf("%02x",(unsigned int*)&message[i]);
        if(i==(index+16-1))
            index+=16;
        if(getchar()=='\n')
        break;
    }
}
void readHexKey(unsigned char *key){
    
    fflush(stdin);
    printf("\nEnter the key in Hexadecimal : \nNote: Your message must be in Hexadecimal Format (eg. ae 7a 9b...) and must be separated by spaces.\n");
    printf("Key (Hex) : ");
    for(int i=0;i<16;i++){
        scanf("%02x",(unsigned int*)&key[i]);
        if(getchar()=='\n')
            break;
    }
}
void readKeyType(unsigned char* key){
    
    printf("Choose any of the following : \n");
    printf("1. Enter Key in Base64.\n2. Enter Key in Hexadecimal.\n");
    char ch = getchar();
    if(ch=='1'){
        fflush(stdin);
        readKey(key);
    }
        else if(ch=='2'){
            fflush(stdin);
            readHexKey(key);
    }
    else{
        printf("\nPlease enter a valid choice.\n\n");
        fflush(stdin);
        readKeyType(key);
    }
}
char readChoice(unsigned char* message,unsigned char *key){

    printf("\nEnter any one of the following :-\n");
    printf("1. Encrypt Text\n2. Decrypt Text\n3. Quit\n");
    char c = getchar();
    if(c=='1'){
        fflush(stdin);
        readMessage(message);
        printf("\n");
        readKeyType(key);
        return '1';
    }
    else if(c=='2'){
        fflush(stdin);
        readMessageHex(message);
        printf("\n");
        fflush(stdin);
        readKeyType(key);
        return '2';
    }
    else if(c=='3')
        exit(0);
    else{
        printf("\nPlease enter a valid entry.\n\n");
        fflush(stdin);
        readChoice(message,key);
        return '\0'; 
    }
}
int main(void){
    unsigned char key[16];
    unsigned char message[1024];
    fflush(stdin);
    system("clear");
    printf("\nADVANCED ENCRYPTION STANDARDS - 128 Bit\n");
    fflush(stdin);
    char choice = readChoice(message,key);
    /*for(int i=0;i<64;i++)
        printf("%02x ",message[i]);
    printf("\n");*/
    int originalLen = strlen((const char*)message);
    int lenOfPaddedMessage = originalLen;

    clock_t start_t,end_t;

    if(lenOfPaddedMessage % 16!=0){
        lenOfPaddedMessage = (lenOfPaddedMessage/16 + 1)*16;
    }

    unsigned char paddedMessage[lenOfPaddedMessage];
    int k=0;
    for(int i=0;i<lenOfPaddedMessage;i++){

        if(i>=originalLen)
            paddedMessage[i] = 0;
        else
            paddedMessage[i] = message[i];
        k=i;
    }
    start_t = clock();
    unsigned char expandedKey[176];
    KeyExpansion(key,expandedKey);
    if(choice == '1'){
        for(int i=0;i<lenOfPaddedMessage;i+=16)
            AES_Encrypt(paddedMessage+i,expandedKey);
        end_t = clock();
        double total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
        printf("\nEncrypted Message : \n");
        for(int i=0;i<lenOfPaddedMessage;i++)
            printf("%02x ",paddedMessage[i]);
        printf("\n\n");
        printf("Length of Message : %d\n",originalLen);
        printf("Length of Encrypted Message : %d\n",lenOfPaddedMessage);
        printf("Time taken to encrypt : %lf seconds\n",total_t);
    }
    else
    {
        for(int i=0;i<lenOfPaddedMessage;i+=16)
            AES_Decrypt(paddedMessage+i,expandedKey);
        end_t = clock();
        double total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
        printf("\nDecrypted Message : \n");
        for(int i=0;i<lenOfPaddedMessage;i++)
            printf("%c",paddedMessage[i]);
        printf("\n\n");
        printf("Length of Message : %d\n",originalLen);
        printf("Length of Decrypted Message : %lu\n",strlen((const char*)paddedMessage));
        printf("Time taken to decrypt : %lf seconds\n",total_t);
    }
    return 0;
}
