#pragma once

#include <vector>

#include "math_toolbox.h"

struct Collider 
{
	std::vector<vector> m_edges;
	vector center;
	float angle;
	std::vector<vector> m_edges_origin;
	bool overlap = false;
	bool isActive = true;
};

bool ColliderOverlaping(Collider& collider, Collider& other);

void translateCollider(Collider& collider);