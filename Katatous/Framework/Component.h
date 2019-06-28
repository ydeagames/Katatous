#pragma once

class GameContext;
class GameObject;

#define COMPONENT(TYPE) \
	public: \
		using Base = TYPE;

// �R���|�[�l���g
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

public:
	GameObject* gameObject = nullptr;

public:
	// ����
	virtual void Initialize(GameContext& context) {}
	// �X�V
	virtual void Update(GameContext& context) {}
	// �`��
	virtual void Render(GameContext& context) {}
	// �j��
	virtual void Finalize(GameContext& context) {}
};
