/**
 * Basic manager for wifi and other networks
 */
#pragma once

#include <string>
#include <vector>

#include "Network.h"


using std::string;
using std::vector;


namespace Orza { namespace Network {


class Manager {

	public:

		Manager();

		vector<Network*> getNetworks();

		vector<string> getNetworkSSIDs();

		void connect( string ssid, string pass );

		vector<string> getInterfaces(bool rescan = false);

		void setInterface(string interface) {
			_interface = interface;
		};

		string getIP();

	private:

		static vector<string> INTERFACES;

		string _interface = string("wlan0");

		static void handleInterfaceProcess(
			int skfd,
			char * ifname,
			char * args[],
			int count
		);

};

}; };
