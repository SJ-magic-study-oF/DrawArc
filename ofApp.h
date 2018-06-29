/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ARC{
private:
	int Resolution;
	int size;
	
	ofVbo Vbo;
	vector<ofVec3f> VboVerts;
	vector<ofFloatColor> VboColor;
	
	float DegToRad(float deg){
		return deg * 3.14159265358979 / 180;
	}
	
public:
	ARC(int _Resolution, const ofColor& color)
	: Resolution(_Resolution)
	, size(2 * Resolution + 2)
	{
		VboVerts.resize(size);
		VboColor.resize(size);
		
		Vbo.setVertexData(&VboVerts[0], VboVerts.size(), GL_DYNAMIC_DRAW);
		Vbo.setColorData(&VboColor[0], VboColor.size(), GL_DYNAMIC_DRAW);
		
		set_singleColor(color);
	}
	
	void set_singleColor(const ofColor& color){
		for(int i = 0; i < VboColor.size(); i++) { VboColor[i].set( double(color.r)/255, double(color.g)/255, double(color.b)/255, double(color.a)/255); }
	}
	
	void update(float r0, float r1, float theta_from, float theta_w){
		/********************
		********************/
		if(r1 <= r0) return;
		
		/********************
		********************/
		float theta_step = theta_w / (Resolution - 1);
		float theta = theta_from;
		for(int i = 0; i < Resolution; i++, theta += theta_step){
			VboVerts[2 * i    ].set( r0 * cos(DegToRad(theta)), r0 * sin(DegToRad(theta)) );
			VboVerts[2 * i + 1].set( r1 * cos(DegToRad(theta)), r1 * sin(DegToRad(theta)) );
		}
		
		/********************
		********************/
		Vbo.updateVertexData(&VboVerts[0], VboVerts.size());
		Vbo.updateColorData(&VboColor[0], VboColor.size());
	}
	
	void draw(int x, int y){
		ofPushMatrix();
		ofTranslate(x, y);
			Vbo.draw(GL_TRIANGLE_STRIP, 0, VboVerts.size()); // GL_POLYGON は、Fillの仕方が狙いと違った.
		ofPopMatrix();
	}
};


/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	enum{
		WINDOW_WIDTH = 1000,
		WINDOW_HEIGHT = 1000,
	};
	
	ARC Arc;
	
public:
	ofApp();
	
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
