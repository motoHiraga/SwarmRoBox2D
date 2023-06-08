/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_evaluation_test.hpp"

void srbEvaluationTest::EvaluateInit()
{
	for (int32 i = 0; i < srbSimulationTest::item_count; i++)
	{
		init_item_position[i] =
				((srbSimulationTest*) m_simulation)->item[i]->GetPosition();
	}
}

void srbEvaluationTest::EvaluateStep()
{
	float distance_y = 0.0f;

	for (int32 i = 0; i < srbSimulationTest::item_count; i++)
	{
		distance_y = init_item_position[i].y
				- ((srbSimulationTest*) m_simulation)->item[i]->GetPosition().y;
		if (distance_y >= 30.0f)
		{
			fitness += 30.0f;
			((srbSimulationTest*) m_simulation)->item[i]->GetMainBody()->SetTransform(
					init_item_position[i], 0.0f);
		}
	}
}

void srbEvaluationTest::PreSolve(b2Contact *contact,
		const b2Manifold *oldManifold)
{
//	b2Body *bA = contact->GetFixtureA()->GetBody();
//	b2Body *bB = contact->GetFixtureB()->GetBody();
//
//	/// Get m_componentFixtureType of components.
//	uintptr_t cftA = contact->GetFixtureA()->GetUserData().pointer;
//	uintptr_t cftB = contact->GetFixtureB()->GetUserData().pointer;
//
//	if(bA != bB){
//		if((cftA==1 && cftB==2) || (cftA==2 && cftB==1)){
//			std::cout << "Collisions with m_componentFixtureType 1 and 2" << std::endl;
//		}
//	}
}

void srbEvaluationTest::EvaluateEnd()
{
	float distance_y = 0.0f;

	for (int32 i = 0; i < srbSimulationTest::item_count; i++)
	{
		distance_y = init_item_position[i].y
				- ((srbSimulationTest*) m_simulation)->item[i]->GetPosition().y;
		if (distance_y > 0.0f)
		{
			fitness += distance_y;
		}
	}

//	for (int32 i = 0; i < srbSimulationTest::item_count; i++)
//	{
//		distance_y = ((srbSimulationTest*) m_simulation)->item[i]->GetPosition().y - init_item_position[i].y;
//		if (distance_y > 0.0f)
//		{
//			fitness += distance_y;
//		}
//	}
}

