#pragma once

#include <raylib.h>

#include <string>

namespace ui // Begin of ui
{
	// Button states
	enum ButtonStates
	{
		ACTIVE = 0,
		CLICKED,
		HOVER,
		DISABLED
	};

	// Button class
	class Button
	{
	private:
		Vector2 m_position, m_size;
		std::string m_text;
		Color m_buttonColor, m_textColor;
		Rectangle m_bounds;
		bool m_isActive;
		ButtonStates m_currentState;

	public:
		Button(const Vector2& pos, const Vector2& size, const std::string&& buttonText, const Color& buttonColor, const Color& textColor);
		~Button();

	public:
		void Update();
		void Render();
		bool OnButtonClick();
		bool OnButtonHover();

	public:
		/* Getters and setters */
		// Position
		void SetPos(const Vector2& pos) { m_position = pos; }
		const Vector2& GetPos() const { return m_position; }

		// Size 
		void SetSize(const Vector2& size) { m_size = size; }
		const Vector2& GetSize() const { return m_size; }

		// Text
		void SetText(const std::string& text) { m_text = text; }
		const std::string& GetText() const { return m_text; }

		// Button color
		void SetButtonColor(const Color& buttonColor) { m_buttonColor = buttonColor; }
		const Color& GetButtonColor() const { return m_buttonColor; }

		// Text color
		void SetTextColor(const Color& textColor) { m_textColor = textColor; }
		const Color& GetTextColor() const { return m_textColor; }

		// Bounds
		const Rectangle& GetBounds() const { return m_bounds; }

		// Active state
		void SetActive(const bool& active) { m_isActive = active; }
		const bool& IsActive() const { return m_isActive; }

		// Button state
		const ButtonStates& GetState() const { return m_currentState; }
	};

} // End of ui