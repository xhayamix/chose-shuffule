# include "InputNumberButton.hpp"

InputNumberButton::InputNumberButton(const String& label, int value, const RectF& rect)
	: m_rect(rect)
	, value(value)
	, m_label(label) {};

void InputNumberButton::draw(const ColorF& colorBase, const ColorF& colorPressed, const ColorF& colorFrame)const {
	const ColorF color = colorBase.lerp(colorPressed, m_transition.easeIn());

	m_rect.draw(color).drawFrame(1, 0, colorFrame);

	if (m_rect.mouseOver()){
		Cursor::RequestStyle(CursorStyle::Hand);
	}
}

const RectF& InputNumberButton::rect() const{
	return m_rect;
}

const String& InputNumberButton::label() const{
	return m_label;
}

void InputNumberButton::update(){
	m_transition.update(m_rect.leftPressed());
}
