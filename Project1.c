//A lot of functions created in this program allow it to mimic the working of certain pre-defined functions.
//This program also mimics the working of a website in its most basic form.

#include<stdio.h>
#include<conio.h>
struct office
{
	char name[100];
	int id;
	double sal;
	double inc;
	double ded;
	double cred;
	int merit;
	int age;
	char post[35];
	char tpwd[35];
	char ppwd[35];
	char mailid[50];
	char phno[14];
};
typedef struct office ofc;
char psys[10][15]={{"messenger"},{"clerk"},{"manager"},{"cm"},{"agm"},{"dgm"},{"gm"},{"cgm"},{"dmd"},{"md"}};		//predefined posts
double salsys[10]={10000,25000,56000,105000,150000,187000,244000,290000,347000,410000};					//predefined salaries for predefined posts
int reasg[100];			//stores positions of employees for certain tools
int visor=0;			//key switch for invalid input handling
int limit=0;			//sets loop limits for reasg
int uid;			//provides a unique id to each employee
int chcou1,chcou2;		//character counters for strings
int dyn1=0,dyn2=0,dyn3=0,dyn4=0;	//dyn1--> 1 to disable and 0 to enable autosave, dyn2--> key switch for menu/list linking, dyn3--> key switch to decide print message while program exit, and dyn4--> key switch t decide last print message in invalidinputhandler function
int s;				//database size global variable
ofc o[100];			//office database array of structures global variable

void fileautosave()		//auto		//saves user-readable data into Employee database file and system-readable data into System Data file automatically
{
	if(dyn1==1)
	{
		int i,*size=&s,*ID=&uid;
		FILE *fp;
		fp=fopen("Employee Database.txt","w");
		fprintf(fp,"\nTotal no. of employees in the database= %d\n\n\n",s);
		fprintf(fp,"\nSNO.\tNAME\t\t\tAGE\tID\tPOST\tMERIT\tPH.NUMBER\tSALARY\t\tINCOME\t\tCREDITS\t\t\tDEDUCTIONS\t\tMAILID\n\n");
		for(i=0;i<s;i++)
			fprintf(fp,"%d\t%s\t\t%d\t%d\t%s\t%d\t%s\t%.2lf\t%.2lf\t%.2lf\t\t%.2lf\t\t%s\n",i+1,o[i].name,o[i].age,o[i].id,o[i].post,o[i].merit,o[i].phno,o[i].sal,o[i].inc,o[i].cred,o[i].ded,o[i].mailid);
		fprintf(fp,"\n\n\n\nID\t\tTEMP PASSWORD\t\tEMPLOYEE PWD\n\n");
		for(i=0;i<s;i++)
			fprintf(fp,"%d\t\t%s\t\t\t%s\n",o[i].id,o[i].tpwd,o[i].ppwd);
		fclose(fp);
		FILE *fpsys;
		fpsys=fopen("System Data.txt","w");
		fwrite(ID,sizeof ID,1,fpsys);
		fwrite(size,sizeof size,1,fpsys);
		fwrite(o,sizeof o,1,fpsys);
		fclose(fpsys);
	}
}

void filemanualsave()	//manual		//saves user-readable data into Employee database file and system-readable data into System Data file
{
	int i,*size=&s,*ID=&uid;
	FILE *fp;
	fp=fopen("Employee Database.txt","w");
	fprintf(fp,"\nTotal no. of employees in the database= %d\n\n\n",s);
	fprintf(fp,"\nSNO.\tNAME\t\t\tAGE\tID\tPOST\tMERIT\tPH.NUMBER\tSALARY\t\tINCOME\t\tCREDITS\t\t\tDEDUCTIONS\t\tMAILID\n\n");
	for(i=0;i<s;i++)
		fprintf(fp,"%d\t%s\t\t%d\t%d\t%s\t%d\t%s\t%.2lf\t%.2lf\t%.2lf\t\t%.2lf\t\t%s\n",i+1,o[i].name,o[i].age,o[i].id,o[i].post,o[i].merit,o[i].phno,o[i].sal,o[i].inc,o[i].cred,o[i].ded,o[i].mailid);
	fprintf(fp,"\n\n\n\nID\t\tTEMP PASSWORD\t\tEMPLOYEE PWD\n\n");
	for(i=0;i<s;i++)
		fprintf(fp,"%d\t\t%s\t\t\t%s\n",o[i].id,o[i].tpwd,o[i].ppwd);
	fclose(fp);
	FILE *fpsys;
	fpsys=fopen("System Data.txt","w");
	fwrite(ID,sizeof ID,1,fpsys);
	fwrite(size,sizeof size,1,fpsys);
	fwrite(o,sizeof o,1,fpsys);
	fclose(fpsys);
}

void filemanualread()		//manual+auto	//reads and restores values of certain global variables essential for future use of this program
{
	int i,*size=&s,*ID=&uid;
	FILE *fpsys;
	fpsys=fopen("System Data.txt","r");
	fread(ID,sizeof ID,1,fpsys);
	fread(size,sizeof size,1,fpsys);
	fread(o,sizeof o,1,fpsys);
	fclose(fpsys);
}

int int_scanner()		//user-defined error-free scanner function for scanning integers(u2)
{
	int int_val;
	fflush(stdin);
	while(!scanf("%d",&int_val))
	{
		fflush(stdin);
		printf("invalid datatype provided. provide an integer: ");
	}
	return int_val;
}

double double_scanner()		//user-defined error-free scanner function for scanning doubles(u2)
{
	double double_val;
	fflush(stdin);
	while(!scanf("%lf",&double_val))
	{
		fflush(stdin);
		printf("invalid datatype provided. provide a real number/integer: ");
	}
	return double_val;
}

char *string_scanner()		//user-defined error-free scanner function for scanning strings(u2)
{
	static char str[50];
	fflush(stdin);
	while(!scanf(" %[^\n]",str))
	{
		fflush(stdin);
		printf("invalid datatype provided. provide a string/character: ");
	}
	return str;
}

char character_scanner()		//user-defined error-free scanner function for scanning characters(u2)
{
	char ch;
	fflush(stdin);
	while(!scanf(" %c",ch))
	{
		fflush(stdin);
		printf("invalid datatype provided. provide a character: ");
	}
	return ch;
}

void invalidinputhandler()	  //auto	//invalid choice handling function
{
	int i;
	printf("\n\t\t\t\t\t\t\t\t\t\t   INVALID INPUT RECIEVED!\n\t\t\t\t\t\t\t\t\tThe choice provided by you does not match any from the list of choices.\n\t\t\t\t\t\t\t\t\tPlease exercise care in providing a choice now:\n\n");
	printf("\t\t\t\t\t\t\t\t\tEnter '1' to go back to where you were redirected from and use the tool or provide a valid choice again\n\t\t\t\t\t\t\t\t\t");
	if(dyn4==0)printf("Enter '0' to logout\n\t\t\t\t\t\t\t\t\t");
	else printf("Enter '0' to exit the program\n\t\t\t\t\t\t\t\t\t");
	i=int_scanner();
	switch(i)
	{
	  case 1:visor=0;dyn4=0;return;
	  case 0:visor=0;dyn2=4;return;
	  default :visor=0;dyn2=4;dyn3=1;return;
	}
}

void display()	//auto+manual	//database displaying function
{
	int i=0;
	printf("\n");
	printf("Details of all the Employees are:\n");
	printf("\nSNO.\tNAME\t\t\tAGE\tID\tPOST\tMERIT\tPH.NUMBER\tSALARY\t\tINCOME\t\tCREDITS\t\t\tDEDUCTIONS\t\tMAILID\n\n");
	for(i=0;i<s;i++)
	  printf("%d\t%s\t\t%d\t%d\t%s\t%d\t%s\t%.2lf\t%.2lf\t%.2lf\t\t%.2lf\t\t%s\n",i+1,o[i].name,o[i].age,o[i].id,o[i].post,o[i].merit,o[i].phno,o[i].sal,o[i].inc,o[i].cred,o[i].ded,o[i].mailid);
	printf("\n");
	
}

void idgenauto()	//auto		//generates IDs for every employee
{
	int i;
	for(i=0;i<s;i++)
	{
		o[i].id=uid;
		uid++;
	}
}

void temppwdgenauto()	//auto		//generates a temporary password for every employee's data
{
	int i,j;
		for(i=0;i<s;i++)
		{
			if(o[i].ppwd[0]=='\0')
			{
				for(j=0;o[i].name[j]!=' '&&o[i].name[j]!='\0';j++)
				{
					o[i].tpwd[j]=o[i].name[j];
				}
			}
		}
}

void charcounter(char str1[],char str2[])	//auto	//counts the no.of characters of the 2 strings provided to it
{
	int i;
	chcou1=0;
	chcou2=0;
	for(i=0;str1[i]!='\0';i++)
		chcou1++;
	for(i=0;str2[i]!='\0';i++)
		chcou2++;
}

void stringassignauto(char *strd,char *strc)		//auto	//copies one string onto another
{
	int i;
	charcounter(strd,strc);
	for(i=0;i<chcou2;i++)
		strd[i]=strc[i];
	strd[i]='\0';
}

void postissueredirect()	//auto	//redirects user to assign post again
{
	int i,j;
	char *cpost;
	for(i=0;i<limit;i++)
	{
		
		printf("Enter a new post for employee id---> %d: ",o[reasg[i]].id);
		cpost=string_scanner();
		stringassignauto(o[reasg[i]].post,cpost);
	}
}

int stringcheckauto(char str1[],char str2[])		//auto	//checks if provided 2 strings are the same
{
	int i,c=0;
	charcounter(str1,str2);
	for(i=0;i<chcou1;i++)
	{
		if(chcou1!=chcou2||str1[i]!=str2[i])
			break;
	}
	if(i==chcou1)
		return 1;
	else
		return 0;
}

void postissuehandler()		//auto	//handles invalid post entries
{
	int i,j,c,m;
	LB:
	visor=0;
	m=0;
	for(i=limit-1;i>=0;i--)
	{
		reasg[i]=reasg[i+1];
	}
	for(i=0;i<s;i++)
	{
		c=0;
		for(j=0;j<10;j++)
		{
			if(stringcheckauto(o[i].post,psys[j])==0)
				c++;
		}
		if(c==10)
		{
			reasg[m]=i;
			m++;
			limit=m;
			visor++;
		}
	}
	if(visor!=0)
	{
			printf("\nA total of %d employee(s) has/have been assigned invalid post. Their details are:\n\n",visor);
			for(i=0;i<limit;i++)
			{
				printf("name--> %s\nid--> %d\nage--> %d\npost--> %s\n\n",o[reasg[i]].name,o[reasg[i]].id,o[reasg[i]].age,o[reasg[i]].post);
			}
				printf("please note down the employee id(s) of this/these employee(s)\n\n");
				postissueredirect();
				goto LB;
	}
}

void salaryassignauto()		//auto  //assigns predefined salary to the post of employees 
{
	int i,j;
	for(i=0;i<s;i++)
	{
		for(j=0;j<10;j++)
		{
			if(stringcheckauto(o[i].post,psys[j])==1)
				o[i].sal=salsys[j];
		}
	}
}

void salarysysscheme()	//manual //shows the predefined salaries asscociated with predefined posts
{
	int i,j;
	printf("\n\nPost\t\tSalary\n\n");
	printf("%s\t%.2lf\n",psys[0],salsys[0]);
	for(i=1;i<10;i++)
	{
		printf("%s\t\t%.2lf\n",psys[i],salsys[i]);
	}
}

void viewposts()		//manual+auto	//Shows posts that are predefined in this function
{
	int i;
	printf("\n\nThe pre-defined posts are shown below:\n");
	for(i=0;i<10;i++)
	{
		printf("%s\t",psys[i]);
	}
}

void postassignself()		//manual	 //post assigning/updating function---> A.1.1
{
	char *npost;
	int id,i;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	printf("Enter new post: ");
	npost=string_scanner();
	  for(i=0;i<s;i++)
	  {
		if(id==o[i].id)
		{
			stringassignauto(o[i].post,npost);
			postissuehandler();salaryassignauto();o[i].inc=o[i].sal;o[i].cred=0.00;o[i].ded=0.00;
			printf("\nUpdate another employee's post?\nEnter '1' to update another post\nEnter '2' to return to previous menu\n");
			i=int_scanner();
			switch(i)
			{
			  case 1:display();fileautosave();goto LB1;
			  case 2:display();fileautosave();return;
			  default :visor=1;goto LB1;
			}
		}
	  }
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	LBE:
		return;
}

void meritassignself()		//manual	 //merit assigning/updating function---> A.1.2
{
	int nmerit,id,i;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	printf("Enter new merit: ");
	nmerit=int_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
		{
			o[i].merit=nmerit;
			printf("\nUpdate another employee's merit?\nEnter '1' to update another merit\nEnter '2' to return to previous menu\n");
			i=int_scanner();
			switch(i)
			{
			  case 1:display();fileautosave();goto LB1;
			  case 2:display();fileautosave();return;
			  default :visor=1;goto LB1;
			}
		}
	}
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	LBE:
		return;
}

void creddedassignself()  	//manual	 //credit/deduction assigning/updating function---> A.1.3
{
	int id,i,j;
	double mon;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
			break;
	}
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	printf("Employees's details:\n");
	printf("\nName-->        %s\nage-->         %d\npost-->        %s\nsalary-->      %.2lf\ndeductions-->  %.2lf\ncredits-->     %.2lf\nincome-->      %.2lf\n\n",o[i].name,o[i].age,o[i].post,o[i].sal,o[i].ded,o[i].cred,o[i].inc);
	printf("How would you like to update this employee's salary?\nEnter '1' to credit money in the salary\nEnter '2' to deduct money from the salary\n");
	j=int_scanner();
	switch(j)
	{
		case 1:printf("\nEnter amount of money to credit: ");mon=double_scanner();o[i].inc+=mon;o[i].cred+=mon;fileautosave();break;
		case 2:printf("\nEnter amount of money to deduct: ");mon=double_scanner();o[i].inc-=mon;o[i].ded+=mon;fileautosave();break;
		default :visor=1;goto LB1;
	}
	printf("\n\nUpdate another employee's salary?\nEnter '1' to update another salary\nEnter '2' to return to previous menu\n");
	j=int_scanner();
	switch(j)
	{
	  case 1:display();fileautosave();goto LB1;
	  case 2:display();fileautosave();return;
	  default :visor=1;goto LB1;
	}
	LBE:
		return;
}

void agereassignself()		//manual	//age updating function---> A.1.4
{
	int nage,id,i;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	printf("Enter new age: ");
	nage=int_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
		{
			o[i].age=nage;
			printf("\nUpdate another employee's age?\nEnter '1' to update another age\nEnter '2' to return to previous menu\n");
			i=int_scanner();
			switch(i)
			{
			  case 1:display();fileautosave();goto LB1;
			  case 2:display();fileautosave();return;
			  default :visor=1;goto LB1;
			}
		}
	}
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	LBE:
		return;
}

void namereassignself()		//manual	//name updating function---> A.1.5
{
	char *newname;
	int id,i;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	printf("Enter new name: ");
	newname=string_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
		{
			stringassignauto(o[i].name,newname);
			printf("\nUpdate another employee's name?\nEnter '1' to update another name\nEnter '2' to return to previous menu\n");
			i=int_scanner();
			switch(i)
			{
			  case 1:display();fileautosave();goto LB1;
			  case 2:temppwdgenauto();display();fileautosave();return;
			  default :temppwdgenauto();visor=1;goto LB1;
			}
		}
	}
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	LBE:
		return;
}

void mailidreassignself()	//manual	//mailid updating function---> A.1.6
{
	char *nmailid;
	int id,i;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	printf("Enter new mailid: ");
	nmailid=string_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
		{
			stringassignauto(o[i].mailid,nmailid);
			printf("\nUpdate another employee's mailid?\nEnter '1' to update another mailid\nEnter '2' to return to previous menu\n");
			i=int_scanner();
			switch(i)
			{
			  case 1:display();fileautosave();goto LB1;
			  case 2:display();fileautosave();return;
			  default :visor=1;goto LB1;
			}
		}
	}
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	LBE:
		return;
}

void phnoreassignself()		//manual	//phone number updating function---> A.1.7
{
	char *nphno;
	int id,i;
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("Enter the id of the employee for whom you wish to update: ");
	id=int_scanner();
	printf("enter new phone number: ");
	nphno=string_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
		{
			stringassignauto(o[i].phno,nphno);
			printf("\nUpdate another employee's phone number?\nEnter '1' to update another phone number\nEnter '2' to return to previous menu\n");
			i=int_scanner();
			switch(i)
			{
			  case 1:display();fileautosave();goto LB1;
			  case 2:display();fileautosave();return;
			  default :visor=1;goto LB1;
			}
		}
	}
	if(i==s)
	{
	  printf("\n\n\t\t\tThe employee Id provided by you does not match any from the database. No changes were made.\n\n\n");
	  return;
	}
	LBE:
		return;
}

void serdel()		//manual	//employee detail searching and deleting function---> A.2.1
{
	int id,i=0;
	printf("\nEnter the employee's id you wish to delete: ");
	id=int_scanner();
	for(i=0;i<s;i++)
	{
	  if(id==o[i].id)
	    break;
	}
	if(i==s)
	{
	  printf("\n\t\t\tThe employee was not found. No changes were made.\n");
	  return;
	}
	for(;i<s-1;i++)
	{
	  o[i]=o[i+1];
	}
	s--;
	display();
}

void posdel()	//manual	//database position deleting function---> A.2.2
{
	int p,i=0;
	printf("\nEnter a position you wish to delete: ");
	p=int_scanner();
	if(p<1||p>s)
	{
	  printf("\n\t\t\tInvalid input recieved. No changes were made.\n");
	  return;
	}
	for(i=p-1;i<s-1;i++)
	{
	  o[i]=o[i+1];
	}
	s--;
	display();
}

void agelimdel()	//manual		//employee limiting age deleting function---> A.2.3
{
	int i=0,c=0,j,age;
	printf("\nEnter a limiting age: ");
	age=int_scanner();
	for(i=0;i<s;i++)
	{
	  if(age<o[i].age)
	  {
	    c++;
	    for(j=i;j<s-1;j++)
		o[j]=o[j+1];
	    s--;
	    i--;
	  }
	}
	if(c==0)
	{
	  printf("\n\t\t\tNo employees had age more than limiting age-->%d. No changes were made.\n",age);
	  return;
	}
	else
	printf("\n\t\t\tA total of %d employee(s) had age more than the limiting age and hence were removed from the database.",c);
	display();
}

void dupdel()	//manual	//duplicate employee details deleting function---> A.2.4
{
	int i=0,j,k,c=0;
	for(i=0;i<s-1;i++)
	{
	  for(j=i+1;j<s;j++)
	  {
	    if(stringcheckauto(o[i].name,o[j].name)==1&&stringcheckauto(o[i].post,o[j].post)==1&&o[i].age==o[j].age&&stringcheckauto(o[i].mailid,o[j].mailid)==1&&stringcheckauto(o[i].phno,o[j].phno)==1)
	    {
		  c++;
		  for(k=j;k<s-1;k++)
		    o[k]=o[k+1];
		  s--;
		  j--;
		}
	  }
	}
	if(c==0)
	{
		printf("\n\t\t\tNo duplicate employee details were found\n\n\n");
		goto LBE;
	}
	else
		printf("\n\t\t\tA total of %d duplicate emp details(s) were found and deleted\n",c);
	display();
	visor=0;
	LB1:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("\n\nSince duplicate employee details are deleted, there is a chance that original income of some employees got deleted, would you like to update those for certain employees?\n");
	do
	{
	  printf("\n\nEnter '1' to update merit\nEnter '2' to update credit and/or deduction\n");
	  printf("Enter '3' to view the predefined salary scheme\n\n");
	  if(dyn1==0)
	  {
		  printf("Enter '4' to save data in Employee Database file\nEnter '5' to enable autosave\n");
	  }
	  else
		  printf("Enter '6' to disble autosave\n");
	  printf("Enter '15' to display employee details\nEnter '0' to leave data as it is\n");
	  i=int_scanner();
	  switch(i)
	  {
		case 1:meritassignself();fileautosave();break;
		case 2:creddedassignself();fileautosave();break;
		case 3:salarysysscheme();fileautosave();break;
		case 4:filemanualsave();if(dyn1==1){visor=1;goto LB1;}break;
		case 5:if(dyn1==1){visor=1;goto LB1;}dyn1=1;break;
		case 6:if(dyn1==0){visor=1;goto LB1;}dyn1=0;break;
		case 15:display();break;
		case 0:break;
	  	default :visor=1;goto LB1;
	  }
	}while(i!=0);
	LBE:
	return;
}

void empadd()	//manual  	//adding an employee detail in runtime function-->	A.3
{
	int i=0,inp,pos,prepos;
	visor=0;
	LB2:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("\nEnter the two positions between which you wish to add your Employee\n");
	LB1:
	prepos=int_scanner();
	pos=int_scanner();
	if(prepos==pos+1)
	  pos=prepos;
	else if(pos==prepos+1)
	  pos=pos+0;
	else
	{
	  printf("\n\t\t\tThe positions provided by you are invalid. Do you wish to provide the two positions again?\nEnter '1' to provide again\nEnter '2' to return to the database editing tools menu\n");
	  i=int_scanner();
	  switch(i)
	  {
	    case 1:printf("Enter the two positions again:\n");goto LB1;
	    case 2:return;
	    default :visor=1;goto LB2;
	  }
	}
	if(pos<1||pos-1>s)
	{
	  printf("\n\t\t\tThe positions '%d' and '%d' provided by you define an area outside the bounds of your database [1,%d]\n",prepos,pos,s+1);
	  printf("\t\t\tNo changes were made to your database. Size was restored to [1,%d]\n",s);
	  return;
	}
	s++;
	for(i=s-2;i>=pos-1;i--)
	{
	  o[i+1]=o[i];
	}
	printf("Enter the details of the employee you wish to add in your database:\n");
	printf("\nEnter employee's name: ");
	char *nname=string_scanner();
	stringassignauto(o[pos-1].name,nname);
	printf("Enter employee's age: ");
	o[pos-1].age=int_scanner();
	printf("Enter employee's post: ");
	char *npost=string_scanner();
	stringassignauto(o[pos-1].post,npost);
	printf("Enter employee's mailid: ");
	char *nmail=string_scanner();
	stringassignauto(o[pos-1].mailid,nmail);
	printf("Enter employee's phone number: ");
	char *nphno=string_scanner();
	stringassignauto(o[pos-1].phno,nphno);
	o[pos-1].id=uid;
	uid++;
	postissuehandler();
	o[pos-1].ppwd[0]='\0';
	temppwdgenauto();
	o[pos-1].cred=0;
	o[pos-1].ded=0;
	o[pos-1].merit=0;
	salaryassignauto();
	o[pos-1].inc=o[pos-1].sal;
	o[pos-1].merit=0;
	display();
	LBE:
		return;
}

void sortpost()		//manual		//databse sorting function to sort similar posts nearby---> A.4
{
	int i=0,j,k=0;
	ofc t[100];
	for(i=0;i<10;i++)
	{
		for(j=0;j<s;j++)
		{
			if(stringcheckauto(o[j].post,psys[i])==1)
			{
				t[k]=o[j];
				k++;
			}
		}
	}
	for(i=0;i<s;i++)
	{
		o[i]=t[i];
	}
}
void sortid()	//manual	//database sorting function to sort in ascending order of employee Ids---> A.5
{
	int i=0,j;
	ofc t;
	for(i=0;i<s;i++)
	{
	  for(j=0;j<s;j++)
	    if(o[i].id<=o[j].id)
		{
		  t=o[i];
		  o[i]=o[j];
		  o[j]=t;
		}
	}
}

void search()	//manual		//employee details and position in database searching function---> B.1.1
{
	int i=0,id;
	printf("\nenter the id of the employee you wish to search details for: ");
	id=int_scanner();
	for(i=0;i<s;i++)
	{
	  if(id==o[i].id)
	  {
	    break;
	  }
	}
	if(i==s)
	  printf("\n\t\t\tThe employee with the id provided by you was not found\n\n");
	else
	  printf("\nSNO.\tNAME\t\t\tAGE\tID\tPOST\tMERIT\tPH.NUMBER\tSALARY\t\tINCOME\t\tCREDITS\t\t\tDEDUCTIONS\t\tMAILID\n\n");
	  printf("%d\t%s\t\t%d\t%d\t%s\t%d\t%s\t%.2lf\t%.2lf\t%.2lf\t\t%.2lf\t\t%s\n",i+1,o[i].name,o[i].age,o[i].id,o[i].post,o[i].merit,o[i].phno,o[i].sal,o[i].inc,o[i].cred,o[i].ded,o[i].mailid);
	  printf("\n");
}

void searchbyname()		//manual	//searches for employees associated with the same name---> B.1.2
{
	int i=0,j=0;
	char *sername;
	for(i=limit-1;i>=0;i--)
	{
		reasg[i]=reasg[i+1];
	}
	ofc t[100];
	limit=0;
	printf("\nEnter the name for which you wish to search for employees associated with: ");
	sername=string_scanner();
	for(i=0;i<s;i++)
	{
	  if(stringcheckauto(sername,o[i].name)==1)
	  {
	    t[j]=o[i];
	    reasg[j]=i+1;
	    j++;
	  }
	}
	limit=j;
	if(j==0)
	  printf("\n\t\t\tNo employess were associated with name---> %s\n\n",sername);
	else
	{
		printf("\n\t\t\tA total of %d employee(s) was/were found associated with name---> %s. Their details are:\n\n",j,sername);
		printf("\n\n");
		printf("\nSNO.\tNAME\t\t\tAGE\tID\tPOST\tMERIT\tPH.NUMBER\tSALARY\t\tINCOME\t\tCREDITS\t\t\tDEDUCTIONS\t\tMAILID\n\n");
		for(j=0;j<limit;j++)
			printf("%d\t%s\t\t%d\t%d\t%s\t%d\t%s\t%.2lf\t%.2lf\t%.2lf\t\t%.2lf\t\t%s\n",reasg[j],t[j].name,t[j].age,t[j].id,t[j].post,t[j].merit,t[j].phno,t[j].sal,t[j].inc,t[j].cred,t[j].ded,t[j].mailid);
		printf("\n");
	}
}

void searchbypost()		//manual	//searches for employees associated with the same post---> B.1.3
{
	int i=0,j=0;
	char *serpost;
	for(i=limit-1;i>=0;i--)
	{
		reasg[i]=reasg[i+1];
	}
	ofc t[100];
	limit=0;
	printf("\nEnter the post for which you wish to search for employees associated with: ");
	serpost=string_scanner();
	for(i=0;i<s;i++)
	{
	  if(stringcheckauto(serpost,o[i].post)==1)
	  {
	    t[j]=o[i];
	    reasg[j]=i+1;
	    j++;
	  }
	}
	limit=j;
	if(j==0)
	  printf("\n\t\t\tNo employess were associated with post---> %s\n\n",serpost);
	else
	{
		printf("\n\t\t\tA total of %d employee(s) was/were found associated with post---> %s. Their details are:\n\n",j,serpost);
		printf("\n\n");
	  	printf("\nSNO.\tNAME\t\t\tAGE\tID\tPOST\tMERIT\tPH.NUMBER\tSALARY\t\tINCOME\t\tCREDITS\t\t\tDEDUCTIONS\t\tMAILID\n\n");
		for(j=0;j<limit;j++)
			printf("%d\t%s\t\t%d\t%d\t%s\t%d\t%s\t%.2lf\t%.2lf\t%.2lf\t\t%.2lf\t\t%s\n",reasg[j],t[j].name,t[j].age,t[j].id,t[j].post,t[j].merit,t[j].phno,t[j].sal,t[j].inc,t[j].cred,t[j].ded,t[j].mailid);
		printf("\n");
	}
}

void searchbynameguest()	//for the use of search by guest
{
	int i=0,j=0;
	char *sername;
	for(i=limit-1;i>=0;i--)
	{
		reasg[i]=reasg[i+1];
	}
	ofc t[100];
	limit=0;
	printf("\nEnter the name for which you wish to search for employees associated with: ");
	sername=string_scanner();
	for(i=0;i<s;i++)
	{
	  if(stringcheckauto(sername,o[i].name)==1)
	  {
	    t[j]=o[i];
	    reasg[j]=i+1;
	    j++;
	  }
	}
	limit=j;
	if(j==0)
	  printf("\n\t\t\tNo employess were associated with name---> %s\n\n",sername);
	else
	{
	  printf("\n\t\t\tA total of %d employee(s) was/were found associated with name---> %s. Their contact details are:\n\n",j,sername);
	  printf("\n\n");
	  printf("NAME\t\t\tPOST\t\tPHONE NUMBER\t\tMAIL ID\n\n");
	  for(j=0;j<limit;j++)
	    printf("%s\t\t%s\t\t%s\t\t%s\n",t[j].name,t[j].post,t[j].phno,t[j].mailid);
	    printf("\n\n");
	}
}

void searchbypostguest()	//for the use of search by guest
{
	int i=0,j=0;
	char *serpost;
	for(i=limit-1;i>=0;i--)
	{
		reasg[i]=reasg[i+1];
	}
	ofc t[100];
	limit=0;
	printf("\nEnter the post for which you wish to search for employees associated with: ");
	serpost=string_scanner();
	for(i=0;i<s;i++)
	{
	  if(stringcheckauto(serpost,o[i].post)==1)
	  {
	    t[j]=o[i];
	    reasg[j]=i+1;
	    j++;
	  }
	}
	limit=j;
	if(j==0)
	  printf("\n\t\t\tNo employess were associated with post---> %s\n\n",serpost);
	else
	{
	  printf("\n\t\t\tA total of %d employee(s) was/were found associated with post---> %s. Their details are:\n\n",j,serpost);
	  printf("\n\n");
	  printf("NAME\t\t\tPOST\t\tPHONE NUMBER\t\tMAIL ID\n\n");
	  for(j=0;j<limit;j++)
	   printf("%s\t\t%s\t\t%s\t\t%s\n",t[j].name,t[j].post,t[j].phno,t[j].mailid);
	   printf("\n\n");
	}
}

void bgsmmerit()	//manual	//biggest and smallest merit finder---> B.2.1
{
	int bmer,smer,i=0;
	ofc be,se;
	bmer=o[0].merit;
	smer=o[0].merit;
	be=o[0];
	se=o[0];
	for(i=1;i<s;i++)
	{
	  if(bmer<o[i].merit)
	  {
	    bmer=o[i].merit;
	    be=o[i];
	  }
	  if(smer>o[i].merit)
	  {
	    smer=o[i].merit;
	    se=o[i];
	  }
	}
	printf("\nThe employee with highest merit= %d has details:\n\nemployee name-->  %s\nid-->             %d\nsalary-->         %.2lf\nage-->            %d\npost-->           %s\nmailid-->         %s\nphone number-->   %s\n\n\n",bmer,be.name,be.id,be.sal,be.age,be.post,be.mailid,be.phno);
	printf("The employee with lowest merit= %d has details:\n\nemployee name-->  %s\nid-->             %d\nsalary-->         %.2lf\nage-->            %d\npost-->           %s\nmailid-->         %s\nphone number-->   %s\n\n\n",smer,se.name,se.id,se.sal,se.age,se.post,se.mailid,se.phno);
}

void bgsmage()	//manual	//biggest and smallest age finder---> B.2.2
{
	int bage,sage,i=0;
	ofc be,se;
	bage=o[0].age;
	sage=o[0].age;
	be=o[0];
	se=o[0];
	for(i=1;i<s;i++)
	{
	  if(bage<o[i].age)
	  {
	    bage=o[i].age;
	    be=o[i];
	  }
	  if(sage>o[i].age)
	  {
	    sage=o[i].age;
	    se=o[i];
	  }
	}
	printf("\nThe oldest employee has details:\n\nemployee name-->  %s\nid-->             %d\nsalary-->         %.2lf\nage-->            %d\nmerit-->          %d\npost-->           %s\nmailid-->         %s\nphone number-->   %s\n\n\n",be.name,be.id,be.sal,be.age,be.merit,be.post,be.mailid,be.phno);
	printf("The youngest employee has details:\n\nemployee name-->  %s\nid-->             %d\nsalary-->         %.2lf\nage-->            %d\nmerit-->          %d\npost-->           %s\nmailid-->         %s\nphone number-->   %s\n\n\n",se.name,se.id,se.sal,se.age,se.merit,se.post,se.mailid,se.phno);
}

void bgsminc()	//manual		//biggest and smallest income finder---> B.2.3
{
	int i;
	double bs,ss;
	ofc be,se;
	bs=o[0].inc;
	ss=o[0].inc;
	be=o[0];
	se=o[0];
	for(i=1;i<s;i++)
	{
	  if(bs<o[i].inc)
	  {
	    bs=o[i].inc;
	    be=o[i];
	  }
	  if(ss>o[i].inc)
	  {
	    ss=o[i].inc;
	    se=o[i];
	  }
	}
	printf("\nThe employee with highest income= %.2lf has details:\n\nemployee name-->  %s\nid-->             %d\nsalary-->         %.2lf\nage-->            %d\nmerit-->          %d\npost-->           %s\nmailid-->         %s\nphone number-->   %s\n\n\n",bs,be.name,be.id,be.sal,be.age,be.merit,be.post,be.mailid,be.phno);
	printf("The employee with lowest income= %.2lf has details:\n\nemployee name-->  %s\nid-->             %d\nsalary-->         %.2lf\nage-->            %d\nmerit-->          %d\npost-->           %s\nmailid-->         %s\nphone number-->   %s\n\n\n",ss,se.name,se.id,se.sal,se.age,se.merit,se.post,se.mailid,se.phno);
}

void mainmenu()		//auto save toggle, read previously saved data or create new data and initialise toggle, linking with sub-menus
{
	void submenuA();
	void submenuB();
	int i,size;
	visor=0;
	LB2:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("\n\nBefore you continue, please specify if you wish to enable the 'auto save' feature of this program.\nYou can change this later in the program.\n");
	printf("Enter '1' to enable\nEnter '0' if you wish for it to remain disabled\n");
	i=int_scanner();
	switch(i)
	{
		case 1:dyn1=1;break;
		case 0:break;
		default:visor=1;goto LB2;
	}
	visor=0;
	LBN:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("\n\nDo you wish to access previous data from the Employee Database file?\n");
	printf("enter '1' to access\nEnter '2' to create new data\n");
	i=int_scanner();
	switch(i)
	{
		case 1:filemanualread();goto LB3;
		case 2:break;
		default :visor=1;goto LBN;
	}
	visor=0;
	LB4:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	printf("\n\nSpecify the no. of employees you wish to store: ");
	LB1:
	s=int_scanner();
	if(s<1||s>100)
	{
	  printf("\nInvalid size of array provided(input size exceeds limits of predefined size=[1,100])\n");
	  printf("\nDo you wish to provide another array size?\nEnter '1' to provide another array size\nEnter '2' to logout\n");
	  i=int_scanner();
	  switch(i)
	  {
		case 1:printf("\nEnter a new size(specify new no.of employee data to store): ");goto LB1;
		case 2:return;
		default :visor=1;goto LB4;
	  }	  
	}
	printf("\n");
	for(i=0;i<s;i++)
	{
		printf("enter emp%d name: ",i+1);
		char *new_name=string_scanner();
		stringassignauto(o[i].name,new_name);
		printf("enter emp%d age: ",i+1);
		o[i].age=int_scanner();
		printf("enter emp%d post: ",i+1);
		char *new_post=string_scanner();
		stringassignauto(o[i].post,new_post);
		printf("enter emp%d mailid: ",i+1);
		char *new_mail=string_scanner();
		stringassignauto(o[i].mailid,new_mail);
		printf("enter emp%d phone number: ",i+1);
		char *new_phno=string_scanner();
		stringassignauto(o[i].phno,new_phno);
		o[i].cred=0;o[i].ded=0;o[i].merit=0;
	}
	uid=1;
	idgenauto();
	postissuehandler();
	for(i=0;i<s;i++)
	  o[i].ppwd[0]='\0';
	temppwdgenauto();
	salaryassignauto();
	for(i=0;i<s;i++)
		o[i].inc=o[i].sal;
	if(dyn1!=0)
		fileautosave();
	visor=0;
	LB3:
	if(visor!=0)
	{
	  invalidinputhandler();
	  if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is a list of sub menus. Choose one accordingly to your need:\n\n");
		printf("Enter '1' to view the menu of a variety of database editing tools\n");
		printf("Enter '2' to view the menu of statistics displaying tools. these do not edit your database in any way\n");
		printf("Enter '3' to view the various posts pre-defined in the database\nEnter '4' to view the salary scheme for different posts\n\n");
		if(dyn1==0)
		{
		printf("Enter '5' to save data in the Employee Database file\n");
		printf("Enter '6' to enable auto save\n");
		}
		else
			printf("Enter '7' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:
			{
				printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");
				submenuA();fileautosave();if(dyn2==4)return;if(dyn2==3)return;
			}break;
			case 2:
			{
				printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");	
				submenuB();fileautosave();if(dyn2==4)return;if(dyn2==3)return;
			}break;
			case 3:viewposts();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 4:salarysysscheme();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 5:filemanualsave();if(dyn1==1){visor=1;goto LB3;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 6:if(dyn1==1){visor=1;goto LB3;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 7:if(dyn1==0){visor=1;goto LB3;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB3;
		}	
	}while(i!=0);
	LBE:
		return;
}

void submenuA()		//Database editing tools menu	//linking with nested-menus A1 and A2
{
	void nestedmenuA1();
	void nestedmenuA2();
	int i;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is a menu of various database editing tools.\nPlease provide your choice after having a look at the menu\n\n");
		printf("Enter '1' to view the list of the tools that allow you to assign/reassgin employee particulars for each employee on an individual basis\n");
		printf("Enter '2' to view the list of the tools that will provide you with a variety of deleting options\n");
		printf("Enter '3' to add an employee with his/her details in a position in the database\n");
		printf("Enter '4' to sort the database so as to put employees with the same post together\nEnter '5' to sort the database in ascending order of employee Ids\n\n");
		printf("Enter '6' to return to the main menu\n");
		if(dyn1==0)
		{
			printf("Enter '7' to save data in the Employee Database file\n");
			printf("Enter '8' to enable auto save\n");
		}
		else
			printf("Enter '9' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to log out\n");
		i=int_scanner();
		switch(i)
		{
			case 1:
			{
				printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");
				LB2:
				nestedmenuA1();if(dyn2==4)return;if(dyn2==3)return;
				else if(dyn2==1)
				{
					dyn2=0;
					return;
				}	
				else if(dyn2==2)
				{
					dyn2=0;
					nestedmenuA2();if(dyn2==4)return;if(dyn2==2)goto LB2;else if(dyn2==3)return;else if(dyn2==1)return;
				}
			}break;
			case 2:
			{
				printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");
				LB3:
				nestedmenuA2();if(dyn2==4)return;if(dyn2==3)return;
				else if(dyn2==1)
				{
					dyn2=0;
					return;
				}
				else if(dyn2==2)
				{
					dyn2=0;
					nestedmenuA1();if(dyn2==4)return;if(dyn2==2)goto LB3;else if(dyn2==3)return;else if(dyn2==1)return;
				}	
			}break;
			case 3:empadd();if(dyn2==4)return;temppwdgenauto();fileautosave();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 4:sortpost();fileautosave();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 5:sortid();fileautosave();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 6:printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");return;
			case 7:filemanualsave();if(dyn1==1){visor=1;goto LB1;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 8:if(dyn1==1){visor=1;goto LB1;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 9:if(dyn1==0){visor=1;goto LB1;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB1;
		}
	}while(i!=0);
	dyn2=3;
	LBE:
		return;
}

void nestedmenuA1()		//assigning or updating tools list	//linking with nested-menu A2
{
	void nestedmenuA2();
	int i;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is the list of tools to assign/update individual employee particulars:\n\n");
		printf("Enter '1' to assign/update a post to an employee\nEnter '2' to assign/update merit to an employee\nEnter '3' to assign credit/deduction to an employee's salary\n");
		printf("Enter '4' to update age of an employee\nEnter '5' to update name of an employee\n");
		printf("Enter '6' to update mailid of an employee\nEnter '7' to update phone number of an employee\n\n");
		printf("Enter '8' to go back to the menu of database editing tools\nEnter '9' to view the list of deleting tools\nEnter '10' to return to the main menu\n");
		if(dyn1==0)
		{
			printf("Enter '11' to save data in the Employee Database file\n");
			printf("Enter '12' to enable auto save\n");
		}
		else
			printf("Enter '13' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:postassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 2:meritassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 3:creddedassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 4:agereassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 5:namereassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 6:mailidreassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 7:phnoreassignself();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 8:dyn2=0;printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");return;
			case 9:dyn2=2;printf("\n\n--------------------|----------------------------|-----------------------------|------------------------------|-----------------------------|--------------------------|------------------------\n");return;
			case 10:dyn2=1;printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");return;
			case 11:filemanualsave();if(dyn1==1){visor=1;goto LB1;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 12:if(dyn1==1){visor=1;goto LB1;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 13:if(dyn1==0){visor=1;goto LB1;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB1;	
		}
	}while(i!=0);
	dyn2=3;
	LBE:
		return;
}

void nestedmenuA2()		//data deleting tools list	//linking with nested-menu A1
{
	int i;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is the list of tools that provide you with a variety of deleting options:\n\n");
		printf("Enter '1' to delete all data of an employee from the database by providing employee's id\n");
		printf("Enter '2' to delete a particular position in the database(It is advised to use the statistics menu to have the best use of this tool)\n");
		printf("Enter '3' to delete all employee data that has age above a limiting age set by you\n");
		printf("Enter '4' to delete duplicate employee details(if any such exists)\n\n");
		printf("Enter '5' to go back to the menu of database editing tools\nEnter '6' to view the list of assign/update tools\nEnter '7' to return to the main menu\n");
		if(dyn1==0)
		{
			printf("Enter '8' to save data in the Employee Database file\n");
			printf("Enter '9' to enable auto save\n");
		}
		else
			printf("Enter '10' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:serdel();fileautosave();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 2:posdel();fileautosave();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 3:agelimdel();fileautosave();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 4:dupdel();fileautosave();if(dyn2==4)return;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 5:dyn2=0;printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");return;
			case 6:dyn2=2;printf("\n\n--------------------|----------------------------|-----------------------------|------------------------------|-----------------------------|--------------------------|------------------------\n");return;
			case 7:dyn2=1;printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");return;
			case 8:filemanualsave();if(dyn1==1){visor=1;goto LB1;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 9:if(dyn1==1){visor=1;goto LB1;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 10:if(dyn1==0){visor=1;goto LB1;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB1;
		}
	}while(i!=0);
	dyn2=3;
	LBE:
		return;
}

void submenuB()		//Database statistics displaying tools menu		//linking with nested-menus B1 and B2
{
	void nestedmenuB1();
	void nestedmenuB2();
	int i;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is the menu of various statistics displaying tools. These do not edit the database in any way.\n\n");
		printf("Enter '1' to view the list of tools that allow you to search for data\n");
		printf("Enter '2' to view the list of tools that help you in determining the biggest and smallest of certain employee details\n\n");
		printf("Enter '3' to return to the main menu\n");
		if(dyn1==0)
		{
			printf("Enter '4' to save data in the Employee Database file\n");
			printf("Enter '5' to enable auto save\n");
		}
		else
			printf("Enter '6' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:
			{
				printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");
				LB2:
				nestedmenuB1();if(dyn2==4)return;if(dyn2==3)return;
				else if(dyn2==1)
				{
					dyn2=0;
					return;
				}
				else if(dyn2==2)
				{
					dyn2=0;
					nestedmenuB2();if(dyn2==4)return;if(dyn2==2)goto LB2;else if(dyn2==3)return;else if(dyn2==1)return;
				}
			}fileautosave();break;
			case 2:
			{
				printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");
				LB3:
				nestedmenuB2();if(dyn2==4)return;if(dyn2==3)return;
				else if(dyn2==1)
				{
					dyn2=0;
					return;
				}
				else if(dyn2==2)
				{
					dyn2=0;
					nestedmenuB1();if(dyn2==4)return;if(dyn2==2)goto LB3;else if(dyn2==3)return;else if(dyn2==1)return;
				}
			}break;
			case 3:printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");return;
			case 4:filemanualsave();if(dyn1==1){visor=1;goto LB1;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 5:if(dyn1==1){visor=1;goto LB1;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 6:if(dyn1==0){visor=1;goto LB1;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB1;
		}
	}while(i!=0);
	dyn2=3;
	LBE:
		return;
}

void nestedmenuB1()		//Data searching tools list		//linking with nested-menu B2
{
	void nestedmenuB2();
	int i;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is the list of tools that help you to search for data in three ways\n\n");
		printf("Enter '1' to search for the details and position in database of an employee with the employee's ID being the parameter of search\n");
		printf("Enter '2' to search for the no. of employees associated with a single name(if any such exist) with employee name being the parameter of search\n");
		printf("Enter '3' to search for the no. of employees associated with a single post(if any such exist) with post being the parameter of search\n\n");
		printf("Enter '4' to go back to the menu of database statistics displaying tools\nEnter '5' to view the list of biggest and smallest details displaying tools\n");
		printf("Enter '6' to return to the main menu\n");
		if(dyn1==0)
		{
			printf("Enter '7' to save data in the Employee Database file\n");
			printf("Enter '8' to enable auto save\n");
		}
		else
			printf("Enter '9' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:search();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 2:searchbyname();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 3:searchbypost();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 4:dyn2=0;printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");return;
			case 5:dyn2=2;printf("\n\n--------------------|----------------------------|-----------------------------|------------------------------|-----------------------------|--------------------------|------------------------\n");return;
			case 6:dyn2=1;printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");return;
			case 7:filemanualsave();if(dyn1==1){visor=1;goto LB1;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 8:if(dyn1==1){visor=1;goto LB1;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 9:if(dyn1==0){visor=1;goto LB1;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB1;
		}
	}while(i!=0);
	dyn2=3;
	LBE:
		return;
}

void nestedmenuB2()		//Extreme values for certain details displaying tools list		//linking with nested-menu B1
{
	int i;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nBelow is the list of tools that help you to determine the biggest and smallest of certain employee details\n\n");
		printf("Enter '1' to display the details of the employees with the highest and the lowest merits\n");
		printf("Enter '2' to display the details of the oldest and the youngest employees\n");
		printf("Enter '3' to display the details of the employees with the highest and lowest incomes\n\n");
		printf("Enter '4' to go back to the menu of database statistics displaying tools\nEnter '5' to view the list of data searching tools\n");
		printf("Enter '6' to return to the main menu\n");
		if(dyn1==0)
		{
			printf("Enter '7' to save data in the Employee Database file\n");
			printf("Enter '8' to enable auto save\n");
		}
		else
			printf("Enter '9' to disable auto save\n");
		printf("Enter '15' to display the Employee Database after any/no changes made to it\nEnter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:bgsmmerit();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 2:bgsmage();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 3:bgsminc();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 4:dyn2=0;printf("\n\n********************|****************************|*****************************|******************************|*****************************|**************************|************************\n");return;
			case 5:dyn2=2;printf("\n\n--------------------|----------------------------|-----------------------------|------------------------------|-----------------------------|--------------------------|------------------------\n");return;
			case 6:dyn2=1;printf("\n\n--------------------X----------------------------X-----------------------------X------------------------------X-----------------------------X--------------------------X------------------------\n");return;
			case 7:filemanualsave();if(dyn1==1){visor=1;goto LB1;}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 8:if(dyn1==1){visor=1;goto LB1;}dyn1=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 9:if(dyn1==0){visor=1;goto LB1;}dyn1=0;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 15:display();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:fileautosave();break;
			default :fileautosave();visor=1;goto LB1;
		}
	}while(i!=0);
	dyn2=3;
	LBE:
		return;
}

void empaccess(int i)	//Employee page		//personal particulars display, set personal password
{
	int j;
	char *pwd;
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	printf("\n\n\nWhat sort of action do you wish to perform?\n");
	do
	{
		printf("\n\nEnter '1' to display all your particulars\nEnter '2' to change your password\nEnter '0' to return to login page\n");
		j=int_scanner();
		switch(j)
		{
			case 1:printf("\n\nName-->          %s\nAge-->           %d\nId-->            %d\npost-->          %s\nMerit-->         %d\nSalary-->        %.2lf\nCredits-->       %.2lf\nDeductions-->    %.2lf\nIncome-->        %.2lf\nMail Id-->       %s\nPhone Number-->  %s\n\n",o[i].name,o[i].age,o[i].id,o[i].post,o[i].merit,o[i].sal,o[i].cred,o[i].ded,o[i].inc,o[i].mailid,o[i].phno);break;
			case 2:
				{
					printf("Enter new password: ");
					pwd=string_scanner();
					stringassignauto(o[i].ppwd,pwd);
				}filemanualsave();break;
			case 0:return;
			default :visor=1;goto LB1;
		}
	}while(j!=0);
	LBE:
		return;
}

void hrredirect()	//HR page	//Main menu linking
{
	char *inpwd;
	printf("\n\t\t\t\t\t\t\t\t\t\tenter your password: ");
	inpwd=string_scanner();
	if(stringcheckauto(inpwd,"start234")==1)
	{
		mainmenu();
	}
	else
	{
		printf("\n\n\t\t\t\t\t\t\t\t\t\tpassword provided is invalid\n\n\n");
	}
}

void empredirect()	//Employee page		//empaccess linking
{
	char *pwd,*name,*cpost;
	int i,id,age;
	filemanualread();
	printf("Enter your id: ");
	id=int_scanner();
	for(i=0;i<s;i++)
	{
		if(id==o[i].id)
			break;
	}
	if(i==s)
	{
		printf("\n\nThe id provided does not exist in the database\n\n\n");
		return;
	}
	printf("Enter your password: ");
	pwd=string_scanner();
	if(o[i].ppwd[0]!='\0')
	{
		if(stringcheckauto(pwd,o[i].ppwd)==1)
			empaccess(i);
		else
		{
			printf("\n\n\t\t\tInvlid password\n\n\n");
			return;
		}
	}
	else
	{
		if(stringcheckauto(pwd,o[i].tpwd)==1)
			empaccess(i);
		else
		{
			printf("\n\nInvlid password\n\n\n");
			return;	
		}
	}
}

void guestredirect()	//Guest page
{
	int i;
	filemanualread();
	printf("Welcome to our company's official website!\nWhat would you like to look for?\n\n");
	visor=0;
	LB1:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\nEnter '1' to search for an employee's contact details by giving their name\n");
		printf("Enter '2' to search for the same by providing their post\nEnter '3' to view the list of all the employee's working in our company\n");
		printf("Enter '0' to logout\n");
		i=int_scanner();
		switch(i)
		{
			case 1:searchbynameguest();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 2:searchbypostguest();printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 3:
			{
				printf("\n\nThe following Employees work in this company:\n\n");
				printf("NAME\t\t\tPOST\t\tPHONE NUMBER\t\tMAIL ID\n\n");
				for(i=0;i<s;i++)
					printf("%s\t\t%s\t\t%s\t\t%s\n",o[i].name,o[i].post,o[i].phno,o[i].mailid);
			}printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");break;
			case 0:break;
			default :visor=1;printf("\n\n________________________________________________________________________________________________________________________________________________________________________________________________\n\n");goto LB1;
		}
	}while(i!=0);
	printf("\n\n");
	LBE:
		return;
}

void main()		//FYI	//login page
{
	int i=1;
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tWELCOME!\n\n");
	printf("If this your first time using this program as an HR, There are a few things that are necessary for you to know before you head to the login page.\nIf you are not the HR, please head straight to the login page\n");
	visor=0;
	LB2:
	if(visor!=0)
	{
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	printf("\nEnter '1' to view the first-time use information\nEnter '2' to head straight to the login page\n");
	i=int_scanner();
	switch(i)
	{
		case 1:
			{
				printf("\n\n\nThis program allows you to create new data, edit existing data and display statistics for an employee database.\nYou can also save the data in a file and access the data from the file in future to further edit it or display statistics for it.\n\n");
				printf("\nThe autosave feature reduces a lot of key-pressing for you but if in a case you delete a data from the database, it will also be deleted from the database file before you can create a backup.\n");
				printf("Therefore, it is advised to disable the autosave feature before heading towards deleting a data, so you can choose when to save.\nYou can also manually create a backup in another file before heading towards deleting data, ");
				printf("if you don't wish to disable autosave.\n\nIn every menu and list, the choices for use of tools and the choices for navigation, toggling of features,etc. is always separated by one blank line for your comfortable viewing.\n\n\n");
				printf("There are 4 types of menu/list separating lines used in this program.\n\n(1) ----X----X---- separates every menu and list from the mainmenu.\n");
				printf("(2) ----|----|---- separates two nested-menus or lists\n(3) *****|****|**** separates a nested-menu/list from a submenu\n(4) ______________ separates a menu from itself when it is displayed again after a tool in that menu is used\n\n");
				printf("By keeping a note of the separating lines in your mind, you can easily notice where you have navigated to without having to check where you are in most cases.\n\n\n");
				printf("Don't worry if you provide an invalid choice anywhere, anytime and for any no.of times throughout the program, as instead of shutting down abnormally, that choice will be handled.\n");
				printf("Although, do take care in providing your choice after the invalid choice is handled or else it will be assumed that you are no longer interested in using the program.\n");
				printf("Invalid data inputs are handled too!\n\n");
			}break;
		case 2:break;
		default :visor=1;goto LB2;	
	}
	visor=0;
	LB1:
	if(visor!=0)
	{
		dyn4=1;
		invalidinputhandler();
		if(dyn2==4)
	  	goto LBE;
	}
	do
	{
		printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t***LOGIN PAGE***\n\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t\t ________________________________\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t\t| Enter '1' to login as HR       |\n\t\t\t\t\t\t\t\t\t\t\t\t| Enter '2' to login as employee |\n\t\t\t\t\t\t\t\t\t\t\t\t");
		printf("| Enter '3' to login as Guest    |\n\t\t\t\t\t\t\t\t\t\t\t\t| Enter '0' to exit the program  |\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t\t --------------------------------\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
		i=int_scanner();
		switch(i)
		{
			case 1:hrredirect();if(dyn3==1)goto LBE;break;
			case 2:empredirect();break;
			case 3:guestredirect();break;
			case 0:break;
			default :visor=1;goto LB1;	
		}
	}while(i!=0);
	LBE:
	if(dyn3==1)
	{
		printf("It seems like you are no more interested in using this program.\nProgram is terminated. Press any key to close this window\n");getche();
		return;
	}
	printf("\n\n\nThank You for using this program!\nPress any key to close this window\n");getche();return;
}
