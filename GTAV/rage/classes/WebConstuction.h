#pragma once

class CNetData {
public:
	char* Data; //0x0000
}; //Size: 0x0008

class CHttpRequest {
public:
	char pad_0000[16]; //0x0000
	class CNetData* RequestData; //0x0010
	char pad_0018[64]; //0x0018
	char* ResponseHeaders; //0x0058
	char pad_0060[40]; //0x0060
	char* RequestHeaders; //0x0088
	char pad_0090[1112]; //0x0090
	class CNetData* ResponseData; //0x04E8
	char pad_04F0[4]; //0x04F0
	uint16_t ContentLength; //0x04F4
	char pad_04F6[18]; //0x04F6
	char* Scheme; //0x0508
	char* Host; //0x0510
	char* Path; //0x0518
	char pad_0520[72]; //0x0520
	char* UserAgent; //0x0568
	char pad_0570[3032]; //0x0570
	char* URLRequest; //0x1148
	char pad_1150[1432]; //0x1150
}; //Size: 0x16E8