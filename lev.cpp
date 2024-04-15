#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <dirent.h>

#define max 1000
using namespace std;
#define WHITE   "\033[0m"
#define ORANGE  "\033[1;38;5;208m"
#define GREEN   "\033[1;32m"

int levenshtein(const char *s, const char *t);
int min2(int a,int b);
int min3(int a,int b,int c);
int max2(int a,int b);

int main() {
    string filename = "original_file/file.txt";
    string files_directory = "files";
    DIR *dir;
    struct dirent *entry;
    
    // Открыть файл для записи вывода
    ofstream outputFile("result/result.txt");
    
    if ((dir = opendir(files_directory.c_str())) != NULL) {
        int fileCounter = 1;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {
                string filename2 = files_directory + "/" + entry->d_name;
                string str1;
                string str2;
                string buffer;
                ifstream input1(filename);
                while (getline(input1, buffer))
                    str1 += (buffer + '\n');
                ifstream input2(filename2);
                while (getline(input2, buffer))
                    str2 += (buffer + '\n');
                float maximum=max2(str1.size(),str2.size());
                float leven=levenshtein(str1.c_str(),str2.c_str())/maximum;
                float plag=(1-leven)*100;
            
                outputFile << "For file " << fileCounter << endl;
                outputFile << plag << "%" << endl;
                if(plag >= 50 && plag <= 100){
                    outputFile << "Plagiarised! :(" << endl;
                }
                else{
                    outputFile << "Not plagiarised! ^^" << endl;
                }
                
                fileCounter++; 
            }
        }
        closedir(dir);
        outputFile.close();
    } else {
        cout << "Files directory not found." << endl;
        return 1;
    }
}

int max2(int a,int b){
    return a>b?a:b;
}

int min2 (int a,int b){
    return a<b?a:b;
}

int min3 (int a,int b,int c){
    return min2(a,min2(b,c));
}




int levenshtein(const char *s, const char *t){
    if(strcmp(s,t)==0){
        return 0;
    }
    if(strlen(s)==0){
        return strlen(t);
    }
    if(strlen(t)==0){
        return strlen(s);
    }
    int len1,len2,x,y,ld,od;
    len1=strlen(s);
    len2=strlen(t);
    int column[len1+1];
    for (y=1;y<=len1;y++)
        column[y]=y;
    for (x=1;x<=len2;x++) {
        column[0]=x;
        for (y=1,ld=x-1;y<=len1;y++){
            od=column[y];
            column[y]=min3(column[y]+1,column[y-1]+1,ld+(s[y-1]==t[x-1]?0:1));
            ld=od;
        }
    }
    return column[len1];
}
