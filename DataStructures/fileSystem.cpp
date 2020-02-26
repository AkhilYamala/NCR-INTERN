#include <iostream>
#include <sstream>
#include <string.h>
#include <set>
#include <iterator>
#include <map>
using namespace std;

class Node {
    string name;
    Node* parent;
    set<string> files;
    map<string, Node*>subDirectory;
    static string path;

    public:
    Node(string name, Node *parent) {
        this->name = name;
        this->parent = parent;
    }

    void addFile(string fname) {
        // check for it's existance
        // auto ind = files.find(fname);
        // if(*ind == fname) {
        //     cout<<"File already exist!!!"<<endl;
        // }
        files.insert(fname);
        // cout<<"File added successfully"<<endl;
    }

    void removeFile(string name) {
        auto ind = files.find(name);
        if(*ind == name) {
            // cout<<"File deleted"<<endl;
            files.erase(ind);
            return;
        }
        cout<<"File does not exist"<<endl;
    }

    void displayStrucutre() {
        cout<<"Files"<<endl;
        for(auto i=files.begin(); i!= files.end(); i++) {
            cout<<*i<<" ";
        }
        cout<<endl<<"DIR"<<endl;
        map<string, Node*>::iterator itr;
        for(auto itr=subDirectory.begin(); itr!= subDirectory.end(); ++itr)
            cout<<itr->first<<" ";
        cout<<endl;
    }

    void addDir(string name) {
        Node *newDirectory = new Node(name, this);
        subDirectory.insert(pair<string, Node*>(name, newDirectory));
    }

    void deleteDir(string name) {
        if(subDirectory.erase(name) != 1)
            cout<<"Directory not found"<<endl;
    }

    Node* cd(string s) {
        if(s == "..") {
            if(this->parent == NULL)
                return this;
            // update path
            int end = path.length();
            while(path[--end] != '/'){}
            // cout<<"end "<<end<<endl;
            path = path.substr(0, end);
            return this->parent;
        }

        Node *temp = this;
        if(temp->subDirectory.find(s) == temp->subDirectory.end()) {
            cout<<"No such directory"<<endl;
            return temp;
        }
        temp = temp->subDirectory.at(s);
        updatePath(temp->name);
        return temp;
    }

    string pwd() {
        return path;
    }

    void updatePath(string n) {
        // cout<<"update path"<<endl;
        path += '/'+n;
    }

};

// initializing path  --->  data_type class_name::var_name = value
string Node::path = "root";

class Dir {
    Node *root = NULL;
    
    public:
    Dir() {
        root = new Node("root", NULL);
    }
    
    void addFile(string fname) {
        root->addFile(fname);
    }

    void removeFile(string name) {
        root->removeFile(name);
    }

    void displayStrucutre() {
        root->displayStrucutre();
    }

    void addDir(string name) {
        root->addDir(name);
    }

    void deleteDir(string name) {
        root->deleteDir(name);
    }

    void cd(string s) {
        root = root->cd(s);
    }
    void pwd() {
        cout<<root->pwd()<<">"<<endl;
    }
    string getPath() {
        return root->pwd();
    }
};

int getNumberOfSpaces(string s) {
    int count = 0;
    for(int i=0; i<s.length(); i++){
        if(s[i] == ' ')
            count++;
    }
    return count;
}

void splitString(string s, string arr[]) {
    int start = 0;
    int ind = 0;
    for(int i=0; i<s.length(); i++) {
        if(s[i] == ' ') {
            arr[ind++] = s.substr(start, i-start);
            start = i+1;
        }
    }
    arr[ind] = s.substr(start, s.length()-start);
}

bool isPath(string s) {
    for(int i=0; i<s.length(); i++)
        if(s[i] == '/')
            return true;
    return false;
}

int main() {
    Dir dir;
    map<string, int>commands;
    commands.insert(pair<string, int>("ls", 1));      // display
    commands.insert(pair<string, int>("mkfil", 2));   // create file
    commands.insert(pair<string, int>("mkdir", 3));   // create directory
    commands.insert(pair<string, int>("exit", 4));    // create exit
    commands.insert(pair<string, int>("rmf", 5));     // delete file
    commands.insert(pair<string, int>("rmdir", 6));   // delete dir
    commands.insert(pair<string, int>("pwd", 7));     // pwd      ------
    commands.insert(pair<string, int>("cd", 8));      // change dir   ----------

    string command;
    int value;
    while(true) {
        cout<<dir.getPath()<<"$";
        // read line including spaces
        getline(cin, command);
        int size = getNumberOfSpaces(command)+1;
        string arr[size];
        splitString(command, arr);

        value = commands.find(arr[0])->second;
        if(value == 1) {
            dir.displayStrucutre();
        }
        else if(value == 2) {
            for(int i=1; i<size; i++)
                dir.addFile(arr[i]);
        }
        else if(value == 3) {
            for(int i=1; i<size; i++) {
                if(isPath(arr[i])) {
                    int start = 0;
                    string s = arr[i];
                    int pathCount = 0;
                    for(int i=0; i<s.length(); i++) {                        
                        if(s[i] == '/') {
                            dir.addDir(s.substr(start, i-start));
                            dir.cd(s.substr(start, i-start));
                            start = i+1;
                            pathCount++;
                        }
                    }
                    dir.addDir(s.substr(start, s.length()-start));
                    
                    for(int i=0; i<pathCount; i++)
                        dir.cd("..");
                }
                else 
                    dir.addDir(arr[i]);
            }
        }
        else if(value == 4) {
            break;
        }
        else if(value == 5) {
            for(int i=1; i<size; i++)
                dir.removeFile(arr[i]);
        }
        else if(value == 6) {
            for(int i=1; i<size; i++)
                dir.deleteDir(arr[i]);
        }
        else if(value == 7) {
            dir.pwd();
        }
        else if(value == 8) {
            for(int i=1; i<size; i++) {
                if(isPath(arr[i])) {
                    int start = 0;
                    string s = arr[i];
                    for(int i=0; i<s.length(); i++) {                        
                        if(s[i] == '/') {
                            dir.cd(s.substr(start, i-start));
                            start = i+1;
                        }
                    }
                    dir.cd(s.substr(start, s.length()-start));
                }
                else 
                    dir.cd(arr[i]);
            }
        }
        else {
            cout<<"Invalid command"<<endl;
        }
    }
}