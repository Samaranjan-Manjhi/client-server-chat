#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
#define MAX 500
#define port 5200

int main()
{
	int sSHandler = socket(AF_INET , SOCK_STREAM , 0);
	if(sSHandler < 0)
        {
		cout << "Unable to create SERVER SOCKET.";
		return 0;
	}
	struct sockaddr_in serAddr , clAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int bindStatus = bind(sSHandler , (struct sockaddr*) & serAddr , sizeof(serAddr));
	if(bindStatus < 0)
    	{
		cout << "Server Socket Connection failed" << endl;
		return 0;
	}
	int listenStatus = listen(sSHandler , 5);
	if(listenStatus < 0)
        {	
		cout << "Listner has failed" << endl;
		return 0;
        }
	cout << "\t\t\t...Waiting for connections... \n\n\n";
	char buff[MAX];
	int cSHandler;
	socklen_t len = sizeof(clAddr);
	int connection;
	if((connection = accept(sSHandler , (struct sockaddr*) & clAddr , &len)) < 0)
    	{
		cout << "Server avoid the connection request." << endl;
		return 0;
	}
	else
    	{
		cout << "Server accepted the connection request." <<endl;
	}
	while(1)
        {
            int rMsgSize;

            if((rMsgSize  = recv(connection , buff , MAX , 0)) > 0)
            {
		cout << "Msg Received From Client : " << buff << endl;
		if(buff[0] == 'b' && buff[1] == 'y' && buff[2] == 'e')
		{
			cout << "Server : Bye! We will meet again..."<< "\n";
			cout << "\nConnection ended... take care bye bye..."<<endl;
			send(connection , buff , strlen(buff)+1 , 0);
			break;
		}
		cout << "Server : ";
		char input[MAX];
		string s;
		getline(cin , s);
		int n = s.size();
		for(int i = 0 ; i < n ; i++)
                {
			input[i] = s[i];
		}
		input[n] = '\0';
		send(connection , input , strlen(input)+1 , 0);
	    }
	}
	close(sSHandler);
	return 0;
}
