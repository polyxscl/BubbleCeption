
#include "MinigameScene.h"


using namespace std::placeholders;

void MinigameScene::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();
	auto& input_manager = game_interface.getIInputManager();


	input_manager.attachKeyPressCallback(
		"mgs_key",
		std::bind(&MinigameScene::keyPressCallback, this, _1, _2)
	);
	input_manager.attachSpecialKeyPressCallback(
		"mgs_spkey",
		std::bind(&MinigameScene::specialKeyPressCallback, this, _1, _2)
	);
	input_manager.attachMousePressCallback(
		"mgs_mp",
		std::bind(&MinigameScene::mousePressCallback, this, _1, _2)
	);

	input_manager.attachMouseMotionCallback(
		"mgs_mm",
		std::bind(&MinigameScene::mouseMotionCallback, this, _1, _2)
	);

	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	A.generate("assets/maps/M_prologue.json");
	player.setspeed(1.f);
	for (auto& i : A.get_enemy_init()) {
		M_Enemy enemy(i.first, i.second);
		enemyset.push_back(enemy);
	}

	Look[0] = 50.f;
	Look[1] = 1.57f;
	Look[2] = 0.f;
	Look[3] = Look[0] * sin(Look[1]) * cos(Look[2]);
	Look[4] = Look[0] * sin(Look[1]) * sin(Look[2]);
	Look[5] = Look[0] * cos(Look[1]);

	start_t = clock();

	M_Player::player_set[0] = M_Image().setAsset(asset_manager.getImageAsset("m_player"));
	M_Player::player_set[1] = M_Image().setAsset(asset_manager.getImageAsset("m_player_face"));
	M_Player::player_set[2] = M_Image().setAsset(asset_manager.getImageAsset("m_player_enemy"));
	M_Player::player_set[3] = M_Image().setAsset(asset_manager.getImageAsset("m_player_enemy_face"));

	M_Enemy::enemy_set[0] = M_Image().setAsset(asset_manager.getImageAsset("m_enemy"));
	M_Enemy::enemy_set[1] = M_Image().setAsset(asset_manager.getImageAsset("m_enemy_face"));

	M_Block::block_set[0] = M_Image().setAsset(asset_manager.getImageAsset("m_block00"));
	M_Block::block_set[1] = M_Image().setAsset(asset_manager.getImageAsset("m_block01"));
	M_Block::block_set[2] = M_Image().setAsset(asset_manager.getImageAsset("m_block02"));
	M_Block::block_set[3] = M_Image().setAsset(asset_manager.getImageAsset("m_block03"));
}

void MinigameScene::clear(IGame& game_interface) {}

void MinigameScene::idle(IGame& game_interface, float t) {
	if (clock() - start_t > 1000 / 60) {
		Look[3] = Look[0] * sin(Look[1]) * cos(Look[2]);
		Look[4] = Look[0] * sin(Look[1]) * sin(Look[2]);
		Look[5] = Look[0] * cos(Look[1]);
		player.move(A);
		for (auto& i : Bubbles) {
			i.move();

		}
		for (auto& i : enemyset) {
			i.move(A);
			for (auto& j : Bubbles) {
				if (Detect(i, j)) {
					handler(i, j);
					enemy_bubble[i] = j;
				}
			}
		}

		handler(player, enemyset);
		handler(player, Bubbles);

		for (auto it = Bubbles.begin(); it != Bubbles.end();) {
			if (it->get_state() == STATE::POPPED) {
				it->pop();
				it = Bubbles.erase(it);
			}
			else {
				++it;
			}
		}

		for (auto it = enemyset.begin(); it != enemyset.end();) {
			if (!it->alive) {
				it = enemyset.erase(it);
			}
			else {
				++it;
			}
		}

		start_t = clock();
	}
}

void MinigameScene::draw(IGame& game_interface) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -8.0, 8.0, 15.0, 450.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Look[4], Look[5], Look[3], 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();
	A.draw();
	player.draw();

	for (auto& i : enemyset) {
		i.draw();
	}
	for (auto& i : Bubbles) {
		i.draw();
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}

void MinigameScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {
	float a = player.getCenter()[0];
	float b = player.getCenter()[1];
	switch (input.key) {
	case ' ':
		if (player.getverticalstate() == STOP) {
			player.setverticalstate(JUMP);
		}
		break;
	case 'S': case 's':
		Bubbles.push_back(player.shootBubble());
		break;
	}
}

void MinigameScene::specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input) {
	switch (input.key) {
	case GLUT_KEY_RIGHT:
		if (input.down) {
			player.setface(RIGHT);
			player.setmoving(true);
		} 
		else {
			player.setmoving(false);
		}
		break;
	case GLUT_KEY_LEFT:
		if (input.down) {
			player.setface(LEFT);
			player.setmoving(true);
	}
		else {
		player.setmoving(false);
		}
		break;
	case GLUT_KEY_UP:
		if (input.down) {
			player.setface(BACKWARD);
			player.setmoving(true);
}
		else {
			player.setmoving(false);
		}
		break;
	case GLUT_KEY_DOWN:
		if (input.down) {
			player.setface(FORWARD);
			player.setmoving(true);
		}
		else {
			player.setmoving(false);
		}
		break;
	}
}

void MinigameScene::mousePressCallback(IInputManager& interface, const InputMouse& input) {
	if (input.down && input.button == MOUSE_BUTTON::LEFT) {
		lastX = input.mouse_pos.x;
		lastY = input.mouse_pos.y;
		isScrolling = false;
	}
	else if (input.button == MOUSE_BUTTON::SCROLL_UP && Look[0] > 45.f) {
		Look[0] -= 0.5f;
		isScrolling = true;
	}
	else if (input.button == MOUSE_BUTTON::SCROLL_DOWN && Look[0] < 65.f) {
		Look[0] += 0.5f;
		isScrolling = true;
	}
	else if (!input.down) {
		isScrolling = true;
	}
}

void MinigameScene::mouseMotionCallback(IInputManager& interface, const InputMouseMotion& input) {
	if (!isScrolling) {
		int dx, dy;
		dx = input.mouse_pos.x - lastX;
		dy = input.mouse_pos.y - lastY;
		Look[1] -= (float)0.002 * dy;
		if (Look[1] > 2.7f) {
			Look[1] = 2.7f;
		}
		else if (Look[1] < 0.44f) {
			Look[1] = 0.44f;
		}
		Look[2] -= (float)0.002 * dx;
		lastX = input.mouse_pos.x;
		lastY = input.mouse_pos.y;
	}
}