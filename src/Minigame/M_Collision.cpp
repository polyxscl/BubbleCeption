#include <deque>
#include <unordered_set>
#include "Minigame/M_Collision.h"

M_BasicCollision CollisionDetect;

void M_CollisionHandler::operator()(M_Player& player, std::vector<M_Enemy>& enemy) {
	int j = 0;
	for (auto& i : enemy) {
		if (CollisionDetect(player, i)) {
			j++;
		}
	}
	if (j != 0) {
		player.settype(2);
	}
	else {
		player.settype(0);
	}
}

void M_CollisionHandler::operator()(M_Player& player, std::vector<M_Bubble>& bubbles) {
	for (auto& b1 : bubbles) {
		if (CollisionDetect(player, b1)) {
			std::deque<M_Bubble*> dq;
			std::unordered_set<M_Bubble*> visited;
			dq.push_back(&b1);
			while (!dq.empty()) {
				auto& b2 = dq.front();
				dq.pop_front();
				if (visited.find(b2) != visited.end()) continue;
				for (M_Bubble& b3 : bubbles) {
					if (b2 == &b3) continue;
					if (CollisionDetect(*b2, b3)) {
						dq.push_back(&b3);
					}
				}
				b2->set_state(STATE::POPPED);
				visited.insert(b2);
			}
		}
	}
}

void M_CollisionHandler::operator()(M_Bubble& bubble1, M_Bubble& bubble2) {
	if (CollisionDetect(bubble1, bubble2)) {

	}
}

void M_CollisionHandler::operator()(M_Enemy& enemy, M_Bubble& bubble) {
	bubble.set_enemy(&enemy);
}