#include "pch.h"
#include "PhysXManager.h"

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
	auto transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = px_unique_ptr<PxPhysics>(PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd.get()));

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = px_unique_ptr<PxDefaultCpuDispatcher>(PxDefaultCpuDispatcherCreate(2));
	sceneDesc.cpuDispatcher = gDispatcher.get();
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = px_unique_ptr<PxScene>(gPhysics->createScene(sceneDesc));

	auto pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	gMaterial = px_unique_ptr<PxMaterial>(gPhysics->createMaterial(0.5f, 0.5f, 0.6f));

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
	gScene->addActor(*groundPlane);
}

void PhysXManager::Update(GameContext& context)
{
}

void PhysXManager::Render(GameContext& context)
{
}

void PhysXManager::Finalize(GameContext& context)
{
}
