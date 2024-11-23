/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Define --------------------------------------------------------------------*/
#define MAX_ROW 2
#define MAX_COLUMN 15
#define MAX_ENTERPRISE 30

/* Enum ----------------------------------------------------------------------*/
typedef enum Status
{
	Empty,
	Registered
} Status;

typedef enum CommandType
{
	REGISTER,
	ALTER,
	SHOW,
	DELETE,
	QUIT,
	INVALID
} CommandType;

/* --------------------------------------------------------------------------- */
/*                            Begin: Student Answer                            */
/* --------------------------------------------------------------------------- */

// Requirement 1: Generate abbreviation from the full name of an enterprise
void getAbbreviation(char *name, char *abbre)
{
    /* 
    name = ten doanh nghiep 
    abbre = viet tat cua doanh nghiep 
	abbre should be an char array of 10. 
    */
    int size = strlen(name); 
    abbre[0] = name[0]; 
    int ptr = 1; 

    for (int i = 0; i < size; ++i) { 
        if (name[i] == ' ') {
            abbre[ptr] = name[i+1]; 
            ++ptr;                     
        }
    }
}
// Requirement 2: Determine the type of command
CommandType getCommandType(char *command)
{
	// TODO: Implement this function
	char cmdList[6][9] = {
			"Register", 
			"Alter", 
			"Show", 
			"Delete", 
			"Quit", 
			"Invaild"
		}; 

	int position = 5; 	
	if (command[0] == 'R') position = 0; 
	if (command[0] == 'A') position = 1; 
	if (command[0] == 'S') position = 2; 
	if (command[0] == 'D') position = 3; 
	if (command[0] == 'Q') position = 4; 
	if (command[0] == 'I') position = 5; 
	
	if (position == 5) return INVALID; 

	int sizeOfOriginalCommand = strlen(cmdList[position]);
	int sizeOfFirstWordInInputCommand = 0; 
	// first space_position location is equal to the length of the first word in command. 
	for (int i = 0; i < strlen(command); ++i) { 
		if (command[i] == ' ') {
			sizeOfFirstWordInInputCommand = i; 
			break; 
		}
	}
	//not exist space => first word = whole command. 
	if (sizeOfFirstWordInInputCommand == 0) 
		sizeOfFirstWordInInputCommand = strlen(command); 
	
	// Case 1: Not reach all cmd -> Fail
	if (sizeOfFirstWordInInputCommand < sizeOfOriginalCommand ) return INVALID; 
	// Consider word of input cm have equal or more character than the Orignial Command. 
	for (int i = 1; i < sizeOfFirstWordInInputCommand; ++i) { 
		if (command[i] != cmdList[position][i])
			return INVALID; 
	}
	
	if (sizeOfFirstWordInInputCommand == sizeOfOriginalCommand) 
		return position; 
	if (sizeOfFirstWordInInputCommand != sizeOfOriginalCommand) { 
		// Case 2: Reach all cmd, but have more char -> Fail
		// Case 3: Reach all cmd and end with a space -> Vaild
		if (command[position] != ' ')
			return INVALID; 
	}
	return position; 
}

// Requirement 3: Define the structure to store enterprise details
typedef struct
{
	// TODO: Implement this function
	int booth_index; 
	char name[100]; 
	char abbre[10]; 
	int itemValue; 
	int itemWeight;
} Enterprise;

// Requirement 4: Print the details of a specific enterprise
void printEnterpriseDetails(Enterprise e)
{
	// TODO: Implement this function
	// "||booth_index||name||abbre||itemValue||itemWeight||"; 
	printf("||%d||%s||%s||%d||%d||"
			, e.booth_index
			, e.name
			, e.abbre
			, e.itemValue
			, e.itemWeight); 
}

// Requirement 5: Create an enterprise with specified values
void createEnterprise(Enterprise *e, int booth_index, int itemValue, int itemWeight, char *name, char *abbre)
{
	// TODO: Implement this function
	bool isNull = false; 

	if (e == NULL) {
		e =  malloc(sizeof (Enterprise));
		isNull = true; 
	}
		e->booth_index = booth_index; 
		e->itemValue = itemValue; 
		e->itemWeight = itemWeight; 
		strcpy(e->name , name);
		strcpy(e->abbre , abbre);
		return; 
}

// Requirement 6: Register an enterprise to a booth
void registerEnterprise(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE],
						char *name, int booth, int itemValue, int itemWeight, int *out_booth, char *out_abbre)
{
	// TODO: Implement this function
	char abbre[10]; 
	getAbbreviation(name, abbre); 
	int boothToBePut = 0; 
	int startRow = 0;
	int startColumn = 0;  
	bool isRegisterSuccessful = false; 
	// if booth's input is None
	if (booth == -1)
	{
		boothToBePut = (strlen(abbre) * 30) % 26;

		for (int i = boothToBePut; i < MAX_ROW; ++i)
		{
			if (enterpriseArray[i].booth_index == -1) { 
				isRegisterSuccessful = true; 
				boothToBePut = i; 
				break; 
			}
		}
		if (isRegisterSuccessful == false)
		{
			for (int i = boothToBePut - 1; i >= 0; --i)
			{
				if (enterpriseArray[i].booth_index == -1) { 
					isRegisterSuccessful = true; 
					boothToBePut = i; 
					break; 
				}
			}
		}
		if (isRegisterSuccessful == false)
		{
			*out_booth = boothToBePut + 100;
			strcpy(out_abbre, abbre);
			return; 
		}
		int rowM = boothToBePut / MAX_COLUMN;
		int colM = boothToBePut - rowM * MAX_COLUMN;

		map[rowM][colM] = Registered; 
		
		enterpriseArray[boothToBePut].booth_index = boothToBePut; 
		enterpriseArray[boothToBePut].itemValue = itemValue; 
		enterpriseArray[boothToBePut].itemWeight = itemWeight; 
		strcpy(enterpriseArray[boothToBePut].name , name);
		strcpy(enterpriseArray[boothToBePut].abbre , abbre);

		*out_booth = boothToBePut + 200; 
		strcpy(out_abbre, abbre);
		return; 
	}
	
	if (enterpriseArray[booth].booth_index == -1)
			isRegisterSuccessful = true;
		else { 
			*out_booth = boothToBePut + 100;
			strcpy(out_abbre, abbre);
			return; 
		}
	enterpriseArray[boothToBePut].itemValue = itemValue; 
	enterpriseArray[boothToBePut].itemWeight = itemWeight; 
	strcpy(enterpriseArray[boothToBePut].name, name); 
	strcpy(enterpriseArray[boothToBePut].abbre, abbre); 
	*out_booth = boothToBePut + 100;
	strcpy(out_abbre, abbre);
	return; 
}

// Requirement 7: Display the booth map and status
void showMap(int map[MAX_ROW][MAX_COLUMN])
{
	// TODO: Implement this function
	printf("|0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|\n"); 
	printf("--\n"); 
	printf("|"); 
	for (int i = 0; i < 14; ++i) { 
		printf("%d|", map[0][i]); 
	}
	printf("\n--\n"); 
	printf("|"); 
		for (int i = 0; i < 14; ++i) { 
		printf("%d|", map[1][i]); 
	}
}

// Requirement 8: Show booth indexes based on their status
void showIndexOfStatus(Enterprise enterpriseArray[MAX_ENTERPRISE], Status status)
{
	// TODO: Implement this function

	printf("Index[");
	bool first = true;
	if (status == Empty)
	{
		for (int i = 0; i < MAX_ENTERPRISE; ++i)
		{
			if (enterpriseArray[i].booth_index == -1)
			{
				if (first == true)
				{
					printf("%d", i);
					first = false;
				}
				printf(",%d", i);
			}
		}
	}
	else {
		for (int i = 0; i < MAX_ENTERPRISE; ++i)
		{
			if (enterpriseArray[i].booth_index != -1)
			{
				if (first == true)
				{
					printf("%d", i);
					first = false;
				}
				printf(",%d", i);
			}
		}
	}
	printf("]"); 
}

// Requirement 9: Show the total count of booths with a specific status
void showTotalOfStatus(Enterprise enterpriseArray[MAX_ENTERPRISE], Status status)
{
	// TODO: Implement this function
	printf("Total: "); 
	int count = 0; 
		if (status == Empty){
		for (int i = 0; i < MAX_ENTERPRISE; ++i){
			if (enterpriseArray[i].booth_index == -1)
				++count; 
		}
		printf("%d", count); 
		return; 
	}
	for (int i = 0; i < MAX_ENTERPRISE; ++i){
			if (enterpriseArray[i].booth_index != -1)
				++count; 
		}
	printf("%d", count); 
}

// Requirement 10: Display details of booths in a specified range
void showIndexBracket(Enterprise enterpriseArray[MAX_ENTERPRISE], int start, int end)
{
	if (end == -1) { 
		printEnterpriseDetails(enterpriseArray[start]); 
		return; 
	}
	bool last = false; 
	for (int i = start; i <= end; ++i) { 
		printf("Index %d:", i); 
		if (enterpriseArray[i].booth_index == -1) { 
			printf("NONE"); 
			continue; 
		}
		printf("["); 
		printEnterpriseDetails(enterpriseArray[i]); 
		printf("]"); 
		if (last == false) 
			printf("\n");

		if (i == end - 1)
			last == true;
	}
	// TODO: Implement this function
}

// Requirement 11: Handle the "Show" command and call the appropriate function
void handleShowCommand(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char *command)
{
	// TODO: Implement this function
	int size = strlen(command); 
	char cmd1[3] = "map"; 
    int space_position = 0; 
    for (int i = 0; i < size ; ++i ) { 
		if (command[i] == ' ') { 
            space_position = i; 
            break;
        }
	}
    if (size <= space_position + 1) { 
        return;
    }

    if (command[space_position + 1] == 'm') { 
        int ptr = 0;
        int cmp = strcmp(command + space_position + 1, cmd1);
        if (cmp == 0) 
			showMap(map);
        return;
    }
	    if (command[space_position + 1] == '&') { 
        if (size <= space_position + 2)
			return;
        if (command[space_position + 2] == '0')
            showIndexOfStatus(enterpriseArray, Empty); 
        if (command[space_position + 2] == '1')
        	showIndexOfStatus(enterpriseArray, Registered); 
        return;
    }

    if (command[space_position + 1] == '#') { 
        if (size <= space_position + 2)
            return;
        if (command[space_position + 2] == '0')
            showTotalOfStatus(enterpriseArray, Empty); 
        if (command[space_position + 2] == '1')
            showIndexOfStatus(enterpriseArray, Registered); 
        return;
    }
	// Handle showIndexBracket related command: Show [num] or show Show [from_index:to_index]
	int double_dot_position = 0; 
    int first_bracket_position = 0; 
    int second_bracket_position = 0;
	for (int i = 0; i < size ; ++i ) { 
		if (command[i] == '[') 
			first_bracket_position = i; 
        if (command[i] == ']') 
			second_bracket_position = i; 
		if (command[i] == ':')
			double_dot_position = i; 
	}
	// If Show [num] is called. 
	if (double_dot_position == 0) { 
		char num[3]; 
		strncpy(num, command+(space_position+1), size - (space_position+1)); 
		num[size - (space_position+1)] = '\0';
		int index = atoi(num); 
		showIndexBracket(enterpriseArray, index, -1);
		return; 
	}
	// If Show [from_index:to_index] is called. 
	char num1[3]; 
	char num2[3]; 
	strncpy(num1, command+(first_bracket_position + 1), double_dot_position - (first_bracket_position+1)); 
	strncpy(num2, command+(double_dot_position + 1), second_bracket_position - double_dot_position - 1); 
	num1[double_dot_position - (first_bracket_position+1)] = '\0';
	num2[second_bracket_position - double_dot_position - 1] = '\0';
	int start = atoi(num1); 
	int end = atoi(num2); 
	showIndexBracket(enterpriseArray, start, -1);
	return; 
}

// Requirement 12: Alter the booth assignment for a specified enterprise
void moveEnterprise(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE],int registerBooth, int newBooth) 
{ 
		enterpriseArray[newBooth].booth_index = newBooth;
		strcpy(enterpriseArray[newBooth].name, enterpriseArray[registerBooth].name);
		strcpy(enterpriseArray[newBooth].abbre, enterpriseArray[registerBooth].abbre);
		enterpriseArray[newBooth].itemValue = enterpriseArray[registerBooth].itemValue;
		enterpriseArray[newBooth].itemWeight = enterpriseArray[registerBooth].itemWeight;

		enterpriseArray[registerBooth].booth_index = -1;
		strcpy(enterpriseArray[registerBooth].name, "");
		strcpy(enterpriseArray[registerBooth].abbre, "");
		enterpriseArray[registerBooth].itemValue = 0;
		enterpriseArray[registerBooth].itemWeight = 0;
		// Empty the old location 
		int rowM = registerBooth / MAX_COLUMN;
		int colM = registerBooth - rowM * MAX_COLUMN;

		map[rowM][colM] = Empty;

		// Registered the new location. 
		rowM = newBooth / MAX_COLUMN;
		colM = newBooth - rowM * MAX_COLUMN;

		map[rowM][colM] = Registered;
}
void alterEnterprise(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char *abbre,
					 int registerBooth, int newBooth, int *out_booth, char *out_abbre)
{
	// default case: newBoooth is null
	
	if (newBooth == -1) {
		int newPosition = -1;  
		for (int i = registerBooth; i < MAX_ENTERPRISE; ++i) { 
			if (enterpriseArray[i].booth_index == -1) { 
				newPosition = i; 
				break; 
			}
		}
		if (newPosition == -1) { 
			for (int i = registerBooth; i >= 0; --i) { 
			if (enterpriseArray[i].booth_index == -1) { 
				newPosition = i; 
				break; 
			}
		}
		}

		if (newPosition == -1) { 
			*out_booth = newPosition + 100;
			strcpy(out_abbre, abbre); 
			return; 
		}
		*out_booth = newPosition + 200;
		strcpy(out_abbre, abbre); 
		moveEnterprise(map, enterpriseArray, registerBooth, newPosition); 
		return; 
	}

	if (enterpriseArray[newBooth].booth_index != -1) { 
		*out_booth = newBooth + 100;
		strcpy(out_abbre, abbre); 			
		return; 
	}
	*out_booth = newBooth + 200;
	strcpy(out_abbre, abbre); 		
	moveEnterprise(map, enterpriseArray, registerBooth,newBooth); 
}

// Requirement 13: Delete an enterprise from the system
void deleteEnterprise(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char *abbre, int booth, int *totalEmpty)
{
	// Empty the enterprise information 
		strcpy(abbre, enterpriseArray[booth].abbre);

		enterpriseArray[booth].booth_index = -1;
		strcpy(enterpriseArray[booth].name, "");
		strcpy(enterpriseArray[booth].abbre, "");
		enterpriseArray[booth].itemValue = 0;
		enterpriseArray[booth].itemWeight = 0;

	// Unregister them in the map. 
		int rowIndex = booth / MAX_COLUMN; 
		int colIndex = booth - rowIndex * MAX_COLUMN; 

		map[rowIndex][colIndex] = Empty; 

		*totalEmpty = *totalEmpty - 1; 
		return; 
}

// Requirement 14: Process commands and call the relevant function
void handleCommand(char *command, int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], CommandType *commandType)
{
	// TODO: Implement this function
	*commandType = getCommandType(command); 
	switch(*commandType) { 
		case REGISTER:
			handleRegisterCommand(map, enterpriseArray, command);
			break; 
		case ALTER:
			handleAlterCommand(map, enterpriseArray,command);
			break;
		case SHOW:
			handleShowCommand(map, enterpriseArray, command);
			break;
		case DELETE:
			handleDeleteCommand(map, enterpriseArray,command);
			break;
		case QUIT:
			handleQuitCommand(map, enterpriseArray,command);
		default:
			break; 
	}

}

void handleRegisterCommand(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char* command)
{
	//  Register [VNG] [1] [2] [2]
	int size = strlen(command);
	
	int first_space = 0; 
	for (int i = 0 ; i < size; ++i) { 
		if (command[i] == ' ') { 
			first_space = i; 
			break; 
		}
	}

	int second_space = 0;
	for (int i = first_space + 1; i < size; ++i) { 
		if (command[i] == ' ') { 
			second_space = i; 
			break;
		}
	}

	int third_space = 0;
	for (int i = second_space + 1; i < size; ++i) { 
		if (command[i] == ' ') { 
			third_space = i; 
			break;
		}
	}

	int last_space = 0;
	for (int i = third_space + 1; i < size; ++i) { 
		if (command[i] == ' ') { 
			last_space = i; 
			break;
		}
	}
	char name[100];
	char booth_index[3];
	char item_value[10];
	char item_weight[10];


	strncpy(name, command + first_space + 2, second_space - first_space - 3);
	strncpy(booth_index, command + second_space + 2, third_space - second_space - 3);
	strncpy(item_value, command + third_space + 2, last_space - third_space - 3);
	strncpy(item_weight, command + last_space + 2, size - last_space - 3);
    
    name[second_space - first_space - 3] = '\0';
    booth_index[third_space - second_space - 3] = '\0';
    item_value[last_space - third_space - 3] = '\0';
    item_weight[size - last_space - 3] = '\0';

	int boothIndex = atoi(booth_index);
	int itemValue = atoi(item_value);
	int itemWeight = atoi(item_weight); 

	int booth = 0;
	char abbrev[10];
	int totalEmpty = 0;
	registerEnterprise(map,enterpriseArray,name,boothIndex,itemValue,itemWeight,&booth,&abbrev);
	return;
}
void handleAlterCommand(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char* command)
{
	//   Alter [<abbre>] [reigster_booth] [new_booth]
	int size = strlen(command);
	
	int first_space = 0; 
	for (int i = 0 ; i < size; ++i) { 
		if (command[i] == ' ') { 
			first_space = i; 
			break; 
		}
	}

	int second_space = 0;
	for (int i = first_space + 1; i < size; ++i) { 
		if (command[i] == ' ') { 
			second_space = i; 
			break;
		}
	}

	int third_space = 0;
	for (int i = second_space + 1; i < size; ++i) { 
		if (command[i] == ' ') { 
			third_space = i; 
			break;
		}
	}
	char abbre[10];
	char register_booth[3];
	char new_booth[3];

	strncpy(abbre, command + first_space + 2, second_space - first_space - 3);
	strncpy(register_booth, command + second_space + 2, third_space - second_space - 3);
	strncpy(new_booth, command + third_space + 2, size - third_space - 3);
    
    abbre[second_space - first_space - 3] = '\0';
    register_booth[third_space - second_space - 3] = '\0';
    new_booth[size - third_space - 3] = '\0';

	int registerBooth = atoi(register_booth);
	int newBooth = atoi(new_booth);

	int booth = 0;
	char abbrev[10];
	int totalEmpty = 0;
	alterEnterprise(map,enterpriseArray,abbrev,registerBooth,newBooth, &booth, &abbrev);
	return;
}
void handleDeleteCommand(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char* command)
{
	//   Delete [<abbre>] [reigsterBooth]
	int size = strlen(command);
	
	int first_space = 0; 
	for (int i = 0 ; i < size; ++i) { 
		if (command[i] == ' ') { 
			first_space = i; 
			break; 
		}
	}

	int second_space = 0;
	for (int i = first_space + 1; i < size; ++i) { 
		if (command[i] == ' ') { 
			second_space = i; 
			break;
		}
	}
	char abbre[10];
	char register_booth[3];
	strncpy(abbre, command + first_space + 2, second_space - first_space - 3);
	strncpy(register_booth, command + second_space + 2, size - second_space - 3);
    
    abbre[second_space - first_space - 3] = '\0';
    register_booth[size - second_space - 3] = '\0';

	int registerBooth = atoi(register_booth);

	int booth = 0;
	char abbrev[10];
	int totalEmpty = 0;
	deleteEnterprise(map,enterpriseArray,abbrev,registerBooth, &totalEmpty);
	return;
}
void handleQuitCommand(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE], char* command)
{
	//  Check if command is vaild 
	return; 
}
// Requirement 15: Optimize items collected using the knapsack algorithm
int knapsack(int map[MAX_ROW][MAX_COLUMN], Enterprise enterpriseArray[MAX_ENTERPRISE],
			 int maxWeight, int numOfEnterprises, int index)
{
	//TODO: Return the maximum value collected
}

/* --------------------------------------------------------------------------- */
/*                             End: Student Answer                             */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/*                           Example Test Cases for Main                        */
/* --------------------------------------------------------------------------- */

// Initializes booth map and enterprise array to default values and then
// runs a series of test cases to verify enterprise registration, booth
// assignments, alterations, and knapsack optimization functionality.

// Initialize the booth map with default status Empty
void initMap(int map[MAX_ROW][MAX_COLUMN])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			map[i][j] = Empty;
		}
	}
}

// Initialize the enterprise array with default values
void initEnterpriseArray(Enterprise enterpriseArray[MAX_ENTERPRISE])
{
	for (int i = 0; i < MAX_ENTERPRISE; i++)
	{
		enterpriseArray[i].booth_index = -1;
		strcpy(enterpriseArray[i].name, "");
		strcpy(enterpriseArray[i].abbre, "");
		enterpriseArray[i].itemValue = 0;
		enterpriseArray[i].itemWeight = 0;
	}
}

int main()
{
		
int map[MAX_ROW][MAX_COLUMN];
    Enterprise enterpriseArray[MAX_ENTERPRISE];
    initMap(map);
    char* command_name[] = {"REGISTER", "ALTER", "SHOW", "DELETE", "QUIT", "INVALID"};
    initEnterpriseArray(enterpriseArray);
    printf("----- Sample testcase 01 -----\n");
    printf("Test getCommandType:\n");
    // char command[] = "Show map";
	// char command[] = "Show [:10]";
		// char command[] = "Quit";
		// char command[] = "Showall";

		// char command[] = "Register [VNG] [1] [2] [2]";
		// char command[] = "Show [from_index:to_index]";
		// char command[] = "Alter [VNG] [11] [12]";
		char command[] = "Delete [VNG] [11]";

    CommandType cmd_type = getCommandType(command);
    printf("Command     : %s\n", command);
    printf("Command type: %s\n", command_name[cmd_type]);
	// // Initialize the map and enterprise array
	// int map[MAX_ROW][MAX_COLUMN];
	// Enterprise enterpriseArray[MAX_ENTERPRISE];
	// initMap(map);
	// initEnterpriseArray(enterpriseArray);

	// int booth = 0;
	// char abbrev[10];
	// int totalEmpty = 0;

	// // Test Case 1: Register enterprises with automatic booth assignment
	// registerEnterprise(map, enterpriseArray, "Tech Co", -1, 10, 10, &booth, abbrev);
	// printf("Registered 'Tech Co' at booth %d with abbreviation %s\n", booth, abbrev);

	// registerEnterprise(map, enterpriseArray, "Innovative Solutions", 10,10, 10,  &booth, abbrev);
	// printf("Registered 'Innovative Solutions' at booth %d with abbreviation %s\n", booth, abbrev);

	// registerEnterprise(map, enterpriseArray, "NextGen", -1,10, 10, &booth, abbrev);
	// printf("Registered 'NextGen' at booth %d with abbreviation %s\n", booth, abbrev);

	// // Test Case 2: Show map to confirm booth registration
	// printf("\nMap Status after Registrations:\n");
	// showMap(map);

	// // Test Case 3: Show indexes based on their status
	// printf("\nEmpty Booths:\n");
	// showIndexOfStatus(enterpriseArray, Empty);

	// printf("\nRegistered Booths:\n");
	// showIndexOfStatus(enterpriseArray, Registered);

	// // Test Case 4: Show total count of booths with specific status
	// printf("\nTotal Empty Booths:\n");
	// showTotalOfStatus(enterpriseArray, Empty);

	// printf("Total Registered Booths:\n");
	// showTotalOfStatus(enterpriseArray, Registered);

	// // Test Case 5: Register an enterprise to an already occupied booth
	// registerEnterprise(map, enterpriseArray, "CompeteX", 10,10, 10, &booth, abbrev);
	// if (booth == -1)
	// {
	// 	printf("\nBooth 10 is already occupied. Registration failed for 'CompeteX'.\n");
	// }

	// // Test Case 6: Alter the booth assignment for an enterprise
	// printf("\nAltering 'NextGen' from current booth to booth 12:\n");
	// alterEnterprise(map, enterpriseArray, "N", booth, 12, &booth, abbrev);
	// if (booth != -1)
	// {
	// 	printf("Booth assignment altered successfully for 'NextGen' to booth %d.\n", booth);
	// }
	// else
	// {
	// 	printf("Failed to alter booth assignment for 'NextGen'.\n");
	// }

	// // Show map to confirm the booth alteration
	// printf("\nMap Status after Alteration:\n");
	// showMap(map);

	// // Test Case 7: Delete an enterprise and free up the booth
	// printf("\nDeleting 'Innovative Solutions' from booth 10:\n");
	// deleteEnterprise(map,enterpriseArray, "I", 10, &totalEmpty);
	// printf("Total empty booths after deletion: %d\n", totalEmpty);

	// // Show map to confirm deletion
	// printf("\nMap Status after Deletion:\n");
	// showMap(map);

	// // Test Case 8: Knapsack optimization test with sample data
	// int maxWeight = 10;
	// int maxValue, usedWeight;
	// knapsack(map, enterpriseArray, maxWeight, &maxValue, &usedWeight);
	// printf("\nKnapsack Optimization:\n");
	// printf("Max Value Collected: %d with Weight Used: %d\n", maxValue, usedWeight);

	// return 0;
}

