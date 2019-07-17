#pragma once
#include "Component.h"
#include <Utilities/Property.h>

// Transform�N���X
class Transform : public Component
{
public:
	// �R���X�g���N�^
	Transform::Transform()
		: parent(nullptr)
		, localPosition(DirectX::SimpleMath::Vector3::Zero)
		, localRotation(DirectX::SimpleMath::Quaternion::Identity)
		, localScale(DirectX::SimpleMath::Vector3::One)
	{
	}

public:
	// ���[�J���ʒu
	DirectX::SimpleMath::Vector3 localPosition;
	// ���[�J����]
	DirectX::SimpleMath::Quaternion localRotation;
	// ���[�J���X�P�[��
	DirectX::SimpleMath::Vector3 localScale;

	Property<DirectX::SimpleMath::Vector3> position
	{
		[&]()
		{
			if (parent)
				return DirectX::SimpleMath::Vector3::Transform(localPosition, parent->GetMatrix().Invert());
			else
				return localPosition;
		},
		[&](const auto& value)
		{
			if (parent)
				localPosition = DirectX::SimpleMath::Vector3::Transform(value, parent->GetMatrix());
			else
				localPosition = value;
		}
	};

	Property<DirectX::SimpleMath::Quaternion> rotation
	{
		[&]()
		{
			if (parent)
				return localRotation * DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(parent->GetMatrix().Invert());
			else
				return localRotation;
		},
		[&](const auto& value)
		{
			if (parent)
				localRotation = value * DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(parent->GetMatrix());
			else
				localRotation = value;
		}
	};

	Property<DirectX::SimpleMath::Vector3> lossyScale
	{
		[&]()
		{
			if (parent)
			{
				DirectX::SimpleMath::Vector3 parentPosition;
				DirectX::SimpleMath::Quaternion parentRotation;
				DirectX::SimpleMath::Vector3 parentScale;
				parent->GetMatrix().Decompose(parentScale, parentRotation, parentPosition);
				auto mat = DirectX::SimpleMath::Matrix::CreateScale(parentScale) * DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotation);
				return DirectX::SimpleMath::Vector3::Transform(localScale, mat.Invert());
			}
			else
				return localScale;
		},
		[&](const auto& value)
		{
			if (parent)
			{
				DirectX::SimpleMath::Vector3 parentPosition;
				DirectX::SimpleMath::Quaternion parentRotation;
				DirectX::SimpleMath::Vector3 parentScale;
				parent->GetMatrix().Decompose(parentScale, parentRotation, parentPosition);
				auto mat = DirectX::SimpleMath::Matrix::CreateScale(parentScale) * DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotation);
				localScale = DirectX::SimpleMath::Vector3::Transform(value, mat);
			}
			else
				localScale = value;
		}
	};

	const Transform* parent;
	void SetParent(const Transform* value)
	{
		DirectX::SimpleMath::Vector3 worldPosition = position;
		DirectX::SimpleMath::Quaternion worldRotation = rotation;
		DirectX::SimpleMath::Vector3 worldScale = lossyScale;
		parent = value;
		position = worldPosition;
		rotation = worldRotation;
		lossyScale = worldScale;
	}

	// �s��擾
	DirectX::SimpleMath::Matrix GetMatrix() const
	{
		return
			DirectX::SimpleMath::Matrix::CreateScale(localScale) *
			DirectX::SimpleMath::Matrix::CreateFromQuaternion(localRotation) *
			DirectX::SimpleMath::Matrix::CreateTranslation(localPosition) *
			(parent != nullptr ? parent->GetMatrix() : DirectX::SimpleMath::Matrix::Identity);
	}
};