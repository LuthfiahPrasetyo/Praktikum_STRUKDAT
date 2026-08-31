#include <iostream>
#include <fstream>
using namespace std;

string usn, pw;
struct Recipe {
	string name;
	string chef;
	string ingrednts;
	string step;
} R[100];

int total_data = 0;

void SaveFile(){
	ofstream file("recipe.txt");
	
	for (int i = 0; i < total_data; i++){
		file <<R[i].name <<endl;
		file <<R[i].chef <<endl;
		file <<R[i].ingrednts;
		file <<"###"<<endl;
		file <<R[i].step;
		file <<"###" <<endl;
	}
	file.close();
}

void LoadFile(){
	string line;
	ifstream file("recipe.txt");
	if (!file.is_open()){
		return;
	}
	
	while(getline(file, R[total_data].name)){
		getline(file, R[total_data].chef); 
		R[total_data].ingrednts = ""; 
		while(getline(file, line)){
			if(line == "###"){
				break;
			}
			R[total_data].ingrednts += line + "\n";
		}
		
		R[total_data].step = "";
		
		while(getline(file, line)){
			if(line == "###"){
				break;
			}
			
			R[total_data].step += line + "\n";
		}
		total_data++;
	}
	file.close();
}
		
void AddRecipe(){
	string line;
	
	cout <<endl<<endl<<"====================================="<<endl;
	cout <<"	    ADD NEW RECIPE	"<<endl;
	cout <<"====================================="<<endl;
	cin.ignore(1000, '\n');
	cout <<"Food Name	: ";
	getline(cin, R[total_data].name);
	cout <<"Chef Name	: ";
	getline(cin, R[total_data].chef);
	cout <<"Ingredients (type '###' at new line to finish): "<<endl;
	R[total_data].ingrednts = "";
	
	while(getline(cin, line)){
		if(line == "###"){
			break;
		}
		R[total_data].ingrednts += line + "\n";
	}
	cout <<"How to Make (type '###' at new line to finish): "<<endl;
	R[total_data].step = "";
	
	while(getline(cin, line)){
		if(line == "###"){
			break;
		}
		R[total_data].step += line + "\n";
	}
	
	total_data++;
	SaveFile();
	
	cout <<"Recipe added successfully."<<endl;
}

void SortRecipe(){
    Recipe temp;

    for(int i = 0; i < total_data - 1; i++){
        for(int j = 0; j < total_data - i - 1; j++){
            if(R[j].name > R[j+1].name){
                temp = R[j];
                R[j] = R[j+1];
                R[j+1] = temp;
            }
        }
    }
}

void ShowRecipe(){
	cout <<endl<<"====================================="<<endl;
	cout <<"	RECIPE LISTS (Sort A-Z)	"<<endl;
	cout <<"====================================="<<endl;
	if(total_data == 0){
		cout <<"No added recipe."<<endl;
		return;
	}
	
	SortRecipe();
	
	for(int i = 0; i < total_data; i++){
		cout <<i+1<<". Food	: "<<R[i].name<<endl;
		cout <<"   Chef	: "<<R[i].chef<<endl;
		cout <<"-------------------------------------"<<endl;
	}
}

void RecipeDetail(){
	SortRecipe();
	string search;
	cin.ignore(1000, '\n');
	int left = 0, mid, right = total_data - 1;
	bool found = false;
	
	cout <<endl<<"====================================="<<endl;
	cout <<"	    RECIPE DETAIL	"<<endl;
	cout <<"====================================="<<endl;
	cout <<"Food Name	: ";
	getline(cin, search);
	cout <<"-------------------------------------"<<endl;
	
	 
	while((!found)&&(left <= right)){
		mid = (left + right)/2;
		if(R[mid].name == search){
			cout <<endl;
			cout <<"Food Name   : " << R[mid].name << endl;
			cout <<"-------------------------------------"<<endl;
			cout <<"Chef        : " << R[mid].chef << endl;
			cout <<"-------------------------------------"<<endl;
			cout <<"Ingredients : " <<endl<< R[mid].ingrednts << endl;
			cout <<"-------------------------------------"<<endl;
			cout <<"How to Make : " <<endl<< R[mid].step << endl;
			cout <<"-------------------------------------"<<endl;

			found = true;
			break;
		}
		else if (R[mid].name > search){
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	if (!found){
		cout <<endl<<"Recipe not found."<<endl;
	}
}

void SearchRecipebyChef(){
    string search;
    bool found = false;
    int total_found = 0;
    cin.ignore(1000, '\n');
    
    cout <<endl<<"====================================="<<endl;
    cout <<"	SEARCH RECIPE BY CHEF "<<endl;
    cout <<"====================================="<<endl;
    cout <<"Chef Name	: ";
    getline(cin, search);
	
	cout <<endl<<"Recipe List by "<<search<<":"<<endl;
	cout <<"-------------------------------------"<<endl;
    for(int i = 0; i < total_data; i++){
        if(R[i].chef == search){
            cout << "Food Name	: " << R[i].name << endl;
            found = true;
            total_found++;
        }
    }
    if(!found){
        cout << endl << "Recipe not found." << endl;
    }
    cout <<"-------------------------------------"<<endl;
    cout <<"Total recipe found: "<< total_found<<endl;
}

void DeleteRecipe(){
	if(total_data == 0){
        return;
    }
	cout <<"====================================="<<endl;
	cout <<"	DELETE RECIPE"<<endl;
	cout <<"====================================="<<endl;
    for(int i = 0; i < total_data; i++){
		cout <<i+1<<". Food: "<<R[i].name<<" - "<<R[i].chef<<endl;
	}
    int delet;
    cout << endl << "Input recipe number to delete : ";
    cin >> delet;
    if(delet < 1 || delet > total_data){
        cout << "Invalid recipe number." << endl;
        return;
    }
    for(int i = delet - 1; i < total_data - 1; i++){
        R[i] = R[i + 1];
    }
    total_data--;
    SaveFile();

    cout << "Recipe deleted successfully." << endl;
}

int main(){
	
	LoadFile();
	
	int menu;
	int times = 3;
	
	while (times > 0){
		cout <<endl<<"====================================="<<endl;
		cout <<"		LOGIN	"<<endl;
		cout <<"====================================="<<endl;
		cout <<"Username	: ";
		cin >> usn;
		cout <<"Password	: ";
		cin >> pw;
		if (usn == "Fia" && pw == "127"){
			cout <<"Login successful."<<endl<<endl;
			do{
				cout <<endl<<"====================================="<<endl;
				cout <<"	   RECIPE MANAGER	"<<endl;
				cout <<"====================================="<<endl;
				cout <<"1. Add Recipe"<<endl;
				cout <<"2. Show Recipe Lists"<<endl;
				cout <<"3. Recipe Details (Search by Food Name)"<<endl;
				cout <<"4. Search Recipe (Search by Chef Name)"<<endl;
				cout <<"5. Delete Recipe"<<endl;
				cout <<"0. Exit"<<endl;
				cout <<"-------------------------------------"<<endl;
				cout <<"Choose menu (0-5)	: ";
				cin >> menu;
				
				switch(menu){
					case 1:
					AddRecipe();
					break;
					
					case 2:
					ShowRecipe();
					break;
					
					case 3:
					RecipeDetail();
					break;
					
					case 4:
					SearchRecipebyChef();
					break;
					
					case 5:
					DeleteRecipe();
					break;
					
					case 0:
					cout <<endl<<"Program ended."<<endl;
					break;
					
					default:
					cout <<endl<<"Invalid menu. Please enter a number between 0 - 5!"<<endl;
				}
			} while(menu != 0);
			return 0;
				
		}
		else{
			times--;
			if(times > 0){
				cout <<"Wrong username or password. Remaining attempts: "<<times<<endl<<endl;
			}
		}
	}
	cout <<"Too many attempts. Program terminated.";
}
