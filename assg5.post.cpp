//Drew Post
//CS1428 Fall 2018
//Assignment 5

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iomanip>


using namespace std;

struct Case
{
    int caseNumber;
    float dollarAmount;
    bool available; //determines if case is opened
};

void swap(int a, int b, float prices[]) //helps set up scramble function
{
    if(a == b) //if the indexes are the same, leave it
    {
        return;
    }

    int temp = prices[a]; //holds a value
    prices[a] = prices[b]; //assigns b value to the a position
    prices[b] = temp; //assigns a value with b position

}

void scrambleArray(float prices[]) //will scramble the prices array so that every case gets a unique price
{
    srand(time(0)); //ensures truly random numbers every time

    int timesToRun = 500 + (rand() % 300); //the timesToRun variable's purpose is to randomize how many times the array will be shuffled. the 500 and 300 were just random numbers that were chosen
    for(int i = 0; i < timesToRun; i++) //for the amount of times timesToRun generates
    {
        swap(rand() % 26, rand() % 26, prices); //swap places in price array
    }

    //by swapping the values a random number of times ensures that there is a very minimal chance that the arrangement of prices for the cases will be the same
}
void assignCaseInfo(Case cases[], float prices[], int size) //gives case struct default values
{

    for(int i = 0; i < size; i++) //assigns to all cases
    {
        cases[i].caseNumber = i + 1; //makes case range (1-26) rather than (0-25)
        cases[i].dollarAmount = prices[i]; //assigns dollar amount to price in price array
        cases[i].available = true; //none of the cases have been opened yet
    }
}

void caseDisplay(int chosenCase) //displays case
{
        cout << "         ----------------------           " << endl;
        cout << "         |                    |           " << endl;
        cout << "         |                    |           " << endl;

        if(chosenCase > 9 && chosenCase < 27) //spacing for if the user's case is between (10-26)
        {
            cout << "         |      CASE: " << chosenCase << "      |           " << endl;
        }

        else if(chosenCase > 0 && chosenCase < 10) //spacing for if the user's case is between (1-9)
        {
            cout << "         |      CASE: " << chosenCase << "       |           " << endl;
        }

        cout << "         |                    |           " << endl;
        cout << "         |                    |           " << endl;
        cout << "         ----------------------           " << endl;
        cout << "              ||________||                " << endl;
        cout << "              ------------                " << endl;
        cout << "                                          " << endl;

}

void openCase(Case cases[], int chosenCase) //opens the case the user wants to open
{
    caseDisplay(chosenCase);
    cout << endl;
    cout << endl;
    cout << "        CASE " << cases[chosenCase - 1].caseNumber << " contains $" << fixed << setprecision(2) << cases[chosenCase - 1].dollarAmount << endl; //displays dollar amount
    cases[chosenCase - 1].available = false; //marks case as opened so the user can't open it again
    cout << endl;
}

void infoStillInPlay(Case cases[], int size, float pricesCopy[], int userCase)
{

    cout << "         DOLLAR AMOUNTS REMAINING: " << endl;
    cout << endl;
    cout << "    ";

   for(int i = 0; i < size; i++)
   {
       for(int j = 0; j < size; j++)
       {
           //if the price from the sorted copy of price array matches the case dollar amount/is unopened OR if the price from the sorted copy of price array matches the user's personal case, print the price in ascending order
           if((pricesCopy[i] == cases[j].dollarAmount) && cases[j].available == true || (cases[j].caseNumber == userCase && pricesCopy[i] == cases[j].dollarAmount)) //i made a copy of the original price array so i can display remaining prices in ascending order
           {
               cout << pricesCopy[i];

             if(i != size - 1) //prints commas for all the prices except the first one
            {
                cout << ", ";
            }

            if(i % 13 == 0) //separates prices to look more organized
            {
                cout << endl;
                cout << "    ";
            }


           }
       }
   }

    cout << endl;
    cout << endl;
    cout << endl;

    cout << "         CASES REMAINING: " << endl;
    cout << endl;
    cout << "    ";

    for(int i = 0; i < size; i++) //displays available case numbers
    {
        if(cases[i].available == true)
        {

            cout << cases[i].caseNumber;

            if(i != size - 1) //prints commas for all the prices except the first one
            {
                cout << ", ";
            }

            if(i % 13 == 0) //separates prices to look more organized
            {
                cout << endl;
                cout << "    ";
            }

        }
    }
}

float bankOffer(Case cases[], int size, int casesLeft) //calculates bank offer based on the cases left
{
    float sum = 0;
    for(int i = 0; i < size; i++) //cycles through all 26 cases
    {
        if(cases[i].available == true) //if the case hasn't been opened yet
        {
            sum = sum + cases[i].dollarAmount; //add it to the sum
        }
    }

    float offer = sum / casesLeft; //calculate average of all unopened cases

    return offer;
}

void printBankOffer(Case cases[], int size, int casesLeft) //prints bank offer, makes it so i can use the bankOffer function in other contexts
{
    cout << "       * BANK OFFER: $" << bankOffer(cases, size, casesLeft) << " *" << endl;
    cout << endl;
}

void deal(Case cases[], int userCase, int size, int casesLeft) //if user picks deal
{
    cout << "   ** YOU WON $" << bankOffer(cases, size, casesLeft) << "! **" << endl; //print what they won
    cout << "   * Your personal case had $" << cases[userCase].dollarAmount << " *" << endl; //print what they could've won
    cout << endl;
}

int main()
{
    int userCase; //the user's personal case
    string userChoice; //for if the user chooses deal or no deal
    string finalChoice; //for final round when the user decides to either keep their case or switch their case for the last one
    struct Case cases[26]; //holds the case information
    float prices[26] = {0.01, 1.00, 5.00, 10.00, 25.00, 50.00, 75.00, 100.00, 200.00, 300.00, 400.00, 500.00, 750.00, 1000.00, 5000.00, 10000.00, 25000.00, 50000.00, 75000.00, 100000.00, 200000.00, 300000.00, 400000.00, 500000.00, 750000.00, 1000000.00};
    float pricesCopy[26] = {0.01, 1.00, 5.00, 10.00, 25.00, 50.00, 75.00, 100.00, 200.00, 300.00, 400.00, 500.00, 750.00, 1000.00, 5000.00, 10000.00, 25000.00, 50000.00, 75000.00, 100000.00, 200000.00, 300000.00, 400000.00, 500000.00, 750000.00, 1000000.00};
    //first price array sets prices up to be scrambled, second array sets prices up for remaining ones to be displayed after each turn
    int numOpened = 0; //keeps track of how many cases the user has opened in order to determine when to end a round
    int chosenCase; //holds case number of the case the user wants to open during the rounds
    const int NUM_CASES = 26;
    int casesLeft = 26; //keeps track of how many cases are left in order to calculate the bank offer
    int round[10] = {6, 5, 4, 3, 2, 1, 1, 1, 1, 0}; //array of how many cases are supposed to be opened in each round
    int roundNum = 0; //keeps track of the round number which will reference the values in the array above
    bool gameOver = false; //keeps track of when to end the game

    cout << endl;
    cout << "      ** DEAL OR NO DEAL **" << endl;
    cout << endl;

    //scrambles prices to assign to cases
    scrambleArray(prices);

    //initialize cases
    assignCaseInfo(cases, prices, NUM_CASES);

    //picking a personal case
    do
    {
        //prompting user
        cout << endl;
        cout << "     PICK PERSONAL CASE (1-26): ";
        cin >> userCase; //store the user's choice
        cout << endl;
        cout << "--------------------------------------------" << endl;
        cout << endl;

        //error checking
        if(userCase > 26 || userCase <= 0) //checks if user choice is in bounds
        {
            cout << "      ERROR: Pick a case between (1-26)";
            cout << endl;
            cout << endl;
            cout << "--------------------------------------------" << endl;
            cout << endl;
        }

    }
    while(userCase > 26 || userCase <= 0); //do this until the user picks a case in bounds


    if(userCase <= 26 && userCase >= 1) //if the choice is in bounds
    {
        cout << "             Player case: " << userCase << endl; //displays case
        cases[userCase - 1].available = false; //sets user's personal case to unavailable to open during the rounds

        cout << endl;
        caseDisplay(userCase); //outprint case 'graphic'
        cout << "--------------------------------------------" << endl;
    }

    cout << endl;



        while(numOpened < round[roundNum] && !gameOver) //while the number of cases opened is less than the number of cases that are supposed to be opened (it'll cycle one extra time because numOpened starts at 0, so it'll cycle the number of times i want it to)
        {
            cout << endl;
            cout << "          OPEN A CASE (1-26): ";
            cin >> chosenCase; //stores user's choice
            cin.ignore(chosenCase, '\n'); //this input has to be ignored from the stream so the user can enter deal or no deal and get the appropriate feedback using getline
            cout << endl;
            cout << endl;

            if(chosenCase < 1 || chosenCase > 26 || cases[chosenCase - 1].available == false)
            {
                cout << "          ERROR: Pick a new case" << endl; //error checking, makes sure case is within bounds and hasn't been opened yet
                cout << endl;
                cout << "--------------------------------------------" << endl;
                cout << endl;
            }

            else
            {
                openCase(cases, chosenCase); //open the case
                numOpened++; //increments the number of cases opened

                casesLeft--; //decrements the number of cases left

                cout << endl;
                cout << "--------------------------------------------" << endl;
                cout << endl;

                infoStillInPlay(cases, NUM_CASES, pricesCopy, userCase); //display cases/prices left

                cout << endl;
                cout << endl;
                cout << "--------------------------------------------" << endl;
                cout << endl;

                if(numOpened == round[roundNum]) //if this is the last case of the round, this works because the roundNum will increment before this implements and before the round ends, calling this loop
                {
                    bankOffer(cases, NUM_CASES, casesLeft); //calculate bank offer
                    printBankOffer(cases, NUM_CASES, casesLeft); //print bank offer

                    cout << "--------------------------------------------" << endl;
                    cout << endl;
                    cout << "         DEAL OR NO DEAL? "; //prompts user
                    getline(cin, userChoice); //allows user to enter an answer with multiple words and stores it in userChoice
                    cout << endl;
                    cout << "--------------------------------------------" << endl;

                    if(userChoice.compare("deal") == 0 || userChoice.compare("Deal") == 0) //if the user enters deal
                    {
                        cout << endl;
                        deal(cases, userCase, NUM_CASES, casesLeft); //display deal info
                        gameOver = true; //ends game
                    }

                    else if(userChoice.compare("No Deal") == 0 || userChoice.compare("no deal") == 0 || userChoice.compare("No deal") == 0) //if user enters no deal
                    {
                        roundNum++; //increments round, continuing the game
                        numOpened = 0; //resets number of cases opened for the new round
                        gameOver = false; //continues game
                        cout << endl;

                        if(roundNum == 9) //if its the last round (round 9)
                        {
                            cout << "-------------------------------------------------" << endl;
                            cout << "                FINAL ROUND                  " << endl;
                            cout << endl;
                            cout << "  Your case is " << userCase << "." << endl; //tells user what case is their personal case

                            int lastCaseNum = 0;

                            for(int i = 0; i < NUM_CASES; i++)
                            {
                                if(cases[i].available == true)
                                {
                                    lastCaseNum = i;
                                    cout << "  The last case is " << lastCaseNum + 1 << "." << endl; //tells user what case is left
                                    break;
                                }
                            }

                            cout << endl;
                            cout << "------------------------------------------------" << endl;
                            cout << endl;
                            cout << "   Do you want to keep your personal case (Enter 'Keep')" << endl;
                            cout << "or switch it out for the last unopened case (Enter 'Switch')? "; //prompts user's final choice
                            cin >> finalChoice; //stores choice

                            cout << endl << endl;

                            if(finalChoice.compare("Keep") == 0 || finalChoice.compare("keep") == 0) //if user chooses to keep personal case
                            {
                                caseDisplay(userCase);
                                openCase(cases, userCase); //opens case

                                cout << "---------------------------------------------------" << endl; //displays results
                                cout << "| ** YOU WON: $" << cases[userCase].dollarAmount << "! **                       |" << endl;
                                cout << "|                                                 |" << endl;
                                cout << "|  The other case had: $" << cases[lastCaseNum].dollarAmount << "              |" << endl;
                                cout << "---------------------------------------------------" << endl;

                                gameOver = true;

                            }

                            else if(finalChoice.compare("Switch") == 0 || finalChoice.compare("switch") == 0) //if the user switches case out for last case
                            {
                                caseDisplay(lastCaseNum);
                                openCase(cases, lastCaseNum);

                                cout << "---------------------------------------------------" << endl; //displays results
                                cout << "| ** YOU WON: $" << cases[lastCaseNum].dollarAmount << "! **                    |" << endl;
                                cout << "|                                                 |" << endl;
                                cout << "| Your personal case had: $" << cases[userCase].dollarAmount << "              |" << endl;
                                cout << "---------------------------------------------------" << endl;

                                gameOver = true;

                            } //if user switches personal case with last case
                        } //if it's the final round in the game

                    } //else if user says no deal

                } //last case per round (if numOpened == round[roundNum])



            } //else - plays rounds


        } //while loop







    return 0;
}
