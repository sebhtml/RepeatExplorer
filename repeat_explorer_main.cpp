// author: Sébastien Boisvert
// 15 Jan. 2011
//

#include<iostream>
#include<sstream>
#include<fstream>
#include <vector>
#include <string.h>
#include<map>
#include<stdlib.h>
#include<string>
using namespace std;

void computeReverse(const char*in,char*out,bool*valid){

	*valid=true;

	int length=strlen(in);

	for(int j=0;j<length;j++){
		char symbol=in[j];
		char opposite='A';
		switch(symbol){
			case 'A':
				opposite='T';
				break;
			case 'T':
				opposite='A';
				break;
			case 'C':
				opposite='G';
				break;
			case 'G':
				opposite='C';
				break;
			default:
				valid=false;
				break;
		}
		if(!valid){
			break;
		}
		out[length-1-j]=opposite;
	}
	out[length]='\0';

}

int main(int argc,char**argv){
	if(argc!=4){
		cout<<"This program compute the redundancy of each k-mer in a genome."<<endl;
		cout<<endl;
	
		cout<<"Usage:"<<endl;
		cout<<endl;
		cout<<argv[0]<<" <genome> <k-mer size> <output>"<<endl;
		cout<<endl;
		cout<<"Example:"<<endl;
		cout<<endl;
		cout<<argv[0]<<" Ecoli.fasta 21 Ecoli.txt"<<endl;
		return 0;
	}
	string genome=argv[1];
	int k=atoi(argv[2]);
	string output=argv[3];
	map<string,int> redundancies;

	// load sequence
	ifstream f(genome.c_str());
	string oldName;
	ostringstream buffer;
	
	vector<string> names;
	vector<string> genomeSequences;

	while(!f.eof()){
		char line[10000];
		f.getline(line,10000);
		if(line[0]!='>'){
			buffer<<line;
		}else{
			if(oldName!=""){
				string sequence=buffer.str();
				genomeSequences.push_back(sequence);
				names.push_back(oldName);
				cout<<oldName<<" -> "<<sequence.length()<<endl;
			}
			int firstSpace=0;
			string lineStr=line;
			while(firstSpace<(int)lineStr.length()&&line[firstSpace]!=' '){
				firstSpace++;
			}

			oldName=lineStr.substr(1,firstSpace-1);
			buffer.str("");
		}
	}
	f.close();
	
	string sequence=buffer.str();
	genomeSequences.push_back(sequence);
	cout<<oldName<<" -> "<<sequence.length()<<endl;
	names.push_back(oldName);

	// count words
	for(int o=0;o<(int)genomeSequences.size();o++){
		string genomeSequence=genomeSequences[o];
		for(int i=0;i<(int)genomeSequence.length()-k+1;i++){
			if(i%100000==0){
				cout<<"Analyzing redundancy "<<i+1<<"/"<<genomeSequence.length()<<endl;
			}
			string word=genomeSequence.substr(i,k);
			bool valid=false;
			char reverseWord[10000];
			computeReverse(word.c_str(),reverseWord,&valid);

			if(valid){

				string theReverse=reverseWord;
				string lower=word;
				if(theReverse < lower)
					lower = theReverse;

				redundancies[lower]++;
			}
		}
	}


	ofstream fOut(output.c_str());
	for(int o=0;o<(int)genomeSequences.size();o++){
		string genomeSequence=genomeSequences[o];
		string handle=names[o];
		for(int i=0;i<(int)genomeSequence.length()-k+1;i++){
			if(i%100000==0){
				cout<<"Writing "<<output<<" "<<i+1<<"/"<<genomeSequence.length()<<endl;
			}
	
			string word=genomeSequence.substr(i,k);

			bool valid;
			char reverseWord[10000];
			computeReverse(word.c_str(),reverseWord,&valid);

			string theReverse=reverseWord;
			string lower=word;
			if(theReverse < lower)
				lower = theReverse;

			int redundancy=0;
			if(redundancies.count(lower)>0){
				redundancy=redundancies[lower];
			}

			fOut<<handle<<"\t"<<i+1<<"\t"<<word<<"\t"<<theReverse<<"\t"<<redundancy<<endl;
		}
	
		cout<<"Writing "<<output<<" "<<genomeSequence.length()<<"/"<<genomeSequence.length()<<endl;
	}

	fOut.close();
	return EXIT_SUCCESS;
}
