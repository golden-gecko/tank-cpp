
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.hpp"

//------------------------------------------------------------------------------

class Multiplayer : public Ogre::Singleton<Multiplayer>
{
	public:

		enum MultiplayerState
		{
			MS_IDLE		= 0x00,
			MS_CLIENT	= 0x01,
			MS_SERVER	= 0x02
		};

		enum MultiplayerMessage
		{
			ID_INPUT_KEY_DOWN	= ID_USER_PACKET_ENUM + 0x01,
			ID_INPUT_KEY_UP		= ID_USER_PACKET_ENUM + 0x02,
		};

	private:

		MultiplayerState	mState;
		std::string			mHost;
		int					mServerPort;
		int					mClientPort;
		int					mRetryCount;

		RakServerInterface*	mServer;
		RakClientInterface*	mClient;
		Packet*				mPacket;

		HANDLE				mThread;

	public:

		Multiplayer();

		~Multiplayer();

		void startGame();

		void joinGame(const std::string& host);

		static int runThread(void* pThis);

		void thread();

		void disconnect();

		void onKeyDown(unsigned char key);

		void onKeyUp(unsigned char key);

		MultiplayerState getState()
		{
			return mState;
		}
		std::string getHost()
		{
			return mHost;
		}
		int getServerPort()
		{
			return mServerPort;
		}
		int getClientPort()
		{
			return mClientPort;
		}
};

//------------------------------------------------------------------------------
