#include <iostream>
#include <fstream>
#include <string.h> //for strcmp and other char* functions

using namespace std;

char *reader, *modMov, *mod, *modSpace;
int size, visa;
char newFileName[] = "QuickenDownloadMod.qfx";
char newFilePath[] = "/Users/davidhartvigsen1/";
char newFileDir[] = "Downloads";
char* newFileString = new char[100];

int main (int argc, char * const argv[]) {

    cout << argv[1] << endl;
    
	ifstream origFile(argv[1]);
	filebuf* of;
	void advancer();
	
	//get the length of the opened quicken file
	//----------------------------------
	origFile.seekg(0,ios::end); //put ifstream get pointer at the end of the file
	size = origFile.tellg();//returns the number of characters at the end of file position pointer 
	origFile.seekg(0,ios::beg);//put the get pointer back to the beginning 
	//----------------------------------
	
	reader = new char[size]; //intialize memory for original file contents
	mod = new char[size]; //initalize memory for modified file contents
	modSpace = modMov = mod;
	
	//create char array of original file contents.
	of = origFile.rdbuf(); //change ifstream object to filebuf object
	of->sgetn(reader, size); //copy the contents of the file buffer into the char aary
	
	*modMov++ = *reader; //preliminary move for while sequence below	
	visa = 0;
	
	advancer();	//character advancer
	
	//create the new modified file
	strcpy(newFileString, newFilePath);
	strcat(newFileString, newFileDir);
	strcat(newFileString, "/");
	strcat(newFileString, newFileName);
	ofstream newFile(newFileString);
	newFile.write(modSpace,size);
	newFile.close();
	
	cout << endl<< visa/2 << " visa debit transactions were modified." << endl;
	cout << endl << "File " << newFileName << " was written in " << newFileDir << "."
	<< endl <<"Path: " << newFileString << endl;

	origFile.close();
	return 0;
}

void advancer(){
	void tokenChecker();
	while(*reader){
		if (*reader != '<'){
			*modMov++ = *(++reader); 
		}
		else {
			tokenChecker();
		}
	}
}

void tokenChecker(){
	void nameAndMemoAnlzr();
	char tkTitle[50];
	char* tkTitlePtr = tkTitle;
	*tkTitlePtr++ = *reader;//preliminary move for while sequence below
	while (*reader != '>'){
		*tkTitlePtr++ = *modMov++ = *(++reader); //all pointers should add '>' then move to the next char
		*tkTitlePtr = '\0'; //finish the token title string (adds a null that is overwritten next loop)
	}	
	//check for the name title or for the memo title
	if (!strcmp(tkTitle,"<NAME>") || !strcmp(tkTitle,"<MEMO>")){
		nameAndMemoAnlzr();
	}
}

//this is the main algorithym of what is trying to be accomplished in this program
void nameAndMemoAnlzr(){
	char testedChars[19] = ""; //19th character for the null
	bool lettNum, hasWS, is18WS; // various flags for verifying visa cc transaction number
	lettNum = true; //is the character sequence alphanumeric only
	hasWS = false;  //has whitespace
	is18WS = true;  //is the 18th character a whitespace
	const int MAX = 17;

	for (int n=0; n <= MAX; n++){
		if (reader[1] != ' '){
			//if not a space, move to next test to of number or character
			//cout << endl << "before letter and number if statement, reader = " << reader[0] << endl;
			if ((reader[1] >= '0' && reader[1] <= '9') || (reader[1] >= 'A' && reader[1] <= 'Z')
				|| (reader[1] >= 'a' && reader[1] <= 'z')){
				testedChars[n] = *(++reader);
				//cout << "the reader value after inserting into testedChars is: "<< reader[1];
			}
			else { //anything that is not an alphanumeric character fails the test
				lettNum = false;
				testedChars[n] = *(++reader);
				break;
			}
		}
		else {
			if (n != MAX){ //a space anywhere besides the 18th character fails the test
				hasWS = true;
				testedChars[n] = *(++reader);
				break;
			}
			else
				testedChars[n] = *(++reader);
		}
	}
	
	// the 18th character must be a space otherwise fail third test
	if (testedChars[16] != '\0'){
		if (testedChars[17] != ' '){
			is18WS = false;
			//cout << endl << "inside 18th is not a whitespace" << endl;
		}
		else{
			*modMov++ = *(++reader);
		}
	}
	
	//check for visa transaction number failure (3 tests),
	//and add the testedChars array to modMov if failed
	if (!lettNum || hasWS || !is18WS){
		for (int n=0; n <= MAX; n++){
			if (testedChars[n] != '\0')
				*modMov++ = testedChars[n];
		}
	}
	else
		visa++;
}