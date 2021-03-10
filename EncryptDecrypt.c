/*
Compiler Used - borland compiler

Program Description:
A program that allows the user to input  a 4-digit code or generate a 4-digit random code (0000 � 9999 inclusive) using the program. 
This code can then be encrypted using a encryption algorithm in the program.
The encrypted code can then be compared with the encrypted access code (4523). 
The code can also be decrypted using a decryption algorithm in the program.  
The user can also select an option to show how many times the entered access code was wrong or right
The user can exit the program

ERROR CHECKS - User cannot access options 2,3 and 4 when the program starts.
                         - Code cannot be encrypted if already encrypted
                         - Only encrypted code can be compared with access code
                         - Code can only be decrypted if it is encrypted
                         - Prevent user input errors
*/

#include <stdio.h>
#include <stdlib.h>
#define CODE 4
#define E_CHECK 0
#define PASS_CH 1


//structure to store the frequency of wrong and correct code comparisons
struct code_counter 
{
    int correct_code;
    int wrong_code;
};

//declare functions
int inputCode(int*,int*,int*,int*,int*);
void encryptCode(int*,int*,int*,int*,int*);
struct code_counter compareCode(int*,int*,int*,int*,int*,code_counter*);
void decryptCode(int*,int*,int*,int*,int*);
void display_counter(code_counter*);
int funcExit();


//start main()
int main()
{
    int menu_loop=E_CHECK;
    int option;
    int user_code[CODE];
    int access_code[CODE]={4,5,2,3};
    int allow_opt=E_CHECK;
    int allow_enc=PASS_CH;
    int allow_dec=E_CHECK;
    int allow_com=E_CHECK;
    int incerment_error;
    struct code_counter count={0,0};
    
    printf("                                                    ACCESS CODE CHECK");
    //loop to show the menu after each option
    do
    {
        //Menu Layout
        printf("\n\n\n\n\n\n          Main Menu\n");
        printf("\n 1.  Enter code or Generate code");
        printf("\n 2.  Encrypt code");
        printf("\n 3.  Code Check");
        printf("\n 4.  Decrypt code ");
        printf("\n 5.  Frequency");
        printf("\n 6.  Exit Program");
        
        option=E_CHECK;
        //choose option
        printf("\n Select a option (Type in number between 1-6):");
        scanf("%d",&option);
        flushall();
        
        //select the option entered by the user
        switch(option)
        {
            case 1:
            {
                allow_opt = inputCode(user_code,&allow_enc,&allow_dec,&allow_com,&incerment_error);
                break;
            }//end case
            
            case 2:
            {
                encryptCode(user_code,&allow_opt,&allow_enc,&allow_dec,&allow_com);
                break;
            }//end case
            
            case 3:
            {
                count = compareCode(user_code,access_code,&allow_opt,&allow_com,&incerment_error,&count);
                break;
            }//end case
            
            case 4:
            {
                decryptCode(user_code,&allow_opt,&allow_enc,&allow_dec,&allow_com);
                break;
            }//end case
            
            case 5:
            {
                display_counter(&count);
                break;
            }//end case
            
            case 6:
            {
                menu_loop=funcExit();
                break;
            }//end case
            
            default:
            {
                printf("\n\n    ERROR : Enter a number bwtween 1 and 6");
            }//end default
            
        }//end switch
        
    }//end do
    while(menu_loop==E_CHECK);
    printf("\n\nPress ENTER to exit the program");
    getchar();
    
    return 0;
    
}//end main()



//implement function inputCode()
//Option 1 -- Inputting the 4 digit code or making a random 4 digit code.
int inputCode(int *in_code, int *al_enc, int *al_dec, int *al_com,int *inc_er)
{
    int i;
    int al_opt;
    int sub_option;
    int loop=E_CHECK;
    int input_loop;
    *al_enc=PASS_CH;
 
    printf("\n\n Press 1 to enter code or 2 to Generate code: ");
    
    //loop to allow user to choose option again if wrong number entered
    do
    {

        scanf("%d",&sub_option);
        flushall();
        
        // chose option netered by user
        switch(sub_option)
        {
            case 1:
            {
                
                //allow user to input code
                printf("\nEnter your 4 digit number\n");
                for(i=0;i<CODE;i++)
                {
                    input_loop=E_CHECK;
                    printf("Enter Digit %d :",i+1);
                    scanf("%d",&*(in_code+i));
                    flushall();
                    
                    //loop to allow multiple entries if a wrong number is entered
                    do
                    {
                        //error check if value entered outside the range 0-9
                        if(*(in_code+i)>-1 && *(in_code+i)<10)
                        {
                            input_loop=PASS_CH;
                        }
                        else
                        {
                            printf("\nERROR : Enter a digit between 0-9 :\n");
                            printf("Enter Digit %d :",i+1);
                            scanf("%d",&*(in_code+i));
                            flushall();
                        }
                    }
                    while(input_loop==E_CHECK);
                }//end for
                
                
                //show the code entered
                printf("\n Your number = ");
                for(i=0;i<CODE;i++)
                {
                    printf("%d",*(in_code+i));
                }//end for
                
                al_opt=PASS_CH;
                loop=PASS_CH;
                *al_com=E_CHECK;
                *al_dec=E_CHECK;
                *inc_er=PASS_CH;
                
                break;
                
            }//end case
            
            case 2:
            {
                
                //generate random code
                for(i=0;i<CODE;i++)
                {
                    *(in_code+i)=rand()%9+0;
                }//end for
                
                //display the random code generated
                printf("\n Your number = ");
                for(i=0;i<CODE;i++)
                {
                    printf("%d",*(in_code+i));
                }//end for
                
                al_opt=PASS_CH;
                loop=PASS_CH;
                *al_com=E_CHECK;
                *al_dec=E_CHECK;
                *inc_er=PASS_CH;
                
                break;
                
            }//end case
            
            default:
            {
                printf("\n  ERROR: Enter 1 or 2: ");
            }//end default
            
        }//end switch
        
    }//end do
    while(loop==E_CHECK);
    
    return al_opt;
    
}//end inputCode()



//implement function encryptCode()
//Option 2 -- Encrypting the code from option one.
void encryptCode(int *in_code,int *al_enc,int *al_enc2,int *al_dec,int *al_com)
{
    int i,j,temp;
    
    //error check when the program opens 
    if(*al_enc==PASS_CH)
    {
        
        //error check for allowing encryption on a code that is not already encrypted
        if(*al_enc2==PASS_CH)
        {
            
            //encryption algorithm 
            for(i=0;i<CODE;i++)
            {
                
                //to switch numbers once
                if(i==0)
                {
                    
                    //switch numbers
                    for(j=0;j<CODE-2;j++)
                    {
                        temp=*(in_code+j);
                        *(in_code+j)=*(in_code+j+2);
                        *(in_code+j+2)=temp;
                    }//end for
                    
                }//end if
                
                //add 1 to numbers 
                 *(in_code+i)=*(in_code+i)+1;
                
                //chnage to 0 if over 9
                if(*(in_code+i)>9)
                {
                    *(in_code+i)==0;
                }//end if
                
            }//end for
            
            //display encrypted number
            printf("\n Your encryped code is ");
            for(i=0;i<CODE;i++)
            {
                printf("%d",*(in_code+i));
            }//end for
            
            *al_enc2=E_CHECK;
            *al_dec=PASS_CH;
            *al_com=PASS_CH;
            
        }//end if
        
        else
        {
            printf("\n\n    ERROR : The CODE is already encrypted\n");
        }//end else
        
    }//end if
    
    else
    {
        printf("\n\n    ERROR : Enter or Generate the 4 digit code first.\n");
    }//end else
    
}//end encryptCode()



//implement function compareCode() 
//Option 3 -- Compare user's code with the access code
struct code_counter compareCode(int *in_code,int *ac_code,int *al_com,int *al_com2,int *inc_er, code_counter *count)
{
    int i;
    int match=0;
    
    //error check when the program opens
    if(*al_com==PASS_CH)
    {
        
        //error check to allow only encrypted code to be compared
        if(*al_com2==PASS_CH)
        {
            
            //counter to see how many numbers match
            for(i=0;i<CODE;i++)
            {
                if(*(in_code+i)==*(ac_code+i))
                {
                    match++;
                }//end if
                
            }//end for
            
            //Dispay if correct or incorrect
            if(match==4)
            {
                printf("\n\n\n\n     Correct Code entered");
                
                //to only allow one increment in one go
                if(*inc_er==PASS_CH)
                {
                    count->correct_code++;
                }//end if
                
            }//end if
            else
            {
                printf("\n\n\n\n     Wrong Code entered");
                
                //to only allow one increment in one go
                if(*inc_er==PASS_CH)
                {
                    count->wrong_code++;
                }
            }//end else
            
            *inc_er=E_CHECK;
            
        }//end if
        else
        {
            printf("\n\n ERROR : The code is not encrypted\n");
        }//end else
        
    }//end if
    else
    {
        printf("\n\n    ERROR : Enter or Generate the 4 digit code first.\n");
    }//end else
    
    return *count;
    
}//end compareCode()



//implement function decryptCode()
//Option 4 -- Decrpyt an encrypted code
void decryptCode(int *in_code,int *al_dec,int *al_enc,int *al_dec2, int *al_com)
{
    int i,j,temp;
    
    //error check at the start of the program
    if(*al_dec==PASS_CH)
    {
        
        //error check to allow decryption once only
        if(*al_dec2==PASS_CH)
        {
            
            //decrypting code
            for(i=0;i<CODE;i++)
            {
                
                //taking away 1 from each number
                *(in_code+i)=*(in_code+i)-1;
                
                //change to 9 if less than 0
                if(*(in_code+i)<0)
                {
                    *(in_code+i)==9;
                }//end if
                
                //to only switch the number once
                if(i==3)
                {
                    
                    //switch the numbers
                    for(j=0;j<CODE-2;j++)
                    {
                        temp=*(in_code+j);
                        *(in_code+j)=*(in_code+j+2);
                        *(in_code+j+2)=temp;
                    }//end for
                    
                }//end if
                
            }//end for
            
            //display the decrypted code
            printf("\n Your decryped code is ");
            for(i=0;i<CODE;i++)
            {
                printf("%d",*(in_code+i));
            }//end for
            
            *al_enc=PASS_CH;
            *al_dec2=E_CHECK;
            *al_com=E_CHECK;
            
        }//end if
        else
        {
            printf("\n\n    ERROR: The code is not encrypted\n");
        }//end else
        
    }//end if
    else
    {
        printf("\n\n    ERROR : Enter or Generate the 4 digit code first.\n");
    }//end else
    
}//end decryptCode()



//implement function display_counter()
//Option 5 -- Displaying the number of times correct or incorrect code entered
void display_counter(code_counter *count)
{
    //display counters
    printf("\n\nCorrect code was entered %d times",count->correct_code);
    printf("\nWrong code was entered %d times",count->wrong_code);
}//end display_counter()


//implement function funcExit()
//Option 6 (Exiting the program)
int funcExit()
{
    
    return PASS_CH;
    
}//end funcExit()

