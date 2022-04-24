#pragma once
# include "Title.hpp"

Title::Title(const InitData& init) : IScene(init) {

}

void Title::update() {

    m_gameTransition.update(m_gameButton.mouseOver());
    m_agentTransition.update(m_agentButton.mouseOver());


    if (m_gameButton.mouseOver() || m_agentButton.mouseOver()) {
        Cursor::RequestStyle(CursorStyle::Hand);
    }

    if (m_gameButton.leftClicked()) {
        changeScene(State::SetGame, 0.3s);
    }
    if (m_agentButton.leftClicked()) {
        changeScene(State::AgentSetGame, 0.3s);
    }
}

void Title::draw() const {
    const String titleText = U"Exciting Shuffling";
    const Vec2 center(Scene::Center().x, 120);
    FontAsset(U"Title")(titleText).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
    FontAsset(U"Title")(titleText).drawAt(center);

    m_gameButton.draw(ColorF(1.0, m_gameTransition.value())).drawFrame(2);
    m_agentButton.draw(ColorF(1.0, m_agentTransition.value())).drawFrame(2);

    FontAsset(U"Menu")(U"Memory Game").drawAt(m_gameButton.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"Agent Memory Game").drawAt(m_agentButton.center(), ColorF(0.25));

}