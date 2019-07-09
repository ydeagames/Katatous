#pragma once
#include <Utilities/picojson.h>

class ISerializedObject
{
	virtual void operator<<(const picojson::value&) = 0;
	virtual void operator>>(picojson::value&) const = 0;
};

class ISerializable
{
	virtual 
};

class SerializableObject
{
private:
	std::unordered_map<std::wstring, SerializableObject> m_fields;
};

class SerializableRegistry
{
public:
	static std::unordered_map<std::wstring, SerializableObject> s_registry;

};
