#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int subjects;
  int experiments;
  int *numsubjects;
  int flag = 0; //signals if command start has been used
  string **temp;
  string **history;
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
		  	deallocation_nation(history); //cleaning the slate
		  }
		  int n;
		  ss >> n;
		  if (ss.fail()) {
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameter should be an integer" << endl;
		  }
		  else if (n < 0) {
		    output << "Error - incorrect command: " << line << endl;
		    output << "Number out of range" << endl;
		  }
		  else {
			subjects = n; 
			flag = 1; 		//signal for if start is called again
			experiments = 1;
			history = new string* [experiments];
			for (int i = 0; i < experiments; ++i) {
				history[i] = new string[subjects];
			}
		  }
	  }
	  else if (curr == "ADD") {
	  	++experiments;			//incrementing # of experiments
	  	temp = new string* [experiments];  // using placeholder array
	  	for (int i = 0; i < experients-1; ++i) {
	  		temp[i] = history[i];
	  	} 
	  	temp[i] = NULL;
	  	rewriting_history(temp);	//sending temp to copy to history
	  }
	  else if (curr == "MOVE") {
	  	int x, y, n, m;
	  	ss >> x >> y >> n >> m;
	  	if (ss.fail()) {
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Too few parameters" << endl;
	  	} 
	  	else if (y > experiments || m > subjects) {
	  		output << "Error - incorrect command: " << line << endl;
	  		output << "Number out of range" << endl;
	  	}
	  	else if ()
	  }
	  else if (curr == "QUERY") {
	  	int x, n;
	  	ss >> x >> n;
	  	if (ss.fail()) {
	  		output << "Error - incorrect command: " << line << endl;
	  	}
	  	else if ()
	  	}

	  }
	  else {
		  output << "Error - incorrect command: " << line << endl;
		  output << "Command does not exist" << endl;
	  }
  }
  return 0;
}
//void transition(string **t) {
//	rewriting_history(t); 
//	deallocation_nation(t);  
//}
void rewriting_history(string **temp) {//copying to new stuff to history
	delete history; //delete the array of pointers not pointers
	history = new string[experiments];
	for (int i = 0; i < experiments; ++i) {
		history [i] = temp[i];
	}
	deallocation_nation(temp);
}
void deallocation_nation(string **bye) { //deallocating & freeing memory
	for(int i = 0; i < experiments; ++i) {
		delete[] bye[i];
	}
	delete bye; 
}

