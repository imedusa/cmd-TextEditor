#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include <fstream>
#include <cctype>
using namespace std;
 
class Line{
    public:
        Line* nextLine;
        string content;
        Line(){
            nextLine=NULL;
            content="";
        }
        Line(string c){
            nextLine=NULL;
            content=c;
        }
};
class Doc{
    public:
        Line* firstLine;
        Line* currLine;
        int numberOfLines;
    private:
        int nodeCursor;
        int charCursor;
    public:
        void cursorDown();
        void cursorEnd();
        void currCursorPos();
        void printDoc();
        void moveCursor(int line,int pos);
        void delChar();
        void delChar(int line, int pos);
        void newLine(std::string s);
        void newLine(int line, std::string s);
        void delLine();
        void addString(std::string s);
        void cursorLeft();
        void cursorRight();
        void cursorUp();
        //void delLine(int line);
        void capitalize(int pos);
        void findAndreplaceString(std::string find, string replace);
        void saveFile();
        Doc(){
            firstLine=NULL;
            currLine=NULL;
            numberOfLines=0;
            nodeCursor=0;
            charCursor=0;
        }
};
void Doc::cursorEnd(){
    charCursor=(currLine->content).length()-1;
}
void Doc::cursorDown(){
    if(currLine==NULL) return;//doc empty
    if(currLine->nextLine!=NULL){
        if(charCursor>=((currLine->nextLine->content).length()))
        {           
            charCursor=(currLine->nextLine->content).length()-1;//goes to the end of the next Line, since the current Line is longer
            //than the next Line
        }
        //else charCursor will remain unchanged
        currLine=currLine->nextLine;
        nodeCursor+=1;
    }
    else{
        cout<<"At the last line. Staying at same position"<<endl;
    }
}
 
void Doc::moveCursor(int line,int pos){
    if(currLine==NULL) return;
    if(line<0){
        cout<<"Invalid line"<<endl;
        return;
    }
    //we assume that the line and pos positions are 0 indexed
    if(line>=numberOfLines)//if line number is greater than the number of lines
    {
        //move cursor to the end of the doc
        while(currLine->nextLine!=NULL){
            currLine=currLine->nextLine;
            nodeCursor+=1;
        }
        //reached last line
        charCursor=((currLine->content).length())-1;
        return;
    }
    if(line<nodeCursor){
        currLine=firstLine;
        nodeCursor=0;
    }
    while(nodeCursor<line){
        currLine=currLine->nextLine;
        nodeCursor+=1;
    }
    //nodeCursor reaches the required line
    if(pos>=((currLine->content).length())){
        charCursor=((currLine->content).length())-1;
        //if pos is greater than the length of the line,
        //it reaches the end of the line
    }    
    else{
        charCursor=pos;
    }
}
 
void Doc::newLine(std::string s){
    if(currLine==NULL){//if doc is currently empty
        firstLine=new Line(s);
        currLine=firstLine;
    }
    else{
        Line* temp=currLine->nextLine;
        currLine->nextLine=new Line(s);
        //cursor moves to the first character of newly added line
        currLine->nextLine->nextLine=temp;
        currLine=currLine->nextLine;
        nodeCursor+=1;
        charCursor=0;
    }
    numberOfLines++;
}
 
void Doc::newLine(int line, std::string s)
{
    //insert new line after specified node
    //line will have the string as input text
    //push action to undostack
 
    if(currLine==NULL)//if doc is empty
    {   newLine(s);
        return;
    }
    if(line<0){
        cout<<"Invalid line"<<endl;
        return;
    }
    if(line==0){
        Line* temp=firstLine;
        firstLine=new Line(s);
        firstLine->nextLine=temp;
        currLine=firstLine;
        nodeCursor=0;
        charCursor=0;
        return;
    }
    if(line>=numberOfLines)//if line number is greater than the number of lines
    {
        //move cursor to the last line
        while(currLine->nextLine!=NULL){
            currLine=currLine->nextLine;
            nodeCursor+=1;
        }
    }
    if(line<=nodeCursor){
        currLine=firstLine;
        nodeCursor=0;
    }
    while(nodeCursor<(line-1)){
        currLine=currLine->nextLine;
        nodeCursor+=1;
    }
    //nodeCursor reaches the required line
    //now we need to add a new line after the current line
    newLine(s);
}
 
void Doc::delChar()
{
    //delete character at cursor
    string str=currLine->content;
    //unless the charCursor is at the last position of the line, the position
    //of cursor remains unchanged
    str.erase(str.begin()+charCursor);
    if(charCursor==str.length())
        charCursor=0;    
    currLine->content=str;
    
}
 
void Doc::delLine(){
    //the cursor adjusts to the line after the deleted line
    //in case it is the last line, it moves to the first line
    if(currLine==NULL) return;// if doc is empty
    if(nodeCursor==0){//if first Line needs to be deleted
        Line* temp=firstLine;
        firstLine=firstLine->nextLine;
        currLine=firstLine;
        charCursor=0;
        delete temp;
        numberOfLines--;
        return;
    }
    Line* temp=firstLine;
    while(temp->nextLine!=currLine){
        temp=temp->nextLine;
    }
    Line* temp2=temp->nextLine;
    temp->nextLine=temp->nextLine->nextLine;
    if(temp->nextLine==NULL) 
    {
        currLine=firstLine;
        nodeCursor=0;
        
    }
    else{
        currLine=temp->nextLine;
        //nodeCursor will remain unchanged, as previous node was deleted
    }
    charCursor=0;
    delete temp2;    
    numberOfLines--;
}
 
void Doc::delChar(int line, int pos)
{
    //delete character at specified position in file
    if(line>=numberOfLines || line<0) return;
    moveCursor(line,pos);
    delChar();
}
 
void Doc::currCursorPos(){
    cout<<"Node pos:"<<nodeCursor<<endl;
    cout<<"Char pos:"<<charCursor<<endl;
}
void Doc::printDoc(){
    Line* temp=firstLine;

    if(temp == NULL) {
        cout << "Empty Doc" << endl;
        return;
    }
    while(temp!=NULL){
        cout<<temp->content<<endl;
        temp=temp->nextLine;
    }
    
}

void Doc::addString(std::string s)
{
    
    //edgecase: empty doc
    if(currLine == NULL) {
        cout << "Empty Document" << endl;
        return;
    }
    currLine->content.insert(charCursor, s);   
}
void Doc::cursorLeft()
{
    //move cursor to left by one position

    //if at beginning of current line, move to end of prev line

    //emptydoc
    if(currLine == NULL) {
        cout << "Empty Doc" << endl;
        return;
    }

    //prev line
    //int line1 = nodeCursor-1;

    //last pos: moves it to the last pos of prev node/string
    int pos1 = INT_MAX;
    if(charCursor == 0) {
        if(currLine == firstLine) {
            cout << "Already at first line, cannot move back" << endl;
            return;
        }
        //change currentline 
        Line* prev = firstLine;
        while(prev->nextLine != currLine) {
            prev = prev->nextLine;
        }
        currLine = prev;
        nodeCursor--;
        moveCursor(nodeCursor, pos1);
        return ;
    }
    charCursor--;
}

void Doc::cursorRight()
{

    //move cursor to right by one position
    //if at end of current line, move to start of next line

    //emptydoc
    if(currLine == NULL) {
        cout << "Empty Doc" << endl;
        return;
    }

    //int line1 = nodeCursor+1;

    if(charCursor == currLine->content.length()-1) {
        //last line of doc
        if(currLine->nextLine == NULL) {
            cout << "Reached end of file" << endl;
            return;
        }
        currLine = currLine->nextLine;
        charCursor = 0;
        nodeCursor++;
        return;
    }
    charCursor++;
}

void Doc::cursorUp()
{
    //move cursor to the start of the prev node

    if(currLine == NULL) {
        cout << "Empty Doc" << endl;
        return;
    }
    //already at the first line
    if(nodeCursor == 0) {
        cout << "Already at first line" << endl;
        return;
    }
    //else moves to prev line
    //change currentline 
    Line* prev = firstLine;
    while(prev->nextLine != currLine) {
        prev = prev->nextLine;
    }
    currLine = prev;
    nodeCursor--;
    moveCursor(nodeCursor, charCursor);
}

// void Doc::delLine(int line)
// {
//     //delete line at specified position
//     //push action to undostack

//     if(currLine == NULL) {
//         cout << "Empty Doc" << endl;
//         return;
//     }
//     if(line > numberOfLines || line < 0) {
//         cout << "No line to delete" << endl;
//         return;
//     }
//     //deletes the node being pointed
//     Line* prev = firstLine;
//     while(prev->nextLine != currLine) {
//         prev = prev->nextLine;
//     }
//     prev->nextLine = currLine->nextLine;
//     delete currLine;
//     //decrements the total number of lines in the doc
//     numberOfLines--;
// }

//takes in the index, caps the chars between current cursor and index input
void Doc::capitalize(int pos)
{
    //convert selected text to upper case
    //if no selected text, prompt user to select
    //null doc
    if(currLine == NULL) {
        cout << "Empty Doc" << endl;
        return;
    }
    if(pos < 0 || pos > currLine->content.length()-1) {
        cout << "Invalid index" << endl;
        return;
    }
    
    if(pos >= charCursor) {
        string selected = currLine->content.substr(charCursor, pos - charCursor + 1);
        std::cout << selected << endl;
        transform(selected.begin(), selected.end(), selected.begin(), ::toupper);
        //replaces
        currLine->content.replace(charCursor, pos - charCursor + 1, selected);
    }
    else {
        string selected = currLine->content.substr(pos, charCursor - pos + 1);
        transform(selected.begin(), selected.end(), selected.begin(), ::toupper);
        currLine->content.replace(pos, charCursor - pos + 1, selected);
    }
}

void Doc::findAndreplaceString(std::string find, string replace)
{
    //replace selected string with input string at cursor
    //delete selected portion
    //insert new string

    Line* temp = firstLine;

    char instance;
    cout << "1)Replace one instances in current line  or 2)all instances in the current line? Input the option" << endl;
    cin >> instance;

    if(instance != '1' && instance != '2') {
        cout << "Enter valid option!" << endl;
        return;
    }
    //one instances in current line
    if(instance == '1') {
        std::size_t pos = currLine->content.find(find);
        if (pos == std::string::npos)  {
            cout << "Not found" << endl;
            return;
        }
    currLine->content.replace(pos, find.length(), replace);
    return;
    }
    //all instances in the curent line
    if(instance == '2') {
        std::size_t pos = currLine->content.find(find);
        if (pos == std::string::npos)  {
            cout << "Not found" << endl;
            return;
        }
        //keeps searching for next instance
        while(pos != std::string::npos) {
            currLine->content.replace(pos, find.length(), replace);
            pos = currLine->content.find(find, pos+1);
        }
    }
}

void Doc:: saveFile() {
    fstream file;

    file.open("file.txt", ios::out);
    if (!file) {
		cout << "File not created!";
	}
	else {
		cout << "File created successfully!";

        Line* itr = firstLine;
        while(itr->nextLine != NULL)
        {
            file << itr->content;
            file << "\n";
            itr = itr->nextLine;
        }

        file << itr->content;
        file.close();
	}


}

int main(){
    Doc d;
    cout << "Enter operation number to perform or -1 to quit "<<endl;
    cout<<"1.Print Document"<<endl;
    cout<<"2.Enter new line after current line"<<endl;
    cout<<"3.Enter new line at specified line number with specified content"<<endl;
    cout<<"4.Delete current line"<<endl;
    cout<<"5.Print current cursor position"<<endl;
    cout<<"6.Move cursor down"<<endl;
    cout<<"7.Move cursor up"<<endl;
    cout<<"8.Move cursor left"<<endl;
    cout<<"9.Move cursor right"<<endl;
    cout<<"10.Move cursor to end of line"<<endl;
    cout<<"11.Move cursor to specified position"<<endl;
    cout<<"12.Delete character at cursor"<<endl;
    cout<<"13.Delete character at specified position"<<endl;
    cout<<"14.Add string behind cursor"<<endl;
    cout<<"15.Capitalize the letters between specified index and cursor"<<endl;
    cout<<"16.Find and replace string"<<endl;
    cout<<"17.Save File"<<endl;
    cout << endl;
    int op;
    do {
        cin >> op;
        cin.clear();
        cin.sync();
        //cout << d.numberOfLines << endl;
        switch(op){
            case 1:{
                d.printDoc();
                break;
            }
            case 2:{
                string s;
                cout<<"Enter content"<<endl;
                getline(cin, s);
                d.newLine(s);
                break;
            }
            case 3:{
                string s;
                int lineNumber;
                
                cout<<"Enter line index"<<endl;
                cin>>lineNumber;
                cout<<"Enter content"<<endl;
                getline(cin, s);
                d.newLine(lineNumber,s);
                
                break;
            }
            case 4:{
                d.delLine();
                break;
            }
            case 5:{
                d.currCursorPos();
                break;
            }
            case 6:{
                d.cursorDown();
                break;
            }
            case 7:{
                d.cursorUp();
                break;
            }
            case 8:{
                d.cursorLeft();
                break;
            }
            case 9:{
                d.cursorRight();
                break;
            }
            case 10:{
                d.cursorEnd();
                break;
            }
            case 11:{
                int line;
                int charPos;
                cout<<"Enter line index"<<endl;
                cin>>line;
                cout<<"Enter character index"<<endl;
                cin>>charPos;
                d.moveCursor(line,charPos);
                break;
            }
            case 12:{
                d.delChar();
                break;
            }
            case 13:{
                int line;
                int charPos;
                cout<<"Enter line index"<<endl;
                cin>>line;
                cout<<"Enter character index"<<endl;
                cin>>charPos;
                d.delChar(line,charPos);
                break;
            }
            case 14:{
                string s;
                cout<<"Enter string"<<endl;
                getline(cin, s);
                d.addString(s);
                break;
            }
            case 15:{
                int idx;
                cout<<"Enter index number"<<endl;
                cin>>idx;
                d.capitalize(idx);
                break;
            }
            case 16:{
                string s1,s2;
                cout<<"String to find"<<endl;
                cin>>s1;
                cout<<"String to replace with"<<endl;
                cin>>s2;
                d.findAndreplaceString(s1,s2);
                break;
            }
            case 17:{
                d.saveFile();
                break;
            }
        }
    } while(op != -1);
    return 0;
}