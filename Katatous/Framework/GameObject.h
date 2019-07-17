#pragma once
#include "Transform.h"
#include "Component.h"
#include <Utilities/TypeId.h>

class GameContext;

template <typename T>
struct hasParent {
private:
	template <typename U>
	static typename U::Bases test(int);
	template <typename>
	static void test(...);
public:
	enum { value = !std::is_void<decltype(test<T>(0))>::value };
};

// �Q�[���I�u�W�F�N�g
class GameObject final : public std::enable_shared_from_this<GameObject>
{
private:
	std::vector<std::shared_ptr<Component>> m_components;
	std::unordered_map<type_id_t, std::shared_ptr<Component>> m_componentMap;

public:
	std::shared_ptr<Transform> transform;
	bool destroyed;

private:
	struct Impl
	{
		template<typename U>
		static auto AddComponentOne(std::unordered_map<type_id_t, std::shared_ptr<Component>>& components, const std::shared_ptr<U>& component)
			-> void
		{
			components.insert(std::make_pair(type_id<U>(), component));
		}

		template<typename U>
		static auto AddComponents(std::unordered_map<type_id_t, std::shared_ptr<Component>>& components, const std::shared_ptr<U>& component)
			-> std::enable_if_t<hasParent<U>::value>
		{
			AddComponentOne<U>(components, component);
			AddComponents<U::Base>(components, component);
		}

		template<typename U>
		static auto AddComponents(std::unordered_map<type_id_t, std::shared_ptr<Component>>& components, const std::shared_ptr<U>& component)
			-> std::enable_if_t<!hasParent<U>::value>
		{
			AddComponentOne<U>(components, component);
		}
	};

public:
	template<typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		auto component = std::make_shared<T>(std::forward<Args>(args)...);
		component->gameObject = this;
		m_components.push_back(component);
		Impl::AddComponents<T>(m_componentMap, component);
		return component;
	}

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		return std::dynamic_pointer_cast<T>(m_componentMap[type_id<T>()]);
	}

private:
	GameObject()
		: destroyed(false)
	{
		transform = AddComponent<Transform>();
	}

public:
	~GameObject() = default;

	static void Destroy(GameObject& obj)
	{
		obj.destroyed = true;
	}

	static std::shared_ptr<GameObject> Create()
	{
		return std::shared_ptr<GameObject>(new GameObject());
	}

public:
	// ����
	void Initialize(GameContext& context)
	{
		for (auto& component : m_components)
			component->Initialize(context);
	}

	// �X�V
	void Update(GameContext& context)
	{
		for (auto& component : m_components)
			component->Update(context);
	}

	// �`��
	void Render(GameContext& context)
	{
		for (auto& component : m_components)
			component->Render(context);
	}

	// �j��
	void Finalize(GameContext& context)
	{
		for (auto& component : m_components)
			component->Finalize(context);
	}
};

