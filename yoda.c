#include <stdio.h>
#include <stddef.h>

void *malloc(size_t size);

int pos(const char* const sentence, int len){
  if(*(sentence+len)==' ') return len+1;
  else return pos(sentence,len-1);
}

int lenstr(const char* const sentence){
  if (*sentence == '\0') return 0;
   else return 1 + lenstr(sentence + 1);
}

char *write(const char* const sentence, char *help_array, int len, int last_space_pos, int i){
  // erstes Wort schreiben
  if(i+1<len-last_space_pos){
    help_array[i]=(sentence[last_space_pos+i]);
    return write(sentence, help_array, len, last_space_pos, i+1);
  // Leerzeichen nach erstem Wort
  } else if(len-last_space_pos-i-1==0){
    help_array[i]=' ';
    return write(sentence, help_array, len, last_space_pos, i+1);
  // Rest des Strings
} else if(i+1<len && i>=len-last_space_pos) {
    help_array[i]=(sentence[last_space_pos+i-len]);
    return write(sentence, help_array, len, last_space_pos, i+1);
  // Satzzeichen
  } else {
    help_array[i]=(sentence[len-1]);
    return help_array;
  }
}

char *upper_lower(char *help_array, int len, int last_space_pos){
  help_array[0]-=32;
  help_array[len-last_space_pos]+=32;
  return help_array;
}

char *yoda(const char * const sentence){
  int len=lenstr(sentence);
  int last_space_pos=pos(sentence, len);

  char *help_array=(char*) malloc (len+1);
  help_array=write(sentence, help_array, len, last_space_pos, 0);
  help_array=upper_lower(help_array, len, last_space_pos);

  return help_array;
}

int main(){
  printf("%s", yoda(" "));
}
