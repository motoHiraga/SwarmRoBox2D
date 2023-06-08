/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef DYNAMICS_SRB_SIMULATION_HPP_
#define DYNAMICS_SRB_SIMULATION_HPP_

#include "srb_object.hpp"
#include "srb_manager.hpp"

struct srbSettings
{
	/// This constructor sets the game definition default values.
	srbSettings()
	{
		renderMode = false;

		timeStep = 1.0f / 60.0f;
		velocityIterations = 8;
		positionIterations = 3;

		maxStepCount = 7200;

		world = nullptr;

		userData = nullptr;
	}
	/// renderMode: ture - render objects in Testbed, false - run without rendering.
	bool renderMode;

	/// Parameters for b2World::Step.
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	/// Maximum timestep.
	int32 maxStepCount;

	/// NULL if you want to create a new b2World.
	b2World *world;

	/// Use this to store application specific game data.
	void *userData;
};

class srbSimulation //: public b2ContactListener
{
public:

	srbSimulation(srbSettings *settings);
	virtual ~srbSimulation();

	virtual void Step();

	/// Refresh all objects.
	/// This performs calls to all srbObject::Refresh.
	void Refresh();

	/// Run this simulation.
	/// @param manager evaluate the simulation.
	/// @return fitness of the simulation.
	const void* Run(srbManager *manager);

	/// Create an object given a definition. No reference to the definition is retained.
	/// @warning object created first will take its step in the end.
	srbObject* CreateObject(srbObjectConf *conf);

	/// Destroy an object given a pointer.
	void DestroyObject(srbObject *object);

	/// Get <b2World* m_world>
	b2World* GetWorld();
	const b2World* GetWorld() const;

	/// Get ground b2Body.
	b2Body* GetGroundBody();
	const b2Body* GetGroundBody() const;

	/// Get timestep in this simulation.
	float GetTimeStep() const;

	/// Get current stepcount.
	int32 GetStepCount() const;

	/// Get maximum stepcount.
	int32 GetMaxStepCount() const;

	/// Get mode of this simulation.
	bool GetRenderMode() const;

	/// Get the srbObject list of this simulation.
	srbObject* GetObjectList();
	const srbObject* GetObjectList() const;

	/// Get the user data pointer that was provided in the game definition.
	void* GetUserData() const;

	/// Set current stepcount to accelerate / decelerate the game
	void SetStepCount(int32 stepcount);

protected:

	b2Body *m_groundBody;
	b2AABB m_worldAABB;
	b2World *m_world;
	int32 m_stepCount;

	bool renderMode;

	srbObject *m_objectList;

	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	int32 maxStepCount;
	void *userData;
};

inline b2World* srbSimulation::GetWorld()
{
	return m_world;
}

inline const b2World* srbSimulation::GetWorld() const
{
	return m_world;
}

inline b2Body* srbSimulation::GetGroundBody()
{
	return m_groundBody;
}

inline const b2Body* srbSimulation::GetGroundBody() const
{
	return m_groundBody;
}

inline float srbSimulation::GetTimeStep() const
{
	return timeStep;
}

inline int32 srbSimulation::GetStepCount() const
{
	return m_stepCount;
}

inline int32 srbSimulation::GetMaxStepCount() const
{
	return maxStepCount;
}

inline bool srbSimulation::GetRenderMode() const
{
	return renderMode;
}

inline srbObject* srbSimulation::GetObjectList()
{
	return m_objectList;
}

inline const srbObject* srbSimulation::GetObjectList() const
{
	return m_objectList;
}

inline void* srbSimulation::GetUserData() const
{
	return userData;
}

inline void srbSimulation::SetStepCount(int32 stepcount)
{
	m_stepCount = stepcount;
}

#endif /* DYNAMICS_SRB_SIMULATION_HPP_ */
