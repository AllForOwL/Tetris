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
	for (int i = 0; i < CNT_WIDTH; i++)
	{
		for (int j = 0; j < CNT_HEIGHT; j++)
		{
			m_field[i][j] = ' ';
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

void TestApp::IncreasePositionX()
{
	for (int i = 0; i < CNT_OBJECT_QUENTITY_ROWS; i++)
	{
		++m_object[i].m_y;
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
//		MoveFigure();
	}
	else if (btnCode == 100)
	{
		m_stateMove = StateMove::MOVE_RIGHT;
//		MoveFigure();
	}

	//if (btnCode == 119) //w
	//	mObj1Y--;
	//else if (btnCode == 115) //s
	//	mObj1Y++;
	//else if (btnCode == 97) //a
	//	mObj1X--;
	//else if (btnCode == 100) //d
	//	mObj1X++;

	//if (mObj1X < 0)
	//	mObj1X = 0;
	//else if (mObj1X >= X_SIZE)
	//	mObj1X = X_SIZE - 1;

	//if (mObj1Y < 0)
	//	mObj1Y = 0;
	//else if (mObj1Y >=Y_SIZE)
	//	mObj1Y = Y_SIZE - 1;
}

void TestApp::UpdateF(float deltaTime)
{
	AddObjectOnField();
	OutputField();
	IncreasePositionX();

	Sleep(500);

	//SetChar(5, 5, L'X');

	//mObj1XOld = mObj1X;
	//mObj1YOld = mObj1Y;

	////-----------------------------

	//SetChar(mObj2X, mObj2Y, L' ');
	//if (mDirection)
	//{
	//	mObj2X++;
	//	if (mObj2X == 40)
	//		mDirection = false;
	//}
	//else
	//{
	//	mObj2X--;
	//	if (mObj2X == 10)
	//		mDirection = true;
	//}
	//SetChar(mObj2X, mObj2Y, L'F');
}
