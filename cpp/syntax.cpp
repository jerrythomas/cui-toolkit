class Indicator
 {
   private :
     char *StartIndicator;
     char *EndIndicator;

   public :
      Indicator();
     ~Indicator();

     void SetIndicator(char *Start, char *End);
     bool IsStart(char *CheckIt,bool IgnoreCase)
     bool IsEnd(char *CheckIt,bool IgnoreCase);
 };

Indicator::Indicator()
 {
   StartIndicator = (char*)NULL;
   EndIndicator   = (char*)NULL;
 }

Indicator::~Indicator()
 {
   if (StartIndicator != (char*)NULL)
      delete StartIndicator;
   if (EndIndicator   != (char*)NULL)
      delete EndIndicator;
   StartIndicator = (char*)NULL;
   EndIndicator   = (char*)NULL;
 }

void Indicator::SetIndicator(char *Start, char *End)
 {
   if (StartIndicator != (char*)NULL)
      delete StartIndicator;
   if (EndIndicator   != (char*)NULL)
      delete EndIndicator;
   StartIndicator = (char*)NULL;
   EndIndicator   = (char*)NULL;

   if (*Start != '\0')
    {
      StartIndicator = new char[strlen(Start)+1];
      strcpy(StartIndicator,Start);
    }
   if (*End != '\0')
    {
      EndIndicator = new char[strlen(End)+1];
      strcpy(EndIndicator,End);
    }
 }
bool Indicator::IsStart(char *CheckIt,bool IgnoreCase)
 {
   if (IgnoreCase)
      return (bool)(!strcmpi(StartIndicator,CheckIt));
   else
      return (bool)(!strcmp(StartIndicator,CheckIt));
 }
bool Indicator::IsEnd(char *CheckIt,bool IgnoreCase)
 {
   if (IgnoreCase)
      return (bool)(!strcmpi(EndIndicator,CheckIt));
   else
      return (bool)(!strcmp(EndIndicator,CheckIt));
 }



struct Comment
 {
   int  SingleCol;              // Column position for single line comment
   char *Single;                // Single line comment indicator
   char *CommentStart;          // Multiline comment start
   char *CommentEnd;            // Multiline comment end
 };

class Syntax
 {
   private :

     bool IgnoreCase;           // Ignore case while checking for syntax
     char *InitKeyWordChars;    // Characters that start a keyword
     char *KeyWordChars         // Character allowed in keywords

     char *SinglePreprocStart   // Single line Preprocessor directive start
     char *PreprocStart         // Multi Line Preproc directive start
     char *PreprocEnd           // Multi Line Preproc directive start

     char *SyntaxStart          // Special character starting syntax
     char *SyntaxEnd            // Special character starting syntax

     Indicator Comment;         // Default comment
     Indicator CommentAlt;             // Alternative comment

     char *StringStart          //
     char *StringEnd            //
     char *StringAlt            //
     char *StringEsc            //

     char *CharStart            //
     char *CharEnd              //
     char *CharEsc              //

     char **KeyWords;
     char **KeyWords




 };