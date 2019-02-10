#include "Camera.h"
#include<GL/freeglut.h>

bool Camera::OnKeyboard(int Key)
{
	bool Ret = false;

	switch (Key) {

	case 'W':
	case 'w':
	{
		m_pos = m_pos + (m_target * StepSize);
		Ret = true;
	}
	break;

	case 'S':
	case 's':
	{
		m_pos = m_pos - (m_target * StepSize);
		Ret = true;
	}
	break;

	case 'A':
	case 'a':
	{
		Vector3f Left = m_target.Cross(m_up);
		Left.Normalize();
		Left = Left * StepSize;
		m_pos = m_pos + Left;
		Ret = true;
	}
	break;

	case 'D':
	case 'd':
	{
		Vector3f Right = m_up.Cross(m_target);
		Right.Normalize();
		Right = Right * StepSize;
		m_pos = m_pos + Right;
		Ret = true;
	}
	break;
	case 'Q':
	case 'q':
	{
		deflectionXZDegree += 1;
		Update();
	}
	break;
	case 'E':
	case 'e':
	{
		deflectionXZDegree -= 1;
		Update();
	}
	break;
	case 'Z':
	case 'z':
	{
		deflectionYZDegree += 1;
		Update();
	}
	break;
	case 'C':
	case 'c':
	{
		deflectionYZDegree -= 1;
		Update();
	}
	break;
	}

	return Ret;
}