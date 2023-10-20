#ifndef BIGINTEGER_H
#define BIGINTEGER_H

// Structure for a node representing a digit in the big integer
typedef struct DigitNode {
    int digit;
    struct DigitNode* next;
} DigitNode;

// Structure for the big integer
typedef struct {
    DigitNode* head;
} BigInteger;
// Declaration for compareBigIntegers function

// Compare two big integers
int compareBigIntegers(const BigInteger* num1, const BigInteger* num2);


// Function to initialize a big integer
void initializeBigInteger(BigInteger* num);

// Function to insert a digit at the beginning of the big integer
void insertDigit(BigInteger* num, int digit);

// Function to add two big integers
BigInteger addBigIntegers(const BigInteger* num1, const BigInteger* num2);

// Function to subtract two big integers (num1 - num2)
BigInteger subtractBigIntegers(const BigInteger* num1, const BigInteger* num2);

// Function to multiply two big integers
BigInteger multiplyBigIntegers(const BigInteger* num1, const BigInteger* num2);

// Function to divide two big integers (num1 / num2)
BigInteger divideBigIntegers(const BigInteger* num1, const BigInteger* num2);

// Function to display the big integer
void displayBigInteger(const BigInteger* num);

// Function to free memory allocated for the big integer
void freeBigInteger(BigInteger* num);

#endif  // BIGINTEGER_H
