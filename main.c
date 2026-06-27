#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char courseName[50];
	char courseCode[10];
	int credit;
	int midtermGrade;
	int finalGrade;
	float average;
}Course;

typedef struct{
	char name[50];
	int studentNo;
	Course *courses; // Pointer for dynamic Course array
	int courseCount; // Number of current courses
	float overallAverage;
}Student;

void initStudent(Student *stu, char *name, int no);
void addCourse(Student *stu, char *name, char *code, int credit);
void deleteCourse(Student *stu, char *code);
void freeSystem(Student *stu);

void enterGrades(Student *stu, char *code, int midterm, int final);
void calculateOverallAverage(Student *stu);
void updateCourse(Student *stu, char *code, char *newName, int newCredit);

int searchCourse(Student *stu, char *code);
void findHighestGradeCourse(Student stu);
void listFailedCourses(Student stu);

void printReportCard(Student stu);
void creditLoadReport(Student stu);
void sortCoursesAlphabetically(Student *stu);

void updateStudentInfo(Student *stu, char *newName, int newNo);
void copyCourses(Student *target, Student source);

int main(){
	Student student1;
	Student student2;
	int choice, tempNo, tempCredit, tempMidterm, tempFinal, newNo, initStudent2=0;
	char *tempName, *tempCode, *newName;
	
	tempName = (char*)calloc(50, sizeof(char));
	if(tempName == NULL){
		printf("Cannot allocate the memory.\n");
		return 1;
	}
	tempCode = (char*)calloc(20, sizeof(char));
	if(tempCode == NULL){
		printf("Cannot allocate the memory.\n");
		return 1;
	}
	newName = (char*)calloc(50, sizeof(char));
	if(newName == NULL){
		printf("Cannot allocate the memory.\n");
		return 1;
	}
	
	printf("Welcome to the Student Information System\n");
	printf("Please enter the name of the student: ");
	scanf(" %[^\n]", tempName);
	printf("Please enter the student number of the student: ");
	scanf(" %d", &tempNo);
	initStudent(&student1, tempName, tempNo);
	
	while(1){
		printf("\n");
		printf("1 - add course\n");
		printf("2 - enter grades\n");
		printf("3 - print report card\n");
		printf("4 - list failed courses\n");
		printf("5 - find the highest graded course\n");
		printf("6 - total credit\n");
		printf("7 - list courses alphabetically\n");
		printf("8 - update course information\n");
		printf("9 - delete course\n");
		printf("10 - update student information\n");
		printf("11 - copy the courses to another student\n");
		printf("12 - calculate the overall average\n");
		printf("13 - search course\n");
		printf("0 - exit\n\n");
		printf("Please chose the operation you want to continue with: ");
		scanf(" %d", &choice);
		
		if(choice==1){
			printf("Please enter the name of the course: ");
			scanf(" %[^\n]", tempName); //%[^/n] is used because of the spaces in the name
			printf("Please enter the code of the course: ");
			scanf(" %s", tempCode); //%s is used because no space is typed 
			printf("Please enter the credit of the course: ");
			scanf(" %d", &tempCredit);
			
			addCourse(&student1, tempName, tempCode, tempCredit);
		}
		
		else if(choice==2){
			printf("Please enter the code of the course: ");
			scanf(" %s", tempCode);
			printf("Please enter the midterm grade: ");
			scanf(" %d", &tempMidterm);
			printf("Please enter the final grade: ");
			scanf(" %d", &tempFinal);
			
			enterGrades(&student1, tempCode, tempMidterm, tempFinal);
		}
		
		else if(choice==3){
			printReportCard(student1);
		}
		
		else if(choice==4){
			listFailedCourses(student1);
		}
		
		else if(choice==5){
			findHighestGradeCourse(student1);
		}
		
		else if(choice==6){
			creditLoadReport(student1);
		}
		
		else if(choice==7){
			sortCoursesAlphabetically(&student1);
		}
		
		else if(choice==8){
			printf("Please enter the code of the course you want to update: ");
			scanf(" %s", tempCode);
			printf("Please enter the new name of the course: ");
			scanf(" %[^\n]", newName);
			printf("Please enter the updated credit of the course: ");
			scanf(" %d", &tempCredit);
			
			updateCourse(&student1, tempCode, newName, tempCredit);
		}
		
		else if(choice==9){
			printf("Please enter the code of the course you want to delete: ");
			scanf(" %s", tempCode);
			
			deleteCourse(&student1, tempCode);
		}
		
		else if(choice==10){
			printf("Please enter the new name of the student: ");
			scanf(" %[^\n]", newName);
			printf("Please enter the updated number of the student: ");
			scanf(" %d", &newNo);
			
			updateStudentInfo(&student1, newName, newNo);
		}
		
		else if(choice==11){
			printf("Please enter the name of the new student: ");
			scanf(" %[^\n]", newName);
			printf("Please enter the student number of the new student: ");
			scanf(" %d", &newNo);
			initStudent(&student2, newName, newNo);
			initStudent2 =1;
			
			copyCourses(&student2, student1);
		}
		
		else if(choice==12){
			calculateOverallAverage(&student1);
			printf("Overall average calculated successfully.\n\n");
		}
		
		else if(choice==13){
			printf("Please enter the code of the course you want to search: ");
			scanf(" %s", tempCode);
			searchCourse(&student1, tempCode);
		}
		
		else if(choice==0){
			freeSystem(&student1);
			
			if(initStudent2 ==1){
				freeSystem(&student2);
			}
			
			free(tempCode);
			free(tempName);
			free(newName);
			return 0;
		}
		
		else{
			printf("Please enter a number from the menu.\n");
		}
	}
	
	return 0;
}

void initStudent(Student *stu, char *name, int no)
{
	strcpy(stu->name, name);
	stu->studentNo= no;
	stu->courses = NULL;
	stu->overallAverage = 0.0;
	stu->courseCount = 0;
	return;
}

void addCourse(Student *stu, char *name, char *code, int credit){
	
	stu->courses=(Course*)realloc(stu->courses, (stu->courseCount +1)*sizeof(Course));
	if(stu->courses == NULL){
		printf("Cannot allocate the memory.\n");
		return;
	}
	strcpy(stu->courses[stu->courseCount].courseCode, code);
	strcpy(stu->courses[stu->courseCount].courseName, name);
	stu->courses[stu->courseCount].credit = credit;
	stu->courses[stu->courseCount].finalGrade= 0;
	stu->courses[stu->courseCount].average= 0.0;
	stu->courses[stu->courseCount].midtermGrade= 0;
	stu->courseCount++;
	return;
}

void deleteCourse(Student *stu, char *code){
	int isValid=0, i=0, validCode;
	while(i< stu->courseCount && isValid != 1){
		if(strcmp(stu->courses[i].courseCode, code)== 0){
			isValid = 1;
			validCode = i;
		}
		i++;
	}
	if(isValid == 1){
		for(i=validCode; i< stu->courseCount-1; i++){
			stu->courses[i] = stu->courses[i+1];
		}
		stu->courseCount--;
		if(stu->courseCount ==0){
			free(stu->courses);
			stu->courses = NULL;
			stu->overallAverage= 0.0;
			printf("The student has no courses left.\n");
		}
		else{
			stu->courses =(Course*)realloc(stu->courses, stu->courseCount*sizeof(Course));
			calculateOverallAverage(stu);
		}
	}
	else printf("Course not found.\n");
	return;
}

void freeSystem(Student *stu){
	free(stu->courses);
	stu->courses= NULL;
	stu->courseCount =0;
	return;
}

void enterGrades(Student *stu, char *code, int midterm, int final){
	int isValid=0, i=0, validCode;
	while(i< stu->courseCount && isValid != 1){
		if(strcmp(stu->courses[i].courseCode, code)== 0){
			isValid = 1;
			validCode = i;
		}
		i++;
	}
	if(isValid == 1){
		stu->courses[validCode].midtermGrade = midterm;
		stu->courses[validCode].finalGrade = final;
		stu->courses[validCode].average = (midterm*0.4)+(final*0.6);
		calculateOverallAverage(stu);
	}
	else printf("Course not found.\n");
	return;
}

void calculateOverallAverage(Student *stu){
	int i, overallCredits=0;
	float overallAverage=0;
	for(i=0; i<stu->courseCount; i++){
		overallAverage += stu->courses[i].average*stu->courses[i].credit;
		overallCredits += stu->courses[i].credit;
	}
	if(overallCredits > 0) stu->overallAverage = overallAverage/overallCredits;
	else{
		printf("Cannot calculate the overall average (no credits).\n");
		stu->overallAverage = 0;
	}
	return;
}

void updateCourse(Student *stu, char *code, char *newName, int newCredit){
	int isValid=0, i=0, validCode;
	while(i< stu->courseCount && isValid != 1){
		if(strcmp(stu->courses[i].courseCode, code)== 0){
			isValid = 1;
			validCode = i;
		}
		i++;
	}
	if(isValid == 1){
		stu->courses[validCode].credit = newCredit;
		strcpy(stu->courses[validCode].courseName, newName);
		calculateOverallAverage(stu);
	}
	else printf("Course not found.\n");
	return;
}

int searchCourse(Student *stu, char *code){
	int isValid=0, i=0, validCode;
	while(i< stu->courseCount && isValid != 1){
		if(strcmp(stu->courses[i].courseCode, code)== 0){
			isValid = 1;
			validCode = i;
		}
		i++;
	}
	if(isValid == 1){
		printf("Course found at index: %d\n", i-1);
		return validCode;
	}
	else return -1;
}

void findHighestGradeCourse(Student stu){
	int i, maxCourse;
	float max=-1.0;
	if(stu.courseCount != 0){
		for(i=0; i< stu.courseCount; i++){
			if(stu.courses[i].average > max){
				max =stu.courses[i].average;
				maxCourse = i;
			}
		}
		printf("Highest Grade Course:\n");
		printf("%s - %.0f\n", stu.courses[maxCourse].courseCode , max);
	}
	else printf("The student does not have any courses.\n");
}

void listFailedCourses(Student stu){
	int i, isFailed=0;
	if(stu.courseCount != 0){
		printf("FAILED COURSES:\n");
		for(i=0; i < stu.courseCount; i++){
			if(stu.courses[i].average < 50){
				printf("%s - %s\n", stu.courses[i].courseCode, stu.courses[i].courseName);
				isFailed++;
			}
		}
		if(isFailed==0) printf("The student does not have any failed courses.");
	}
	else printf("The student does not have any courses.\n");
	return;
}

void printReportCard(Student stu){
	int i;
	if(stu.courseCount != 0){
		printf("Student name: %s\n", stu.name);
		printf("Student No: %d\n\n", stu.studentNo);
		printf("Courses:\n");
		printf("---------------------------\n");
		for(i=0; i < stu.courseCount; i++){
			printf("Course Name: %s\n", stu.courses[i].courseName);
			printf("Course Code: %s\n", stu.courses[i].courseCode);
			printf("Credit: %d\n", stu.courses[i].credit);
			printf("Midterm: %d\n", stu.courses[i].midtermGrade);
			printf("Final: %d\n", stu.courses[i].finalGrade);
			printf("Average: %.0f\n", stu.courses[i].average);
			printf("---------------------------\n");
		}
		printf("Overall Average: %.2f\n", stu.overallAverage);
	}
	else printf("The student does not have any courses.\n");
	return;
}

void creditLoadReport(Student stu){
	int i, totalCredit=0;
	if(stu.courseCount != 0){
		for(i=0; i< stu.courseCount; i++){
			totalCredit += stu.courses[i].credit;
		}
		printf("Total Credit: %d\n", totalCredit);
	}
	else printf("The student does not have any courses.\n");
	return;
}

void sortCoursesAlphabetically(Student *stu){
	int i, j;
	Course tempCourse;
	if(stu->courseCount != 0){
		for(i=0; i< stu->courseCount -1; i++){
			for(j=0; j< stu->courseCount-1-i; j++){
				if(strcmp(stu->courses[j].courseName, stu->courses[j+1].courseName) > 0){
					tempCourse = stu->courses[j];
					stu->courses[j] = stu->courses[j+1];
					stu->courses[j+1] = tempCourse;
				}
			}
		}
		for(i=0; i< stu->courseCount; i++){
			printf("%s\n", stu->courses[i].courseName);
		}
		printf("\n");
	}
	else printf("The student does not have any courses.\n");
	return;
}

void updateStudentInfo(Student *stu, char *newName, int newNo){
	strcpy(stu->name, newName);
	stu->studentNo = newNo;
	return;
}

void copyCourses(Student *target, Student source){
	int i;
	
	if(target->courses != NULL) free(target->courses);
	target->courseCount = source.courseCount;
	target->courses= (Course*)malloc(target->courseCount *sizeof(Course));
	if(target->courses == NULL){
		printf("Cannot allocate the memory.\n");
		return;
	}
	for(i=0; i< target->courseCount; i++){
		target->courses[i]= source.courses[i];
	}
	calculateOverallAverage(target);
	printf("\n");
	printReportCard(*target);
	return;
}
