#ifndef ESPNOW_MANAGER_H
#define ESPNOW_MANAGER_H

#include <esp_now.h>
#include <UtilityManager.h>

#define NUM_MEMBERS		10
#define PRINTSCANRESULTS 	1
#define DATASIZE 			48

typedef struct struct_message {
	const char* boardID;
	const char* remoteAddress;
	const char* message;
	DateTime datetime_sent;
	DateTime datetime_received;
	} struct_message;

struct_message msgOut;
struct_message* msgIn;

esp_now_peer_info_t member;
esp_now_peer_info_t members[NUM_MEMBERS] = {};
const esp_now_peer_info_t* peer = &member;
int memberCount = 0;
bool messageReceived = false;

class ESPNOW_Manager
	{
		private:
		UtilityManager uMan = UtilityManager();

		const char* esp_now_ssid = "AlphaN5";
		const char* esp_now_password = "TT-9058590898";
		const char* esp_now_ssid_prefix = "NIXIEMASTER";

		public:
		ESPNOW_Manager() {}
		~ESPNOW_Manager() {};

		boolean hasUnreadMail() { return messageReceived; }
		void mailRead() { messageReceived = false; }
		void mailReceived() { messageReceived = true; }

		int getMemberCount() {
			return sizeof(members);
			}

		/////////////////////////////////////////////////////////////////
		// MASTER AP SETUP
		/////////////////////////////////////////////////////////////////
		void configMasterAP() {
			bool result = WiFi.softAP(esp_now_ssid, esp_now_password, CHANNEL, 0);

			if (!result) {
				Serial.println("AP Config failed.");
				}
			else {
				Serial.println("AP Config Success. Broadcasting with AP: " + (String)esp_now_ssid);
				}
			}

		/////////////////////////////////////////////////////////////////
		// ESP-NOW SETUP, CALLBACK AND HANDLERS
		/////////////////////////////////////////////////////////////////
		void sendMessage(uint8_t* remoteMac, struct_message& msgOut) {
			bool exists = esp_now_is_peer_exist(remoteMac);
			if (exists) {
				//msgOut.boardID = WiFi.macAddress().toCharArray();
				//msgOut.remoteAddress = remoteMac[6];
				//msgOut.message = "Hi From " + WiFi.macAddress().toCharArray();
				//msgOut.datetime_sent = uMan.getNow();

				esp_err_t result = esp_now_send(remoteMac, (uint8_t*)&msgOut, sizeof(msgOut));
				if (result == ESP_OK) Serial.println("Success");
				else if (result == ESP_ERR_ESPNOW_NOT_INIT) Serial.println("ESPNOW not Init.");
				else if (result == ESP_ERR_ESPNOW_ARG) Serial.println("Invalid Argument");
				else if (result == ESP_ERR_ESPNOW_INTERNAL) Serial.println("Internal Error");
				else if (result == ESP_ERR_ESPNOW_NO_MEM) Serial.println("ESP_ERR_ESPNOW_NO_MEM");
				else if (result == ESP_ERR_ESPNOW_NOT_FOUND) Serial.println("Peer not found.");
				else Serial.println("Not sure what happened");
				}
			}

		// callback when data is sent
		void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
			char macStr[18];
			snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
			Serial.print("Last Packet Sent to: "); Serial.println(macStr);
			Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
			}

		// callback when data is received
		void OnDataRecv(const uint8_t* mac, const uint8_t* msgIn, int len) {

			bool exists = esp_now_is_peer_exist(mac);
			if (!exists) {
				member.channel = CHANNEL;      // pick a channel
				member.encrypt = false;              // no encryption
				memcpy(member.peer_addr, mac, 6);
				esp_now_add_peer(&member);
				//memberList->add
				}

			char macStr[18];
			snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			memcpy(&msgIn, msgIn, sizeof(msgIn));

			// TODO: 
			//showReceivedMessage(*mac, *&msgIn);
			mailReceived();
			}

		// Add Memebers to peer list for communication
		uint8_t memberData = 0;
		void EnrolMembers() {
			memberData++;
			for (int i = 0; i < memberCount; i++) {
				const uint8_t* peer_addr = members[i].peer_addr;
				if (i == 0) { // print only for first member
					Serial.print("Sending: ");
					Serial.println(memberData);
					}
				esp_err_t result = esp_now_send(peer_addr, &memberData, sizeof(memberData));
				Serial.print("Send Status: ");
				if (result == ESP_OK) {
					Serial.println("Success");
					}
				else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
					// How did we get so far!!
					Serial.println("ESPNOW not Init.");
					}
				else if (result == ESP_ERR_ESPNOW_ARG) {
					Serial.println("Invalid Argument");
					}
				else if (result == ESP_ERR_ESPNOW_INTERNAL) {
					Serial.println("Internal Error");
					}
				else if (result == ESP_ERR_ESPNOW_NO_MEM) {
					Serial.println("ESP_ERR_ESPNOW_NO_MEM");
					}
				else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
					Serial.println("Peer not found.");
					}
				else {
					Serial.println("Not sure what happened");
					}
				delay(100);
				}
			}

		// Scan for members in AP mode
		void ScanForMembers() {
			int8_t scanResults = WiFi.scanNetworks();
			// reset memebers
			memset(members, 0, sizeof(members));
			memberCount = 0;
			Serial.println("");
			if (scanResults == 0)  Serial.println("No Members Found");
			else {
				//Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
				for (int i = 0; i < scanResults; ++i) {
					// Print SSID and RSSI for each device found
					String SSID = WiFi.SSID(i);
					int32_t RSSI = WiFi.RSSI(i);
					String BSSIDstr = WiFi.BSSIDstr(i);
					delay(10);

					std::string s = SSID.c_str();
					if (s.rfind("NIXIE", 0) == 0) {
						Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");

						// Get BSSID => Mac Address of the member
						int mac[6];
						if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]))
							{
							for (int ii = 0; ii < 6; ++ii) { members[memberCount].peer_addr[ii] = (uint8_t)mac[ii]; }
							}

						members[memberCount].channel = CHANNEL; // pick a channel
						members[memberCount].encrypt = 0; // no encryption
						memberCount++;
						Serial.println(memberCount + " New Members");
						}
					}
				}

			if (memberCount > 0) { Serial.print(memberCount); Serial.println(" member(s) found, processing.."); }
			//else  { Serial.println("No member Found, trying again."); }

		// clean up ram
			WiFi.scanDelete();
			}

		// Check if the member is already paired with the master If not, pair the member with master
		void manageMembers() {

			if (memberCount == 0) { return; }

			for (int i = 0; i < memberCount; i++) {
				Serial.print("Processing: ");
				for (int ii = 0; ii < 6; ++ii) {
					Serial.print((uint8_t)members[i].peer_addr[ii], HEX);
					if (ii != 5) { Serial.print(":"); }
					}
				Serial.print(" Status: ");

				// check if the peer exists
				bool exists = esp_now_is_peer_exist(members[i].peer_addr);
				if (exists) { Serial.println("Already Paired"); }
				else {
					// member not paired, attempt pair
					esp_err_t addStatus = esp_now_add_peer(&members[i]);
					if (addStatus == ESP_OK) {
						// Pair success
						Serial.println("Pair success");
						}
					else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
						// How did we get so far!!
						Serial.println("ESPNOW Not Init");
						}
					else if (addStatus == ESP_ERR_ESPNOW_ARG) {
						Serial.println("Add Peer - Invalid Argument");
						}
					else if (addStatus == ESP_ERR_ESPNOW_FULL) {
						Serial.println("Peer list full");
						}
					else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
						Serial.println("Out of memory");
						}
					else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
						Serial.println("Peer Exists");
						}
					else {
						Serial.println("Not sure what happened");
						}
					delay(100);
					}
				}
			}

		// INITIALIZE ESP-NOW
		void initMesh() {

			messageReceived = false;
			if (esp_now_init() == ESP_OK) {
				Serial.println("ESPNow Init Success");
				}
			else {
				Serial.println("ESPNow Init Failed");
				while (1);
				}
			// TDOD: FIX CB				
			esp_now_register_send_cb(OnDataSent);
			esp_now_register_recv_cb(OnDataRecv);
			}
	};
#endif