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
	gFoundation = px_unique_ptr<PxFoundation>(PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback));

	gPvd = px_unique_ptr<PxPvd>(PxCreatePvd(*gFoundation));
	gPvdTransport = px_unique_ptr<PxPvdTransport>(PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10));
	gPvd->connect(*gPvdTransport, PxPvdInstrumentationFlag::eALL);

	gPhysics = px_unique_ptr<PxPhysics>(PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd.get()));

	gDispatcher = px_unique_ptr<PxDefaultCpuDispatcher>(PxDefaultCpuDispatcherCreate(2));
	gMaterial = px_unique_ptr<PxMaterial>(gPhysics->createMaterial(0.5f, 0.5f, 0.6f));

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
	gScene->addActor(*groundPlane);
}

void PhysXManager::Update(GameContext& context)
{
	//gScene->simulate(1.0f / 60.0f);
	gScene->simulate(float(context.GetTimer().GetElapsedSeconds()));
	gScene->fetchResults(true);
}

void PhysXManager::Render(GameContext& context)
{
}

void PhysXManager::Finalize(GameContext& context)
{
}

PhysXScene PhysXManager::CreateScene()
{
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.cpuDispatcher = gDispatcher.get();
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	return px_unique_ptr<PxScene>(gPhysics->createScene(sceneDesc));
}
