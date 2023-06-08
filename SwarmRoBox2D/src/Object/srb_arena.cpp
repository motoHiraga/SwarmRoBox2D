/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_arena.hpp"

srbArena::srbArena(srbArenaConf *conf, srbSimulation *simulation) :
		srbObject(conf, simulation)
{
	wall_length_x = conf->wall_length_x;
	wall_length_y = conf->wall_length_y;

	srbWallConf wc;
	wc.density = 0.0f;
	wc.friction = 0.7f;
	wc.restitution = 0.0f;

	wc.start_point = b2Vec2(wall_length_x / 2.0f, wall_length_y / 2.0f);
	wc.end_point = b2Vec2(wall_length_x / 2.0f, -wall_length_y / 2.0f);
	wall[0] = (srbWall*) CreateComponent(&wc);

	wc.start_point = b2Vec2(wall_length_x / 2.0f, -wall_length_y / 2.0f);
	wc.end_point = b2Vec2(-wall_length_x / 2.0f, -wall_length_y / 2.0f);
	wall[1] = (srbWall*) CreateComponent(&wc);

	wc.start_point = b2Vec2(-wall_length_x / 2.0f, -wall_length_y / 2.0f);
	wc.end_point = b2Vec2(-wall_length_x / 2.0f, wall_length_y / 2.0f);
	wall[2] = (srbWall*) CreateComponent(&wc);

	wc.start_point = b2Vec2(-wall_length_x / 2.0f, wall_length_y / 2.0f);
	wc.end_point = b2Vec2(wall_length_x / 2.0f, wall_length_y / 2.0f);
	wall[3] = (srbWall*) CreateComponent(&wc);
}

