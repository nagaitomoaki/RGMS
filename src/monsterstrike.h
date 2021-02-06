#pragma once
class MonsterStrike{
public:
	MonsterStrike();
	~MonsterStrike();
	void proceedStory();
	void saveData();
private:
	unsigned char state;
	void battle();
	void clickMessage();
	void matchingImage();
	void getState();
};