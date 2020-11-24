
#include "collisions.h"

bool ColliderOverlaping(Collider& collider, Collider& other) 
{
	if (!collider.isActive || !other.isActive)
		return false;

	Collider* col = &collider;
	Collider* oth = &other;

	for (int i = 0; i < 2; i++) 
	{
		//test on both polygons
		if (i) 
		{
			col = &other;
			oth = &collider;
		}

		for (int x = 0; x < col->m_edges.size(); x++) 
		{
			int b = (x + 1) % col->m_edges.size();
			vector axisProj = { -(col->m_edges[b].y - col->m_edges[x].y), col->m_edges[b].x - col->m_edges[x].x };
			float min_r1 = INFINITY , max_r1 = -INFINITY;
			for (int p = 0; p < col->m_edges.size(); p++) 
			{
				float q = (col->m_edges[p].x * axisProj.x + col->m_edges[p].y * axisProj.y);
				min_r1 = std::min(min_r1, q);
				max_r1 = std::max(max_r1, q);
			}

			float min_r2 = INFINITY, max_r2 = -INFINITY;
			for (int p = 0; p < oth->m_edges.size(); p++)
			{
				float q = (oth->m_edges[p].x * axisProj.x + oth->m_edges[p].y * axisProj.y);
				min_r2 = std::min(min_r2, q);
				max_r2 = std::max(max_r2, q);
			}

			if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
				return false;
		}
		collider.overlap = true;
		other.overlap = true;
		return true;
	}
}

void translateCollider(Collider& collider) 
{
	collider.overlap = false;
	for (int i = 0; i < collider.m_edges_origin.size(); i++) 
	{
		collider.m_edges[i] =
		{
			(collider.m_edges_origin[i].x * cosf(collider.angle)) - (collider.m_edges_origin[i].y * sinf(collider.angle)) + collider.center.x,
			(collider.m_edges_origin[i].x * sinf(collider.angle)) + (collider.m_edges_origin[i].y * cosf(collider.angle)) + collider.center.y,
		};
	}
}

