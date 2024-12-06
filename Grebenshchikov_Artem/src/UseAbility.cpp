#include "UseAbility.h"
#include "BattleshipException.h"


UseAbility::UseAbility(Game& game) : game(game){
    initializeAbilityHandlers();
}

void UseAbility::initializeAbilityHandlers() {
    abilityHandlers[answerAbilities::BombardmentDestroyedShip] = [&]() {
        game.getGameEntities()->getManagerIO()->outputMassage("Способностью Bombardment был уничтожен корабль!\n");
        game.getGameEntities()->getAbilityManager()->addAbility();
    };
    abilityHandlers[answerAbilities::DoubleDamage] = [&]() {
        game.getGameEntities()->getManagerIO()->outputMassage("Способность DoubleDamage позволяет следующем выстрелом нанести двойной урон!\n");
        game.getGameEntities()->getGameFlags()->setDoubleDamage(true);
    };
    abilityHandlers[answerAbilities::ScannerFoundShip] = [&]() {
        game.getGameEntities()->getManagerIO()->outputMassage("Способность Scanner обнаружила корабль!\n");
    };
    abilityHandlers[answerAbilities::ScannerNotFoundShip] = [&]() {
        game.getGameEntities()->getManagerIO()->outputMassage("Способность Scanner не обнаружила корабль!\n");
    };
    abilityHandlers[answerAbilities::BombardmentSuccess] = [&]() {
        game.getGameEntities()->getManagerIO()->outputMassage("Способность Bombardment нанесла урон по кораблю!\n");
    };
}

void UseAbility::handle() {
    std::shared_ptr<Ability> ability;
    try{
        ability = game.getGameEntities()->getAbilityManager()->getAbility();
    }catch (NoAbilitiesError& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    game.getGameEntities()->getGameFlags()->setUseAbility(true);
    answerAbilities result = ability->use();

    auto it = abilityHandlers.find(result);
    it->second(); // Вызов соответствующей лямбда-функции
}


std::string UseAbility::toString() {
    return "UseAbility";
}