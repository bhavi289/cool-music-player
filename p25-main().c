#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

typedef struct listTopTen{
  int sno;
  char song[100];
  char artist[100];
  char album[100];
  char genre[100];
  int count;
  struct listTopTen * next;
}TOPTEN;

typedef struct allSongs{
  int sno;
  char song[100];
  char artist[100];
  char album[100];
  char genre[100];
  int times;
  struct allSongs* next;
}ALLSONGS;

typedef struct list{
    char A[1000];
    struct list* next;
}LIST;

LIST *head;
ALLSONGS *allSongshead,*allSongslast;

ALLSONGS* createNode1(char[],char[],char[],char[],int,int );
void createList2(char[],int,int);
LIST* createNode2(char[]);
void genSongsDatabase(FILE*);
void editSong(char[],char[]);
void deleteSong(char[],char[],char[],char[]);
void addSong();
void adminAccess();
void show(int);
//------------------------------------------------------------------
void choices(char[]);
void playMusic(int,char[]);
void currentSong(TOPTEN*,int,char[]);
void prevSong(TOPTEN*,int,char[]);
void nextSong(TOPTEN *,int,char[]);
void topTen(int,char[],char[]);
void latest(int,char[],char[]);
int checkinArray(int,int[],int);
void startScreen();
void loginScreen();
void createAccount();
void userFile(char[]);
void makeMenu(char[]);
void loading(char[],int);
void DoProgress(char[],int ,int);
void caselow(char[] ,int);
void search(char[]);
int getch();
void predictions(TOPTEN*,char[]);
TOPTEN *headTopTen,*lastTopTen;



int main(){
  int i;
  startScreen();
}
/*
  Display function displays details of the nodes of the linked list
*/
void display(TOPTEN *p){
  while(p!=NULL){
    printf("%d.) %s, %s \n",p->sno,p->song,p->artist);
    p = p->next;
  }
}


void makeMenu(char ch[]){
  int n,i;
  system("clear");
  //system("cls");
  printf("***************************************************************************************************************************************************************************************\n");
  printf("                                                                              HELLO ");
  for(i=0;i<strlen(ch)-4;i++)
    {
        printf("%c",ch[i]);
    }
  printf("\n***************************************************************************************************************************************************************************************\n");
  system("date");
}



//creates linked list for editSong,deleteSong,show operation
ALLSONGS* createNode1(char song[],char artist[],char album[],char genre[],int sno,int times){
  ALLSONGS *temp;
  temp = (ALLSONGS*)malloc(sizeof(ALLSONGS));
  temp->sno=sno+1;
  strcpy(temp->song,song);
  strcpy(temp->artist,artist);
  strcpy(temp->album,album);
  strcpy(temp->genre,genre);
  temp->times=times;
  temp->next = NULL;
  return temp;
}


//initiating linked list for editSong,deleteSong,show operation
void createList2(char str[],int sno,int counter){

  int l=strlen(str),count=0;int times;
  char song[100],artist[100],album[100],genre[100];
  int i,k=0;
  static int f=0;char temp[10];
  for(i=0;i<l;i++){
    if(str[i]=='^'){
      if(count==0) song[k]='\0';
      else if(count==1) artist[k]='\0';
      else if(count==2) album[k]='\0';
      else if(count==3) genre[k]='\0';
      //else if(count==4) temp[k]='\0';
      k=0;
      count++;
    }
    if(str[i]!='^' && count==0){
      song[k++]=str[i];
    }
    else if(str[i]!='^' && count==1){
      artist[k++]=str[i];
    }
    else if(str[i]!='^' && count==2){
      album[k++]=str[i];
    }
    else if(str[i]!='^' && count==3){
      genre[k++]=str[i];
    }
    else if(str[i]=='#'){
            i+=1;
            while(i<l)
            {
                temp[k++]=str[i];
                i++;
            }
            times=atoi(temp);
    }
  }
  ALLSONGS *p;
  p=createNode1(song,artist,album,genre,sno,times);
  if(counter==0){
    allSongslast=allSongshead=p;
    f++;
  }
  else{
    allSongslast->next=p;
    allSongslast=p;
  }
}

//creates linked list for addSong operation
LIST* createNode2(char ch[]){
    LIST* temp;

    temp=(LIST*)malloc(sizeof(LIST));
    strcpy(temp->A,ch);
    return temp;
}

//initiating linked list for addSong operation
void genSongsDatabase(FILE *fp){

    int i=0;char ch[100];
    LIST *last,*p;

    while(fscanf(fp," %[^\n]s",ch)>=0)
    {
        p=createNode2(ch);
        if(i==0){
            last=head=p;
            i++;
        }
        else{
            last->next=p;
            last=p;
        }
    }
    fclose(fp);
}

void editSong(char editsongname[], char editsongartist[]){
      ALLSONGS *temp;
      temp=allSongshead;int flag=0,want;
      char newname[100],newartist[100],newalbum[100],newgenre[100];

//traversing through linked list and editing the particular node if found
      while(temp!=NULL)
      {
          if ((strcmp(temp->song,editsongname)==0)&&(strcmp(temp->artist,editsongartist)==0))   //for all nodes except last one
          {
                printf("\nDo you want to edit the song name? Type 1 for yes or 0 for no: ");
                scanf("%d",&want);
                if(want==1)
                {
                    printf("\nEnter the New song name: ");
                    scanf(" %[^\n]s",newname);
                    strcpy(temp->song,newname);
                }
                else if(want==0)
                {
                    strcpy(newname,temp->song);
                }
                else if(want!=1 && want!=0)
                {
                    printf("\nYou entered an invalid choice..Redirecting to Main Menu...");
                    exit(0);
                }
                printf("\nDo you want to edit the song's artist name? Type 1 for yes or 0 for no: ");
                scanf("%d",&want);
                if(want==1)
                {
                    printf("\nEnter the New artist name: ");
                    scanf(" %[^\n]s",newartist);
                    strcpy(temp->artist,newartist);
                }
                else if(want==0)
                {
                    strcpy(newartist,temp->artist);
                }
                else if(want!=1 && want!=0)
                {
                    printf("\nYou entered an invalid choice..Redirecting to Main Menu...");
                    exit(0);
                }
                printf("\nDo you want to edit the song's album name? Type 1 for yes or 0 for no: ");
                scanf("%d",&want);
                if(want==1)
                {
                    printf("\nEnter the New album name: ");
                    scanf(" %[^\n]s",newalbum);
                    strcpy(temp->album,newalbum);
                }
                else if(want==0)
                {
                    strcpy(newalbum,temp->album);
                }
                else if(want!=1 && want!=0)
                {
                    printf("\nYou entered an invalid choice..Redirecting to Main Menu...");
                    exit(0);
                }
                printf("\nDo you want to edit the song's genre? Type 1 for yes or 0 for no: ");
                scanf("%d",&want);
                if(want==1)
                {
                    printf("\nEnter the New genre: ");
                    scanf(" %[^\n]s",newgenre);
                    strcpy(temp->genre,newgenre);
                }
                else if(want==0)
                {
                    strcpy(newgenre,temp->genre);
                }
                else if(want!=1 && want!=0)
                {
                    printf("\nYou entered an invalid choice..Redirecting to Main Menu...");
                    exit(0);
                }

                flag=1;
          }
          if(temp!=NULL)
            {
                temp=temp->next;
            }
          else if(flag==1)
            {break;}
          else
            {break;}
      }

          if(flag==1)
            {
                printf("\nSong Successfully edited in database.Redirecting to Main Menu...\n");
            }
          else
            {
                printf("\nSong not found..Try entering the details correctly..Redirecting to Main Menu...\n");
            }

//writing the edited linked list into global.txt file
  FILE *fp2 = fopen("global.txt", "w");
  temp=allSongshead;
    while (temp != NULL) {
    fwrite (temp->song,strlen(temp->song), 1, fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->artist,strlen(temp->artist),1,fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->album,strlen(temp->album),1,fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->genre,strlen(temp->genre),1,fp2);
    fwrite("^ #",strlen("^ #"),1,fp2);
    fprintf(fp2, "%d", temp->times);
    fwrite("\n",strlen("\n"),1,fp2);
    temp = temp->next;
  }
  free(temp);
  fclose(fp2);

//opening admin file and reading each file name and also each file's content and storing that file's content into a linked list
     int i=0;char chh[100];
       FILE *abc=fopen("admin.txt","r");
       fscanf(abc," %[^\n]s",chh);

      while(fscanf(abc," %[^\n]s",chh)>=0){
            int counter=0;
              FILE *fp=fopen(chh,"r");
        char ch1[100];
        char pw1[100];
        fscanf(fp," %[^\n]s",pw1);
        while(fscanf(fp," %[^\n]s",ch1)>=0){
                      createList2(ch1,i,counter);
                      counter++;
                          i++;
                }
        fclose(fp);
        temp=allSongshead;

        //editing the node of linked list
        while(temp!=NULL)
        {
          if ((strcmp(temp->song,editsongname)==0)&&(strcmp(temp->artist,editsongartist)==0))
          {
                strcpy(temp->song,newname);
                strcpy(temp->artist,newartist);
                strcpy(temp->album,newalbum);
                strcpy(temp->genre,newgenre);
                flag=1;
          }
          if(temp!=NULL)
            {
                temp=temp->next;
            }
          else if(flag==1)
            {break;}
          else
            {break;}
      }

     //writing into each file the edited linked list
    FILE *fp2 = fopen(chh, "w");
  fprintf(fp2,"%s\n",pw1);

  temp=allSongshead;
    while (temp != NULL) {
    fwrite (temp->song,strlen(temp->song), 1, fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->artist,strlen(temp->artist),1,fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->album,strlen(temp->album),1,fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->genre,strlen(temp->genre),1,fp2);
    fwrite("^ #",strlen("^ #"),1,fp2);
    fprintf(fp2, "%d", temp->times);
    fwrite("\n",strlen("\n"),1,fp2);
    temp = temp->next;
    }
  fclose(fp2);
  free(temp);
}
}

void deleteSong(char delsongname[], char delsongartist[],char ch[],char pw[]){
      ALLSONGS *temp,*temp2;
      temp=allSongshead;
      int flag=0;

//traversing through linked list and deleting the particular node if found
//for head node
      while(temp->next!=NULL)
      {
          if ((strcmp(temp->song,delsongname)==0)&&(strcmp(temp->artist,delsongartist)==0))
          {
              allSongshead=temp->next;
              free(temp);
              temp=allSongshead;
              flag=1;
          }
          //for normal nodes
          else if ((strcmp(temp->next->song,delsongname)==0)&&(strcmp(temp->next->artist,delsongartist)==0))
          {
                temp->next=temp->next->next;
                flag=1;
          }

        if(temp->next!=NULL)
            {
                temp=temp->next;
            }
        else if(flag==1)
            {break;}
        else{break;}
       }
//for last node
      if (temp->next==NULL)
          {
              if((strcmp(temp->song,delsongname)==0)&&(strcmp(temp->artist,delsongartist)==0))
             {
                free(temp);
                flag=1;
             }
          }
          if(flag==1)
            {
                printf("\nSong Successfully deleted from database.Redirecting to Main Menu...\n");
            }
          else
            {
                printf("\nSong not found..Try entering the details correctly..Redirecting to Main Menu...\n");
            }
 //writing the new linked list into all files
  FILE *fp2 = fopen(ch, "w");
//if file is not global then printing password of user into the file
  if(strcmp(ch,"global.txt")!=0)
  {
    fclose(fp2);
    FILE *fp2 = fopen(ch, "w");
    fprintf(fp2,"%s\n",pw);
  }
  temp=allSongshead;
      while (temp != NULL) {
    fwrite (temp->song,strlen(temp->song), 1, fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->artist,strlen(temp->artist),1,fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->album,strlen(temp->album),1,fp2);
    fwrite("^",strlen("^"),1,fp2);
    fwrite(temp->genre,strlen(temp->genre),1,fp2);
    fwrite("^ #",strlen("^ #"),1,fp2);
    fprintf(fp2, "%d", temp->times);
    fwrite("\n",strlen("\n"),1,fp2);
    temp = temp->next;
    }
  fclose(fp2);
    free(temp);
}

void show(int input){
      ALLSONGS *temp;
      temp=allSongshead;
      int flag=0;

      while(temp!=NULL)
      {
          if (temp->sno==input)
          {
            printf("\nSongname-%s\nArtist-%s\nAlbum-%s\nGenre-%s\n",temp->song,temp->artist,temp->album,temp->genre);
            flag=1;
            break;
          }
          if(temp!=NULL)
            {temp=temp->next;}
}
        if(flag==0)
        {
            printf("\nEnter Serial Number correctly.Redirecting to Main Menu..." );
        }
}

void addSong(){
    char newsong[100],newartist[100],newalbum[100],newgenre[100],songline[100];
//take details of new song and store them into a string
    printf("\nEnter Song Name : ");
    scanf(" %[^\n]s", newsong);
    printf("\nEnter Song Artist : ");
    scanf(" %[^\n]s", newartist);
    printf("\nEnter Song Album : ");
    scanf(" %[^\n]s", newalbum);
    printf("\nEnter Genre : ");
    scanf(" %[^\n]s", newgenre);
    strcpy(songline,newsong);
    strcat(songline,"^");
    strcat(songline,newartist);
    strcat(songline,"^");
    strcat(songline,newalbum);
    strcat(songline,"^");
    strcat(songline,newgenre);
    strcat(songline,"^");
    strcat(songline," #0");
    printf("\nSong successfully Added.Redirecting to Main Menu...\n");

//adding node to linked list
    LIST *new = NULL;
    new = (LIST *)malloc(sizeof(LIST));
    strcpy(new->A,songline);
    new->next = head;
    head=new;

//writing into global.txt file and all user files
    FILE *fp1 = fopen("global.txt", "w");
    while (head != NULL) {
    fwrite (head->A,strlen(head->A), 1, fp1);
    fwrite("\n",strlen("\n"),1,fp1);
    head = head->next;
    }
    fclose(fp1);
    FILE *abc=fopen("admin.txt","r");
    char pw[100];
    fscanf(abc," %[^\n]s",pw);
    char ch[100];
    while(fscanf(abc," %[^\n]s",ch)>=0)
    {
      FILE *fp1=fopen(ch,"a");
      fprintf(fp1,"%s\n",songline);
    }
    fclose(abc);
}

void adminAccess()
{
        int choice,cont =2;
        int counter=0;

        while(cont == 2)
        {
         FILE *fp=fopen("global.txt","r");

         //show menu to the user
         printf("\n****************WELCOME ADMIN***************\n");
         printf("\nSETTINGS: \n");
         printf("\n1. ADD A SONG\n");
         printf("\n2. DELETE A SONG\n");
         printf("\n3. EDIT A SONG\n");
         printf("\n4. DISPLAY ALL SONGS\n");
         printf("\nEnter your choice number: ");
         scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                genSongsDatabase(fp);
                addSong();
                break;
            case 2:
                {
                    int i=0;char delsongname[100],delsongartist[100];char ch[100];
                    ALLSONGS *temp=NULL;
                    counter=0;
                    while(fscanf(fp," %[^\n]s",ch)>=0){
                    //   printf("%s \n",ch);
                        createList2(ch,i,counter);
                        counter++;
                        i++;
                    }
                    fclose(fp);
                    //printf("%s\n",allSongshead->song);
                    temp=allSongshead;
                    printf("S.no Songname Artist  Album  Genre\n");
                    while(temp!=NULL){
                        printf("%d.) %s       %s       %s       %s\n",temp->sno,temp->song,temp->artist,temp->album,temp->genre);
                        temp = temp->next;
                    }
                    printf("\nEnter the Song's Name you want to delete:");
                    scanf(" %[^\n]s", delsongname);
                    printf("Enter the Song's Artist name you want to delete:");
                    scanf(" %[^\n]s", delsongartist);
                    deleteSong(delsongname,delsongartist,"global.txt","none"); //writes into global.txt file

      i=0;
      FILE *abc=fopen("admin.txt","r");
      fscanf(abc," %[^\n]s",ch);
      while(fscanf(abc," %[^\n]s",ch)>=0){
        counter=0;
                      FILE *fp=fopen(ch,"r");
        char ch1[100];
        char pw[100];
        fscanf(fp," %[^\n]s",pw);
        while(fscanf(fp," %[^\n]s",ch1)>=0){
                      createList2(ch1,i,counter);
                      counter++;
                  i++;
                }
        fclose(fp);
        deleteSong(delsongname,delsongartist,ch,pw); //writes into every user file
                      }
      fclose(abc);
                }
                break;
               case 3:
                {
                    int i=0;char editsongname[100],editsongartist[100];char ch[100];
                    ALLSONGS *temp=NULL;
                    counter=0;
//read global.txt for all songs and create a linked list
                    while(fscanf(fp," %[^\n]s",ch)>=0){
                        createList2(ch,i,counter);
                        counter++;
                        i++;
                    }
                    fclose(fp);
                    temp=allSongshead;
                    printf("S.no Songname Artist  Album  Genre\n");
                    while(temp!=NULL){
                        printf("%d.) %s     %s     %s     %s\n",temp->sno,temp->song,temp->artist,temp->album,temp->genre);
                        temp = temp->next;
                    }
//enter songname and song artist to be edited
                    printf("\nEnter the Song's Name you want to edit:");
                    scanf(" %[^\n]s", editsongname);
                    printf("Enter the Song's Artist name you want to edit:");
                    scanf(" %[^\n]s", editsongartist);
                    editSong(editsongname,editsongartist);
               }
                break;

               case 4:
                {
                    int i=0;char ch[100];int input;
                    ALLSONGS *temp=NULL;
                    counter=0;
//read global.txt for a  songs and create a linked list
                    while(fscanf(fp," %[^\n]s",ch)>=0){
                        createList2(ch,i,counter);
                        counter++;
                        i++;
                    }
                    fclose(fp);
                    temp=allSongshead;
//display those songs
                    printf("S.no Songname \n");
                    while(temp!=NULL){
                        printf("%d.) %s\n",temp->sno,temp->song);
                        temp = temp->next;
                    }
                    printf("Enter a serial number of song name to view more about it.Else type 0 to exit: ");
                    scanf("%d",&input);
                    if(input==0)
                    {
                        break;
                    }
                    else
                    {
                       show(input);
                    }

                }
                break;
            default:
                printf("You entered an invalid choice.Redirecting To Main Menu...");
            }
        printf("\n\nWant to exit? Type 1 to EXIT.Type 2 to continue to Main Menu: ");
        scanf("%d", &cont);
    }
}
//-------------------------------------------------------------------------------------------end of member task

int getch() {
    struct termios oldtc, newtc;
    int c;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    c=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return c;
}
/*
  This function is used to increment the count of the song that has been played by the user.
  This function is called to increment the song count in the main file- "global.txt" & all the user files that have been reated 
  whenever a user signs up.
*/

void increment(char sname[], char sartist[], char fname[], int flag){
  FILE *fp=fopen(fname,"r");
  FILE *fp2=fopen("global1.txt","w");
  char str[100];
  if(strcmp(fname,"global.txt")!=0){
    fscanf(fp," %[^\n]s",str);
    fprintf(fp2,"%s\n",str);
  }
  while(fscanf(fp," %[^\n]s",str)>=1){
    char song[100],artist[100],album[100],genre[100],num[100];
    int i,k=0,l=strlen(str),n,j,count=0,m=0;
    int f=0;
    for(i=0;i<l;i++){
      if(str[i]=='^'){
        if(count==0) song[k]='\0';
        else if(count==1) artist[k]='\0';
        else if(count==2) album[k]='\0';
        else if(count==3) genre[k]='\0';
        k=0;
        count++;
      }
      if(str[i]!='^' && count==0){
        song[k++]=str[i];
      }
      else if(str[i]!='^' && count==1){
        artist[k++]=str[i];
      }
      else if(str[i]!='^' && count==2){
        album[k++]=str[i];
      }
      else if(str[i]!='^' && count==3){
        genre[k++]=str[i];
      }
      else if(str[i]=='#'){
        for(j=i+1;j<l;j++){
          num[m++]=str[j];
          num[m]='\0';
          n=atoi(num);
        }
        m=0;
        break;
      }
    }
    if(strcmp(sname,song)==0 && strcmp(sartist,artist)==0){
      char str2[100],temp;
      strcpy(str2,"");
      n++;
      int rev=0;
      m=0;
      while(n!=0){
        num[m++]=(n%10)+48;
        n/=10;
      }
      k=m-1;
      for(i=0;i<=(m-1)/2;i++){
        temp=num[i];
        num[i]=num[k];
        num[k]=temp;
        k--;
      }
      num[m]='\0';
      strcat(str2,song);
      strcat(str2,"^");
      strcat(str2,artist);
      strcat(str2,"^");
      strcat(str2,album);
      strcat(str2,"^");
      strcat(str2,genre);
      strcat(str2,"^");
      strcat(str2," #");
      strcat(str2,num);
      fprintf(fp2,"%s\n",str2);
    }
    else fprintf(fp2,"%s\n",str);
  }
  rename("global1.txt",fname);
  fclose(fp);
  fclose(fp2);
}


void musicBar(){
  fflush(stdin);
  fflush(stdout);
  int i=0,n=0,pos=0,choice=0;
  char percentage='%';
  while(n<=100){
    static char bars[]={'/','-','\\','|'};
    static int nbars=sizeof(bars)/sizeof(char);
    for(i=0;i<n;i++) printf("_");
    for(i=0;i<100-n;i++) printf(".");
    printf("%c %d%c\r",bars[pos],n,percentage);
    pos=(pos+1)%nbars;
    if(pos==0) n+=1;
    if(n!=0) usleep(13000);
  }
  printf("\nDone\n");
}
/*
  Function used to play previous song to current song with help of linked list
*/
void prevSong(TOPTEN* current,int flag,char ch[]){
  TOPTEN *temp=headTopTen;
  while(temp!=NULL){
    if(temp==current){
      printf("NO PREVIOUS SONG\n");
      break;
    }
    if(temp->next==current){
      printf("PLAYING %s, %s\n",temp->song,temp->artist);
      musicBar();
      increment(temp->song,temp->artist,"global.txt",flag);
      increment(temp->song,temp->artist,ch,flag);
      break;
    }
    temp=temp->next;
  }
  printf("Enter 1 for Previous Song, 2 to Repeat Current Song, 3 for next song, 4 for Back, 5 for Main Menu\n");
  int choice;
  scanf("%d",&choice);
  if(choice==1) prevSong(temp,flag,ch);
  else if(choice==2) currentSong(temp,flag,ch);
  else if(choice==3) nextSong(temp,flag,ch);
  else if(choice==4) {
    makeMenu(ch);
    if(flag==1){
      printf("TOPTEN\n");
      topTen(flag,"global.txt",ch);
      display(headTopTen);
      playMusic(1,ch);
    }
    else if(flag==2){
      printf("LATEST\n");
      latest(flag,"global.txt",ch);
    }
    else if(flag==3){
      printf("FAVOURITES\n");
      topTen(flag,ch,ch);
      display(headTopTen);
      playMusic(3,ch);
    }
    else if(flag==4){
      printf("SEARCH....");
      search(ch);
    }
    else if(flag==5){
      makeMenu(ch);
      printf("SUGGESTIONS:-\n");
      topTen(3,ch,ch);
      char genre[20];
      strcpy(genre,headTopTen->genre);
      predictions(headTopTen,genre);
      display(headTopTen);
      playMusic(5,ch);
  
    }
  }
  else if(choice==5){
    makeMenu(ch);
    choices(ch);
  }
}
/*
  Function used to play song with serial number of the list shown
*/
void currentSong(TOPTEN* current,int flag, char ch[]){
  TOPTEN *temp=headTopTen;

  while(temp!=NULL){
    if(temp==current){
      printf("PLAYING %s, %s\n",temp->song,temp->artist);
      musicBar(ch);
      increment(temp->song,temp->artist,"global.txt",flag);
      increment(temp->song,temp->artist,ch,flag);
      break;
    }
    temp=temp->next;
  }
  printf("Enter 1 for Previous Song, 2 to Repeat Current Song, 3 for next song, 4 for Back, 5 for Main Menu\n");
  int choice;
  scanf("%d",&choice);
  if(choice==1) prevSong(temp,flag,ch);
  else if(choice==2) currentSong(temp,flag,ch);
  else if(choice==3) nextSong(temp,flag,ch);
  else if(choice==4) {
    makeMenu(ch);
    if(flag==1){
      printf("TOPTEN\n");
      topTen(flag,"global.txt",ch);
      display(headTopTen);
      playMusic(1,ch);
    }
    else if(flag==2){
      printf("LATEST\n");
      latest(flag,"global.txt",ch);
    }
    else if(flag==3){
      printf("FAVOURITES\n");
      topTen(flag,ch,ch);
      display(headTopTen);
      playMusic(3,ch);
    }
    else if(flag==4){
      printf("SEARCH....");
      search(ch);
    }
    else if(flag==5){
      makeMenu(ch);
      printf("SUGGESTIONS:-\n");
      topTen(3,ch,ch);
      char genre[20];
      strcpy(genre,headTopTen->genre);
      predictions(headTopTen,genre);
      display(headTopTen);
      playMusic(5,ch);
  
    }
  }
  else if(choice==5){
    makeMenu(ch);
    choices(ch);
  }
}
/*
  Function is used to play next song to the current song .
*/
void nextSong(TOPTEN *current,int flag,char ch[]){
  TOPTEN *temp=headTopTen;
  while(temp!=NULL){
    if(temp==current){
      if(temp->next==NULL){
        printf("LAST SONG\n");
        break;
      }
      printf("PLAYING %s, %s\n",temp->next->song,temp->next->artist);
      musicBar();
      increment(temp->next->song,temp->next->artist,ch,flag);
      increment(temp->next->song,temp->next->artist,"global.txt",flag);
      break;
    }
    temp=temp->next;
  }
  printf("Enter 1 for Previous Song, 2 to Repeat Current Song, 3 for next song, 4 for Back, 5 for Main Menu\n");
  int choice;
  scanf("%d",&choice);
  if(choice==1) prevSong(temp->next,flag,ch);
  else if(choice==2) currentSong(temp->next,flag,ch);
  else if(choice==3) nextSong(temp->next,flag,ch);
  else if(choice==4) {
    makeMenu(ch);
    if(flag==1){
      printf("TOPTEN\n");
      topTen(flag,"global.txt",ch);
      display(headTopTen);
      playMusic(1,ch);
    }
    else if(flag==2){
      printf("LATEST\n");
      latest(flag,"global.txt",ch);
    }
    else if(flag==3){
      printf("FAVOURITES\n");
      topTen(flag,ch,ch);
      display(headTopTen);
      playMusic(3,ch);
    }
    else if(flag==4){
      printf("SEARCH....");
      search(ch);
    }
    else if(flag==5){
      makeMenu(ch);
      printf("SUGGESTIONS:-\n");
      topTen(3,ch,ch);
      char genre[20];
      strcpy(genre,headTopTen->genre);
      predictions(headTopTen,genre);
      display(headTopTen);
      playMusic(5,ch);
  
    }
  }
  else if(choice==5){
    makeMenu(ch);
    choices(ch);
  }
}
/*
  Function prompts user to give input to play song number and then calls currentSong() to play it.
*/
void playMusic(int flag,char ch[]){
  TOPTEN *temp=headTopTen;
  int n;
  char c[2];
  printf("\nPRESS SERIAL NUMBER OF SONG TO PLAY\t\tPRESS 'b' TO RETURN TO MAIN MENU.\n");
  scanf("%s",c);
  if(strcmp(c,"b")==0)
  {
    makeMenu(ch);
    choices(ch);
  }
  else
  {
    n=atoi(c);
  }
  while(temp!=NULL){
    if(temp->sno==n){
      currentSong(temp,flag,ch);
      break;
    }
    temp=temp->next;
  }
  printf("Enter 1 for Previous Song, 2 to Repeat Current Song, 3 for next song, 4 for Back, 5 for Main Menu\n");
  int choice;
  scanf("%d",&choice);
  if(choice==1) prevSong(temp,flag,ch);
  else if(choice==2) currentSong(temp,flag,ch);
  else if(choice==3) nextSong(temp,flag,ch);
  else if(choice==4) {
    makeMenu(ch);
    if(flag==1){
      printf("TOPTEN\n");
      topTen(flag,"global.txt",ch);
      display(headTopTen);
      playMusic(1,ch);
    }
    else if(flag==2){
      printf("LATEST\n");
      latest(flag,"global.txt",ch);
    }
    else if(flag==3){
      printf("FAVOURITES\n");
      topTen(flag,ch,ch);
      display(headTopTen);
      playMusic(3,ch);
    }
    else if(flag==4){
      printf("SEARCH....");
      search(ch);
    }
  }
  else if(choice==5){
    makeMenu(ch);
    choices(ch);
  }
}


/*
  Function returns created node, with all specified parameter.
*/
TOPTEN* createNode(char song[],char artist[],char album[],char genre[],int sno,int n){
  TOPTEN *temp;
  temp = (TOPTEN*)malloc(sizeof(TOPTEN));
  temp->sno=sno+1;
  strcpy(temp->song,song);
  strcpy(temp->artist,artist);
  strcpy(temp->album,album);
  strcpy(temp->genre,genre);
  temp->count=n;
  temp->next = NULL;
  return temp;
}
/*
  Function used to create linked list out of file contents.
  First, it seperates the song, artist, album, genre, and count from a line from the file.
  Then it proceeds to add the data in a linked list
*/
void createList(char str[],int sno){
  int l=strlen(str),count=0;
  char song[100],artist[100],album[100],genre[100],num[100];
  int i,k=0,j,n=0,m=0;
  for(i=0;i<l;i++){
    if(str[i]=='^'){
      if(count==0) song[k]='\0';
      else if(count==1) artist[k]='\0';
      else if(count==2) album[k]='\0';
      else if(count==3) genre[k]='\0';
      k=0;
      count++;
    }
    if(str[i]!='^' && count==0){
      song[k++]=str[i];
    }
    else if(str[i]!='^' && count==1){
      artist[k++]=str[i];
    }
    else if(str[i]!='^' && count==2){
      album[k++]=str[i];
    }
    else if(str[i]!='^' && count==3){
      genre[k++]=str[i];
    }
    else if(str[i]=='#'){
      for(j=i+1;j<l;j++){
          num[m++]=str[j];
        }
        num[m]='\0';
        n=atoi(num);
        m=0;
        break;
    }
  }
  TOPTEN *p;
  p=createNode(song,artist,album,genre,sno,n);
  if(sno==0){
    lastTopTen=headTopTen=p;
  }
  else{
    lastTopTen->next=p;
    lastTopTen=p;
  }
}
/*
  Function to check repetitions in array. It is required as 2 songs having same count can possibly return inaccurate values.
*/
int checkinArray(int ln,int prevPos[],int q){
  for(int i=0;i<q;i++){
    if(prevPos[i]==ln)
      return 1;
  }
  return 0;
}
/*
  Picks up the first 15 strings from file and cretes a linked list.
  (In file new songs are added at the top)
*/
void latest(int flag,char fname[],char ch[]){
  FILE *fp=fopen(fname,"r");
  char str[100];
  int i=0,j=0;
  while(fscanf(fp," %[^\n]s",str)>=0){
    if(i==15) break;
    int l=strlen(str);
    int x=0;
    createList(str,i);
    printf("%d.) ",i+1);
    for(j=0;j<l;j++){
      if(str[j]=='^' && x==1){
        printf("\n");
        break;
      }
      if(str[j]!='^') printf("%c",str[j]);
      else{
        printf(", ");
        x=1;
      }
    }
    i++;
  }
  playMusic(flag,ch);
}
/*
  Searches for the most played songs by all the users and hence prints the topTen songs based on the data.
*/
void topTen(int flag,char fname[],char ch[]){
  int i,j=0,k,max2=9999,prevPos[1000],q=0;
  for(i=0;i<10;i++){
    char str[1000],st[1000];
    FILE *fp=fopen(fname,"r");
    int max=0;
    int n,ln=0,m=0,pos;
    if(flag==3) fscanf(fp," %[^\n]s",str);
    while(fscanf(fp," %[^\n]s",str)>=0){
      int l=strlen(str);
      m=0;
      char num[1000];
      for(j=0;j<l;j++){
        if(str[j]=='#'){
          for(k=j+1;k<l;k++)
            num[m++]=str[k];
          num[m]='\0';
          n=atoi(num);
          break;
        }
      }
      if(n>max && n<=max2 && checkinArray(ln,prevPos,q)==0){
        max=n;

        pos=ln;
      }
      ln++;
    }
    //printf("max:%d\n",max);
    if(max==0 && i==0)
    {
      printf("You have not played anything in your library yet..\n");
      //system("clear");
      printf("Enter 1 to Log in from another account, 2 to return to the main screen\n");
      int z;
      scanf("%d",&z);
      if(z==1) loginScreen(ch);
      if (z==2) choices(ch);
      else
      break;
    }
    if(max==0) break;
    prevPos[q++]=pos;
    max2=max;
    ln=0;
    FILE *fp2=fopen(fname,"r");

    if(flag==3) fscanf(fp2," %[^\n]s",str);
    while(fscanf(fp2," %[^\n]s",str)>=0){
      int l=strlen(str);
      int x=0;
      if(ln==pos){
        createList(str,i);
        //printf("%d.) ",i+1);
        for(j=0;j<l;j++){
          if(str[j]=='^' && x==1){
            //printf("\n");
            break;
          }
          //if(str[j]!='^') printf("%c",str[j]);
          else{
            //printf(", ");
            x=1;
          }
        }
        break;
      }
      ln++;
    }
    fclose(fp);
    fclose(fp2);
  }
}
/*
  This functions gives the predictions to what the user might like to hear based on his/her genre intersts.
  eg. if a user tends to listen to 'pop' music more, his predictions will have pop music songs.
*/
void predictions(TOPTEN* headTopTen, char genre[]){
  FILE *fp=fopen("global.txt","r");
  char str[100];
  int f=0;
  while(fscanf(fp," %[^\n]s",str)>=0){
    int l=strlen(str),count=0;
    char song[100],artist[100],album[100],genre2[100],num[100];
    int i,k=0,j,n=0,m=0;
    for(i=0;i<l;i++){
      if(str[i]=='^'){
        if(count==0) song[k]='\0';
        else if(count==1) artist[k]='\0';
        else if(count==2) album[k]='\0';
        else if(count==3) genre2[k]='\0';
        k=0;
        count++;
      }
      if(str[i]!='^' && count==0){
        song[k++]=str[i];
      }
      else if(str[i]!='^' && count==1){
        artist[k++]=str[i];
      }
      else if(str[i]!='^' && count==2){
        album[k++]=str[i];
      }
      else if(str[i]!='^' && count==3){
        genre2[k++]=str[i];
      }
      else if(str[i]=='#'){
        for(j=i+1;j<l;j++){
            num[m++]=str[j];
          }
          num[m]='\0';
          n=atoi(num);
          m=0;
          break;
      }
    }
    if(strcmp(genre,genre2)==0){
      //printf("%s %s\n",song,artist);
      createList(str,f);
      f++;
    }
  }
}
/*
  This is the Main Menu function where the user is given choices to display and play the music from the various lists offered by our music player.
*/
void choices(char ch[]){
  int n;
  system("clear");
  makeMenu(ch);
  printf("Press 1 for TOP TEN \t\t Press 2 for LATEST \t\t Press 3 for your Personalisied Library\t\t Press 4 to search\t\t Press 5 for suggestions\n");
  scanf("%d",&n);
  int flag;
  switch(n){
    case(1):
      makeMenu(ch);
      printf("\nTOP TEN OF THE WEEK :\n\n");
      topTen(1,"global.txt",ch);
      display(headTopTen);
      playMusic(1,ch);
      break;
    case(2):
      makeMenu(ch);
      printf("LATEST SONGS:-\n");
      latest(2,"global.txt",ch);
      break;
    case(3):
      makeMenu(ch);
      printf("FAVOURITES:-\n");
      topTen(3,ch,ch);
      display(headTopTen);
      playMusic(3,ch);
      break;
    case(4):
      makeMenu(ch);
      printf("SEARCH:-\n");
      search(ch);
      break;
    case(5):
      makeMenu(ch);
      printf("SUGGESTIONS:-\n");
      topTen(3,ch,ch);
      char genre[20];
      strcpy(genre,headTopTen->genre);
      predictions(headTopTen,genre);
      display(headTopTen);
      playMusic(5,ch);
  }
}


void userFile(char ch[])
{
    FILE *fp=fopen(ch,"a");
    FILE *G=fopen("global.txt","r");
    choices(ch);

}

void addToUser(char ch[]){
  FILE *fp=fopen("global.txt","r");
  FILE *fp2=fopen(ch,"a+");
  char str[100];
  while(fscanf(fp," %[^\n]s",str)>=0){
    int l=strlen(str),count=0;
    char song[100],artist[100],album[100],genre2[100],num[100];
    int i,k=0,j,n=0,m=0;
    for(i=0;i<l;i++){
      if(str[i]=='^'){
        if(count==0) song[k]='\0';
        else if(count==1) artist[k]='\0';
        else if(count==2) album[k]='\0';
        else if(count==3) genre2[k]='\0';
        k=0;
        count++;
      }
      if(str[i]!='^' && count==0){
        song[k++]=str[i];
      }
      else if(str[i]!='^' && count==1){
        artist[k++]=str[i];
      }
      else if(str[i]!='^' && count==2){
        album[k++]=str[i];
      }
      else if(str[i]!='^' && count==3){
        genre2[k++]=str[i];
      }
      else if(str[i]=='#'){
        for(j=i+1;j<l;j++){
            num[m++]=str[j];
          }
          num[m]='\0';
          n=atoi(num);
          m=0;
          break;
      }
    }

    if(n==1) fprintf(fp2,"%s",str);
    if(n!=1) break;
  }
  fclose(fp);
  fclose(fp2);
}

void loginScreen()
{
  char pws[100],pwe[100],ch[100];
  int i=0;
  char c=' ';
  printf("Enter Username\n");
  scanf("%s",ch);
  strcat(ch,".txt");
  FILE *fp=fopen(ch,"r");
  printf("Enter password\n");
  getchar();
      while(i<=100) {
          c = getch();
    pwe[i]=c;
          if(c=='\n')
          {
                break;
          }
          else
          {
                printf("*");
          }
  i++;
    }
    pwe[i]='\0';
  fscanf(fp,"%s",pws);
  i=0;
  for(i=0;i<strlen(pws);i++)
  {
    if(i%2==0)
    {
      pws[i]=pws[i]-3;
    }
    else
    {
      pws[i]=pws[i]+3;
    }
  }
  if(strcmp(pws,pwe)==0)
  {
      system("clear");
      loading("Logging In..",1000);
    if(strcmp(ch,"admin.txt")!=0)
    {
      printf("\nYou are logged in\n");
      addToUser(ch);
      //fclose(fp);
      system("clear");
      userFile(ch);
    }
    else
    {
      adminAccess();
    }
  }
  else
      {
    char o;
  //        SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED );
    printf("\nIncorrect Username or Password combination\nTry Again(y/n)");
    fflush(stdin);
  //        SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), 0x08 );
    scanf("%c",&o);
    if(o=='y'||o=='Y')
    {
        system("clear");
        loginScreen();
    }
    else if(o=='n'||o=='N')
    {
        system("clear");
        startScreen();
    }

      }
}
void writeinFile(char ch[])
{
  FILE *fp=fopen("global.txt","r");
  FILE *fp2=fopen(ch,"a");
  char ch1[100];
  fprintf(fp2, "\n");
  //printf("hello\n");
  while(fscanf(fp," %[^\n]s",ch1)>=0)
  {
   // printf("%s\n",ch1);
    int i=0;
    char str[100];
    while(ch1[i]!='#')
    {
      str[i]=ch1[i];
      i++;
    }
    str[i]='\0';
    strcat(str,"#0");
    //printf("%s\n",str );
    fprintf(fp2,"%s\n",str);
  }
  fclose(fp2);

}
void writeinAdmin(char ch[])
{
  FILE *fp=fopen("admin.txt","a");
  fprintf(fp,"%s\n",ch);
  fclose(fp);
}
void createAccount(){
  char ch[100],pw[100];
  char c=' ';
  int i=0;;
  printf("Enter your unique username\n");
  scanf("%s",ch);
  strcat(ch,".txt");
  FILE *fp=fopen(ch,"a");
  printf("Enter your password\n");
  getchar();
      while(i<=100) {
          c = getch();
    pw[i]=c;
          if(c=='\n')
          {
                break;
          }
          else
          {
                printf("*");
          }
  i++;
   }
   pw[i]='\0';
    loading("Creating",1000);
    for(i=0;i<strlen(pw);i++)
    {
      if(i%2==0)
      {
      fprintf(fp, "%c", pw[i]+3);
    }
    else
    {
      fprintf(fp, "%c", pw[i]-3);
    }
  }
  //printf("hi\n");
  fclose(fp);
  writeinFile(ch);
  writeinAdmin(ch);
  printf("\nAccount successfully created!\nPress 1 to go back to main screen and 2 to log in.");
  scanf("%d",&i);
  if(i==1)
    {
        startScreen();
    }
    else if(i==2)
    {
        loginScreen();
    }
    else
    {
        printf("\nInvalid input\n");
    }
}

void loading(char ch[],int speed){
  fflush(stdin);
  fflush(stdout);
  int i=0,n=0,pos=0,choice=0;
  char percentage='%';
  while(n<=100){
    static char bars[]={'/','-','\\','|'};
    static int nbars=sizeof(bars)/sizeof(char);
    printf("%s   ",ch);
    for(i=0;i<n;i++) printf("#");
    for(i=0;i<100-n;i++) printf(".");
    printf("%c %d%c\r",bars[pos],n,percentage);
    pos=(pos+1)%nbars;
    if(pos==0) n+=1;
    if(n!=0) usleep(13000);
  }
  printf("\nDone\n");
}


void startScreen(){
  //makeMenu();
  //choices();
  //display(headTopTen);
  int i;
  printf("Press 1 to create a new account\n");
  printf("Press 2 to log in\n");
  printf("Press 3 to exit\n");
  scanf("%d",&i);
  if(i==1)
  {
    system("clear");
    createAccount();
  }
  else if(i==2)
  {
    system("clear");
    loginScreen();
  }
  else if(i==3)
    {
        exit(0);
    }
  else
    {
        printf("\nInvalid input\n");
    }
}

//This is to change all the uppercase in a string to lowercase 
void caselow(char str[100],int l){
    int i;
    for(i=0;i<l;i++){
        if(str[i]>='A'&&str[i]<='Z'){
            str[i]+='a'-'A';
        }
    }
}
//This function is to search for anything present in the song database. 
void search(char usr[100]){
    char buff[1000000],user[1000],bufr[1000000],ch='y',ser[100];
    int flag1=1,key=0,count;

    //The below loop is keep prompting search until he user wants to.
    while(ch=='y'){
      system("clear");
      strcpy(user,usr);
      user[strlen(user)-4]=0;
      printf("----------------------------------------Welcome %s------------------------------------------\n\n\n",user);
      
      //The key is to know the refine criteria which you selected
      switch(key){
        case 1:printf("         Search refined to song\n");break;
        case 2:printf("         Search refined to artist\n");break;
        case 3:printf("         Search refined to album\n");break;
        case 4:printf("         Search refined to genre\n");break;
      }

      //flag1 is to know if you have any refinements
      if(flag1==1){
        printf("Search for:");
        fflush(stdin);

        scanf(" %[^\n]s",ser);
      }
      else{
        printf("Searched For:%s\n",ser);
      }
      flag1=1;
      int l=strlen(ser),flag=0,i,j,k,count=0;
      caselow(ser,l);
      FILE *fp;
      fp = fopen("global.txt", "r");

      //One by one lines are taken as input
      while(fgets(buff, 1000, fp)) {
        k=0;
        if(key!=0){
          for(i=0;k<key-1;i++){
              if(buff[i]=='^')k++;
          }
          for(k=0;buff[i]!='^';i++){
            bufr[k]=buff[i];
            k++;
          }
          bufr[k]=0;
        }
        else strcpy(bufr,buff);
        for(i=0;i<=strlen(bufr)-l&&strlen(bufr)>=l;i++){
          flag=0;
          for(j=0;j<l;j++){
              if(ser[j]!=bufr[i+j])flag=1;
          }
          k=i;
          if(flag==0 &&(i==0 || buff[i-1]==' '|| buff[i-1]=='^' || buff[i-1]=='\(' )){
            while(k!=-1)k--;
            k++;
            printf("%d.)",count+1);

            //The songs matched are sen to be in a linked list
            createList(buff,count);
            count++;
            //Printing the songs
            printf("SONG: ");
            while(buff[k]!='^'){
              if(k==0||buff[k-1]==' ')printf("%c",buff[k]-'a'+'A');
              else printf("%c",buff[k]);
              k++;
            }
            printf("\n   ARTIST: ");
            i+=l;
            k++;
            while(buff[k]!='^'){
              if((buff[k-1]==' '||buff[k-1]=='^'||buff[k-1]=='.')&&(buff[k]>='a'&&buff[k]<='z'))printf("%c",buff[k]-'a'+'A');
              else printf("%c",buff[k]);
              k++;
            }
            printf(" ALBUM: ");
            k++;
            while(buff[k]!='^'){
              if((buff[k-1]==' '||buff[k-1]=='^'||buff[k-1]=='.')&&(buff[k]>='a'&&buff[k]<='z'))printf("%c",buff[k]-'a'+'A');
              else printf("%c",buff[k]);
              k++;
            }
            printf(" GENRE: ");
            k++;
            while(buff[k]!='^'){
              if((buff[k-1]==' '||buff[k-1]=='^'||buff[k-1]=='.')&&(buff[k]>='a'&&buff[k]<='z'))printf("%c",buff[k]-'a'+'A');
              else printf("%c",buff[k]);
              k++;
            }
            printf("\n");
            break;
        }
      }
}
   fclose(fp);
   if(count!=0){
    fflush(stdin);
    printf("Do you want to refine your search\n\nEnter \n1 to search by song name\n2 to search by artist\n3 to search by album\n4 to search by genre\n5 to remove any constraints\n0 to exit refine\nYour option:");
    scanf(" %d",&key);
    if(key!=0){
     flag1=0;
      if(key>=5)key=0;
      count=0;
      continue;
     }
    }
    else {
    printf("Your search returned no results\n");
    key=0;
    }
   printf("\n\nWant to search again\nEnter y to search again:");
   fflush(stdin);
   getch();
   scanf("%c",&ch);
   fflush(stdin);
  }
 if(count!=0) playMusic(4,usr);
 else {
  makeMenu(usr);
  choices(usr);
 }
}


