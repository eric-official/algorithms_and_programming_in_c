#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int lenstr(char* sentence){ //bestimmt laenge des strings
  if (*sentence == '\0') return 0;
   else return 1 + lenstr(sentence + 1);
}

char *no_space(char *arr){ //entfernt leerzeichen
  int x=lenstr(arr);
  int idx=0;
  for(int i=0;i<x-2;i++){
    if(*(arr+i)!=' '){
      idx++;
    }
  }
  char *help_array=(char*) malloc (idx+1);
  idx=0;
  for(int i=0;i<x;i++){
    if(*(arr+i)!=' '){
      help_array[idx]=arr[i];
      idx++;
    }
  }
  return help_array;
}

char *upper_lower(char *arr){ //konvertiert grosse buchstaben zu kleinen
  int x=lenstr(arr);
  for(int i=0;i<x;i++){
    if(arr[i]>=65 && arr[i]<=90) arr[i]+=32;
  }
  return arr;
}

int loc_char(char *string, char c){
  int counter=0;
  while(*(string+counter)!=c) counter++;
  return counter;
}

int checker(char *string1, char *string2){
  char helpstring1[lenstr(string1)];
  strcpy(helpstring1,string1);
  char helpstring2[lenstr(string2)];
  strcpy(helpstring2,string2);
  int counter=0;
  for(int i=0;i<lenstr(helpstring1);i++){
    for(int j=0;j<lenstr(helpstring2);j++){
      if(*(helpstring1+i)==*(helpstring2+j) && *(helpstring1+i)!=' ' && *(helpstring2+j)!=' '){
        helpstring1[i]=' ';
        helpstring2[j]=' ';
        counter++;
      }
    }
  }
  return counter;
}

void swap_arr_rows(char** str1, char** str2) {
    char* temp;
    temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

int space_counter(char *string){
  int counter=0;
  for(int i=0;i<lenstr(string);i++){
    if(*(string+i)==' ') counter++;
  }
  return counter;
}

char *sort(char *string){
  int spacecounter=0;
  int i, j;
  for(i=0; i<lenstr(string);i++){
    if(string[i]==' '){
      spacecounter++;
    }
  }
  i=0;
  char *words[spacecounter];
  char *token;
  token = strtok(string, " ");
  while( token != NULL ) {
    words[i]=token;
    token = strtok(NULL, " ");
    i++;
  }
  for(i=0;i<spacecounter;i++){
    for(j=i+1;j<spacecounter;j++){
      if(strcmp(words[i],words[j])>0){
        swap_arr_rows(words+i, words+j);
      }
    }
  }
  char *newstr=(char*)malloc(lenstr(string)+1);
  newstr[0]='\0';
  for(i=0;i<spacecounter;i++){
    strcat(newstr, words[i]);
    strcat(newstr, " ");
  }
  return newstr;
}

int string_in_array(char **string_arr, char *string){
  bool check=1;
  int counter=0;
  while(string_arr[counter][0]!='\0'){
    counter++;
  }
  if(counter==0) check=strcmp((string_arr[counter]), (string));
  else {
    int i=0;
    while(i<counter && check!=0){
      check=strcmp((string_arr[i]), (string));
      i++;
    }
  }
  return check;
}

char *anagram(char *string, char **string_arr, int arg){
  char helpstring[lenstr(string)];
  int counter=0;
  strcpy(helpstring,string);
  for(int i=0;i<=arg;i++){ //Schleife fuer einzelne argumente aus argv
    if(checker(helpstring, *(string_arr+i))==lenstr(*(string_arr+i))){
      for(int j=0;j<lenstr(*(string_arr+i));j++){ //Schleife um laenge von anagramstring ermitteln
        counter++;
      }
      counter++;
    }
  }
  char *anagrams=(char*)malloc(counter+1);
  anagrams[0]='\0';
  for(int i=0;i<=arg;i++){ //Schleife fuer einzelne argumente aus argv
    if(checker(helpstring, *(string_arr+i))==lenstr(*(string_arr+i))){
      for(int j=0;j<lenstr(*(string_arr+i));j++){ //Schleife um leerzeichen in string zu setzen
        int location=loc_char(helpstring, *(string_arr[i]+j));
        helpstring[location]=' ';
      }
      strcat(anagrams, *(string_arr+i));
      strcat(anagrams, " ");
      i=0;
    }
  }
  if(space_counter(helpstring)==lenstr(string)){
    return anagrams;
  } else {
    return NULL;
  }
}

void mixer(char *string, char **string_arr, int idx, int arg, int counter, char **result_arr){
  int i;
  if (idx == arg) {
    if(anagram(string,string_arr, arg)!=NULL && string_in_array(result_arr, sort(anagram(string, string_arr, arg)))!=0){
      while(result_arr[counter][0]!='\0'){
        counter++;
      }
      strcpy(result_arr[counter], sort(anagram(string,string_arr, arg)));
    }
  } else {
    for (i=idx;i<=arg;i++){
      swap_arr_rows((string_arr+idx), (string_arr+i));
      mixer(string, string_arr, idx+1, arg, counter, result_arr);
      swap_arr_rows((string_arr+idx), (string_arr+i)); //backtrack
    }
  }
}

int main(int argc, char **argv){
  //arrays aus argv erstellen
  char *first_array=*(argv+1);
  char *second_array[argc-2];
  char *anagramhelper[argc-2];
  int i;
  for(i=0;i<argc-2;i++){
    anagramhelper[i]=(char*)malloc(lenstr(argv[i+2]));
    strcpy(anagramhelper[i],argv[i+2]);
  }
  for(i=0;i<argc-2;i++){
    *(second_array+i)=*(argv+i+2);
  }
  //grosse zu kleine zeichen
  char *first_array_lower=no_space(upper_lower(first_array));
  char *second_array_lower[argc-2];
  for(i=0;i<argc-2;i++){
    second_array_lower[i]=upper_lower(second_array[i]);
  }
  //checken, ob woerter in anagram
  int counter=0;
  for(i=0;i<argc-2;i++){
    if(checker(first_array_lower, *(second_array_lower+i))==lenstr(*(second_array_lower+i))){
      counter++;
    }
  }
  //array ohne sinnlose woerter erstellen
  char *small_array[counter];
  counter=0;
  for(i=0;i<argc-2;i++){
    if(checker(first_array_lower, *(second_array_lower+i))==lenstr(*(second_array_lower+i))){
      *(small_array+counter)=*(second_array_lower+i);
      counter++;
    }
  }
  char **result_arr;
  result_arr =(char**) malloc(50 * sizeof(char*));
  for (int i = 0; i < 50; i++){
    result_arr[i] =(char*) malloc((100) * sizeof(char));
  }
  mixer(first_array_lower, small_array, 0, counter-1, 0, result_arr);
  i=0;
  while(result_arr[i][0]!='\0'){
    char comparestring[lenstr(result_arr[i])];
    comparestring[0]='\0';
    char helper[lenstr(result_arr[i])];
    strcpy(helper,result_arr[i]);
    /*for(int j=0;j<argc-2;j++){
      if(strstr(helper, upper_lower(second_array[j]))!=NULL){
        comparestring=strstr(helper, upper_lower(second_array[j]));
        if(lenstr(comparestring)==lenstr(result_arr[i])){
          strncpy(comparestring, anagramhelper[j], lenstr(anagramhelper[j]));
          strcpy(result_arr[i],comparestring);
          j--;
        }
      }
    }*/
    char *words[space_counter(result_arr[i])];
    char *token;
    int x=0;
    token = strtok(helper, " ");
    while( token != NULL ) {
      words[x]=token;
      token = strtok(NULL, " ");
      x++;
    }
    for(int k=0;k<x;k++){ //schleife fuer words
      for(int m=0;m<argc-2;m++){ //schleife fuer result_arr
        if(strcmp(words[k],second_array[m])==0){
          strcat(comparestring, anagramhelper[m]);
          strcat(comparestring, " ");
        }
      }
    }
    //printf("com: %s\n", comparestring);
    strcpy(result_arr[i],comparestring);
    printf("%s\n", result_arr[i]);
    i++;
  }
  printf("===\n");
  for(i=0;i<argc-2;i++){
    free(anagramhelper[i]);
  }
  free(result_arr);
  free(first_array_lower);
}
