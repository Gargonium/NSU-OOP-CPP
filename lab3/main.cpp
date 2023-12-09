#include "Engine.h"
#include "UploadLvls.h"

/*
Structure of Game:
VFP:
	files:
		music:
			*.wav
		levels:
			*.mp
		leaderboard.ld
	out:
		build:
			game.exe
*/

int main() {

	bool isUpload = 0;
	
	if (isUpload) {
		startUpload();
	}
	else {
		Engine engine;
		engine.Menu();
	}

	return 0;
}
