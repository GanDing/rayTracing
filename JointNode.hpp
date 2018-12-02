// Fall 2018

#pragma once

#include "SceneNode.hpp"

class JointNode : public SceneNode {
public:
	JointNode(const std::string & name);
	virtual ~JointNode();

	void set_joint_x(float min, float init, float max);
	void set_joint_y(float min, float init, float max);

	struct JointRange {
		float min, init, max;
	};


	JointRange m_joint_x, m_joint_y;
};
