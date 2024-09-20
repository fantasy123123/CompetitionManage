#include"SpeechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();

	this->createspeaker();

	this->loadrecord();
}

SpeechManager::~SpeechManager() {

}

void SpeechManager::showMenu() {
	cout << "----------------------" << endl;
	cout << "1.��ʼ�ݽ�����" << endl;
	cout << "2.�鿴�����¼" << endl;
	cout << "3.��ձ�����¼" << endl;
	cout << "0.�˳���������" << endl;
	cout << "----------------------" << endl;
	cout << endl;
}

void SpeechManager::exitsystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);

}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vv.clear();
	this->m.clear();

	this->index = 1;

	this->record.clear();
}


void SpeechManager::createspeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string mname = "ѡ��";
		mname += nameseed[i];

		Speaker sp;
		sp.name = mname;
		for (int j = 0; j < 2; j++) {
			sp.score[j] = 0;
		}

		this->v1.push_back(i + 10001);

		this->m.insert(pair<int, Speaker>(i + 10001, sp));
	}
}

void SpeechManager::start() {
	this->draw();
	this->contest();
	this->showscore();
	this->index++;
	this->draw();
	this->contest();
	this->showscore();
	this->savescore();
	cout << "���������ϣ�" << endl;

	this->initSpeech();

	this->createspeaker();

	this->loadrecord();

	system("pause");
	system("cls");
}

void SpeechManager::draw() {
	cout << "��" << this->index << "�ֳ������" << endl;

	

	if (this->index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++){
			cout << *it << "  ";
		}
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << "  ";
		}
	}

	cout<< endl << "--------------------------" << endl;

}

void SpeechManager::contest() {
	cout << "----------------------------��" << this->index << "�ֱ�����ʼ��------------------------------" << endl;
	multimap<double, int, greater<double>>groupscore;
	int num = 0;
	vector<int>src;
	src.resize(v1.size() + v2.size());
	if (this->index == 1)
	{
		src = v1;
	}
	else
	{
		src = v2;
	}

	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) 
	{
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->m[*it].score[this->index - 1] = avg;
		//cout << "��ţ�" << *it << " ������" << this->m[*it].name << "��ƽ���֣�" << this->m[*it].score[this->index - 1] << endl;

		groupscore.insert(pair<double, int>(avg, *it));

		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;

			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++) 
			{
				cout << "��ţ�" << it->second << " ������" << this->m[it->second].name << " �ĳɼ�:" << this->m[it->second].score[this->index - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end() && count < 3; it++, count++)
			{
				if (this->index == 1) 
				{
					v2.push_back(it->second);
				}
				else
				{
					vv.push_back(it->second);
				}
			}
            groupscore.clear();
			cout << endl;


		}
	}
	cout << "------------------------��" << this->index << "�ֱ������------------------------" << endl;
}


void SpeechManager::showscore() {
	cout << "------------------��" << this->index << "�ֽ���ѡ�֣�-------------" << endl;
	vector<int>v;
	v.resize(vv.size() + v2.size());
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = vv;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ��" << *it << " ����" << this->m[*it].name << " �ĵ÷֣�" << this->m[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManager::savescore() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
	{
		ofs << *it << "," << this->m[*it].score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�Ѽ�¼" << endl;
	this->fileempty = 0;
}



void SpeechManager::loadrecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileempty = 1;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileempty = 1;
		ifs.close();
		return;
	}


	this->fileempty = 0;
	ifs.putback(ch);

	string data;
	int mindex=1;
	while (ifs >> data)
	{
		//cout << data << endl;

		int pos1 = -1;
		
		int start = 0;
		vector<string>v;
		while (1)
		{
			
				pos1 = data.find(",", start);
				if (pos1 == -1)
				{
					break;
				}
				string temp1 = data.substr(start, pos1 - start);
				//cout << temp1 << ": ";
				v.push_back(temp1);
				start = pos1 + 1;
		}
		this->record.insert(make_pair(mindex, v));
		mindex++;
		v.clear();
	}
	
	ifs.close();

	//for (map<int, vector<string>>::iterator it = record.begin(); it != record.end(); it++)
	//{
	//cout << it->first << "�ھ����" << it->second[0] << " ����:" << it->second[1] << endl;
	//}

	
}


void SpeechManager::showrecord() {
	if (this->fileempty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
	}
	else 
	{
		for(map<int, vector<string>>::iterator it = record.begin(); it != record.end(); it++)
		{
			cout << "��" <<it->first<< "�죺" << endl
			    << "�ھ����" << it->second[0] << "�ķ�����" <<it->second[1] << endl
				<< "�Ǿ����" << it->second[2] << "�ķ�����" << it->second[3] << endl
				<< "�������" << it->second[4] << "�ķ�����" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}


void SpeechManager::clearrecord() {
	cout << "---------�Ƿ�ȷʵ��գ�-----------" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
	}

	this->initSpeech();

	this->createspeaker();

	this->loadrecord();

	cout << "��ճɹ���" << endl;

	system("pause");
	system("cls");
}