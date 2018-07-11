//
// Created by Paolo on 10/07/2018.
//

#ifndef ROCKPAPERSCISSORSLIZARDSPOCK_GAME_H
#define ROCKPAPERSCISSORSLIZARDSPOCK_GAME_H

#define MAX_VICTORIES 11
#define MAX_ROUNDS 20

enum hand {
    ROCK = 0,
    PAPER,
    SCISSORS,
    LIZARD,
    SPOCK
};

enum winner {
    WINNER_NONE,
    WINNER_MACHINE,
    WINNER_PLAYER,
    WINNER_DRAW
};

constexpr int playMap[5][5] = {
    {0, 1, -1,  -1, 1},
    {-1, 0, 1, 1, -1},
    {1, -1, 0, -1, 1},
    {1, -1, 1, 0, -1},
    {-1, 1, -1, 1, 0}
};

class Game {
private:
    int machine = 0;
    int player = 0;
    int round = 0;
public:
    int winner() const;
    int performRound(int machine, int player);
};


#endif //ROCKPAPERSCISSORSLIZARDSPOCK_GAME_H
