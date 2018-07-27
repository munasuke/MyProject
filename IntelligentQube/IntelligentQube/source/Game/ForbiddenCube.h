#pragma once
#include "Cube.h"

//黒いキューブ。消したらダメ
class ForbiddenCube :
	public Cube {
public:
	ForbiddenCube();
	~ForbiddenCube();
};

