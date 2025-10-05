#include "Grid.h"
#include "raylib.h"
#include "../Core/Debug.h"


FallingSand::Grid::Grid(float positionX, float positionY, int columns, int rows, float cellSize) 
	: m_positionX(positionX),  m_positionY(positionY), m_columns(columns), m_rows(rows), m_cellSize(cellSize), m_columnOrder(columns), m_rng(m_rd())
{
	std::iota(m_columnOrder.begin(), m_columnOrder.end(), 0);

	m_grid.resize(m_columns);
	for (int x = 0; x < m_columns; ++x)
		m_grid[x].resize(m_rows, nullptr);
}

void FallingSand::Grid::Update()
{
	std::shuffle(m_columnOrder.begin(), m_columnOrder.end(), m_rng);

	std::vector<Element*> grid(m_columns * m_rows);
	std::vector<bool> updated(m_columns * m_rows, false);

	for (int xi = 0; xi < m_columns; xi++)
	{
		int x = m_columnOrder[xi];
		for (int y = m_rows - 1; y >= 0; --y)
		{
			if (m_grid[x][y] != nullptr)
				m_grid[x][y]->Update();
		}
	}
}

void FallingSand::Grid::Render()
{
	for (int x = 0; x < m_columns; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			if (m_debug)
				DrawRectangleLines(m_positionX + x * m_cellSize, m_positionY + y * m_cellSize, m_cellSize, m_cellSize, m_debugColor);

			if (m_grid[x][y] != nullptr)
				m_grid[x][y]->Render();
		}
	}
}

void FallingSand::Grid::AddElement(Element* element)
{
	int x = element->m_positionX;
	int y = element->m_positionY;

	// Left
	if (x - 1 >= 0)
	{
		auto left = GetElement(x - 1, y);
		if (left != nullptr)
			left->Awake();
	}

	// Right
	if (x + 1 < GetColumns())
	{
		auto right = GetElement(x + 1, y);
		if (right != nullptr)
			right->Awake();
	}

	// Up
	if (y - 1 >= 0)
	{
		auto up = GetElement(x, y - 1);
		if (up != nullptr)
			up->Awake();
	}

	// Down
	if (y + 1 < GetRows())
	{
		auto down = GetElement(x, y + 1);
		if (down != nullptr)
			down->Awake();
	}

	if (element->m_positionX >= 0 && element->m_positionX < m_columns &&
		element->m_positionY >= 0 && element->m_positionY < m_rows)
	{
		m_grid[element->m_positionX][element->m_positionY] = element;
	}
	else
	{
		Core::Debug::LogError("Element position out of bounds!");
	}
}

void FallingSand::Grid::ClearElement(int x, int y)
{
	// Left
	if (x - 1 >= 0)
	{
		auto left = GetElement(x - 1, y);
		if (left != nullptr)
			left->Awake();
	}

	// Right
	if (x + 1 < GetColumns())
	{
		auto right = GetElement(x + 1, y);
		if (right != nullptr)
			right->Awake();
	}

	// Up
	if (y - 1 >= 0)
	{
		auto up = GetElement(x, y - 1);
		if (up != nullptr)
			up->Awake();
	}

	// Down
	if (y + 1 < GetRows())
	{
		auto down = GetElement(x, y + 1);
		if (down != nullptr)
			down->Awake();
	}

	m_grid[x][y] = nullptr;
}

FallingSand::Element* FallingSand::Grid::GetElement(int x, int y)
{
	return m_grid[x][y];
}

Vector2 FallingSand::Grid::WorldToGrid(Vector2 pos)
{
	Vector2 gridPos;

	// shift into grid-local space
	float localX = pos.x - m_positionX;
	float localY = pos.y - m_positionY;

	// convert to grid coords
	int gx = (int)floor(localX / m_cellSize);
	int gy = (int)floor(localY / m_cellSize);

	gridPos.x = gx;
	gridPos.y = gy;

	return gridPos;
}

FallingSand::Grid::~Grid()
{
	
}
