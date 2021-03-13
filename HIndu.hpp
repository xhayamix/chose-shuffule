#pragma once
#include "Common.hpp"

class Hindu : public MyApp::Scene
{
private:


public:

	Hindu(const InitData& init);
	void update() override;
	void draw() const override;

};