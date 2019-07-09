#include "pch.h"
#include "PhysXManager.h"
#include "PhysXScene.h"
#include "GameContext.h"
#include <Common/StepTimer.h>

using namespace physx;

PhysXManager::PhysXManager()
{
}

PhysXManager::~PhysXManager()
{
}

void PhysXManager::Initialize(GameContext& context)
{
	m_foundation = px_unique_ptr<PxFoundation>(PxCreateFoundation(PX_PHYSICS_VERSION, m_allocator, m_errorCallback));

	m_pvd = px_unique_ptr<PxPvd>(PxCreatePvd(*m_foundation));
	m_pvdTransport = px_unique_ptr<PxPvdTransport>(PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10));
	m_pvd->connect(*m_pvdTransport, PxPvdInstrumentationFlag::eALL);

	m_physics = px_unique_ptr<PxPhysics>(PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale(), true, m_pvd.get()));

	m_dispatcher = px_unique_ptr<PxDefaultCpuDispatcher>(PxDefaultCpuDispatcherCreate(2));
}

void PhysXManager::Update(GameContext& context)
{
	auto num = m_physics->getNbScenes();
	if (num)
	{
		std::vector<physx::PxScene*> scenes(num);
		m_physics->getScenes(&scenes[0], num);

		for (auto& scene : scenes)
		{
			//scene->simulate(1.0f / 60.0f);
			scene->simulate(float(context.GetTimer().GetElapsedSeconds()));
			scene->fetchResults(true);
		}
	}
}

void PhysXManager::Render(GameContext& context)
{
}

void PhysXManager::Finalize(GameContext& context)
{
}

std::unique_ptr<PhysXScene> PhysXManager::CreateScene()
{
	PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.cpuDispatcher = m_dispatcher.get();
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	return std::make_unique<PhysXScene>(px_unique_ptr<PxScene>(m_physics->createScene(sceneDesc)));
}
