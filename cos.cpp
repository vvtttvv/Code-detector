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

char *strlwr(char *str);
int sum(int count[max],int num1);
double dotprod(char words1[max][50],char words2[max][50],int num1,int num2,int count1[max],int count2[max]);
int occurences(FILE *fp,int count[max],char words[max][50]);

int main() {
    DIR *dir;
    struct dirent *ent;
    const double PI = 3.1415926;
    char path1[100], path2[100];
    char words1[max][50], words2[max][50];
    int count1[max], count2[max];
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcat(cwd, "/output/");
    } else {
        perror("getcwd() error");
        return 1;
    }

    ofstream outFile("result/result.txt");
    if (!outFile) {
        cerr << "Failed to create result.txt file!" << endl;
        return 1;
    }

    strcpy(path1, "original_file/file.txt");
    int fileCounter = 1;
    if ((dir = opendir("files")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { 
                strcpy(path2, "files/");
                strcat(path2, ent->d_name);
                strcat(cwd, ent->d_name);

                FILE *fp1 = fopen(path1, "r"); 
                FILE *fp2 = fopen(path2, "r"); 
                
                if (fp1 == NULL || fp2 == NULL) {
                    cerr << "Failed to open :(" << endl;
                    exit(EXIT_FAILURE);
                }

                int num1 = occurences(fp1, count1, words1);
                fclose(fp1);
                int num2 = occurences(fp2, count2, words2);
                fclose(fp2);

                double mod1 = sqrt(sum(count1, num1));
                double mod2 = sqrt(sum(count2, num2));
                double dotsum = dotprod(words1, words2, num1, num2, count1, count2);
                double plag = acos(dotsum / (mod1 * mod2)) * 180 / PI;
                double percent = 100 - (plag / 90) * 100;
                
                outFile << "For file " << fileCounter << endl;
                outFile << "Plagiarism probability: " << percent << "%" << endl;
                if (plag >= 0 && plag <= 45) {
                    outFile << "Plagiarised!   :(" << endl;
                } else {
                    outFile << "Not plagiarised! ^^" << endl;
                }
                fileCounter++;
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return EXIT_FAILURE;
    }

    outFile.close();

    return 0;
}
 

char *strlwr(char *str){
  char *p=(char *)str;
  while (*p)
  {
     *p=tolower((char)*p);
      p++;
  }
  return str;
}

double dotprod(char words1[max][50],char words2[max][50],int num1,int num2,int count1[max],int count2[max]){
    int i,j;
    double s=0;
    for(i=0;i<num1;i++){
        for(j=0;j<num2;j++){
            if(strcmp(words2[j],words1[i])==0){
                s=s+count1[i]*count2[j];
                break;
            }
        }
    }
    return s;
}

int sum(int count[max],int num1){
    int i,s=0;
    for(i=0;i<num1;i++)
    {
        s=s+pow(count[i],2);
    }
    return s;
}

int occurences(FILE *fp, int count[max], char words[max][50]) {
    char word[50];
    int index = 0;

    while (fscanf(fp, "%s", word) != EOF) {
        strlwr(word);

        int len = strlen(word);
        int j = 0;
        for (int i = 0; i < len; i++) {
            if (isalnum(word[i])) {
                word[j++] = word[i];
            }
        }
        word[j] = '\0';

        if (j != 0) { 
            int uniq = 1;
            for (int i = 0; i < index; i++) {
                if (strcmp(words[i], word) == 0) {
                    uniq = 0;
                    count[i]++;
                    break;
                }
            }
            if (uniq) {
                strcpy(words[index], word);
                count[index++] = 1;
            }
        }
    }
    return index;
}


