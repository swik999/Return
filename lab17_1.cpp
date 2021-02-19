#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
	ifstream source(filename.c_str());
	string text;
	char format[] = "%[^:]:%f %f %f";
	char name[100];
	float a,b,c;
	while(getline(source,text)){
		sscanf(text.c_str(),format,name,&a,&b,&c);
		int score = a+b+c;
		names.push_back(name);
		scores.push_back(score);
		grades.push_back(score2grade(score));
	}

}

void getCommand(string &command,string &key){
	string x;
	cout << "Please input your command: ";
	getline(cin,x);
	int y = x.find_first_of(" ");
	command = x.substr(0,y);
	key = x.substr(y+1);

}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
	
	cout << "---------------------------------" << endl;
	for(unsigned int i=0;i<names.size();i++){
		if(toUpperStr(names[i]) == key){
			cout << names[i] << "'s score = " << scores[i] << endl;
			cout << names[i] << "'s grade = " << grades[i] << endl;
			cout << "---------------------------------" << endl;
			return ;
		}
	}
	cout << "Cannot found." << endl;
	cout << "---------------------------------" << endl;

}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
	cout << "---------------------------------" << endl;
	for(unsigned int i=0;i<grades.size();i++){
		if(grades[i] == key[0]){
			cout << names[i] << " (" << scores[i] << ")" << endl;
		}
	}
	cout << "---------------------------------" << endl;

}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
