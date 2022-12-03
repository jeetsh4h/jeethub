#include "PlaylistNode.h"
#include <string>

void PrintMenu(const string playlistTitle) {
    cout << playlistTitle << " PLAYLIST MENU\n";
    cout << "a - Add song\n";
    cout << "d - Remove song\n";
    cout << "c - Change position of song\n";
    cout << "s - Output songs by specific artist\n";
    cout << "t - Output total time of playlist (in seconds)\n";
    cout << "o - Output full playlist\n";
    cout << "q - Quit\n";
}

void AddSong(PlaylistNode* &headNode, string id, string sName, string aName, int len) {
    PlaylistNode* newSong = new PlaylistNode(id, sName, aName, len);
    PlaylistNode* current = headNode->GetNext();

    if(current == NULL) {
        headNode->SetNext(newSong);
        return;
    }

    while(current->GetNext() != NULL) {
        current = current->GetNext();
    }
    current->SetNext(newSong);
    return;
}

void RemoveSongID(PlaylistNode* &headNode, string id) {
    PlaylistNode* current = headNode->GetNext();
    PlaylistNode* prev = headNode;
    
    while (true) {
        if (current->GetID() == id) {
            prev->SetNext(current->GetNext());
            break;
        } else {
            current = current->GetNext();
            prev = prev->GetNext();
        }
    }
    cout << '\"' << current->GetSongName() << "\" removed.\n";
    delete current;
}

void RemoveSong(PlaylistNode* &headNode, PlaylistNode* &node) {
    PlaylistNode* current = headNode->GetNext();
    PlaylistNode* prev = headNode;
    while (current != node) {
        current = current->GetNext();
        prev = prev->GetNext();
    }

    prev->SetNext(current->GetNext());
    delete current;
}

void ChangePos(PlaylistNode* &headNode, int cPos, int nPos) {
    PlaylistNode *current;
    PlaylistNode *nCurrent;
    PlaylistNode *prev;
    int numNodes;
    int i;

    current = headNode;
    numNodes = 0;
    while (current->GetNext() != NULL) {
        current = current->GetNext();
        numNodes++;
    }

    nPos = (nPos > numNodes) ? numNodes : nPos;
    nPos = (nPos < 1) ? 1 : nPos;
    cPos = (cPos > numNodes) ? numNodes : cPos;
    cPos = (cPos < 1) ? 1 : cPos;

    // if (cPos == nPos) { 
    //     cout << "\n\"" << current->GetSongName() << "\" moved to position " 
    //          << nPos << endl << endl;
    //     return; 
    // }

    prev = headNode;
    i = 0;
    while (i < cPos - 1) {
        prev = prev->GetNext();
        i++;
    }
    current = prev->GetNext();
    prev->SetNext(current->GetNext());
    current->SetNext(NULL);


    nCurrent = headNode;
    i = 0;
    while (i < nPos - 1) {
        nCurrent = nCurrent->GetNext();
        i++;
    }
    current->InsertAfter(nCurrent);

    cout << "\n\"" << current->GetSongName() << "\" moved to position " 
         << nPos << endl << endl;
}

void OutputArtistSongs(PlaylistNode* &headNode, string aName) {
    int numbering = 1;
    PlaylistNode* current = headNode->GetNext();

    while (current != NULL) {
        if (current->GetArtistName() == aName) {    
            cout << endl << numbering << '.' << endl;
            current->PrintPlaylistNode();
        }
        current = current->GetNext();
        numbering++;
    }
}

int TotalPlayTime(PlaylistNode* &headNode) {
    int time = 0;
    PlaylistNode* current = headNode->GetNext();

    while (current != NULL) {
        time += current->GetSongLength();
        current = current->GetNext();
    }

    return time;
}

void OutputPlaylist(PlaylistNode* &headNode) {
    int numbering = 1;
    PlaylistNode* current = headNode->GetNext();

    if (headNode->GetNext() == NULL) {
        cout << "\nPlaylist is empty\n";
    } else {
        while (current != NULL) {
            cout << endl << numbering << '.' << endl;
            
            current->PrintPlaylistNode();
            current = current->GetNext();

            numbering++;
        }
    }
}

PlaylistNode* ExecuteMenu(char option, string playlistTitle, PlaylistNode* headNode) {
    string id;          //used in RemoveSongID
    string sName;
    string aName;       //used in output by specific artist (also)
    int len;
    
    int cPos;
    int nPos;

    switch (option) {
        case 'a':
            cout << "\nADD SONG\n";

            cout << "Enter song's unique ID:\n";
            cin.ignore();
            getline(cin, id);
            
            cout << "Enter song's name:\n";
            getline(cin, sName);

            cout << "Enter artist's name:\n";
            getline(cin, aName);

            cout << "Enter song's length (in seconds):\n";
            cin >> len;

            AddSong(headNode, id, sName, aName, len);
            cout << endl;
            break;
        
        case 'd':
            cout << "\nREMOVE SONG\n";

            cout << "Enter song's unique ID:\n";
            cin.ignore();
            getline(cin, id);

            RemoveSongID(headNode, id);
            cout << endl;
            break;

        case 'c':
            cout << "\nCHANGE POSITION OF SONG\n";

            cout << "Enter song's current position:\n";
            cin >> cPos;
            cout << "Enter new position for song:\n";
            cin >> nPos;
            
            ChangePos(headNode, cPos, nPos);
            break;

        case 's':
            cout << "\nOUTPUT SONGS BY SPECIFIC ARTIST\n";
            cout << "Enter artist's name:\n";
            cin.ignore();
            getline(cin, aName);

            OutputArtistSongs(headNode, aName);
            cout << endl;
            break;

        case 't':
            cout << "\nOUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n";
            cout << "Total time: " << TotalPlayTime(headNode) << " seconds\n\n";
            break;
        case 'o':
            cout << endl << playlistTitle << " - OUTPUT FULL PLAYLIST";
            OutputPlaylist(headNode);
            cout << endl;
            break;
    }
    return headNode;
}

int main() {
    string playlistTitle;
    char option;
    PlaylistNode* PlaylistHead = new PlaylistNode();        //headed list

    cout << "Enter playlist's title:\n";
    getline(cin, playlistTitle);

    cout << endl;
    PrintMenu(playlistTitle);
    cout << "\nChoose an option:\n";
    cin >> option;

    while (true) {
        switch (option) {
            case 'a':
            case 'd':
            case 'c':
            case 's':
            case 't':
            case 'o':
                PlaylistHead = ExecuteMenu(option, playlistTitle, PlaylistHead);

                PrintMenu(playlistTitle);
                cout << "\nChoose an option:\n";
                cin >> option;
                break;
            case 'q':
                return 0;
            default:
                PrintMenu(playlistTitle);
                cout << "\nChoose an option:\n";
                cin >> option;
        }
    }

    return 0;
}