#pragma once

#include "Solid.h"

namespace FallingSand
{

	class Rock : public Solid
	{
	public:
		Rock(int posX, int posY, Grid* grid) : Solid(posX, posY, grid)
		{
			m_movable = false;
		}
	};

}