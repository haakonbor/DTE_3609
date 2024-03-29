#include <windows.h>
#include "../include/SceneObject.hpp"

#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"
#include <GL/gl.h>

// NB! Check matrix mult and scoped_ptr

SceneObject::SceneObject()
{
  matrix_ = glm::mat4(1.0f);
}

SceneObject::~SceneObject()
{
}

void SceneObject::render()
{
  glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix_));
    this->privateRender();
    for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
        it != children_.end(); it++)
        (*it)->render();
  glPopMatrix();
}

void SceneObject::update(double fps)
{
  this->fps_ = fps;
  this->privateUpdate();
  for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++) {
      // Update each sceneobject's view matrix to be the camera position,
      // which in this case is the gamemanager's model matrix
      (*it)->viewMatrix_ = matrix_;
      (*it)->update(fps);
  }

}

void SceneObject::init()
{
  this->privateInit();
  for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
      (*it)->init();
}

void SceneObject::addSubObject(std::shared_ptr<SceneObject> newchild)
{
  children_.push_back(newchild);
}

void SceneObject::removeSubObject(const std::shared_ptr<SceneObject> child)
{
  for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
    if(*it == child)
    {
      children_.erase(it);
      break;
    }
}


