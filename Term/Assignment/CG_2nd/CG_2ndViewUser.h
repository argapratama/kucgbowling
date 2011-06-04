#pragma once

class CCG_2ndViewUser
{
public:
	// Translation
	float f_transX, f_transY, f_transZ;
	// Scaling
	float f_scaleX, f_scaleY, f_scaleZ;
	// Axis Rotation
	float f_aRotateX, f_aRotateY, f_aRotateZ;
	
	void InitPosition();
	void DoModelTransform();
	
	CCG_2ndViewUser(void);
	~CCG_2ndViewUser(void);
};
