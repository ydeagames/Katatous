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

	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);

	// �V�[���쐬
	PhysXScene CreateScene();
};

