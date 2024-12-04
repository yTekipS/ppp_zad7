#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Dane
{
	vector <float> czujniki;
	string data;
	string godzina;
};

vector<float> SplitToSensors(string line) {
	string tempo = "";
	
	vector<float> Sensors;

	for (int i = 0; i < line.length(); i++) {

		if (line[i] == ',') {
			tempo += '.';
			continue;
		}
		if (line[i] == ';' || i == line.length()-1) { 
			Sensors.emplace_back(stof(tempo)); 
			tempo = ""; 
			continue;
		}
		tempo += line[i];
	}

	return Sensors;
}

int main() {

	vector <Dane> Lines;
	Lines.reserve(205);
	ifstream file("pomiary.txt");
	string line;

	Dane dane;
	if (file) {
		getline(file, line);
		//------------------------------------------------------- Odczyt z pliku oraz zapisz to wektora --------------------------------------------------------------------------------------------------------------
		while (!file.eof()) {
			getline(file, line);
			if (line != "") {
				dane.data = line.substr(0, 10);
				dane.godzina = line.substr(12, 5);
				string temp="";
				for (int i = 17; i < line.length(); i++) {
					temp += line[i];
				}
				//cout << temp << endl;
				dane.czujniki = SplitToSensors(temp);
			}
			Lines.emplace_back(dane);
		}

		//------------------------------------------------------- Srednia poszczegolny dni ---------------------------------------------------------------------------------------------------------------------------------
		vector <float> avrageOfDay;
		float avrage=0;
		for (int i = 0; i < Lines.size(); i++) {
			for (int j = 0; j < Lines[i].czujniki.size(); j++) {
				avrage += Lines[i].czujniki[j];
			}
			
			avrage /= Lines[i].czujniki.size();
			avrageOfDay.emplace_back(avrage);
		}

		for (auto& avr : avrageOfDay) {
			cout << avr << endl;
		}

		cout << "\n\n\n";

		//--------------------------------------------------------- Srednia z poszczegolnych czyjnikow -------------------------------------------------------------------------------------------------------------------------------------------

		vector <float> avrageOfSensor;
		float avrageTemporary = 0;
		
		for (int j = 0; j < Lines[0].czujniki.size(); j++)
		{
			avrageTemporary += Lines[0].czujniki[j];
			
			avrageOfSensor.emplace_back(avrageTemporary);
		}
		 
		for (auto& item : Lines) {

			for (int i = 0; i < item.czujniki.size();i++) {

				avrageOfSensor[i] += item.czujniki[i];
			}

		}
		cout << "\n\n";
		for (auto& item : avrageOfSensor) {
			item/=Lines.size();
			cout << item << endl;
		}
	}
	else cout << "eeeeee";
}