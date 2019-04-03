#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int all_space;
  int start_address;
  struct node* next;
}node;


node *alloc_list,*flist;
int all_space;
int start_address;

void free_up(node *nptr);
void to_allocate(node *nptr);
node* Next_Fit(node *nptr);
void First_Fit();
void Best_Fit();
void allocate_list();
void free_list();
void free_fun(node *nptr);
node* malloc_fun();

void main()
{
   node *nptr,*ptr;
   flist = NULL;
   alloc_list = NULL;
   all_space = 10000;
   start_address=0;
   nptr = malloc_fun();
   nptr->next = flist;
   flist = nptr;
   ptr = flist;            

   int choice,i,fchoice,done;

   fchoice=1;
   
   printf("\n\n\t\t\t\tCPL LAB ASSIGNMENT - SIMULATION OF HEAP MANAGEMENT\n\n");
   printf("\t\t\t\t\t-----------------------------------------\n");
   printf("\t\t\t\t\t|\t Name: Amay Jain\t\t|\n");
   printf("\t\t\t\t\t|\t Batch: R1\t\t\t|\n");
   printf("\t\t\t\t\t|\t Roll-No: BT17CSE010\t\t|\n");
   printf("\t\t\t\t\t|\t Submission Date: 02-04-2019\t|\n");
   printf("\t\t\t\t\t-----------------------------------------\n");

   while(fchoice)
   {
   		printf("\n===============================================================\n");
	 	printf("1 - For MALLOC/Creation of NEW Space\n");
		printf("2 - For FREEING/Deleting the previously ALLOCATED Space\n");
		printf("3 - For Traversing the ALLOCATED List\n");
		printf("4 - For Traversing the remaining FREE List\n");
		printf("0 - EXIT this SIMULATION OF HEAP\n");
		printf("===============================================================\n");
		printf("Enter the CHOICE you want to Execute\n->");
        scanf("%d",&choice);
    
        
	        if(choice==1)
	        {
	            int method;
	            int s;
	          
	          	printf("\t1 - Integer\n");
				printf("\t2 - Float\n");
				printf("\t3 - Character\n");
				printf("\t4 - How much Space do you want to ALLOCATE?\n\t->");
	            scanf("%d",&s);
	            
	            switch(s)
	            {
	            	case 1: all_space = 4;
	            			break;
	            	case 2: all_space = 8;
	            			break;
	            	case 3: all_space = 1;
	            			break;
	            	case 4: scanf("%d",&all_space);
	            			break;
				}
	
				printf("\t\t1 - Allocate by FIRST-FIT method\n");
				printf("\t\t2 - Allocate by BEST-FIT method\n");
				printf("\t\t3 - Allocate by NEXT-FIT method\n\t\t->");
	            scanf("%d",&method);
	
	            switch(method)
	            {
	
	                case 1: First_Fit();
	                        break;
	
	                case 2: Best_Fit();
		        	        break;
	
			   		case 3: ptr = Next_Fit(ptr);
				   			break;
	            }
	            fchoice=1;
	
		 	}
			else
	        {
	            if(choice==2)
	            {
			        int done;
			        done=0;
			        node *prev;
			        prev=NULL;
	
			        nptr = alloc_list;     
			        printf("Enter Address of Variable to be freed\n");
			        scanf("%d",&start_address);
	
	
			        while(nptr!=NULL && done==0)
			        {
			            if(nptr->start_address==start_address)
			            {
			                done=1; 
			            }
			            else
			            { 
			              prev = nptr;
			              nptr = nptr->next; 
			            }
			        }
	
			        if(done==0)
			        { 
						printf("The Entered node does not Exist, and hence cannot be Deleted from Allocated List\n");
				    }
	
			        else
			            {
					   if(prev!=NULL)                         //removal from allocated list and insertion into free list
					   {
					        prev->next = nptr->next;
					   }
					   else
					   { 
						alloc_list = alloc_list->next;
					   }
	
	            	        nptr->next = NULL;
							free_up(nptr);  
			        }
	            }
	        
	            else
	            {
	                if(choice==3)
					{ 
						allocate_list();
					}
	                else if(choice==4)
	                { 
						free_list();
					}
					else
					{
						fchoice=0;
					}
	
	            }
	
		 	}
	
	    }
	}

 
    node* malloc_fun()
    {
          node *nptr;
          nptr = (node*)malloc(sizeof(node));
          nptr->all_space = all_space;
          nptr->start_address = start_address;
          nptr->next=NULL;   
          return nptr;
    }
 

    void First_Fit()
	{
	   	node *temp,*prev,*nptr;
        temp = flist;
        prev = NULL;
		int done=0;
                
		while(temp!=NULL && done==0)
		{
		    if(temp->all_space < all_space)
            { 
                prev=temp;
 		   	    temp = temp->next;
			}
            else
		    {
                done=1;
			    if(temp->all_space > all_space)
		        {
                    start_address = temp->start_address;
		            nptr = malloc_fun();
		            to_allocate(nptr);
		            temp->all_space -=all_space;
		            temp->start_address += all_space;
		        }
		        else
		        {
		            if(prev!=NULL)
		            {
		                prev->next = temp->next;  
		            }
				    else
				    {
		                flist = flist->next;
				    }
		            to_allocate(temp);
		        }
	      
		    }
		}
         
        if(done==0)
        { 
			printf("Space not Enough to Allocate\nTry Best-Fit/Next-Fit OR reduce Space Size\n");
		}
        else
        {
			printf("Your Required Space was Allocated Succesfully using FIRST-FIT\n");
		}
    } 
  
      
    void Best_Fit()
	{
	   	node *temp,*prev,*nptr,*t;
        temp = flist;
        prev = NULL;
        t=NULL;

		int diff,max,done;
        max=10000;
        done=0;

		while(temp!=NULL && done==0)
		{
		    if(temp->all_space < all_space)
            { 
                prev=temp;
 			    temp = temp->next;
			}
            else
		    { 
                if(temp->all_space > all_space)
		        {
                    diff = temp->all_space - all_space;
                    if(diff<max)
					{
						max=diff;
						t=temp; 
					}
                    prev = temp;
                    temp = temp->next;
		        }
		        else
		        {
                    done=1;
		            if(prev!=NULL)
		            {
		                prev->next = temp->next;  
		            }
				    else
				    {
		                flist = flist->next;
				    }
		            to_allocate(temp);
		        }
	      
		    }
                     
		}
         
        if(done==0)
        {
            if(t==NULL) 
            {
		  		printf("Space not Enough to Allocate\nTry First-Fit/Next-Fit OR reduce Space Size\n"); 
		    }

            else
            {
                start_address = t->start_address;
                nptr = malloc_fun();
		        to_allocate(nptr);
		        t->all_space -= all_space;
		        t->start_address += all_space;
                printf("Your Required Space was Allocated Succesfully using BEST-FIT");
            }
        }
    } 

    
    node* Next_Fit(node* ptr)
    {
            node *temp,*prev,*nptr;
            temp = flist;
            prev = NULL;
			int done=0;

            while(temp!=NULL && temp!=ptr)
            {
                prev=temp;
                temp = temp->next;
            }

            if(temp==NULL)
            {
                temp = flist; 
            }
                

			while(temp!=NULL && done==0)
			{
		        if(temp->all_space < all_space)
                { 
                    prev=temp;
 			   		temp = temp->next;
				}
                else
		        {
                    done=1;
				    if(temp->all_space > all_space)
		            {

                        start_address = temp->start_address;
		                nptr = malloc_fun();
		                to_allocate(nptr);
		                temp->all_space -= all_space;
		                temp->start_address += all_space;
                        ptr = temp;
		            }
		            else
		            {
		                if(prev!=NULL)
		                {
		                    prev->next = temp->next;  
                            ptr = prev;
		                }
				    	else
				    	{
		                    flist = flist->next;
                            ptr = flist;
				      	}
		                to_allocate(temp);
		            }
	      
		       }
			}
         
        	if(done==0)
            { 
				printf("Space not Enough to Allocate\nTry First-Fit/Best-Fit OR reduce Space Size\n\n"); 
				ptr = flist;
			}
            else
			{ 
				printf("Your Required Space was Allocated Succesfully using NEXT-FIT\n");
			}
        return ptr;
                			
	}

 
     //this function is to insert node in allocated list a_list;

      void to_allocate(node* nptr)
      {
		 node* temp,* prev;
		 temp = alloc_list;
		 prev=NULL;

		 while(temp!=NULL && nptr->start_address > temp->start_address)
		 {
		    prev=temp;
		    temp = temp->next;
		 }
		   
		 if(prev==NULL)
		 {
		    nptr->next = alloc_list;
		    alloc_list = nptr;
		 }
		 else
		 {
		      prev->next = nptr;
		      nptr->next = temp;
		 }
      }
      

      void free_up(node* nptr)
		{
		    node *prev,*temp;
		
		    int done=0,sum;
		    prev = NULL;
		    temp = flist;
		
		    while(temp!=NULL && done==0)
		    {
		        if(temp->start_address > nptr->start_address)
		        {
		            done=1;
		        }
		        else
		        {
		
		            prev=temp;
		            temp = temp->next;
		
		        }
		    }
		
		    if(done==1)
		    {
		        sum = nptr->start_address + nptr->all_space;
		        if(sum==temp->start_address)                      //if matches fine otherwise we will insert it
		        {
		            temp->start_address = nptr->start_address;
		            temp->all_space += nptr->all_space;
		            free_fun(nptr);
		            if(prev != NULL)
		            {
		                sum = prev->start_address + prev->all_space;
		                if(sum == temp->start_address)
		                {
		                    prev->all_space += temp->all_space;
		                    node* t= temp;
		                    prev->next = t->next;
		                    t->next = NULL;
		                    free_fun(t);
		                }
		            }
		
		        }
		        else
		        {
		            if(prev!=NULL)
		            {
		                sum = prev->start_address + prev->all_space;
		                if(sum==nptr->start_address)
		                {
		                    prev->all_space += nptr->all_space;
		                    free_fun(nptr);
		                }
		                else
		                {
		                    prev->next = nptr;
		                    nptr->next = temp;
		                }
		            }
		            else
		            {
		                nptr->next = temp;
		                flist = nptr;
		            }
		
		
		        }
		    }
		    else                 //means insertion at end
		    {
		        if(prev==NULL)
		        { nptr->next = temp; flist = nptr;}
		        else
		        {
		            sum = prev->start_address + prev->all_space;
		            if(sum==nptr->start_address)
		            {
		                prev->all_space += nptr->all_space;
		                free_fun(nptr);
		            }
		            else
		            {
		                prev->next = nptr;
		                nptr->next = temp;
		            }
		        }
		
		    }
		}

    
      void free_fun(node* nptr) 
      {
          free(nptr);
      }


       void allocate_list()
       {
            node *temp;
            temp = alloc_list;
            int count=1;
            printf("The following is/are your Allocated List\n");
            while(temp!=NULL)
            {
                printf("Starting address for list %d: %d Space Occupied: %d\n",count,temp->start_address,temp->all_space);
                temp = temp->next;
                count++;
            }
            
       }

        
       void free_list()
       {
            node *temp;
            temp = flist;
            int count=1;
            printf("The following is/are your Free List: \n");
            while(temp!=NULL)
            {
               printf("Starting address for list %d: %d Space Occupied: %d\n",count,temp->start_address,temp->all_space);
               temp = temp->next;
            }
       }

