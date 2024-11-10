#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(Vector4D cameraPosition, Vector4D cameraTarget, Vector4D cameraFront, Vector4D cameraUp)
{
	camPos = cameraPosition;
	camTarget = cameraTarget;
	camFront = cameraFront;
	camUp = cameraUp;
}


Matrix4D& Camera::getPerspRef()
{
	return perspective;
}

Matrix4D Camera::getPersp()
{
	return perspective;
}

void Camera::setPersp(Matrix4D persp)
{
	perspective = persp;
}

Matrix4D& Camera::getViewRef()
{
	return view;
}

Matrix4D Camera::getView()
{
	return view;
}

void Camera::setView(Matrix4D newView)
{
	view = newView;
}
void Camera::setView()
{
	Matrix4D temp = Matrix4D::lookat(camPos, camPos + camFront, Vector4D(0.0f, 1.0f, 0.0f));
	view = temp;
}

Vector4D Camera::getPosition()
{
	return camPos;
}

void Camera::setPosition(Vector4D position)
{
	camPos = position;
}

