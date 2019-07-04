#pragma once

class GameContext;

class PhysXManager
{
public:
	template<typename T>
	struct px_deleter
	{
		void operator()(T* t)
		{
			if (t)
				t->release();
		}
	};

	template<typename T>
	using px_unique_ptr = std::unique_ptr<T, px_deleter<T>>;

private:
	physx::PxDefaultAllocator			gAllocator;
	physx::PxDefaultErrorCallback		gErrorCallback;

	px_unique_ptr<physx::PxFoundation>	gFoundation = NULL;
	px_unique_ptr<physx::PxPhysics>		gPhysics = NULL;

	px_unique_ptr<physx::PxDefaultCpuDispatcher> gDispatcher = NULL;
	px_unique_ptr<physx::PxScene>		gScene = NULL;

	px_unique_ptr<physx::PxMaterial>	gMaterial = NULL;

	px_unique_ptr<physx::PxPvd>			gPvd = NULL;

public:
	PhysXManager();
	~PhysXManager();

	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);
};

