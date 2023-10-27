#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

using namespace std;
#define MAX 500
#define port 5200

int main()
{
	int cS , sS , receiveMsgSize;
	cS = socket(AF_INET , SOCK_STREAM , 0);
	if(cS < 0)
        {
		cout << "Unable to create CLIENT SOCKET.." << endl;
		return 0;
        }
	struct sockaddr_in serAddr , cliAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = inet_addr("127.0.0.100");
	serAddr.sin_port = htons(port);
	if(connect(cS,(struct sockaddr*) & serAddr,sizeof(serAddr)) < 0)
	{
		cout << "Connection Failed..." << endl;
		return 0;
	}
	else
	{
		cout << "\t\t\tConnection Success..." << endl;
	}
	while(1)
	{
		string s;
		char input[MAX];
		cout << "Client : ";
		getline(cin , s);
		int n = s.size();
		for(int i = 0 ; i < n ; i++)
		{
			input[i] = s[i];
		}
		input[n] = '\0';
		send(cS , input , strlen(input)+1 , 0);
		char receiveMessage[MAX];
		int rMsgSize = recv(cS , receiveMessage , MAX , 0);
		if(rMsgSize < 0)
		{
			cout << "Packet recieve failed." << endl;
			return 0;
		}
		else if(rMsgSize == 0)
		{
			cout << "Server is off." << endl;
			return 0;
		}
		if(receiveMessage[0] == 'b' && receiveMessage[1] == 'y' && receiveMessage[2] == 'e')
		{
			cout << "\nConnection ended... take care bye bye... " <<endl;
			break;
		}
		cout << "Msg Received From Server : " << receiveMessage <<endl;
	}
	close(cS);
	return 0;
}
