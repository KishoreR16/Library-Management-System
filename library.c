/*Create a mini application using structures, pointers, file systems and implement memory allocation technique along with arrays.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void books_available();
void adminchoice3();
void studentchoice2();
void studentchoice3();
FILE *fp2,*fp3,*fp4;
int count;
struct book
{
	char name[30];
	int id;
	char author[30];
	int year;
};
struct book *books;
void display()
{
	printf("-----LIBRARY MANAGEMENT SYSTEM----\n");
	printf("press 1 to login as Admin\n");
	printf("press 2 to login as student\n");
	printf("press 3 to exit from the App\n");
}
void AdminLogin()
{
	printf("Welcome Admin\n");
	printf("-----ADMIN PAGE-----\n");
	printf("press 1 to add books\n");
	printf("press 2 to view the books available\n");
	printf("press 3 to view the books rented\n");
	printf("press 4 to log out\n");
	int Adminchoice;
	printf("enter your choice:");
	scanf("%d",&Adminchoice);
	switch(Adminchoice)
	{
		case 1:
			printf("Add books\n");
			FILE *fp,*fp1;
			fp=fopen("Add_books.txt","a");
			printf("enter name of the book:");
			scanf("%s",books[count].name);
			printf("enter book id:");
			scanf("%d",&books[count].id);
			printf("enter author name of the book:");
			scanf("%s",books[count].author);
			printf("published year:");
			scanf("%d",&books[count].year);
			fprintf(fp,"%s\n",books[count].name);
			fprintf(fp,"%d\n",books[count].id);
			fprintf(fp,"%s\n",books[count].author);
			fprintf(fp,"%d\n",books[count].year);
			count++;
			fp1=fopen("count.txt","w");
			fprintf(fp1,"%d",count);
			
			fclose(fp);
			fclose(fp1);
			AdminLogin();
			break;
		case 2:
			printf("Available books\n");
			books_available();
			AdminLogin();
			break;
		case 3:
			printf("Books Rented\n");
			adminchoice3();
			AdminLogin();
			break;
		case 4:
			printf("Successfully Logged out\n");
			break;
		default:
			printf("you pressed a wrong key.press a proper key\n");
			AdminLogin();
	}	
	
}
void adminchoice3()
{
	fp2=fopen("books_rented.txt","r");
	fp3=fopen("renter.txt","r");
	printf("    Book Name   |   Book Id  |  Author Name  | published year  |renter\n");
	char str[50],str1[50];
	int i=0;
	while(fgets(str,sizeof(str),fp2))
	{
		str[strcspn(str,"\n")]=0;
		printf("         %s   ",str);
		
		i++;
		if(i==4)
		{
			fgets(str1,sizeof(str1),fp3);
			printf("    %s  ",str1);
			i=0;
			printf("\n");
		}
	}
	fclose(fp2);
	fclose(fp3);
	
}
void books_available()
{
	printf("    Book Name   |   Book Id  |  Author Name  | published year\n");
	for(int i=0;i<count;i++)
	{
		printf("  %8s",books[i].name);
		printf("  %8d",books[i].id);
		printf("  %8s",books[i].author);
		printf("  %8d",books[i].year);
		printf("\n");
	}
	printf("\n");
}
void StudentLogin(char *student)
{
	printf("Welcome Student\n");
	printf("-----STUDENT PAGE-----\n");
	printf("press 1 to view the books available\n");
	printf("press 2 to rent a book \n");
	printf("press 3 to see the books rented\n");
	printf("press 4 to log out\n");
	int Studentchoice;
	printf("enter your choice:");
	scanf("%d",&Studentchoice);
	switch(Studentchoice)
	{
		case 1:
			printf("Available books\n");
			books_available();
			StudentLogin(student);
			break;
		case 2:
			printf("Rent a Book\n");
			studentchoice2(student);
			StudentLogin(student);
			break;
		case 3:
			printf("Books rented\n");
			studentchoice3();
			StudentLogin(student);
			break;
		case 4:
			printf("Successfully Logged out\n");
			break;
		default:
			printf("you pressed a wrong key.press a proper key\n");
			StudentLogin(student);
		}
	
	
}
void studentchoice2(char *student)
{
	printf("you chose to rent a book\n");
	printf("books available:\n");
	books_available();
	char book_name[50];
	printf("enter a book name:");
	scanf("%s",book_name);
	char str[50];
	fp2=fopen("Add_books.txt","r");
	int flag=0;
	int i=0;
	while(i<count)
	{
		fgets(str,sizeof(str),fp2);
		str[strcspn(str,"\n")]=0;
		if(!(strcmp(str,book_name)))
		{
			printf("hi\n");
			flag=1;
			break;
		}
		else
		{
			fgets(str,sizeof(str),fp2);
			fgets(str,sizeof(str),fp2);
			fgets(str,sizeof(str),fp2);
		}
		i++;
	}
	
	if(flag==1)
	{
		fp3=fopen("books_rented.txt","a");
		fprintf(fp3,"%s\n",books[i].name);
		fprintf(fp3,"%d\n",books[i].id);
		fprintf(fp3,"%s\n",books[i].author);
		fprintf(fp3,"%d\n",books[i].year);
		fp4=fopen("renter.txt","a");
		fprintf(fp4,"%s\n",student);
		fclose(fp4);
		
		
	}
	else
	{
		printf("book doesn't exist\n");
	}
	
	fclose(fp2);
	fclose(fp3);
}

void studentchoice3()
{
	fp2=fopen("books_rented.txt","r");
	printf("    Book Name   |   Book Id  |  Author Name  | published year\n");
	char str[50];
	int i=0;
	while(fgets(str,sizeof(str),fp2)!=NULL)
	{
		str[strcspn(str,"\n")]=0;
		printf("          %s   ",str);
		
		i++;
		if(i==4)
		{
			printf("\n");
			i=0;
		}
	}
	fclose(fp2);
}
int checkAdmin(char *str1,char *str2)
{
	char str[50];
	fp2=fopen("Admin_password.txt","r");
	while(1)
	{
		if(fgets(str,sizeof(str),fp2))
		{
			str[strcspn(str,"\n")]=0;
			if(strcmp(str,str1)==0)
			{
				printf("admin:%s",str);
				
				fgets(str,sizeof(str),fp2);
				str[strcspn(str,"\n")]=0;
				printf("\npassword:%s\n",str);
				if(strcmp(str,str2)==0)
				{
					printf("user exists\n");
					return 1;
				}
				else
				{
					printf("invalid password\n");
					return 0;
				}
					
					 
			}
		}
		else
		{
			return 0;
		}
	}fclose(fp2);
}
int checkstudent(char *str1,char *str2)
{
	char str[50];
	fp2=fopen("Student_password.txt","r");
	while(1)
	{
		if(fgets(str,sizeof(str),fp2))
		{
			str[strcspn(str,"\n")]=0;
			if(strcmp(str,str1)==0)
			{
				printf("user:%s\n",str);
				
				fgets(str,sizeof(str),fp2);
				str[strcspn(str,"\n")]=0;
				printf("pass:%s\n",str);
				if(strcmp(str,str2)==0)
				{
					printf("user exists\n");
					return 1;
				}
				else
				{
					printf("invalid password\n");
					return 0;
				}
					
					
			}
		}
		else
		{
			return 0;
		}
	}fclose(fp2);
}
int main()
{
	books=malloc(sizeof(struct book)*100);
	char ch[50];
	fp3=fopen("count.txt","r");
	fgets(ch,sizeof(ch),fp3);
	count=atoi(ch);
	fclose(fp3);
	fp2=fopen("Add_books.txt","r");
	char str[50];
	for(int i=0;i<count;i++)
	{
		fgets(str,sizeof(str),fp2);
		str[strcspn(str,"\n")]=0;
		strcpy(books[i].name,str);
		fgets(str,sizeof(str),fp2);
		str[strcspn(str,"\n")]=0;
		books[i].id=atoi(str);
		fgets(str,sizeof(str),fp2);
		str[strcspn(str,"\n")]=0;
		strcpy(books[i].author,str);
		fgets(str,sizeof(str),fp2);
		str[strcspn(str,"\n")]=0;	
		books[i].year=atoi(str);
	}
	fclose(fp2);
	printf("-----LIBRARY MANAGEMENT SYSTEM-----\n");
	printf("Press 1 to login as Admin\n");
	printf("Press 2 to login as Student\n");
	printf("Press 3 to exit from the App\n");
	int choice;
	do
	{
		printf("enter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("you chose to login as Admin\n");
				char admin[50],password1[50];
				printf("enter username:");
				scanf("%s",admin);
				printf("enter password:");
				scanf("%s",password1);
				if(checkAdmin(admin,password1))
				{	
					AdminLogin();
				}
				else
				{
					printf("Invalid Admin credentials\n");
				}
				display();
				break;
			case 2:
				printf("you chose to login as Student\n");
				char student[50],password2[50];
				printf("enter username:");
				scanf("%s",student);
				printf("enter password:");
				scanf("%s",password2);
				if(checkstudent(student,password2))
				{	
					StudentLogin(student);
				}
				else
				{
					printf("Invalid Admin credentials\n");
				}
				display();
				break;
			case 3:
				printf("You chose exit\nThank you for using our Application\n");
				exit(0);
			default:
				printf("you pressed a wrong key.press a proper key\n");
		}
	}while(choice!=3);
	return 0;
}