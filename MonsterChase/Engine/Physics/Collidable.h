#pragma once
#include "AxisAlignedBoundingBox.h"
#include "../GameObject.h"
#include <string>

class Collidable
{
public:
	Collidable() = default;
	Collidable(GameObject * i_GameObject, const float i_SizeX, const float i_SizeY, const float i_SizeZ) 
		: m_pGameObject(i_GameObject), m_SizeX(i_SizeX), m_SizeY(i_SizeY), m_SizeZ(i_SizeZ) {
		m_Name = i_GameObject->GetName();
		m_Position = i_GameObject->GetPosition();
		m_Velocity = i_GameObject->GetVelocity();
		InitAABB();
	}

	void InitAABB(); // initilize the AABB representation
	void UpdateAABB(); // recompute position of AABB
	Vector3D GetPosition();
	inline std::string GetName() const { return m_Name; }
	inline std::string SetName(const std::string & i_str) { m_Name = i_str; }
	inline bool operator == (const Collidable & i_col) { return this->m_Name == i_col.GetName(); }
	inline AxisAlignedBoundingBox & GetAABB() { return m_AABB; }
	inline bool IsBouncy() { return m_ShouldBounceOff; }
	inline void SetBouncy(bool i_bBouncy) { m_ShouldBounceOff = i_bBouncy; }
	
	inline void SetSizeX(float i_SizeX) { m_SizeX = i_SizeX; }
	inline void SetSizeY(float i_SizeY) { m_SizeY = i_SizeY; }
	inline void SetSizeZ(float i_SizeZ) { m_SizeZ = i_SizeZ; }
	inline void SetSize(float i_SizeX, float i_SizeY, float i_SizeZ) {
		m_SizeX = i_SizeX;
		m_SizeY = i_SizeY;
		m_SizeZ = i_SizeZ;
	}

	inline void SetGameObject(GameObject * i_pGameObject) { m_pGameObject = i_pGameObject; }
	inline GameObject * GetGameObject() { return m_pGameObject; }

	inline Vector3D GetVelocity() { return m_pGameObject->GetVelocity(); }
	void SetVelocity(float i_VeloX, float i_VeloY, float i_VeloZ);

	// Change the direction of velocity with a unit vector
	void ChangeVelocityDirection(const Vector3D & i_DeltaVec);
	void MoveWithVelocity();

	~Collidable() {};

private:
	GameObject * m_pGameObject;
	AxisAlignedBoundingBox m_AABB;
	bool m_ShouldBounceOff; // if the object should bounce off upon collision

	Vector3D m_Position;
	float m_SizeX; // size of the collision box (AABB / OBB)
	float m_SizeY;
	float m_SizeZ;
	Vector3D m_MinPosition;
	Vector3D m_MaxPosition;

	Vector3D m_Velocity;

	std::string m_Name;
};
