#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;
void deallocation_nation(string **bye, int experiments);
void rewriting_history(string **temp, string**history, int experiments);
void rewriting_nums(int *sub_subs, int *numsubjects, int experiments);
void move_it(string **history, int experiments, int x, int y, int n, int m, int *numsubjects);
void removie(string *exp, int n, int m, int *numsubjects, int x, string **history);
//void deallocation_num(int *bye, int experiments);

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);
  if (input.fail()) {
  	output << "Error - input file does not exist" << endl; 
  }
  int subjects;
  int experiments = 0;
  int *numsubjects = NULL; //array 
  int *sub_subs = NULL; //used to store temporary 
  int flag = 0; //signals if command start has been used
  string **temp = NULL;
  string **history = NULL;
  string line;
  string curr;

  //for each experiment, you will need to keep track of the number of subjects; and for each subject, of their history

  //loop to read The Rani's logbook.
  while(getline(input, curr)) {
  	line = curr;
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "START") {
	    // Hint: This does not cover all errors yet.
		  if (flag > 0) {		//checking if we need to restart
		  	deallocation_nation(history, experiments); //cleaning the slate
		  	flag = 0;
		  }
		  double n;
		  ss >> n;
		  if (ss.fail() || (int)n != n) {
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameter should be an integer" << endl;
		  }
		  
		  else if (n < 0) {
		    output << "Error - incorrect command: " << line << endl;
		    output << "Number out of range" << endl;
		  }
		  else {
		  	subjects = (int)n;
			flag = 1; 		//signal for if start is called again
			experiments = 1;
			history = new string* [experiments];
			history[0] = new string[subjects];
			for (int i = 0; i < subjects; ++i) {
				history[0][i] = ""; 
			}
			numsubjects = new int[experiments];
			numsubjects[0] = subjects;
		  }
	  }
	  else if (curr == "ADD") {
	  	++experiments;			//incrementing # of experiments
	  	temp = new string* [experiments];  // using placeholder array
	  	for (int i = 0; i < experiments; ++i) {
	  		if (i != experiments-1) {
	  			temp[i] = history[i];
	  		}
	  		else {
	  			temp[i] = NULL;
	  		}
	  	} 
	  	rewriting_history(temp, history, experiments);	//sending temp to copy to history
	  	sub_subs = new int[experiments]; 
	  	for(int i = 0; i < experiments; i++) {
	  		if (i != (experiments -1)) {
	  			sub_subs[i] = numsubjects[i];
	  		}
	  		else {
	  			sub_subs[i] = 0;
	  		}
	  	}
	  	rewriting_nums(sub_subs, numsubjects, experiments);

	  }
	  else if (curr == "MOVE") {
	  	double x, y, n, m;
	  	ss >> x >> y >> n >> m;
	  	if (ss.fail()) {
	  		output << "Error - incorrect command: " << line << endl;
	  		if (&x == NULL || &y == NULL || &n == NULL || &m == NULL) {
	  			output << "Too few parameters" << endl;
	  		}
	  	}
	  	else if ((int)n != n || (int)m != m ||(int)x != x ||(int)y != y) {
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Parameter should be an integer" << endl;
	  	}
	  	else if (y > experiments) {
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Number out of range" << endl;
	  	}
	  	else if ((int)m > numsubjects[(int)x]){
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Invalid range of subjects" << endl;
	  	}
	  	else {
	  		move_it(history, experiments, (int)x, (int)y, (int)n, (int)m, numsubjects);
	  	}
	  }
	  else if (curr == "QUERY") {
	  	int x, n;
	  	ss >> x >> n;
	  	if (ss.fail()) {
	  		output << "Error - incorrect command: " << line << endl;
	  		if (&n == NULL || &x == NULL) {
	  			output << "Too few parameters" << endl;
	  		}
	  		else {
	  			output << "Parameter should be an integer" << endl;
	  		}
	  	}
	  	else if ((int)x > experiments){
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Number out of range" << endl;
	  	}
	  	else if (n > numsubjects[(int)n]) {
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Invalid range of subjects" << endl;
	  	}
	  	else {
	  		output << history[x][n] << endl; 
	  	}

	 }

	 else {
		  output << "Error - incorrect command: " << line << endl;
		  output << "Command does not exist" << endl;
	  }
	}
  return 0;
}

void rewriting_history(string **temp, string **history, int experiments) {//copying to new stuff to history
	delete history; //delete the array of pointers not pointers
	history = new string*[experiments];
	for (int i = 0; i < experiments; ++i) {
		history [i] = temp[i];
	}
	delete[] temp;
}
void rewriting_nums(int *sub_subs, int *numsubjects, int experiments) {//copying to new stuff to history
	delete[] numsubjects; //delete the array of pointers not pointers
	numsubjects = new int[experiments];
	for (int i = 0; i < experiments; ++i) {
		numsubjects [i] = sub_subs[i];
	}
	delete[] sub_subs; 
}
void deallocation_nation(string **bye, int experiments) { //deallocating & freeing memory
	for(int i = 0; i < experiments; ++i) {
		if (bye[i] != NULL) {
			delete[] bye[i];
		}
	}
	delete[] bye; 
}
void move_it(string **history, int experiments, int x, int y, int n, int m, int *numsubjects) {
	int ranger = m - n +1; 
	int u = n;
	string **tempo = new string*[numsubjects[y]+ranger];
	string *tem = history[x];
	for (int i = 0; i < numsubjects[y]; ++i){ //coping history into temp
		tempo[y][i] = history[y][i];
	}
	for (int j = numsubjects[y]-1; j < (numsubjects[y]+ ranger)-1; ++j) {
		tempo[y][0] = history[x][0] + "" + (char)(x+'0'); 	// adding newbies into temp
		++u;
	}
	rewriting_history(tempo, history, experiments);
	removie(tem, n, m, numsubjects, x, history);

	int *sub_subs = new int[experiments]; 
	for(int i = 0; i < experiments; i++) { //rewrites the numsubs for y
	 	if (i != (y) && i != x) {
  			sub_subs[i] = numsubjects[i];
	  	}
	  	else if (i = x) {
	  		sub_subs[i] = numsubjects[i] - ranger;
	  	}
  		else {
  			sub_subs[i] = numsubjects[i] + ranger;
  		}
  	}
	rewriting_nums(sub_subs, numsubjects, experiments);
}
void removie(string *exp, int n, int m, int *numsubjects, int x, string **history) {
	int rip = m - n; 
	string *tempe = new string[numsubjects[x]- rip];
	for (int i = 0; i < numsubjects[x]; ++i) {
		if (i ==n) {
			while (i < m){
				++i;
			}
		}
		else {
			tempe[i] = history[x][i];
		}
	} 
	delete[] history[x];
	history[x] = tempe;
}
