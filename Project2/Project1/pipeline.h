#pragma once
#include "Vector3f.h"
#include "cyMatrix.h"
struct {
	Vector3f Pos;
	Vector3f Target;
	Vector3f Up;
} m_camera;
const cyMatrix4f* Pipeline::GetTrans()
{
	cyMatrix4f ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

	ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
	RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
	TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
	CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
	CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
	PersProjTrans.InitPersProjTransform(m_persProj.FOV, m_persProj.Width, m_persProj.Height, m_persProj.zNear, m_persProj.zFar);

	m_transformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;
	return &m_transformation;
}