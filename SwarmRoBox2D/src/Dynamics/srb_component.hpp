/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef DYNAMICS_SRB_COMPONENT_HPP_
#define DYNAMICS_SRB_COMPONENT_HPP_

#include "srb_common.hpp"

class srbObject;
class srbComponent;

struct srbComponentConf
{
	srbComponentConf()
	{
		position = b2Vec2(0.0f, 0.0f);
		angle = 0.0f;

		m_componentFixtureType = 0;
		m_parentMainBody = nullptr;

		io_buffer = nullptr;
	}
	virtual ~srbComponentConf()
	{
	}

	/// Override this function.
	/// @return pointer of derived class's instance.
	virtual srbComponent* createFcn(srbComponentConf *conf,
			srbObject *object) = 0;

	b2Vec2 position;
	float angle;
	b2Body *m_parentMainBody;

	/// User data to track components.
	int32 m_componentFixtureType;

	/// Pointer of the data buffer to store inputs and outputs.
	std::vector<float>* io_buffer;
};

class srbComponent
{
public:
	srbComponent(srbComponentConf *conf, srbObject *object);
	virtual ~srbComponent()
	{
	}

	/// Do something. Called by srbObject::Update.
	virtual void Update() = 0;

	/// Refresh parameters if necessary.
	virtual void Refresh()
	{
	}

	/// Get the world position of the component.
	/// @return the world position of the component.
	virtual b2Vec2 GetPosition() const;

	/// Get the angle.
	/// @return the current world rotation angle.
	virtual float GetAngle() const;

	/// Get the total mass of the component.
	/// @return the mass, in kilograms.
	virtual float GetMass() const;

	/// Get the parent object of this component.
	srbObject* GetObject();
	const srbObject* GetObject() const;

	/// Get the pointer to the b2Body of this component if exists.
	b2Body* GetBody();
	const b2Body* GetBody() const;

	/// Get the next a2Component in the list.
	srbComponent* GetNext();
	const srbComponent* GetNext() const;

	/// Get the previous a2Component in the list.
	srbComponent* GetPrev();
	const srbComponent* GetPrev() const;

	/// Returns the fixture type of the component defined by user.
	int32 GetComponentFixtureType() const;

protected:

	friend class srbObject;

	srbObject *m_object;

	srbComponent *m_prev;
	srbComponent *m_next;

	b2Body *m_body;
	b2Body *m_parentMainBody;

	b2Vec2 worldPosition;
	float worldAngle;

	int32 m_componentFixtureType;

	std::vector<float>* io_buffer;
};

inline b2Vec2 srbComponent::GetPosition() const
{
	if (m_body)
	{
		return m_body->GetPosition();
	}
	else
	{
		return worldPosition;
	}
}

inline float srbComponent::GetAngle() const
{
	if (m_body)
	{
		return m_body->GetAngle();
	}
	else
	{
		return worldAngle;
	}
}

inline float srbComponent::GetMass() const
{
	if (m_body)
	{
		return m_body->GetMass();
	}
	else
	{
		return 0.0f;
	}
}

inline srbObject* srbComponent::GetObject()
{
	return m_object;
}

inline const srbObject* srbComponent::GetObject() const
{
	return m_object;
}

inline b2Body* srbComponent::GetBody()
{
	return m_body;
}

inline const b2Body* srbComponent::GetBody() const
{
	return m_body;
}

inline srbComponent* srbComponent::GetNext()
{
	return m_next;
}

inline const srbComponent* srbComponent::GetNext() const
{
	return m_next;
}

inline srbComponent* srbComponent::GetPrev()
{
	return m_prev;
}

inline const srbComponent* srbComponent::GetPrev() const
{
	return m_prev;
}

inline int32 srbComponent::GetComponentFixtureType() const
{
	return m_componentFixtureType;
}

#endif /* DYNAMICS_SRB_COMPONENT_HPP_ */
