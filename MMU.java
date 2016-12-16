import java.io.*;
import java.util.*;

class Page_Table_Entry{
	boolean present;// true->data in real memory
	boolean dirty; // true->page is written by data 
	int page_frame; // No. of page frame
	int time_used; // based on time stamp, the larger, the newer
}

public class MMU{
	Page_Table_Entry[] pageTable;
	
	int page_frame_high=0;// highest No. of page frame
	int page_frame_limit=0;// size of real memory
	int no_virt_pages=0; // number of virtual pages 
	int page_faults=0, rejected_pages=0, writebacks=0;
   
	MMU(int no_pages, int no_page_frames){ // initialize
	   no_virt_pages = no_pages; //number of total pages
	   pageTable = new Page_Table_Entry[no_virt_pages]; // set array size
	   for(int i=0; i<no_virt_pages;i++){
		   pageTable[i] = new Page_Table_Entry(); // set element type
		   pageTable[i].present = false; // initialize
		   pageTable[i].dirty = false;
		   pageTable[i].page_frame = 0;
		   pageTable[i].time_used = 0;
	   }
	   page_frame_limit = no_page_frames; // size of real memory
	}
	
	public int memRead(int addr,int timestamp) { // read from memory
		if(pageTable[addr].present==false){ // data isn't in real memory, need add page fault & new page frame
			page_faults++; 
			pageTable[addr].page_frame = getPageFrame(addr); 
			pageTable[addr].present = true;
			pageTable[addr].dirty = false;
			
		}
		pageTable[addr].time_used = timestamp;// get a new time stamp
		return 0;
	}

   public void memWrite(int addr,int timestamp) { // write from memory
	   if(pageTable[addr].present==false){ // has free room in real memory, need add page fault & new page frame
		   page_faults++;
		   pageTable[addr].page_frame = getPageFrame(addr);
		   pageTable[addr].present = true;
	   }
	   pageTable[addr].dirty = true;
	   pageTable[addr].time_used = timestamp;
//	   System.out.println("memWrite addr REQUIRED: "+addr+" memWrite page_frame ALLOCARED: "+pageTable[addr].page_frame);
   }
   
   private int getPageFrame(int addr){ 
	   if(page_frame_high < page_frame_limit){ // still have room in real memory
		   page_frame_high++;
		   return page_frame_high-1;
	   }else{ // 			no room in real memory, need remove old pages and reject page.
		   return getLRU();
//		   return getFIFO(addr);
	   }
   }
   
   private int getFIFO(int addr){
	   int earliest = 0x00000000;
	   int earliest_index = 0; 
	   
	   if(pageTable[addr].present){ // new frame has been in actual memory(1024,1040 <- 1024)
		   pageTable[addr].present = false;	
		 return pageTable[addr].page_frame; // return the new data's page frame which is same as the one same as it in real memory.
	   }else{
		   pageTable[addr].present = true;
		   for(int i=0; i<no_virt_pages;i++){
			   if(pageTable[i].time_used>earliest){
				   earliest = pageTable[i].time_used;
				   pageTable[addr] = pageTable[i]; // allocate the newest data address to the location of first-input data 
				   earliest_index = i;
			   }
			   
		   }
		   pageTable[earliest_index].present = false;
		   if(pageTable[earliest_index].dirty){ // earliest page was written, need refresh dirty page
			   writebacks++;
		   }
		   rejected_pages++; // explained in getPageFrame()
		   
		   return earliest_index;
	   }
	   
	   
	   
   }
   
   private int getLRU(){ //remove the page which uses less time.
	  int oldest = 0x7fffffff;
	   int oldest_pf_num = 0;
	   int oldest_index = 0;
	   
	   for(int i=0; i<no_virt_pages;i++){
		   if(pageTable[i].present==true&&pageTable[i].time_used<oldest){//find a pageTable which has the smallest time_used i.e. the oldest.
			   oldest_pf_num = pageTable[i].page_frame;
			   oldest = pageTable[i].time_used;
			   oldest_index = i;
		   }
		   
	   }
	   
	   pageTable[oldest_index].present = false;
	   if(pageTable[oldest_index].dirty){
		   writebacks++;
	   }
	   rejected_pages++;
	 return oldest_pf_num;
   }
   
}