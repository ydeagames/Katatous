#pragma once
#include "PhysXCommons.h"
#include "Component.h"

class GameContext;
class PhysXScene;

class PhysXManager : public Component
{
private:
	physx::PxDefaultAllocator						m_allocator;
	physx::PxDefaultErrorCallback					m_errorCallback;

	px_unique_ptr<physx::PxPvdTransport>			m_pvdTransport;
	px_unique_ptr<physx::PxPvd>						m_pvd;

	px_unique_ptr<physx::PxDefaultCpuDispatcher>	m_dispatcher;

	px_unique_ptr<physx::PxPhysics>					m_physics;
	px_unique_ptr<physx::PxFoundation>				m_foundation;

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

	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);

	// �V�[���쐬
	std::unique_ptr<PhysXScene> CreateScene();
};

