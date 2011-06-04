#include "StdAfx.h"
#include "CG_2ndViewUser.h"

CCG_2ndViewUser::CCG_2ndViewUser(void)
{
}

CCG_2ndViewUser::~CCG_2ndViewUser(void)
{
}

void CCG_2ndViewUser::InitPosition()
{
	f_transX = f_transY = f_transZ = 0;
	f_scaleX = f_scaleY = f_scaleZ = 1;
	f_aRotateX = f_aRotateY = f_aRotateZ = 0;
}

void CCG_2ndViewUser::DoModelTransform()
{
	// 좌표축 회전
	glRotatef(f_aRotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(f_aRotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(f_aRotateZ, 0.0f, 0.0f, 1.0f);
	// Translate
	glTranslated(f_transX, f_transY, f_transZ);
	// Scaling
	glScalef(f_scaleX, f_scaleY, f_scaleZ);
}