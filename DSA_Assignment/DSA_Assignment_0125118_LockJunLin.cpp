#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
using namespace std;

/*
	Title: Convert a String In C++ To Upper Case
	Author: -
	Retrieved Date: 9/4/2009
	Code version: -
	Availability: https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
*/

// a node structure with song details and next link
struct Music
{
	string nArtist, nSong;
	int durationM, durationS, sNumber;
	Music* next;
};

Music* front = NULL; // front node which is the first node of the list
Music* rear = NULL; // rear node which is the last node of the list
Music* temp;

// boolean function to check if list is empty 
bool isEmpty()
{
	// if both front and rear is NULL, list is empty
	if (front == NULL)
		return 1;
	else
		return 0;
}

// display playlist format
void pListFormat(Music* temp1)
{
	if (temp1->durationS < 10)
		cout << temp1->sNumber << ".\t" << temp1->nSong << "\t\t\t\t" << temp1->nArtist << "\t\t\t\t" << temp1->durationM << ":0" << temp1->durationS << endl;
	else
		cout << temp1->sNumber << ".\t" << temp1->nSong << "\t\t\t\t" << temp1->nArtist << "\t\t\t\t" << temp1->durationM << ":" << temp1->durationS << endl;
}

// void function to create a new node with user input
void createNode(int duraM1, int duraS1, int num2, string art1, string song1)
{
	temp = new Music;
	temp->durationM = duraM1;
	temp->durationS = duraS1;
	temp->nArtist = art1;
	temp->nSong = song1;
	temp->sNumber = num2;
	temp->next = NULL;
}

// function to add numbering sequence to each music in playlist
int numbering()
{
	temp = front;
	int num1 = 1;
	// first music will be label as number 1 in the playlist
	if (isEmpty()) //same as when (temp == NULL)
		return num1;
	else
	{
		while (temp != NULL) // the following sequence will increase by 1 for every new music added to the playlist
		{
			temp = temp->next;
			num1++;
		}
		return num1;
	}
}

// enqueue function to add new music to the playlist
// every new music will added to the back of the playlist
void enqueue()
{
	if (isEmpty())
		front = rear = temp;
	else
	{
		rear->next = temp;
		rear = temp;
	}
}

// dequeue function to remove played music in the playlist
// remove played music from the playlist
void dequeue()
{
	temp = front;
	if (isEmpty())
		cout << "\nPlaylist is empty. No music removed.\n" << endl;
	else
	{
		Music* remSong = front; //a node to store data of removed music in playlist
		front = front->next;
		if (front == NULL) // if front is NULL, rear will be NULL to show that list is empty
			rear = NULL;
		cout << "\nFinished song in the playlist:\nNo.\tSong Name\t\t\tArtist Name\t\t\tSong Duration(minute:second)" << endl;
		pListFormat(remSong);
		temp = front;
		while (temp != NULL) //rearrange numbering sequence of music playlist
		{
			temp->sNumber = temp->sNumber - 1;
			temp = temp->next;
		}
	}
}

// search function to search for requested music in playlist
void search(string song2)
{
	temp = front;
	string Usong2 = song2, UnSong;
	transform(Usong2.begin(), Usong2.end(), Usong2.begin(), toupper); //change input to uppercase
	if (isEmpty()) // if music playlist is empty
		cout << "\nPlaylist is empty. Search Failed.\n" << endl;
	else
	{
		while (temp != NULL) // temp will traverse until reaches the end or the while loop breaks
		{
			UnSong = temp->nSong;
			transform(UnSong.begin(), UnSong.end(), UnSong.begin(), toupper); //change music name to uppercase
			if (Usong2 == UnSong) //if input same as music in playlist then requested music will be display
			{
				cout << "\nNo.\tSong Name\t\t\tArtist Name\t\t\tSong Duration(minute:second)" << endl;
				pListFormat(temp);
				break;
			}
			temp = temp->next;
		}
		if ((temp == NULL) && (Usong2 != UnSong)) // music playlist is not empty and requested song does not exists in playlist
		{
			cout << "\nSong could not be found in Playlist." << endl;
		}
	}
}

// function to delete requested music in the playlist
void delFromNPos(int num2)
{
	Music* navi = front;  //navi node to track the movement in the playlist to point to the previous node of temp
	temp = front;
	if (isEmpty())
		cout << "\nPlaylist is empty. No music removed." << endl;
	else
	{
		if (num2 == 1)
		{
			front = temp->next;
			cout << "\nRemove song in the playlist:\nNo.\tSong Name\t\t\tArtist Name\t\t\tSong Duration(minute:second)" << endl;
			pListFormat(temp); // display removed music from playlist
		}
		else
		{
			while (temp != NULL) // temp will traverse until reaches the end of playlist or the while loop breaks
			{
				if (temp->sNumber == num2) // if requested music to remove is found in playlist, music will be removed
				{ 
					navi->next = temp->next;
					cout << "\nRemove song in the playlist:\nNo.\tSong Name\t\t\tArtist Name\t\t\tSong Duration(minute:second)" << endl;
					pListFormat(temp); // display removed music from playlist
					free(navi->next);
					navi->next = NULL;
					break;
				}
				else
				{
					navi = temp; //navi will always point to the node previous of temp
					temp = temp->next;
				}
			}
		}
		if (temp == NULL) // music playlist is not empty and requested song does not exists in playlist
		{
			cout << "\nSong could not be found in Playlist." << endl;
		}
		while (temp != NULL) //rearrange numbering sequence of music playlist
		{
			temp->sNumber = temp->sNumber - 1;
			temp = temp->next;
		}
	}
}

// display function to display music playlist
void displayQueue()
{
	temp = front;
	if (isEmpty()) // if music playlist is empty
		cout << "Playlist is empty. Please add music to the playlist to view the playlist.\n" << endl;
	else
	{
		cout << "No.\tSong Name\t\t\tArtist Name\t\t\tSong Duration(minute:second)" << endl;
		while (temp != NULL) // temp node will traverse from start of the playlist to the end of the playlist
		{
			pListFormat(temp);
			temp = temp->next;
		}
	}
}

int main()
{
	int opt, duraM, duraS, num;
	string art, song;
	do
	{
		cout << "Lock's Digital Music Player" << endl;
		cout << "Enter the following number to choose an action:" << endl;
		cout << "1 - Add music to playlist" << endl;            // enqueue
		cout << "2 - Search for music in playlist" << endl;         // Search for requested node in queue
		cout << "3 - Display music playlist" << endl;   // Display queue
		cout << "4 - Remove played music in playlist" << endl;         //dequeue
		cout << "5 - Remove music in playlist" << endl;         // Delete music at specific position
		cout << "6 - Exit" << endl;                       // exit program
		cout << "Enter here : ";
		cin >> opt;
		cout << endl;
		switch (opt)
		{
		case 1:
		{
			//user input
			cout << "Enter name of the song: ";
			cin.ignore();
			getline(cin, song, '\n');
			cout << "Enter name of the artist of the song: ";
			cin.clear();
			getline(cin, art, '\n');
			cout << "Enter duration of the song:-\nMinutes: ";
			cin >> duraM;
			cout << "Seconds: ";
			cin >> duraS;
			num = numbering();
			createNode(duraM, duraS, num, art, song);
			enqueue();
			cout << "Music added to playlist.\n" << endl;
			system("pause");
			system("CLS");
		}
		break;
		case 2:
		{
			cout << "\nEnter name of the song to find in playlist: ";
			cin.ignore();
			getline(cin,song,'\n');
			search(song);
			cout << endl;
			system("pause");
			system("CLS");
		}
		break;
		case 3:
		{
			displayQueue();
			cout << endl;
			system("pause");
			system("CLS");
		}
		break;
		case 4:
		{
			dequeue();
			cout << endl;
			system("pause");
			system("CLS");
		}
		break;
		case 5:
		{
			cout << "\nEnter number label of music in playlist to be removed: ";
			cin >> num;
			delFromNPos(num);
			cout << endl;
			system("pause");
			system("CLS");
			cin.clear();
			cin.ignore(1000, '\n');
		}
		break;
		case 6:
		{
			cout << "Exit Program.\n" << endl;
		}
		break;
		default:
		{
			cout << "Invalid input. Please enter again.\n" << endl;
			system("pause");
			system("CLS");
			cin.clear();
			cin.ignore(1000, '\n');
		}
		}
	} while (opt != 6);
	system("pause");
}