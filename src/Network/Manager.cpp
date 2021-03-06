/**
 * Basic manager for wifi and other networks
 */
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdexcept>
#include <string>
#include <vector>

//Network libs
#include <iwlib.h>

#include <netdb.h>
#include <sys/types.h>
#include <ifaddrs.h>

#include "Manager.h"


using std::string;
using std::vector;


namespace Orza { namespace Network {


vector<string> Manager::INTERFACES = {};

Manager::Manager() {

};


vector<Network*> Manager::getNetworks() {

	vector<Network*> out;

	wireless_scan_head head;
	wireless_scan *result;
	iwrange range;
	int sock;

	/* Open socket to kernel */
	sock = iw_sockets_open();

	/* Get some metadata to use for scanning */
	std::cout << "NETWORKS FOR " << _interface << "\n";

	if (iw_get_range_info(sock, _interface.c_str(), &range) < 0) {
		throw std::runtime_error(
			"Error during iw_get_range_info. Aborting."
		);
	}

	/* Perform the scan */
	if( iw_scan( sock, (char*) _interface.c_str(), range.we_version_compiled, &head ) < 0 ) {
		throw std::runtime_error(
			"Error during iw_scan. Aborting."
		);
	}


	/* Traverse the results */

	result = head.result;

	while (NULL != result) {

		Network * net = new Network;

		net->ssid = result->b.essid;

		result = result->next;


		//Hide hidden

		if( net->ssid.empty() ) { continue; }

		//net->wep = result->b.key;

		out.push_back( net );

	}

	return out;

};

vector<string> Manager::getInterfaces(bool rescan) {

	//already scanned
	if(INTERFACES.size() && !rescan) {
		return INTERFACES;
	}

	int skfd;

	if((skfd = iw_sockets_open()) < 0) {
		std::cout << "No devices iw_sockets_open error\n";
		return {};
	}

	iw_enum_devices(skfd, (iw_enum_handler)handleInterfaceProcess, nullptr, 0);

	iw_sockets_close(skfd);

	return INTERFACES;
};


//Implement of iw_enum_handler for iwlib
void Manager::handleInterfaceProcess(
	int skfd,
	char * ifname,
	char * args[],
	int count
) {

	INTERFACES.push_back(ifname);

};


/**
 * Get networks ssids loop through getter
 */

vector<string> Manager::getNetworkSSIDs() {

	vector<string> out;

	vector<Network*> nets = getNetworks();

	if( nets.empty() ) { return out; }


	//Loop through push back SSIDs

	vector<Network*>::const_iterator it;

	for( it = nets.begin(); it != nets.end(); ++ it ) {

		out.push_back( (*it)->ssid );

	}

	return out;

};

string Manager::getIP() {

	struct ifaddrs *ifaddr, *ifa;

	int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		throw std::runtime_error("Could not read ifaddrs");
		return "";
	}

	//ifap[0]->ifa_addr->sa_data;
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		//Check valid
		if (ifa->ifa_addr == NULL) {
			continue;
		}

		//Check right interface
		string ifname(ifa->ifa_name);
		if (_interface != ifname) {
			continue;
		}

		family = ifa->ifa_addr->sa_family;

		if (family != AF_INET && family != AF_INET6) {
			continue;
		}

		s = getnameinfo(ifa->ifa_addr,
			(family == AF_INET) ? sizeof(struct sockaddr_in) :
			sizeof(struct sockaddr_in6),
			host, NI_MAXHOST,
			NULL, 0, NI_NUMERICHOST
		);

		if (s != 0) {
			//printf("getnameinfo() failed: %s\n", gai_strerror(s));
			throw std::runtime_error("getnameinfo() failed");
		}

		freeifaddrs(ifaddr);
		return (string)host;
	}

	freeifaddrs(ifaddr);
	return "";
	//netent net = getnetbyname(_interface);
};


/**
 * Main connect to new network
 */

void Manager::connect( string ssid, string pass ) {

	char * cmd = (char*) malloc(
		sizeof( ssid )
		+ sizeof( pass )
		+ 100
	);

	sprintf( cmd, "wpa_passphrase '%s' '%s' | sudo tee -a /etc/wpa_supplicant.conf", ssid.c_str(), pass.c_str() );

	std::cout << cmd << "\n";


	//Restart wpa_supplicant
	//@TODO specify interface

	system( cmd );
	system( "sudo wpa_supplicant -B -D wext -i wlan0 -c /etc/wpa_supplicant.conf" );

};

}; };
