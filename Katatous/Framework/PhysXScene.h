#pragma once
#include "PhysXCommons.h"

class PhysXManager;

class PhysXScene
{
private:
	px_unique_ptr<physx::PxScene>		m_scene;

public:
	PhysXScene(const px_unique_ptr<physx::PxScene>& scene);
	~PhysXScene();

	// �V�[���擾
	physx::PxScene& GetScene();
	// �V�[��Pvd�L����
	void ActivatePvd();
	// �I�u�W�F�N�g�ǉ�
	void CreateObject(physx::PxActor& obj);
};

