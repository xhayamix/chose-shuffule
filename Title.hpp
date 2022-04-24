#pragma once
#include "Common.hpp"

class Title : public MyApp::Scene {
private:

    Rect m_gameButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
    Transition m_gameTransition = Transition(0.4s, 0.2s);
    Rect m_agentButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
    Transition m_agentTransition = Transition(0.4s, 0.2s);

public:

    Title(const InitData& init);
    void update() override;
    void draw() const override;

};