//
// Created by Adam Levin on 2/7/18.
//

#ifndef MONOPOLY_2_RULES_H
#define MONOPOLY_2_RULES_H


class Rules {
private:
    int starting_cash;
    int turn_limit;
    int player_endgame;
    int property_set_multiplier;
    int houses_before_hotels;
    bool build_houses_evenly;
    bool freeparking;
    bool auction;
    int go_multiplier;
    int turncount;

public:
    int getStarting_cash() const;

    void setStarting_cash(int starting_cash);

    int getTurn_limit() const;

    void setTurn_limit(int turn_limit);

    int getPlayer_endgame() const;

    void setPlayer_endgame(int player_endgame);

    int getProperty_set_multiplier() const;

    void setProperty_set_multiplier(int property_set_multiplier);

    int getHouses_before_hotels() const;

    void setHouses_before_hotels(int houses_before_hotels);

    bool isBuild_houses_evenly() const;

    void setBuild_houses_evenly(bool build_houses_evenly);

    bool isFreeparking() const;

    void setFreeparking(bool freeparking);

    bool isAuction() const;

    void setAuction(bool auction);

    int getGo_multiplier() const;

    void setGo_multiplier(int go_multiplier);

    int getTurncount() const;

    void setTurncount(int turncount);


};


#endif //MONOPOLY_2_RULES_H
