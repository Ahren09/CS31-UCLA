#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
const int MAX_WORD_LENGTH = 20;
const int LONGEST_DOC = 250;


/*
 NOTE:
 in proper form
 rating
 
 
 
 */

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns);

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns);

int toArray(char document[],char docCopy[(const int)LONGEST_DOC/2+1][LONGEST_DOC+1]);
void swapC(char c1[MAX_WORD_LENGTH+1], char c2[MAX_WORD_LENGTH+1]);

int main(){
    
    char w1[8][MAX_WORD_LENGTH+1]={"mad","deranged","NEFARIOUS","half-witted","robot","plot","have","NeFaRiOuS"};
    char w2[8][MAX_WORD_LENGTH+1]={"scientist","robot","PLOT","assistant",
        "deranged","Nefarious","mad","pLoT"};
    int separation[8] = {1,3,1,2,1,0,12,0};
    
    cerr<<makeProper(w1,w2,separation,8)<<endl;
    for(int i=0;i<8;i++){
        for(int j=0;w1[i][j]!='\0';j++)
            cerr<<w1[i][j];
        cerr<<'\t';
        for(int j=0;w2[i][j]!='\0';j++)
            cerr<<w2[i][j];
        cerr<<'\t'<<separation[i];
        cerr<<'\n';
        //cout<<w1[i]<<'\t'<<w2[i]<<'\t'<<separation[i]<<endl;
     }
    /*
     
        char doc[]="Hello world! Ha ha!";
    char arr[4][MAX_WORD_LENGTH+1]={"yes","yes","yes","yes"};
        int res = toArray(doc,arr);
        cerr<<res;
        for(int i=0;i<125;i++){
            for(int j=0;arr[i][j]!='\0';j++){
                cout<<arr[i][j];
            }
            cout<<endl;
        }
     */
    
    
}



void swapC(char c1[MAX_WORD_LENGTH+1], char c2[MAX_WORD_LENGTH+1]){ // Can remove size?
    char temp[MAX_WORD_LENGTH+1];
    strcpy(temp,c1);
    strcpy(c1,c2);
    strcpy(c2,temp);
}

/*
 If document is an empty string
    return 0
 Repeatedly:
 find start of next word
    if no remaining word
        break
    copy each letter to the C string
 find end of word
 shift to the next char string
 add 1 to number of words
 
 */


int toArray(char document[],char docCopy[][LONGEST_DOC+1]){
    
    if(strcmp(document,"")==0)
        return 0;
    int index=0,i=0,j=0,wordCount=0;
    
    while(document[index]!='\0'){
        
        //read an alpha
        if(isalpha(document[index])){
            docCopy[i][j]=tolower(document[index]);
            j++;
        }
        //read a space
        else if(document[index]==' '||document[index]=='\0'){
            if(j!=0)
            {
                i++;
                wordCount++;
                j=0;
            }
        }
        
        //read something else
        index++;
    }
        return wordCount;
}

/*PseudoCode
 for every pair of elements
 convert to lower case
 mark those to be deleted
 
 remove those with signs
 remove those that are duplicates of another pair
 
 
 
 
 */

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns){
    
    //treat negative as 0
    if(nPatterns<0){
        nPatterns=0;
        return 0;
    }
    
    
    int validNum=0;
    
    
    
    for(int i=0;i<nPatterns;i++){
        bool toBeDelete=false;
        //问题：validNum会多减 如果两个word都不合要求
        
        //Examine empty string and negative separation
        if(strcmp(word1[i],"")==0||strcmp(word2[i],"")==0||separation[i]<0)
        {
            toBeDelete=true;
        }
        
        
        //examines each letter of word1 and word2
        else{
            
            for(int j=0;word1[i][j]!='\0';j++){ //NOTICE here is not j!='\0'
                // if contains signs, add this element to the delete array and skip to the next outer loop
                word1[i][j]=tolower(word1[i][j]);
                if(!isalpha(word1[i][j])){
                    toBeDelete=true;
                    break;
                }
            }
            for(int j=0;word2[i][j]!='\0';j++){
                word2[i][j]=tolower(word2[i][j]);
                if(!isalpha(word2[i][j])){
                    toBeDelete=true;
                    break;
                }
            }
            
            //examine duplicates of word pairs,provided that the word satisfies all previous requirements
            //turn separation to the lowest
            
            for(int k=i-1;k>=0;k--){
            if((strcmp(word1[i],word1[k])==0&&strcmp(word2[i],word2[k])==0)
               ||(strcmp(word1[i],word2[k])==0&&strcmp(word2[i],word1[k])==0)){
                separation[k]=min(separation[i],separation[k]);
                toBeDelete=true;
            }
            }
            
            
        }
        
        if(toBeDelete==false){
            
            strcpy(word1[validNum],word1[i]);
            strcpy(word2[validNum],word2[i]);
            separation[validNum]=separation[i];
            validNum++;
        }
        
    }
    
    
    return validNum;
}
    
    //Search duplicates of word pairs
               
/*PseudoCode
 Remove punctuations in document
 count the number of words in document
 Convert sentence into a 2D array of separated words
 
 repeatedly:
    find start of next word
    if no words remaining
        break
 
 Repeatedly:
    search each words of document in both word1 and word2
 
    if word matches
        search within the range of separation words
            if search reaches the end of program
                word pair not found
    else repeat
 
    if no words remaining
        break
    else continue moving forward
 endif
 
 */



int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns){
    
    char docCopy[126][MAX_WORD_LENGTH+1];
    
    if(strcmp(document,"")==0)
        return 0;
    int index=0,i=0,j=0,wordCount=0;
    
    while(document[index]!='\0'){
        
        //read an alpha
        if(isalpha(document[index])){
            docCopy[i][j]=tolower(document[index]);
            j++;
        }
        //read a space
        else if(document[index]==' '||document[index]=='\0'){
            
            if(j!=0)
            {
                docCopy[i][j]='\0'; // put a terminate point
                i++;
                wordCount++;
                j=0;
            }
        }
        
        //read something else
        index++;
    }
    
    for(int i=0;i<wordCount;i++){
        for(char str[]:word1){
            
            
        }
        
        
    }
    
    
    
}
 

  //  int PatternNum=makeProper(word1,word2,separation,nPatterns);
  

 






