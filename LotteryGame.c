/*Assignment 2
Rakshit Nautiyal
C19313276

This program represents a lottery game. The user is asked to input his 6 numbers. Thses numbers are stored and can be viewed by the user any time. 
There is option to sort the numbers in acending order. These numbers are compared with the with the winning numbers do declare what the user has won,
This program also allows user to enter multiple sets of number and display the frequency of a number that has been inputed by the user.*/

#include <stdio.h>
#define SIZE 6
#define PRE_ERROR 0
#define ERROR 1
#define NUM_SET 42

void user_nums(int*);
void display_nums(int*);
void sort_nums(int*);
void compare_nums(int*,int*);
void nums_freq(int*,int*,int*);
int funcExit();

/*------START MAIN------*/
int main()
{
    printf("\n      LOTTO GAME\n\n");
    int menu_loop=PRE_ERROR;
    int error_check=PRE_ERROR;
    int round=PRE_ERROR;
    int frqPass;
    int passError=PRE_ERROR;
    int *myptr;
    
    myptr = &frqPass;
    
    do
    {
        int user_input[SIZE];
        int option_sel;
        int wining_set[SIZE]={1,3,5,7,9,11};
        int frequency_arr[NUM_SET];
        
        printf("\n\nMAIN MENU\n\n");
        printf(" 1. Put in Lotto Numbers\n");
        printf(" 2. Display Your Numbers\n");
        printf(" 3. Arrange Numbers\n");
        printf(" 4. Compare Numbers\n");
        printf(" 5. Number Frequency\n");
        printf(" 6. Exit\n\n");
        
        do
        {
            //Choose option
            printf("\nSelect a option (Type in the option number between 1-6):");
            scanf("%d",&option_sel);
            
            //error check to deny access to other options before selection option 1
            if(option_sel>ERROR && option_sel<6)
            {
                
                if(round<ERROR)
                {
                    printf("\nERROR **Option 1 must be selected first**");
                }//end if
                
            }//end if
            else
            {
                error_check++;
                round++;
            }//end else
        }//end do
        while(error_check<ERROR);
        
        //switch case to choose a option and to remove error inputs
        switch(option_sel)
        {
            
            //OPTION 1
            case 1:
            {
                //call function user_nums()
                user_nums(user_input);
                passError++;
                *(myptr)=PRE_ERROR;
                nums_freq(user_input,frequency_arr,myptr);
                break;
            }//end case
            
            //OPTION 2
            case 2:
            {
                //call function user_nums()
                display_nums(user_input);
                break;
            }//end if
            
            //OPTION 3
            case 3:
            {
                //call function sort_nums()
                sort_nums(user_input);
                break;
            }//end case
            
            //OPTION 4
            case 4:
            {
                //call function compare_nums()
                compare_nums(user_input, wining_set);
                break;
            }//end case
            
            //Option 5
            case 5:
            {
                //call function nums_freq()
                *(myptr)=ERROR;
                nums_freq(user_input,frequency_arr,myptr);
                break;
            }//end case
            
            //OPTION 6 (exit)
            case 6:
            {
                menu_loop=funcExit();
                break;
            }//end case
            
            //error check for menu to allow 1 to 6 only
            default:
            {
                printf("\n\nERROR **Type in a number between 1 and 6**\n\n\n\n\n");
                
                /*error check to get out of the loop after first round and to deny access to other (except option 1) options in round one. 
                            This is put in to deny user to surpass error check to select other options in round one after entering a value outside of 1-6 value range.*/
                if(passError<ERROR)
                {
                    error_check=PRE_ERROR;
                    round=PRE_ERROR;
                }//end if
                
            }//end default
            
        }//end switch
        
    }//end do
    while(menu_loop==0);
    
    getchar();
    return 0;
}


//______________________________Option 1 (input lotto numbers)
//implement function user_nums() 
void user_nums(int *nums)
{
    int i;
    int j;
    int error_c1;
    int error_c2;
    int error_c3;
    
    
    printf("\nType in your 6 lottery numbers\n\n");
    //loop for the user to input all the numbers
    for(i=0;i<SIZE;i++)
    {
        
        do
        {
            //error check to only allow the user to enter a number between 1-42
            do
            {
                error_c1=0;
                error_c2=0;
                error_c3=0;
                
                //reading in the user's numbers
                scanf("%d",&*(nums+i));
                flushall();
                
                if(*(nums+i)>0 && *(nums+i)<43)
                {
                    error_c2++;
                }//end if 
                else
                {
                    printf("\n\nERROR **Type in a number between 1 and 42**\n\n\n");
                }//end else
                
                //error check to allow one number to be inputed once
                if(i>0)
                {
                    
                    for(j=0;j<i;j++)
                    {
                        
                        if(*(nums+i)==*(nums+j))
                        {
                            printf("\n\nERROR **This number was already entered**\n");
                            error_c3++;
                        }//end if
                        
                    }//end for
                    
                    if(error_c3<ERROR)
                    {
                        error_c1++;
                    }//end if
                    
                }//end if
                else
                {
                    error_c1++;
                }//end else
                
            }//end do
            while(error_c2<ERROR);
            
        }//end do
        
        while(error_c1<ERROR);
            
    }//end for
    
}//end function user_nums()


//______________________________Option 2 (Display enetred nums)
//implement function display_nums
void display_nums(int *nums)
{
    int i;
    
    //displaying the numbers the user has entered
    for(i=0;i<SIZE;i++)
    {
        printf("\n%d",*(nums+i));
    }//end for
    
}//end display_nums()

//______________________________Option 3 (Sort and display numbers in ascending order)
//implement sort_nums()
void sort_nums(int *nums)
{
    int i,j,temp;
    
    //loop to sort the numbers in acending order
    for(i=0;i<SIZE;i++)
    {
        
        for(j=0;j<i;j++)
        {
            
            if(nums[i]<nums[j])
            {
                temp = *(nums+i);
                *(nums+i)=*(nums+j);
                *(nums+j)=temp;
            }//end if
            
        }//end for
        
    }//end for 
    
    //printing the sorted numbers
    printf("\n Sorted elements in ascending order:\n");
    
    for(i=0;i<SIZE;i++)
    {
        printf("\n %d",*(nums+i));
    }//end for

}//end sort_nums()

//______________________________Option 4 (Compare the user numbers with the winning number and deciding the price)
//implement compare_nums()
void compare_nums(int *nums, int *win_nums)
{
    int i,j,temp;
    int counter=0;
    
    //loop to sort the numbers in acending order
    for(i=0;i<SIZE;i++)
    {
        
        for(j=0;j<i;j++)
        {
            
            if(nums[i]<nums[j])
            {
                temp = *(nums+i);
                *(nums+i)=*(nums+j);
                *(nums+j)=temp;
            }//end if
            
        }//end for
        
    }//end for
    
    //loop to compare the user's numbers with the wining numbers 
    for(i=0;i<SIZE;i++)
    {
        
        if(*(nums+i)==*(win_nums+i))
        {
            //displaying numbers matched 
            printf("\nNumber %d is a match",*(nums+i));
            counter++;
        }//end if
        else
        {
            //displaying numbers not matched
            printf("\nNumber %d is not a match",*(nums+i));
        }//end else
        
    }
    
    //displaying the total matches
    printf("\n%d numbers match",counter);
    
    //deciding the price
    switch(counter)
    {
        case 6 :
        {
            printf("\n\nCongratulations, you have won the JACKPOT");
            break;
        }//end case
        
        case 5 :
        {
            printf("\n\nCongratulations, you have won a NEW CAR");
            break;
        }//end case
        
        case 4 :
        {
            printf("\n\nCongratulations, you have won a WEEKEND AWAY");
            break;
        }//end case
        
        case 3 :
        {
            printf("\n\nCongratulations, you have won a CINEMA PASS");
            break;
        }//end case
        
        default:
        {
            printf("\n\nYou did not win a price. Better luck next time\n\n");
        }//end default
    }//end switch
    
    
}

//______________________________Option 5 (Calculating the frequencies of numbers)
//implement function nums_freq()
void nums_freq(int *nums, int *set, int *frqCatch)
{
    int i,j;
    static int freq_count[NUM_SET];
    
    //if statement stopping the array to be passed in twice as this function is called twice int main.
    if(*(frqCatch)==PRE_ERROR)
    {
        for(i=0;i<NUM_SET;i++)
        {
            *(set+i)=i+1;
        }//end for
        
        
        //Counting the frequency of the numbers
        for(i=0;i<SIZE;i++)
        {
            
            for(j=0;j<NUM_SET;j++)
            {
                
                if(*(set+j)==*(nums+i))
                {
                    *(freq_count+j)=*(freq_count+j)+1;
                }//end if
                
            }//end for
            
        }//end for
    }//end if
    
    //if statement stopping the array to be printrd twice as this function is called twice in the main.
    if(*(frqCatch)==ERROR)
    {
        printf("\n           NUMBER              FREQUENCY");
        
        //print the frequencies
        for(i=0;i<NUM_SET;i++)
        {
            
            //if statement to print number frequencies more than 1 only.
            if(*(freq_count+i)>0)
            {
                
                //if statement to align the table
                if(i<9)
                {
                    printf("\n             %d                    %d",*(set+i),*(freq_count+i));
                }//end if
                else
                {
                    printf("\n             %d                   %d",*(set+i),*(freq_count+i));
                }//end else
                
            }//end if
            
        }//end for
        
    }//end if
    
}//end nums_freq()

//______________________________Option 6 (Exiting the program)
//implement function funcExit()
int funcExit()
{
    
    return ERROR;
    
}//end funcExit()



/*                                                                                                                                                  /-------------------END------------------/                                                                                                                                                        */
