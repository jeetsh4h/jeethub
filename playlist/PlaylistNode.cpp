#include "PlaylistNode.h"

PlaylistNode::PlaylistNode() {
    uniqueId = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = NULL;
}

PlaylistNode::PlaylistNode(string id, string sName, string aName, int len) {
    uniqueId = id;
    songName = sName;
    artistName = aName;
    songLength = len;
    nextNodePtr = NULL;
}

PlaylistNode::PlaylistNode(PlaylistNode *&song) {
    uniqueId = song->GetID();
    songName = song->GetSongName();
    artistName = song->GetArtistName();
    songLength = song->GetSongLength();
    nextNodePtr = song->GetNext();
}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    this->SetNext(node->GetNext());
    node->SetNext(this);
}

void PlaylistNode::SetNext (PlaylistNode* newNext) { nextNodePtr = newNext; }

string PlaylistNode::GetID () { return uniqueId; }

string PlaylistNode::GetSongName () { return songName; }

string PlaylistNode::GetArtistName () { return artistName; }

int PlaylistNode::GetSongLength () { return songLength; }

PlaylistNode* PlaylistNode::GetNext () { return nextNodePtr; }

void PlaylistNode::PrintPlaylistNode () {
    cout << "Unique ID: " << uniqueId << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

