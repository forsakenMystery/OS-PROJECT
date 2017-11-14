struct table_of_content {
	int freq; //frequency
	int referred_page; //page
};


int lfu(int pages[], int frames, int size_of_page) {
	struct table_of_content page[size_of_page];
	struct table_of_content page_table[frames];
	int i,j,k,w;
	int index,flag,fault_count=0,pointer=0, frame_count=0, replace_count=0;

	for (i=0;i<size_of_page;i++) {
		page[i].referred_page= pages[i];
		page[i].freq=0;
	}
	for(i=0;i<frames;i++) {
		page_table[i].referred_page=-1;
		page_table[i].freq=0;
	}

	for(i=0;i<size_of_page;i++) {
	/*	printf("freq  ,page \n");
		for( w=0;w<frames;w++){
			printf("%5d , %5d\n",page_table
			[w].freq,page_table[w].referred_page);
		}
		printf("\n");
		getchar();*/
		flag=0;
		for(k=0;k<size_of_page;k++) {
			if(page[i].referred_page == page[k].referred_page)
				page[k].freq++; // because whether found or added the frequency has to be incremented
		}
		for(index=0;index < frames;index++) {
			if(page[i].referred_page == page_table[index].referred_page) {
				//printf("match found \n");
				page_table[index].freq= page[i].freq;
				flag=1;
				break;
			}
		}
		if((frame_count < frames) && (flag == 0)) {
			//fill in first three frames
			page_table[pointer]= page[i];
			pointer= (pointer+1) % frames;
			fault_count++;
			frame_count++;
		}
		else if (flag == 0) {
			int minimum= page_table[0].freq;
			int eq_arr_count=0;
			for (k=0;k<frames;k++) {
				if(page_table[k].freq < minimum) {
					minimum= page_table[k].freq;
					j=k;
				}
			}
			for (k=0;k<frames;k++) {
				if (page_table[k].freq == minimum){
					//increment the eq_arr_count
					eq_arr_count++;
					}
			}
			if (eq_arr_count > 1) {//if eq_arr_count > 1
				int eq_arr[eq_arr_count];	//create new array int eq_arr[eq_arr_count];
				k=0;
				while(k < eq_arr_count)	{
					for(index=0; index<frames; index++) {
						if(page_table[index].freq == minimum){
							eq_arr[k++]=index;//initialise this new array with 'index' values that are equal to minimum
					}
				}
			}
			int dobreak=1,x=0,var_ptr= pointer; //copy pointer into new variable var_ptr and keep incrementing until var_ptr poits to anything in the array
			for(x=0;dobreak && (x<frames);x++) { //edit line
				for(k=0; k<eq_arr_count; k++) {
					if(var_ptr == eq_arr[k]) {
						j=eq_arr[k];//j= var_ptr and break;
						dobreak=0;
						break;
					}
				}
				var_ptr= (var_ptr+1) % frames;
			}
			}
			page_table[j]= page[i];
			fault_count++;
			replace_count=replace_count+1;
			pointer= (pointer+1) % frames;
		}
		
	}
		return (fault_count-frames);
}
/*
int main() {
	int arr[]= {0,1,0,2,8,10,11,4,1,2,3,10,11,12,11,0,1,2,3,4,5,6,7,8,10,1,0,1,
	2,3,10,1,2,0,1,0,4, 3,11,7,8,9,7,7,8,1,2,4,5,7,2,33,11,5,6,4,3,2,1,0,0,0,0,
	1,2,3,4,3,2,1,3,2,1,4,2,3,11, 12,5,4,3,2,1,1,0,1,2,3,4,5,1,2,3,4,5,4,3,2,1,
	4,6,7,8,1,2,3,4,2,1,0,1,0,1,0,4,5,6,7,8, 9,8,7,6,11,10,12,2,3,1,2,5,3,4,3,1,
	2,0,5,3,1,4,2,4,2,8,7,6,4,5,2,1,4,2,2,2,12,1,0,1};
	int frames= 3, j=159;
	int a= lfu(arr,frames,j);
	printf("\n Evaluated= %d", a);
	return 0;
}
*/
