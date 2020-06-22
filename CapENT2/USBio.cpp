#include "stdafx.h"
#include "usbhid.h"
#include "setupapi.h"//setupapi.lib　をプロジェクト・設定・リンクからちゃんと設定しておく
#define MAX_DEVS 64 // 認識できるUSB-IOの最大数
#define MAX_DEV 64 // 認識できるUSB-IOの最大数
#define IOREAD_WAIT 50 // 待ち時間
int uio_free ();
int uio_inp ( int* p1, int port, int p3, int p4 );
int uio_SendRecv(BYTE *sendData,BYTE *recvData);
int uio_out ( int port, int value, int p3, int p4 );
int uio_find();
// 対応しているUSB-IO
struct USBDEVID{
	unsigned short vid; // Vender ID
	unsigned short pid; // Product ID
} usbdevs[]={
//	{0x1352, 0x0110}, // USB-FSIO
	{0x1352, 0x100}, // Km2Net
	{0x1352, 0x0120}, // USB-IO2.0
	{0x1352, 0x0121}// USB-IO2.0(AKI)
//	{0x1352, 0x0111}, // USB-FSIO30
};


//HID API (from w2k DDK)
HINSTANCE hHID_DLL=NULL; // hid.dll handle
_HidD_GetAttributes HidD_GetAttributes;
_HidD_GetHidGuid HidD_GetHidGuid;
_HidD_GetPreparsedData HidD_GetPreparsedData;
_HidD_FreePreparsedData HidD_FreePreparsedData;
_HidP_GetCaps HidP_GetCaps;
_HidP_GetValueCaps HidP_GetValueCaps;


char DevPath[MAX_DEVS][MAX_PATH]; // USB-IO device path.
int Devs=0; // Number of USB-IO
int Dev=0;  // Current device (0-MAX_DEV)
int InputByte=9;
int OutputByte=9;
HANDLE hHID=NULL; // Handle

bool LoadHidDLL(){
	hHID_DLL=LoadLibrary("hid.dll");
	if(!hHID_DLL){
		MessageBox(NULL,"Error at Load 'hid.dll'","ERRR",MB_OK);
		return false;
	}
	HidD_GetAttributes
		=(_HidD_GetAttributes)GetProcAddress(hHID_DLL,"HidD_GetAttributes");
	if(!HidD_GetAttributes){
		MessageBox(NULL,"Error at HidD_GetAttributes","ERR",MB_OK);
		return false;
	}
	HidD_GetHidGuid
		=(_HidD_GetHidGuid)GetProcAddress(hHID_DLL,"HidD_GetHidGuid");
	if(!HidD_GetHidGuid){
		MessageBox(NULL,"Error at HidD_GetHidGuid","ERR",MB_OK);
		return false;
	}
	HidD_GetPreparsedData
		=(_HidD_GetPreparsedData)GetProcAddress(hHID_DLL,"HidD_GetPreparsedData");
	HidD_FreePreparsedData
		=(_HidD_FreePreparsedData)GetProcAddress(hHID_DLL,"HidD_FreePreparsedData");
	HidP_GetCaps
		=(_HidP_GetCaps)GetProcAddress(hHID_DLL,"HidP_GetCaps");
	HidP_GetValueCaps
		=(_HidP_GetValueCaps)GetProcAddress(hHID_DLL,"HidP_GetValueCaps");
	return true;
}

////////////////////////////////////////////////////////////////////////
// HIDディバイスを開く
void OpenTheHid(int d){
	if (d>=Devs) return;
	Dev=d;
	if (hHID) {
		CloseHandle(hHID);
		hHID=NULL;
	}
	// 開く
	hHID = CreateFile(DevPath[Dev],
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,NULL);

	// 入出力長を得る
	HIDP_CAPS Caps;
	PHIDP_PREPARSED_DATA PreparsedData;
	HidD_GetPreparsedData(hHID,&PreparsedData);
	HidP_GetCaps(PreparsedData,&Caps);
	HidD_FreePreparsedData(PreparsedData);
	InputByte=Caps.InputReportByteLength;
	OutputByte=Caps.OutputReportByteLength;
}
// HIDディバイスを閉じる
void CloseTheHid(){
	if (hHID) {
		CloseHandle(hHID);
		hHID=NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// HIDディバイス一覧からUSBIOを検索

int FindHid(){
	int i=0,devnum;
	ULONG Needed,l;
	GUID HidGuid;
	HDEVINFO DeviceInfoSet;
	HIDD_ATTRIBUTES DeviceAttributes;
	SP_DEVICE_INTERFACE_DATA DevData;
	PSP_INTERFACE_DEVICE_DETAIL_DATA DevDetail;
	//SP_DEVICE_INTERFACE_DETAIL_DATA *MyDeviceInterfaceDetailData;

	DeviceAttributes.Size=sizeof(HIDD_ATTRIBUTES);
	DevData.cbSize=sizeof(_SP_DEVICE_INTERFACE_DATA);

	HidD_GetHidGuid(&HidGuid);
	DeviceInfoSet=SetupDiGetClassDevs(&HidGuid,NULL,
		NULL,DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	CloseTheHid();
	Devs=0;
	HANDLE hDEV;

	while(SetupDiEnumDeviceInterfaces(DeviceInfoSet,0,&HidGuid,i++,&DevData)){
		SetupDiGetDeviceInterfaceDetail(DeviceInfoSet,&DevData,
			NULL,0,&Needed,0);
		l=Needed;
		DevDetail=(SP_DEVICE_INTERFACE_DETAIL_DATA*)GlobalAlloc(GPTR,l+4);
		DevDetail->cbSize=sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		SetupDiGetDeviceInterfaceDetail(DeviceInfoSet,&DevData,
			DevDetail,l,&Needed,0);
		hDEV = CreateFile(
			DevDetail->DevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,NULL);
		if(hDEV!=INVALID_HANDLE_VALUE) {
			HidD_GetAttributes(hDEV,&DeviceAttributes);
			// USB-IOかどうか調べる
			int k;
			for(k=0;k<sizeof(usbdevs)/sizeof(USBDEVID);k++){
				if (DeviceAttributes.VendorID==usbdevs[k].vid
					&& DeviceAttributes.ProductID==usbdevs[k].pid) {
					if(Devs<MAX_DEVS) {
						wsprintf(DevPath[Devs],"%s",DevDetail->DevicePath);
						//strcpy(DevPath[Devs],DevDetail->DevicePath);
						Devs++;
						devnum=k;
					}
					break;
				}
			}
			CloseHandle(hDEV);
		}
		GlobalFree(DevDetail);
	}
	if (Devs) {
		OpenTheHid(0);
	}
	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
	if(Devs==0)return 0;
	else return 10*Devs+devnum;
}


/////////////////////////////////////////////////////////////////////////////
int uio_find()
//BOOL WINAPI uio_find( int p1, int p2, int p3, int p4 )
{
	int devn;
	if(!hHID_DLL){
		// 読み込まれていなければ読み込む
		if (!LoadHidDLL())return -1;
	}
	if((devn=FindHid())==0){ // USB-IO検索
		return -2;
	}
	else return devn%10;
}

//int uio_out ( int p1, int p2, int p3, int p4 )
//BOOL WINAPI uio_out ( int p1, int p2, int p3, int p4 )
//EXPORT BOOL WINAPI uio_out ( int port, int value, int p3, int p4 )
int uio_out ( int port, int value, int p3, int p4 )
{
	if(!Devs){
		uio_find();
	}
	ULONG sz;
	BYTE dat[16]={0x00,0x01+(port&1),value,0x00};
	if(p3){
		dat[1]=0x10+(port&3);
	}
	if(!WriteFile(hHID,dat,OutputByte,&sz,NULL))
		return -1;
	return 0;
}
int uio_SendRecv(BYTE *sendData,BYTE *recvData)
{
	int i;
	ULONG NumberOfBytesWritten,NumberOfBytesRead;
	BYTE wrtData[130];//OutputByte-1];
	BYTE readData[130];
	wrtData[0]=0;
	for(i=0;i<64;i++)wrtData[i+1]=sendData[i];
	WriteFile(hHID,wrtData,OutputByte,&NumberOfBytesWritten,NULL);
	while(1){
		ReadFile(hHID,readData,InputByte,&NumberOfBytesRead,NULL);
		if(wrtData[64]==readData[64])break;
	}
	for(i=0;i<64;i++)recvData[i]=readData[i+1];
	return 0;
}


//int uio_inp ( int* p1, int p2, int p3, int p4)
//BOOL WINAPI uio_inp ( int* p1, int p2, int p3, int p4 )
//EXPORT BOOL WINAPI uio_inp ( int* p1, int port, int p3, int p4 )
int uio_inp ( int* p1, int port, int p3, int p4 )
{
	static int n=0;
	if(!Devs){
		uio_find();
	}
	ULONG sz;
	n++;
	BYTE idat[128],odat[16]={0x00,0x03+(port&1),0x00,0x00};
	odat[7]=n; // 受信確認用ID (XP対策)
	if(p3){
		odat[1]=0x14+(port&3);
	}
	if(!WriteFile(hHID,odat,OutputByte,&sz,NULL))
		return -1;
	int i=0;
	do { // (XPだと260ms経つか，連続して32回くらい読み取るとデータが返る)
		//Sleep(IOREAD_WAIT);
		if(!ReadFile(hHID,idat,InputByte,&sz,NULL))
			return -2;
		if (++i>100) return -3;
	}while (idat[7]!=odat[7]);
	*p1=idat[2];
	return 0;
}

int uio_free ()
//BOOL WINAPI uio_free ( int p1, int p2, int p3, int p4 )
{
	if(hHID){
		CloseTheHid();
	}
	if(hHID_DLL){
		FreeLibrary(hHID_DLL);
		hHID_DLL=NULL;
	}
	Devs=0;
	return 0;
}
