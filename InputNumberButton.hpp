#pragma once
# include <Siv3D.hpp>
class InputNumberButton {
	private:

		RectF m_rect;

		String m_label;
		Transition m_transition = Transition(0.0s, 0.5s);

	public:
		InputNumberButton() = default;
		InputNumberButton(const String& label, const RectF& rect)
			: m_rect(rect)
			, m_label(label) {};
		void draw(const ColorF& colorBase = ColorF(0.9, 0.92, 0.94),
			const ColorF& colorFrame = ColorF(0.9, 0.92, 0.94)) const;
		const RectF& rect() const;
		const String& label() const;
};