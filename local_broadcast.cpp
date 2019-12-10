#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Node {			//saves userdata
	char name[20];
	char pin[10];
	struct Node* next;
};

struct Message {		//saves message data	
	char name[20];
	char msg[100];
	struct Message* next;
};

struct Node* head_usr = NULL;
struct Message* head_msg = NULL;

void addUser(char new_name[20], char new_pin[10]) {	//adds user

	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(new_node->name, new_name);
	strcpy(new_node->pin, new_pin);
	if(head_usr == NULL) {
		new_node->next = NULL;
		head_usr = new_node;
		printf("\nUser: %s Saved.\n", new_node->name);
		return;
	}
	new_node->next = head_usr;
	head_usr = new_node;
	printf("\nUser: %s Saved.\n", new_node->name);
}

bool verify_usr(char verify_name[20], char verify_pin[10]) {	//verifies username and password
	struct Node* find = head_usr;
	while(find != NULL) {
		if(strcmp(find->name, verify_name) == 0)
			break;
		find = find->next;
	}
		
	if(strcmp(find->name, verify_name) == 0) {
		printf("\nAccount found!\n");
		if(strcmp(find->pin, verify_pin) == 0) {
			printf("Login Successful!\n");
			return true;
		}
		else {
			printf("Nice try! Wrong Password.\n");
			return false;
		}
	}
	else {
	printf("Account not found. Please verify your username.\n");
	return false;
	} 
		
	
}

void send(char name[20], char new_msg[100]) {	//adds message to struct Message
	struct Message* new_node = (struct Message*)malloc(sizeof(struct Message));
	strcpy(new_node->name, name);
	strcpy(new_node->msg, new_msg);
	if(head_msg == NULL){
		new_node->next = NULL;
		head_msg = new_node;
		printf("\nMessage Sent: %s\n", new_node->msg);
		return;
	}
	new_node->next = head_msg;
	head_msg = new_node;
	printf("\nMessage Sent: %s\n", new_node->msg);
	return;
}

void view() {		//views message
	if(head_msg == NULL)
	{
		printf("\nNo Messages!\n");
		return;
	}
	
	struct Message* last = head_msg;
	printf("\n");
	while(last != NULL)
	{
		printf("%s Posted: %s\n", last->name, last->msg);
		last = last->next;
	}
	
	printf("\n");
}

void display_users() {	//displays number of users created
	if(head_usr == NULL)
	{
		printf("\nNo Users.\n");
		return;
	}
	
	struct Node* last = head_usr;
	while(last != NULL)
	{
		printf("\n%s\n", last->name);
		last = last->next;
	}
}

char temp[3] = "abc";

void export_usr() {		//exports user data to file
	FILE *out_file = fopen("broadcast_usr", "w");
	struct Node* last_usr = head_usr;
	
	while(last_usr != NULL) {
		fprintf(out_file, " %s\n", temp);
		fprintf(out_file, " %s\n", last_usr->name);
		fprintf(out_file, " %s\n", last_usr->pin);
		last_usr = last_usr->next;
	}
	return;
	
	
}

void import_usr() {		//imports user data from file
	FILE *in_file = fopen("broadcast_usr", "r");
	if(in_file == NULL) {
		return;
	}
	char name[20];
	char pin[10];
	do {
		fscanf(in_file," %s\n", temp);
		fscanf(in_file," %[^\n]\n", name);
		fscanf(in_file," %[^\n]\n", pin);
		addUser(name, pin);
	} while(fgetc(in_file) != EOF);
	return;
}


void export_msg() {		//exports message data to file
	FILE *out_file = fopen("broadcast_msg", "w");
	struct Message* last_msg = head_msg;
	
	while(last_msg != NULL) {
		fprintf(out_file, " %s\n", temp);
		fprintf(out_file, " %s\n", last_msg->name);
		fprintf(out_file, " %s\n", last_msg->msg);
		last_msg = last_msg->next;
		return;
	} 
}

void import_msg() {		//imports message data from file
	FILE *in_file = fopen("broadcast_msg", "r");
	if(in_file == NULL) {
		return;
	}
	char name[20];
	char msg[100];
	do {
		fscanf(in_file," %s\n", temp);
		fscanf(in_file," %[^\n]\n", name);
		fscanf(in_file," %[^\n]\n", msg);
		send(name, msg);
	} while(fgetc(in_file) != EOF);
	return;
}


int main() {		//main driver function
	import_usr();
	import_msg();
	system("clear");
	printf("Previous data imported from file.\n");
	char name[20];
	char msg[100];
	char pin[10];
	menu:
	while(1) {
		printf("\n1. Log In.\n");
		printf("2. Sign Up.\n");
		printf("3. List Users.\n");
		printf("Press any other integer to Save/Exit.\n");
		int choice;
		scanf(" %d", &choice);
		switch(choice) {
			case 1:
				system("clear");
				if(head_usr == NULL) {
					printf("\nNo local accounts found.\n");
				}
				else {
					printf("\nUsername: ");
					scanf(" %[^\n]", name);
					printf("Password: ");
					scanf(" %[^\n]", pin);
					int verify = verify_usr(name, pin);
					if(verify == 1) {
						while(1) {
							printf("\n1. Send Broadcast.\n");
							printf("2. Recieved Broadcasts.\n");
							printf("Press any other integer to Log Out.\n");
							scanf(" %d", &choice);
							switch(choice) {
								case 1:
									system("clear");
									printf("\nEnter message: ");
									scanf(" %[^\n]", msg);
									send(name, msg);
									break;
							
								case 2:
									system("clear");
									view();
									printf("\nPress any key to go back.\n");
									scanf(" %d", &choice);
									break;
										
								
										
								default:
									system("clear");
									printf("Thank You!\n");
									goto menu;
							}
						}
					}
					else {
						break;
					}
				}
				break;
				
			case 2:
				system("clear");
				printf("\nCreate Username: ");
				scanf(" %[^\n]", name);
				printf("Create Password: ");
				scanf(" %[^\n]d", pin);
				addUser(name, pin);
				break;
					
			case 3:
				system("clear");
				display_users();
				break;
					
					
			default:
				export_usr();
				export_msg();
				system("clear");
				printf("Process terminated!\n");
				exit(1);
		}
		
	}
}
