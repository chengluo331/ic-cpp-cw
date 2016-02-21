// COURSEWORK NUMBER: 2
// STUDENT NAME: JOSHUA DING

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){
	// Initialise all variables to be used throughout
	int singdata, i = 0, j = 4;
	vector<int> data, dummy1(4), dummy2(4), dummy3(4), dummy(2);

	// Save data from the input file to a vector
	ifstream fin("skyline.in");
	if (!fin.is_open()) {
		std::cout << "Error opening the file skyline.in." << endl;
		return -1;
	}
	while (fin >> singdata){
		data.push_back(singdata);
	}
	fin.close();

	// Modify data by comparing the top lines of
	// buildings and deleting the lowest intersection
	int datasize3 = data.size();
	while ((i < (datasize3-3)) && (j < (datasize3-3))){
		dummy1.clear();
		dummy2.clear();
		dummy3.clear();
		if ((data[i + 2] == data[j + 2]) && (data[i] == data[j]) && (i != j)){
			if (data[i + 1] < data[j + 1]){
				data.erase(data.begin() + i, data.begin() + i + 4);
				j = i + 4;
			}
			else {
				data.erase(data.begin() + j, data.begin() + j + 4);
				if (j < i){
					i = i - 4;
				}
			}
		}
		else if ((data[i + 2] >= data[j + 2] && data[i] >= data[j + 2] && i != j) || (data[i + 2] <= data[j] && data[i] <= data[j] && i != j)){
			if (j + 4 == i) {
				j = j + 8;
			}
			else{
				j = j + 4;
			}
		}
		else if (data[i] <= data[j] && data[i + 2] >= data[j] && data[i + 1] <= data[j + 1] && i != j){
			dummy1.clear();
			dummy2.clear();
			dummy3.clear();
			if (data[j + 2] >= data[i + 2]){
				dummy1.push_back(data[i]);
				dummy1.push_back(data[i + 1]);
				dummy1.push_back(data[j]);
				dummy1.push_back(data[i + 1]);
				dummy2.push_back(data[j]);
				dummy2.push_back(data[j + 1]);
				dummy2.push_back(data[j + 2]);
				dummy2.push_back(data[j + 1]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				data.insert(data.end(), dummy2.begin(), dummy2.begin() + 4);
				dummy1.clear();
				dummy2.clear();
			}
			else {
				dummy1.push_back(data[i]);
				dummy1.push_back(data[i + 1]);
				dummy1.push_back(data[j]);
				dummy1.push_back(data[i + 1]);
				dummy2.push_back(data[j]);
				dummy2.push_back(data[j + 1]);
				dummy2.push_back(data[j + 2]);
				dummy2.push_back(data[j + 1]);
				dummy3.push_back(data[j + 2]);
				dummy3.push_back(data[i + 1]);
				dummy3.push_back(data[i + 2]);
				dummy3.push_back(data[i + 1]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				data.insert(data.end(), dummy2.begin(), dummy2.begin() + 4);
				data.insert(data.end(), dummy3.begin(), dummy3.begin() + 4);
				dummy1.clear();
				dummy2.clear();
				dummy3.clear();
			}
			j = i + 4;
		}
		else if (data[j] <= data[i] && data[j + 2] >= data[i] && data[i + 1] <= data[j + 1] && i != j){
			dummy1.clear();
			dummy2.clear();
			dummy3.clear();
			if (data[j + 2] <= data[i + 2]){
				dummy1.push_back(data[j]);
				dummy1.push_back(data[j + 1]);
				dummy1.push_back(data[j + 2]);
				dummy1.push_back(data[j + 1]);
				dummy2.push_back(data[j + 2]);
				dummy2.push_back(data[i + 1]);
				dummy2.push_back(data[i + 2]);
				dummy2.push_back(data[i + 1]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				data.insert(data.end(), dummy2.begin(), dummy2.begin() + 4);
				dummy1.clear();
				dummy2.clear();
			}
			else {
				dummy1.push_back(data[j]);
				dummy1.push_back(data[j + 1]);
				dummy1.push_back(data[j + 2]);
				dummy1.push_back(data[j + 3]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				dummy1.clear();
			}
			j = i + 4;
		}
		else if (data[i] <= data[j] && data[i + 2] >= data[j] && data[i + 1] >= data[j + 1] && i != j){
			dummy1.clear();
			dummy2.clear();
			dummy3.clear();
			if (data[i + 2] <= data[j + 2]){
				dummy1.push_back(data[i]);
				dummy1.push_back(data[i + 1]);
				dummy1.push_back(data[i + 2]);
				dummy1.push_back(data[i + 1]);
				dummy2.push_back(data[i + 2]);
				dummy2.push_back(data[j + 1]);
				dummy2.push_back(data[j + 2]);
				dummy2.push_back(data[j + 1]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + (i + 4));
					data.erase(data.begin() + j, data.begin() + (j + 4));
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				data.insert(data.end(), dummy2.begin(), dummy2.begin() + 4);
				dummy1.clear();
				dummy2.clear();
			}
			else {
				dummy1.push_back(data[i]);
				dummy1.push_back(data[i + 1]);
				dummy1.push_back(data[i + 2]);
				dummy1.push_back(data[i + 3]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				dummy1.clear();
			}
			j = i + 4;
		}
		else if (data[j] <= data[i] && data[j + 2] >= data[i] && data[i + 1] >= data[j + 1] && i != j){
			dummy1.clear();
			dummy2.clear();
			dummy3.clear();
			if (data[i + 2] >= data[j + 2]){
				dummy1.push_back(data[j]);
				dummy1.push_back(data[j + 1]);
				dummy1.push_back(data[i]);
				dummy1.push_back(data[j + 1]);
				dummy2.push_back(data[i]);
				dummy2.push_back(data[i + 1]);
				dummy2.push_back(data[i + 2]);
				dummy2.push_back(data[i + 1]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				data.insert(data.end(), dummy2.begin(), dummy2.begin() + 4);
				dummy1.clear();
				dummy2.clear();
			}
			else {
				dummy1.push_back(data[j]);
				dummy1.push_back(data[j + 1]);
				dummy1.push_back(data[i]);
				dummy1.push_back(data[j + 1]);
				dummy2.push_back(data[i]);
				dummy2.push_back(data[i + 1]);
				dummy2.push_back(data[i + 2]);
				dummy2.push_back(data[i + 1]);
				dummy3.push_back(data[i + 2]);
				dummy3.push_back(data[j + 1]);
				dummy3.push_back(data[j + 2]);
				dummy3.push_back(data[j + 1]);
				if (i <= j){
					data.erase(data.begin() + j, data.begin() + j + 4);
					data.erase(data.begin() + i, data.begin() + i + 4);
				}
				else {
					data.erase(data.begin() + i, data.begin() + i + 4);
					data.erase(data.begin() + j, data.begin() + j + 4);
				}
				data.insert(data.end(), dummy1.begin(), dummy1.begin() + 4);
				data.insert(data.end(), dummy2.begin(), dummy2.begin() + 4);
				data.insert(data.end(), dummy3.begin(), dummy3.begin() + 4);
				dummy1.clear();
				dummy2.clear();
				dummy3.clear();
			}
			j = i + 4;
		}
		else {
			datasize3 = data.size();
			if (j >= (datasize3 - 4 - 2)){
				i = i + 4;
				j = i + 4;
			}
			else {
				j = j + 4;
			}
		}
		datasize3 = data.size();
		if (j + 3 >= datasize3){
			i = i + 4;
			j = 0;
		}
		datasize3 = data.size();
	}

	// Delete duplicated coordinate pairs (index increments of 4 and then 2)
	int datasize2 = data.size();
	for (j = 4; j > 1; j = j-2){
		for (i = 0; i < datasize2 - 3; i = i + j){
			if (data[i] == data[i+2] && data[i+1] == data[i+3]){
				data.erase (data.begin()+i,data.begin()+i+4);
				i = i-j;
			}
			datasize2 = data.size();
		}
	}
	
	// Sort data using insertion sort
	int datasize = data.size();
	for (j = 0; j < datasize; j = j + 2){ 
		i = 2;
		while (i < j + 2){
			if (data[j] < data[j - i] || (data[j] == data[j - i] && data[j + 1] < data[j - i + 1])){
				i = i + 2;
			}
			else{
				break;
			}
		}
		copy(data.begin() + j, data.begin() + (j + 2), dummy.begin());
		data.erase(data.begin() + j, data.begin() + j + 2);
		data.insert(data.begin() + (j - i + 2), dummy.begin(), dummy.begin() + 2);
		datasize = data.size();
	}

	// Second data modification, now by adding in necessary points
	// for bottoms of buildings and internal corners
	dummy.push_back(data[0]);
	dummy.push_back(0);
	data.insert(data.begin(), dummy.begin(), dummy.end());
	dummy.clear();
	dummy.push_back(data[data.size() - 2]);
	dummy.push_back(0);
	data.insert(data.end(), dummy.begin(), dummy.end());
	dummy.clear();
	for (unsigned int i = 0; i < data.size() - 5; i = i + 2){
		if (data[i + 1] != data[i + 3] && data[i + 1] == data[i + 5] && data[i + 2] == data[i + 4]){
			dummy.push_back(data[i + 4]);
			dummy.push_back(data[i + 5]);
			data.erase(data.begin() + i + 4, data.begin() + i + 6);
			data.insert(data.begin() + i + 2, dummy.begin(), dummy.end());
			dummy.clear();
		}
		else if (data[i] != data[i + 2] && data[i] != data[i + 4] && data[i + 1] != data[i + 3] && data[i + 1] != data[i + 5]){
			dummy.push_back(data[i]);
			dummy.push_back(0);
			data.insert(data.begin() + i + 2, dummy.begin(), dummy.end());
			dummy.clear();
			dummy.push_back(data[i + 4]);
			dummy.push_back(0);
			data.insert(data.begin() + i + 4, dummy.begin(), dummy.end());
			dummy.clear();
			i = i + 4;
		}
	}
	
	// Delete duplicated coordinate pairs (index increments of 2), middle coordinate pair of three consecutive pairs on a horizontal line, and redundant first four points
	for (unsigned int i = 0; i < data.size() - 3; i = i + 2){
		if (data[i + 1] == data[i + 3] && data[i] == data[i + 2]){
			data.erase(data.begin() + i, data.begin() + i + 2);
			i = i - 2;
		}
	}
	for (unsigned int i = 0; i < data.size() - 5; i = i + 2){
		if (data[i + 1] == data[i + 3] && data[i + 3] == data[i + 5]){
			if (((data[i] < data[i + 2]) && (data[i + 2] < data[i + 4])) || ((data[i + 4] < data[i + 2]) && (data[i + 2] < data[i]))){
				data.erase(data.begin() + i + 2, data.begin() + i + 4);
			}
			else if (((data[i + 2] < data[i + 4]) && (data[i + 4] < data[i])) || ((data[i] < data[i + 4]) && (data[i + 4] < data[i + 2]))){
				data.erase(data.begin() + i + 4, data.begin() + i + 6);
			}
			else {
				data.erase(data.begin() + i, data.begin() + i + 2);
			}
			i = i - 2;
		}
	}
	data.erase(data.begin(), data.begin() + 4);

	//Write data to output file
	ofstream fout("skyline.out");
	if (!fout.is_open()) {
		cout << "Error opening output file." << endl;
		return -1;
	}
	for (unsigned int i = 0; i < data.size(); i++){
		if (i % 2 == 0){
			fout << data[i] << " ";
		}
		else {
			fout << data[i] << endl;
		}
	}
	fout.close();

	return 0;
}