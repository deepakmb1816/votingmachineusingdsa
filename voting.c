#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int voterIdCounter=0;
int candidateIdCounter=0;

typedef struct Voter {
    int id;
    char name[50];
    char gender[10];
    int age;
    int hasVoted;
    struct Voter* next;
} Voter;

typedef struct Candidate {
    int id1;
    int age;
    char name[50];
    char gender[10];
    int voteCount;
    struct Candidate* next;
} Candidate;

Voter* voterinsertion(Voter *, char *,char *,int); 
Voter* voterdeletion(Voter*,int); 
Candidate* candidateinsertion(Candidate *, char *,char *,int);
Candidate* candidatedeletion(Candidate *,int );
Voter* searchvoter(Voter*,int);
Candidate* searchcandidate(Candidate*, int);
void displayvoter(Voter *); 
void displaycandidate(Candidate *);
Voter* deleteDuplicateVoters(Voter* start);
void voteForCandidate(Voter* , Candidate*);
int countVotersVoted(Voter* );
void displayResultsAndWinner(Candidate* );
void main()
{

Voter *start=NULL;
Candidate *start1=NULL;
char voter_name[100],candidate_name[100],votergender[10],candidategender[10];
int voter_age,choice,key_age,candidate_age,keysearchvoter_age,votersid,candidatesid;
char keyvoter_name[100],key_candidatename[100],keysearchvoter_name[100],keysearchcandidate_name[100];
while(1)
{
	printf("\nEnter your choice\n");
	printf("1. Add new voters\n");
	printf("2. Delete voters\n");
	printf("3. Add new candidates\n");
	printf("4. Delete candidates\n");
	printf("5. Display voters\n");
	printf("6. Display candidates\n");
	printf("7. Search Voter\n");
    printf("8. Search candidate\n");
    printf("9. Delete duplicate voter\n");
    printf("10. vote a candidate \n");
    printf("11. total number of voters voted \n");
    printf("12. Display the results and winner \n");
	printf("13. Exit\n");
    scanf("%d", &choice);
	switch(choice)
   {
        case 1: printf(" Enter the name of the voter \n");
                scanf("%s",voter_name);
                printf(" Enter the age of the voter\n");
                scanf("%d",&voter_age);
                printf("Enter gender of the voter\n");
                scanf("%s",votergender);
                if(voter_age>= 18)
                {
                    if (strcmp(votergender, "male") == 0 || strcmp(votergender, "female") == 0)
                    {
                        start= voterinsertion(start,voter_name,votergender,voter_age);
                    }
                    else 
                    {
                        printf("invalid gender");
                    }
                }    
                else
                {
                    printf("voter not eligible to vote\n");
                }
                break;
        case 2: printf("Enter the id of the voter\n");
                scanf("%d",&votersid);
  	            start= voterdeletion(start,votersid);
                break;
        case 3: printf(" Enter the name of the candidate\n");
                scanf("%s",candidate_name);
                printf("Enter the age of candidate\n");
	            scanf("%d",&candidate_age);
                printf("enter gender of the candidate\n");
                scanf("%s",candidategender);
                if(candidate_age>=35)
                {
                    if (strcmp(candidategender, "male") == 0 || strcmp(candidategender, "female") == 0)
                    {
                        start1=candidateinsertion(start1,candidate_name,candidategender,candidate_age);
                    }
                    else 
                    {
                        printf("invalid gender");
                    }
                }
                    else
                    {
                        printf("The candidate is not eligible\n");
                          
                    }
                    break;
        case 4: printf("Enter the candidate id to delete\n");
                scanf("%d",&candidatesid);
                start1=candidatedeletion(start1,candidatesid);
                break;
	          
  	    case 5: printf("The list of voters are : \n");
                displayvoter(start);
                break;
 	    case 6: printf("The list of candidates are :\n"); 
                displaycandidate(start1);
                break;
        case 7:
                printf("Enter the id of the voter\n");
                scanf("%d",&votersid);
                searchvoter(start,votersid);
                break;
   	    case 8: printf("Enter the candidate to be searched :\n");
                scanf("%d",&candidatesid);
	            searchcandidate(start1,candidatesid);
	            break; 
        case 9: deleteDuplicateVoters(start);
                break;     
        case 10:
                printf("Enter the id of the voter:\n");
                scanf("%d", &votersid);

                 Voter* temp;
                    Candidate *current;
                temp = start;
                if (temp == NULL)
                {
                    printf("Voter list is empty\n");
                }
                else
                {
                    while (temp != NULL && temp->id != votersid)
                    {
                        temp = temp->next;
                    }

                    if (temp == NULL)
                    {
                        printf("Invalid voter id\n");
                    }
                    else
                    {
                        printf("Voter details:\nName: %s\t Age: %d \t Gender: %s\n", temp->name, temp->age, temp->gender);
                        if (temp->hasVoted == 0)
                        {
                                printf("Enter the id of the candidate:\n");
                                scanf("%d", &candidatesid);
                                current = start1;
                                while (current != NULL && current->id1 != candidatesid)
                                 {
                                        current = current->next;
                                    }

                              if (current == NULL)
                            {
                                printf("Invalid candidate id\n");
                            }
                            else
                            {
                                printf("Candidate name: %s\n", current->name);
                                voteForCandidate(temp, current);
                            }
                        }
                        else
                    {
                        printf("Voter has already voted\n");
                     }
        }
    }
    break;
        case 11:
            printf("Total number of voters who have voted: %d\n", countVotersVoted(start));
            break;
        case 12: 
            displayResultsAndWinner(start1);
            break;
        case 13: printf("program over");
                exit(0);
        default:
            printf("enter the valid option\n");
   }
 }
}

Voter* voterinsertion(Voter *start, char *str,char *gen,int x)
{
    Voter* new_voter;
    new_voter=(Voter *)malloc(sizeof(Voter));
    new_voter->id=++voterIdCounter;
    printf("unique id of the voter %d",voterIdCounter);
    strcpy(new_voter->name,str);
    strcpy(new_voter->gender,gen);
    new_voter->hasVoted=0;
    new_voter->age=x;
    new_voter->next=start;
    start= new_voter;
    return start;
}

Voter* voterdeletion(Voter *start, int votersid)
{
    Voter *temp, *current, *prev;
    if (start == NULL)
    {
        printf("The voter list is empty\n");
        return start;
    }
    else if (start->id == votersid)
    {
        temp = start;
        start = start->next;
        printf("The deleted voter name: %s\t\t age: %d\t\t gender: %s\n", temp->name, temp->age, temp->gender);
        free(temp);
    }
    else
    {
        prev = start;
        current = start->next;

        while (current != NULL && current->id != votersid)
        {
            prev = prev->next;
            current = current->next;
        }

        if (current == NULL)
        {
            printf("Invalid key\n");
        }
        else
        {
            prev->next = current->next;
            temp = current;
            printf("The deleted voter name: %s\t\t age: %d\t\t gender: %s\n", temp->name, temp->age, temp->gender);
            free(temp);
        }
    }

    return start;
}


Candidate* candidateinsertion(Candidate *start1, char *str2,char*candidategender,int candidate_age)
{
    Candidate *new_candidate;
    new_candidate=(Candidate*)malloc(sizeof(Candidate));
    new_candidate->id1=++candidateIdCounter;
    printf("unique id of the voter %d",candidateIdCounter);
    strcpy(new_candidate->name,str2);
    strcpy(new_candidate->gender,candidategender);
    new_candidate->age=candidate_age;
    new_candidate->next=start1;
    start1=new_candidate;
    return start1;
}

Candidate* candidatedeletion(Candidate *start1,int candidatesid)
 {
    Candidate *temp,*current,*prev;
    
    if (start1 == NULL)
    {
        printf("The voter list is empty\n");
        return start1;
    }
    else if (start1->id1 == candidatesid)
    {
        temp=start1;
        start1=start1->next;
        printf("The deleted candidate name: %s\t\t age: %d\t\t gender: %s", temp->name,temp->age,temp->gender);
        free(temp);
    }
    else
    {
        prev = start1;
        current = start1->next;
        
        while (current != NULL && current->id1 != candidatesid)
        {
            prev = prev->next;
            current = current->next;
        }

        if (current == NULL)
        {
            printf("Invalid key\n");
        }
        else
        {
            prev->next = current->next;
           printf("The deleted candidate name: %s\t\t age: %d\t\t gender: %s", temp->name,temp->age,temp->gender);

            free(current);
        }
    }
    return start1;
}

void displayvoter(Voter *start)
{ 
    Voter *ptr;
    if(start==NULL)
    {
        printf("No voters in the list\n");
    }
    else
    {
        ptr=start;
        while(ptr!=NULL)
        {
            printf("\nName: %s \t Age :%d\t gender : %s \t uniqueid: %d \n",ptr->name,ptr->age,ptr->gender,ptr->id);
            ptr=ptr->next;
        }
    }
}

void displaycandidate(Candidate *start1)
{ 
    Candidate *ptr;
    if(start1==NULL)
    {
        printf("No candidates in the list\n");
    }
    else
    {
        ptr=start1;
        while(ptr!=NULL)
        {
            printf("\nName: %s \t Age :%d\t gender : %s \t uniqueid: %d \n",ptr->name,ptr->age,ptr->gender,ptr->id1);
            ptr=ptr->next;
        }
    }
}

Voter* searchvoter(Voter* start, int votersid) 
{
   Voter *temp;
   if(start==NULL)
   {
    printf("list is empty");
    return start;
   }
   else
   {   
         temp = start;  
         while((temp != NULL)&&(temp->id !=votersid))
                   {
                         temp = temp->next;
                   }
          
            if((temp == NULL)&&temp->id!=votersid)
                   printf("Invalid key\n");
            else
                   printf("voter ID %d founded \n voter details is :\n Name :%s \n Age : %d\n Gender:%s\n", temp->id,temp->name,temp->age,temp->gender);   
      }    
    return start;   
} 

Candidate* searchcandidate(Candidate* start1, int candidatesid) 
{
    Candidate *current;
    if(start1==NULL)
   {
    printf("list is empty");
    return start1;
   }
   else
   {    
         current= start1;  
         while((current != NULL)&&(current->id1 !=candidatesid))
                   {
                        current = current->next;
                   }
          
            if((current== NULL)&&current->id1!=candidatesid)
                   printf("Invalid key\n");
            else
                   printf("voter ID %d founded \n voter details is :\n Name :%s \n Age : %d\n Gender:%s \n", current->id1,current->name,current->age,current->gender);   
      }    
    return start1;   
} 

Voter* deleteDuplicateVoters(Voter* start)
{
    Voter* current = start;
    Voter* compare;
    Voter* temp;
    while (current != NULL)
    {
        compare = current;
        while (compare->next != NULL) 
        {
            if (strcmp(current->name, compare->next->name) == 0 && current->age == compare->next->age) 
            {
                temp = compare->next;
                compare->next = compare->next->next;
                printf("\nThe duplicate voter is:\nName: %s\nAge: %d\nID: %d\nGender: %s\n", temp->name, temp->age, temp->id, temp->gender);
                free(temp);
            }
            else 
            {
                compare = compare->next;
            }
        }
        current = current->next;
    }
    printf("no duplicate voters in the list");
   return start;
}

void voteForCandidate(Voter* tempofvoter, Candidate* candidate)
{
        printf("Voter %s voted for Candidate %s\n", tempofvoter->name, candidate->name);
        candidate->voteCount++;
        tempofvoter->hasVoted=1;
}

int countVotersVoted(Voter* start)
{
    int count = 0;
    Voter* current = start;
    while (current != NULL) 
    {
        if (current->hasVoted == 1)
        {
            count++;
        }
        current = current->next;
    }
    return count;
}

void displayResultsAndWinner(Candidate* start1)
{
    Candidate* current = start1;
    int maxVotes = 0;
    Candidate* winner = NULL;
    if (current == NULL) 
    {
        printf("No candidates in the list\n");
        return;
    }
    printf("Results:\n");
    while (current != NULL)
    {
        printf("\nName: %s \t Age: %d \t Gender: %s \t Votes: %d \t Candidate ID: %d\n", current->name, current->age, current->gender, current->voteCount, current->id1);
        if (current->voteCount > maxVotes) 
        {
            maxVotes = current->voteCount;
            winner = current;
        }
        current = current->next;
    }
    if (winner != NULL) 
    {
        printf("\nWinner:\nName: %s \t Age: %d \t Gender: %s \t Votes: %d \t Candidate ID: %d\n", winner->name, winner->age, winner->gender, winner->voteCount, winner->id1);
    }
    else
    {
        printf("\nNo winner found\n");
}
}
