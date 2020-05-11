#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
public:
    Player();
    string GetName();
    bool PlayAgain();

private:
    void ConvertToLowerCase(string &play_again);

private:
    string player_name;
};

#endif