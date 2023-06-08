/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_omnicamera.hpp"

srbOmniCamera::srbOmniCamera(srbOmniCameraConf *conf, srbObject *object) :
		srbComponent(conf, object)
{
	targetObjectCount = conf->targetObjectCount;
	range = conf->range;
	partitionCount = conf->partitionCount;

	/// Center angle of the partition.
	centerAngle = 2.0f * b2_pi / partitionCount;

	/// Rotate partition in the range [-b2_pi, b2_pi].
	rotationAngle = -b2_pi / partitionCount;

	targetList.reserve(100);

	randomTools = conf->randomTools;
	isNoiseAdded = conf->isNoiseAdded;
	angularNoiseLevel = conf->angularNoiseLevel;
}

void srbOmniCamera::Update()
{
	float sensorValues[maxPartitionCount] = { };

	comp_dist.comp_tmp_data = m_object;
	std::partial_sort(targetList.begin(),
			targetList.begin() + targetObjectCount, targetList.end(),
			comp_dist);

	for (int32 i = 0; i < targetObjectCount; i++)
	{
		if (!(m_object->GetPosition() == targetList[i]->GetPosition()))
		{
			b2Vec2 tmp = targetList[i]->GetPosition() - m_object->GetPosition();
			float distance = tmp.Length();
			b2Vec2 localVec = m_object->GetMainBody()->GetLocalVector(tmp);

			float cosLocal = localVec.x / localVec.Length();
			float sinLocal = localVec.y / localVec.Length();

			float relativeAngle = atan2f(sinLocal, cosLocal);

			if (isNoiseAdded)
			{
				relativeAngle += randomTools->GetUnif(-angularNoiseLevel,
						angularNoiseLevel);
				if (relativeAngle > b2_pi)
				{
					relativeAngle -= b2_pi;
				}
				else if (relativeAngle < -b2_pi)
				{
					relativeAngle += b2_pi;
				}
			}

			if (distance < range)
			{
				if (rotationAngle > 0)
				{
					if ((relativeAngle > -b2_pi)
							&& relativeAngle <= -b2_pi + rotationAngle)
					{
						relativeAngle += 2.0f * b2_pi;
					}
				}
				if (rotationAngle < 0)
				{
					if (relativeAngle >= b2_pi + rotationAngle
							&& (relativeAngle < b2_pi))
					{
						relativeAngle -= 2.0f * b2_pi;
					}
				}
				for (int32 j = 0; j < partitionCount; j++)
				{
					float startAngle = j * centerAngle + rotationAngle - b2_pi;
					float endAngle = startAngle + centerAngle;
					if (relativeAngle >= startAngle && relativeAngle < endAngle)
					{
						sensorValues[j] = 1.0f;
					}
				}
			}
		}
	}

	for (int32 i = 0; i < partitionCount; i++)
	{
		io_buffer->push_back(sensorValues[i]);
	}
}
