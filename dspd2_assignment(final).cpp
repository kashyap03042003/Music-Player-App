#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define MAX_PLS 20 // assuming maximum no of playlists we can create is 20
typedef struct Song{
    char singer[50];
    char lyricist[50];
    char film[50];
    char composer[50];
    char genre[50];
    char songName[50];
    int duration;
    struct Song *next;
    struct Song *prev;
}Song;

//q1 Write a function, InsertSong(), which reads a song from user and insert into a linked list of structures. Add a new song at the end in the list
void InsertSong(struct Song** head, int *dataBaseCount)
{
    Song* new_song = (Song*) malloc(sizeof(Song));
    
    printf("Enter song name: ");
    scanf("%s", new_song->songName);
    printf("Enter singer name: ");
    scanf("%s", new_song->singer);
    printf("Enter lyricist name: ");
    scanf("%s", new_song->lyricist);
    printf("Enter film/album name: ");
    scanf("%s", new_song->film);
    printf("Enter composer name: ");
    scanf("%s", new_song->composer);
    printf("Enter genre: ");
    scanf("%s", new_song->genre);
    printf("Enter song duration in seconds: ");
    scanf("%d", &new_song->duration);

    new_song->next = NULL;
    new_song->prev = NULL;
    (*dataBaseCount)++;

    if (!(*head)) 
    {
        
        new_song->prev = NULL;
        *head = new_song;
    }
    else 
    {
        
        Song* last_node = *head;
        while (last_node->next)
        {
            last_node = last_node->next;
        }
        
        
        last_node->next = new_song;
        new_song->prev = last_node;
    }
}

//q2 Write a function removeDuplicates() to remove the duplicate entries from the records

void removeDuplicates(Song** head) {
    if (!(*head))
	{
        return;
    }
    
    Song *current = *head;
	Song *temp = NULL;
	Song *duplicate_node = NULL;
    
    while (current && current->next) {
        temp = current;
        
        while (temp->next != NULL) {
            if (strcmp(current->singer, temp->next->singer) == 0 && strcmp(current->lyricist, temp->next->lyricist) == 0 && strcmp(current->film, temp->next->film) == 0 &&
                strcmp(current->composer, temp->next->composer) == 0 && strcmp(current->genre, temp->next->genre) == 0 && current->duration == temp->next->duration &&
                strcmp(current->songName, temp->next->songName) == 0)
			{
                
                duplicate_node = temp->next;
                temp->next = duplicate_node->next;
                if(duplicate_node->next) duplicate_node->next->prev = temp; // duplicate node is not the last node (edited)
                free(duplicate_node);
                
            } 
			else 
			{
                temp = temp->next;
            }
        }
        current = current->next;
    }
}

//to play a particular song :
void playSong(Song *sptr){
    printf("Song: %s\n", sptr->songName);
    printf("Singer: %s\n", sptr->singer);
    printf("Lyricist: %s\n", sptr->lyricist);
    printf("Film/Album: %s\n", sptr->film);
    printf("Composer: %s\n", sptr->composer);
    printf("Genre: %s\n", sptr->genre);
    printf("Duration: %d\n\n", sptr->duration);
}

//to count matchings
int countMatches(Song *curr_song, int num_attributes, char **attributes, char **values){
    int matches = 0, i;
    for (i = 0; i < num_attributes; i++) {
        if (strcmp(attributes[i], "singer") == 0 && strcmp(curr_song->singer, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "lyricist") == 0 && strcmp(curr_song->lyricist, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "film") == 0 && strcmp(curr_song->film, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "composer") == 0 && strcmp(curr_song->composer, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "genre") == 0 && strcmp(curr_song->genre, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "songName") == 0 && strcmp(curr_song->songName, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "duration") == 0 && curr_song->duration == atoi(values[i])) {
            matches++;
        }
    }
    return matches;
}

//q3 Write a function to printPlaylist() which prints the records in the linked list in ascending as well as in descending order.

//a mergesort function for sorting according to different attributes
Song* merge(Song *left, Song *right, char attribute[]){
    Song *result = NULL;
    if(left == NULL){
        return right;
    }
    else if(right == NULL){
        return left;
    }
    if(strcmp(attribute, "songName") == 0){
        if(strcmp(left->songName, right->songName) <= 0){
            result = left;
            result->next = merge(left->next, right, attribute);
        }
        else{
            result = right;
            result->next = merge(left, right->next, attribute);
        }
    }
    else if(strcmp(attribute, "singer") == 0){
        if(strcmp(left->singer, right->singer) <= 0){
            result = left;
            result->next = merge(left->next, right, attribute);
        }
        else{
            result = right;
            result->next = merge(left, right->next, attribute);
        }
    }
    else if(strcmp(attribute, "film") == 0){
        if(strcmp(left->film, right->film) <= 0){
            result = left;
            result->next = merge(left->next, right, attribute);
        }
        else{
            result = right;
            result->next = merge(left, right->next, attribute);
        }
    }
    else if(strcmp(attribute, "composer") == 0){
        if(strcmp(left->composer, right->composer) <= 0){
            result = left;
            result->next = merge(left->next, right, attribute);
        }
        else{
            result = right;
            result->next = merge(left, right->next, attribute);
        }
    }
    else if(strcmp(attribute, "genre") == 0){
        if(strcmp(left->genre, right->genre) <= 0){
            result = left;
            result->next = merge(left->next, right, attribute);
        }
        else{
            result = right;
            result->next = merge(left, right->next, attribute);
        }
    }
    else if(strcmp(attribute, "duration") == 0){
        if(left->duration <= right->duration){
            result = left;
            result->next = merge(left->next, right, attribute);
        }
        else{
            result = right;
            result->next = merge(left, right->next, attribute);
        }
    }
    return result;
}

Song* mergeSort(Song *head, char attribute[]){
    if(!head || !head->next){
        return head;
    }
    Song *slow = head;
    Song *fast = head->next->next;
    while(fast != NULL){
        slow = slow->next;
        if(fast->next){
            fast = fast->next->next;
        }
        else fast = fast->next;
    }
    Song *left = head;
    Song *right = slow->next;
    slow->next = NULL;
    left = mergeSort(left, attribute);
    right = mergeSort(right, attribute);
    return merge(left, right, attribute);
}

void rearrangeAfterMergeSort(Song *head){
    Song *curr = head, *pre = NULL;
    while(curr){
        curr->prev = pre;
        pre = curr;
        curr = curr->next;
    }
}

void printPlaylist(Song *head){
    Song *temp = head, *pre = NULL;
    printf("\n******printing in ascending order!!******\n");
    while(temp){
        playSong(temp);
        pre = temp; // edited
        temp = temp->next;
    }
    
    Song *temp1 = pre;
        printf("\n\n\n******printing in descending order!!******\n");
    while(temp1 != NULL){
        playSong(temp1);
        temp1 = temp1->prev;
    }    
}


/*q4 Write a function to DeleteSong() to delete 
 the particular song details from the linked list
 as per the song_name and also as per the name of
 the artist provided by the user and deletes all 
 the entries with that artist.*/

void DeleteSong(struct Song** head) {
    Song* current = *head;
    Song* pre = NULL;
    Song* temp = NULL;
    char name[50];
    char artist[50];
    printf("\nenter the name of the song\n");
    scanf("%s",name);
    printf("\nenter the name of the artist/singer\n");
    scanf("%s",artist);
    
    while (current != NULL) {
        if (strcmp(current->songName, name) == 0 && strcmp(current->singer, artist) == 0) 
		{
            if (pre == NULL) 
			{
                // If the matched node is the first node
                *head = current->next;
                if(*head){ // and contains multiple nodes (edited)
                    (*head)->prev = NULL;
                }
            } 
			else 
			{
                // If the matched node is not the first node
                pre->next = current->next;
                if(current->next){ // and matched node is not the last node (edited)
                    current->next->prev = pre;
                }
            }
            temp = current;
            current = current->next;
            free(temp);
        } 
		else 
		{
            // Move to the next node
            pre = current;
            current = current->next;
        }
    }
    printf("Songs Romoved from the dataBase successfully\n");
}

//q5 Create a play-list based on the attribute and its value given. 

void InsertPlaylist(Song **head, Song *new_song) {
    if (*head == NULL) {
        *head = new_song;
    }
    else {
        Song *curr_song = *head;
        while (curr_song->next != NULL) {
            curr_song = curr_song->next;
        }
        curr_song->next = new_song;
        new_song->prev = curr_song;
    }
}

Song* CreatePlaylist(Song *head, char* attributes[], char* values[], int num_attributes) {
    Song *playlist = NULL, *curr_song = head;
    while (curr_song != NULL) {
        int matches = countMatches(curr_song, num_attributes, attributes, values);
        if (matches == num_attributes) {
            Song *new_song = (Song*)malloc(sizeof(Song));
            strcpy(new_song->singer, curr_song->singer);
            strcpy(new_song->lyricist, curr_song->lyricist);
            strcpy(new_song->film, curr_song->film);
            strcpy(new_song->composer, curr_song->composer);
            strcpy(new_song->genre, curr_song->genre);
            strcpy(new_song->songName, curr_song->songName);
            new_song->duration = curr_song->duration;
            new_song->next = NULL;
            new_song->prev = NULL;
            InsertPlaylist(&playlist, new_song);
        }
        curr_song = curr_song->next;
    }
    removeDuplicates(&playlist);   // Remove duplicates if any
    
	char attribute_songname[100]="songName";
    playlist=mergeSort(playlist,attribute_songname);
    return playlist;
}

//q6 display playlist for give attributes and take option from user to print details of previous song details or next song details
void DisplayPlaylist(Song* playlist)
{
	int serial_no=1;
	Song* temp=playlist;
	while(temp)
	{
        playSong(temp);
		serial_no++;
		temp=temp->next;
	}
	
	int sNo,k=1;
	printf("\nenter the serial number of the song name to be displayed");
	scanf("%d",&sNo);
	Song* tempNode=playlist;
	while(k<sNo)
	{
		k++;
		tempNode=tempNode->next;
	}
	
	printf("\nThe name of the current song is %s",tempNode->songName);
	if(tempNode->prev){
		printf("\nThe name of the previous song is %s",tempNode->prev->songName);
	}
	
	if(tempNode->next){
		printf("\nThe name of the next song is %s",tempNode->next->songName);
	}
	Song* temp1=tempNode;
	
	int choice;
	printf("\n\nPress 0 to display the details of the previous song\n");
	printf("Press 1 to display the details of the next song\n");
	printf("Note: ENTER ONLY EITHER ZERO OR ONE\n");	
	scanf("%d",&choice);
	
	while(choice==0 || choice==1) // infinite loop (edited)
	{
		if(choice==0)
		{
			Song* prev_node=temp1->prev;
			if(!prev_node){
				printf("\nCannot show the details of the previous song\n");
			}
			else
			{
				printf("***The details of the previous song***\n");
				printf("song name is : %s\nfilm name is : %s\nsinger name is : %s\ncomposer name is : %s\n The duration of the song is : %d",prev_node->songName,prev_node->film,prev_node->singer,prev_node->composer,prev_node->duration);
			}	
            choice = -1; // edited		
		}
		
		else if(choice==1)
		{
			Song* next_node=temp1->next;
			if(!next_node)
			{
			printf("\nCannot show the details of the next song\n");	
			}
			else
			{
				printf("***The details of the Next song***\n");
				printf("song name is : %s\nfilm name is : %s\nsinger name is : %s\ncomposer name is : %s\n The duration of the song is : %d",next_node->songName,next_node->film,next_node->singer,next_node->composer,next_node->duration);
			}		
            choice = -1; // edited
		}
	}
}



/*q7 Given a play-list and the serial number of the song, display details of the song. 
At this point, given an integer offset �k� and direction �up� or �down�, display the details of kth
previous or kth next song, from the current song, respectively, in the play-list.*/
void DisplayplaylistDetails(Song* playlist,int index)
{
	int tempSerial=1;
	Song* temp1=playlist;
	while(temp1 && tempSerial<index)
	{
		tempSerial++;
		temp1=temp1->next;		
	}
	printf("\n***Current Playing Song***\n");
    playSong(temp1);
	int k;
	char direction[10];
	
	printf("\nenter the value k: \n");
	scanf("%d",&k);
	
	printf("enter the direction up/down");
	scanf("%s",&direction);
	
	if(strcmp(direction, "down") == 0 || strcmp(direction, "Dowm") == 0 || strcmp(direction, "DOWN") == 0)
	{
		Song* tempDown = temp1;
		int tempvalue1=k;
		while(tempvalue1 && tempDown) // loop invariant edited
		{
		    tempDown = tempDown->next;
            tempvalue1--;
		}
		if(tempDown == NULL){
			printf("%d th node from down cannot exist. Try giving another value", k); // '&' removed before k
		}
		else
		{
			printf("***The details of the %d th song from down is:***\n\n",k); // '&' removed before k
            playSong(tempDown);
		}		
	}
	else if(strcmp(direction, "up") == 0 || strcmp(direction, "Up") == 0 || strcmp(direction, "UP") == 0){
		Song* tempUp=temp1;
		int tempvalue2=k;
		while(tempvalue2 && tempUp) // loop invariant edited
		{
		    tempUp = tempUp->prev;
            tempvalue2--;
		}
		if(tempUp == NULL){
			printf("%d th node from up cannot exist. Try giving another value",k); 
		}
		else
		{
			printf("***The details of the %d th song from up is:***\n\n",k); 
            playSong(tempUp);
		}	
	}
}

/*q8 Given a play-list and the serial number of the song, display details of the song. Provide an 
option to the user to select one or many attributes of this �current� song and create a playlist for these attribute values from the original database*/
Song* createPlayListFromSong(Song *head, Song *plptr, int sno){
    Song *ptr = plptr, *nplptr = NULL; //new play list pointer
    int k = 1;
    while(k < sno && ptr){
        ptr = ptr->next;
        k++;
    }
    if(ptr == NULL){
        printf("song with the given serial number %d in the given playlist doesnot exist!!\n", sno);
        nplptr = NULL;
    }
    else{
        printf("\n***Current Playing Song in the given playlist***\n");
        playSong(ptr);        
        int numOfAtt, i;
        printf("Enter how many number of attributs of this song you want to select to create a new playlist based on their values\n");
        scanf("%d", &numOfAtt);
        fflush stdin;
        char *attributes[numOfAtt];
        for(i=0; i<numOfAtt; i++){
            attributes[i] = (char*)malloc(50*sizeof(char));
            printf("Enter attribute %d", i+1);
            scanf("%s", attributes[i]);
        }
        Song *curr = head;
        while (curr){
            int matches = 0;
            for(i=0; i<numOfAtt; i++){
                if(strcmp(attributes[i], "singer") == 0 && strcmp(ptr->singer, curr->singer) == 0) matches++;
                else if(strcmp(attributes[i], "lyricist") == 0 && strcmp(ptr->lyricist, curr->lyricist) == 0) matches++;
                else if(strcmp(attributes[i], "film") == 0 && strcmp(ptr->film, curr->film) == 0) matches++;
                else if(strcmp(attributes[i], "composer") == 0 && strcmp(ptr->composer, curr->composer) == 0) matches++;
                else if(strcmp(attributes[i], "genre") == 0 && strcmp(ptr->genre, curr->genre) == 0) matches++;
                else if(strcmp(attributes[i], "duration") == 0 && ptr->duration == curr->duration) matches++;
                else if(strcmp(attributes[i], "songname") == 0 && strcmp(ptr->songName, curr->songName) == 0) matches++;
            }
            if(matches == numOfAtt){
                Song *snptr = (Song*)malloc(sizeof(Song));
                snptr->next = snptr->prev = NULL;
                strcpy(snptr->composer, curr->composer);
                strcpy(snptr->film, curr->film);
                strcpy(snptr->genre, curr->genre);
                strcpy(snptr->lyricist, curr->lyricist);
                strcpy(snptr->singer, curr->singer);
                strcpy(snptr->songName, curr->songName);
                snptr->duration = curr->duration;
                InsertPlaylist(&nplptr, snptr);
            }
            curr = curr->next;
        }
        for(i=0; i<numOfAtt; i++){
            free(attributes[i]);
        }
        removeDuplicates(&nplptr);
    }
    return nplptr;   
}


//q9 Filter the playlist. Given a play-list and an attribute value, filter all songs in the playlist matching the attribute value
void filterPlayList(Song* playlist, char* attribute) {
    Song* currHead = playlist;
    int found = 0; 
    
    printf("\nSongs matching attribute value %s:\n", attribute);
    while(currHead) {
        if(strcmp(currHead->composer, attribute) == 0 || strcmp(currHead->film, attribute) == 0 || strcmp(currHead->genre, attribute) == 0 || strcmp(currHead->lyricist, attribute) == 0 || strcmp(currHead->songName, attribute) == 0) {
            playSong(currHead);
            printf("*******************************************\n");
            found = 1; 
        }
        currHead = currHead->next;
    }
    if(!found) {
        printf("\nNo songs found with %s\n", attribute);
    }
}


//q10 play in a loop k times
void playInLoop(Song* playlist, int k) {
    for(int i = 0; i < k; i++) {
        printf("\nLoop %d\n", i+1);
        Song* curr = playlist;
        while(curr) {
            printf("\n");
            playSong(curr);
            printf("\n\n");
            curr = curr->next;
        }
    }
}


//q11 
/*Shuffle to something else. Take a set of attributes and their values as inputs. Randomly
select any song from the original database matching all the attribute values provided.

Mark it using FLAG so that it doesn’t get a chance again till all other songs in the playlist
are played randomly.*/
void shuffleToSomethingElse(Song *head, char **attributes, char **values, int numOfAtt, int dataBaseCount){
    int done = 0, i;
    int flag[dataBaseCount];
    for(i=0; i<dataBaseCount; i++) flag[i] = 0;

    while(!done){
        Song *currSong = head;
        int songNum = abs(rand()) % dataBaseCount, k=0;
        while(currSong && k<songNum){
            currSong = currSong->next;
            k++;
        }
        if(!flag[k]){
            flag[k] = 1;
            int matches = countMatches(currSong, numOfAtt, attributes, values);
            if(matches == numOfAtt){
                playSong(currSong);
            }
        }
        int c = 0;
        for(i=0; i<dataBaseCount; i++){
            if(flag[i] == 1){
                c++;
            }
        }
        if(c == dataBaseCount) done = 1;
    }
}

int main()
{
    Song* head = NULL;
    int dataBaseCount = 0, playListCount = -1;
    Song* new_playlist[MAX_PLS];  
   
    int choice;
    do
    {
        printf("\n*****MAIN MENU*****\n");
        printf("1. Insert Song\n");
        printf("2. Remove Duplicates\n");
        printf("3. Sort based on given attributes\n");
        printf("4. Display Songs\n");
        printf("5. Delete all songs based on song name and singer name\n");
        printf("6. Create new playlist based on attribute(s) and value\n");
        printf("7. Display a playlist\n");
        printf("8. display contents of kth up or kth down node from the current song\n");
        printf("9. Filter all songs in the playlist according to given attribute\n");
        printf("10. play the playlist in a loop\n");
        printf("11. Create new playlist based on attribute(s) and value of selected song\n");
        printf("12. Shuffle to something else\n");
        printf("13. Exit\n");


        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                InsertSong(&head, &dataBaseCount);
                printf("\nSong Inserted Successfully!\n");
                break;
            case 2:
                removeDuplicates(&head);
                printf("\nDuplicates Removed Successfully!\n");
                break;
            case 3:
                char attribute[50];
                printf("\nEnter the attribute upon which you want to sort (songName, singer, film, composer, genre, duration):\n\n****NOTE:ENTER THE ATTRIBUTES FROM ONLY ABOVE.EACH AND EVERY ATTRIBUTE IS CASE SENSITIVE!!****\n\n");
                scanf("%s", attribute);
                head = mergeSort(head, attribute);
                rearrangeAfterMergeSort(head);
                break; 
            case 4:            	
                printPlaylist(head);
                break;
            case 5:
                DeleteSong(&head);
                break;     
            case 6:
                char* attributes[10];
                char* values[10];
                int num_attributes;
                printf("\nEnter the number of attributes to use for the playlist: ");
                scanf("%d", &num_attributes);
                for(int i=0; i<num_attributes; i++)
				{
                    attributes[i] = (char*)malloc(50*sizeof(char));
                    values[i] = (char*)malloc(50*sizeof(char));
                    printf("\nEnter attribute %d: ", i+1);
                    scanf("%s", attributes[i]);
                    printf("Enter value %d: ", i+1);
                    scanf("%s", values[i]);
                }
                new_playlist[++playListCount] = CreatePlaylist(head, attributes, values, num_attributes);
                printf("\nNew playlist created successfully!\n");
                printf("\nPlaylist:\n");
                printPlaylist(new_playlist[playListCount]);
               
			    // Free the memory allocated for attributes and values
               	for(int i=0; i<num_attributes; i++)
				{
                    free(attributes[i]);
                    free(values[i]);
                }
                break;
            case 7:
                int idx;
                printf("Enter the index of the playlist that you want to select\n");
                printf("Available no of playlists are from 0 to %d\n", playListCount);
                printf("*****NOTE : Enter index only in this range (both inclusive)*****\n");
                scanf("%d", &idx);
			    DisplayPlaylist(new_playlist[idx]);
				break; 
			case 8:
                int songIndx, plindx;
                printf("Enter the index of the playlist that you want to select\n");
                printf("Available no of playlists are from 0 to %d\n", playListCount);
                printf("*****NOTE : Enter index only in this range (both inclusive)*****\n");
                scanf("%d", &plindx);
                printf("enter the index for the song to be displayed");
                scanf("%d",&songIndx);
                DisplayplaylistDetails(new_playlist[plindx],songIndx);
                break;
			case 9:
                char attri[50];
                printf("Enter the attribute\n");
                scanf("%s",attri);	
                printf("Enter the index of the playlist that you want to select\n");
                printf("Available no of playlists are from 0 to %d\n", playListCount);
                printf("*****NOTE : Enter index only in this range (both inclusive)*****\n");
                scanf("%d", &idx);
                filterPlayList(new_playlist[idx],attri);
                break;
			case 10:
                int loop;
                printf("Enter the index of the playlist that you want to select\n");
                printf("Available no of playlists are from 0 to %d\n", playListCount);
                printf("*****NOTE : Enter index only in this range (both inclusive)*****\n");
                scanf("%d", &idx);
                printf("enter the number of times you want to play the list in loop");
                scanf("%d",&loop);
                playInLoop(new_playlist[idx],loop);
                break;	
            case 11: // actual q8
                int songNum;
                printf("Enter the index of the playlist that you want to select\n");
                printf("Available no of playlists are from 0 to %d (both inclusive)\n", playListCount);
                scanf("%d", &idx);
                printf("Enter the serial number of the song : ");
                scanf("%d", &songNum);
                new_playlist[++playListCount] = createPlayListFromSong(head, new_playlist[idx], songNum);
				break;
            case 12: // actual q11
                printf("\nEnter the number of attributes to use for the playlist: ");
                scanf("%d", &num_attributes);
                for(int i=0; i<num_attributes; i++)
				{
                    attributes[i] = (char*)malloc(50*sizeof(char));
                    values[i] = (char*)malloc(50*sizeof(char));
                    printf("\nEnter attribute %d: ", i+1);
                    scanf("%s", attributes[i]);
                    printf("Enter value %d: ", i+1);
                    scanf("%s", values[i]);
                }

                shuffleToSomethingElse(head, attributes, values, num_attributes, dataBaseCount);

                for(int i=0; i<num_attributes; i++)
				{
                    free(attributes[i]);
                    free(values[i]);
                }
            case 13:
                printf("\nExiting...\n");
                exit(0);
                break;
        
            default:
                printf("\nInvalid Choice!\n");
        }
    } while (choice != 13);

    return 0;
}










