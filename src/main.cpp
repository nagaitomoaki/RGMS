/*screen size 540x960*/
#include"monsterstrike.h"

bool isExitFlag = true;

int main() {

	while (isExitFlag) {
		MonsterStrike monsterStrike;
		monsterStrike.proceedStory();
		//monsterStrike.saveData();
	}
	return 0;
}