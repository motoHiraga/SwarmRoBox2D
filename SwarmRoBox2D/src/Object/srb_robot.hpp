/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_SRB_ROBOT_HPP_
#define OBJECT_SRB_ROBOT_HPP_

#include "Component/srb_mainbody.hpp"
#include "Component/srb_tire.hpp"
#include "Component/srb_ray_cast_sensor.hpp"
#include "Component/srb_omnicamera.hpp"
#include "Component/srb_compass.hpp"

#include "Controller/srb_neural_network.hpp"

struct srbRobotConf;

class srbRobot: public srbObject
{
public:
	srbRobot(srbRobotConf *conf, srbSimulation *simulaiton);
	virtual ~srbRobot()
	{
	}

	srbMainBody *mainBody;
	srbTire *tire[2];

	srbNeuralNetwork *network;

	srbRayCastSensor *rayCastSensor[7];
	srbOmniCamera *omniCamera[2];
	srbCompass *compass;

	/// Get the pointer of m_io_buffer of the robot.
	std::vector<float>* GetIOBuffer();

protected:

	/// Data buffer to store inputs and outputs of the controller.
	std::vector<float> m_io_buffer;

	srbRandomTools *random_tools;
};

struct srbRobotConf: srbObjectConf
{
	srbRobotConf()
	{
		robot_radius = 1.0f;
		ray_cast_range = 4.0f;
		ray_cast_sensor_count = 7;
		omni_camera_range = 10.0f;
		omni_camera_partition_count = 4;

		random_tools = nullptr;
	}

	float robot_radius;
	float ray_cast_range;
	int32 ray_cast_sensor_count;
	float omni_camera_range;
	int32 omni_camera_partition_count;

	srbRandomTools *random_tools;

	srbObject* createFcn(srbObjectConf *conf, srbSimulation *simulaiton)
	{
		return new srbRobot((srbRobotConf*) conf, simulaiton);
	}
};

inline std::vector<float>* srbRobot::GetIOBuffer()
{
	return &m_io_buffer;
}

#endif /* OBJECT_SRB_ROBOT_HPP_ */
