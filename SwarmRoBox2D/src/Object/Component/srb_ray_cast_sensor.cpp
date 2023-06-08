/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_ray_cast_sensor.hpp"

srbRayCastSensor::srbRayCastSensor(srbRayCastSensorConf *conf,
		srbObject *object) :
		srbComponent(conf, object)
{
	range = conf->range;
	offset = conf->offset;

	randomTools = conf->randomTools;
	noiseType = conf->noiseType;
	noiseLevel = conf->noiseLevel;
}

void srbRayCastSensor::Update()
{
	b2Vec2 start_point, end_point;
	b2Vec2 tmp;

	/// Calculate start point of the sensor.
	tmp = b2Vec2(offset * cosf(m_parentMainBody->GetAngle() + worldAngle),
			offset * sinf(m_parentMainBody->GetAngle() + worldAngle));
	start_point = m_parentMainBody->GetWorldPoint(worldPosition) + tmp;

	/// Calculate end point of the sensor.
	tmp = b2Vec2(range * cosf(m_parentMainBody->GetAngle() + worldAngle),
			range * sinf(m_parentMainBody->GetAngle() + worldAngle));
	end_point = start_point + tmp;

	srbRayCastClosestCallback callback;
	m_parentMainBody->GetWorld()->RayCast(&callback, start_point, end_point);

	/// If the sensor hits objects.
	if (callback.m_hit)
	{
		end_point = callback.m_point;
	}

	float sensorValue;
	sensorValue = 1.0f - (end_point - start_point).Length() / range;

	/// This is set to avoid the small sensor noise.
	if (sensorValue < 0.000001)
	{
		sensorValue = 0.0f;
	}

	if (noiseType != 0)
	{
		if (noiseLevel < 0.0f)
		{
			throw std::runtime_error(
					"Negative noise level in the ray cast sensor");
		}
		else if (noiseLevel > 0.0f)
		{
			if (noiseType == 1)
			{
				sensorValue += randomTools->GetUnif(-noiseLevel, noiseLevel);
			}
			else if (noiseType == 2)
			{
				sensorValue += noiseLevel * randomTools->GetGaussf();
			}
			else
			{
				throw std::runtime_error("Undefined noise type");
			}
		}
		sensorValue = std::clamp(sensorValue, 0.0f, 1.0f);
	}

	io_buffer->push_back(sensorValue);
}
