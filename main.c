#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ERR "Error in the input.txt"
#define MAX 1000

bool isCapital(char c) {
    // Check whether string begins with Capital Latin Letter
    int pos = (int) c; // ASCII position of the character A -> 65, ... , Z -> 90
    if(pos >= 65 && pos <= 90) return true;
    return false;
}

bool isAllLatin(char s[]) {
    // Check whether all elements of the string is Latin Letter
    // in ASCII: a -> 97, ..., z -> 122
    for(int i = 1; i < strlen(s)-1; i++){
        // Loop through the string
        // If letter is not Latin then return false
        if(!(s[i] >= 97 && s[i] <= 122)) return false;
    }
    return true;
}

int strToInt(char s[]) {
    // Convert string to integer
    int n = 0;
    for(int i = 0; i < strlen(s)-1; i++){
        // Check elements are number else return -1
        if(!(s[i]-'0' >= 0 && s[i]-'0' <= 9)) return -1;
        n*=10;
        n+=(s[i]-'0');
    }
    // Converted integer
    return n;
}

bool strCompare(char str1[], char str2[]) {
    // Compare 2 strings if the second is lexical smaller then return true
    int i = 0;

    while(str1[i] != '\0' && str2[i] != '\0') {
        // check each letter
        if(str1[i] > str2[i] || str2[i]=='\n' || str2[i]=='\0') {
            return true;
        } else if(str1[i] < str2[i] ||str1[i]=='\n' || str1[i]=='\0') return false;
        i++;
    }

    // the first is equal or smaller
    return false;
}

int main()
{
    FILE *inFile;
    inFile = fopen("input.txt", "r");

    // ************ DECLARATIONS ************* //

    char str[MAX]; // string variable
    char strArray[MAX][MAX]; // main Array
    int targetCnt; // Desired number of lines
    int cnt = 0; // Count the number of lines on file

    FILE *outFile;
    outFile = fopen("output.txt", "w");
    fprintf(outFile, ERR);
    fclose(outFile);


    // ************ TESTING ************* //

    while(fgets(str, MAX, inFile)) {

        if(cnt == 0) {
            // Given in File, Desired number of lines
            targetCnt = strToInt(str);
            if(targetCnt == -1) return printf(ERR),0; // If it is not legal integer

            cnt++; // Another Line
            continue;
        }

        if(!(isAllLatin(str))) return printf(ERR),0; // Show Error msg when at least a element is not latin

        if(!(isCapital(str[0]))) return printf(ERR),0; // Show Error msg when first elem is not Capital


        strncpy(strArray[cnt-1], str, MAX); // Initialize main string array

        cnt++; // Another Line

        if(cnt > targetCnt+1) return printf(ERR),0; // if the number of lines is exceeded
    }

    if(cnt != targetCnt+1) return printf(ERR),0; // if the number of lines is not enough

    fclose(inFile);

    // ************ END OF TEST CASES ************** //


    // ************ MAIN ALGORITHM ************* //

    for(int i = 0; i < targetCnt; i++){
        // Loop through the string to check again
        for(int j = 0; j < targetCnt-1; j++){

            if(strCompare(strArray[j], strArray[j+1])){
                // if the second is lexicographically smaller than the first
                char cache[MAX];
                strncpy(cache, strArray[j], MAX);
                strncpy(strArray[j], strArray[j+1], MAX);
                strncpy(strArray[j+1], cache, MAX);
            }

        }
    }

    // ************ OUTPUT ************* //

    FILE *initFile;
    initFile = fopen("output.txt", "w");
    for(int i = 0; i < targetCnt; i++){
        fprintf(initFile, "%s", strArray[i]);
    }
    fclose(initFile);

    return 0;
}
