struct table_of_contents {
	int bit; //0-1
	int referred_page; //page
};


int lru1(int pages[], int frames, int size_of_page) {
	struct table_of_contents page[size_of_page];
	struct table_of_contents page_table[frames];
	int i,j,k,w;
	int index,flag,fault_count=0, miss=0, frame_count=0, pointer=0;

	for (i=0;i<size_of_page;i++) {
		page[i].referred_page= pages[i];
		page[i].bit=0;  //ref_bit
	}
	for(i=0;i<frames;i++) {
		page_table[i].referred_page = -1;
		page_table[i].bit=0;
	}
	for(i=0;i<size_of_page;i++) {
	/*printf("biti  ,page \n");
		for( w=0;w<frames;w++){
			printf("%5d , %5d\n",page_table
			[w].bit,page_table[w].referred_page);
		}
		printf("\n");
		getchar();*/
		flag=0;
		j=0; //fault_count_flag
		for(index=0;index < frames;index++) {
			if(page[i].referred_page == page_table[index].referred_page) {
				flag=1;
				page_table[index].bit = 1; //set page_table[ref_bit] =1 ;
			}
		}
		while (flag == 0) {
			if(page_table[pointer].bit == 0) {
				flag=1;
				page_table[pointer] = page[i];
				fault_count++;
				pointer= (pointer+1) % frames;	//replace this page and set flag=1;
			}
			else if(page_table[pointer].bit ==1) {
				page_table[pointer].bit = 0;
				pointer= (pointer+1) % frames;
			}
		}
		//---------------
		if (frame_count > size_of_page+1) {
			index=0;
		}
		//---------------
		miss= fault_count -frames;
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
	int a= lru1(arr,frames,j);
	printf("\n Evaluated= %d", a);
	return 0;
}*/

