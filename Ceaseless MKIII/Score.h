#pragma once

class Score
{
public:
	Score();
	~Score();

private:
	unsigned int m_score, m_highScore;

public:
	void Update();

	/* Getters and setters */
	// Score
	void SetScore(const unsigned int& score) { m_score = score; }
	const unsigned int& GetScore() const { return m_score; }

	// High score
	void SetHighScore(const unsigned int& highScore) { m_highScore = highScore; }
	const unsigned int& GetHighScore() const { return m_highScore; }
};
extern Score score;