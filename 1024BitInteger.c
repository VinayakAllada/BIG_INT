                                               //NAME    : VINAYAK ALLADA
                                               //EN_ROLL: BT23CSE067
                                               //DATE  : 24-01-2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 310

typedef struct {
    char num[SIZE];
    int sign;
} bigInt;


void additionOfTwoBigIntegers(bigInt n1, bigInt n2, bigInt* result);
void subtractionOfTwoBigIntegers(bigInt n1, bigInt n2, bigInt* result);


void skipZeroes(bigInt* n) {
    int len = strlen(n->num);
    int start = 0;

    // Find the first non-zero character
    while (start < len - 1 && n->num[start] == '0') {
        start++;
    }

    // If all characters are zero, set the number to "0"
    if (start == len - 1 && n->num[start] == '0') {
        n->num[0] = '0';
        n->num[1] = '\0';
        n->sign = 1; // Normalize the sign for zero
    } else {
        // Move the non-zero part to the beginning of the string
        memmove(n->num, n->num + start, len - start + 1);
    }
}

// Function to read input and set the sign
void readInput(bigInt* n) {

    printf("Enter the number: ");
    scanf("%s", n->num);

    if (n->num[0] == '-') {
        n->sign = -1;
        memmove(n->num, n->num + 1, strlen(n->num)); // Remove the '-' sign
    } 
    else {
        n->sign = 1;
        if(n->num[0] == '+'){
           memmove(n->num, n->num + 1, strlen(n->num)); 
        }
    }

    if (strcmp(n->num, "0") == 0) {
        n->sign = 1; // Normalize the sign for zero
    }
    
    for(int i=0; i<strlen(n->num); i++){
        if(n->num[i]<'0' || n->num[i]>'9'){
            printf("Invalid input. Please enter a valid number.\n");
            readInput(n);
            return;
        }
    }
}

// Function to add two bigInt numbers
void additionOfTwoBigIntegers(bigInt n1, bigInt n2, bigInt* result) {

    if (strcmp(n1.num, "0") == 0) {
        *result = n2; // If n1 is 0, the result is n2
        return;
    }
    if (strcmp(n2.num, "0") == 0) {
        *result = n1; // If n2 is 0, the result is n1
        return;
    }

    char tempResult[SIZE] = {0};
    int len1 = strlen(n1.num);
    int len2 = strlen(n2.num);

    // Initialize result
    memset(result->num, '0', SIZE);
    result->num[SIZE - 1] = '\0';


    int k = SIZE - 2, carry = 0;

    if (n1.sign == n2.sign) {

        // Same signs, perform addition
        result->sign = n1.sign;
        for(int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry>0 ; i--, j--) {
            int digit1 = (i >= 0) ? n1.num[i] - '0' : 0;
            int digit2 = (j >= 0) ? n2.num[j] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            tempResult[k--] = (sum % 10) + '0';
            carry = sum / 10;
        }
    } 
    else {
        // Opposite signs, convert to subtraction
        if (n1.sign == -1) {
            n1.sign = 1;
            subtractionOfTwoBigIntegers(n2, n1, result);
            return;
        } else {
            n2.sign = 1;
            subtractionOfTwoBigIntegers(n1, n2, result);
            return;
        }
    }


    // Copy tempResult to result.num, removing leading zeros
    int start = k + 1;
    strcpy(result->num, tempResult + start);
    skipZeroes(result);

    return ;
}

void subtractionOfTwoBigIntegers(bigInt n1, bigInt n2, bigInt* result) {
    if (strcmp(n2.num, "0") == 0) {
        *result = n1; // If n2 is 0, the result is n1
        return;
    }
    if (strcmp(n1.num, "0") == 0) {
        *result = n2; // If n1 is 0, the result is -n2
        result->sign = -n2.sign;
        return;
    }

    int len1 = strlen(n1.num), len2 = strlen(n2.num);

    if (n1.sign != n2.sign) {
        // Different signs, convert to addition
        n2.sign = -n2.sign;
        additionOfTwoBigIntegers(n1, n2, result);
        return;
    }

    // Determine which number is larger in absolute value
    int compareResult = strcmp(n1.num, n2.num);
    int isNegative = 0;

    if (len1 < len2 || (len1 == len2 && compareResult < 0)) {
        isNegative = 1;
        bigInt temp = n1;
        n1 = n2;
        n2 = temp;
    }

    // Initialize result
    memset(result->num, '0', SIZE);
    result->num[SIZE - 1] = '\0';
    
    char tempResult[SIZE] = {0};
    int k = SIZE - 2, borrow = 0;

    // Perform subtraction
    for(int i = strlen(n1.num) - 1, j = strlen(n2.num) - 1; i >= 0; i--, j--) {
        int digit1 = n1.num[i] - '0';
        int digit2 = (j >= 0) ? n2.num[j] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        tempResult[k--] = diff + '0';
    }

    // Copy result and set sign
    strcpy(result->num, tempResult + k + 1);
    
    // Determine the final sign
    if (n1.sign == 1) {
        result->sign = isNegative ? -1 : 1;
    } else {
        result->sign = isNegative ? 1 : -1;
    }

    skipZeroes(result);
}



// Function to multiply two bigInt numbers
void multiplicationOfTwoBigIntegers(bigInt n1, bigInt n2, bigInt* result) {

    if (strcmp(n1.num, "0") == 0 || strcmp(n2.num, "0") == 0) {

        // If either number is 0, the result is 0
        strcpy(result->num, "0");
        result->sign = 1;
        return;
    }

    int len1 = strlen(n1.num), len2 = strlen(n2.num);
    int tempResult[SIZE] = {0};

    // Initializing result
    memset(result->num, '0', SIZE);
    result->num[SIZE - 1] = '\0';

    // Performing multiplication
    for (int i = len1 - 1; i >= 0; i--) {

        int carry = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int product = (n1.num[i] - '0') * (n2.num[j] - '0') + tempResult[i + j + 1] + carry;
            tempResult[i + j + 1] = product % 10;
            carry = product / 10;
        }
        tempResult[i] += carry;
    }

    // Converting tempResult to string
    int k = 0, start = 0;
    while (start < len1 + len2 && tempResult[start] == 0) {
        start++;
    }
    for (int i = start; i < len1 + len2; i++) {
        result->num[k++] = tempResult[i] + '0';
    }
    result->num[k] = '\0';

    // Handling sign
    result->sign = n1.sign * n2.sign;

    if (strlen(result->num) == 0) {
        strcpy(result->num, "0");
        result->sign = 1;
    }

    skipZeroes(result);
}

int main() {
    bigInt n1, n2, addRes, subRes, multiRes;

    int choice;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1:
                readInput(&n1);
                readInput(&n2);
                additionOfTwoBigIntegers(n1, n2, &addRes);
                printf("Addition Result: %s%s\n", (addRes.sign == -1) ? "-" : "", addRes.num);
                break;
            case 2:
                readInput(&n1);
                readInput(&n2);
                subtractionOfTwoBigIntegers(n1, n2, &subRes);
                printf("Subtraction Result: %s%s\n", (subRes.sign == -1) ? "-" : "", subRes.num);
                break;
            case 3:
                readInput(&n1);
                readInput(&n2);
                multiplicationOfTwoBigIntegers(n1, n2, &multiRes);
                printf("Multiplication Result: %s%s\n", (multiRes.sign == -1) ? "-" : "", multiRes.num);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}