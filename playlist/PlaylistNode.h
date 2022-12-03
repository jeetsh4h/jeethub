#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;


class PlaylistNode {
   string         uniqueId;
   string         songName;
   string         artistName;
   int            songLength;
   PlaylistNode*  nextNodePtr;

public:
   PlaylistNode ();
   PlaylistNode (string id, string sName, string aName, int len);
   PlaylistNode (PlaylistNode *&song);
   
   void           InsertAfter       (PlaylistNode* node);
   void           SetNext           (PlaylistNode* newNext);
   string         GetID             ();
   string         GetSongName       ();
   string         GetArtistName     ();
   int            GetSongLength     ();
   PlaylistNode*  GetNext           ();
   void           PrintPlaylistNode ();
};
