/**
 * Program: To check if two strings are anagram or not.
 * Author: Dev Mehta
 * Date: 5th Aug 2023.
*/
#include <stdio.h>
#include <string.h>


int areAnagrams(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    
    if (len1 != len2)
        return 0;

    
    int freq1[256] = {0};
    int freq2[256] = {0};


    for (int i = 0; i < len1; i++)
        freq1[str1[i]]++;

    
    for (int i = 0; i < len2; i++)
        freq2[str2[i]]++;

    
    for (int i = 0; i < 256; i++) {
        if (freq1[i] != freq2[i])
            return 0; 
    }

    return 1; 
}

int main() {
    char str1[100], str2[100];

    printf("Enter the first string: ");
    scanf("%s", str1);

    printf("Enter the second string: ");
    scanf("%s", str2);

    if (areAnagrams(str1, str2))
        printf("The strings are anagrams.\n");
    else
        printf("The strings are not anagrams.\n");

    return 0;
}
