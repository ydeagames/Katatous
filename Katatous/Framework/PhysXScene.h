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

	// シーン取得
	physx::PxScene& GetScene();
	// シーンPvd有効化
	void ActivatePvd();
	// オブジェクト追加
	void CreateObject(physx::PxActor& obj);
};

