// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		enum StateObject
		{
			STATE_HORISONTAL,
			STATE_VERTICAL,
			STATE_SQUARE
		};
		
		enum StateMove
		{
			MOVE_LEFT,
			MOVE_RIGHT
		};

		struct Point
		{
			int m_x;
			int m_y;
			Point() : m_x(0), m_y(0)
			{

			}
		};

		StateObject m_stateObject;
		StateMove	m_stateMove;

		std::vector<std::vector<char>> m_field;
		std::vector<Point> m_object;

		std::vector<Point> m_pinObject;

		int  m_activeSymbol;

	public:
		TestApp();
		void ChangeFigure();
		void ExecuteFigure();
		void MoveFigure();
		void OutputField();
		void AddObjectOnField();
		void IncreasePositionY();
		void ClearField();
		void CheckFullLineX();

		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};
