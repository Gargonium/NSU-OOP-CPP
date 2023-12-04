#include "Engine.h"
#include "UploadLvls.h"

int main() {

	bool isUpload = 0;
	if (isUpload) {
		startUpload();
	}
	else {
		Engine engine;
		engine.start();
	}


	return 0;
}