/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef DYNAMICS_SRB_COMMON_HPP_
#define DYNAMICS_SRB_COMMON_HPP_

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "box2d/box2d.h"

#define RAND_LIMIT 32767

/// Default random tools in Box2D Testbed
/// Random number in range [-1,1]
inline float srbRandomFloat()
{
	float r = (float) (rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = 2.0f * r - 1.0f;
	return r;
}

/// Default random tools in Box2D Testbed
/// Random floating point number in range [lo, hi]
inline float srbRandomFloat(float lo, float hi)
{
	float r = (float) (rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}

/// Class to use random values using Mersenne Twister
class srbRandomTools
{
public:
	srbRandomTools()
	{
		random_seed = time(nullptr);
	}

	~srbRandomTools()
	{
	}

	void SetSeed(int32 seed);
	int32 GetSeed() const;
	void Refresh();
	float GetRandf();
	float GetGaussf();
	float GetGaussf(float mean, float std);
	int32 GetUniInt(int32 min, int32 max);
	float GetUnif(float min, float max);

protected:
	int32 random_seed;
	std::mt19937 mt;
};

inline void srbRandomTools::SetSeed(int32 seed)
{
	random_seed = seed;
}

inline int32 srbRandomTools::GetSeed() const
{
	return random_seed;
}

inline void srbRandomTools::Refresh()
{
	mt.seed(random_seed);
}

inline float srbRandomTools::GetRandf()
{
	std::uniform_real_distribution<float> randf(0.0f, 1.0f);
	return randf(mt);
}

inline float srbRandomTools::GetGaussf()
{
	std::normal_distribution<float> distf(0.0f, 1.0f);
	return distf(mt);
}

inline float srbRandomTools::GetGaussf(float mean, float std)
{
	std::normal_distribution<float> distf(mean, std);
	return distf(mt);
}

inline int32 srbRandomTools::GetUniInt(int32 min, int32 max)
{
	std::uniform_int_distribution<int32> unirand(min, max);
	return unirand(mt);
}

inline float srbRandomTools::GetUnif(float min, float max)
{
	std::uniform_real_distribution<float> unirandf(min, max);
	return unirandf(mt);
}

#endif /* DYNAMICS_SRB_COMMON_HPP_ */
