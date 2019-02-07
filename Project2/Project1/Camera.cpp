#include "Camera.h"
#include<GL/freeglut.h>

bool Camera::OnKeyboard(int Key)
{
	bool Ret = false;

	switch (Key) {

	case GLUT_KEY_UP:
	{
		m_pos = m_pos + (m_target * StepSize);
		Ret = true;
	}
	break;

	case GLUT_KEY_DOWN:
	{
		m_pos = m_pos - (m_target * StepSize);
		Ret = true;
	}
	break;

	case GLUT_KEY_LEFT:
	{
		Vector3f Left = m_target.Cross(m_up);
		Left.Normalize();
		Left = Left * StepSize;
		m_pos = m_pos + Left;
		Ret = true;
	}
	break;

	case GLUT_KEY_RIGHT:
	{
		Vector3f Right = m_up.Cross(m_target);
		Right.Normalize();
		Right = Right * StepSize;
		m_pos = m_pos + Right;
		Ret = true;
	}
	break;
	}

	return Ret;
}