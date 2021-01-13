#include <stdlib.h>
#include <stdio.h>

int lenstr(char* string){ //bestimmt laenge des strings
  int counter=0;
  while(string[counter]!='\0') counter++;
  return counter;
}



int is_comma(char *string){
  int checker=0; //1 komma da, 0 komma nicht da
  int counter=0;
  while(string[counter]!='\0'){
    if(string[counter]==',') checker=1;
    //else checker=0;
    counter++;
  }
  return checker;
}



int loc_comma(char *string){
  int counter=0;
  while(string[counter]!=',' && string[counter]!='\0') counter++;
  return counter;
}



char* pre_comma_part(char *string){
  char *part=(char*) malloc (loc_comma(string)+1);
  for(int i=0;i<loc_comma(string);i++){
    part[i]=string[i];
  }
  part[loc_comma(string)]='\0';
  return part;
}



char* post_comma_part(char *string){
  char* part=(char*) malloc (lenstr(string)-loc_comma(string));
  char* ifnull=(char*) malloc(2);
  int counter=loc_comma(string)+1;
  if(is_comma(string)==0){
    ifnull[0]='0';
    ifnull[1]='\0';
    free(part);
    return ifnull;
  } else {
    for(int i=0;i<lenstr(string)-loc_comma(string)-1;i++){
      part[i]=string[counter];
      counter++;
    }
    part[lenstr(string)-loc_comma(string)-1]='\0';
    free(ifnull);
    return part;
  }
}

int compare(char* num1, char* num2){
  int counter=0;
  int res=0;
  while(num1[counter] && num2[counter] && res==0){
    if(((int)(num1[counter])-'0')>((int)(num2[counter])-'0')){
      res=1;
      counter++;
    } else if(((int)(num1[counter])-'0')<((int)(num2[counter])-'0')) {
      res=2;
      counter++;
    } else {
      res=0;
      counter++;
    }
  }
  return res;
}

char* add(char* pre_num1, char* post_num1, char* pre_num2, char* post_num2){
  int i=0;
  int temp_overflow=0;
  int temp_res;
  int longer; //0-->gleichlang 1-->post_num1 laenger 2-->post_num2 laenger
  int short_length;
  int pos=0;
  int pre_num1_len=lenstr(pre_num1);
  int post_num1_len=0;
  int pre_num2_len=lenstr(pre_num2);
  int post_num2_len=0;
  int res_post_len=0;
  int res_pre_len=0;

  if(post_num1!=0){
    post_num1_len=lenstr(post_num1);
  } else {
    post_num1="0";
    post_num1_len=lenstr(post_num1);
  }
  if(post_num2!=0) {
    post_num2_len=lenstr(post_num2);
  } else {
    post_num2="0";
    post_num2_len=lenstr(post_num2);
  }

  if(pre_num2[0]=='-'){ //minus eliminieren
    for(i=0;i<pre_num2_len-1;i++){
      pre_num2[i]=pre_num2[i+1];
    }
    pre_num2[i]='\0';
  }

  if(post_num1_len==post_num2_len){ //laengen von nachkommastellen bestimmen
    longer=0;
    short_length=post_num1_len;
    res_post_len=post_num1_len;
  }else if(post_num1_len>post_num2_len){
    longer=1;
    short_length=post_num2_len;
    res_post_len=post_num1_len;
  }else if(post_num1_len<post_num2_len){
    longer=2;
    short_length=post_num1_len;
    res_post_len=post_num2_len;
  }

  if(pre_num1_len==pre_num2_len){
    res_pre_len=pre_num1_len;
  }else if(pre_num1_len>pre_num2_len){
    res_pre_len=pre_num1_len;
  }else if(pre_num1_len<pre_num2_len){
    res_pre_len=pre_num2_len;
  }

  char* res=(char*) malloc(res_pre_len+res_post_len+3); //platz für überlauf, komma und abschließende null reserviert
  res[res_pre_len+res_post_len+2]='\0';
  res[res_pre_len+1]=',';
  pos=short_length-1;
  for(i=res_pre_len+1+short_length;i>res_pre_len+1;i--,pos--){ //addition ab letztem möglichen element
    temp_res=((int)(post_num1[pos]-'0') + (int)(post_num2[pos]-'0')+temp_overflow);
    if(temp_res<=8){ //zwischenergebnis in res schreiben
      temp_overflow=0;
      res[i]=temp_res+'0';
    }else if(temp_res>8){
      temp_overflow=1;
      res[i]=temp_res%9+'0';
    }
  }
  pos=short_length;

  if(longer==1){  //falls nötig restliche zahlen in array schreiben
    for(i=res_pre_len+short_length+2;i<res_pre_len+res_post_len+2;i++,pos++){ //restliche zahlen auffüllen
      res[i]=post_num1[pos];
    }
  }else if(longer==2){
    for(i=res_pre_len+short_length+2;i<res_pre_len+res_post_len+2;i++,pos++){ //restliche zahlen auffüllen
      res[i]=post_num2[pos];
    }
  }

  //jetzt kommen die vorkommastellen
  int new_len=0; //laenge von neuem array bestimmen
  if(pre_num1_len==pre_num2_len){
    longer=0;
    short_length=pre_num1_len;
    new_len=pre_num1_len;
  }else if(pre_num1_len>pre_num2_len){
    longer=1;
    short_length=pre_num1_len;
    new_len=pre_num1_len;
  }else if(pre_num1_len<pre_num2_len){
    longer=2;
    short_length=pre_num2_len;
    new_len=pre_num2_len;
  }

  char* new_pre=(char*) malloc(new_len+1);
  if(longer==0){
    free(new_pre);
  }else if(longer==1){
    for(i=0;i<(pre_num1_len-pre_num2_len);i++){
      new_pre[i]='0';
    }
    for(i=(pre_num1_len-pre_num2_len);i<pre_num1_len;i++){
      new_pre[i]=pre_num2[i-(pre_num1_len-pre_num2_len)];
    }
    new_pre[new_len]='\0';
  }else if(longer==2){
    for(i=0;i<(pre_num2_len-pre_num1_len);i++){
      new_pre[i]='0';
    }
    for(i=(pre_num2_len-pre_num1_len);i<pre_num2_len;i++){
      new_pre[i]=pre_num1[i-(pre_num2_len-pre_num1_len)];
    }
    new_pre[new_len]='\0';
  }

  for(i=res_pre_len;i>=1;i--){ //addition ab letztem möglichen element
    if(longer==0){
      temp_res=((int)(pre_num1[i-1]-'0') + (int)(pre_num2[i-1]-'0')+temp_overflow);
    }else if(longer==1){
      temp_res=((int)(pre_num1[i-1]-'0') + (int)(new_pre[i-1]-'0')+temp_overflow);
    }else if(longer==2){
      temp_res=((int)(new_pre[i-1]-'0') + (int)(pre_num2[i-1]-'0')+temp_overflow);
    }
    if(temp_res<=8){ //zwischenergebnis in res schreiben
      temp_overflow=0;
      res[i]=temp_res+'0';
    }else if(temp_res>8){
      temp_overflow=1;
      res[i]=temp_res%9+'0';
    }
  }

  //überlauf für erste stelle
  if(temp_overflow==0) res[0]='0';
  else if(temp_overflow==1) res[0]='1';

  //überflüssige nullen löschen
  int x=0;
  while(res[x]=='0'){
    for(int y=x;y<lenstr(res);y++){
      res[y]=res[y+1];
    }
    res[lenstr(res)]='\0';
  }
  x=lenstr(res)-1;
  while(res[x]=='0'){
    res[x]='\0';
    x--;
  }

  if(res[lenstr(res)-1]==',') res[lenstr(res)-1]='\0';
  if(longer!=0) free(new_pre);
  return res;
}


char* multiply(char* pre_num1, char* post_num1, char* pre_num2, char* post_num2){
  int minus_status=0;
  int pre_num1_len=lenstr(pre_num1);
  int post_num1_len=0;
  int pre_num2_len=lenstr(pre_num2);
  int post_num2_len=0;
  int i=0;
  int j=0;
  int x=0;
  int current_digit;

  if(post_num1!=0){
    post_num1_len=lenstr(post_num1);
  }
  if(post_num2!=0) {
    post_num2_len=lenstr(post_num2);
  }

  if(pre_num1[0]=='-'){ //minus eliminieren
    minus_status++;
    for(i=0;i<pre_num1_len-1;i++){
      pre_num1[i]=pre_num1[i+1];
    }
    pre_num1[i]='\0';
    pre_num1_len--;
  }

  if(pre_num2[0]=='-'){ //minus eliminieren
    minus_status++;
    for(i=0;i<pre_num2_len-1;i++){
      pre_num2[i]=pre_num2[i+1];
    }
    pre_num2[i]='\0';
    pre_num2_len--;
  }

  char* num1=(char*)malloc(pre_num1_len+post_num1_len+1);
  for(i=0; i<pre_num1_len+post_num1_len; i++){
    if(i<pre_num1_len){
      num1[i]=pre_num1[i];
    } else if(i>=pre_num1_len) {
      num1[i]=post_num1[i-pre_num1_len];
    }
  }
  num1[pre_num1_len+post_num1_len]='\0';
  int num1_len=lenstr(num1);

  char* num2=(char*)malloc(pre_num2_len+post_num2_len+1);
  for(i=0; i<pre_num2_len+post_num2_len; i++){
    if(i<pre_num2_len){
      num2[i]=pre_num2[i];
    } else if(i>=pre_num2_len) {
      num2[i]=post_num2[i-pre_num2_len];
    }
  }
  num2[pre_num2_len+post_num2_len]='\0';
  int num2_len=lenstr(num2);


  char sum_array[pre_num2_len+post_num2_len][num1_len+post_num2_len+2]; //platz für nullen, overflow und abschlussnull
  char temp_sum[num1_len+2];
  int pos=0;
  for(i=num2_len-1;i>=0;i--){ //für jede ziffer von num2
    current_digit=(int)(num2[i]-'0');
    for(j=0;j<num1_len+1;j++){
      temp_sum[j]='0';
    }
    temp_sum[num1_len+1]='\0';
    if(current_digit==1){ //falls Ziffer 1 --> Produkt ist num1
      for(j=0;j<lenstr(num1);j++){
        temp_sum[j]=num1[j];
      }
      temp_sum[lenstr(num1)]='\0';

    } else if(current_digit>1) {
      for(j=2;j<=current_digit+1;j++){
        char* helper=(char*) malloc(num1_len+2);
        helper=add(temp_sum, "0", num1, "0");

        for(x=0;x<lenstr(helper);x++){
          temp_sum[num1_len-x]=helper[lenstr(helper)-1-x];
        }
        free(helper);
      }
    }

    x=0;
    for(j=0;j<num1_len+post_num2_len+1;j++){ //array mit nullen auffüllen
      sum_array[pos][j]='0';
    }
    sum_array[pos][num1_len+post_num2_len+1]='\0';

    for(j=num1_len+post_num2_len;j>num1_len+post_num2_len-lenstr(temp_sum);j--){
      sum_array[pos][j-pos]=temp_sum[lenstr(temp_sum)-1-x];
      x++;
    }
    sum_array[pos][num1_len+post_num2_len+1]='\0';
    pos++;
  }

  pos=0;
  i=0;
  x=0;
  j=0;
  char* res=(char*) malloc(num1_len+num2_len+3); //platz für minus, overflow, komma und abschlussnull
  res[num1_len+num2_len+2]='\0';

  //summen der spalten bilden
  int temp_overflow=0;
  int temp_res=0;
  pos=num1_len+num2_len+1;
  for(j=num1_len+post_num2_len;j>=0;j--){ //iterator für spalten
    temp_res=0;
    for(i=0;i<num2_len;i++){ //iterator für zeilen
      temp_res=((int)(sum_array[i][j]-'0') + temp_res +temp_overflow);
      if(temp_res<=8){ //zwischenergebnis in res schreiben
        temp_overflow=0;
        //res[i]=temp_res+'0';
      }else if(temp_res>8){
        temp_overflow=1;
        temp_res=temp_res%9;
      }
    }
    if(pos>pre_num1_len+pre_num2_len+1 || pos<pre_num1_len+pre_num2_len){
      res[pos]=temp_res+'0';
      pos--;
    } else if(pos==pre_num1_len+pre_num2_len+1){
      pos--;
      res[pos]=temp_res+'0';
      pos--;
    }
  }

  res[pre_num1_len+pre_num2_len+1]=',';
  res[1]=temp_overflow+'0';
  i=0;

  //überflüssige nullen löschen
  x=1;
  while(res[x]=='0' || res[x]<48 || res[x]>56){
    for(i=x;i<lenstr(res);i++){
      res[i]=res[i+1];
    }
    res[lenstr(res)]='\0';
  }
  x=lenstr(res)-1;
  while(res[x]=='0'){
    res[x]='\0';
    x--;
  }
  i=0;
  x=0;
  if(minus_status==1) res[0]='-';
  else {
    for(i=0;i<lenstr(res);i++){
      res[i]=res[i+1];
    }
    res[lenstr(res)]='\0';
  }

  if(res[lenstr(res)-1]==',') res[lenstr(res)-1]='\0';
  for(i=0;i<lenstr(res);i++){
  }
  free(num1);
  free(num2);
  return res;
}



char* sub(char* pre_num1, char* post_num1, char* pre_num2, char* post_num2){
  int pre_num1_len=lenstr(pre_num1);
  int post_num1_len=0;
  int pre_num2_len=lenstr(pre_num2);
  int post_num2_len=0;
  int pre_num1_int=0; //zahlen als int zum vergleichen
  int post_num1_int=0;
  int pre_num2_int=0;
  int post_num2_int=0;
  int minus_status=0;
  int num1_minus=0; // ist bei zahl1 ein minus
  int num2_minus=0; // ist bei zahl2 ein minus
  int zehner=1;
  int i=0;

  if(post_num1!=0){
    post_num1_len=lenstr(post_num1);
  } else {
    post_num1="0";
    post_num1_len=lenstr(post_num1);
  }
  if(post_num2!=0) {
    post_num2_len=lenstr(post_num2);
  } else {
    post_num2="0";
    post_num2_len=lenstr(post_num2);
  }

  if(pre_num1[0]=='-'){ //minus eliminieren
    minus_status++;
    num1_minus=1;
    for(i=0;i<pre_num1_len-1;i++){
      pre_num1[i]=pre_num1[i+1];
    }
    pre_num1[i]='\0';
    pre_num1_len--;
  }

  if(pre_num2[0]=='-'){ //minus eliminieren
    minus_status++;
    //num2_minus=1;
    for(i=0;i<pre_num2_len-1;i++){
      pre_num2[i]=pre_num2[i+1];
    }
    pre_num2[i]='\0';
    pre_num2_len--;
  }

  for(i=pre_num1_len-1;i>=0;i--){
    pre_num1_int=pre_num1_int+(int)(pre_num1[i]-'0')*zehner;
    zehner*=10;
  }
  zehner=1;
  for(i=post_num1_len-1;i>=0;i--){
    post_num1_int=post_num1_int+((int)(post_num1[i]-'0'))*zehner;
    zehner*=10;
  }
  zehner=1;
  for(i=pre_num2_len-1;i>=0;i--){
    pre_num2_int=pre_num2_int+((int)(pre_num2[i]-'0'))*zehner;
    zehner*=10;
  }
  zehner=1;
  for(i=post_num2_len-1;i>=0;i--){
    post_num2_int=post_num2_int+((int)(post_num2[i]-'0'))*zehner;
    zehner*=10;
  }
  zehner=1;


  char* temp_char;
  int temp_int;
  int swap=0;
  if((pre_num2_int>pre_num1_int) || (pre_num2_int==pre_num1_int && compare(post_num1,post_num2)==2)){ //zahlen der größe nach ordnen falls nötig
    temp_char = pre_num1;
    pre_num1 = pre_num2;
    pre_num2 = temp_char;

    temp_int=pre_num1_len;
    pre_num1_len=pre_num2_len;
    pre_num2_len=temp_int;

    temp_int=pre_num1_int;
    pre_num1_int=pre_num2_int;
    pre_num2_int=temp_int;

    temp_int=num1_minus;
    num1_minus=num2_minus;
    num2_minus=temp_int;

    temp_char = post_num1;
    post_num1 = post_num2;
    post_num2 = temp_char;

    temp_int=post_num1_len;
    post_num1_len=post_num2_len;
    post_num2_len=temp_int;

    temp_int=post_num1_int;
    post_num1_int=post_num2_int;
    post_num2_int=temp_int;
    swap=1;
  }

  int res_post_len;
  int res_pre_len;
  int longer;
  if(post_num1_len==post_num2_len){ //laengen von nachkommastellen bestimmen
    longer=0;
    res_post_len=post_num1_len;
  }else if(post_num1_len>post_num2_len){
    longer=1;
    res_post_len=post_num1_len;
  }else if(post_num1_len<post_num2_len){
    longer=2;
    res_post_len=post_num2_len;
  }

  if(pre_num1_len==pre_num2_len){
    res_pre_len=pre_num1_len;
  }else if(pre_num1_len>pre_num2_len){
    res_pre_len=pre_num1_len;
  }else if(pre_num1_len<pre_num2_len){
    res_pre_len=pre_num2_len;
  }


  char* new_post=(char*) malloc(res_post_len+1); //bei ungleicher länge mit nullen auffüllen
  if(longer==0){
    free(new_post);
  }else if(longer==1){
    for(i=res_post_len-1;i>post_num2_len-1;i--){
      new_post[i]='0';
    }
    for(i=post_num2_len-1;i>=0;i--){
      new_post[i]=post_num2[i];
    }
    new_post[res_post_len]='\0';
  }else if(longer==2){
    for(i=res_post_len-1;i>post_num1_len-1;i--){
      new_post[i]='0';
    }
    for(i=post_num1_len-1;i>=0;i--){
      new_post[i]=post_num1[i];
    }
    new_post[res_post_len]='\0';
  }

  char* res=(char*) malloc(res_pre_len+res_post_len+3); //platz für vorzeichen, komma und abschließende null reserviert
  res[res_pre_len+res_post_len+2]='\0';
  res[res_pre_len+1]=',';
  int temp_res;
  int temp_overflow=0;
  int pos=res_pre_len+res_post_len+1;
  for(i=res_post_len-1;i>=0;i--,pos--){ //addition ab letztem möglichen element
    if(longer==0){
      temp_res=((int)(post_num1[i]-'0') - (int)(post_num2[i]-'0')-temp_overflow);
    }else if(longer==1){
      temp_res=((int)(post_num1[i]-'0') - (int)(new_post[i]-'0')-temp_overflow);
    }else if(longer==2){
      temp_res=((int)(new_post[i]-'0') - (int)(post_num2[i]-'0')-temp_overflow);
    }
    if(temp_res>=0){ //zwischenergebnis in res schreiben
      temp_overflow=0;
      res[pos]=temp_res+'0';
    }else if(temp_res<0){
      temp_overflow=1;
      res[pos]=temp_res+9+'0';
    }
  }
  if(longer!=0) free(new_post);


  if(pre_num1_len==pre_num2_len){
    longer=0;
  }else if(pre_num1_len>pre_num2_len){
    longer=1;
  }else if(pre_num1_len<pre_num2_len){
    longer=2;
  }


  char* new_pre=(char*) malloc(res_pre_len+1); //bei ungleicher länge mit nullen auffüllen
  if(longer==0){
    free(new_pre);
  }else if(longer==1){
    for(i=0;i<(pre_num1_len-pre_num2_len);i++){
      new_pre[i]='0';
    }
    for(i=(pre_num1_len-pre_num2_len);i<pre_num1_len;i++){
      new_pre[i]=pre_num2[i-(pre_num1_len-pre_num2_len)];
    }
    new_pre[res_pre_len]='\0';
  }else if(longer==2){
    for(i=0;i<(pre_num2_len-pre_num1_len);i++){
      new_pre[i]='0';
    }
    for(i=(pre_num2_len-pre_num1_len);i<pre_num2_len;i++){
      new_pre[i]=pre_num1[i-(pre_num2_len-pre_num1_len)];
    }
    new_pre[res_pre_len]='\0';
  }

  pos=res_pre_len;
  for(i=res_pre_len-1;i>=0;i--,pos--){ //addition ab letztem möglichen element
    if(longer==0){
      temp_res=((int)(pre_num1[i]-'0') - (int)(pre_num2[i]-'0')-temp_overflow);
    }else if(longer==1){
      temp_res=((int)(pre_num1[i]-'0') - (int)(new_pre[i]-'0')-temp_overflow);
    }else if(longer==2){
      temp_res=((int)(new_pre[i]-'0') - (int)(pre_num2[i]-'0')-temp_overflow);
    }
    if(temp_res>=0){ //zwischenergebnis in res schreiben
      temp_overflow=0;
      res[pos]=temp_res+'0';
    }else if(temp_res<0){
      temp_overflow=1;
      res[pos]=temp_res+9+'0';
    }
  }
  if(longer!=0) free(new_pre);

  int x=1;
  while(res[x]=='0' && res_pre_len>=2){
    for(int y=x;y<res_pre_len+res_post_len+1;y++){
      res[y]=res[y+1];
    }
    res[res_pre_len+res_post_len+1]='\0';
    res_pre_len--;
  }
  x=res_pre_len+res_post_len+1;
  while(res[x]=='0'){
    res[x]='\0';
    x--;
  }

  int end_minus=swap+temp_overflow+num1_minus+num2_minus; //wenn ungerade --> negatives vorzeichen, wenn gerade --> positives
  if(end_minus%2!=0){
    res[0]='-';
  }else if(end_minus%2==0){
    for(i=0;i<res_pre_len+res_post_len+1;i++){
      res[i]=res[i+1];
    }
    res[res_pre_len+res_post_len+1]='\0';
  }

  if(res[lenstr(res)-1]==',') res[lenstr(res)-1]='\0';

  return res;
}



char* sub_add(char* pre_num1, char* post_num1, char* pre_num2, char* post_num2){
  int pre_num1_len=lenstr(pre_num1);
  int post_num1_len=0;
  int pre_num2_len=lenstr(pre_num2);
  int post_num2_len=0;
  int i=0;

  if(post_num1!=0){
    post_num1_len=lenstr(post_num1);
  } else {
    post_num1="0";
    post_num1_len=lenstr(post_num1);
  }
  if(post_num2!=0) {
    post_num2_len=lenstr(post_num2);
  } else {
    post_num2="0";
    post_num2_len=lenstr(post_num2);
  }

  if(pre_num1[0]=='-'){ //minus eliminieren
    for(i=0;i<pre_num1_len-1;i++){
      pre_num1[i]=pre_num1[i+1];
    }
    pre_num1[i]='\0';
    pre_num1_len--;
  }

  if(pre_num2[0]=='-'){ //minus eliminieren
    for(i=0;i<pre_num2_len-1;i++){
      pre_num2[i]=pre_num2[i+1];
    }
    pre_num2[i]='\0';
    pre_num2_len--;
  }

  int res_post_len;
  int res_pre_len;
  int longer;
  if(post_num1_len==post_num2_len){ //laengen von nachkommastellen bestimmen
    longer=0;
    res_post_len=post_num1_len;
  }else if(post_num1_len>post_num2_len){
    longer=1;
    res_post_len=post_num1_len;
  }else if(post_num1_len<post_num2_len){
    longer=2;
    res_post_len=post_num2_len;
  }

  if(pre_num1_len==pre_num2_len){
    res_pre_len=pre_num1_len;
  }else if(pre_num1_len>pre_num2_len){
    res_pre_len=pre_num1_len;
  }else if(pre_num1_len<pre_num2_len){
    res_pre_len=pre_num2_len;
  }


  char* new_post=(char*) malloc(res_post_len+1); //bei ungleicher länge mit nullen auffüllen
  if(longer==0){
    free(new_post);
  }else if(longer==1){
    for(i=res_post_len-1;i>post_num2_len-1;i--){
      new_post[i]='0';
    }
    for(i=post_num2_len-1;i>=0;i--){
      new_post[i]=post_num2[i];
    }
    new_post[res_post_len]='\0';
  }else if(longer==2){
    for(i=res_post_len-1;i>post_num1_len-1;i--){
      new_post[i]='0';
    }
    for(i=post_num1_len-1;i>=0;i--){
      new_post[i]=post_num1[i];
    }
    new_post[res_post_len]='\0';
  }

  char* res=(char*) malloc(res_pre_len+res_post_len+4); //platz für vorzeichen, überlauf, komma und abschließende null reserviert
  res[res_pre_len+res_post_len+3]='\0';
  res[res_pre_len+2]=',';
  int temp_res;
  int temp_overflow=0;
  int pos=res_pre_len+res_post_len+2;
  for(i=res_post_len-1;i>=0;i--,pos--){ //addition ab letztem möglichen element
    if(longer==0){
      temp_res=((int)(post_num1[i]-'0') + (int)(post_num2[i]-'0')+temp_overflow);
    }else if(longer==1){
      temp_res=((int)(post_num1[i]-'0') + (int)(new_post[i]-'0')+temp_overflow);
    }else if(longer==2){
      temp_res=((int)(new_post[i]-'0') + (int)(post_num2[i]-'0')+temp_overflow);
    }
    if(temp_res<=8){ //zwischenergebnis in res schreiben
      temp_overflow=0;
      res[pos]=temp_res+'0';
    }else if(temp_res>8){
      temp_overflow=1;
      res[pos]=temp_res%9+'0';
    }
  }
  if(longer!=0) free(new_post);


  if(pre_num1_len==pre_num2_len){
    longer=0;
  }else if(pre_num1_len>pre_num2_len){
    longer=1;
  }else if(pre_num1_len<pre_num2_len){
    longer=2;
  }

  char* new_pre=(char*) malloc(res_pre_len+1); //bei ungleicher länge mit nullen auffüllen
  if(longer==0){
    free(new_pre);
  }else if(longer==1){
    for(i=0;i<(pre_num1_len-pre_num2_len);i++){
      new_pre[i]='0';
    }
    for(i=(pre_num1_len-pre_num2_len);i<pre_num1_len;i++){
      new_pre[i]=pre_num2[i-(pre_num1_len-pre_num2_len)];
    }
    new_pre[res_pre_len]='\0';
  }else if(longer==2){
    for(i=0;i<(pre_num2_len-pre_num1_len);i++){
      new_pre[i]='0';
    }
    for(i=(pre_num2_len-pre_num1_len);i<pre_num2_len;i++){
      new_pre[i]=pre_num1[i-(pre_num2_len-pre_num1_len)];
    }
    new_pre[res_pre_len]='\0';
  }

  pos=res_pre_len+1;
  for(i=res_pre_len-1;i>=0;i--,pos--){ //addition ab letztem möglichen element
    if(longer==0){
      temp_res=((int)(pre_num1[i]-'0') + (int)(pre_num2[i]-'0')+temp_overflow);
    }else if(longer==1){
      temp_res=((int)(pre_num1[i]-'0') + (int)(new_pre[i]-'0')+temp_overflow);
    }else if(longer==2){
      temp_res=((int)(new_pre[i]-'0') + (int)(pre_num2[i]-'0')+temp_overflow);
    }
    if(temp_res<=8){ //zwischenergebnis in res schreiben
      temp_overflow=0;
      res[pos]=temp_res+'0';
    }else if(temp_res>8){
      temp_overflow=1;
      res[pos]=temp_res%9+'0';
    }
  }
  if(longer!=0) free(new_pre);
  res[1]=temp_overflow+'0';
  int x=1;
  while(res[x]=='0'){
    for(int y=x;y<res_pre_len+res_post_len+2;y++){
      res[y]=res[y+1];
    }
    res[res_pre_len+res_post_len+2]='\0';
    res_pre_len--;
  }
  x=res_pre_len+res_post_len+2;
  while(res[x]=='0'){
    res[x]='\0';
    x--;
  }
  res[0]='-';

  if(res[lenstr(res)-1]==',') res[lenstr(res)-1]='\0';

  return res;
}



int main(int argc, char *argv[]){
  char* pre_num1=pre_comma_part(argv[argc-3]);
  char* post_num1=post_comma_part(argv[argc-3]);
  char* pre_num2=pre_comma_part(argv[argc-1]);
  char* post_num2=post_comma_part(argv[argc-1]);
  char *target="\0";
  if((argv[2][0]=='+' && argv[1][0]!='-' && argv[3][0]!='-') || (argv[2][0]=='-' && argv[1][0]!='-' && argv[3][0]=='-')){
    target=add(pre_num1, post_num1, pre_num2, post_num2);
  } else if((argv[1][0]!='-' && argv[2][0]=='+' && argv[3][0]=='-') || (argv[1][0]=='-' && argv[2][0]=='+' && argv[3][0]!='-') || (argv[1][0]!='-' && argv[2][0]=='-' && argv[3][0]!='-') || (argv[1][0]=='-' && argv[2][0]=='-' && argv[3][0]=='-')){
    target=sub(pre_num1, post_num1, pre_num2, post_num2);
  } else if((argv[1][0]=='-' && argv[2][0]=='-' && argv[3][0]!='-') || (argv[1][0]=='-' && argv[2][0]=='+' && argv[3][0]=='-')){
    target=sub_add(pre_num1, post_num1, pre_num2, post_num2);
  } else {
    target=multiply(pre_num1, post_num1, pre_num2, post_num2);
  }
  printf("%s\n", target);
  free(target);
  free(pre_num1);
  free(post_num1);
  free(pre_num2);
  free(post_num2);

}
