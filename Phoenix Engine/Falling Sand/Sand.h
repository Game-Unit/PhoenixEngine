#pragma once

#include "Solid.h"

namespace FallingSand
{

	class Sand : public Solid
	{
	public:
		Sand(int posX, int posY, Grid* grid) : Solid(posX, posY, grid)
		{

		}
	};

}