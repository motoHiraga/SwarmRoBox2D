/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_SRB_ARENA_HPP_
#define OBJECT_SRB_ARENA_HPP_

#include "Component/srb_wall.hpp"

struct srbArenaConf;

class srbArena: public srbObject
{
public:
	srbArena(srbArenaConf *def, srbSimulation *simulation);
	virtual ~srbArena()
	{
	}

	static const int32 wall_count = 4;
	float wall_length_x;
	float wall_length_y;

	srbWall *wall[wall_count];
};

struct srbArenaConf: public srbObjectConf
{
	srbArenaConf()
	{
		wall_length_x = 50.0f;
		wall_length_y = 60.0f;
	}

	float wall_length_x;
	float wall_length_y;

	srbObject* createFcn(srbObjectConf *conf, srbSimulation *simulation)
	{
		return new srbArena((srbArenaConf*) conf, simulation);
	}
};

#endif /* OBJECT_SRB_ARENA_HPP_ */
