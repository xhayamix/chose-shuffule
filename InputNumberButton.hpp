#pragma once
# include <Siv3D.hpp>
class InputNumberButton {
	private:

		RectF m_rect;

		String m_label;
		int value;
		Transition m_transition = Transition(0.0s, 0.5s);

	public:
		InputNumberButton() = default;
		InputNumberButton(const String& label,int value, const RectF& rect);
		void draw(const ColorF& colorBase = ColorF(0.9, 0.92, 0.94),
			const ColorF& colorPressed = ColorF(1.0),
			const ColorF& colorFrame = ColorF(0.9, 0.92, 0.94)) const;
		const RectF& rect() const;
		const String& label() const;
};