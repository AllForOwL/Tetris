#include "TestApp.h"

const int CNT_WIDTH		= 50;
const int CNT_HEIGHT	= 50;

const int CNT_OBJECT_QUENTITY_COLS = 4;
const int CNT_OBJECT_QUENTITY_ROWS = 4;

TestApp::TestApp() : Parent(CNT_WIDTH, CNT_HEIGHT)
{
	mDirection = true;
	mObj1XOld = mObj1X = 10;
	mObj1YOld = mObj1Y = 10;
	mObj2X = 10;
	mObj2Y = 12;

	m_stateObject = StateObject::STATE_HORISONTAL;

	m_object.resize(CNT_OBJECT_QUENTITY_ROWS);
	m_object[0].m_x = CNT_WIDTH / 2;
	m_object[1].m_x = CNT_WIDTH / 2 + 1;
	m_object[2].m_x = CNT_WIDTH / 2 + 2;
	m_object[3].m_x = CNT_WIDTH / 2 + 3;

	m_field.resize(CNT_WIDTH, std::vector<char>(CNT_WIDTH));
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
	for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
	{
		m_field[m_object[i].m_x][m_object[i].m_y] = 'X';
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
			if (_positionX)
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
			if (_positionX != CNT_WIDTH)
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

	Sleep(500);
}
