#pragma once

#include "Vector.h"

namespace Virgin
{

enum CameraViewMode
{
    CameraViewMode_Orthographic,
    CameraViewMode_Perspective,
    CameraViewMode_Frustum
};

class Camera
{
public:
    Camera(void);
    ~Camera(void);

    void SetToOrthographicView(double left, double right, double bottom, double top, double zNear, double zFar);
    void SetToFrustumView(double left, double right, double bottom, double top, double zNear, double zFar);
    void SetToPerspectiveView(double fov, double aspect, double zNear, double zFar);

    void SetAspect(double aspect);

    void MoveTo(float x, float y, float z);
    void MoveMore(float x, float y, float z);
    void LookAt(float x, float y, float z);
    void SetUpVector(float x, float y, float z);

    void Rotate(float angle, float x, float y, float z);
    void RotateYMore(float angle);
    void ResetRotation();

    void Apply();

private:
    CameraViewMode viewMode_;

    double fov_;
    double aspect_;
    double left_;
    double right_;
    double top_;
    double bottom_;
    double near_;
    double far_;

    Vector3 location_;
    Vector3 lookingAt_;
    Vector3 up_;
    Vector3 anglesForEachAxis_;

    float rotateAngle_;
    float rotateX_;
    float rotateY_;
    float rotateZ_;
};

}
