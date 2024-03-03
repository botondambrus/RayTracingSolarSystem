#include "Canvas.h"

void Canvas::allignToCamera(Camera* camera)
{
	mTransform = glm::inverse(camera->getViewMatrix());
}

glm::mat4 Canvas::getTransform() const
{
	return mTransform;
}
