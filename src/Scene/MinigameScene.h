#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <set>
#include <queue>

#include "Constants.h"

#include "Minigame/M_Light.h"
#include "Minigame/M_Collision.h"

#include <GL/freeglut.h>
#include <FreeImage.h>


using namespace std;

#define WINDOW_WIDTH SCREEN_WIDTH * TILE_SIZE		// window's width
#define WINDOW_HEIGHT SCREEN_HEIGHT * TILE_SIZE		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2

#include <unordered_set>

#include "Scene.h"

class MinigameScene : virtual public Scene {
public:
	void init(IGame& game_interface) override;
	void clear(IGame& game_interface) override;
	void idle(IGame& game_interface, float t) override;
	void draw(IGame& game_interface) override;

	void keyPressCallback(IInputManager& interface, const InputKeyboard& input);
	void specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input);
	void mousePressCallback(IInputManager& interface, const InputMouse& input);
	void mouseMotionCallback(IInputManager& interface, const InputMouseMotion& input);

	vector<M_Bubble> Bubbles;

private:
	float Look[6];
	int lastX, lastY;
	bool MB = false;

	M_CollisionHandler handler;
	vector<M_Enemy> enemyset;
	std::map<M_Enemy, M_Bubble> enemy_bubble;

	clock_t start_t;

	M_BasicCollision Detect;

	M_Map A = M_Map("prologue");
	M_Player player = M_Player(A, 0);

	Light light = Light(150, 150, 150, GL_LIGHT0);

	bool isScrolling = false;
};