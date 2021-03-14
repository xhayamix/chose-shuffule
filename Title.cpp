#pragma once
# include "Title.hpp"

Title::Title(const InitData& init) : IScene(init){

}

void Title::update() {
    m_startTransition.update(m_startButton.mouseOver());
    m_exitTransition.update(m_exitButton.mouseOver());

    if (m_startButton.mouseOver() || m_exitButton.mouseOver()){
        Cursor::RequestStyle(CursorStyle::Hand);
    }

    if (m_startButton.leftClicked()){
        changeScene(State::Hindu);
    }

    if (m_exitButton.leftClicked()){
        changeScene(State::Farrow);
    }

}

void Title::draw() const {
    const String titleText = U"エキサイティングなシャッフル";
    const Vec2 center(Scene::Center().x, 120);
    FontAsset(U"Title")(titleText).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
    FontAsset(U"Title")(titleText).drawAt(center);

    m_startButton.draw(ColorF(1.0, m_startTransition.value())).drawFrame(2);
    m_exitButton.draw(ColorF(1.0, m_exitTransition.value())).drawFrame(2);

    FontAsset(U"Menu")(U"ヒンズーシャッフル").drawAt(m_startButton.center(), ColorF(0.25));
    FontAsset(U"Menu")(U"ファローシャッフル").drawAt(m_exitButton.center(), ColorF(0.25));

}