//
// Created by Paolo on 10/07/2018.
//

#include "Game.h"

winner Game::winner() const {
    if (machine == MAX_VICTORIES) {
        return WINNER_MACHINE;
    } else if (player == MAX_VICTORIES) {
        return WINNER_PLAYER;
    } else if (round >= MAX_ROUNDS) {
        if (player > machine) {
            return WINNER_PLAYER;
        } else if (machine > player) {
            return WINNER_MACHINE;
        } else {
            return WINNER_DRAW;
        }
    } else {
        return WINNER_NONE;
    }
}
int Game::performRound(int machine, int player) {
    if (round >= MAX_ROUNDS) {
        return -1;
    }
    this->round++;
    const auto roundWinner = playMap[machine][player];
    if (roundWinner == -1) {
        this->machine++;
        return WINNER_MACHINE;
    } else if (roundWinner == 1) {
        this->player++;
        return WINNER_PLAYER;
    } else {
        return WINNER_DRAW;
    }
}
