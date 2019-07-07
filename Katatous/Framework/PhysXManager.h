#pragma once
#include "PhysXCommons.h"

class GameContext;
class PhysXScene;

class PhysXManager
{
private:
	physx::PxDefaultAllocator						m_allocator;
	physx::PxDefaultErrorCallback					m_errorCallback;

	px_unique_ptr<physx::PxFoundation>				m_foundation;
	px_unique_ptr<physx::PxPhysics>					m_physics;

	px_unique_ptr<physx::PxDefaultCpuDispatcher>	m_dispatcher;
	px_unique_ptr<physx::PxScene>					m_scene;

	px_unique_ptr<physx::PxPvd>						m_pvd;
	px_unique_ptr<physx::PxPvdTransport>			m_pvdTransport;

public:
	PhysXManager();
	~PhysXManager();

public:
	physx::PxPhysics* GetPhysics()
	{
		return m_physics.get();
	}

	physx::PxPvd* GetPvd()
	{
		return m_pvd.get();
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

