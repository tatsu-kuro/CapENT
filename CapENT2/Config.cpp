#include "stdafx.h"
#include "CapENT2.h"
#include "CapENT2Dlg.h"
#include "CapENT2moromoro.h"

static char *ptext[]={
				"Camera Number:",
				"Interlace Filter:",
				"Video Display size(x,y):",
				"(*)Video Capture size(x,y):",
				"(*)Video Capture FPS:",
				"(*)write ID on-off:",
				"(*)write date on-off:",
				"(*)USBIO_loop:",
				"(*)USBIO_latency:",//�X�C�b�`���ω�����Enter�𑗂�܂ł̎���
				"(*)USBIO_sleep:",//���̃X�C�b�`���`�F�b�N����܂ł̋x�ݎ���
				"ref0 text:",
				"ref1 text:",
				"ref2 text:",
				"ref3 text:",
				"ref4 text:",
				"ref5 text:",
				"ref6 text:",
				"ref7 text:",
				"ref8 text:",
				"ref9 text:",
				"HozonFolder:",
				"BackupFolder:",
				"ID history:"
				};

static char *ptextdef[]={
				"0",
				"0",
				"640,480",
				"640,480",
				"30",
				"1",
				"1",
				"10",
				"20",
				"500",
#ifdef English
				"ref0_no_setumei",
				"ref1_no_setumei",
				"ref2_no_setumei",
				"ref3_no_setumei",
				"ref4_no_setumei",
				"ref5_no_setumei",
				"ref6_no_setumei",
				"ref7_no_setumei",
				"ref8_no_setumei",
				"ref9_no_setumei",
#else
				"���F����",
				"������",
				"�����̑�",
				"�A���F����",
				"�A��",
				"�����A���o�A��F����",
				"����",
				"���o�A��",
				"���̑�",
				"���̑��Q",
#endif
				"",
				"",
				"00000111,00000222,00000333,00000444,00000555,00000666,00000777,00000888,00000999,00001000"
				};
void LoadCon()
{
	int i;
	char buf[500];
	CStdioFile ff;
	if(!ff.Open(CONF_FN,CFile::modeRead|CFile::typeText))
	{
		ff.Open(CONF_FN,CFile::modeCreate|CFile::modeWrite|CFile::modeRead|CFile::typeText);
		for(i=0;i<PARA;i++){
			sprintf_s(buf,"%s%s\n",ptext[i],ptextdef[i]);
			ff.WriteString(buf);
//			strcpy_s(b,buf);
		}
		ff.Abort();
		for(i=0;i<PARA;i++){
			strcpy_s(ptxt[i],ptextdef[i]);
		}
	}else{
		bool txtf[PARA+1];
		for(i=0;i<PARA;i++)txtf[i]=false;
		while(ff.ReadString(buf,395)){
			for(i=0;i<PARA;i++){
				if(strstr(buf,ptext[i])&&buf[0]==ptext[i][0]){
					strcpy_s(ptxt[i],&buf[strlen(ptext[i])]);
					ptxt[i][strlen(ptxt[i])-1]=0;
					txtf[i]=true;
				}
			}
		}
		ff.Abort();

		for(i=0;i<PARA;i++){
			if(!txtf[i]){
				strcpy_s(ptxt[i],ptextdef[i]);
			}
		}
	}
	if(strlen(ptxt[CSIZ])<5||strlen(ptxt[CSIZ])>9)
	{
		sprintf_s(buf,"LoadCon %s is destroyed.\ndelete the %s and run CapNYS2.exe.",CONF_FN,CONF_FN);
		AfxMessageBox(buf);//"CapNYS.ini is destroyed.\n delete the CapNYS.ini and run CapNYS.exe.");
		exit(0);
	}

}
/*
void LoadConCsize()
{
//	int i;
	char buf[500];
	CStdioFile ff;
	if (ff.Open(CONF_FN, CFile::modeRead | CFile::typeText))
	{
		while (ff.ReadString(buf, 395)) {
			if (strstr(buf, ptext[CSIZ])) {// && buf[0] == ptext[i][0]) {
				strcpy_s(ptxt[CSIZ], &buf[strlen(ptext[CSIZ])]);
				ptxt[CSIZ][strlen(ptxt[CSIZ]) - 1] = 0;
				break;
			}
		}
		ff.Abort();
	}
}*/
void SaveCon()
{
	CStdioFile ff;
	char buf[300];
	int i;	
	ff.Open(CONF_FN,CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
	for(i=0;i<PARA;i++){//writeini
		sprintf_s(buf,"%s%s\n",ptext[i],ptxt[i]);
		ff.WriteString(buf);
	}
	ff.Abort();
	if (strlen(ptxt[CSIZ]) < 5 || strlen(ptxt[CSIZ]) > 9)
	{
		sprintf_s(buf,"SaveCon %s is destroyed.\ndelete the %s and run CapNYS2.exe.",CONF_FN,CONF_FN);
		AfxMessageBox(buf);//"CapNYS.ini is destroyed.\n delete the CapNYS.ini and run CapNYS.exe.");
	}
}
int Para0(int para)
{
	char *p;
	int i,j;
	if(p=strstr(ptxt[para],",")){
		if(strstr(p+1,",")){//,��2��������߂�
			return -1;
		}else{//,��1�̂Ƃ�
			sscanf_s(ptxt[para],"%d,%d",&i,&j);
			return i;
		}
	}else{//,���Ȃ��Ƃ�
		sscanf_s(ptxt[para],"%d",&i);
		return i;
	}
}
int Para1(int para)
{
	char *p;
	int i,j;
	if(p=strstr(ptxt[para],",")){
		if(strstr(p+1,",")){//,��2��������߂�
			return -1;
		}else{//,��1�̂Ƃ�
			sscanf_s(ptxt[para],"%d,%d",&i,&j);
			return j;
		}
	}else{//,���Ȃ��Ƃ�
		return -1;
	}
}


char foundfsize[300][100];
char foundf[300][301];
static int foundn;

void FolderTree2list(CString inPath,CStdioFile *list)
{//2017\1234567820171231121212.jpg
    //�t�@�C���̌���
    CFileFind Finder;
//	char sizeb[301],temp[301],iddate[301];
    CString Path=inPath+_T("\\*.*");
    BOOL bWorking=Finder.FindFile(Path,0);
//	int insn,size;
    while(bWorking){
		bWorking=Finder.FindNextFile();//))break;
 		CString Getpath=Finder.GetFilePath();
		CString Getname=Finder.GetFileName();
//		size=Finder.GetLength();
//		wsprintf(sizeb,"%d",size/1000);// �t�H���_�̂݁@�ċA�I�Ƀt�H���_�A�C�e�����쐬
		if(!(GetFileAttributes(Getpath)&FILE_ATTRIBUTE_DIRECTORY)){
//			if(strstr(Getname,".avi")||strstr(Getname,".wmv")||strstr(Getname,".jpg")){
				//strcat(Getname,"\n");
				list->WriteString(Getpath.Right(31));
				list->WriteString("\n");

//			}
		}else{
			if(Getname!=_T(".")&&Getname!=_T("..")){
				FolderTree2list(Getpath,list);// �t�H���_�̏ꍇ�͎������g���Ăђ����B
			}
		}
	}
	Finder.Close();
}

bool check_jpgwmv(char *fn)
{
	if(strstr(fn,".jpg")||strstr(fn,".avi")||strstr(fn,".wmv"))return true;
	return false;
}
int check_JPGWMV(char *fn)
{
	if(strstr(fn,".jpg")||strstr(fn,".avi")||strstr(fn,".wmv"))return 1;
	if(strstr(fn,".JPG")||strstr(fn,"Jpg")||strstr(fn,".AVI")||strstr(fn,".WMV"))return 2;
	return 0;
}
int static fcnt;

void DB_make(CStdioFile *fn,char *DirName)
{
	WIN32_FIND_DATA fd;  // �񋓏��擾�p
	char Pattern[500];
	char SubFolder[500]; 
	char fdfn[500];
	char fpath[500];
	strcpy_s(Pattern,DirName); // �T���p�X���쐬 
	strcat_s(Pattern,"*.*");
	
	HANDLE hFind;   // �����p�̃n���h�� 

	hFind = FindFirstFile(Pattern,&fd); // �ŏ��̃t�@�C�������� 
	if(hFind==INVALID_HANDLE_VALUE) 
		return;  // �t�@�C���͂P�����݂��Ȃ�(���ۂ� . ..������̂Ŏ��s����Ȃ��͂�) 
	do{ 
//		int jpgwmv;
		strcpy_s(fdfn,fd.cFileName);
		if(strcmp(fdfn,".")!=0 && strcmp(fdfn,"..")!=0){ // . ..�͖��� 
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ // �t�H���_���������ׂ� 
				//���݂̃t�H���_�Ɍ��������t�H���_��ǉ�
				sprintf_s(SubFolder,300,"%s%s\\",DirName,fdfn);
				DB_make(fn,SubFolder);  // �T�u�t�H���_���������� 
			}else{
				if(check_jpgwmv(fdfn)){
					sprintf_s(fpath,"%s%s",DirName,fdfn);
					fn->WriteString(&fpath[strlen(DirName)-5]);//�N���t�H���_���܂߂�
//					fn->WriteString(fdfn);//�t�@�C�����̂�
					fn->WriteString("\n");
					fcnt++;
				}
			}
		} 
	}while(FindNextFile(hFind,&fd)!=0);  // �t�@�C���������Ȃ�܂ő����� 
	FindClose(hFind);  //�n���h������� 
}


int CCapENT2Dlg::SetAllPics(void)
{
	CStdioFile ff;
	char fold[MAX_PATH];
	fcnt = 0;
	sprintf_s(fold, "%s\\gazou\\", CurDir);
	ff.Open(DATA_FN, CFile::modeCreate |
		CFile::modeWrite | CFile::modeRead | CFile::typeText);
	//	ff.SeekToEnd();//�ǋL�̏ꍇ
	DB_make(&ff, fold);
	ff.Abort();
	return fcnt;
}
