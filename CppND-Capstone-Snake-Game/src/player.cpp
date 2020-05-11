#include <iostream>
#include "player.h"
using namespace std;

string Player::GetName() { return player_name; }

Player::Player()
{
    string name;
    cout << "Enter Your Name Please: ";
    cin >> name;
    player_name = name;
}

void Player::ConvertToLowerCase(string &play_again)
{
    //Change input from the user to lower case
    //Using pass-by-reference
    for (char &i : play_again)
        i = tolower(static_cast<unsigned char>(i));
}

bool Player::PlayAgain()
{
    while (true)
    {
        string play_again;
        cout << "Would you like to play agin? [y/n]: " << endl;
        cin >> play_again;

        ConvertToLowerCase(play_again);

        if (play_again == "n" || play_again == "no")
            return false;

        else if (play_again == "y" || play_again == "yes")
            return true;

        else
            return false;
    }
}