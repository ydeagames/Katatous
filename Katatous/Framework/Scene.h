#pragma once
#include "Component.h"

class GameObject;
class PhysXScene;
class GameContext;

// ゲームオブジェクトコンテナ
class Scene : public Component
{
public:
	// 子ゲームオブジェクト
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	// PhysX
	std::unique_ptr<PhysXScene> physics;

public:
	Scene();
	~Scene();

public:
	void Add(const std::shared_ptr<GameObject>& obj);

public:
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
	// 破棄
	void Finalize(GameContext& context);
};