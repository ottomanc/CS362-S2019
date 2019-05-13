//Colleen Ottomano
//CS 362 Spring 2019
//Random Test Quiz

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    char charOptions[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','(',')','{','}','[',']'};
    char chosenChar;
    int r1;   //random number to select from the array
    r1 = rand() % 33;   //choose a number from 0-32
    chosenChar = charOptions[r1];
    return chosenChar;
}

char *inputString()
{
    // TODO: rewrite this function
    //string should be of length 6
    int stringLength;
    stringLength = 6;
    //Reusing similar code to the inputChar
    char charOptions[] = {'\0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int r1;   //random number to select from the array
    //set up the string
    char chosenString[6] = {' ',' ',' ',' ',' ',' '};
    //for each char in the array
    for(int i=0; i<6; i++){
      r1 = rand() % 27;   //choose a number from 0-32
      chosenString[i] = charOptions[r1];
    }

    return chosenString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
