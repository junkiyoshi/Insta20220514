#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 60 == 0) {

		this->random_seed = ofRandom(1000);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum());

	string word = "ULTRAMAN";
	ofColor color;

	ofSeedRandom(this->random_seed);

	ofFill();
	for (int z = -150; z <= 150; z += 150) {

		color.setHsb(ofRandom(255), 130, 255);
		ofSetColor(color);

		ofPushMatrix();
		ofTranslate(0, 0, z);

		vector<glm::vec2> location_list;
		vector<float> radius_list;

		while (location_list.size() < 120) {

			int x = ofRandom(-320, 320);
			int y = ofRandom(-320, 320);

			glm::vec2 location = glm::vec2(x, y);
			float radius = ofRandom(10, 120);

			if (location.x + radius > 320 || location.x - radius < -320 || location.y + radius > 320 || location.y - radius < -320) {

				continue;
			}

			bool flag = true;
			for (int i = 0; i < location_list.size(); i++) {

				if (glm::distance(location, location_list[i]) < radius_list[i] + radius) {

					flag = false;
					break;
				}
			}

			if (flag) {

				location_list.push_back(location);
				radius_list.push_back(radius);
			}
		}

		ofBeginShape();

		ofVertex(glm::vec2(-360, -360));
		ofVertex(glm::vec2(-360, 360));
		ofVertex(glm::vec2(360, 360));
		ofVertex(glm::vec2(360, -360));

		for (int i = 0; i < location_list.size(); i++) {

			int word_index = ofRandom(word.size());
			ofPath chara_path = this->font.getCharacterAsPoints(word[word_index], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();
			int rotate_deg = ofRandom(360);
			auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec2 location = vertex / 100 * radius_list[i] * 1.5;
					location -= glm::vec2(radius_list[i] * 0.75, -radius_list[i] * 0.75);
					location = glm::vec4(location, 0, 0) * rotation;
					ofVertex(location + location_list[i]);
				}
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}
	
	ofSeedRandom(this->random_seed);

	ofNoFill();
	ofSetColor(255);
	for (int z = -150; z <= 150; z += 150) {

		color.setHsb(ofRandom(255), 180, 255);

		ofPushMatrix();
		ofTranslate(0, 0, z);

		vector<glm::vec2> location_list;
		vector<float> radius_list;

		while (location_list.size() < 120) {

			int x = ofRandom(-320, 320);
			int y = ofRandom(-320, 320);

			glm::vec2 location = glm::vec2(x, y);
			float radius = ofRandom(10, 120);

			if (location.x + radius > 320 || location.x - radius < -320 || location.y + radius > 320 || location.y - radius < -320) {

				continue;
			}

			bool flag = true;
			for (int i = 0; i < location_list.size(); i++) {

				if (glm::distance(location, location_list[i]) < radius_list[i] + radius) {

					flag = false;
					break;
				}
			}

			if (flag) {

				location_list.push_back(location);
				radius_list.push_back(radius);
			}
		}

		ofBeginShape();

		ofVertex(glm::vec2(-360, -360));
		ofVertex(glm::vec2(-360, 360));
		ofVertex(glm::vec2(360, 360));
		ofVertex(glm::vec2(360, -360));

		for (int i = 0; i < location_list.size(); i++) {

			int word_index = ofRandom(word.size());
			ofPath chara_path = this->font.getCharacterAsPoints(word[word_index], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();
			int rotate_deg = ofRandom(360);
			auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec2 location = vertex / 100 * radius_list[i] * 1.5;
					location -= glm::vec2(radius_list[i] * 0.75, -radius_list[i] * 0.75);
					location = glm::vec4(location, 0, 0) * rotation;
					ofVertex(location + location_list[i]);
				}
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}
	

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}