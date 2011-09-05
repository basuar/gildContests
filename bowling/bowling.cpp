#include<stdio.h>
#include<unistd.h>
inline unsigned int gS(const char*b,const unsigned int*s,unsigned int n){unsigned int r=b[n*2];if(__builtin_expect(r=='X',0))return 10;else if(__builtin_expect(r=='/',0))return (10-s[n-1]);else return (r-'0');}
int main(int c,char**a){FILE*f=fopen(a[1],"r");char b[64],*p=b;size_t z=64;while(getline(&p,&z,f)!=-1){unsigned int s[22];register unsigned int tS=0,f=0,c=0,i=0;s[0]=b[0]=='X'?10:b[0]-'0';s[1]=gS(b,s,1);
while(f<10){s[i+2]=gS(b,s,i+2);tS+=s[i];if(c){if(__builtin_expect(((s[i-1]+s[i])==10U),0))tS+=s[i+1];++f;c=0;}else if(__builtin_expect((s[i]==10U),0)){tS+=s[i+1]+s[i+2];++f;}else{c=1;}++i;}printf("%d\n",tS);}fflush(stdout);_exit(0);}
