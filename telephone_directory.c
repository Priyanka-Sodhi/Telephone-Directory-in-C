#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct record{   
char name[50];
char address[1000];
char gender[10];
char mail[50];
long int mobile_no;
};

void menu();
void ad();
void del();
void update();
void disp();
void input();

int main()
{
	system("color 3f");
	menu();
	return(0);
}

void menu()
{
 system("cls");
 int ch;
 char c;
 printf("\t\t*********************WELCOME TO PHONEBOOK**************************");
 printf("\n\n\t\t-------------------------MENU-----------------------");
 printf("\n1.Add a contact\n2.Delete a contact\n3.update a contact\n4.Display contact list\n5.Exit.");
 printf("\n\nSelect any one option: ");
 scanf("%d",&ch);
 switch(ch)
 {
 	case 1: ad();
 			  break;
 	case 2: update();
 			  break;
 	case 3: del();
 			  break;
 	case 4: disp();
 			  break;
 	case 5: exit(0);
	 		  break;
 	default: system("cls");
	 		 printf("\nInvalid choice!");
 			 printf("Enter from given options only: ");
 			 getch();
menu();
}
}


void ad() // function for adding new record to the list
{	
	system("cls");
	FILE *f;
	struct record r;
	f=fopen("record.txt","a+"); //creating file
	printf("\nEnter name:");
	fflush(stdin);
	input(r.name);
	printf("\nEnter gender:");
	input(r.gender);
	printf("\nEnter address:");
	input(r.address);
	printf("\nEnter mobile no.:");
	scanf("%ld",&r.mobile_no);
	printf("Enter email:");
	input(r.mail);
	fwrite(&r,sizeof(r),1,f);
    printf("\nrecord saved");
	fclose(f);
	system("cls");
	menu();
}

void disp() //function to display full list of records 
{
struct record r;
FILE *f;
f=fopen("record.txt","r");
if(f==NULL)
{
printf("\nfile opening error");
exit(1);
}
while(fread(&r,sizeof(r),1,f)==1)
{
    printf("\n\n\n YOUR RECORD IS:\n ");
    printf("\nName=%s\nAdress=%s\nGender=%s\nMobile no.=%ld\nE-mail=%s\n",r.name,r.address,r.gender,r.mobile_no,r.mail);
    getch();
    system("cls");
}
fclose(f);
system("cls");
menu();
}

void update() //function for any modification in any of the records.
{
	FILE *f;
	int flag=0;
	struct record r,s;
	char name[30];
	f=fopen("record.txt","r+");
	if(f==NULL)  //to check whether file exists or not.
	{
	printf("This contact's data not added yet! ");
	exit(1);
	} 
	else
	{
		printf("\nEnter contact name to be modified: ");
		gets(name);
		while(fread(&r,sizeof(r),1,f)==1)
		{
			if(strcmp(name,r.name)==0)
			{
			printf("\nEnter name:");
			input(r.name);
			printf("\nEnter gender:");
			input(r.gender);
			printf("\nEnter address:");
			input(r.address);
			printf("\nEnter mobile no.:");
			scanf("%ld",&r.mobile_no);
			printf("\nEnter email:");
			input(r.mail);
			fseek(f,-sizeof(r),SEEK_CUR);
			fwrite(&r,sizeof(r),1,f);
			flag=1;
			break;
			}
			fflush(stdin);
   		}
		if(flag==1)
			{
			printf("\nrecord updated!");
			}
		else
			{
			printf("Data not found!");
			}
			fclose(f);
			system("cls");
			menu();
	}
}

void del() //deleting the record
{	
	struct record r;
	FILE *f,*nf;
	int flag;
	char name[100];
	f=fopen("record.txt","r");
	if(f==NULL)
	{
	printf("Seems like this data not added yet!");
	}
	else
	{
		nf=fopen("recordcopy.txt","w+");
		if(nf==NULL)
			printf("File doesn't exists!");
		else
		{
		printf("Enter contact name to be deleted: ");
		input(name);
		fflush(stdin);
		while(fread(&r,sizeof(r),1,f)==1)
			{
			if(strcmp(r.name,name)!=0)
				fwrite(&r,sizeof(r),1,nf);
            if(strcmp(r.name,name)==0)
			    flag=1;
        	}
    	fclose(f);
    	fclose(nf);
    	if(flag!=1)
    		{
        	printf("NO CONACT'S RECORD TO DELETE.");
        	remove("recordcopy.txt");
    		}
        else
        	{
            remove("record.txt");
            rename("recordcopy.txt","record.txt");
            printf("\nRECORD DELETED SUCCESSFULLY.");
			}
    	}
	}
	printf("\nEnter any key: ");
	getch();
	system("cls");
menu();
}
	
void input(char *name)
{

   int i=0,j;
    char c,ch;
    do
    {
        c=getch();
                if(c!=8&&c!=13)
                {
                    *(name+i)=c;
                        putch(c);
                        i++;
                }
                if(c==8)
                {
                    if(i>0)
                    {
                        i--;
                    }
                   // printf("h");
                    system("cls");
                    for(j=0;j<i;j++)
                    {
                        ch=*(name+j);
                        putch(ch);

                    }

                }
    }while(c!=13);
      *(name+i)='\0';
}	
	







