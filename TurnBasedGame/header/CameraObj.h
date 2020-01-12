#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

class CameraObj : public Object {
public:
	CameraObj();
	~CameraObj();

	//Updates camera and camBounds
	virtual void updateCamera();

	void setBounds(int *mapMaxX, int *mapMaxY, int *indexMaxX, int *indexMaxY);
	void setBounds(int *mapMaxX, int *mapMaxY, int *indexMaxX, int *indexMaxY, int width, int height);
	//Can use setBounds instead 
	void setCameraBounds(int width, int height);
	void setCamera(SDL_Rect*); //For Player
	void setCamera(); //For Non-Players

	//Object camera variables
	SDL_Rect *camera = NULL, *camBounds = NULL;
	int *mapMaxX, *mapMaxY, *indexMaxX, *indexMaxY;
	int maxCameraW, maxCameraH;

private:

};

#endif//CAMERA_H