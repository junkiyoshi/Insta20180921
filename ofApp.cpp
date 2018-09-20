#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->number_of_targets = 80;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->targets1.push_back(glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
		this->targets2.push_back(glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));

		glm::vec3  color = glm::vec3(1.0, 1.0, 1.0);
		int color_type = i % 6;
		switch (color_type) {
		case 0:
			color = glm::vec4(1.0, 0.0, 0.0, 0.0);
			break;
		case 1:
			color = glm::vec4(0.0, 1.0, 0.0, 0.0);
			break;
		case 2:
			color = glm::vec4(0.0, 0.0, 1.0, 0.0);
			break;
		case 3:
			color = glm::vec4(1.0, 1.0, 0.0, 0.0);
			break;
		case 4:
			color = glm::vec4(0.0, 1.0, 1.0, 0.0);
			break;
		case 5:
			color = glm::vec4(1.0, 0.0, 1.0, 0.0);
			break;
		}
		this->colors.push_back(color);
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	float radius = 300;
	for (int i = 0; i < this->number_of_targets; i++) {

		int deg1 = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.001), 0, 1, -360, 360);
		this->targets1[i] = glm::vec2(radius * cos(deg1 * DEG_TO_RAD) + ofGetWidth() * 0.5 , radius * sin(deg1 * DEG_TO_RAD) + ofGetHeight() * 0.5);

		int deg2 = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.001), 0, 1, -360, 360);
		this->targets2[i] = glm::vec2(radius * cos(deg2 * DEG_TO_RAD) + ofGetWidth() * 0.5, radius * sin(deg2 * DEG_TO_RAD) + ofGetHeight() * 0.5);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets1", &this->targets1[0].x, this->number_of_targets);
	this->shader.setUniform2fv("targets2", &this->targets2[0].x, this->number_of_targets);
	this->shader.setUniform3fv("colors", &this->colors[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}