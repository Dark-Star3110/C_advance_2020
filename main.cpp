#include<bits/stdc++.h>
#include"graph.hpp"
#define MAX_INT -100
using namespace std;

map <string,int> rank;

// doc file roi luu cac dong doc duoc vao mang
string * readFile(string filePath){
    int count;
    ifstream infile(filePath);
    infile>>count;
    // cout << count << endl;
    string* lines = new string[count];
    int index = -1;
    if(infile.is_open()){
        string line;
        while(getline(infile, line)){
            if(index == -1){
                index++;
            }
            else{
                lines[index] = line.c_str();
                index++;
            }
            // cout << line.c_str() << endl;
        }
        infile.close();
    }
    // for(int i = 0; i <count; i++){
    //     cout << lines[i] << endl;
    // }
    return lines;
}

int numberLines(string filePath){
    int count;
    ifstream infile(filePath);
    infile>>count;
    infile.close();
    return count;
}

// tach chuoi theo ki tu truyen vao, roi luu vao mang
int numSub(string s,string sub){
    int count = 0;
    int start = 0;
    int end = s.find(sub);
    while (end != -1) {
        start = end + sub.size();
        end = s.find(sub, start);
        count++;
    }
    return count;
}
string* split(string s, string del) 
{
    int count = numSub(s,del)+1;
    string *output = new string[count];
    int i = 0;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        output[i] = s.substr(start, end - start);
        start = end + del.size();
        end = s.find(del, start);
        i++;
    }
    output[i] = s.substr(start, end - start);
    return output;
}

void recordFile(Graph g,string filePath){
    int count=0;
    for(auto x:g){
        count++;
    }
    ofstream outfile; 
    outfile.open(filePath); 
    // cout << count << endl;
    outfile << count << endl;
    for(auto x:g){
        outfile << x.first << " ";
        for(auto y:g[x.first]){
            outfile << y.first << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

void displayGraph(Graph g){
    for(auto x:g){
        for(auto y:g[x.first]){
            cout << x.first<<"--"<<y.first<<endl;
        }
    }
}

int main(){
    Graph g;
    string *lines;
    int num = numberLines("tiepXucGan.txt");
    // case 3 variables
    string name1,name2;
    bool checkConnections = false;
    bool check1=false;
    bool check2=false;

    // case 4 variables
    string nameCheck;

    // case 5 variables
    map<string,int> rankConnect;
    vector<int> rankCopy;
    int max = MAX_INT;
    // case 6 variables
    string nameF0;
    vector<string> F1;
    vector<string> F2;
    bool checkName =false;
    map<string,int> fre;
    vector<string>::iterator new_end;

    // case 7 variables
    string nameAdd;
    string nameEg;
    int countEg;

    // case 8 variables
    string nameAdd1, nameAdd2;

    int menu;
    while(1){
        cout <<endl<<"------------------------------MENU-------------------------------" << endl;
        cout << "1.Doc danh sach tiep xuc gan tu file"<< endl;
        cout << "2.in danh sach tiep xuc gan"<< endl;
        cout << "3.nhap ten 2 nguoi tu ban phim kiem tra tiep xuc gan" << endl;
        cout << "4.nhap 1 nguoi in danh sach tiep xuc gan"<< endl;
        cout << "5.in danh sach nhung nguoi tiep xuc gan voi nhieu nguoi nhat"<< endl;
        cout << "6.nhap ten 1 nguoi in 2 danh sach F1 va F2"<< endl;
        cout << "7.nhap them 1 nguoi cap nhat danh sach tiep xuc gan"<< endl;
        cout << "8.bo sung them thong tin tiep xuc gan giua 2 nguoi da co trong danh sach"<< endl;
        cout << "9.ghi danh sach tiep xuc gan ra file"<< endl;
        cout << "10.thoat"<< endl;
        cout << "chon menu:";
        cin >> menu;
        switch(menu){
            case 1:
            lines = readFile("tiepXucGan.txt");
            for(int i = 0; i < num; i++){
                string *vertexs = split(lines[i]," ");
                insert_vertex(g,vertexs[0]);
                int cc = numSub(lines[i]," ")+1;
                for(int j = 1; j < cc; j++){
                    // cout << vertexs[j]<< endl;
                    insert_vertex(g,vertexs[j]);
                    insert_edge(g,vertexs[0],vertexs[j],1);
                    insert_edge(g,vertexs[j],vertexs[0],1);
                    rankConnect[vertexs[0]]++;
                    rankConnect[vertexs[j]]++;
                }
            }
            for(auto x:g){
                rankConnect[x.first]/=2;
                rankCopy.push_back(rankConnect[x.first]);
            }
            displayGraph(g);
            break;
            case 2:
            for(auto x:g){
                cout << x.first <<" ";
                for(auto y:g[x.first]){
                    cout<<y.first <<" ";
                }
                cout << endl;
            }
            break;
            case 3:
            cout<<"nhap nguoi thu nhat:"; cin>>name1;
            cout<<"nhap nguoi thu hai:"; cin>>name2;
            for(auto x:g){
                if(x.first == name1) check1=true;
                if(x.first == name2) check2=true;
            }
            if(!check1 || !check2 || name1 == name2){
                cout<<"sai cu phap nhap"<<endl;
            }
            else{
                for(auto x:g[name1]){
                    if(x.first == name2)  checkConnections = true;
                }
                if(!checkConnections){
                cout<<"2 nguoi nay khong tiep xuc voi nhau"<<endl;
                }
                else{
                    cout<<"2 nguoi nay tiep xuc voi nhau"<<endl;
                }
            }
            
            checkConnections=false;
            check1=false;
            check2=false;
            break;
            case 4:
            cout<<"nhap nguoi can check:"; cin>>nameCheck;
            cout<<"danh sach tiep xuc gan:";
            for(auto x : g[nameCheck]){
                cout<<x.first<<" ";
            }
            cout<<endl;
            break;
            case 5:
            for(int i=0; i < rankCopy.size();i++){
                if(rankCopy[i] > max){
                    max = rankCopy[i];
                }
            }
            cout<<"Danh sach tiep xuc nhieu nhat:"<<endl;
            for(auto x:g){
                if(rankConnect[x.first] == max){
                    cout<<x.first<<" tiep xuc "<<rankConnect[x.first]<<" nguoi"<<endl;
                }
            }
            max = MAX_INT;
            break;
            case 6:
            cout<<"Nhap ten F0:"; cin>>nameF0;
            for(auto x : g){
                if(x.first == nameF0) checkName=true;
                fre[x.first] = 0;
            }
            if(!checkName){
                cout<<"khong co ten nguoi nay"<<endl;
            }
            else{
                for(auto i : g[nameF0]){
                    F1.push_back(i.first);
                    fre[i.first]++;
                    for(auto j : g[i.first]){
                        if(j.first != nameF0 && j.first != i.first && fre[j.first]==0){
                            F2.push_back(j.first);
                            fre[j.first]++;
                        }
                    }
                }   
            }
            cout<<"Danh sach F1:";
            for(int i = 0; i < F1.size(); i++){
                cout << F1[i] <<" ";
                for(int j = 0; j < F2.size(); j++){
                    if(F1[i] == F2[j]){
                        new_end = remove(F2.begin(), F2.end(), F2[j]);
                    }
                }
            }
            cout<<endl<<"Danh sach F2:";
            for(int i = 0; i < F2.size(); i++){
                cout << F2[i] <<" ";
            }
            cout<<endl;
            F1.clear();
            F2.clear();
            break;
            case 7:
            cout<<"nhap ten nguoi can them:"<<endl;
            cin>>nameAdd;
            insert_vertex(g,nameAdd);
            cout<<"nhap so nguoi tiep xuc gan:"<<endl;
            cin>>countEg;
            cout<<"nhap danh sach tiep xuc gan:"<<endl;
            for(int i=0;i<countEg;i++){
                cin>>nameEg;
                insert_edge(g,nameAdd,nameEg,1);
                insert_edge(g,nameEg,nameAdd,1);
            }
            displayGraph(g);
            break;
            case 8:
            cout<<"nhap lien ket gan can them:"<<endl;
            cin>>nameAdd1;
            cin>>nameAdd2;
            insert_edge(g,nameAdd1,nameAdd2,1);
            insert_edge(g,nameAdd2,nameAdd1,1);
            displayGraph(g);
            break;
            case 9:
            recordFile(g,"dataFake.txt");
            break;
            case 10:
            exit(0);
            break;
        }
    }
    return 0; 
}