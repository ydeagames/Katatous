#pragma once
#include "Component.h"

class GameObject;
class PhysXScene;
class GameContext;

// �Q�[���I�u�W�F�N�g�R���e�i
class Scene : public Component
{
public:
	// �q�Q�[���I�u�W�F�N�g
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	// PhysX
	std::unique_ptr<PhysXScene> physics;

public:
	Scene();
	~Scene();

public:
	void Add(const std::shared_ptr<GameObject>& obj);

public:
	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);
};