#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<fstream>
class SpeechManager {
public:
	SpeechManager();

	~SpeechManager();

	void showMenu();

	void exitsystem();


	vector<int>v1;

	vector<int>v2;

	vector<int>vv;

	map<int, Speaker>m;

	int index;

	void initSpeech();

	void createspeaker();

	void start();

	void draw();

	void contest();

	void showscore();

	void savescore();

	void loadrecord();
	bool fileempty;
	map<int, vector<string>>record;

	void showrecord();

	void clearrecord();
};