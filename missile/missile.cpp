#include <cstdio>
#include <deque>
int main(int,char** a){register int h,u,v;std::deque<int> m,b;FILE* f=fopen(a[1],"r");
while(!feof(f)){fscanf(f,"%u",&h);m.push_back(h);}b.push_back(0);
for(size_t i=1;i<m.size();++i){if(m[b.back()]<m[i]){b.push_back(i);continue;}
for(u=0,v=b.size()-1;u<v;){register const int c=(u+v)/2;if(m[b[c]]<m[i])u=c+1;else v=c;}if(m[i]<m[b[u]])b[u]=i;}
printf("%u\n",b.size());return 0;}
