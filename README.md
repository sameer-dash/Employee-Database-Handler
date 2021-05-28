# Employee-Database-Handler
A program written in C language to create, manipulate and delete employee data of a given company.

The data can be saved in a file and can be accessed from it in future to further edit it or display statistics for it. This programs mimics the use of 'autosave'.
The autosave feature reduces a lot of key-pressing but if in a case a data is deleted from the database, it will also be deleted from the database file before a backup can be created. Therefore, it is advisable to disable the autosave feature before heading towards deleting a data, so it can be chosen when to save.
Backup can also be created manually in another file before heading towards deleting data, if disabling autosave is not desired.

In every menu and list, the choices for use of tools and the choices for navigation, toggling of features,etc. is always separated by one blank line for comfortable viewing.
There are 4 types of menu/list separating lines used in this program.
(1) ----X----X---- separates every menu and list from the mainmenu.
(2) ----|----|---- separates two nested-menus or lists
(3) *****|****|**** separates a nested-menu/list from a submenu
(4) ______________ separates a menu from itself when it is displayed again after a tool in that menu is used
By keeping a note of the separating lines, it can be easily noticed where the user has navigated to without having to check where he/she is in most cases.

It is not a problem if an invalid choice is provided anywhere, anytime and for any no.of times throughout the program, as instead of shutting down abnormally, that invalid choice will be handled.
Although, care has to be taken in providing a choice after the invalid choice is handled or else it will be assumed that the user is no longer interested in using the program.
It is strongly advised to take extreme care while inputting Employee data when the program runs as in some cases program will shut down abnormally.
Invalid data inputs can not be handled when a type of data provided mismatches the type of data required.

This program also mimics the working of a login page in its most basic form.
The user can login as HR/Employee/Guest and is therefore allowed to certain functions that are associated to the type of login.
The HR has complete access to the database apart from setting an employee's login password.
An employee can view all of his/her personal data in the database and can change the login password.
A guest can search for the contact details of an employee by giving their name/post and can also view the contact info of all the employees working in the company.

---------------My thoughts while creating this project---------------
A lot of functions created in this program allow it to mimic the working of certain pre-defined functions.
I do have the knowledge of various pre-defined functions such as strcmp(),strcpy(),exit (0),etc. that can be used with the pre-processing directives such as #include<string.h>, #include<stdlib.h>, #include<math.h>, etc.
I do know that by using such pre-defined functions, i could have shortened the code written in this program.
Although, what i am trying to show here is that even when i am provided with the most basic tools to create a program, i can create my own functions according to my need to make the program do what i need it to do.
