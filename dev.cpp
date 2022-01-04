#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
void download_mod_list() {
	//Create Mod Loading Utility
	ofstream batch;
    batch.open("download_mod_util.bat", ios::out);
    batch <<"@echo OFF"<<endl;
    batch <<"echo Downloading Mod List"<<endl;
    batch <<"powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://code.lumpology.com/blockstory_mod_list.txt', 'blockstory_mod_list.txt')\""<<endl;
    batch <<"echo done!"<<endl;
    batch <<"goto :eof"<<endl;
    batch.close();
	
	system("download_mod_util.bat");
	return;
}
void display_mod_list() {
	ifstream myReadFile;
	string output;
	bool display_condition = true;
	myReadFile.open("blockstory_mod_list.txt");
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			getline(myReadFile,output);
			if (display_condition==true) {
				cout<<output<<endl;
				display_condition = false;
				continue;
			}
			display_condition = true;
		}
	}
	myReadFile.close();
	return;
}
void download_mod_single(string sellected_mod,string &blockstorypath) {
	//find mod in downloaded list
	ifstream myReadFile;
	string output;
	bool display_condition = true;
	bool found_mod = false;
	myReadFile.open("blockstory_mod_list.txt");
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			getline(myReadFile,output);
			if (display_condition==true) {
				if (output==sellected_mod) {
					getline(myReadFile,output);
					sellected_mod = output;
					found_mod = true;
					break;
				}
				display_condition = false;
				continue;
			}
			display_condition = true;
		}
	}
	myReadFile.close();
	if (found_mod == false) {
		cout<<"Error: Mod Not Found"<<endl;
		return;
	}
	
	//parce path
	string spriter = sellected_mod;
	string delimiter = "/";

	size_t pos = 0;
	string tokens;
	while ((pos = spriter.find(delimiter)) != string::npos) {
		tokens = spriter.substr(0, pos);
		cout << tokens << endl;
		spriter.erase(0, pos + delimiter.length());
}
	cout<<"last["<<spriter<<"]"<<endl;
	//path path end
	
	
	//Create Mod Downloading Utility
	ofstream batch;
    batch.open("download_mod_util2.bat", ios::out);
    batch <<"@echo OFF"<<endl;
    batch <<"echo Downloading Mod List"<<endl;
    batch <<"powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://code.lumpology.com/BlockStoryMods/"<<sellected_mod<<"', '"<<spriter<<"')\""<<endl;
	batch <<"md "<<tokens<<endl;
	batch <<"move "<<"\""<<spriter<<"\" "<<"\""<<tokens<<"\\"<<spriter<<"\""<<endl;
    batch <<"echo done!"<<endl;
    batch <<"goto :eof"<<endl;
    batch.close();
	
	//run mod downloading util
	system("download_mod_util2.bat");
	
	//install mod
	batch.open("inject_mod_util.bat", ios::out);
	batch <<"@echo OFF"<<endl;
    batch <<"echo Injecting Mod"<<endl;
	batch <<"copy "<<"\""<<tokens<<"\\"<<spriter<<"\" "<<"\""<<blockstorypath<<"\\Block Story_Data\\Managed\\"<<spriter<<"\""<<endl;
	batch <<"echo done!"<<endl;
	batch <<"goto :eof"<<endl;
	batch.close();
	
	system("inject_mod_util.bat");
	
	cout<<"Mod Installed, Launch Block Story to start playing!"<<endl;
	cout<<"Please note we recomend backing up your worlds and or starting new ones when using mods"<<endl;
	return;
}
void backup_blockstory(string &path) {
	ofstream batch;
    batch.open("block_story_backup_util.bat", ios::out);
    batch <<"@echo OFF"<<endl;
    batch <<"echo Creating Block Story Restore Point."<<endl;
    batch <<"md backup"<<endl;
	batch <<"copy \""<<path<<"\\Block Story_Data\\Managed\\Blocksters.Terrain.dll\""<<" \"backup\\Blocksters.Terrain.dll\""<<endl;
	//batch <<"copy \""<<path<<"\\Block Story_Data\\Managed\\Blocksters.Logger.dll\""<<" \"backup\\Blocksters.Logger.dll\""<<endl;
	//batch <<"copy \""<<path<<"\\Block Story_Data\\Managed\\Blocksters.MathLib.dll\""<<" \"backup\\Blocksters.MathLib.dll\""<<endl;
	//batch <<"copy \""<<path<<"\\Block Story_Data\\Managed\\Blocksters.Performance.dll\""<<" \"backup\\Blocksters.Performance.dll\""<<endl;
    batch <<"echo Restore Point Created, type the 'restore' command to remove mods at any time"<<endl;
    batch <<"goto :eof"<<endl;
    batch.close();
	
	//run mod downloading util
	system("block_story_backup_util.bat");
	return;
}
void revert_blockstory_to_vanilla(string &path) {
	ofstream batch;
    batch.open("block_story_restore_util.bat", ios::out);
    batch <<"@echo OFF"<<endl;
    batch <<"echo Creating Block Story Restore Point."<<endl;
    batch <<"md backup"<<endl;
	batch <<"copy \"backup\\Blocksters.Terrain.dll\"";
	batch<<" \"";
	batch<<path;
	batch<<"\\Block Story_Data\\Managed\\Blocksters.Terrain.dll\""<<endl;
    batch <<"echo Block Story has restored from the backup"<<endl;
    batch <<"goto :eof"<<endl;
    batch.close();
	
	//run mod downloading util
	system("block_story_restore_util.bat");
	return;
}

int main(int argc, char *argv[]) {
	system("color 1f");
	string collected_path;
	string collect_index;
	
	download_mod_list();
	
	cout<<"Enter Path to Block Story.exe here (or type 'default'): ";
	
	getline(cin,collected_path);
	if (collected_path=="default") {
		collected_path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\BlockStory";
	}
	cout<<endl<<"Specify the mod you wish to install."<<endl<<"We recomend installing only one mod at a time due to few mods being compatible with one another."<<endl<<"Type 'list' to view all mods, type 'exit' to quit mod loader."<<endl;
	
	while (true) {
		cout<<">|";
		getline(cin,collect_index);
		
		if (collect_index=="list") {
			cout<<"Defined Commands: list, exit/stop, setup/first/backup, restore/revert, debug"<<endl;
			cout<<"Mod List:"<<endl;
			display_mod_list();
			continue;
		} else if (collect_index=="exit"||collect_index=="stop") {
			cout<<"Stopping Mod Loader"<<endl;
			break;
		} else if (collect_index=="restore"||collect_index=="revert") {
			revert_blockstory_to_vanilla(collected_path);
			continue;
		} else if (collect_index=="first"||collect_index=="setup"||collect_index=="backup") {
			backup_blockstory(collected_path);
			continue;
		} else if (collect_index=="debug") {
			cout<<"Path Registered: "<<collected_path<<endl;
			continue;
		} else {
			download_mod_single(collect_index, collected_path);
			cout<<"----------------"<<endl;
			continue;
		}
	}
	return 0;
}
