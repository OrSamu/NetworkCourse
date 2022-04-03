#include "clientUtils.h"

void printUserMenu()
{
    system("cls");

    cout << "1.  Get Time - will return current date and time" << endl;
    cout << "2.  Get Time Without Date - will return only the current time  " << endl;
    cout << "3.  Get Time Since Epoch - will return seconds passed from 01.01.1970 until now" << endl;
    cout << "4.  Get Client To Server Delay Estimation" << endl;
    cout << "5.  Measure RTT - will measure the round trip time" << endl;
    cout << "6.  Get Time Without Date Or Seconds - will return time by hh:mm" << endl;
    cout << "7.  Get Year - will return the current year" << endl;
    cout << "8.  Get Month and Day - will return the current day and month" << endl;
    cout << "9.  Get Seconds Since Begining Of Month - will return the number of seconds passed from the start of the month" << endl;
    cout << "10. Get Week Of Year - will return the number of week since the start of the year" << endl;
    cout << "11. Get Daylight Savings - will return if the daylight saving is on or off" << endl;
    cout << "12. Get Time Without Date In City - will return the time in chosen city" << endl;
    cout << "13. Measure Time Lap - will return the time past between client's requests (up to 3 minutes)" << endl;
    cout << "0.  Exit" << endl;
}

void printCityMenu()
{
	cout << "city menu is working" << endl;
}

int getUserRequest()
{
    int userInput;
    bool keepCheckingForValidation = true;

	printUserMenu();

    while (keepCheckingForValidation)
    {
        cin >> userInput;
        isInputValid(userInput) ? keepCheckingForValidation = false : keepCheckingForValidation = true;
        if (keepCheckingForValidation)
        {
            cout << "Invalid selection, please try again" << endl;
        }
    }

	return userInput;
}

void closeClient()
{
	char bye;
    bool waitForKeyPress = true;

	system("cls");
	cout << "Bye bye - press any key to exit the program" << endl;
    while (waitForKeyPress)
    {
        if (_kbhit())
        {
            waitForKeyPress = false;
        }
    }

    return;
}

bool isInputValid(int userInput)
{
    return userInput >= USER_MENU_MIN_OPTION && userInput <= USER_MENU_MAX_OPTION;
}