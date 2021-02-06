#include"monsterstrike.h"

bool exitFlag = false;

int main() {

	MonsterStrike monsterStrike;

	while (exitFlag) {
		monsterStrike.proceedStory();
		monsterStrike.saveData();
	}
	return 0;
}