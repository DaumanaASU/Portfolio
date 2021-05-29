// David Alejandro Umana Fleck
// Programming environment used: VS
// Simple program with different functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable : 4996)

#define MAX_DIM 3 //Maximum matrix Dimensions
#define STUDENTS 5		//Number of students
#define MAX_LENGTH 50 //Maximum length of sentence
int matrixA[MAX_DIM][MAX_DIM], matrixB[MAX_DIM][MAX_DIM], sum[MAX_DIM][MAX_DIM];
int scores[STUDENTS];
int *pScores = NULL;


void inputMatrixA();
void copyToMatrixB();
void addMatrix();
void displaySumMatrix();
void inputScores();
void scoreStats();
void createUsername();
void lowerToUpperCase();
void searchPattern();

// Main
int main()
{
    printf("Matrix Sum Calculator\n");
    printf("===============================\n\n");
    inputMatrixA();

    copyToMatrixB();

    addMatrix();

    displaySumMatrix();
    printf("-------------------------------\n\n");

    printf("Score Average & Max Calculator\n");
    printf("===============================\n\n");
    
    inputScores();

    scoreStats();

    getchar();
    printf("-------------------------------\n\n");

	printf("Username Creation\n");
    printf("===============================\n\n");
    createUsername();
    
    printf("-------------------------------\n\n");
    printf("Conversion to Uppercase\n");
    printf("===============================\n\n");
    lowerToUpperCase();

    printf("-------------------------------\n\n");
    printf("Search in String\n");
    printf("===============================\n\n");
    searchPattern();

    //system("pause");	// needed to keep console open in VS
    return 0;
}



/*
Input the elements of matrixA from the user.
Note: Usually, matrix is entered row-wise. So input 1st row of elements , followed by 2nd row and so on.
*/
void inputMatrixA()
{
    int i, j;
    for (i = 0; i < MAX_DIM; i++) // outer for loop, i will be used as the rows, will repeat the same number of times as the MAX_DIM
    {
        for (j = 0; j < MAX_DIM; j++) // inner for loop, j will be used as the columns, will repeat the same number of times as the MAX_DIM
        {
            printf("Enter matrix element: ");
            scanf("%d", &matrixA[i][j]);    // reads the input and places it into matrixA in the corresponding place
        }
    }
}

/*
Copy elements of matrixA to matrixB. 
*/
void copyToMatrixB()
{
    memcpy(matrixB, matrixA, sizeof(matrixB)); // This will copy the elements of matrix A into matrixB, without the need for a for loop, which would be inefficient.
}


/*
Implements this math operation: (2*A) + B and stores the result in matrix 'sum'.
*/
void addMatrix()
{
    int i, j;  // Initializing counters for the loops
    for (i = 0; i < MAX_DIM; i++) // outer for loop, i will be used as the rows, will repeat the same number of times as the MAX_DIM
    {
        for (j = 0; j < MAX_DIM; j++) // inner for loop, j will be used as the columns, will repeat the same number of times as the MAX_DIM
        {
            sum[i][j] = 2*matrixA[i][j] + matrixB[i][j]; //each element of the matrix sum will be the 2 times the element in the same position in matrixA plus the element in that position in matrixB
        }
    }
}

/*
Displays the 'sum' matrix.
*/
void displaySumMatrix()
{
    int i,j;  // Initializing counters for the loops
    printf("\nThe matrix sum=\n");
    for (i = 0; i < MAX_DIM; i++)  // outer for loop, i will be used as the rows, will repeat the same number of times as the MAX_DIM
    {
        for (j = 0; j < MAX_DIM; j++)  // inner for loop, j will be used as the columns, will repeat the same number of times as the MAX_DIM
        {
            printf("%d\t", sum[i][j]);  // prints every element of a row in matrix sum
        }
        printf("\n");  // new line
    }
}

/*
Input the scores of students.
The valid range of score is 0 to 100 (0 and 100 included).
*/
void inputScores()
{
    int i = 0;  // initializes counter for loop
    int score;  // temporary variable to check if input is valid
    pScores = &scores[0];  // places address of element 0 of scores in the pointer
    while (i< STUDENTS)  // will repeat the same number of times as there are students
    {
        printf("Enter score %d: ", i+1);  // requests input
        scanf("%d",&score); // score = input
        if (score >=0 && score <=100) // checks if score is valid
        {
            *pScores = score; //assigns the value of score to the address stored in the pointer
            pScores++;  // moves the pointer to the next element
            i++;  // counter, it is inside the if statement, so that an invalid input will not affect the number of accepted inputs
        } else
        {
            printf("Enter a valid score (Between 0 and 100)\n");  // asks for a valid input.
        }
    }
}

/*
Find the maximum and the average of scores.
*/
void scoreStats()
{
    int i;  // initializes counter for loop
    int max = 0; // will hold max value
    int average = 0; // will hold average value
    pScores = &scores[0];
    for (i = 0; i<STUDENTS; i++) // will repeat the same number of times as there are students
    {
        if (*pScores > max) // checks if the current element is bigger than the current max
        {
            max = *pScores; // sets max to the current element
        }
        average = average + *pScores; // adds the current value to the average variable, which is at this point a running total
        pScores++; // moves the pointer to the next element
    }
    average = average/STUDENTS;  // Divides the total of all elements by the number of elements, giving the average
    printf("\nMax Score= %d\n", max); // displays the max value
    printf("Avg Score= %d\n", average); // displays the average value
}

/*
The username is the first letter of first name, followed by the last name.
*/
void createUsername()
{
    char firstName[15], lastName[15], userName[16]; // initializes the string arrays, changed the size of username array as having it any larger was redundant
    char *user = NULL;  // create a pointer
    user = &userName[0];  // sets pointer to first element of userName array
    printf("Enter your first name : "); // requests input
    fgets(firstName, 15, stdin); // records input in firstName
    firstName[strcspn(firstName, "\n")] = 0; // removes \n from the string
    printf("Enter your last name : "); // requests input
    fgets(lastName, 15, stdin); //records input as lastName
    lastName[strcspn(lastName, "\n")] = 0;  // removes \n from the string
    *user = toupper(firstName[0]);  // sets the first letter (In UPPERCASE) of the first name as the first element of userName
    user++;  //moves pointer to next element
    for (int i = 0; i < strlen(lastName); i++)  // for loop will run the same number of times as the length of the last name
    {
        *user = toupper(lastName[i]); // adds the every letter (In UPPERCASE) in the last name to userName
        user++;  // moves pointer to next element
    }
    *user = '\n';  // adds \n to userName after the last name
    userName[strcspn(userName, "\n")] = 0; // removes \n and all unused values from userName, this was done because userName was printing out the empty elements as unusual characters
    printf("User name : %s\n", userName );  // prints userName
}

/*
Count the number of lower case characters in sentence and convert lower case characters to upper case.
*/
void lowerToUpperCase()
{
	char sentence[MAX_LENGTH];
	printf("Enter sentence: \n");
	fgets(sentence, MAX_LENGTH, stdin);
    //char sentence[]="THiS SentENCE HAS SOMe LoWEr CASE ChARAcTERs";  // initializes and declare the sentence
    int lowerCases = 0;  // counts the number of lower case letters in the sentence
    for (int i = 0; sentence[i] != '\0'; i++)  // for loop will go thru all elements in the string
    {
        if (sentence[i] >= 'a' && sentence[i] <= 'z') // checks if the current element is a lower case letter
        {
            lowerCases++; // adds to the lower case counter
        }
        sentence[i] = toupper(sentence[i]);  // converts all letters to upper case
    }
    printf("\nNumber of lower case characters= %d \n", lowerCases);  // prints number of lower case letters
    printf("Upper case sentence : %s \n",sentence); // prints the sentence which is now all in UPPERCASE
}

/*
Search for a pattern in a string
*/
void searchPattern()
{
    char *str, *pattern;
    int strLen=128, patternLen=3;
    printf("Enter the N-character string which needs to be searched for a pattern: "); // request input
    str = malloc(sizeof(char)*strLen); //tried using realloc, however since we are given a maximum number of characters (128) I just allocated enough memory for that.
    pattern = malloc(sizeof(char)*patternLen); // allocate memory for pattern
    scanf("%128s",str); // save string
    printf("Enter the three character pattern to search: "); // request input
    scanf("%3s", pattern); // save pattern
    if (strstr(str, pattern)) // pattern exists
    {
        printf("\nPattern found \n");  // prints out the pattern was found
        printf("Pattern in location= %s \n", strstr(str, pattern));  /*this prints out the rest of the string starting from where the pattern is found,
                                                                            if we use %c and *strstr(str, pattern) it will print out the first letter of the pattern, and if we
                                                                            use %.3s instead it will only return the pattern, since it asks for the location I figured printing
                                                                            the whole string starting from the pattern was the most useful
                                                                            */
    } else //pattern does not exist
    {
        printf("Pattern not found \n");  // prints out that the pattern was not found
    }
}
