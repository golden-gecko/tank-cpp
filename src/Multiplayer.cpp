

//------------------------------------------------------------------------------

#include "Tank2007.h"

#include "Multiplayer.h"

#include "Console.h"
#include "Graphics.h"

//------------------------------------------------------------------------------

Multiplayer::Multiplayer() :
	mState(MS_IDLE),
	mHost("127.0.0.1"),
	mServerPort(2007),
	mClientPort(7002),
	mRetryCount(2),
	mServer(RakNetworkFactory::GetRakServerInterface()),
	mClient(RakNetworkFactory::GetRakClientInterface()),
	mPacket(NULL),
	mThread(NULL)
{
}

//------------------------------------------------------------------------------

Multiplayer::~Multiplayer()
{
	disconnect();

	RakNetworkFactory::DestroyRakServerInterface(mServer);
	RakNetworkFactory::DestroyRakClientInterface(mClient);
}

//------------------------------------------------------------------------------

void Multiplayer::startGame()
{
	disconnect();

	mState = MS_SERVER;

	mServer->InitializeSecurity(0, 0);
	mServer->SetPassword("tank2007");

	if (mServer->Start(8, 0, 30, mServerPort)) {

		mThread = CreateThread(
			NULL,
			0,
			(unsigned long (__stdcall*)(void*))this->runThread,
			(void*)this,
			0,
			NULL);

		Console::getSingletonPtr()->write("Game started.");
	}
	else
	{
		Console::getSingletonPtr()->write("Error while trying to host a new game.");
	}
}

//------------------------------------------------------------------------------

void Multiplayer::joinGame(const std::string& host)
{
	disconnect();

	mState = MS_CLIENT;
	mHost = host;

	mClient->InitializeSecurity(0, 0);
	mClient->SetPassword("tank2007");

	srand(GetTickCount());

	mClientPort += 1024 + rand() % 50;

	if (mClient->Connect(mHost.c_str(), mServerPort, mClientPort, 0, 0)) {

		mThread = CreateThread(
			NULL,
			0,
			(unsigned long (__stdcall*)(void*))this->runThread,
			(void*)this,
			0,
			NULL);

		Console::getSingletonPtr()->write("Connecting...");
	}
	else
	{
		Console::getSingletonPtr()->write("Error while trying to connect to a server.");
	}
}

//------------------------------------------------------------------------------

int Multiplayer::runThread(void* pThis)
{
	((Multiplayer*)(pThis))->thread();

	return 0;
}

//------------------------------------------------------------------------------

void Multiplayer::thread()
{
	while (1)
	{
		switch (mState)
		{
			case MS_SERVER:	mPacket = mServer->Receive();	break;
			case MS_CLIENT:	mPacket = mClient->Receive();	break;
		}

		if (mPacket == NULL)

			continue;

		switch (mPacket->data[0])
		{
			case ID_DISCONNECTION_NOTIFICATION:

				Console::getSingletonPtr()->write("ID_DISCONNECTION_NOTIFICATION");

				break;

			case ID_REMOTE_DISCONNECTION_NOTIFICATION:

				Console::getSingletonPtr()->write("ID_REMOTE_DISCONNECTION_NOTIFICATION");

				break;

			case ID_REMOTE_CONNECTION_LOST:

				Console::getSingletonPtr()->write("ID_REMOTE_CONNECTION_LOST");

				break;

			case ID_REMOTE_NEW_INCOMING_CONNECTION:

				Console::getSingletonPtr()->write("ID_REMOTE_NEW_INCOMING_CONNECTION");

				break;

			case ID_REMOTE_EXISTING_CONNECTION:

				Console::getSingletonPtr()->write("ID_REMOTE_EXISTING_CONNECTION");

				break;

			case ID_CONNECTION_BANNED:

				Console::getSingletonPtr()->write("ID_CONNECTION_BANNED");

				break;

			case ID_NEW_INCOMING_CONNECTION:

				Console::getSingletonPtr()->write("ID_NEW_INCOMING_CONNECTION");

				break;

			case ID_RECEIVED_STATIC_DATA:

				switch (mState)
				{
					case MS_SERVER:
						
						mServer->GetStaticServerData();

						Console::getSingletonPtr()->write("ID_RECEIVED_STATIC_DATA");
						
						break;

					case MS_CLIENT:
						
						mClient->GetStaticServerData();
						
						Console::getSingletonPtr()->write("ID_RECEIVED_STATIC_DATA");

						break;
				}

				break;

			case ID_MODIFIED_PACKET:

				Console::getSingletonPtr()->write("ID_MODIFIED_PACKET");

				break;

			case ID_CONNECTION_LOST:

				Console::getSingletonPtr()->write("ID_CONNECTION_LOST");
				
				break;

			case ID_CONNECTION_ATTEMPT_FAILED:

				Console::getSingletonPtr()->write("ID_CONNECTION_ATTEMPT_FAILED");

				if (mRetryCount)
				{
					joinGame("127.0.0.1");

					mRetryCount--;
				}
				else
				{
					mRetryCount = 2;
				}

				break;

			case ID_NO_FREE_INCOMING_CONNECTIONS:

				Console::getSingletonPtr()->write("ID_NO_FREE_INCOMING_CONNECTIONS");

				break;

			case ID_INVALID_PASSWORD:

				Console::getSingletonPtr()->write("ID_INVALID_PASSWORD");

				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:

				Console::getSingletonPtr()->write("ID_CONNECTION_REQUEST_ACCEPTED");

				break;

			case ID_INPUT_KEY_DOWN:

				{
					Console::getSingletonPtr()->write("ID_INPUT_KEY_DOWN");

					RakNet::BitStream stream(mPacket->data, mPacket->length, false);

					if (mState == MS_SERVER)

						mServer->Send(&stream, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, mPacket->playerId, true);

					int i;
					stream.Read(i);
					unsigned char c;
					stream.Read(c);

					Graphics::getSingletonPtr()->onKeyDown2(c);
				}

				break;

			case ID_INPUT_KEY_UP:

				{
					Console::getSingletonPtr()->write("ID_INPUT_KEY_UP");

					RakNet::BitStream stream(mPacket->data, mPacket->length, false);

					if (mState == MS_SERVER)

						mServer->Send(&stream, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, mPacket->playerId, true);

					int i;
					stream.Read(i);
					unsigned char c;
					stream.Read(c);

					Graphics::getSingletonPtr()->onKeyUp2(c);
				}

				break;
		}

		switch (mState)
		{
			case MS_SERVER:	mServer->DeallocatePacket(mPacket);	break;
			case MS_CLIENT:	mClient->DeallocatePacket(mPacket);	break;
		}
	}
}

//------------------------------------------------------------------------------

void Multiplayer::disconnect()
{
	mState = MS_IDLE;
	mHost = "127.0.0.1";
	mServerPort = 2007;
	mClientPort = 7002;

	switch (mState)
	{
		case MS_CLIENT:
			
			CloseHandle(mThread);

			mClient->Disconnect(300);
			
			break;

		case MS_SERVER:
			
			CloseHandle(mThread);

			mServer->Disconnect(300);
			
			break;
	}
}

//------------------------------------------------------------------------------

void Multiplayer::onKeyDown(unsigned char key)
{
	switch (mState)
	{
		case MS_SERVER:

			{
				RakNet::BitStream stream;

				stream.Write(ID_INPUT_KEY_DOWN);
				stream.Write(key);

				mServer->Send(&stream, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, UNASSIGNED_PLAYER_ID, true);
			}

			break;

		case MS_CLIENT:

			{
				RakNet::BitStream stream;

				stream.Write(ID_INPUT_KEY_DOWN);
				stream.Write(key);

				mClient->Send(&stream, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
			}

			break;
	}
}

//------------------------------------------------------------------------------

void Multiplayer::onKeyUp(unsigned char key)
{
	switch (mState)
	{
		case MS_SERVER:

			{
				RakNet::BitStream stream;

				stream.Write(ID_INPUT_KEY_UP);
				stream.Write(key);

				mServer->Send(&stream, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, UNASSIGNED_PLAYER_ID, true);
			}

			break;

		case MS_CLIENT:

			{
				RakNet::BitStream stream;

				stream.Write(ID_INPUT_KEY_UP);
				stream.Write(key);

				mClient->Send(&stream, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
			}

			break;
	}
}

//------------------------------------------------------------------------------
