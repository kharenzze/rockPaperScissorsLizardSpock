//
// Created by Paolo on 10/07/2018.
//

#ifndef ROCKPAPERSCISSORSLIZARDSPOCK_GAME_H
#define ROCKPAPERSCISSORSLIZARDSPOCK_GAME_H

#include <string>
#include <iostream>

#define MAX_VICTORIES 11
#define MAX_ROUNDS 20

const char* const MACHINE = "Machine";
const char* const USER = "User";
const char* const DRAW = "Draw! Nobody";

enum hand : int {
    ROCK = 0,
    PAPER,
    SCISSORS,
    LIZARD,
    SPOCK
};

enum winner : int {
    WINNER_NONE = 0,
    WINNER_MACHINE,
    WINNER_PLAYER,
    WINNER_DRAW
};

struct gameState {
    int machine;
    int player;
    int round;
    winner lastRoundWinner;
    winner winner;
};

inline const char* _winnerToText(winner w) {
    switch (w) {
        case WINNER_DRAW:
            return DRAW;
        case WINNER_MACHINE:
            return MACHINE;
        case WINNER_PLAYER:
            return USER;
        default:
            return "";
    }
}

inline bool logGameState(struct gameState &s) {
    bool ended = false;
    if (s.winner != WINNER_NONE) {
        std::cout << "Game finished! " << _winnerToText(s.winner) << " wins!" << std::endl;
        ended = true;
    } else {
        std::cout << _winnerToText(s.lastRoundWinner) << "wins! Round " << s.round << ". ";
        std::cout << "Player: " << s.player << "Machine: " << s.machine << std::endl;
    }
    return ended;
}

constexpr int playMap[5][5] = {
    {0, 1, -1,  -1, 1},
    {-1, 0, 1, 1, -1},
    {1, -1, 0, -1, 1},
    {1, -1, 1, 0, -1},
    {-1, 1, -1, 1, 0}
};

class Game {
public:
    Game() = default;
    winner winner() const;
    int performRound(int machine, int player);
    int machine = 0;
    int player = 0;
    int round = 0;
};


#endif //ROCKPAPERSCISSORSLIZARDSPOCK_GAME_H
