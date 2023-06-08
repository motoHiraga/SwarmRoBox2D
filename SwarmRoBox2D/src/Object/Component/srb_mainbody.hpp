/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_COMPONENT_SRB_MAINBODY_HPP_
#define OBJECT_COMPONENT_SRB_MAINBODY_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbMainBodyConf;

class srbMainBody: public srbComponent
{
public:

	srbMainBody(srbMainBodyConf *conf, srbObject *object);
	~srbMainBody();

	void Update()
	{
	}

	b2Shape *shape;
};

struct srbMainBodyConf: public srbComponentConf
{
	srbMainBodyConf()
	{
		shape = nullptr;
		friction = 0.1f;
		density = 0.0f;
		restitution = 0.3f;

		isGroundFricition = false;
		isStatic = false;
		isTouchable = true;
	}

	/// Shape for this component.
	/// See b2_shape.h for details.
	/// e_circle = 0, e_edge = 1, e_polygon = 2, e_chain = 3, e_typeCount = 4
	b2Shape *shape;
	b2CircleShape circleShape;
	b2EdgeShape edgeShape;
	b2PolygonShape polygonShape;
	b2ChainShape chainShape;

	/// Parameters for b2Fixture.
	float friction;
	float density;
	float restitution;

	/// Friction with the ground body.
	bool isGroundFricition;

	/// Set as a static body.
	bool isStatic;

	/// Disable collisions.
	bool isTouchable;

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbMainBody((srbMainBodyConf*) conf, object);
	}
};

#endif /* OBJECT_COMPONENT_SRB_MAINBODY_HPP_ */
