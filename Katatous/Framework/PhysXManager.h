#pragma once
#include "PhysXCommons.h"

class GameContext;
class PhysXScene;

class PhysXManager
{
private:
	physx::PxDefaultAllocator			gAllocator;
	physx::PxDefaultErrorCallback		gErrorCallback;

	px_unique_ptr<physx::PxFoundation>	gFoundation;
	px_unique_ptr<physx::PxPhysics>		gPhysics;

	px_unique_ptr<physx::PxDefaultCpuDispatcher> gDispatcher;
	px_unique_ptr<physx::PxScene>		gScene;

	px_unique_ptr<physx::PxMaterial>	gMaterial;

	px_unique_ptr<physx::PxPvd>			gPvd;
	px_unique_ptr<physx::PxPvdTransport>gPvdTransport;

public:
	PhysXManager();
	~PhysXManager();

public:
	physx::PxPhysics* GetPhysics()
	{
		return gPhysics.get();
	}

	physx::PxPvd* GetPvd()
	{
		return gPvd.get();
	}

	physx::PxMaterial* GetDefaultMaterial()
	{
		return PxMaterial.get();
	}

	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
	// 破棄
	void Finalize(GameContext& context);

	// シーン作成
	PhysXScene CreateScene();
};

