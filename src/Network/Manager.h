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

		void setInterface(const char * interface) {
			_interface = interface;
		};

	private:

		static vector<string> INTERFACES;

		const char * _interface = "wlan0";

		static void handleInterfaceProcess(
			int skfd,
			char * ifname,
			char * args[],
			int count
		);

};

}; };
