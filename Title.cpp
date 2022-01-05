#pragma once
# include "Title.hpp"

Title::Title(const InitData& init) : IScene(init){

}

void Title::update() {
    m_startTransition.update(m_startButton.mouseOver());
    m_exitTransition.update(m_exitButton.mouseOver());
    m_gameTransition.update(m_gameButton.mouseOver());
    m_plotTransition.update(m_plotButton.mouseOver());


    if (m_startButton.mouseOver() || m_exitButton.mouseOver() || m_gameButton.mouseOver() || m_plotButton.mouseOver()){
        Cursor::RequestStyle(CursorStyle::Hand);
    }

    if (m_startButton.leftClicked()){
        changeScene(State::Hindu, 0.3s);
    }

    if (m_exitButton.leftClicked()){
        changeScene(State::Farrow, 0.3s);
    }
    if (m_gameButton.leftClicked()) {
        changeScene(State::SetGame, 0.3s);
    }
    if (m_plotButton.leftClicked()) {
        changeScene(State::Plot, 0.3s);
    }
}

void Title::draw() const {
    const String titleText = U"Exciting Shuffling";
    const Vec2 center(Scene::Center().x, 120);
    FontAsset(U"Title")(titleText).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
    FontAsset(U"Title")(titleText).drawAt(center);

    m_startButton.draw(ColorF(1.0, m_startTransition.value())).drawFrame(2);
    m_exitButton.draw(ColorF(1.0, m_exitTransition.value())).drawFrame(2);
    m_gameButton.draw(ColorF(1.0, m_gameTransition.value())).drawFrame(2);
    m_plotButton.draw(ColorF(1.0, m_plotTransition.value())).drawFrame(2);

    FontAsset(U"Menu")(U"Hindu Shuffle").drawAt(m_startButton.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"Farrow Shuffle").drawAt(m_exitButton.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"Memory Game").drawAt(m_gameButton.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"Plot Shuffle").drawAt(m_plotButton.center(), ColorF(0.25));

}