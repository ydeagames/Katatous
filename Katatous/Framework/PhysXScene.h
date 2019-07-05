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

	// シーンPvd有効化
	void ActivatePvd();
	// オブジェクト追加
	void CreateObject(const physx::PxRigidStatic& obj);
};

