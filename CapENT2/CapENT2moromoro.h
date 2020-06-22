#define CAME 0
#define INTE 1
#define DSIZ 2
#define CSIZ 3
#define FPSN 4
#define WRID 5
#define WRCA 6
#define LOOP 7
#define LATE 8
#define SLEE 9
#define REF0 10
#define REF1 11
#define REF2 12
#define REF3 13
#define REF4 14
#define REF5 15
#define REF6 16
#define REF7 17
#define REF8 18
#define REF9 19
#define HOZN 20
#define BKUP 21
#define HIST 22
#define PARA 23
#define CONF_FN "CapENT2config.ini"
#define DATA_FN "CapENT2data.txt"

#ifdef CapENT2_TOP
int CapENTmode;//0:preview 1:capture 2:play
char Sxyz[10];
int params[20];
DWORD grayRGB;
char CurDir[301];
char ptxt[30][200];
char CurPics[10001][200];
int allCnt;
int idCnt;
int dayCnt;
int PicsOffset;
int CurPicTop;
char CurPics4[6][50];//0-3 4:“ü‚ê‘Ö‚¦‚Ì‚Æ‚«‚Ìƒ[ƒNƒf[ƒ^@5:
char CurPicL[50];
int PicPos[30][4];
int Gwinw,Gwinh;//‰f‘œWindow‚Ì‰¡c•
int Gwinx,Gwiny;//‰f‘œWindow‚Ì¶ã
int slidex,slidey,sliderf;
int picsflag;
int slidew;
int slideh;
int Winw,Winh;//Window‚Ì‰¡c•
char lastrecfn[301];
char playingfn[301];
char trimingfn[301];

#else
extern int CapENTmode;//0:preview 1:capture 2:play
extern char Sxyz[10];
extern int params[20];
extern DWORD grayRGB;
extern char CurDir[301];
extern char ptxt[30][200];
extern char CurPics[10001][200];
extern int allCnt;
extern int idCnt;
extern int dayCnt;
extern int PicsOffset;
extern int CurPicTop;
extern char CurPics4[6][50];
extern char CurPicL[50];
extern int PicPos[30][4];
extern int Gwinw,Gwinh;//‰f‘œWindow‚Ì‰¡c•
extern int Gwinx,Gwiny;//‰f‘œWindow‚Ì¶ã
extern int slidex,slidey,sliderf;
extern int slidew;//slider‚Ì•
extern int slideh;//slider‚Ìc•
extern int Winw,Winh;//Window‚Ì‰¡c•
extern char lastrecfn[301];
extern char playingfn[301];
extern char trimingfn[301];

#endif
int Ymd_make(CStdioFile *fn, char *DirName, char *ymd);
bool strstr_match(char *str1, char *str2);
bool IsFile(char *fn);
bool Checkarcom(int n);
int GetarcomsDTR_N();
void Directory(char *path,char *found[]);
void SetEN(char *s1,char *s2,int mode);//mode0:\‚Ü‚Å@mode:1 2017--
void Setfn2iddate(char *fn,char *iddate);
void Waku(CDC *pDC,int x,int y,int x1,int y1);
void Addfn2listavi(CListCtrl *list,char *fn);
void FolderTree2list(CString inPath,CListCtrl *list,char *kensaku);
void Setlistavi2listcur(CListCtrl* all,CListCtrl* cur,int id);
void f2gomi(char *gomi);
bool checkavifn(char *fn);
void LoadCon();
//void LoadConCsize();
void SaveCon();
int Para0(int para);
int Para1(int para);
//void Disp_ken(Mat img,float q0,float q1,float q2,float q3,int sisei);
int checkslider(int x,int y);
void GetQuartanion(int f,float *q0,float *q1,float *q2,float *q3);
void GetSXYZ(char *sxyz,int s);
int GetSXYZn(char *sxyz);
void SetPlayCapfn(char *playcapfn,char *playingfn,int currentframe);
void Picsflag2fn(char *fn,int pn);
bool CheckPicsflagfn(int pn);
void Putfn2Datafile(char *fname);
void Del21xx_Datafile();
bool picsflagnull(int fnn);//""‚È‚çtrue‚Å‚à‚Ç‚éBgazou‚ğw‚µ‚Ä‚¢‚È‚¯‚ê‚Îfalse
bool check_jpgwmv(char *fn);