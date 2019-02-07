//#pragma once
//#include "Vector3f.h"
//#include "cyMatrix.h"
//typedef struct {
//	Vector3f Pos;
//	Vector3f Target;
//	Vector3f Up;
//} Camera;
//Camera m_camera;
//
//
//
//void InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
//{
//	/*Vector3f N = Target;
//	N.Normalize();
//	Vector3f U = Up;
//	U.Normalize();
//	U = U.Cross(Target);
//	Vector3f V = N.Cross(U);
//
//	m[0][0] = U.x; m[0][1] = U.y; m[0][2] = U.z; m[0][3] = 0.0f;
//	m[1][0] = V.x; m[1][1] = V.y; m[1][2] = V.z; m[1][3] = 0.0f;
//	m[2][0] = N.x; m[2][1] = N.y; m[2][2] = N.z; m[2][3] = 0.0f;
//	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;*/
//}
//
////const cyMatrix4f* Pipeline::GetTrans()
////{
////	cyMatrix4f ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;
////
////	ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
////	RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
////	TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
////	CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
////	CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
////	PersProjTrans.InitPersProjTransform(m_persProj.FOV, m_persProj.Width, m_persProj.Height, m_persProj.zNear, m_persProj.zFar);
////
////	m_transformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;
////	return &m_transformation;
////}