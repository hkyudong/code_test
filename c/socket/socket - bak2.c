#include <winsock2.h>
#include <stdio.h> 
#pragma comment(lib,"WS2_32.lib") 
#pragma warning(disable:4996)

int Login(char* header);
int main()
{
	system("color 0A"); //���ÿ���̨�ı�Ϊǳ��ɫ 
	char *header = "POST http://gzfa.xdz.com.cn/ModuleBook/PersonalRentBook/Index HTTP/1.1\r\n"
		"Host: gzfa.xdz.com.cn\r\n"
		"Connection: keep-alive\r\n"
		"Content-Length: 397\r\n"
		"Cache-Control: max-age=0\r\n"
		"Origin: http://gzfa.xdz.com.cn\r\n"
		"Upgrade-Insecure-Requests: 1\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.116 Safari/537.36\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
		"Referer: http://gzfa.xdz.com.cn/ModuleBook/PersonalRentBook/Index\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Accept-Language: zh-CN,zh;q=0.8\r\n"
		"\r\n"
		"UTPersonalRentBookEntity.RoomTypeID=&UTPersonalRentBookEntity.RoomID=&UTPersonalRentBookEntity.Name=%E5%A4%A7%E5%B8%88%E5%82%85&UTPersonalRentBookEntity.CompanyName=%E7%AC%AC%E4%B8%89%E6%96%B9&UTPersonalRentBookEntity.CertType=0&UTPersonalRentBookEntity.CertNo=330184198501184115&UTPersonalRentBookEntity.Mobile=18710882105&UTPersonalRentBookEntity.CommunityID=e46fe9e8-bd85-4b87-b68d-a3c501146273\r\n";
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
	printf("��վ��ַ��%s, ����IP��ַ��%s", host_name, inet_ntoa(addr.sin_addr));
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
