#include <winsock2.h>
#include <stdio.h> 
#pragma comment(lib,"WS2_32.lib") 
#pragma warning(disable:4996)

int Login(char* header);
int main()
{
	system("color 0A"); //���ÿ���̨�ı�Ϊǳ��ɫ 
	char *header = "POST http ://gzfa.xdz.com.cn/ModuleBook/PersonalRentBook/Index HTTP/1.1\r\n"
		"Accept : text / html, application / xhtml + xml, image / jxr, */*\r\n"
		"Referer: http://gzfa.xdz.com.cn/ModuleBook/PersonalRentBook/Index\r\n"
		"Accept-Language: zh-Hans-CN,zh-Hans;q=0.5\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36 Edge/14.14393\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Content-Length: 388\r\n"
		"Host: gzfa.xdz.com.cn\r\n"
		"Connection: Keep-Alive\r\n"
		"Pragma: no-cache\r\n"
		"UTPersonalRentBookEntity.RoomTypeID=&UTPersonalRentBookEntity.RoomID=&UTPersonalRentBookEntity.Name=%E9%B1%BC%E9%B1%BC&UTPersonalRentBookEntity.CompanyName=%E6%98%AF%E6%89%93%E5%8F%91&UTPersonalRentBookEntity.CertType=0&UTPersonalRentBookEntity.CertNo=330184198501184115&UTPersonalRentBookEntity.Mobile=13310882188&UTPersonalRentBookEntity.CommunityID=3fec5392-a75a-43db-9dd0-a0970100a6d2	Login(header);\r\n";
	Login(header);
	printf("�������\n");
	system("pause");
	return 0;
}

int Login(char* header)
{
	INT             nret;
	SOCKADDR_IN     addr;
	WSADATA         wsaData;
	SOCKET          Socket;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (Socket == INVALID_SOCKET)
	{
		closesocket(Socket);
		WSACleanup();
		printf("��ȡ���Ӿ��ʧ�ܡ���\n");
		return 0;
	}

	char*   host_name = "gzfa.xdz.com.cn";
	LPHOSTENT lphostent;
	lphostent = gethostbyname(host_name);
	if (lphostent == NULL)
		printf("lphostentΪ�գ�");
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr = *((LPIN_ADDR)*lphostent->h_addr_list);
	// ����SOCKET����  
	nret = connect(Socket, (LPSOCKADDR)&addr, sizeof(SOCKADDR_IN));


	//addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = inet_addr("61.185.220.154");
	//addr.sin_port = htons(8080);
	//nret = connect(Socket, (LPSOCKADDR)&addr, sizeof(SOCKADDR_IN));

	if (nret == SOCKET_ERROR)
	{
		printf("����ʧ�ܡ���\n");
		closesocket(Socket);
		WSACleanup();
		system("pause");
		return 0;
	}

	printf("���ڵ�¼Internet����\n");
	Sleep(1000); //���Ӻ���ʱ1�룬�����޷��������� 
	nret = send(Socket, header, strlen(header), 0);
	if (nret == SOCKET_ERROR)
	{
		printf("�������ݰ�ʱ����");
		closesocket(Socket);
		system("pause");
	}
	char   Dest[3000];
	nret = 1;
	while (nret>0)
	{
		// ���շ������ݰ�  
		nret = recv(Socket, (LPSTR)Dest, sizeof(Dest), 0);
		if (nret>0)
			Dest[nret] = 0;
		else
			Dest[0] = 0;
		// ��ʾ�������ݰ��Ĵ�С������ 
		printf("\nReceived   bytes:%d\n", nret);
		printf("Result:\n%s", Dest);
	}
	closesocket(Socket);
	WSACleanup();
	system("pause");
	return 1;
}
