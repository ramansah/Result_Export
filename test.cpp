#include<iostream>
#include<fstream>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

const int m_disp[] = {0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1};
const int SUB = 11;
const int GT_MAX = 700;

const int MAX_SUB = 30;			//	Max Subjects
const int MAX_STU = 450;		// 	Max Students

int what_is_word();
void export_csv();
void data_sort();
void data_total();

using namespace std;

string word;
int N, temp;
char te[10];

struct database
{
	string name, result, seat;
	unsigned marks[MAX_SUB], total;
}st[MAX_STU];

int main()
{
	int i,j,k,what;
	ifstream file_in;
	file_in.open("sample.txt");
	i = j = k = 0;
	while(!file_in.eof())
	{
        file_in >> word;
		what = what_is_word();
		if(what)
		switch(what)
		{
			case 2:		if(!st[i].name.length())
						st[i].name = word;	break;
			case 4:		strcpy(te,word.c_str());
						if(m_disp[k])						
						st[i].marks[j++]=atoi(te);
						k++;				break;
			case 5:		j = k = 0;      i++;
						while(!file_in.eof())
                        {
                            file_in >> word;
    						if(what_is_word()==1)
                            {
                                st[i].seat = word;
    						    break;	
                            }					
                        }
		}
	}
	N = i-1;

	data_total();
	data_sort();
	export_csv();
	return 0;
}

/*
	Function	:	what_is_word
	Arguments	:	NULL
	Return		:	Cases present
					1 = Seat Number				FXXXXXXXXX
					2 = Name (Self / Mother)		XYZ
					3 = Subject Code			107001
					4 = Marks				100,--
					5 = Delimiter				..........
					0 = Others
*/

int what_is_word()
{
	if(((word[0]=='B')||(word[0]=='T')||(word[0]=='S')||(word[0]=='F'))&&(isdigit(word[1])))
	return 1;
	
	if((word[0]=='.')&&(word[1]=='.'))	return 5;

	if((word[0]=='-')&&(word[1]=='-'))	return 4;

	int flag = 1;	
	for(int i=0;i<word.length();++i)
	if(!isalpha(word[i]))
	flag = 0;
	if(flag)	return 2;

	flag = 1;
	for(int i=0;i<word.length();++i)
	if(!isdigit(word[i]))
	flag = 0;

	if((flag)&&(word.length()==6))		return 3;
	else if((flag)&&(word.length()<5))	return 4;
	return 0;
}

void data_sort()
{
	int i,j;
	database temp;
	for(i=0;i<N-1;++i)
	for(j=0;j<N-1;++j)
	if(st[j].total < st[j+1].total)
	{
		temp = st[j];
		st[j] = st[j+1];
		st[j+1] = temp;
	}
}

void data_total()
{
	int j;
	int total;
	for(int i=0;i<N;++i)
	{
		j = 0;
		total = 0;
		for(j=0;j<SUB;++j)
		total += st[i].marks[j];
		st[i].total = total;
	}
}

void export_csv()
{
	ofstream file_out;
	int j;
	file_out.open("output.csv");
	for(int i=0;i<N;++i)
	{
		j = 0;
		file_out<<st[i].seat<<","<<st[i].name;
		for(j=0;j<SUB;++j)		
		file_out<<","<<st[i].marks[j];
		file_out<<","<<st[i].total<<","<<st[i].total/(float)GT_MAX*100<<"\n";
	}
	file_out.close();
}
