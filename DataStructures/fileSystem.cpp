#include <iostream>
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
        if(s == " ..") {
            // update path
            int end = path.length();
            while(path[--end] != '/'){}
            // cout<<"end "<<end<<endl;
            path = path.substr(0, end);
            return this->parent;
        }

        Node *temp = this;
        bool flag=false;
        int start=0,end=0;
        while(end < s.length()) {
            if(s[end] != '/') { 
                end++;
                continue;
            }
            // cout<<"data--"<<s.substr(start, end-start)<<"--"<<endl;
            // finding if file exists
            string dir_name = s.substr(start, end-start);
            if(temp->subDirectory.find(dir_name) == temp->subDirectory.end()) {
                cout<<"No such directory"<<endl;
                return temp;
            }
            temp = temp->subDirectory.at(dir_name);
            updatePath(temp->name);
            end++;
            start = end;
            flag = true;
        }
        if(!flag) {
            string dir_name = s.substr(start, s.length());
            if(temp->subDirectory.find(dir_name) == temp->subDirectory.end()) {
                cout<<"No such directory"<<endl;
                return temp;
            }
            // cout<<"outside "<<s.substr(start, end-start)<<endl;
            temp = subDirectory.at(dir_name);
            // cout<<"name "<<temp->name<<endl;
            updatePath(temp->name);
        }
        // iterate over nested paths
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
};

int processCommand(string s) {
    int index = 0;
    while(s[index++] != ' '){}
    return index-1;
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
    int value, index;
    while(true) {
        cout<<"$";
        // read line including spaces
        getline(cin, command);
        index = processCommand(command);
        value = commands.find(command.substr(0, index))->second;
        if(value == 1) {
            dir.displayStrucutre();
        }
        else if(value == 2) {
            dir.addFile(command.substr(index, command.length()));
        }
        else if(value == 3) {
            dir.addDir(command.substr(index, command.length()));
        }
        else if(value == 4) {
            break;
        }
        else if(value == 5) {
            dir.removeFile(command.substr(index, command.length()));
        }
        else if(value == 6) {
            dir.deleteDir(command.substr(index, command.length()));
        }
        else if(value == 7) {
            dir.pwd();
        }
        else if(value == 8) {
            // cout<<"substring--"<<command.substr(index, command.length())<<"--"<<endl;
            dir.cd(command.substr(index, command.length()));
        }
    }
}