/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef OBJECT_COMPONENT_SRB_OMNICAMERA_HPP_
#define OBJECT_COMPONENT_SRB_OMNICAMERA_HPP_

#include "../../Dynamics/srb_simulation.hpp"

struct srbOmniCameraConf;

struct srbCompDistance
{
	srbCompDistance()
	{
		comp_tmp_data = nullptr;
	}

	bool operator()(srbObject *A, srbObject *B)
	{
		return ((b2Vec2) (comp_tmp_data->GetPosition() - A->GetPosition())).LengthSquared()
				< ((b2Vec2) (comp_tmp_data->GetPosition() - B->GetPosition())).LengthSquared();
	}

	srbObject *comp_tmp_data;
};

class srbOmniCamera: public srbComponent
{
public:
	srbOmniCamera(srbOmniCameraConf *conf, srbObject *object);
	~srbOmniCamera()
	{
	}

	void Update();

	void AddTarget(srbObject *object);

	b2Vec2 GetPosition() const;
	float GetAngle() const;

	static const int32 maxPartitionCount = 20;

protected:

	std::vector<srbObject*> targetList;
	int32 targetObjectCount;

	float range;
	int32 partitionCount;

	float centerAngle;
	float rotationAngle;

	srbCompDistance comp_dist;

	srbRandomTools *randomTools;
	bool isNoiseAdded;
	float angularNoiseLevel;
};

struct srbOmniCameraConf: srbComponentConf
{
	srbOmniCameraConf()
	{
		targetObjectCount = 0;
		range = 10.0f;
		partitionCount = 4;

		randomTools = nullptr;
		isNoiseAdded = false;
		angularNoiseLevel = 0.0f;
	}

	int32 targetObjectCount;
	float range;
	int32 partitionCount;

	srbRandomTools *randomTools;
	bool isNoiseAdded;
	float angularNoiseLevel;

	srbComponent* createFcn(srbComponentConf *conf, srbObject *object)
	{
		return new srbOmniCamera((srbOmniCameraConf*) conf, object);
	}
};

inline void srbOmniCamera::AddTarget(srbObject *object)
{
	targetList.push_back(object);
}

inline b2Vec2 srbOmniCamera::GetPosition() const
{
	return m_object->GetPosition();
}

inline float srbOmniCamera::GetAngle() const
{
	return m_object->GetAngle();
}

#endif /* OBJECT_COMPONENT_SRB_OMNICAMERA_HPP_ */
