#include<stdio.h>
inline int gs(char* b,int*s,int n){int r=b[n<<1];if(__builtin_expect(r=='X',0))return 10;if(__builtin_expect(r>'/',1))return(r-'0');return(10-s[n-1]);}
int main(int c,char**a){FILE* f=fopen(a[1],"r");char b[64],*p=b;size_t z=64;
while(getline(&p,&z,f)!=-1){int s[22],t=0,f=0,c=0,i=0;s[0]=b[0]=='X'?10:b[0]-'0';s[1]=gs(b,s,1);
while(f<10){s[i+2]=gs(b,s,i+2);t+=s[i];if(c){if((s[i-1]+s[i])==10)t+=s[i+1];++f;c=0;}else if(s[i]==10){t+=s[i+1]+s[i+2];++f;}else c=1;++i;}printf("%d\n",t);}}
