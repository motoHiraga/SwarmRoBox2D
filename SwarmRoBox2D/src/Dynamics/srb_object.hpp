/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef DYNAMICS_SRB_OBJECT_HPP_
#define DYNAMICS_SRB_OBJECT_HPP_

#include "srb_component.hpp"

class srbSimulation;

struct srbObjectConf
{
	srbObjectConf()
	{
		position = b2Vec2(0.0f, 0.0f);
		angle = 0.0f;
	}
	virtual ~srbObjectConf()
	{
	}

	/// Override this function.
	/// @return pointer of derived class's instance.
	virtual srbObject* createFcn(srbObjectConf *conf,
			srbSimulation *simulation) = 0;

	b2Vec2 position;
	float angle;
};

class srbObject
{
public:
	srbObject(srbObjectConf *conf, srbSimulation *simulation);
	virtual ~srbObject();

	/// Do something.
	/// This performs calls to all srbComponent::Act, called by srbSimulation::Step.
	void Update();

	void Refresh();

	/// Create a component given a definition. No reference to the definition is retained.
	/// @warning component created first will take its step in the end.
	srbComponent* CreateComponent(srbComponentConf *conf);

	/// Destroy a component given a pointer.
	void DestroyComponent(srbComponent *component);

	/// Get the total mass of the object.
	/// @return the mass, in kilograms.
	float GetMass() const;

	/// Get the world position of the object's main body.
	/// @return the world position of the object's main body.
	const b2Vec2& GetPosition() const;

	/// Get the mainbody's angle.
	/// @return the current world rotation angle of the main body.
	float GetAngle() const;

	/// Get original world position of the object
	const b2Vec2& GetWorldPosition() const;

	/// Get the original world rotation angle.
	float GetWorldAngle() const;

	/// Get the parent simulation of this object.
	srbSimulation* GetSimulation();
	const srbSimulation* GetSimulation() const;

	/// Get the main body of this object.
	/// @warning All objects must have main body.
	b2Body* GetMainBody();
	const b2Body* GetMainBody() const;

	/// Get the next a2Object in the list
	srbObject* GetNext();
	const srbObject* GetNext() const;

	/// Get the previous a2Object in the list
	srbObject* GetPrev();
	const srbObject* GetPrev() const;

	/// Get the a2Component list of this a2Object
	srbComponent* GetComponentList();
	const srbComponent* GetComponentList() const;

	/// Set the main body of this object.
	void SetMainBody(b2Body *body);

protected:

	friend class srbSimulation;

	srbSimulation *m_simulation;

	srbObject *m_prev;
	srbObject *m_next;
	srbComponent *m_componentList;

	b2Body *m_mainBody;

	b2Vec2 worldPosition;
	float worldAngle;
};

inline const b2Vec2& srbObject::GetPosition() const
{
	return m_mainBody->GetPosition();
}

inline float srbObject::GetAngle() const
{
	return m_mainBody->GetAngle();
}

inline const b2Vec2& srbObject::GetWorldPosition() const
{
	return worldPosition;
}

inline float srbObject::GetWorldAngle() const
{
	return worldAngle;
}

inline srbSimulation* srbObject::GetSimulation()
{
	return m_simulation;
}

inline const srbSimulation* srbObject::GetSimulation() const
{
	return m_simulation;
}

inline b2Body* srbObject::GetMainBody()
{
	return m_mainBody;
}

inline const b2Body* srbObject::GetMainBody() const
{
	return m_mainBody;
}

inline srbObject* srbObject::GetNext()
{
	return m_next;
}

inline const srbObject* srbObject::GetNext() const
{
	return m_next;
}

inline srbObject* srbObject::GetPrev()
{
	return m_prev;
}

inline const srbObject* srbObject::GetPrev() const
{
	return m_prev;
}

inline srbComponent* srbObject::GetComponentList()
{
	return m_componentList;
}

inline const srbComponent* srbObject::GetComponentList() const
{
	return m_componentList;
}

inline void srbObject::SetMainBody(b2Body *body)
{
	m_mainBody = body;
}

#endif /* DYNAMICS_SRB_OBJECT_HPP_ */
