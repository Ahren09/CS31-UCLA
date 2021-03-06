#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
using namespace std;
const int MAX_WORD_LENGTH = 20;
const int LONGEST_DOC = 250;

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns);

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns);

int removePunc(const char document[],char alphaSpace[]);

void toArray(char alphaSpace[],char docCopy[][MAX_WORD_LENGTH +1]);


int main(){
    
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    
    
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever."
                ,test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    cout << "All tests succeeded" << endl;

     
    
    
    cout<<rate("The mad UCLA scientist unleashed a deranged evil giant robot.",test1w1, test1w2, test1dist, TEST1_NRULES)<<endl;
    cout<<rate("The mad UCLA scientist unleashed    a deranged robot.",test1w1, test1w2, test1dist, TEST1_NRULES)<<endl;
    cout<<rate("**** 2018 ****",test1w1, test1w2, test1dist, TEST1_NRULES)<<endl;
    cout<<rate("That plot nefarious",test1w1, test1w2, test1dist, TEST1_NRULES)<<endl;
    cout<<rate("That scientist said two mad scientists suffer from deranged-robot fever.",
               test1w1, test1w2, test1dist, TEST1_NRULES)<<endl;
    cout<<rate("deranged deranged robot deranged robot robot",test1w1, test1w2, test1dist, TEST1_NRULES)<<endl;
    
    
    
    
     
     
    
    
    
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
               
/*PseudoCode
 
 Repeatedly:
    search each words of document in word1
 
    if word matches
        search word2 within range of separation words
            if word2 found
                increase rate by 1
                mark the matching pair as found
 
    if no words remaining
        break
 
 */
int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns){
    
    char alphaSpace[251];
    int wordCount=removePunc(document,alphaSpace);
    char docCopy[125][MAX_WORD_LENGTH+1];
    toArray(alphaSpace, docCopy);
    int rate=0;
    
    //store the search result of each word pair in word1[] and word2[]
    
    bool match[125];
    for(int i=0;i<125;i++)
        match[i]=false;
    
    //i is the indicator of docCopy - the words to be tested
    for(int i=0;i<wordCount;i++){
        if(strcmp(docCopy[i],"")==0)
            break;
        //j is the indicator of word1 and word2
        for(int j=0;j<nPatterns;j++){
            
            //if contains word1
            if(strcmp(docCopy[i],word1[j])==0){
                
                //k specifies the scope of search
                int k;
                int upperBound=((i+separation[j]+1)<wordCount)?(i+separation[j]+1):(wordCount-1);
                int lowerBound=((i-separation[j]-1)>=0)?(i-separation[j]-1):0;
                
                //find word2
                for(k=lowerBound;k<=upperBound;k++){
                    if(k==j)
                        k++;
                    else if(strcmp(docCopy[k],word2[j])==0&&match[j]==false){
                        rate++;
                        match[j]=true;
                        break;
                    }
                    
                }
                
                
            }
            
            
            
        }
        
        
    }
    
    return rate;
    
}

/*
 Convert sentence into a 2D array of separated words
 
 repeatedly:
 find start of next word
 if no words remaining
 break
 */
void toArray(char alphaSpace[],char docCopy[][MAX_WORD_LENGTH +1]){
    int index=0;
    int m=0,n=0;
    while(true){
        if(isalpha(alphaSpace[index])){
            if(n>=MAX_WORD_LENGTH) //这里要改，如果某30字母单词缩写后正好等于word中某20字母单词
                continue;
            docCopy[m][n]=alphaSpace[index];
            n++;
        }
        else if(alphaSpace[index]==' '){
            docCopy[m][n]='\0';
            m++;
            n=0;
        }
        else if(alphaSpace[index]=='\0'){
            docCopy[m][n]='\0';
            m++;
            strcpy(docCopy[m],"");
            break;
        }
        index++;
    }
}

/*
 Remove punctuations in document
 count the number of words in document
 */

int removePunc(const char document[],char alphaSpace[]){
    
    if(document[0]=='\0')
        return 0;
    
    int index=0,i=0;
    int wordCount=0;
    while(true){
        
        //read an alpha
        if(isalpha(document[index])){
            alphaSpace[i]=tolower(document[index]);
            i++;
        }
        //read a space
        else if(document[index]==' '){
            if(i>0&&isalpha(alphaSpace[i-1])){ //if not the first character
                alphaSpace[i]=document[index];//copy the space, but at most copy one
                wordCount++;
                i++;
            }
        }
        else if(document[index]=='\0'){
            alphaSpace[i]='\0';
            if(i>0&&isalpha(alphaSpace[i-1])){
                wordCount++;
            }
            break;
        }
        index++;
    }
    return wordCount;
}
 


  

 






