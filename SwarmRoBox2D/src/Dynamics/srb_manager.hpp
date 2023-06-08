/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef DYNAMICS_MANAGER_HPP_
#define DYNAMICS_MANAGER_HPP_

#include "srb_common.hpp"

class srbSimulation;
class srbManager;

class srbManager: public b2ContactListener
{
public:
	/// Constructor.
	srbManager()
	{
		m_simulation = nullptr;
	}

	virtual ~srbManager()
	{
	}

	void SetSimulation(srbSimulation *simulation);

	/// Override this function in derived classes.
	/// Initialization for evaluation.
	virtual void EvaluateInit()
	{
	}

	/// Override this function in derived classes.
	/// Evaluation in each timestep.
	virtual void EvaluateStep()
	{
	}

	/// Override this function in derived classes.
	/// Evaluation after the game is over.
	virtual void EvaluateEnd()
	{
	}

	/// Report fitness of <srbSimulation* m_simulation>.
	/// @return fitness.
	virtual const void* EvaluationReport() const = 0;

	/// Let derived tests know that a joint was destroyed.
	virtual void JointDestroyed(b2Joint *joint)
	{
		B2_NOT_USED(joint);
	}

	/// Callbacks for derived classes.
	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact *contact) override
	{
		B2_NOT_USED(contact);
	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact *contact) override
	{
		B2_NOT_USED(contact);
	}

	/// This is called after a contact is updated. This allows you to inspect a
	/// contact before it goes to the solver. If you are careful, you can modify the
	/// contact manifold (e.g. disable contact).
	/// A copy of the old manifold is provided so that you can detect changes.
	/// Note: this is called only for awake bodies.
	/// Note: this is called even when the number of contact points is zero.
	/// Note: this is not called for sensors.
	/// Note: if you set the number of contact points to zero, you will not
	/// get an EndContact callback. However, you may get a BeginContact callback
	/// the next step.
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
	override
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	/// This lets you inspect a contact after the solver is finished. This is useful
	/// for inspecting impulses.
	/// Note: the contact manifold does not include time of impact impulses, which can be
	/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
	/// in a separate data structure.
	/// Note: this is only called for contacts that are touching, solid, and awake.
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
	override
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

protected:

	srbSimulation *m_simulation;
};

inline void srbManager::SetSimulation(srbSimulation *simulation)
{
	m_simulation = simulation;
}

#endif /* DYNAMICS_MANAGER_HPP_ */
