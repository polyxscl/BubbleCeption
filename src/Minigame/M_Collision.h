#pragma once
#include "Minigame/M_Player.h"
#include "Minigame/M_Bubble.h"
#include "Minigame/M_Enemy.h"


class M_CollisionHandler {
public:
	void operator()(M_Player& player, std::vector<M_Enemy>& enemy);
	void operator()(M_Player& player, std::vector<M_Bubble>& bubbles);
	void operator()(M_Bubble& bubble1, M_Bubble& bubble2);
	void operator()(M_Enemy& enemy, M_Bubble& bubble);
};