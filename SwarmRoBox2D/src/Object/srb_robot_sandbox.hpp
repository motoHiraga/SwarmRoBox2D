/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_SRB_ROBOT_SANDBOX_HPP_
#define OBJECT_SRB_ROBOT_SANDBOX_HPP_

#include "Component/srb_mainbody.hpp"
#include "Component/srb_tire.hpp"


struct srbRobotSBConf;

class srbRobotSB: public srbObject
{
public:
	srbRobotSB(srbRobotSBConf *conf, srbSimulation *simulaiton);
	virtual ~srbRobotSB()
	{
	}

	srbMainBody *mainBody;
	srbTire *tire[2];

	/// Get the pointer of m_io_buffer of the robot.
	std::vector<float>* GetIOBuffer();

protected:

	/// Data buffer to store inputs and outputs of the controller.
	std::vector<float> m_io_buffer;
};

struct srbRobotSBConf: srbObjectConf
{
	srbRobotSBConf()
	{
		robot_radius = 1.0f;
	}

	float robot_radius;

	srbObject* createFcn(srbObjectConf *conf, srbSimulation *simulaiton)
	{
		return new srbRobotSB((srbRobotSBConf*) conf, simulaiton);
	}
};

inline std::vector<float>* srbRobotSB::GetIOBuffer()
{
	return &m_io_buffer;
}

#endif /* OBJECT_SRB_ROBOT_SANDBOX_HPP_ */
