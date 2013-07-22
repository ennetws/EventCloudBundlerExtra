#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

std::vector<string> readNextLine(std::ifstream & in){
	std::string line;
	std::getline(in, line);
	istringstream iss( line );
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
				istream_iterator<string>(),
				back_inserter<vector<string> >(tokens));
	return tokens;
}

int main(int argc, char *argv[]){
	std::ifstream in(argv[1]);
	std::ofstream out("model.json");
	std::vector<string> tokens, t;
	int vcount = 0;
	while(!in.eof()){
		tokens = readNextLine(in);
		if(!tokens.size()) continue; 

		if(tokens[0].compare("element") == 0)
			vcount = atoi( tokens[2].c_str() );

		if(tokens[0].compare("end_header") == 0){
			out << "{ \"points\": [ \n";
			for(int i = 0; i < vcount; i++){
				t = readNextLine(in);
				out << "\t{";
				out << " \"x\": " << t[0] << ", \"y\":" << t[1] << ", \"z\":" << t[2] << ","; // Position
				out << " \"nx\": " << t[3] << ", \"ny\":" << t[4] << ", \"nz\":" << t[5] << ","; // Normal
				out << " \"r\": " << t[6] << ", \"g\":" << t[7] << ", \"b\":" << t[8]; // Color
				if(i < vcount-1) 
					out << "},\n";
				else
					out << "}\n"; // last one
			}
			out << "] }";
		}
	}
	out.close();
	return 0;
}

