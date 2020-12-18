#include <cs50.h>
#include <stdio.h>

//identifying the function
int get_positive_int(string prompt);

//always have this in your code
int main(void)

{
    int number = get_positive_int("Height: "); //to get a number from a user 
   
    for (int height = 0; height < number; height++) // for loop inside loop to build blocks #
    {
        for (int dots = number - height - 2; dots >= 0; dots--)
        {
            printf(" "); //printing dots for visibility, then remove to space
        }
        for (int row = 0; row <= height; row++) //loop for rows
        {
            printf("#");
        }
        printf("\n");
    }
}

//get positive number from a user and executing the function
int get_positive_int(string prompt) 
{
    int number; //making new integer to copmly with task conditions
    do // do loop for runing code at least once
    {
        number = get_int("%s", prompt);
    }
    while (number < 1 || number > 8); // to display digits from 1 to 8 inclusive 
    return number; //will ask again if anything but 1-8 digits
}
