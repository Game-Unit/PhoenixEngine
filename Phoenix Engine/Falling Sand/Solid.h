#pragma once
#include "Element.h"
#include "Grid.h"
#include "../Core/Debug.h"
#include "../Core/Random.h"

#include <string>
#include <cstdlib> 
#include <ctime>    

namespace FallingSand
{

	class Solid : public Element
	{
	public:
		Solid(int posX, int posY, Grid* grid) : Element(posX, posY, grid)
		{
			
		}

		void Update() override
		{
			if (m_movable)
			{
				if (!m_asleep)
				{
					int targetY = m_positionY + 1;

					// if target position is out of bounds set target position to current position
					if (!(targetY >= 0 && targetY < m_grid->GetRows()))
					{
						targetY = m_positionY;
						return;
					}

					// finds element in gird at target position
					Element* targetElement = m_grid->GetElement(m_positionX, targetY);

					// if target position is empty
					if (targetElement == nullptr)
					{
						m_grid->ClearElement(m_positionX, m_positionY);
						m_positionY++;
						m_grid->AddElement(this);
					}
					else
					{
						int side = Core::Random::Range(0, 1);

						if (side == 0)
						{
							if (m_positionX - 1 >= 0)
							{
								int targetX = m_positionX - 1;
								targetElement = m_grid->GetElement(targetX, targetY);
							}

							if (targetElement == nullptr)
							{
								m_grid->ClearElement(m_positionX, m_positionY);
								m_positionX--;
								m_grid->AddElement(this);
							}
							else
							{
								if (m_positionX + 1 <= m_grid->GetColumns() - 1)
								{
									int targetX = m_positionX + 1;
									targetElement = m_grid->GetElement(targetX, targetY);
								}

								if (targetElement == nullptr)
								{
									m_grid->ClearElement(m_positionX, m_positionY);
									m_positionX++;
									m_grid->AddElement(this);
								}
								else
								{
									if (m_positionX - 1 >= 0)
									{
										int targetX = m_positionX - 1;
										targetElement = m_grid->GetElement(targetX, targetY);
									}

									if (targetElement == nullptr)
									{
										m_grid->ClearElement(m_positionX, m_positionY);
										if (m_positionX - 1 >= 0)
											m_positionX--;
										m_grid->AddElement(this);
									}
									m_asleep = true;
								}
							}
						}
						else
						{
							if (m_positionX + 1 <= m_grid->GetColumns() - 1)
							{
								int targetX = m_positionX + 1;
								targetElement = m_grid->GetElement(targetX, targetY);
							}

							if (targetElement == nullptr)
							{
								m_grid->ClearElement(m_positionX, m_positionY);
								m_positionX++;
								m_grid->AddElement(this);
							}
							else
							{
								if (m_positionX - 1 >= 0)
								{
									int targetX = m_positionX - 1;
									targetElement = m_grid->GetElement(targetX, targetY);
								}

								if (targetElement == nullptr)
								{
									m_grid->ClearElement(m_positionX, m_positionY);
									m_positionX--;
									m_grid->AddElement(this);
								}
								else
								{
									if (m_positionX + 1 <= m_grid->GetColumns() - 1)
									{
										int targetX = m_positionX + 1;
										targetElement = m_grid->GetElement(targetX, targetY);
									}

									if (targetElement == nullptr)
									{
										m_grid->ClearElement(m_positionX, m_positionY);
										if (m_positionX + 1 <= m_grid->GetColumns() - 1)
											m_positionX++;
										m_grid->AddElement(this);
									}
									m_asleep = true;
								}
							}
						}
					}
				}
			}
		}
	protected:
		bool m_movable = true;
	};

}