#include "TestApp.h"

const int CNT_WIDTH		= 20;
const int CNT_HEIGHT	= 20;

const int CNT_OBJECT_QUENTITY_COLS = 4;
const int CNT_OBJECT_QUENTITY_ROWS = 4;

TestApp::TestApp() : Parent(CNT_WIDTH, CNT_HEIGHT)
{
	m_stateObject = StateObject::STATE_HORISONTAL;

	m_object.resize(CNT_OBJECT_QUENTITY_ROWS);
	m_object[0].m_x = CNT_WIDTH / 2;
	m_object[1].m_x = CNT_WIDTH / 2 + 1;
	m_object[2].m_x = CNT_WIDTH / 2 + 2;
	m_object[3].m_x = CNT_WIDTH / 2 + 3;

	m_field.resize(CNT_WIDTH, std::vector<char>(CNT_HEIGHT));
	for (int i = 0; i < CNT_WIDTH; i++)
	{
		for (int j = 0; j < CNT_HEIGHT; j++)
		{
			m_field[i][j] = ' ';
		}
	}
}

void TestApp::AddObjectOnField()
{
	bool _isPin = false;
	for (int i = 0; i < CNT_WIDTH; i++)
	{
		for (int j = 0; j < CNT_HEIGHT; j++)
		{
			for (int b = 0; b < m_pinObject.size(); b++)
			{
				if (m_pinObject[b].m_x == i && m_pinObject[b].m_y == j)
				{
					_isPin = true;

					break;
					break;
				}
			}
			if (!_isPin)
			{
				m_field[i][j] = ' ';
			}
			_isPin = false;
		}
	}
	for (int b = 0; b < CNT_OBJECT_QUENTITY_ROWS; b++)
	{
		m_field[m_object[b].m_x][m_object[b].m_y] = 'X';
	}
}

void TestApp::CheckFullLineX()
{
	int _quentityXInRows = 0;
	for (int y = 0; y < CNT_HEIGHT; y++)
	{
		for (int x = 0; x < CNT_WIDTH; x++)
		{
			if (m_field[x][y] == 'X')
			{
				++_quentityXInRows;
			}
		}
		if (_quentityXInRows == CNT_WIDTH)
		{
			for (int _x = 0; _x < CNT_WIDTH; _x++)
			{
				m_field[_x][y] = ' ';
			}

			for (int d = 0; d < m_pinObject.size(); d++)
			{
				if (m_pinObject[d].m_y == y)
				{
					m_pinObject.erase(m_pinObject.begin() + d);
				}
			}

			for (int i = CNT_HEIGHT - 2; i > 0; i--)
			{
				for (int j = 0; j < CNT_WIDTH; j++)
				{
					m_field[i][j] = m_field[i - 1][j];
				}
			}
		}

		_quentityXInRows = 0;
	}
}

void TestApp::OutputField()
{
	for (int i = 0; i < CNT_WIDTH; i++)
	{
		for (int j = 0; j < CNT_HEIGHT; j++)
		{
			SetChar(i, j, m_field[i][j]);
		}
	}
}

void TestApp::ChangeFigure()
{
	if (m_stateObject == StateObject::STATE_HORISONTAL)
	{
		m_stateObject = StateObject::STATE_VERTICAL;
	}
	else if (m_stateObject == StateObject::STATE_VERTICAL)
	{
		m_stateObject = StateObject::STATE_SQUARE;
	}
	else if (m_stateObject == StateObject::STATE_SQUARE)
	{
		m_stateObject = StateObject::STATE_HORISONTAL;
	}
}

void TestApp::IncreasePositionY()
{
	if (m_object[3].m_y != CNT_HEIGHT - 1 && m_field[m_object[3].m_x][m_object[3].m_y + 1] != 'X')
	{
		for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
		{
			++m_object[i].m_y;
		}
	}
	else
	{
		for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
		{
			m_pinObject.push_back(m_object[i]);
		}

		m_object[0].m_x = CNT_WIDTH / 2;
		m_object[1].m_x = CNT_WIDTH / 2 + 1;
		m_object[2].m_x = CNT_WIDTH / 2 + 2;
		m_object[3].m_x = CNT_WIDTH / 2 + 3;
		for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
		{
			m_object[i].m_y = 0;
		}

		CheckFullLineX();
	}
}

void TestApp::ExecuteFigure()
{
	Point _positionOneElement = m_object[0];
	switch (m_stateObject)
	{
		case StateObject::STATE_HORISONTAL:
		{
			int _valueY = _positionOneElement.m_y + 1;
			int _valueX = _positionOneElement.m_x - 2;

			if (_valueX <= 0)
			{
				return;
			}

			for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
			{
				m_object[i].m_y = _valueY;
				m_object[i].m_x = _valueX;
				++_valueX;
			}

			break;
		}
		case StateObject::STATE_VERTICAL:
		{
			int _valueY = _positionOneElement.m_y - 2;
			int _valueX = _positionOneElement.m_x + 1;

			if (_valueY <= 0)
			{
				return;
			}

			for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
			{
				m_object[i].m_y = _valueY;
				m_object[i].m_x = _valueX;
				++_valueY;
			}

			break;
		}
		case StateObject::STATE_SQUARE:
		{
			int _valueY = _positionOneElement.m_y;
			int _valueX = _positionOneElement.m_x;

			if (_valueX <= 1)
			{
				return;
			}

			m_object[0].m_x = _valueX;
			m_object[0].m_y = _valueY;

			++_valueX;
			m_object[1].m_x = _valueX;
			m_object[1].m_y = _valueY;

			--_valueX;
			++_valueY;
			m_object[2].m_x = _valueX;
			m_object[2].m_y = _valueY;

			++_valueX;
			m_object[3].m_x = _valueX;
			m_object[3].m_y = _valueY;

			break;
		}
		default:
			break;
	}
}

void TestApp::MoveFigure()
{
	switch (m_stateMove)
	{
		case StateMove::MOVE_LEFT:
		{
			int _positionX = m_object[0].m_x;
			if (_positionX > 0)
			{
				for (int i = 0; i < m_object.size(); i++)
				{
					--m_object[i].m_x;
				}
			}
	
			break;
		}
		case StateMove::MOVE_RIGHT:
		{
			int _positionX = m_object[3].m_x;
			if (_positionX != CNT_WIDTH-1)
			{
				for (int i = 0; i < m_object.size(); i++)
				{
					++m_object[i].m_x;
				}
			}

			break;
		}
	default:
		break;
	}
}

void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 32)
	{
		ChangeFigure();
		ExecuteFigure();
	}
	else if (btnCode == 97)
	{
		m_stateMove = StateMove::MOVE_LEFT;
		MoveFigure();
	}
	else if (btnCode == 100)
	{
		m_stateMove = StateMove::MOVE_RIGHT;
		MoveFigure();
	}
}

void TestApp::UpdateF(float deltaTime)
{
	AddObjectOnField();
	OutputField();
	IncreasePositionY();

	Sleep(400);
}
