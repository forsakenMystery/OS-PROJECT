int lru8(int pages[],int frames,int size_of_page) {
int page_table[frames][2],index=0,flag=0,pointer=0,miss=0,min=0;
int i,j,k,w;
for(i=0;i<frames;i++) {
    page_table[i][0]=-1;
    page_table[i][1]=0x00;
}
for(i=0;i<size_of_page;i++) {
	/*printf("ffew  ,page \n");
		for( w=0;w<frames;w++){
			printf("%p , %5d\n",page_table
			[w][1],page_table[w][0]);
		}
		printf("\n");
		getchar();*/
    index=0;
    flag=0;
    min=page_table[0][1];
    for(j=0;j<frames;j++) {
        page_table[j][1]=page_table[j][1]>>1;
    }
    for(j=0;j<frames;j++) {
    	
        if(pages[i]==page_table[j][0]) {
                flag=1;
                index=j;
                break;
        }
    }
    if(flag==1) {
      	page_table[index][1]=page_table[index][1]|0x80;
    }
    else if((flag!=1) && (page_table[frames-1][0]==-1)) {
    	page_table[pointer][0]=pages[i];
        page_table[pointer][1]=page_table[pointer][1]|0x80;
        pointer=(pointer+1)%frames;
    }
    else {
        for(j=0;j<frames;j++) {
            if(min>page_table[j][1]) {
                 min=page_table[j][1];
            }
        }
        for(j=0;j<frames;j++) {
            if(page_table[j][1]==min) {
                 index=j;
                 break;
            }
        }
        page_table[index][0]=pages[i];
        page_table[index][1]=0x80;
        miss=miss+1;
    }
}
return miss;
}

/*
int main() {
	int arr[]= {0,1,0,2,8,10,11,4,1,2,3,10,11,12,11,0,1,2,3,4,5,6,7,8,10,1,0,1,
	2,3,10,1,2,0,1,0,4, 3,11,7,8,9,7,7,8,1,2,4,5,7,2,33,11,5,6,4,3,2,1,0,0,0,0,
	1,2,3,4,3,2,1,3,2,1,4,2,3,11, 12,5,4,3,2,1,1,0,1,2,3,4,5,1,2,3,4,5,4,3,2,1,
	4,6,7,8,1,2,3,4,2,1,0,1,0,1,0,4,5,6,7,8, 9,8,7,6,11,10,12,2,3,1,2,5,3,4,3,1,
	2,0,5,3,1,4,2,4,2,8,7,6,4,5,2,1,4,2,2,2,12,1,0,1};
	int frames= 3, j=159;
	int a= lru8(arr,frames,j);
	printf("\n Evaluated= %d", a);
	return 0;
}
*/
