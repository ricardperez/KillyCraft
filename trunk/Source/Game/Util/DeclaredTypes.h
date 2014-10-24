//
//  DeclaredTypes.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#ifndef KillyCraft_DeclaredTypes_h
#define KillyCraft_DeclaredTypes_h

#include <string>

class Type
{
public:
	Type(const std::string& typeStr, const Type* baseType) : typeStr(typeStr), baseType(baseType) {}
	const std::string& getTypeStr() const { return typeStr; }
	const Type* getBaseType() const { return baseType; }

	virtual bool isA(const Type* type) const
	{
		if (typeStr == type->getTypeStr())
		{
			return true;
		}
		else if (baseType != nullptr)
		{
			return baseType->isA(type);
		}
		
		return false;
	}
	
private:
	std::string typeStr;
	const Type* baseType;
};

#define DECLARE_BASE_TYPE(name) \
static const Type* getClassType() { static Type t(#name, nullptr); return &t; } \
virtual const Type* getInstanceType() const { return getClassType(); } \
template <typename T> bool isA() const { return getInstanceType()->isA(T::getClassType()); } \
template <typename T> T* asA() const { if (isA<T>()) { return static_cast<T*>(this); } return nullptr; }

#define DECLARE_TYPE_WITH_BASE_TYPE(name, baseName) \
typedef baseName Base; \
static const Type* getClassType() { static Type t(#name, baseName::getClassType()); return &t; } \
virtual const Type* getInstanceType() const { return getClassType(); } \
template <typename T> bool isA() const { return getInstanceType()->isA(T::getClassType()); } \
template <typename T> T* asA() const { if (isA<T>()) { return static_cast<T*>(this); } return nullptr; }


#endif
