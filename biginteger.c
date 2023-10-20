#include "biginteger.h"
#include <stdlib.h>
#include <stdio.h>
// biginteger.c
#include "biginteger.h"

// Your other function implementations...

// Compare two big integers
int compareBigIntegers(const BigInteger* num1, const BigInteger* num2) {
    // Traverse the linked lists and compare each digit
    // Return a positive value if num1 is greater, a negative value if num2 is greater,
    // and 0 if they are equal.

    DigitNode* current1 = num1->head;
    DigitNode* current2 = num2->head;

    while (current1 != NULL && current2 != NULL) {
        if (current1->digit > current2->digit) {
            return 1;  // num1 is greater
        } else if (current1->digit < current2->digit) {
            return -1;  // num2 is greater
        }

        // Move to the next digit
        current1 = current1->next;
        current2 = current2->next;
    }

    // If one number has more digits than the other, the one with more digits is greater
    if (current1 != NULL) {
        return 1;  // num1 is greater
    } else if (current2 != NULL) {
        return -1;  // num2 is greater
    }

    // Both numbers are equal
    return 0;
}


// Function to initialize a big integer
void initializeBigInteger(BigInteger* num) {
    num->head = NULL;
}

// Function to insert a digit at the beginning of the big integer
void insertDigit(BigInteger* num, int digit) {
    DigitNode* newNode = (DigitNode*)malloc(sizeof(DigitNode));
    if (newNode == NULL) {
        exit(1); // Exit if memory allocation fails
    }

    newNode->digit = digit;
    newNode->next = num->head;
    num->head = newNode;
}

// Function to add two big integers
BigInteger addBigIntegers(const BigInteger* num1, const BigInteger* num2) {
    // Placeholder for the result
    BigInteger result;
    initializeBigInteger(&result);

    // Variables for carrying and current sum
    int carry = 0, sum;

    // Traverse both linked lists
    DigitNode *ptr1 = num1->head, *ptr2 = num2->head;

    while (ptr1 != NULL || ptr2 != NULL || carry != 0) {
        // Get digits from each linked list (or 0 if the list is shorter)
        int digit1 = (ptr1 != NULL) ? ptr1->digit : 0;
        int digit2 = (ptr2 != NULL) ? ptr2->digit : 0;

        // Calculate sum including carry
        sum = digit1 + digit2 + carry;

        // Calculate the carry for the next iteration
        carry = sum / 10;

        // Update the result with the current digit
        insertDigit(&result, sum % 10);

        // Move to the next nodes, if available
        if (ptr1 != NULL) ptr1 = ptr1->next;
        if (ptr2 != NULL) ptr2 = ptr2->next;
    }

    return result;
}

// Function to subtract two big integers (num1 - num2)
BigInteger subtractBigIntegers(const BigInteger* num1, const BigInteger* num2) {
    // Placeholder for the result
    BigInteger result;
    initializeBigInteger(&result);

    // Variables for borrowing and current difference
    int borrow = 0, diff;

    // Traverse both linked lists
    DigitNode *ptr1 = num1->head, *ptr2 = num2->head;

    while (ptr1 != NULL || ptr2 != NULL) {
        // Get digits from each linked list (or 0 if the list is shorter)
        int digit1 = (ptr1 != NULL) ? ptr1->digit : 0;
        int digit2 = (ptr2 != NULL) ? ptr2->digit : 0;

        // Calculate difference including borrow
        diff = digit1 - digit2 - borrow;

        // Calculate the borrow for the next iteration
        borrow = (diff < 0) ? 1 : 0;

        // Update the result with the current digit
        insertDigit(&result, (diff + 10) % 10);

        // Move to the next nodes, if available
        if (ptr1 != NULL) ptr1 = ptr1->next;
        if (ptr2 != NULL) ptr2 = ptr2->next;
    }

    // Remove leading zeros
    while (result.head != NULL && result.head->digit == 0) {
        DigitNode* temp = result.head;
        result.head = result.head->next;
        free(temp);
    }

    return result;
}

BigInteger multiplyBigIntegers(const BigInteger* num1, const BigInteger* num2) {
    BigInteger result;
    initializeBigInteger(&result);

    // Traverse the first linked list (num1)
    DigitNode* ptr1 = num1->head;

    while (ptr1 != NULL) {
        // Variables for current product and carry
        int carry = 0;

        // Traverse the second linked list (num2)
        DigitNode* ptr2 = num2->head;

        // Initialize the temporary result for the current multiplication
        BigInteger tempResult;
        initializeBigInteger(&tempResult);

        // Multiply the current digit of num1 with each digit of num2
        while (ptr2 != NULL) {
            int product = (ptr1->digit) * (ptr2->digit) + carry;
            carry = product / 10;

            // Append the current digit to the temporary result
            insertDigit(&tempResult, product % 10);

            ptr2 = ptr2->next;
        }

        // If there's a carry after the inner loop, append it to the result
        while (carry > 0) {
            insertDigit(&tempResult, carry % 10);
            carry /= 10;
        }

        // Left-shift the temporary result by the position of ptr1
        for (int i = 0; i < ptr1->digit; ++i) {
            insertDigit(&tempResult, 0);
        }

        // Add the current multiplication result to the overall result
        result = addBigIntegers(&result, &tempResult);

        // Move to the next node in the first linked list
        ptr1 = ptr1->next;
    }

    return result;
}

BigInteger divideBigIntegers(const BigInteger* num1, const BigInteger* num2) {
    BigInteger result;
    initializeBigInteger(&result);

    // Create a copy of num1 to be modified during the division
    BigInteger dividend;
    initializeBigInteger(&dividend);

    // Copy the digits from num1 to dividend
    DigitNode* ptr1 = num1->head;
    while (ptr1 != NULL) {
        insertDigit(&dividend, ptr1->digit);
        ptr1 = ptr1->next;
    }

    // While dividend is greater than or equal to num2
    while (compareBigIntegers(&dividend, num2) >= 0) {
        // Initialize quotient digit and temporary result
        int quotientDigit = 0;
        BigInteger tempResult;
        initializeBigInteger(&tempResult);

        // Perform long division
        while (compareBigIntegers(&dividend, num2) >= 0) {
            dividend = subtractBigIntegers(&dividend, num2);
            quotientDigit++;

            // Append the quotient digit to the temporary result
            insertDigit(&tempResult, quotientDigit);
        }

        // Add the current division result to the overall result
        result = addBigIntegers(&result, &tempResult);
    }

    return result;
}


void displayBigInteger(const BigInteger* num) {
    DigitNode* current = num->head;

    // Skip leading zeros
    while (current != NULL && current->digit == 0) {
        current = current->next;
    }

    // If the number is zero, display a single zero
    if (current == NULL) {
        printf("0\n");
        return;
    }

    // Display the remaining digits
    while (current != NULL) {
        printf("%d", current->digit);
        current = current->next;
    }

    printf("\n");
}



// Function to free memory allocated for the big integer
void freeBigInteger(BigInteger* num) {
    DigitNode* current = num->head;
    DigitNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // After freeing the nodes, you might need to do additional cleanup, if any
    // For example, if there are other dynamically allocated components in your BigInteger structure

    // Clear the head to indicate an empty list
    num->head = NULL;
}

    // Initialize a temporary big
