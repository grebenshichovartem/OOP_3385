#ifndef OOP_USE_ABILITY_H
#define OOP_USE_ABILITY_H

#include <unordered_map>
#include <functional>
#include "GameState.h"
#include "Game.h"



class UseAbility : public GameState{
private:
    Game& game;
    std::unordered_map<answerAbilities, std::function<void()>> abilityHandlers;

    void initializeAbilityHandlers();

public:
    explicit UseAbility(Game& game);
    void handle() override;
    std::string toString() override;
};


#endif
