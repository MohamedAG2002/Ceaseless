#include "Ui.h"
#include "Assets.h"

// Consts
const float MAX_VALUE = 100.0f;

ui::Button::Button(const Vector2& pos, const Vector2& size, const std::string&& buttonText, const Color& buttonColor, const Color& textColor)
	:m_position(pos), m_size(size), m_text(buttonText), m_buttonColor(buttonColor), m_textColor(textColor)
{
	m_bounds.width = size.x;
	m_bounds.height = size.y;
	m_bounds.x = pos.x - size.x / 2.0f;
	m_bounds.y = pos.y - size.y / 2.0f;

	m_currentState = ACTIVE;

	m_isActive = true;
}

ui::Button::~Button()
{}

void ui::Button::Update()
{
	// Changing the state
	if (m_isActive && OnButtonClick()) m_currentState = CLICKED;
	else if (!OnButtonClick() && OnButtonHover()) m_currentState = HOVER;
	else if (!m_isActive) m_currentState = DISABLED;
	else m_currentState = ACTIVE;

	// Setting the color depending on the state
	switch (m_currentState)
	{
	case ACTIVE: m_buttonColor.a = 255;
		break;
	case CLICKED: m_buttonColor.a = 55;
		break;
	case HOVER: m_buttonColor.a = 200;
		break;
	case DISABLED: m_buttonColor.a = 25;
		break;
	}
}

void ui::Button::Render()
{
	// Rendering the button
	DrawRectangleRec(m_bounds, m_buttonColor);
	DrawRectangleLinesEx(m_bounds, 0.7f, BLACK);

	// Rendering the text
	DrawTextPro(GetFontDefault(), m_text.c_str(), m_position, Vector2{ MeasureText(m_text.c_str(), 20) / 2.0f - 1.0f, 10.0f}, 0.0f, 20.0f, 1.0f, m_textColor);
}

bool ui::Button::OnButtonClick()
{
	if (CheckCollisionPointRec(GetMousePosition(), m_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		PlaySound(Assets::Instance().GetSound("Click"));
		return true;
	}

	return false;
}

bool ui::Button::OnButtonHover()
{
	if (CheckCollisionPointRec(GetMousePosition(), m_bounds))
		return true;

	return false;
}