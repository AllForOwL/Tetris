// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		int mObj1XOld;
		int mObj1YOld;
		int mObj1X;
		int mObj1Y;

		int mObj2X;
		int mObj2Y;

		bool mDirection;

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

		int  m_activeSymbol;

	public:
		TestApp();
		void ChangeFigure();
		void ExecuteFigure();
	//	void MoveFigure();
		void OutputField();
		void AddObjectOnField();
		void IncreasePositionX();
		void ClearField();

		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};
