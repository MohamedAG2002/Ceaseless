#include "Score.h"
#include "File.h"

// Extern variable init
Score score;

Score::Score()
{
	m_score = 0;
	m_highScore = File::Instance().LoadData();
}

Score::~Score()
{}

void Score::Update()
{
	// Setting the high score
	if (m_score > m_highScore)
	{
		m_highScore = m_score;
		File::Instance().SaveData(m_highScore);
	}
}
