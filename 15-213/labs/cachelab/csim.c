#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <string.h>
#include "cachelab.h"

typedef long long address_t;
typedef struct{
    bool valid;
    address_t tag;
    int t;
} line_t;

line_t sets[20][16];
int s=0,e=0,b=0;
int mask=0;
address_t get_tag_index(address_t addr){
    return addr>>(s+b);
}

address_t get_set_index(address_t addr){
    return mask&(addr>>b);
}

void update(int i,int ex){
    for(int j=0;j<e;j++)
        if(j!=ex&&sets[i][j].valid)
            sets[i][j].t++;
}

int find_lru(int i){
     int maxx=-1;
     int next_j=0;
     for(int j=0;j<e;j++)
     {
        if(!sets[i][j].valid)
            return j;
        if(maxx<sets[i][j].t)
        {
            maxx=sets[i][j].t;
            next_j=j;
        }
     }
     return next_j;
}

int set_tag(int i,int j,int tag){
    sets[i][j].tag=tag;
    sets[i][j].t=0;
    if(sets[i][j].valid) return 2;
    sets[i][j].valid=true;
    return 1;
}

int check(address_t addr){
    
    address_t i=get_set_index(addr);
    address_t tag=get_tag_index(addr);
    for(int j=0;j<e;j++)
        if(sets[i][j].tag==tag&&sets[i][j].valid){
            sets[i][j].t=0;
            update(i,j);
            return 0;
        }
    int next=find_lru(i);
    update(i,next);
    return set_tag(i,next,tag);
}

void calculate(FILE *stream,int *hit,int *miss,int *eviction,int mode){
    
    char opt='\0';
    address_t addr;
    int bytes;
    do{
        fscanf(stream," ");
        switch (opt)
        {
        case 'I':
            break;
        case 'L':
        case 'M':
        case 'S':
            int output=check(addr);
            if(output==0){
               (*hit)++;
               if(opt=='M'){
                   (*hit)++;
                   if(mode) printf("%c %llx,%d hit hit\n",opt,addr,bytes);
                }else{
                   if(mode) printf("%c %llx,%d hit\n",opt,addr,bytes);
                }
            }else if(output==1){
                (*miss)++;
                if(opt=='M'){
                   (*hit)++;
                   if(mode) printf("%c %llx,%d miss hit\n",opt,addr,bytes);
                }else{
                   if(mode) printf("%c %llx,%d miss\n",opt,addr,bytes);
                }
            }else{
                (*miss)++;(*eviction)++;
                if(opt=='M'){
                   (*hit)++;
                   if(mode) printf("%c %llx,%d miss eviction hit\n",opt,addr,bytes);
                }else{
                   if(mode) printf("%c %llx,%d miss eviction\n",opt,addr,bytes);
                }
            }
            break;
        default:
            break;
        }
    }while (fscanf(stream,"%c %llx,%d\n",&opt,&addr,&bytes)!=EOF);
}

int main(int argc, char *argv[])
{
       
    int ch=0;
    int mode=0;
    char t[200]={0};
    while((ch=getopt(argc,argv,"s:E:b:t:v"))!=-1){
        switch (ch)
        {
        case 's':
            s=atoi(optarg);
            break;
        case 'E':
            e=atoi(optarg);
            break;
        case 'b':
            b=atoi(optarg);
            break;
        case 't':
            strncpy(t,optarg,200);
            break;
        case 'v':
            mode=1;
            break;   
        default:
            break;
        }
    }

    if(!s||!e||!b){
        printf("Please enter correct parameters!");
        exit(-1);
    }

    for(int i=1;i<=s;i++)
        mask=(mask<<1)|1;
    
    FILE *stream=fopen(t,"r");
    if(!stream){
        printf("File Not Exist!\n");
        exit(-1);
    }

    int miss=0,hit=0,eviction=0;
    calculate(stream,&hit,&miss,&eviction,mode);
    
    printSummary(hit, miss, eviction); 
    return 0;
}
