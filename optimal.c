int optimal(int pages[], int frames, int size_of_page) {
	int miss=0,i,j,k,w,frame_count=0,flag,index,next,stay;
	int page_table[frames][2];
	for(i=0;i<frames;i++){
		page_table[i][0]=-1;//page_table
		page_table[i][1]=0;//next
	}
	for( i=0;i<size_of_page;i++){
	/*	printf("next  ,page \n");
		for( w=0;w<frames;w++){
			printf("%5d , %5d\n",page_table
			[w][1],page_table[w][0]);
		}
		printf("\n");
		getchar();*/
		flag=0;
		for( j=0;j<frames;j++){
			if(pages[i]==page_table[j][0]){
				flag=1;
				stay=j;
			}
		}
		next=0;
		for(j=i+1;j<size_of_page;j++){
			if(next==0&&pages[j]==pages[i]){
				index=j;
				next=1;
			}
		}
		if(flag==0&&frame_count<frames){
			page_table[frame_count][0]=pages[i];
			page_table[frame_count][1]=index;
			frame_count++;
			miss++;
		}
		else if(flag==0){
			int max=page_table[0][1];
			stay=0;
			for(j=0;j<frames;j++){
				if(max<page_table[j][1]){
					max=page_table[j][1];
					stay=j;
				}
			}
			page_table[stay][0]=pages[i];
			page_table[stay][1]=index;
			miss++;
		}else if(flag==1){
			page_table[stay][1]=index;
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
	int a= optimal(arr,frames,j);
	printf("\n Evaluated= %d", a);
	return 0;
}
*/
