#ifndef OOP_GAME_FLAGS_H
#define OOP_GAME_FLAGS_H


class GameFlags {
private:
    bool doubleDamage;
    bool useAbility;
    bool loadAndNewGame;

public:
    GameFlags();

    void setDoubleDamage(bool flag);
    bool getDoubleDamage() const;

    void setUseAbility(bool flag);
    bool getUseAbility() const;

    void setLoadAndNewGame(bool flag);
    bool getLoadAndNewGame() const;
};


#endif
