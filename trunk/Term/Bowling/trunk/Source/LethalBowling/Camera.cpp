#include "StdAfx.h"
#include "Camera.h"
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Virgin
{

Camera::Camera(void)
    : viewMode_(CameraViewMode_Perspective)
    , fov_(100.0)
    , aspect_(2.5)
    , left_(0.0)
    , right_(0.0)
    , top_(0.0)
    , bottom_(0.0)
    , near_(1.5)
    , far_(1000.0)
    , rotateAngle_(0.0)
    , rotateX_(0.0)
    , rotateY_(0.0)
    , rotateZ_(0.0)
    /*, up_(0.0, 1.0, 0.0)
    , location_(0.0, 0.0, 1.0)*/
    , up_(0.0, 0.0, 1.0)
    , location_(10.0, 1.0, 2.0)
{
}


Camera::~Camera(void)
{
}

void Camera::MoveTo(float x, float y, float z)
{
    location_.X() = x;
    location_.Y() = y;
    location_.Z() = z;
}
void Camera::MoveMore(float x, float y, float z)
{
    MoveTo(location_.X() + x, location_.Y() + y, location_.Z() + z);
}

void Camera::SetAspect(double aspect)
{
    aspect_ = aspect;
}

void Camera::Rotate(float angle, float x, float y, float z)
{
    rotateAngle_ = angle;
    rotateX_ = x;
    rotateY_ = y;
    rotateZ_ = z;
}

void Camera::Apply()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch(viewMode_)
    {
    case CameraViewMode_Orthographic:
        glOrtho(left_, right_, bottom_, top_, near_, far_);
        break;
    case CameraViewMode_Frustum:
        glFrustum(left_, right_, bottom_, top_, near_, far_);
        break;
    case CameraViewMode_Perspective:
        gluPerspective(fov_, aspect_, near_, far_);
        break;
    }

    //glTranslatef(translateX_, translateY_, translateZ_);
    //glRotatef(rotateAngle_, rotateX_, rotateY_, rotateZ_);
    //gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    gluLookAt(location_.X(), location_.Y(), location_.Z(), lookingAt_.X(), lookingAt_.Y(), lookingAt_.Z(), up_.X(), up_.Y(), up_.Z());

    glRotatef(anglesForEachAxis_.X(), 1.0, 0.0, 0.0);
    glRotatef(anglesForEachAxis_.Y(), 0.0, 1.0, 0.0);
    glRotatef(anglesForEachAxis_.Z(), 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void Camera::LookAt(float x, float y, float z)
{
    lookingAt_.X() = x;
    lookingAt_.Y() = y;
    lookingAt_.Z() = z;
}

void Camera::SetUpVector(float x, float y, float z)
{
    up_.X() = x;
    up_.Y() = y;
    up_.Z() = z;
}

void Camera::RotateXMore(float angle)
{
    anglesForEachAxis_.X() += angle;
}

void Camera::RotateYMore(float angle)
{
    anglesForEachAxis_.Y() += angle;
}

void Camera::RotateZMore(float angle)
{
    anglesForEachAxis_.Z() += angle;
}

void Camera::SetToOrthographicView(double left, double right, double bottom, double top, double zNear, double zFar)
{
    viewMode_ = CameraViewMode_Orthographic;
    left_ = left;
    right_ = right;
    bottom_ = bottom;
    top_ = top;
    near_ = zNear;
    far_ = zFar;
}

void Camera::SetToFrustumView(double left, double right, double bottom, double top, double zNear, double zFar)
{
    viewMode_ = CameraViewMode_Frustum;
    left_ = left;
    right_ = right;
    bottom_ = bottom;
    top_ = top;
    near_ = zNear;
    far_ = zFar;
}

void Camera::SetToPerspectiveView(double fov, double aspect, double zNear, double zFar)
{
    viewMode_ = CameraViewMode_Perspective;
    fov_ = fov;
    aspect_ = aspect;
    near_ = zNear;
    far_ = zFar;
}

void Camera::ResetRotation()
{
    anglesForEachAxis_ = Vector3::ZERO;
}

}

