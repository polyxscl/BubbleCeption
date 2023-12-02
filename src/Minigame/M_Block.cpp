#include "Minigame/M_Block.h"

M_Image M_Block::block_set[4];

M_Block::M_Block() {

}

M_Block::M_Block(Vector3f a, int b) {
	Vector3f v(0.f, 0.f, 0.f);
	this->center = a;
	this->type = b;
	this->volume = 1.0f;
	this->length = Block_length;
	this->Cubeset();
	this->velocity = v;
	this->acceleration = v;
}

void M_Block::setshow(bool* info) {
	for (int i = 0; i < 6; i++) {
		this->show[i] = info[i];
	}
}

void M_Block::draw() const {
	for (int j = 0; j < 100; j++) {
		if (this->gettype() == 0) {
			continue;
		}
		if (this->gettype() == j) {
			if (this->show[0]) {
				block_set[j].draw(this->getpoint(6), this->getpoint(4), this->getpoint(0), this->getpoint(2));
			}
			if (this->show[1]) {
				block_set[j].draw(this->getpoint(2), this->getpoint(0), this->getpoint(1), this->getpoint(3));
			}
			if (this->show[2]) {
				block_set[j].draw(this->getpoint(3), this->getpoint(1), this->getpoint(5), this->getpoint(7));
			}
			if (this->show[3]) {
				block_set[j].draw(this->getpoint(7), this->getpoint(5), this->getpoint(4), this->getpoint(6));
			}
			if (this->show[4]) {
				block_set[j].draw(this->getpoint(4), this->getpoint(5), this->getpoint(1), this->getpoint(0));
			}
			if (this->show[5]) {
				block_set[j].draw(this->getpoint(2), this->getpoint(3), this->getpoint(7), this->getpoint(6));
			}
		}
	}
}