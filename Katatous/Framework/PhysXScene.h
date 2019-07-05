#pragma once
#include "PhysXCommons.h"

class PhysXManager;

class PhysXScene
{
private:
	PhysXManager*						m_manager;
	px_unique_ptr<physx::PxScene>		m_scene;

public:
	PhysXScene(const px_unique_ptr<physx::PxScene>& scene);
	~PhysXScene();

	// �V�[��Pvd�L����
	void ActivatePvd();
	// �I�u�W�F�N�g�ǉ�
	void CreateObject(const physx::PxRigidStatic& obj);
};

