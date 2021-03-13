# include "InputNumberButton.hpp"

void InputNumberButton::draw(const ColorF& colorBase,const ColorF& colorFrame)const {
	m_rect.draw(colorBase).drawFrame(1, 0, colorFrame);
}

const RectF& InputNumberButton::rect() const
{
	return m_rect;
}

const String& InputNumberButton::label() const
{
	return m_label;
}