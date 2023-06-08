/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef EVALUATIONMANAGER_SRB_EVALUATION_TEST_HPP_
#define EVALUATIONMANAGER_SRB_EVALUATION_TEST_HPP_

#include "../Simulation/srb_simulation_test.hpp"

class srbEvaluationTest: public srbManager
{
public:

	srbEvaluationTest()
	{
		fitness = 0.0f;
	}

	/// Destroy the evaluation manager.
	virtual ~srbEvaluationTest()
	{
	}

	void EvaluateInit();
	void EvaluateStep();
	void EvaluateEnd();

	const void* EvaluationReport() const;

	void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);

protected:

	float fitness;

	b2Vec2 init_item_position[srbSimulationTest::item_count];
};

inline const void* srbEvaluationTest::EvaluationReport() const
{
	return &fitness;
}

#endif /* EVALUATIONMANAGER_SRB_EVALUATION_TEST_HPP_ */
