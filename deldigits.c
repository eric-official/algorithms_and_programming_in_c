unsigned combine(unsigned num1, unsigned num2){
  if(num2==0) return num1;
  else {
    num1=num1*10+num2%10;
    return combine(num1, num2/10);
  }
}

unsigned deldigits(unsigned num, unsigned short div){
  if(num==0) return 0;
  else {
    if((num%10)%div==0) return deldigits(num/10, div);
    else {
      return combine(deldigits(num/10, div), num%10);
    }
  }
}
