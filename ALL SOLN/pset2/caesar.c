#include <stdio.h>
#include <cs50.h> // for getting user-input
#include <ctype.h> // for string operation
#include <string.h> // for strlen()
#include <stdlib.h> // for converting string into int

void Do_cipher(); // perform cipher
int check_keyBound(); // key boundations according to alphabets

int main(int argc, string argv[])
{
    if (argc == 2) //validating command-line argument
    {
        for (int i = 0, n = strlen(argv[1]); i < n ; i++) //accessing each character in argv[1]
        {
            if (! isdigit(argv[1][i])) // if there is no number in argv[1]
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }

        }

        Do_cipher(argv[1]); // run the program
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}



int check_keyBound(string k) // taking argv[1]
{
    int key = atoi(k); // string into int w.r.t it's values

    while (key > 26) //if key is above 'Z or z' letter
    {
        key -= 26; // subtract key value from 26 (ex: key = 27 then key = 27 - 26)
    }
    return key;
}


void Do_cipher(string k)
{
    int key = check_keyBound(k);// checking key bound

    string p = get_string("plaintext: ");
    
    int c[strlen(p)]; // to store all the ascii values of cipher text
	
	//NOTE:  we are printing c[i] individually . because, if we try to print c(cipher text) as a whole so it is encountering some pointer error.
    printf("ciphertext: ");

    for (int i = 0; i < strlen(p); i++) //for accessing each value inside plain text (p)
    {
        if (isalpha(p[i])) // if p[i] is alphabet
        {
            if (isupper(p[i])) // for uppercase
            {
                c[i] = p[i] + key; // shifting p[i] value by key value

                if (c[i] > 90) //checking character-bound
                {
                    c[i] -= 26; // same as [ ci = (pi + k) % 26 ]

                    printf("%c", c[i]);
                }
                else
                {
                    printf("%c", c[i]);
                }
            }
            else // for lowercase
            {
                c[i] = p[i] + key; // shifting p[i] value by key value

                if (c[i] > 122) //checking character-bound
                {
                    c[i] -= 26; // same as [ ci = (pi + k) % 26 ]
                    printf("%c", c[i]);
                }
                else
                {
                    printf("%c", c[i]);
                }
            }
        }
        else
        {
            c[i] = p[i]; // copy character as it is if didn't find any alphabet
            printf("%c", c[i]);
        }
    }
    
    printf("\n"); //for new line in terminal after printing cipher text
}
